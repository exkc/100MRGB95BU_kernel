#ifndef _REG_DDRC_M2_h
#define _REG_DDRC_M2_h
//Header File for DDRC_M2 in \O24\O24_DRAM_M2_Register_Manual.xls

#define REG_DDRC_M2_DRAM_CONF                                               (APB_DDRC_M2_BASE+0x0000)
#define REG_DDRC_M2_MODE_SEL                                                (APB_DDRC_M2_BASE+0x0004)
#define REG_DDRC_M2_BASE_PERIOD                                             (APB_DDRC_M2_BASE+0x0008)
#define REG_DDRC_M2_ALP                                                     (APB_DDRC_M2_BASE+0x0100)
#define REG_DDRC_M2_CGL                                                     (APB_DDRC_M2_BASE+0x0104)
#define REG_DDRC_M2_CGL_MON                                                 (APB_DDRC_M2_BASE+0x0108)
#define REG_DDRC_M2_PERFMON                                                 (APB_DDRC_M2_BASE+0x0200)
#define REG_DDRC_M2_PERFMON_EMG_MAX                                         (APB_DDRC_M2_BASE+0x0204)
#define REG_DDRC_M2_PERFMON_W0                                              (APB_DDRC_M2_BASE+0x0210)
#define REG_DDRC_M2_PERFMON_W1                                              (APB_DDRC_M2_BASE+0x0214)
#define REG_DDRC_M2_PERFMON_W2                                              (APB_DDRC_M2_BASE+0x0218)
#define REG_DDRC_M2_PERFMON_W3                                              (APB_DDRC_M2_BASE+0x021C)
#define REG_DDRC_M2_PERFMON_R0                                              (APB_DDRC_M2_BASE+0x0220)
#define REG_DDRC_M2_PERFMON_R1                                              (APB_DDRC_M2_BASE+0x0224)
#define REG_DDRC_M2_PERFMON_R2                                              (APB_DDRC_M2_BASE+0x0228)
#define REG_DDRC_M2_PERFMON_R3                                              (APB_DDRC_M2_BASE+0x022C)
#define REG_DDRC_M2_LATMON                                                  (APB_DDRC_M2_BASE+0x0230)
#define REG_DDRC_M2_DFS                                                     (APB_DDRC_M2_BASE+0x0300)
#define REG_DDRC_M2_DFS_RESULT                                              (APB_DDRC_M2_BASE+0x0304)
#define REG_DDRC_M2_ADDR_MAP                                                (APB_DDRC_M2_BASE+0x0400)
#define REG_DDRC_M2_COMMON                                                  (APB_DDRC_M2_BASE+0x0404)
#define REG_DDRC_M2_DATA_ENC0                                               (APB_DDRC_M2_BASE+0x0408)
#define REG_DDRC_M2_DATA_ENC1                                               (APB_DDRC_M2_BASE+0x040C)
#define REG_DDRC_M2_RD_URG                                                  (APB_DDRC_M2_BASE+0x0500)
#define REG_DDRC_M2_WR_URG                                                  (APB_DDRC_M2_BASE+0x0504)
#define REG_DDRC_M2_FIFO_RDY                                                (APB_DDRC_M2_BASE+0x1000)
#define REG_DDRC_M2_FIFO_STATUS                                             (APB_DDRC_M2_BASE+0x1004)
#define REG_DDRC_M2_FIFO_CONF                                               (APB_DDRC_M2_BASE+0x1008)
#define REG_DDRC_M2_LIMITER_EN                                              (APB_DDRC_M2_BASE+0x1010)
#define REG_DDRC_M2_LIMITER_AW_THR                                          (APB_DDRC_M2_BASE+0x1014)
#define REG_DDRC_M2_LIMITER_W_THR                                           (APB_DDRC_M2_BASE+0x1018)
#define REG_DDRC_M2_LIMITER_AR_THR                                          (APB_DDRC_M2_BASE+0x1024)
#define REG_DDRC_M2_LIMITER_R_THR                                           (APB_DDRC_M2_BASE+0x1028)
#define REG_DDRC_M2_FIFO_MUX                                                (APB_DDRC_M2_BASE+0x1100)
#define REG_DDRC_M2_FIFO_MUX_MAX                                            (APB_DDRC_M2_BASE+0x1104)
#define REG_DDRC_M2_FIFO_MUX_WR_PRT                                         (APB_DDRC_M2_BASE+0x1108)
#define REG_DDRC_M2_FIFO_MUX_RD_PRT                                         (APB_DDRC_M2_BASE+0x110C)
#define REG_DDRC_M2_FIFO_MUX_PRT_MAX                                        (APB_DDRC_M2_BASE+0x1110)
#define REG_DDRC_M2_PQ                                                      (APB_DDRC_M2_BASE+0x2000)
#define REG_DDRC_M2_BQ                                                      (APB_DDRC_M2_BASE+0x2004)
#define REG_DDRC_M2_BQ_RW_THR                                               (APB_DDRC_M2_BASE+0x2008)
#define REG_DDRC_M2_BQ_HYB_STV                                              (APB_DDRC_M2_BASE+0x200C)
#define REG_DDRC_M2_LPD4_MAIN_FSM_INIT_0                                    (APB_DDRC_M2_BASE+0x3000)
#define REG_DDRC_M2_LPD4_MAIN_FSM_INIT_1                                    (APB_DDRC_M2_BASE+0x3004)
#define REG_DDRC_M2_LPD4_MAIN_FSM_INIT_2                                    (APB_DDRC_M2_BASE+0x3008)
#define REG_DDRC_M2_LPD4_MAIN_FSM_CTRL                                      (APB_DDRC_M2_BASE+0x300C)
#define REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_0                                (APB_DDRC_M2_BASE+0x3010)
#define REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_1                                (APB_DDRC_M2_BASE+0x3014)
#define REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_2                                (APB_DDRC_M2_BASE+0x3018)
#define REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_3                                (APB_DDRC_M2_BASE+0x301C)
#define REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_4                                (APB_DDRC_M2_BASE+0x3020)
#define REG_DDRC_M2_LPD4_MAIN_FSM_DFS_MRW                                   (APB_DDRC_M2_BASE+0x3024)
#define REG_DDRC_M2_LPD4_MAIN_FSM_CTRLUPD                                   (APB_DDRC_M2_BASE+0x3028)
#define REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_0                                (APB_DDRC_M2_BASE+0x302C)
#define REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_1                                (APB_DDRC_M2_BASE+0x3030)
#define REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_2                                (APB_DDRC_M2_BASE+0x3034)
#define REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_3                                (APB_DDRC_M2_BASE+0x3038)
#define REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_4                                (APB_DDRC_M2_BASE+0x303C)
#define REG_DDRC_M2_LPD4_MR_CTRL_0                                          (APB_DDRC_M2_BASE+0x3050)
#define REG_DDRC_M2_LPD4_MR_CTRL_1                                          (APB_DDRC_M2_BASE+0x3054)
#define REG_DDRC_M2_LPD4_MR_CTRL_2                                          (APB_DDRC_M2_BASE+0x3058)
#define REG_DDRC_M2_LPD4_REF_REQ_CTRL                                       (APB_DDRC_M2_BASE+0x3060)
#define REG_DDRC_M2_LPD4_REF_CTRL                                           (APB_DDRC_M2_BASE+0x3070)
#define REG_DDRC_M2_LPD4_BANK_FSM                                           (APB_DDRC_M2_BASE+0x3080)
#define REG_DDRC_M2_LPD4_BANK_STATUS                                        (APB_DDRC_M2_BASE+0x30A0)
#define REG_DDRC_M2_LPD4_PHY_IF                                             (APB_DDRC_M2_BASE+0x30C0)
#define REG_DDRC_M2_LPD4_DFS0_MR_0_CH0                                      (APB_DDRC_M2_BASE+0x3100)
#define REG_DDRC_M2_LPD4_DFS0_MR_1_CH0                                      (APB_DDRC_M2_BASE+0x3104)
#define REG_DDRC_M2_LPD4_DFS0_MR_2_CH0                                      (APB_DDRC_M2_BASE+0x3108)
#define REG_DDRC_M2_LPD4_DFS0_MR_3_CH0                                      (APB_DDRC_M2_BASE+0x310C)
#define REG_DDRC_M2_LPD4_DFS0_MR_4_CH0                                      (APB_DDRC_M2_BASE+0x3110)
#define REG_DDRC_M2_LPD4_DFS0_MR_5_CH0                                      (APB_DDRC_M2_BASE+0x3114)
#define REG_DDRC_M2_LPD4_DFS0_MR_6_CH0                                      (APB_DDRC_M2_BASE+0x3118)
#define REG_DDRC_M2_LPD4_DFS0_MR_0_CH1                                      (APB_DDRC_M2_BASE+0x3120)
#define REG_DDRC_M2_LPD4_DFS0_MR_1_CH1                                      (APB_DDRC_M2_BASE+0x3124)
#define REG_DDRC_M2_LPD4_DFS0_MR_2_CH1                                      (APB_DDRC_M2_BASE+0x3128)
#define REG_DDRC_M2_LPD4_DFS0_MR_3_CH1                                      (APB_DDRC_M2_BASE+0x312C)
#define REG_DDRC_M2_LPD4_DFS0_MR_4_CH1                                      (APB_DDRC_M2_BASE+0x3130)
#define REG_DDRC_M2_LPD4_DFS0_MR_5_CH1                                      (APB_DDRC_M2_BASE+0x3134)
#define REG_DDRC_M2_LPD4_DFS0_MR_6_CH1                                      (APB_DDRC_M2_BASE+0x3138)
#define REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_0                                    (APB_DDRC_M2_BASE+0x3140)
#define REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_1                                    (APB_DDRC_M2_BASE+0x3144)
#define REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_2                                    (APB_DDRC_M2_BASE+0x3148)
#define REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_3                                    (APB_DDRC_M2_BASE+0x314C)
#define REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_4                                    (APB_DDRC_M2_BASE+0x3150)
#define REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_5                                    (APB_DDRC_M2_BASE+0x3154)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_0                                (APB_DDRC_M2_BASE+0x3160)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_1                                (APB_DDRC_M2_BASE+0x3164)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_2                                (APB_DDRC_M2_BASE+0x3168)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_3                                (APB_DDRC_M2_BASE+0x316C)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_4                                (APB_DDRC_M2_BASE+0x3170)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_5                                (APB_DDRC_M2_BASE+0x3174)
#define REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_6                                (APB_DDRC_M2_BASE+0x3178)
#define REG_DDRC_M2_LPD4_DFS0_REF_CTRL                                      (APB_DDRC_M2_BASE+0x3190)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_0                                 (APB_DDRC_M2_BASE+0x31A0)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_1                                 (APB_DDRC_M2_BASE+0x31A4)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_2                                 (APB_DDRC_M2_BASE+0x31A8)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_3                                 (APB_DDRC_M2_BASE+0x31AC)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_4                                 (APB_DDRC_M2_BASE+0x31B0)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_5                                 (APB_DDRC_M2_BASE+0x31B4)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_6                                 (APB_DDRC_M2_BASE+0x31B8)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_7                                 (APB_DDRC_M2_BASE+0x31BC)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_8                                 (APB_DDRC_M2_BASE+0x31C0)
#define REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_9                                 (APB_DDRC_M2_BASE+0x31C4)
#define REG_DDRC_M2_LPD4_DFS0_PHY_IF                                        (APB_DDRC_M2_BASE+0x31E0)
#define REG_DDRC_M2_LPD4_DFS1_MR_0_CH0                                      (APB_DDRC_M2_BASE+0x3200)
#define REG_DDRC_M2_LPD4_DFS1_MR_1_CH0                                      (APB_DDRC_M2_BASE+0x3204)
#define REG_DDRC_M2_LPD4_DFS1_MR_2_CH0                                      (APB_DDRC_M2_BASE+0x3208)
#define REG_DDRC_M2_LPD4_DFS1_MR_3_CH0                                      (APB_DDRC_M2_BASE+0x320C)
#define REG_DDRC_M2_LPD4_DFS1_MR_4_CH0                                      (APB_DDRC_M2_BASE+0x3210)
#define REG_DDRC_M2_LPD4_DFS1_MR_5_CH0                                      (APB_DDRC_M2_BASE+0x3214)
#define REG_DDRC_M2_LPD4_DFS1_MR_6_CH0                                      (APB_DDRC_M2_BASE+0x3218)
#define REG_DDRC_M2_LPD4_DFS1_MR_0_CH1                                      (APB_DDRC_M2_BASE+0x3220)
#define REG_DDRC_M2_LPD4_DFS1_MR_1_CH1                                      (APB_DDRC_M2_BASE+0x3224)
#define REG_DDRC_M2_LPD4_DFS1_MR_2_CH1                                      (APB_DDRC_M2_BASE+0x3228)
#define REG_DDRC_M2_LPD4_DFS1_MR_3_CH1                                      (APB_DDRC_M2_BASE+0x322C)
#define REG_DDRC_M2_LPD4_DFS1_MR_4_CH1                                      (APB_DDRC_M2_BASE+0x3230)
#define REG_DDRC_M2_LPD4_DFS1_MR_5_CH1                                      (APB_DDRC_M2_BASE+0x3234)
#define REG_DDRC_M2_LPD4_DFS1_MR_6_CH1                                      (APB_DDRC_M2_BASE+0x3238)
#define REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_0                                    (APB_DDRC_M2_BASE+0x3240)
#define REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_1                                    (APB_DDRC_M2_BASE+0x3244)
#define REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_2                                    (APB_DDRC_M2_BASE+0x3248)
#define REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_3                                    (APB_DDRC_M2_BASE+0x324C)
#define REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_4                                    (APB_DDRC_M2_BASE+0x3250)
#define REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_5                                    (APB_DDRC_M2_BASE+0x3254)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_0                                (APB_DDRC_M2_BASE+0x3260)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_1                                (APB_DDRC_M2_BASE+0x3264)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_2                                (APB_DDRC_M2_BASE+0x3268)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_3                                (APB_DDRC_M2_BASE+0x326C)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_4                                (APB_DDRC_M2_BASE+0x3270)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_5                                (APB_DDRC_M2_BASE+0x3274)
#define REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_6                                (APB_DDRC_M2_BASE+0x3278)
#define REG_DDRC_M2_LPD4_DFS1_REF_CTRL                                      (APB_DDRC_M2_BASE+0x3290)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_0                                 (APB_DDRC_M2_BASE+0x32A0)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_1                                 (APB_DDRC_M2_BASE+0x32A4)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_2                                 (APB_DDRC_M2_BASE+0x32A8)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_3                                 (APB_DDRC_M2_BASE+0x32AC)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_4                                 (APB_DDRC_M2_BASE+0x32B0)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_5                                 (APB_DDRC_M2_BASE+0x32B4)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_6                                 (APB_DDRC_M2_BASE+0x32B8)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_7                                 (APB_DDRC_M2_BASE+0x32BC)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_8                                 (APB_DDRC_M2_BASE+0x32C0)
#define REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_9                                 (APB_DDRC_M2_BASE+0x32C4)
#define REG_DDRC_M2_LPD4_DFS1_PHY_IF                                        (APB_DDRC_M2_BASE+0x32E0)
#define REG_DDRC_M2_LPD4_DFS2_MR_0_CH0                                      (APB_DDRC_M2_BASE+0x3300)
#define REG_DDRC_M2_LPD4_DFS2_MR_1_CH0                                      (APB_DDRC_M2_BASE+0x3304)
#define REG_DDRC_M2_LPD4_DFS2_MR_2_CH0                                      (APB_DDRC_M2_BASE+0x3308)
#define REG_DDRC_M2_LPD4_DFS2_MR_3_CH0                                      (APB_DDRC_M2_BASE+0x330C)
#define REG_DDRC_M2_LPD4_DFS2_MR_4_CH0                                      (APB_DDRC_M2_BASE+0x3310)
#define REG_DDRC_M2_LPD4_DFS2_MR_5_CH0                                      (APB_DDRC_M2_BASE+0x3314)
#define REG_DDRC_M2_LPD4_DFS2_MR_6_CH0                                      (APB_DDRC_M2_BASE+0x3318)
#define REG_DDRC_M2_LPD4_DFS2_MR_0_CH1                                      (APB_DDRC_M2_BASE+0x3320)
#define REG_DDRC_M2_LPD4_DFS2_MR_1_CH1                                      (APB_DDRC_M2_BASE+0x3324)
#define REG_DDRC_M2_LPD4_DFS2_MR_2_CH1                                      (APB_DDRC_M2_BASE+0x3328)
#define REG_DDRC_M2_LPD4_DFS2_MR_3_CH1                                      (APB_DDRC_M2_BASE+0x332C)
#define REG_DDRC_M2_LPD4_DFS2_MR_4_CH1                                      (APB_DDRC_M2_BASE+0x3330)
#define REG_DDRC_M2_LPD4_DFS2_MR_5_CH1                                      (APB_DDRC_M2_BASE+0x3334)
#define REG_DDRC_M2_LPD4_DFS2_MR_6_CH1                                      (APB_DDRC_M2_BASE+0x3338)
#define REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_0                                    (APB_DDRC_M2_BASE+0x3340)
#define REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_1                                    (APB_DDRC_M2_BASE+0x3344)
#define REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_2                                    (APB_DDRC_M2_BASE+0x3348)
#define REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_3                                    (APB_DDRC_M2_BASE+0x334C)
#define REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_4                                    (APB_DDRC_M2_BASE+0x3350)
#define REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_5                                    (APB_DDRC_M2_BASE+0x3354)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_0                                (APB_DDRC_M2_BASE+0x3360)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_1                                (APB_DDRC_M2_BASE+0x3364)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_2                                (APB_DDRC_M2_BASE+0x3368)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_3                                (APB_DDRC_M2_BASE+0x336C)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_4                                (APB_DDRC_M2_BASE+0x3370)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_5                                (APB_DDRC_M2_BASE+0x3374)
#define REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_6                                (APB_DDRC_M2_BASE+0x3378)
#define REG_DDRC_M2_LPD4_DFS2_REF_CTRL                                      (APB_DDRC_M2_BASE+0x3390)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_0                                 (APB_DDRC_M2_BASE+0x33A0)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_1                                 (APB_DDRC_M2_BASE+0x33A4)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_2                                 (APB_DDRC_M2_BASE+0x33A8)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_3                                 (APB_DDRC_M2_BASE+0x33AC)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_4                                 (APB_DDRC_M2_BASE+0x33B0)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_5                                 (APB_DDRC_M2_BASE+0x33B4)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_6                                 (APB_DDRC_M2_BASE+0x33B8)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_7                                 (APB_DDRC_M2_BASE+0x33BC)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_8                                 (APB_DDRC_M2_BASE+0x33C0)
#define REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_9                                 (APB_DDRC_M2_BASE+0x33C4)
#define REG_DDRC_M2_LPD4_DFS2_PHY_IF                                        (APB_DDRC_M2_BASE+0x33E0)
#define REG_DDRC_M2_DEBUG_COMMON                                            (APB_DDRC_M2_BASE+0x5000)
#define REG_DDRC_M2_DEBUG_PERIOD                                            (APB_DDRC_M2_BASE+0x5004)
#define REG_DDRC_M2_IRQ_MASK                                                (APB_DDRC_M2_BASE+0x5010)
#define REG_DDRC_M2_IRQ_STATUS                                              (APB_DDRC_M2_BASE+0x5014)
#define REG_DDRC_M2_DEBUG_BUS_IF                                            (APB_DDRC_M2_BASE+0x5100)
#define REG_DDRC_M2_DEBUG_PORT_IF_0                                         (APB_DDRC_M2_BASE+0x5200)
#define REG_DDRC_M2_DEBUG_PORT_IF_1                                         (APB_DDRC_M2_BASE+0x5204)
#define REG_DDRC_M2_DEBUG_PORT_IF_2                                         (APB_DDRC_M2_BASE+0x5208)
#define REG_DDRC_M2_DEBUG_PORT_IF_3                                         (APB_DDRC_M2_BASE+0x520C)
#define REG_DDRC_M2_DEBUG_PORT_IF_4                                         (APB_DDRC_M2_BASE+0x5210)
#define REG_DDRC_M2_DEBUG_PORT_IF_5                                         (APB_DDRC_M2_BASE+0x5214)
#define REG_DDRC_M2_DEBUG_PORT_IF_6                                         (APB_DDRC_M2_BASE+0x5218)
#define REG_DDRC_M2_DEBUG_PORT_IF_7                                         (APB_DDRC_M2_BASE+0x521C)
#define REG_DDRC_M2_DEBUG_UQ_1                                              (APB_DDRC_M2_BASE+0x5300)
#define REG_DDRC_M2_DEBUG_UQ_2                                              (APB_DDRC_M2_BASE+0x5304)
#define REG_DDRC_M2_DEBUG_SCH0                                              (APB_DDRC_M2_BASE+0x5400)
#define REG_DDRC_M2_DEBUG_SCH1                                              (APB_DDRC_M2_BASE+0x5404)
#define REG_DDRC_M2_DEBUG_ALP                                               (APB_DDRC_M2_BASE+0x5500)
#define REG_DDRC_M2_DEBUG_ALP_ENTRY_NUM                                     (APB_DDRC_M2_BASE+0x5504)
#define REG_DDRC_M2_DEBUG_ALP_TIME                                          (APB_DDRC_M2_BASE+0x5508)
#define REG_DDRC_M2_DEBUG_ALP_WAIT_CNT                                      (APB_DDRC_M2_BASE+0x550C)
#define REG_DDRC_M2_DEBUG_DFS                                               (APB_DDRC_M2_BASE+0x5600)
#define REG_DDRC_M2_DEBUG_IDLE_CNT                                          (APB_DDRC_M2_BASE+0x5700)
#define REG_DDRC_M2_DEBUG_RD_CNT                                            (APB_DDRC_M2_BASE+0x5704)
#define REG_DDRC_M2_DEBUG_RDL_CNT                                           (APB_DDRC_M2_BASE+0x5708)
#define REG_DDRC_M2_DEBUG_RWR_CNT                                           (APB_DDRC_M2_BASE+0x5710)
#define REG_DDRC_M2_DEBUG_MWR_CNT                                           (APB_DDRC_M2_BASE+0x5714)
#define REG_DDRC_M2_DEBUG_WRL_CNT                                           (APB_DDRC_M2_BASE+0x5718)
#define REG_DDRC_M2_DEBUG_PRG_CNT                                           (APB_DDRC_M2_BASE+0x5720)
#define REG_DDRC_M2_DEBUG_REF_CNT                                           (APB_DDRC_M2_BASE+0x5724)
#define REG_DDRC_M2_DEBUG_ACT_CNT                                           (APB_DDRC_M2_BASE+0x5728)
#define REG_DDRC_M2_DEBUG_RW_SWC_CNT                                        (APB_DDRC_M2_BASE+0x572C)
#define REG_DDRC_M2_DEBUG_R_URG_SWC_CNT                                     (APB_DDRC_M2_BASE+0x5730)
#define REG_DDRC_M2_DEBUG_R_REQ_ROW_HIT_CNT                                 (APB_DDRC_M2_BASE+0x5734)
#define REG_DDRC_M2_DEBUG_R_REQ_HIT_CNT                                     (APB_DDRC_M2_BASE+0x5738)
#define REG_DDRC_M2_DEBUG_R_URG_ROW_HIT_CNT                                 (APB_DDRC_M2_BASE+0x573C)
#define REG_DDRC_M2_DEBUG_R_URG_HIT_CNT                                     (APB_DDRC_M2_BASE+0x5740)
#define REG_DDRC_M2_DEBUG_R_ROW_HIT_CNT                                     (APB_DDRC_M2_BASE+0x5744)
#define REG_DDRC_M2_DEBUG_R_LUCKY_HIT_CNT                                   (APB_DDRC_M2_BASE+0x5748)
#define REG_DDRC_M2_DEBUG_W_URG_SWC_CNT                                     (APB_DDRC_M2_BASE+0x5750)
#define REG_DDRC_M2_DEBUG_W_REQ_ROW_HIT_CNT                                 (APB_DDRC_M2_BASE+0x5754)
#define REG_DDRC_M2_DEBUG_W_REQ_HIT_CNT                                     (APB_DDRC_M2_BASE+0x5758)
#define REG_DDRC_M2_DEBUG_W_URG_ROW_HIT_CNT                                 (APB_DDRC_M2_BASE+0x575C)
#define REG_DDRC_M2_DEBUG_W_URG_HIT_CNT                                     (APB_DDRC_M2_BASE+0x5760)
#define REG_DDRC_M2_DEBUG_W_ROW_HIT_CNT                                     (APB_DDRC_M2_BASE+0x5764)
#define REG_DDRC_M2_DEBUG_W_LUCKY_HIT_CNT                                   (APB_DDRC_M2_BASE+0x5768)
#define REG_DDRC_M2_DEBUG_MAX_LAT_QOS                                       (APB_DDRC_M2_BASE+0x5770)
#define REG_DDRC_M2_DEBUG_R_HYB_SWC_CNT                                     (APB_DDRC_M2_BASE+0x5800)
#define REG_DDRC_M2_DEBUG_W_HYB_SWC_CNT                                     (APB_DDRC_M2_BASE+0x5804)
#define REG_DDRC_M2_DEBUG_R_FIFO_0_PRT_CNT                                  (APB_DDRC_M2_BASE+0x5900)
#define REG_DDRC_M2_DEBUG_R_FIFO_1_PRT_CNT                                  (APB_DDRC_M2_BASE+0x5904)
#define REG_DDRC_M2_DEBUG_R_FIFO_2_PRT_CNT                                  (APB_DDRC_M2_BASE+0x5908)
#define REG_DDRC_M2_DEBUG_R_FIFO_3_PRT_CNT                                  (APB_DDRC_M2_BASE+0x590C)
#define REG_DDRC_M2_DEBUG_W_FIFO_0_PRT_CNT                                  (APB_DDRC_M2_BASE+0x5910)
#define REG_DDRC_M2_DEBUG_W_FIFO_1_PRT_CNT                                  (APB_DDRC_M2_BASE+0x5914)
#define REG_DDRC_M2_DEBUG_W_FIFO_2_PRT_CNT                                  (APB_DDRC_M2_BASE+0x5918)
#define REG_DDRC_M2_DEBUG_W_FIFO_3_PRT_CNT                                  (APB_DDRC_M2_BASE+0x591C)
#define REG_DDRC_M2_DEBUG_LPD4_0                                            (APB_DDRC_M2_BASE+0x6000)
#define REG_DDRC_M2_DEBUG_LPD4_1                                            (APB_DDRC_M2_BASE+0x6004)
#define REG_DDRC_M2_DEBUG_LPD4_2                                            (APB_DDRC_M2_BASE+0x6008)
#define REG_DDRC_M2_DEBUG_LPD4_3                                            (APB_DDRC_M2_BASE+0x600C)
#define REG_DDRC_M2_DEBUG_LPD4_4                                            (APB_DDRC_M2_BASE+0x6010)
#define REG_DDRC_M2_DEBUG_LPD4_5                                            (APB_DDRC_M2_BASE+0x6014)
#define REG_DDRC_M2_DEBUG_LPD4_6                                            (APB_DDRC_M2_BASE+0x6018)
#define REG_DDRC_M2_DEBUG_LPD4_7                                            (APB_DDRC_M2_BASE+0x601C)
#define REG_DDRC_M2_DEBUG_LPD4_8                                            (APB_DDRC_M2_BASE+0x6020)
#define REG_DDRC_M2_DEBUG_LPD4_9                                            (APB_DDRC_M2_BASE+0x6024)
#define REG_DDRC_M2_DEBUG_LPD4_10                                           (APB_DDRC_M2_BASE+0x6028)
#define REG_DDRC_M2_DEBUG_LPD4_11                                           (APB_DDRC_M2_BASE+0x602C)
#define REG_DDRC_M2_DEBUG_LPD4_12                                           (APB_DDRC_M2_BASE+0x6030)
#define REG_DDRC_M2_DEBUG_LPD4_13                                           (APB_DDRC_M2_BASE+0x6034)
#define REG_DDRC_M2_DEBUG_LPD4_14                                           (APB_DDRC_M2_BASE+0x6038)
#define REG_DDRC_M2_DEBUG_LPD4_15                                           (APB_DDRC_M2_BASE+0x603C)
#define REG_DDRC_M2_DEBUG_LPD4_16                                           (APB_DDRC_M2_BASE+0x6040)
#define REG_DDRC_M2_DEBUG_LPD4_MR_0                                         (APB_DDRC_M2_BASE+0x6100)
#define REG_DDRC_M2_DEBUG_LPD4_MR_1                                         (APB_DDRC_M2_BASE+0x6104)
#define REG_DDRC_M2_DEBUG_LPD4_MR_2                                         (APB_DDRC_M2_BASE+0x6108)
#define REG_DDRC_M2_DEBUG_LPD4_MR_3                                         (APB_DDRC_M2_BASE+0x610C)
#define REG_DDRC_M2_DEBUG_LPD4_MR_4                                         (APB_DDRC_M2_BASE+0x6110)
#define REG_DDRC_M2_DEBUG_LPD4_MR_5                                         (APB_DDRC_M2_BASE+0x6114)
#define REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_0                                   (APB_DDRC_M2_BASE+0x6118)
#define REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_1                                   (APB_DDRC_M2_BASE+0x611C)
#define REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_2                                   (APB_DDRC_M2_BASE+0x6120)
#define REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_3                                   (APB_DDRC_M2_BASE+0x6124)
#define REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_4                                   (APB_DDRC_M2_BASE+0x6128)
#define REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_5                                   (APB_DDRC_M2_BASE+0x612C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MRW1                                     (APB_DDRC_M2_BASE+0x6200)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MRW0                                     (APB_DDRC_M2_BASE+0x6204)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_LP_EXIT                                  (APB_DDRC_M2_BASE+0x6208)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_LP_ENTRY                                 (APB_DDRC_M2_BASE+0x620C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_SR_PD_EXIT                               (APB_DDRC_M2_BASE+0x6210)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_SR_PD_ENTRY                              (APB_DDRC_M2_BASE+0x6214)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_SR_EXIT                                  (APB_DDRC_M2_BASE+0x6218)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_SR_ENTRY                                 (APB_DDRC_M2_BASE+0x621C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PD_EXIT                                  (APB_DDRC_M2_BASE+0x6220)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PD_ENTRY                                 (APB_DDRC_M2_BASE+0x6224)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ZQLAT                                    (APB_DDRC_M2_BASE+0x6228)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ZQCAL                                    (APB_DDRC_M2_BASE+0x622C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_CKE1                                     (APB_DDRC_M2_BASE+0x6230)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_CKE0                                     (APB_DDRC_M2_BASE+0x6234)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RSTN1                                    (APB_DDRC_M2_BASE+0x6238)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RSTN0                                    (APB_DDRC_M2_BASE+0x623C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD0                                      (APB_DDRC_M2_BASE+0x6240)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD1                                      (APB_DDRC_M2_BASE+0x6244)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD2                                      (APB_DDRC_M2_BASE+0x6248)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD3                                      (APB_DDRC_M2_BASE+0x624C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD4                                      (APB_DDRC_M2_BASE+0x6250)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD5                                      (APB_DDRC_M2_BASE+0x6254)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD6                                      (APB_DDRC_M2_BASE+0x6258)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_RD7                                      (APB_DDRC_M2_BASE+0x625C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR0                                     (APB_DDRC_M2_BASE+0x6260)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR1                                     (APB_DDRC_M2_BASE+0x6264)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR2                                     (APB_DDRC_M2_BASE+0x6268)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR3                                     (APB_DDRC_M2_BASE+0x626C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR4                                     (APB_DDRC_M2_BASE+0x6270)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR5                                     (APB_DDRC_M2_BASE+0x6274)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR6                                     (APB_DDRC_M2_BASE+0x6278)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MWR7                                     (APB_DDRC_M2_BASE+0x627C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR0                                      (APB_DDRC_M2_BASE+0x6280)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR1                                      (APB_DDRC_M2_BASE+0x6284)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR2                                      (APB_DDRC_M2_BASE+0x6288)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR3                                      (APB_DDRC_M2_BASE+0x628C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR4                                      (APB_DDRC_M2_BASE+0x6290)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR5                                      (APB_DDRC_M2_BASE+0x6294)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR6                                      (APB_DDRC_M2_BASE+0x6298)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_WR7                                      (APB_DDRC_M2_BASE+0x629C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT0                                     (APB_DDRC_M2_BASE+0x62A0)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT1                                     (APB_DDRC_M2_BASE+0x62A4)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT2                                     (APB_DDRC_M2_BASE+0x62A8)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT3                                     (APB_DDRC_M2_BASE+0x62AC)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT4                                     (APB_DDRC_M2_BASE+0x62B0)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT5                                     (APB_DDRC_M2_BASE+0x62B4)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT6                                     (APB_DDRC_M2_BASE+0x62B8)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_ACT7                                     (APB_DDRC_M2_BASE+0x62BC)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB0                                  (APB_DDRC_M2_BASE+0x6300)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB1                                  (APB_DDRC_M2_BASE+0x6304)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB2                                  (APB_DDRC_M2_BASE+0x6308)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB3                                  (APB_DDRC_M2_BASE+0x630C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB4                                  (APB_DDRC_M2_BASE+0x6310)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB5                                  (APB_DDRC_M2_BASE+0x6314)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB6                                  (APB_DDRC_M2_BASE+0x6318)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB7                                  (APB_DDRC_M2_BASE+0x631C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB0                                  (APB_DDRC_M2_BASE+0x6320)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB1                                  (APB_DDRC_M2_BASE+0x6324)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB2                                  (APB_DDRC_M2_BASE+0x6328)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB3                                  (APB_DDRC_M2_BASE+0x632C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB4                                  (APB_DDRC_M2_BASE+0x6330)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB5                                  (APB_DDRC_M2_BASE+0x6334)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB6                                  (APB_DDRC_M2_BASE+0x6338)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB7                                  (APB_DDRC_M2_BASE+0x633C)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_CG_REF_AB                                (APB_DDRC_M2_BASE+0x6340)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MF_REF_AB                                (APB_DDRC_M2_BASE+0x6344)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_CG_PRG_AB                                (APB_DDRC_M2_BASE+0x6350)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_MF_PRG_AB                                (APB_DDRC_M2_BASE+0x6354)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_CG_BL                                    (APB_DDRC_M2_BASE+0x6360)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_CG_AP                                    (APB_DDRC_M2_BASE+0x6364)
#define REG_DDRC_M2_DEBUG_CTRL_CMD_REF_CYCLE                                (APB_DDRC_M2_BASE+0x6368)
#define REG_DDRC_M2_DEBUG_DFI                                               (APB_DDRC_M2_BASE+0x6700)
#define REG_DDRC_M2_DRAM_BIST_CTRL_0                                        (APB_DDRC_M2_BASE+0x6800)
#define REG_DDRC_M2_DRAM_BIST_CTRL_1                                        (APB_DDRC_M2_BASE+0x6804)
#define REG_DDRC_M2_DRAM_BIST_CTRL_2                                        (APB_DDRC_M2_BASE+0x6808)
#define REG_DDRC_M2_DRAM_BIST_DATA_0                                        (APB_DDRC_M2_BASE+0x680C)
#define REG_DDRC_M2_DRAM_BIST_DATA_1                                        (APB_DDRC_M2_BASE+0x6810)
#define REG_DDRC_M2_DRAM_BIST_DATA_2                                        (APB_DDRC_M2_BASE+0x6814)
#define REG_DDRC_M2_DRAM_BIST_ADDR_0                                        (APB_DDRC_M2_BASE+0x6818)
#define REG_DDRC_M2_DRAM_BIST_ADDR_1                                        (APB_DDRC_M2_BASE+0x681C)
#define REG_DDRC_M2_DRAM_BIST_ADDR_2                                        (APB_DDRC_M2_BASE+0x6820)
#define REG_DDRC_M2_DRAM_BIST_OPCMD_0                                       (APB_DDRC_M2_BASE+0x6824)
#define REG_DDRC_M2_DRAM_BIST_OPCMD_1                                       (APB_DDRC_M2_BASE+0x6828)
#define REG_DDRC_M2_DRAM_BIST_OPCMD_2                                       (APB_DDRC_M2_BASE+0x682C)
#define REG_DDRC_M2_DRAM_BIST_OPCMD_3                                       (APB_DDRC_M2_BASE+0x6830)
#define REG_DDRC_M2_DRAM_BIST_ERR_ADDR_INFO                                 (APB_DDRC_M2_BASE+0x6834)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_00                              (APB_DDRC_M2_BASE+0x6838)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_01                              (APB_DDRC_M2_BASE+0x683C)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_02                              (APB_DDRC_M2_BASE+0x6840)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_03                              (APB_DDRC_M2_BASE+0x6844)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_04                              (APB_DDRC_M2_BASE+0x6848)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_05                              (APB_DDRC_M2_BASE+0x684C)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_06                              (APB_DDRC_M2_BASE+0x6850)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_07                              (APB_DDRC_M2_BASE+0x6854)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_08                              (APB_DDRC_M2_BASE+0x6858)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_09                              (APB_DDRC_M2_BASE+0x685C)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_10                              (APB_DDRC_M2_BASE+0x6860)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_11                              (APB_DDRC_M2_BASE+0x6864)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_12                              (APB_DDRC_M2_BASE+0x6868)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_13                              (APB_DDRC_M2_BASE+0x686C)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_14                              (APB_DDRC_M2_BASE+0x6870)
#define REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_15                              (APB_DDRC_M2_BASE+0x6874)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_00                              (APB_DDRC_M2_BASE+0x6878)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_01                              (APB_DDRC_M2_BASE+0x687C)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_02                              (APB_DDRC_M2_BASE+0x6880)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_03                              (APB_DDRC_M2_BASE+0x6884)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_04                              (APB_DDRC_M2_BASE+0x6888)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_05                              (APB_DDRC_M2_BASE+0x688C)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_06                              (APB_DDRC_M2_BASE+0x6890)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_07                              (APB_DDRC_M2_BASE+0x6894)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_08                              (APB_DDRC_M2_BASE+0x6898)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_09                              (APB_DDRC_M2_BASE+0x689C)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_10                              (APB_DDRC_M2_BASE+0x68A0)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_11                              (APB_DDRC_M2_BASE+0x68A4)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_12                              (APB_DDRC_M2_BASE+0x68A8)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_13                              (APB_DDRC_M2_BASE+0x68AC)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_14                              (APB_DDRC_M2_BASE+0x68B0)
#define REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_15                              (APB_DDRC_M2_BASE+0x68B4)
#define REG_DDRC_M2_REY_SPARE                                               (APB_DDRC_M2_BASE+0x6FE0)

typedef union {
	UINT32 udata32;
	struct {						//0xC4500000 RW
	UINT32 reg_dram_ch                      :1;	//0 //Dram channel width (0: x16, 1: x32)
	UINT32 resvd0                           :3;  
	UINT32 reg_byte_mode                    :1;	//4 //Byte mode enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M2_DRAM_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500004 RW
	UINT32 reg_op_mode                      :1;	//0 //operation mode selection (0: normal, 1: debug)
	UINT32 reg_bist_en                      :1;	//1 //bist mode enable
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M2_MODE_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500008 RW
	UINT32 reg_base_period                  :10;	//9:0	//base period for counter (counter resolution) - ex: 1us
	UINT32 resvd                            :22; 
	};
}REG_DDRC_M2_BASE_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500100 RW
	UINT32 reg_alp_en                       :2;	//1:0	//low power mode enable 	 ([0]: power down, [1]: self refresh)
	UINT32 resvd0                           :2;  
	UINT32 reg_pd_thr                       :4;	//7:4	//power down threshold - waiting for 4*(x+1) cycles
	UINT32 reg_sr_thr                       :4;	//11:8	//self refresh threshold - waiting for tREFI*(x+1) cycles
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M2_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500104 RW
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
}REG_DDRC_M2_CGL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500108 RO
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
}REG_DDRC_M2_CGL_MON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500200 RW
	UINT32 reg_pm_en                        :1;	//0 //performance monitor enable
	UINT32 resvd0                           :3;  
	UINT32 reg_emg_period                   :10;	//13:4	//emergency dfs monitoring period (ex: 100us) - (reg_base_period+1 (ex:1us)) * (reg_emg_period+1) : (final default value 0x63 --> 100ms)
	UINT32 resvd1                           :18; 
	};
}REG_DDRC_M2_PERFMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500204 RO
	UINT32 reg_emg_max                      :12;	//11:0	//max value among dfs_emg_totals during debug monitoring period : emg_total >> cut_width	(max of served bytes during emg period in debug monitoring period can be calculated by reg_emg_max * 16 << cut_width)	- cut_width : reg_emg_period[9]? 10 : 	                  reg_emg_period[8]?  9 :	                   reg_emg_period[7]?  8 :   	                   reg_emg_period[6]?  7 :	                   reg_emg_period[5]?  6 :	                   reg_emg_period[4]?  5 :   	                   reg_emg_period[3]?  4 :	                   reg_emg_period[2]?  3 :	                   reg_emg_period[1]?  2 :   	                      reg_emg_period[0]?  1 : 0
	UINT32 resvd                            :20; 
	};
}REG_DDRC_M2_PERFMON_EMG_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500210 RO
	UINT32 reg_pm_w0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_W0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500214 RO
	UINT32 reg_pm_w1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_W1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500218 RO
	UINT32 reg_pm_w2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_W2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450021C RO
	UINT32 reg_pm_w3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_W3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500220 RO
	UINT32 reg_pm_r0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_R0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500224 RO
	UINT32 reg_pm_r1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_R1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500228 RO
	UINT32 reg_pm_r2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_R2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450022C RO
	UINT32 reg_pm_r3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M2_PERFMON_R3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500230 
	UINT32 reg_max_lat_en                   :1;	//0 //max latency monitor enable
	UINT32 resvd0                           :7;  
	UINT32 reg_max_lat                      :8;	//15:8	//max latency for read request in unified Q (it is reset at every period)
	UINT32 resvd1                           :16; 
	};
}REG_DDRC_M2_LATMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500300 RW
	UINT32 reg_dfs_en                       :1;	//0 //normal dfs enable
	UINT32 reg_dfs_emg_en                   :1;	//1 //emergency dfs enable
	UINT32 reg_dfs_mask_en                  :1;	//2 //dfs mask enable by external blocking	- dfs is masked when asserting external blocking signal
	UINT32 reg_dfs_do                       :1;	//3 //user driven dfs start
	UINT32 resvd0                           :4;  
	UINT32 reg_dfs_block_period             :8;	//15:8	//dfs blocking period after completing dfs done : (reg_dfs_block_period+1)*0x100
	UINT32 reg_dfs_emg_thr                  :12;	//27:16	//emergency dfs threshold : it can be determined like as ((reg_base_period+1)*(reg_emg_period+1))*12.8G/(1s*16*2^cut_width))*80%)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500304 RO
	UINT32 reg_dfs_done                     :1;	//0 //dfs done
	UINT32 resvd0                           :3;  
	UINT32 reg_dfs_type                     :2;	//5:4	//dfs type: DFS0, DFS1, DFS2 (emergency DFS exit)
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M2_DFS_RESULT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500400 RW
	UINT32 reg_dram_density                 :3;	//2:0	//dram density configuration per channel 	(enum {2Gb, 3Gb, 4Gb, 6Gb, 8Gb, 12Gb, 16Gb})
	UINT32 reg_addr_scrb_en                 :1;	//3 //address map: bank scramble enable
	UINT32 reg_addr_sel_bq                  :4;	//7:4	//address map: bank position	(enum {BG4, BG5, BG6, BG7, BP4, BP5, BP6, BP7, BP8, BP9, BP11, BP12})
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_ADDR_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500404 RW
	UINT32 reg_fast_en                      :1;	//0 //fast b valid enable
	UINT32 reg_ooo_en                       :1;	//1 //out of order enable
	UINT32 reg_lpd4_32bl_en                 :1;	//2 //lpddr4 long burst support
	UINT32 reg_exmon_en                     :1;	//3 //exclusive monitor enable
	UINT32 reg_errchk_en                    :1;	//4 //errore checker enable	 - 0: error checker disable	   - for out of range address, row address bits are truncated according to dram_density	     - 6Gb, 8Gb : row[16] = 1'b0	     - 3Gb, 4Gb : row[16:15] = 2'h0	     - 2Gb : row[16:14] = 3'h0	 - 1: error checker enable
	UINT32 reg_illegal_strb_mask_dis        :1;	//5 //illegal strb mask disable	      - '0 : mask illegal strb bits	      - '1 : disable illegal strb checker
	UINT32 resvd                            :26; 
	};
}REG_DDRC_M2_COMMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500408 
	UINT32 reg_rc4_enb                      :1;	//0 //data encryption enable
	UINT32 resvd0                           :7;  
	UINT32 reg_rc4_key_in_4                 :8;	//15:8	//key seed for data encryption (39:32 bits)
	UINT32 reg_rc4_state                    :2;	//17:16	//rc4 key generation status
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M2_DATA_ENC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450040C RW
	UINT32 reg_rc4_key_in_3_0               :32;	//31:0	//key seed for data encryption (31:0 bits)
	};
}REG_DDRC_M2_DATA_ENC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500500 RW
	UINT32 reg_sameid_urg_en                :1;	//0 //urgent arbitration enable for predecssor wth same id	 - if it is enabled, whenever sameid request served at cbuf, prt_tag of previous request with same id is incremented
	UINT32 reg_sameid_urg_wt                :3;	//3:1	//weight value to increase prt_tag when same id urgent occurs
	UINT32 reg_prt_en                       :3;	//6:4	//per-request timeout enable ([0]: cbuf, [1]: pq, [2]: bq)
	UINT32 resvd0                           :1;  
	UINT32 reg_prt_bq_thr                   :4;	//11:8	//threshold value of per-request timeout for bank Q
	UINT32 reg_prt_pq_thr                   :4;	//15:12	//threshold value of per-request timeout for port Q
	UINT32 reg_ep_period                    :10;	//25:16	//a period of epoch counter for per-request timeout
	UINT32 resvd1                           :6;  
	};
}REG_DDRC_M2_RD_URG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4500504 RW
	UINT32 reg_urg_en                       :1;	//0 //urgent enable for port Q and bank Q in write port	 - if a request is blocking others due to RAW or WAW, it becomes urgent one.
	UINT32 resvd0                           :3;  
	UINT32 reg_wr_prt_en                    :1;	//4 //per-request timeout enable for port Q and bank Q in write port	 - if a request is timed-out, it becomes urgent one
	UINT32 resvd1                           :3;  
	UINT32 reg_wr_prt_thr                   :4;	//11:8	//threshold value of per-request timeout for write port
	UINT32 resvd2                           :4;  
	UINT32 reg_wr_ep_period                 :10;	//25:16	//a period of epoch counter for per-request timeout
	UINT32 resvd3                           :6;  
	};
}REG_DDRC_M2_WR_URG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501000 RW
	UINT32 reg_awready_en                   :4;	//3:0	//enable awready for each port
	UINT32 reg_pre_wready_en                :1;	//4 //enable pre-wready
	UINT32 resvd0                           :3;  
	UINT32 reg_arready_en                   :4;	//11:8	//enable arready for each port
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M2_FIFO_RDY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501004 RO
	UINT32 reg_aw_all_empty                 :4;	//3:0	//monitor whether all aw valid entries is empty for each port
	UINT32 reg_ar_all_empty                 :4;	//7:4	//monitor whether all aw valid entries is empty for each port
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_FIFO_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501008 RW
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
}REG_DDRC_M2_FIFO_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501010 RW
	UINT32 reg_w_c_lim_en                   :4;	//3:0	//enable cmd cnt limiter
	UINT32 reg_w_d_lim_en                   :4;	//7:4	//enable data len limiter
	UINT32 reg_r_c_lim_en                   :4;	//11:8	//enable cmd cnt limiter
	UINT32 reg_r_d_lim_en                   :4;	//15:12	//enable data len limiter
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LIMITER_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501014 RW
	UINT32 reg_w_c_lim_thr0                 :5;	//4:0	//threshold value for cmd cnt limiter for write port 0
	UINT32 resvd0                           :3;  
	UINT32 reg_w_c_lim_thr1                 :5;	//12:8	//threshold value for cmd cnt limiter for write port 1
	UINT32 resvd1                           :3;  
	UINT32 reg_w_c_lim_thr2                 :5;	//20:16	//threshold value for cmd cnt limiter for write port 2
	UINT32 resvd2                           :3;  
	UINT32 reg_w_c_lim_thr3                 :5;	//28:24	//threshold value for cmd cnt limiter for write port 3
	UINT32 resvd3                           :3;  
	};
}REG_DDRC_M2_LIMITER_AW_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501018 RW
	UINT32 reg_w_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_w_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_w_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_w_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M2_LIMITER_W_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501024 RW
	UINT32 reg_r_c_lim_thr0                 :5;	//4:0	//threshold value for cmd cnt limiter for write port 0
	UINT32 resvd0                           :3;  
	UINT32 reg_r_c_lim_thr1                 :5;	//12:8	//threshold value for cmd cnt limiter for write port 1
	UINT32 resvd1                           :3;  
	UINT32 reg_r_c_lim_thr2                 :5;	//20:16	//threshold value for cmd cnt limiter for write port 2
	UINT32 resvd2                           :3;  
	UINT32 reg_r_c_lim_thr3                 :5;	//28:24	//threshold value for cmd cnt limiter for write port 3
	UINT32 resvd3                           :3;  
	};
}REG_DDRC_M2_LIMITER_AR_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501028 RW
	UINT32 reg_r_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_r_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_r_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_r_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M2_LIMITER_R_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501100 RW
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
}REG_DDRC_M2_FIFO_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501104 RW
	UINT32 reg_wfo_sol_max0                 :4;	//3:0	//The number of additionally continuous max serving requests for a write fifo 0
	UINT32 reg_wfo_sol_max1                 :4;	//7:4	//The number of additionally continuous max serving requests for a write fifo 1
	UINT32 reg_wfo_sol_max2                 :4;	//11:8	//The number of additionally continuous max serving requests for a write fifo 2
	UINT32 reg_wfo_sol_max3                 :4;	//15:12	//The number of additionally continuous max serving requests for a write fifo 3
	UINT32 reg_rfo_sol_max0                 :4;	//19:16	//The number of additionally continuous max serving requests for a read fifo 1
	UINT32 reg_rfo_sol_max1                 :4;	//23:20	//The number of additionally continuous max serving requests for a read fifo 1
	UINT32 reg_rfo_sol_max2                 :4;	//27:24	//The number of additionally continuous max serving requests for a read fifo 2
	UINT32 reg_rfo_sol_max3                 :4;	//31:28	//The number of additionally continuous max serving requests for a read fifo 3
	};
}REG_DDRC_M2_FIFO_MUX_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501108 RW
	UINT32 reg_wfo_prt_sol_max_en           :1;	//0 //write fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_wfo_prt_sol_max_thr          :4;	//7:4	//write fifo prt sol max threshold
	UINT32 reg_wfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for wfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M2_FIFO_MUX_WR_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450110C RW
	UINT32 reg_rfo_prt_sol_max_en           :1;	//0 //read fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_rfo_prt_sol_max_thr          :4;	//7:4	//read fifo prt sol max threshold
	UINT32 reg_rfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for rfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M2_FIFO_MUX_RD_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4501110 RW
	UINT32 reg_wfo_prt_sol_max0             :4;	//3:0	//The number of additionally continuous max serving requests for a write fifo 0 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max1             :4;	//7:4	//The number of additionally continuous max serving requests for a write fifo 1 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max2             :4;	//11:8	//The number of additionally continuous max serving requests for a write fifo 2 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max3             :4;	//15:12	//The number of additionally continuous max serving requests for a write fifo 3 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max0             :4;	//19:16	//The number of additionally continuous max serving requests for a read fifo 1 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max1             :4;	//23:20	//The number of additionally continuous max serving requests for a read fifo 1 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max2             :4;	//27:24	//The number of additionally continuous max serving requests for a read fifo 2 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max3             :4;	//31:28	//The number of additionally continuous max serving requests for a read fifo 3 in the case prt occurred
	};
}REG_DDRC_M2_FIFO_MUX_PRT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4502000 RW
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
}REG_DDRC_M2_PQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4502004 RW
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
}REG_DDRC_M2_BQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4502008 RW
	UINT32 reg_bq_rd_urg_stv_thr            :6;	//5:0	//ead starvation threshold when per request timeout hit is asserted  : 32*(x+1)
	UINT32 resvd0                           :2;  
	UINT32 reg_bq_wr_urg_stv_thr            :6;	//13:8	//write starvation threshold when urg hit is asserted : 32*(x+1)
	UINT32 resvd1                           :2;  
	UINT32 reg_bq_wr_stv_thr                :8;	//23:16	//write starvation threshold : 32*(x+1)
	UINT32 reg_bq_rd_stv_thr                :8;	//31:24	//read starvation threshold : 32*(x+1)
	};
}REG_DDRC_M2_BQ_RW_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450200C RW
	UINT32 reg_bq_hyb_stv_en                :1;	//0 //hybrid starvation enable
	UINT32 resvd0                           :3;  
	UINT32 reg_bq_hyb_stv_thr               :8;	//11:4	//hybrid starvation threshold : 32*(x+1)
	UINT32 resvd1                           :4;  
	UINT32 reg_bq_hyb_stv_cbuf_thr          :5;	//20:16	//cbuf threshold for hybrid starvation operation
	UINT32 resvd2                           :3;  
	UINT32 reg_bq_hyb_stv_dbuf_thr          :8;	//31:24	//dbuf threshold for hybrid starvation operation
	};
}REG_DDRC_M2_BQ_HYB_STV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503000 RW
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
}REG_DDRC_M2_LPD4_MAIN_FSM_INIT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503004 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp0        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP0 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_INIT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503008 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp1        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP1 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_INIT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450300C RW
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
}REG_DDRC_M2_LPD4_MAIN_FSM_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503010 
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
}REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503014 RW
	UINT32 lpd4_reg_dir_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503018 RW
	UINT32 lpd4_reg_dir_mrr_ma              :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450301C RW
	UINT32 lpd4_reg_dir_sr_mrw_ma           :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503020 RW
	UINT32 lpd4_reg_dir_sr_mrr_ma           :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503024 RW
	UINT32 lpd4_reg_dfs_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for DFS	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_DFS_MRW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503028 
	UINT32 lpd4_reg_dfi_ctrlupd_req         :1;	//0 //DFI control update request (This will be cleared when lpd4_mf_reg_dfi_ctrlupd_ack is asserted high)
	UINT32 lpd4_mf_reg_dfi_ctrlupd_ack      :1;	//1 //Completion of DFI control update request
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_CTRLUPD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450302C RW
	UINT32 lpd4_reg_mpc_fifo_en             :1;	//0 //Periodic MPC WR/RD FIFO command enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_mpc_fifo_cmd_cnt        :3;	//6:4	//Number of MPC FIFO commands issued at one time
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503030 RW
	UINT32 lpd4_reg_mpc_fifo_period         :32;	//31:0	//Period of MPC WR/RD FIFO command
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503034 RW
	UINT32 lpd4_reg_mpc_fifo_data0          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503038 RW
	UINT32 lpd4_reg_mpc_fifo_data1          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450303C RW
	UINT32 lpd4_reg_mpc_fifo_dmi0           :4;	//3:0	//DMI data pattern of MPC WR FIFO Command
	UINT32 lpd4_reg_mpc_fifo_dmi1           :4;	//7:4	//DMI data pattern of MPC WR FIFO Command
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503050 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_sel         :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-channel (x32)	- 2'b00 : CH0 or CH1	- 2'b01 : CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_sel        :2;	//5:4	//Refresh rate in MR4 selection between two-channel (x32)	- 2'b00 : Bigger value between CH0 and CH1	- 2'b01 : Smaller value between CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M2_LPD4_MR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503054 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_byte_sel    :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Byte0 or Byte1	- 2'b01 : Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_byte_sel   :2;	//5:4	//Refresh rate in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Bigger value between Byte0 and Byte1	- 2'b01 : Smaller value between Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M2_LPD4_MR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503058 RW
	UINT32 lpd4_reg_mrr_byte_sel            :1;	//0 //MR selection between two-byte (x16) in byte-mode	- 1'b0 : Byte0	- 1'b1 : Byte1
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_LPD4_MR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503060 RW
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
}REG_DDRC_M2_LPD4_REF_REQ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503070 RW
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
}REG_DDRC_M2_LPD4_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503080 RW
	UINT32 lpd4_reg_bank_lock_wait          :8;	//7:0	//Configurable locking time for BANK FSM operation
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_LPD4_BANK_FSM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45030A0 RW
	UINT32 lpd4_reg_tBL                     :8;	//7:0	//Additional offset of AC timing parameters when applying BL32
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_LPD4_BANK_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45030C0 RW
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
}REG_DDRC_M2_LPD4_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503100 RW
	UINT32 lpd4_reg_mr1_ch0_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS0_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503104 RW
	UINT32 lpd4_reg_mr9_ch0_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503108 RW
	UINT32 lpd4_reg_mr12_ch0_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS0_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450310C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503110 RW
	UINT32 lpd4_reg_mr15_ch0_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS0_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503114 RW
	UINT32 lpd4_reg_mr21_ch0_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS0_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503118 RW
	UINT32 lpd4_reg_mr31_ch0_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS0_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503120 RW
	UINT32 lpd4_reg_mr1_ch1_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS0_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503124 RW
	UINT32 lpd4_reg_mr9_ch1_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503128 RW
	UINT32 lpd4_reg_mr12_ch1_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS0_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450312C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503130 RW
	UINT32 lpd4_reg_mr15_ch1_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS0_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503134 RW
	UINT32 lpd4_reg_mr21_ch1_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS0_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503138 RW
	UINT32 lpd4_reg_mr31_ch1_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS0_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503140 RW
	UINT32 lpd4_reg_period_zq_req_dfs0      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503144 RW
	UINT32 lpd4_reg_tINIT1_dfs0             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs0             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503148 RW
	UINT32 lpd4_reg_tINIT5_dfs0             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs0             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs0             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450314C RW
	UINT32 lpd4_reg_tXP_dfs0                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs0             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs0            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs0            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503150 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs0           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503154 RW
	UINT32 lpd4_reg_tXSR_dfs0               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs0         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503160 RW
	UINT32 lpd4_reg_tREFI_dfs0              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs0           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503164 RW
	UINT32 lpd4_reg_tMRR4I_dfs0             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503168 RW
	UINT32 lpd4_reg_tRRD_dfs0               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs0           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs0           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs0               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450316C RW
	UINT32 lpd4_reg_tRAS_dfs0               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs0              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs0              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs0               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503170 RW
	UINT32 lpd4_reg_tRAP_dfs0               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs0        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs0    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs0    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503174 RW
	UINT32 lpd4_reg_tRCD_derate_dfs0        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs0        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs0       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs0       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503178 RW
	UINT32 lpd4_reg_tWAP_derate_dfs0        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs0        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503190 RW
	UINT32 lpd4_reg_ref_ab_en_dfs0          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs0          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M2_LPD4_DFS0_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031A0 RW
	UINT32 lpd4_reg_odt_on_dfs0             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031A4 RW
	UINT32 lpd4_reg_tCCD_dfs0               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs0             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs0               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs0               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031A8 RW
	UINT32 lpd4_reg_tW2PD_dfs0              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs0             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs0           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs0         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs0        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs0               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs0              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs0             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs0           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs0               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031B4 RW
	UINT32 lpd4_reg_tRFCab_dfs0             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs0             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031B8 RW
	UINT32 lpd4_reg_tMRW_dfs0               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs0           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs0       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs0      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031BC RW
	UINT32 lpd4_reg_tFC_dfs0                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs0           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs0               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs0              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs0            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs0             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs0             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs0           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45031E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs0             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs0            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs0             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS0_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503200 RW
	UINT32 lpd4_reg_mr1_ch0_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS1_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503204 RW
	UINT32 lpd4_reg_mr9_ch0_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503208 RW
	UINT32 lpd4_reg_mr12_ch0_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS1_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450320C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503210 RW
	UINT32 lpd4_reg_mr15_ch0_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS1_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503214 RW
	UINT32 lpd4_reg_mr21_ch0_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS1_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503218 RW
	UINT32 lpd4_reg_mr31_ch0_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS1_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503220 RW
	UINT32 lpd4_reg_mr1_ch1_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS1_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503224 RW
	UINT32 lpd4_reg_mr9_ch1_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503228 RW
	UINT32 lpd4_reg_mr12_ch1_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS1_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450322C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503230 RW
	UINT32 lpd4_reg_mr15_ch1_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS1_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503234 RW
	UINT32 lpd4_reg_mr21_ch1_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS1_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503238 RW
	UINT32 lpd4_reg_mr31_ch1_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS1_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503240 RW
	UINT32 lpd4_reg_period_zq_req_dfs1      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503244 RW
	UINT32 lpd4_reg_tINIT1_dfs1             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs1             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503248 RW
	UINT32 lpd4_reg_tINIT5_dfs1             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs1             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs1             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450324C RW
	UINT32 lpd4_reg_tXP_dfs1                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs1             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs1            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs1            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503250 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs1           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503254 RW
	UINT32 lpd4_reg_tXSR_dfs1               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs1         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503260 RW
	UINT32 lpd4_reg_tREFI_dfs1              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs1           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503264 RW
	UINT32 lpd4_reg_tMRR4I_dfs1             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503268 RW
	UINT32 lpd4_reg_tRRD_dfs1               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs1           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs1           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs1               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450326C RW
	UINT32 lpd4_reg_tRAS_dfs1               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs1              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs1              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs1               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503270 RW
	UINT32 lpd4_reg_tRAP_dfs1               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs1        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs1    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs1    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503274 RW
	UINT32 lpd4_reg_tRCD_derate_dfs1        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs1        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs1       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs1       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503278 RW
	UINT32 lpd4_reg_tWAP_derate_dfs1        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs1        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503290 RW
	UINT32 lpd4_reg_ref_ab_en_dfs1          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs1          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M2_LPD4_DFS1_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032A0 RW
	UINT32 lpd4_reg_odt_on_dfs1             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032A4 RW
	UINT32 lpd4_reg_tCCD_dfs1               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs1             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs1               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs1               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032A8 RW
	UINT32 lpd4_reg_tW2PD_dfs1              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs1             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs1           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs1         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs1        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs1               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs1              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs1             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs1           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs1               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032B4 RW
	UINT32 lpd4_reg_tRFCab_dfs1             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs1             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032B8 RW
	UINT32 lpd4_reg_tMRW_dfs1               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs1           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs1       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs1      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032BC RW
	UINT32 lpd4_reg_tFC_dfs1                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs1           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs1               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs1              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs1            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs1             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs1             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs1           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45032E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs1             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs1            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs1             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS1_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503300 RW
	UINT32 lpd4_reg_mr1_ch0_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS2_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503304 RW
	UINT32 lpd4_reg_mr9_ch0_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503308 RW
	UINT32 lpd4_reg_mr12_ch0_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS2_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450330C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503310 RW
	UINT32 lpd4_reg_mr15_ch0_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS2_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503314 RW
	UINT32 lpd4_reg_mr21_ch0_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS2_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503318 RW
	UINT32 lpd4_reg_mr31_ch0_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M2_LPD4_DFS2_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503320 RW
	UINT32 lpd4_reg_mr1_ch1_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS2_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503324 RW
	UINT32 lpd4_reg_mr9_ch1_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503328 RW
	UINT32 lpd4_reg_mr12_ch1_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS2_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450332C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503330 RW
	UINT32 lpd4_reg_mr15_ch1_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS2_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503334 RW
	UINT32 lpd4_reg_mr21_ch1_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS2_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503338 RW
	UINT32 lpd4_reg_mr31_ch1_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M2_LPD4_DFS2_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503340 RW
	UINT32 lpd4_reg_period_zq_req_dfs2      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503344 RW
	UINT32 lpd4_reg_tINIT1_dfs2             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs2             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503348 RW
	UINT32 lpd4_reg_tINIT5_dfs2             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs2             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs2             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450334C RW
	UINT32 lpd4_reg_tXP_dfs2                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs2             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs2            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs2            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503350 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs2           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503354 RW
	UINT32 lpd4_reg_tXSR_dfs2               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs2         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503360 RW
	UINT32 lpd4_reg_tREFI_dfs2              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs2           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503364 RW
	UINT32 lpd4_reg_tMRR4I_dfs2             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503368 RW
	UINT32 lpd4_reg_tRRD_dfs2               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs2           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs2           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs2               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450336C RW
	UINT32 lpd4_reg_tRAS_dfs2               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs2              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs2              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs2               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503370 RW
	UINT32 lpd4_reg_tRAP_dfs2               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs2        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs2    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs2    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503374 RW
	UINT32 lpd4_reg_tRCD_derate_dfs2        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs2        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs2       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs2       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503378 RW
	UINT32 lpd4_reg_tWAP_derate_dfs2        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs2        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4503390 RW
	UINT32 lpd4_reg_ref_ab_en_dfs2          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs2          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M2_LPD4_DFS2_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033A0 RW
	UINT32 lpd4_reg_odt_on_dfs2             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033A4 RW
	UINT32 lpd4_reg_tCCD_dfs2               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs2             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs2               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs2               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033A8 RW
	UINT32 lpd4_reg_tW2PD_dfs2              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs2             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs2           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs2         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs2        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs2               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs2              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs2             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs2           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs2               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033B4 RW
	UINT32 lpd4_reg_tRFCab_dfs2             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs2             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033B8 RW
	UINT32 lpd4_reg_tMRW_dfs2               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs2           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs2       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs2      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033BC RW
	UINT32 lpd4_reg_tFC_dfs2                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs2           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs2               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs2              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs2            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs2             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs2             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs2           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45033E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs2             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs2            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs2             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M2_LPD4_DFS2_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505000 RO
	UINT32 reg_dram_init_done               :1;	//0 //DRAM initialization done
	UINT32 reg_rey_idle                     :1;	//1 //Rey idle
	UINT32 resvd0                           :2;  
	UINT32 reg_init_set                     :1;	//4 //debug mode or before dram initialization
	UINT32 reg_set                          :1;	//5 //debug mode or rey idle
	UINT32 reg_alp_ready                    :1;	//6 //ALP READY state
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M2_DEBUG_COMMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505004 RW
	UINT32 reg_debug_mon_period             :20;	//19:0	//debug monitoring period (ex: 100ms) - (reg_base_period+1) * (reg_debug_mon_period+1)
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505010 RW
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
}REG_DDRC_M2_IRQ_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505014 RO
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
}REG_DDRC_M2_IRQ_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505100 RO
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
}REG_DDRC_M2_DEBUG_BUS_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505200 RO
	UINT32 reg_aw_err_0                     :4;	//3:0	//AXI AW Request ERR flag in port0
	UINT32 reg_aw_err_1                     :4;	//7:4	//AXI AW Request ERR flag in port1
	UINT32 reg_aw_err_2                     :4;	//11:8	//AXI AW Request ERR flag in port2
	UINT32 reg_aw_err_3                     :4;	//15:12	//AXI AW Request ERR flag in port3
	UINT32 reg_ar_err_0                     :4;	//19:16	//AXI AR Request ERR flag in port0
	UINT32 reg_ar_err_1                     :4;	//23:20	//AXI AR Request ERR flag in port1
	UINT32 reg_ar_err_2                     :4;	//27:24	//AXI AR Request ERR flag in port2
	UINT32 reg_ar_err_3                     :4;	//31:28	//AXI AR Request ERR flag in port3
	};
}REG_DDRC_M2_DEBUG_PORT_IF_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505204 RW
	UINT32 reg_port_cmd_mon_en              :1;	//0 //AXI  Request capture en in wfo/rfo
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_DEBUG_PORT_IF_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505208 RO
	UINT32 reg_ar_err_id                    :18;	//17:0	//AXI AR Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M2_DEBUG_PORT_IF_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450520C RO
	UINT32 reg_ar_err_addr                  :32;	//31:0	//AXI AR Request ERR or Last Request's addr
	};
}REG_DDRC_M2_DEBUG_PORT_IF_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505210 RO
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
}REG_DDRC_M2_DEBUG_PORT_IF_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505214 RO
	UINT32 reg_aw_err_id                    :18;	//17:0	//AXI AW Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M2_DEBUG_PORT_IF_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505218 RO
	UINT32 reg_aw_err_addr                  :32;	//31:0	//AXI AW Request ERR or Last Request's addr
	};
}REG_DDRC_M2_DEBUG_PORT_IF_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450521C RO
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
}REG_DDRC_M2_DEBUG_PORT_IF_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505300 RO
	UINT32 reg_debug_wuq_valid              :1;	//0 //wuq to sch valid signal probe
	UINT32 reg_debug_wuq_ready              :1;	//1 //wuq to sch ready signal probe
	UINT32 reg_debug_ruq_valid              :1;	//2 //ruq to sch valid signal probe
	UINT32 reg_debug_ruq_ready              :1;	//3 //ruq to sch ready signal probe
	UINT32 resvd                            :28; 
	};
}REG_DDRC_M2_DEBUG_UQ_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505304 RO
	UINT32 reg_debug_wuq_c_cnt              :6;	//5:0	//wuq data queue pending cnt
	UINT32 resvd0                           :10; 
	UINT32 reg_debug_wuq_d_cnt              :9;	//24:16	//wuq command queue pending cnt
	UINT32 resvd1                           :7;  
	};
}REG_DDRC_M2_DEBUG_UQ_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505400 RO
	UINT32 reg_debug_prg_rdy                :8;	//7:0	//precharge ready signal probe per each bank
	UINT32 reg_debug_act_rdy                :8;	//15:8	//activate ready signal probe per each bank
	UINT32 reg_debug_wr_rdy                 :8;	//23:16	//write ready signal probe per each bank
	UINT32 reg_debug_mwr_rdy                :8;	//31:24	//masked write ready signal probe per each bank
	};
}REG_DDRC_M2_DEBUG_SCH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505404 RO
	UINT32 reg_debug_rd_rdy                 :8;	//7:0	//read ready signal probe per each bank
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_DEBUG_SCH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505500 RO
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
}REG_DDRC_M2_DEBUG_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505504 RO
	UINT32 reg_debug_pd_cnt                 :16;	//15:0	//the number of power down entry during monitor period
	UINT32 reg_debug_sr_cnt                 :16;	//31:16	//the number of self refresh entry during monitor period
	};
}REG_DDRC_M2_DEBUG_ALP_ENTRY_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505508 RO
	UINT32 reg_debug_pd_time                :16;	//15:0	//total time of power down stay during monitor period
	UINT32 reg_debug_sr_time                :16;	//31:16	//total time of self refresh stay during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M2_DEBUG_ALP_TIME_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450550C RO
	UINT32 reg_debug_pd_std_cnt             :8;	//7:0	//max value of power down entry waiting counter during monitor period
	UINT32 reg_debug_sr_std_cnt             :8;	//15:8	//max value of self refresh entry waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	UINT32 reg_debug_pd_ex_std_cnt          :8;	//23:16	//max value of power down exit waiting counter during monitor period
	UINT32 reg_debug_sr_ex_std_cnt          :8;	//31:24	//max value of self refresh exit waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M2_DEBUG_ALP_WAIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505600 RO
	UINT32 reg_debug_dfs_state              :3;	//2:0	//dfs status
	UINT32 resvd                            :29; 
	};
}REG_DDRC_M2_DEBUG_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505700 RO
	UINT32 reg_debug_nidle                  :32;	//31:0	//number of idle cycle
	};
}REG_DDRC_M2_DEBUG_IDLE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505704 RO
	UINT32 reg_debug_nrd                    :32;	//31:0	//number of short read commands
	};
}REG_DDRC_M2_DEBUG_RD_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505708 RO
	UINT32 reg_debug_nrdl                   :32;	//31:0	//number of long read commands
	};
}REG_DDRC_M2_DEBUG_RDL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505710 RO
	UINT32 reg_debug_nwr                    :32;	//31:0	//number of short write commands
	};
}REG_DDRC_M2_DEBUG_RWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505714 RO
	UINT32 reg_debug_nmwr                   :32;	//31:0	//number of short masked write commands
	};
}REG_DDRC_M2_DEBUG_MWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505718 RO
	UINT32 reg_debug_nwrl                   :32;	//31:0	//number of long write commands
	};
}REG_DDRC_M2_DEBUG_WRL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505720 RO
	UINT32 reg_debug_nap                    :20;	//19:0	//number of AP commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_PRG_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505724 RO
	UINT32 reg_debug_nref                   :20;	//19:0	//number of all bank refresh commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_REF_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505728 RO
	UINT32 reg_debug_nact                   :32;	//31:0	//number of act commands
	};
}REG_DDRC_M2_DEBUG_ACT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450572C RO
	UINT32 reg_debug_nrw_swc                :32;	//31:0	//number of read/write command swich
	};
}REG_DDRC_M2_DEBUG_RW_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505730 RO
	UINT32 reg_debug_nr_urg_swc             :32;	//31:0	//number of urgent read command swich
	};
}REG_DDRC_M2_DEBUG_R_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505734 RO
	UINT32 reg_debug_nr_req_row_hit         :32;	//31:0	//number of req_row hit in read port
	};
}REG_DDRC_M2_DEBUG_R_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505738 RO
	UINT32 reg_debug_nr_req_hit             :32;	//31:0	//number of req hit in read port
	};
}REG_DDRC_M2_DEBUG_R_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450573C RO
	UINT32 reg_debug_nr_urg_row_hit         :32;	//31:0	//number of urgent row hit in read port
	};
}REG_DDRC_M2_DEBUG_R_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505740 RO
	UINT32 reg_debug_nr_urg_hit             :32;	//31:0	//number of urgent hit in read port
	};
}REG_DDRC_M2_DEBUG_R_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505744 RO
	UINT32 reg_debug_nr_row_hit             :32;	//31:0	//number of row hit in read port
	};
}REG_DDRC_M2_DEBUG_R_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505748 RO
	UINT32 reg_debug_nr_lucky_hit           :32;	//31:0	//number of lucky in read port
	};
}REG_DDRC_M2_DEBUG_R_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505750 RO
	UINT32 reg_debug_nw_urg_swc             :32;	//31:0	//number of urgent write command swich
	};
}REG_DDRC_M2_DEBUG_W_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505754 RO
	UINT32 reg_debug_nw_req_row_hit         :32;	//31:0	//number of req_row hit in write port
	};
}REG_DDRC_M2_DEBUG_W_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505758 RO
	UINT32 reg_debug_nw_req_hit             :32;	//31:0	//number of req hit in write port
	};
}REG_DDRC_M2_DEBUG_W_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450575C RO
	UINT32 reg_debug_nw_urg_row_hit         :32;	//31:0	//number of urgent row hit in write port
	};
}REG_DDRC_M2_DEBUG_W_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505760 RO
	UINT32 reg_debug_nw_urg_hit             :32;	//31:0	//number of urgent hit in write port
	};
}REG_DDRC_M2_DEBUG_W_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505764 RO
	UINT32 reg_debug_nw_row_hit             :32;	//31:0	//number of row hit in write port
	};
}REG_DDRC_M2_DEBUG_W_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505768 RO
	UINT32 reg_debug_nw_lucky_hit           :32;	//31:0	//number of lucky in write port
	};
}REG_DDRC_M2_DEBUG_W_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505770 RO
	UINT32 reg_debug_max_lat_3              :8;	//7:0	//max latency for qos 1~3
	UINT32 reg_debug_max_lat_5              :8;	//15:8	//max latency for qos 4~5
	UINT32 reg_debug_max_lat_7              :8;	//23:16	//max latency for qos 6~7
	UINT32 reg_debug_max_lat_8              :8;	//31:24	//max latency for qos 8~
	};
}REG_DDRC_M2_DEBUG_MAX_LAT_QOS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505800 RO
	UINT32 reg_debug_nr_hyb_swc             :32;	//31:0	//number of hybrid read command swich
	};
}REG_DDRC_M2_DEBUG_R_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505804 RO
	UINT32 reg_debug_nw_hyb_swc             :32;	//31:0	//number of hybrid write command swich
	};
}REG_DDRC_M2_DEBUG_W_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505900 RO
	UINT32 reg_debug_nr_fifo_0_prt          :32;	//31:0	//number of read fifo 0 prt
	};
}REG_DDRC_M2_DEBUG_R_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505904 RO
	UINT32 reg_debug_nr_fifo_1_prt          :32;	//31:0	//number of read fifo 1 prt
	};
}REG_DDRC_M2_DEBUG_R_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505908 RO
	UINT32 reg_debug_nr_fifo_2_prt          :32;	//31:0	//number of read fifo 2 prt
	};
}REG_DDRC_M2_DEBUG_R_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450590C RO
	UINT32 reg_debug_nr_fifo_3_prt          :32;	//31:0	//number of read fifo 3 prt
	};
}REG_DDRC_M2_DEBUG_R_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505910 RO
	UINT32 reg_debug_nw_fifo_0_prt          :32;	//31:0	//number of write fifo 0 prt
	};
}REG_DDRC_M2_DEBUG_W_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505914 RO
	UINT32 reg_debug_nw_fifo_1_prt          :32;	//31:0	//number of write fifo 1 prt
	};
}REG_DDRC_M2_DEBUG_W_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4505918 RO
	UINT32 reg_debug_nw_fifo_2_prt          :32;	//31:0	//number of write fifo 2 prt
	};
}REG_DDRC_M2_DEBUG_W_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450591C RO
	UINT32 reg_debug_nw_fifo_3_prt          :32;	//31:0	//number of write fifo 3 prt
	};
}REG_DDRC_M2_DEBUG_W_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506000 RO
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
}REG_DDRC_M2_DEBUG_LPD4_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506004 RO
	UINT32 lpd4_mf_reg_fsm_status_0         :32;	//31:0	//Main FSM information (1ST)
	};
}REG_DDRC_M2_DEBUG_LPD4_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506008 RO
	UINT32 lpd4_mf_reg_fsm_status_1         :32;	//31:0	//Main FSM information (2ND)
	};
}REG_DDRC_M2_DEBUG_LPD4_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450600C RO
	UINT32 lpd4_mf_reg_fsm_status_2         :1;	//0 //Main FSM information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_DEBUG_LPD4_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506010 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_0    :32;	//31:0	//Direct control done information (1ST)
	};
}REG_DDRC_M2_DEBUG_LPD4_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506014 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_1    :32;	//31:0	//Direct control done information (2ND)
	};
}REG_DDRC_M2_DEBUG_LPD4_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506018 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_2    :1;	//0 //Direct control done information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M2_DEBUG_LPD4_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450601C RO
	UINT32 lpd4_rr_reg_ref_req_ctrl_status  :32;	//31:0	//[31:16] : Derated tREFI	[15:12] : Derated threshold value of urgent refresh	[11:4] : Derated tRRD	[1] : Forced all-bank refresh mode	[0] : Distributed all-bank refresh mode
	};
}REG_DDRC_M2_DEBUG_LPD4_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506020 RO
	UINT32 lpd4_rc_reg_fsm_status           :11;	//10:0	//Refresh controller FSM information
	UINT32 resvd                            :5;  
	UINT32 lpd4_rc_reg_ref_pb_sel_flag      :8;	//23:16	//Bank selection information for per-bank refresh
	UINT32 lpd4_rc_reg_ref_pb_done_flag     :8;	//31:24	//Bank completion information for per-bank refresh
	};
}REG_DDRC_M2_DEBUG_LPD4_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506024 RO
	UINT32 lpd4_bf_reg_fsm_status_b0        :14;	//13:0	//Bank FSM information (bank0)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b1        :14;	//29:16	//Bank FSM information (bank1)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M2_DEBUG_LPD4_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506028 RO
	UINT32 lpd4_bf_reg_fsm_status_b2        :14;	//13:0	//Bank FSM information (bank2)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b3        :14;	//29:16	//Bank FSM information (bank3)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M2_DEBUG_LPD4_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450602C RO
	UINT32 lpd4_bf_reg_fsm_status_b4        :14;	//13:0	//Bank FSM information (bank4)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b5        :14;	//29:16	//Bank FSM information (bank5)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M2_DEBUG_LPD4_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506030 RO
	UINT32 lpd4_bf_reg_fsm_status_b6        :14;	//13:0	//Bank FSM information (bank6)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b7        :14;	//29:16	//Bank FSM information (bank7)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M2_DEBUG_LPD4_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506034 RO
	UINT32 lpd4_bs_reg_bank_open            :8;	//7:0	//Bank open information
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M2_DEBUG_LPD4_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506038 RO
	UINT32 lpd4_bs_reg_rdy_status_0         :32;	//31:0	//Bank ready information	[31:24] : Read	[23:16] : Masked write	[15:8] : Write	[7:0] : Activate
	};
}REG_DDRC_M2_DEBUG_LPD4_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450603C RO
	UINT32 lpd4_bs_reg_rdy_status_1         :32;	//31:0	//Bank ready information	[28] : MRR	[27] : MRW	[26] : Power-down	[25] : All-bank refresh	[23:16] : Per-bank refresh	[15:8] : Auto-precharge	[7:0] : Per-bank precharge
	};
}REG_DDRC_M2_DEBUG_LPD4_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506040 RO
	UINT32 lpd4_pi_reg_fifo_status          :32;	//31:0	//Pointer information	[22:20] : Read pipeline pointer	[18:16] : Write pipeline pointer	[15:12] : RFIFO output pointer	[11:8] : RFIFO input pointer	[7:4] : WFIFO output pointer	[3:0] : WFIFO input pointer
	};
}REG_DDRC_M2_DEBUG_LPD4_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506100 RO
	UINT32 lpd4_mr_reg_mr0_ch0              :8;	//7:0	//MR0 read information for CH0
	UINT32 lpd4_mr_reg_mr4_ch0              :8;	//15:8	//MR4 read information for CH0
	UINT32 lpd4_mr_reg_mr5_ch0              :8;	//23:16	//MR5 read information for CH0
	UINT32 lpd4_mr_reg_mr6_ch0              :8;	//31:24	//MR6 read information for CH0
	};
}REG_DDRC_M2_DEBUG_LPD4_MR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506104 RO
	UINT32 lpd4_mr_reg_mr7_ch0              :8;	//7:0	//MR7 read information for CH0
	UINT32 lpd4_mr_reg_mr8_ch0              :8;	//15:8	//MR8 read information for CH0
	UINT32 lpd4_mr_reg_mr12_ch0             :8;	//23:16	//MR12 read information for CH0
	UINT32 lpd4_mr_reg_mr14_ch0             :8;	//31:24	//MR14 read information for CH0
	};
}REG_DDRC_M2_DEBUG_LPD4_MR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506108 RO
	UINT32 lpd4_mr_reg_mr18_ch0             :8;	//7:0	//MR18 read information for CH0
	UINT32 lpd4_mr_reg_mr19_ch0             :8;	//15:8	//MR19 read information for CH0
	UINT32 lpd4_mr_reg_mr24_ch0             :8;	//23:16	//MR24 read information for CH0
	UINT32 lpd4_mr_reg_mr25_ch0             :8;	//31:24	//MR25 read information for CH0
	};
}REG_DDRC_M2_DEBUG_LPD4_MR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450610C RO
	UINT32 lpd4_mr_reg_mr0_ch1              :8;	//7:0	//MR0 read information for CH1
	UINT32 lpd4_mr_reg_mr4_ch1              :8;	//15:8	//MR4 read information for CH1
	UINT32 lpd4_mr_reg_mr5_ch1              :8;	//23:16	//MR5 read information for CH1
	UINT32 lpd4_mr_reg_mr6_ch1              :8;	//31:24	//MR6 read information for CH1
	};
}REG_DDRC_M2_DEBUG_LPD4_MR_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506110 RO
	UINT32 lpd4_mr_reg_mr7_ch1              :8;	//7:0	//MR7 read information for CH1
	UINT32 lpd4_mr_reg_mr8_ch1              :8;	//15:8	//MR8 read information for CH1
	UINT32 lpd4_mr_reg_mr12_ch1             :8;	//23:16	//MR12 read information for CH1
	UINT32 lpd4_mr_reg_mr14_ch1             :8;	//31:24	//MR14 read information for CH1
	};
}REG_DDRC_M2_DEBUG_LPD4_MR_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506114 RO
	UINT32 lpd4_mr_reg_mr18_ch1             :8;	//7:0	//MR18 read information for CH1
	UINT32 lpd4_mr_reg_mr19_ch1             :8;	//15:8	//MR19 read information for CH1
	UINT32 lpd4_mr_reg_mr24_ch1             :8;	//23:16	//MR24 read information for CH1
	UINT32 lpd4_mr_reg_mr25_ch1             :8;	//31:24	//MR25 read information for CH1
	};
}REG_DDRC_M2_DEBUG_LPD4_MR_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506118 RO
	UINT32 lpd4_reg_mpc_fifo_fail_cnt       :32;	//31:0	//Periodic MPC FIFO fail count
	};
}REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450611C RO
	UINT32 lpd4_reg_mpc_fifo_fail_data0     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506120 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data1     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506124 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data2     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506128 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data3     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450612C RO
	UINT32 lpd4_reg_mpc_fifo_fail_dmi0      :4;	//3:0	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi1      :4;	//7:4	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi2      :4;	//11:8	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi3      :4;	//15:12	//Periodic MPC FIFO fail dmi data
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506200 RO
	UINT32 reg_mf_mrw1_cnt                  :20;	//19:0	//number of channel 1 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MRW1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506204 RO
	UINT32 reg_mf_mrw0_cnt                  :20;	//19:0	//number of channel 0 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MRW0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506208 RO
	UINT32 reg_mf_lp_exit_cnt               :20;	//19:0	//number of lp exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_LP_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450620C RO
	UINT32 reg_mf_lp_entry_cnt              :20;	//19:0	//number of lp entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_LP_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506210 RO
	UINT32 reg_mf_sr_pd_exit_cnt            :20;	//19:0	//number of self-rerfresh power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_SR_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506214 RO
	UINT32 reg_mf_sr_pd_entry_cnt           :20;	//19:0	//number of self-refresh power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_SR_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506218 RO
	UINT32 reg_mf_sr_exit_cnt               :20;	//19:0	//number of self-refresh exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_SR_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450621C RO
	UINT32 reg_mf_sr_entry_cnt              :20;	//19:0	//number of self_refresh entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_SR_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506220 RO
	UINT32 reg_mf_pd_exit_cnt               :20;	//19:0	//number of power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506224 RO
	UINT32 reg_mf_pd_entry_cnt              :20;	//19:0	//number of power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506228 RO
	UINT32 reg_mf_zqlat_cnt                 :20;	//19:0	//number of zqcal latch command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ZQLAT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450622C RO
	UINT32 reg_mf_zqcal_cnt                 :20;	//19:0	//number of zqcal command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ZQCAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506230 RO
	UINT32 reg_mf_cke_1_cnt                 :20;	//19:0	//number of cke rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_CKE1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506234 RO
	UINT32 reg_mf_cke_0_cnt                 :20;	//19:0	//number of cke falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_CKE0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506238 RO
	UINT32 reg_mf_rstn_1_cnt                :20;	//19:0	//number of reset rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RSTN1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450623C RO
	UINT32 reg_mf_rstn_0_cnt                :20;	//19:0	//number of reset falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RSTN0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506240 RO
	UINT32 reg_cg_rd0_cnt                   :32;	//31:0	//number of bank 0 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506244 RO
	UINT32 reg_cg_rd1_cnt                   :32;	//31:0	//number of bank 1 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506248 RO
	UINT32 reg_cg_rd2_cnt                   :32;	//31:0	//number of bank 2 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450624C RO
	UINT32 reg_cg_rd3_cnt                   :32;	//31:0	//number of bank 3 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506250 RO
	UINT32 reg_cg_rd4_cnt                   :32;	//31:0	//number of bank 4 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506254 RO
	UINT32 reg_cg_rd5_cnt                   :32;	//31:0	//number of bank 5 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506258 RO
	UINT32 reg_cg_rd6_cnt                   :32;	//31:0	//number of bank 6 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450625C RO
	UINT32 reg_cg_rd7_cnt                   :32;	//31:0	//number of bank 7 read command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_RD7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506260 RO
	UINT32 reg_cg_mwr0_cnt                  :32;	//31:0	//number of bank 0 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506264 RO
	UINT32 reg_cg_mwr1_cnt                  :32;	//31:0	//number of bank 1 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506268 RO
	UINT32 reg_cg_mwr2_cnt                  :32;	//31:0	//number of bank 2 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450626C RO
	UINT32 reg_cg_mwr3_cnt                  :32;	//31:0	//number of bank 3 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506270 RO
	UINT32 reg_cg_mwr4_cnt                  :32;	//31:0	//number of bank 4 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506274 RO
	UINT32 reg_cg_mwr5_cnt                  :32;	//31:0	//number of bank 5 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506278 RO
	UINT32 reg_cg_mwr6_cnt                  :32;	//31:0	//number of bank 6 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450627C RO
	UINT32 reg_cg_mwr7_cnt                  :32;	//31:0	//number of bank 7 masked write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MWR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506280 RO
	UINT32 reg_cg_wr0_cnt                   :32;	//31:0	//number of bank 0 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506284 RO
	UINT32 reg_cg_wr1_cnt                   :32;	//31:0	//number of bank 1 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506288 RO
	UINT32 reg_cg_wr2_cnt                   :32;	//31:0	//number of bank 2 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450628C RO
	UINT32 reg_cg_wr3_cnt                   :32;	//31:0	//number of bank 3 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506290 RO
	UINT32 reg_cg_wr4_cnt                   :32;	//31:0	//number of bank 4 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506294 RO
	UINT32 reg_cg_wr5_cnt                   :32;	//31:0	//number of bank 5 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506298 RO
	UINT32 reg_cg_wr6_cnt                   :32;	//31:0	//number of bank 6 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450629C RO
	UINT32 reg_cg_wr7_cnt                   :32;	//31:0	//number of bank 7 write command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_WR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062A0 RO
	UINT32 reg_cg_act0_cnt                  :32;	//31:0	//number of bank 0 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062A4 RO
	UINT32 reg_cg_act1_cnt                  :32;	//31:0	//number of bank 1 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062A8 RO
	UINT32 reg_cg_act2_cnt                  :32;	//31:0	//number of bank 2 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062AC RO
	UINT32 reg_cg_act3_cnt                  :32;	//31:0	//number of bank 3 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062B0 RO
	UINT32 reg_cg_act4_cnt                  :32;	//31:0	//number of bank 4 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062B4 RO
	UINT32 reg_cg_act5_cnt                  :32;	//31:0	//number of bank 5 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062B8 RO
	UINT32 reg_cg_act6_cnt                  :32;	//31:0	//number of bank 6 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45062BC RO
	UINT32 reg_cg_act7_cnt                  :32;	//31:0	//number of bank 7 activate command issued by command generator
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_ACT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506300 RO
	UINT32 reg_ref_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506304 RO
	UINT32 reg_ref_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506308 RO
	UINT32 reg_ref_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450630C RO
	UINT32 reg_ref_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506310 RO
	UINT32 reg_ref_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506314 RO
	UINT32 reg_ref_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506318 RO
	UINT32 reg_ref_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450631C RO
	UINT32 reg_ref_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506320 RO
	UINT32 reg_prg_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506324 RO
	UINT32 reg_prg_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506328 RO
	UINT32 reg_prg_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450632C RO
	UINT32 reg_prg_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506330 RO
	UINT32 reg_prg_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506334 RO
	UINT32 reg_prg_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506338 RO
	UINT32 reg_prg_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450633C RO
	UINT32 reg_prg_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506340 RO
	UINT32 reg_cg_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_CG_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506344 RO
	UINT32 reg_mf_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MF_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506350 RO
	UINT32 reg_cg_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_CG_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506354 RO
	UINT32 reg_mf_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_MF_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506360 RO
	UINT32 reg_cg_bl_cnt                    :22;	//21:0	//number of long burst command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_CG_BL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506364 RO
	UINT32 reg_cg_ap_cnt                    :22;	//21:0	//number of auto precharge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_CG_AP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506368 RO
	UINT32 reg_ref_cycling_done_cnt         :20;	//19:0	//number of refresh cycling done command
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M2_DEBUG_CTRL_CMD_REF_CYCLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506700 RO
	UINT32 pi_reg_dfi_status                :32;	//31:0	//DFI information	[30] : dfi_lp_ack	[29:26] : dfi_lp_wakeup	[25] : dfi_lp_req	[24] : dfi_dram_clk_disable	[23:21] : pll_freq_type[2:0]	[20] : pll_lock_done	[19:18] : pll_freq_type[4:3]	[17] : dfi_ctrlupd_ack	[16] : dfi_ctrlupd_req	[14] : dfi_phyupd_ack	[13] : dfi_phyupd_type	[12] : dfi_phyupd_req	[10] : dfi_phymstr_ack	[9] : dfi_phymstr_type	[8] : dfi_phymstr_req	[6] : dfi_init_complete	[5:1] : dfi_frequency	[0] : dfi_init_start
	};
}REG_DDRC_M2_DEBUG_DFI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506800 
	UINT32 reg_bist_start                   :1;	//0 //dram bist start, 0: stop, 1: start
	UINT32 resvd0                           :3;  
	UINT32 reg_bist_done                    :1;	//4 //dram bist done check, 0: running or idle, 1: done
	UINT32 resvd1                           :3;  
	UINT32 reg_bist_result                  :1;	//8 //dram bist result check , 0: PASS, 1: FAIL
	UINT32 resvd2                           :3;  
	UINT32 reg_bist_opcmd_ptr               :4;	//15:12	//dram bist opcmd pointer monitor
	UINT32 reg_bist_err_cnt                 :16;	//31:16	//dram bist err count monitor
	};
}REG_DDRC_M2_DRAM_BIST_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506804 
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
}REG_DDRC_M2_DRAM_BIST_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506808 
	UINT32 reg_bist_cmdq_vld                :16;	//15:0	//bist cmdq valid state monitor
	UINT32 reg_bist_cmdq_req                :16;	//31:16	//bist cmdq request state monitor
	};
}REG_DDRC_M2_DRAM_BIST_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450680C 
	UINT32 reg_user_pat                     :32;	//31:0	//set bist user data pattern
	};
}REG_DDRC_M2_DRAM_BIST_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506810 
	UINT32 reg_mask_pat_0                   :16;	//15:0	//data mask for 1st 16byte data
	UINT32 reg_mask_pat_1                   :16;	//31:16	//data mask for 2nd 16byte data
	};
}REG_DDRC_M2_DRAM_BIST_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506814 
	UINT32 reg_mask_pat_2                   :16;	//15:0	//data mask for 3rd 16byte data
	UINT32 reg_mask_pat_3                   :16;	//31:16	//data mask for 4th 16byte data
	};
}REG_DDRC_M2_DRAM_BIST_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506818 
	UINT32 reg_bist_addr_cnt_max            :32;	//31:0	//Set how many times to repeat when reg_bist_addr_map is not "SPL".
	};
}REG_DDRC_M2_DRAM_BIST_ADDR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450681C 
	UINT32 reg_s_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col)
	};
}REG_DDRC_M2_DRAM_BIST_ADDR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506820 
	UINT32 reg_e_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col), default 2Gbyte setting
	};
}REG_DDRC_M2_DRAM_BIST_ADDR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506824 
	UINT32 reg_bist_opcmd_00                :8;	//7:0	//
	UINT32 reg_bist_opcmd_01                :8;	//15:8	//
	UINT32 reg_bist_opcmd_02                :8;	//23:16	//
	UINT32 reg_bist_opcmd_03                :8;	//31:24	//set bist operation cmd  , default MARCH C-,
	};
}REG_DDRC_M2_DRAM_BIST_OPCMD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506828 
	UINT32 reg_bist_opcmd_04                :8;	//7:0	//
	UINT32 reg_bist_opcmd_05                :8;	//15:8	//
	UINT32 reg_bist_opcmd_06                :8;	//23:16	//
	UINT32 reg_bist_opcmd_07                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M2_DRAM_BIST_OPCMD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450682C 
	UINT32 reg_bist_opcmd_08                :8;	//7:0	//
	UINT32 reg_bist_opcmd_09                :8;	//15:8	//
	UINT32 reg_bist_opcmd_10                :8;	//23:16	//
	UINT32 reg_bist_opcmd_11                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M2_DRAM_BIST_OPCMD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506830 
	UINT32 reg_bist_opcmd_12                :8;	//7:0	//
	UINT32 reg_bist_opcmd_13                :8;	//15:8	//
	UINT32 reg_bist_opcmd_14                :8;	//23:16	//
	UINT32 reg_bist_opcmd_15                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M2_DRAM_BIST_OPCMD_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506834 RO
	UINT32 reg_err_addr                     :32;	//31:0	//address where error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_ADDR_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506838 RO
	UINT32 reg_err_data_00                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450683C RO
	UINT32 reg_err_data_01                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506840 RO
	UINT32 reg_err_data_02                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506844 RO
	UINT32 reg_err_data_03                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506848 RO
	UINT32 reg_err_data_04                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450684C RO
	UINT32 reg_err_data_05                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506850 RO
	UINT32 reg_err_data_06                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506854 RO
	UINT32 reg_err_data_07                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506858 RO
	UINT32 reg_err_data_08                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450685C RO
	UINT32 reg_err_data_09                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506860 RO
	UINT32 reg_err_data_10                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506864 RO
	UINT32 reg_err_data_11                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506868 RO
	UINT32 reg_err_data_12                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450686C RO
	UINT32 reg_err_data_13                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506870 RO
	UINT32 reg_err_data_14                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506874 RO
	UINT32 reg_err_data_15                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506878 RO
	UINT32 reg_exp_data_00                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450687C RO
	UINT32 reg_exp_data_01                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506880 RO
	UINT32 reg_exp_data_02                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506884 RO
	UINT32 reg_exp_data_03                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506888 RO
	UINT32 reg_exp_data_04                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450688C RO
	UINT32 reg_exp_data_05                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506890 RO
	UINT32 reg_exp_data_06                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506894 RO
	UINT32 reg_exp_data_07                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506898 RO
	UINT32 reg_exp_data_08                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC450689C RO
	UINT32 reg_exp_data_09                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45068A0 RO
	UINT32 reg_exp_data_10                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45068A4 RO
	UINT32 reg_exp_data_11                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45068A8 RO
	UINT32 reg_exp_data_12                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45068AC RO
	UINT32 reg_exp_data_13                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45068B0 RO
	UINT32 reg_exp_data_14                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC45068B4 RO
	UINT32 reg_exp_data_15                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4506FE0 RW
	UINT32 reg_rey_spare                    :32;	//31:0	//spare register for ECO (should not be removed)
	};
}REG_DDRC_M2_REY_SPARE_T;

typedef struct {
	REG_DDRC_M2_DRAM_CONF_T                                   dram_conf;	//0xC4500000
	REG_DDRC_M2_MODE_SEL_T                                     mode_sel;	//0xC4500004
	REG_DDRC_M2_BASE_PERIOD_T                               base_period;	//0xC4500008
	UINT32                                                    reserved0;	//0xC450000C
	UINT32                                                    reserved1;	//0xC4500010
	UINT32                                                    reserved2;	//0xC4500014
	UINT32                                                    reserved3;	//0xC4500018
	UINT32                                                    reserved4;	//0xC450001C
	UINT32                                                    reserved5;	//0xC4500020
	UINT32                                                    reserved6;	//0xC4500024
	UINT32                                                    reserved7;	//0xC4500028
	UINT32                                                    reserved8;	//0xC450002C
	UINT32                                                    reserved9;	//0xC4500030
	UINT32                                                   reserved10;	//0xC4500034
	UINT32                                                   reserved11;	//0xC4500038
	UINT32                                                   reserved12;	//0xC450003C
	UINT32                                                   reserved13;	//0xC4500040
	UINT32                                                   reserved14;	//0xC4500044
	UINT32                                                   reserved15;	//0xC4500048
	UINT32                                                   reserved16;	//0xC450004C
	UINT32                                                   reserved17;	//0xC4500050
	UINT32                                                   reserved18;	//0xC4500054
	UINT32                                                   reserved19;	//0xC4500058
	UINT32                                                   reserved20;	//0xC450005C
	UINT32                                                   reserved21;	//0xC4500060
	UINT32                                                   reserved22;	//0xC4500064
	UINT32                                                   reserved23;	//0xC4500068
	UINT32                                                   reserved24;	//0xC450006C
	UINT32                                                   reserved25;	//0xC4500070
	UINT32                                                   reserved26;	//0xC4500074
	UINT32                                                   reserved27;	//0xC4500078
	UINT32                                                   reserved28;	//0xC450007C
	UINT32                                                   reserved29;	//0xC4500080
	UINT32                                                   reserved30;	//0xC4500084
	UINT32                                                   reserved31;	//0xC4500088
	UINT32                                                   reserved32;	//0xC450008C
	UINT32                                                   reserved33;	//0xC4500090
	UINT32                                                   reserved34;	//0xC4500094
	UINT32                                                   reserved35;	//0xC4500098
	UINT32                                                   reserved36;	//0xC450009C
	UINT32                                                   reserved37;	//0xC45000A0
	UINT32                                                   reserved38;	//0xC45000A4
	UINT32                                                   reserved39;	//0xC45000A8
	UINT32                                                   reserved40;	//0xC45000AC
	UINT32                                                   reserved41;	//0xC45000B0
	UINT32                                                   reserved42;	//0xC45000B4
	UINT32                                                   reserved43;	//0xC45000B8
	UINT32                                                   reserved44;	//0xC45000BC
	UINT32                                                   reserved45;	//0xC45000C0
	UINT32                                                   reserved46;	//0xC45000C4
	UINT32                                                   reserved47;	//0xC45000C8
	UINT32                                                   reserved48;	//0xC45000CC
	UINT32                                                   reserved49;	//0xC45000D0
	UINT32                                                   reserved50;	//0xC45000D4
	UINT32                                                   reserved51;	//0xC45000D8
	UINT32                                                   reserved52;	//0xC45000DC
	UINT32                                                   reserved53;	//0xC45000E0
	UINT32                                                   reserved54;	//0xC45000E4
	UINT32                                                   reserved55;	//0xC45000E8
	UINT32                                                   reserved56;	//0xC45000EC
	UINT32                                                   reserved57;	//0xC45000F0
	UINT32                                                   reserved58;	//0xC45000F4
	UINT32                                                   reserved59;	//0xC45000F8
	UINT32                                                   reserved60;	//0xC45000FC
	REG_DDRC_M2_ALP_T                                               alp;	//0xC4500100
	REG_DDRC_M2_CGL_T                                               cgl;	//0xC4500104
	REG_DDRC_M2_CGL_MON_T                                       cgl_mon;	//0xC4500108
	UINT32                                                   reserved61;	//0xC450010C
	UINT32                                                   reserved62;	//0xC4500110
	UINT32                                                   reserved63;	//0xC4500114
	UINT32                                                   reserved64;	//0xC4500118
	UINT32                                                   reserved65;	//0xC450011C
	UINT32                                                   reserved66;	//0xC4500120
	UINT32                                                   reserved67;	//0xC4500124
	UINT32                                                   reserved68;	//0xC4500128
	UINT32                                                   reserved69;	//0xC450012C
	UINT32                                                   reserved70;	//0xC4500130
	UINT32                                                   reserved71;	//0xC4500134
	UINT32                                                   reserved72;	//0xC4500138
	UINT32                                                   reserved73;	//0xC450013C
	UINT32                                                   reserved74;	//0xC4500140
	UINT32                                                   reserved75;	//0xC4500144
	UINT32                                                   reserved76;	//0xC4500148
	UINT32                                                   reserved77;	//0xC450014C
	UINT32                                                   reserved78;	//0xC4500150
	UINT32                                                   reserved79;	//0xC4500154
	UINT32                                                   reserved80;	//0xC4500158
	UINT32                                                   reserved81;	//0xC450015C
	UINT32                                                   reserved82;	//0xC4500160
	UINT32                                                   reserved83;	//0xC4500164
	UINT32                                                   reserved84;	//0xC4500168
	UINT32                                                   reserved85;	//0xC450016C
	UINT32                                                   reserved86;	//0xC4500170
	UINT32                                                   reserved87;	//0xC4500174
	UINT32                                                   reserved88;	//0xC4500178
	UINT32                                                   reserved89;	//0xC450017C
	UINT32                                                   reserved90;	//0xC4500180
	UINT32                                                   reserved91;	//0xC4500184
	UINT32                                                   reserved92;	//0xC4500188
	UINT32                                                   reserved93;	//0xC450018C
	UINT32                                                   reserved94;	//0xC4500190
	UINT32                                                   reserved95;	//0xC4500194
	UINT32                                                   reserved96;	//0xC4500198
	UINT32                                                   reserved97;	//0xC450019C
	UINT32                                                   reserved98;	//0xC45001A0
	UINT32                                                   reserved99;	//0xC45001A4
	UINT32                                                  reserved100;	//0xC45001A8
	UINT32                                                  reserved101;	//0xC45001AC
	UINT32                                                  reserved102;	//0xC45001B0
	UINT32                                                  reserved103;	//0xC45001B4
	UINT32                                                  reserved104;	//0xC45001B8
	UINT32                                                  reserved105;	//0xC45001BC
	UINT32                                                  reserved106;	//0xC45001C0
	UINT32                                                  reserved107;	//0xC45001C4
	UINT32                                                  reserved108;	//0xC45001C8
	UINT32                                                  reserved109;	//0xC45001CC
	UINT32                                                  reserved110;	//0xC45001D0
	UINT32                                                  reserved111;	//0xC45001D4
	UINT32                                                  reserved112;	//0xC45001D8
	UINT32                                                  reserved113;	//0xC45001DC
	UINT32                                                  reserved114;	//0xC45001E0
	UINT32                                                  reserved115;	//0xC45001E4
	UINT32                                                  reserved116;	//0xC45001E8
	UINT32                                                  reserved117;	//0xC45001EC
	UINT32                                                  reserved118;	//0xC45001F0
	UINT32                                                  reserved119;	//0xC45001F4
	UINT32                                                  reserved120;	//0xC45001F8
	UINT32                                                  reserved121;	//0xC45001FC
	REG_DDRC_M2_PERFMON_T                                       perfmon;	//0xC4500200
	REG_DDRC_M2_PERFMON_EMG_MAX_T                       perfmon_emg_max;	//0xC4500204
	UINT32                                                  reserved122;	//0xC4500208
	UINT32                                                  reserved123;	//0xC450020C
	REG_DDRC_M2_PERFMON_W0_T                                 perfmon_w0;	//0xC4500210
	REG_DDRC_M2_PERFMON_W1_T                                 perfmon_w1;	//0xC4500214
	REG_DDRC_M2_PERFMON_W2_T                                 perfmon_w2;	//0xC4500218
	REG_DDRC_M2_PERFMON_W3_T                                 perfmon_w3;	//0xC450021C
	REG_DDRC_M2_PERFMON_R0_T                                 perfmon_r0;	//0xC4500220
	REG_DDRC_M2_PERFMON_R1_T                                 perfmon_r1;	//0xC4500224
	REG_DDRC_M2_PERFMON_R2_T                                 perfmon_r2;	//0xC4500228
	REG_DDRC_M2_PERFMON_R3_T                                 perfmon_r3;	//0xC450022C
	REG_DDRC_M2_LATMON_T                                         latmon;	//0xC4500230
	UINT32                                                  reserved124;	//0xC4500234
	UINT32                                                  reserved125;	//0xC4500238
	UINT32                                                  reserved126;	//0xC450023C
	UINT32                                                  reserved127;	//0xC4500240
	UINT32                                                  reserved128;	//0xC4500244
	UINT32                                                  reserved129;	//0xC4500248
	UINT32                                                  reserved130;	//0xC450024C
	UINT32                                                  reserved131;	//0xC4500250
	UINT32                                                  reserved132;	//0xC4500254
	UINT32                                                  reserved133;	//0xC4500258
	UINT32                                                  reserved134;	//0xC450025C
	UINT32                                                  reserved135;	//0xC4500260
	UINT32                                                  reserved136;	//0xC4500264
	UINT32                                                  reserved137;	//0xC4500268
	UINT32                                                  reserved138;	//0xC450026C
	UINT32                                                  reserved139;	//0xC4500270
	UINT32                                                  reserved140;	//0xC4500274
	UINT32                                                  reserved141;	//0xC4500278
	UINT32                                                  reserved142;	//0xC450027C
	UINT32                                                  reserved143;	//0xC4500280
	UINT32                                                  reserved144;	//0xC4500284
	UINT32                                                  reserved145;	//0xC4500288
	UINT32                                                  reserved146;	//0xC450028C
	UINT32                                                  reserved147;	//0xC4500290
	UINT32                                                  reserved148;	//0xC4500294
	UINT32                                                  reserved149;	//0xC4500298
	UINT32                                                  reserved150;	//0xC450029C
	UINT32                                                  reserved151;	//0xC45002A0
	UINT32                                                  reserved152;	//0xC45002A4
	UINT32                                                  reserved153;	//0xC45002A8
	UINT32                                                  reserved154;	//0xC45002AC
	UINT32                                                  reserved155;	//0xC45002B0
	UINT32                                                  reserved156;	//0xC45002B4
	UINT32                                                  reserved157;	//0xC45002B8
	UINT32                                                  reserved158;	//0xC45002BC
	UINT32                                                  reserved159;	//0xC45002C0
	UINT32                                                  reserved160;	//0xC45002C4
	UINT32                                                  reserved161;	//0xC45002C8
	UINT32                                                  reserved162;	//0xC45002CC
	UINT32                                                  reserved163;	//0xC45002D0
	UINT32                                                  reserved164;	//0xC45002D4
	UINT32                                                  reserved165;	//0xC45002D8
	UINT32                                                  reserved166;	//0xC45002DC
	UINT32                                                  reserved167;	//0xC45002E0
	UINT32                                                  reserved168;	//0xC45002E4
	UINT32                                                  reserved169;	//0xC45002E8
	UINT32                                                  reserved170;	//0xC45002EC
	UINT32                                                  reserved171;	//0xC45002F0
	UINT32                                                  reserved172;	//0xC45002F4
	UINT32                                                  reserved173;	//0xC45002F8
	UINT32                                                  reserved174;	//0xC45002FC
	REG_DDRC_M2_DFS_T                                               dfs;	//0xC4500300
	REG_DDRC_M2_DFS_RESULT_T                                 dfs_result;	//0xC4500304
	UINT32                                                  reserved175;	//0xC4500308
	UINT32                                                  reserved176;	//0xC450030C
	UINT32                                                  reserved177;	//0xC4500310
	UINT32                                                  reserved178;	//0xC4500314
	UINT32                                                  reserved179;	//0xC4500318
	UINT32                                                  reserved180;	//0xC450031C
	UINT32                                                  reserved181;	//0xC4500320
	UINT32                                                  reserved182;	//0xC4500324
	UINT32                                                  reserved183;	//0xC4500328
	UINT32                                                  reserved184;	//0xC450032C
	UINT32                                                  reserved185;	//0xC4500330
	UINT32                                                  reserved186;	//0xC4500334
	UINT32                                                  reserved187;	//0xC4500338
	UINT32                                                  reserved188;	//0xC450033C
	UINT32                                                  reserved189;	//0xC4500340
	UINT32                                                  reserved190;	//0xC4500344
	UINT32                                                  reserved191;	//0xC4500348
	UINT32                                                  reserved192;	//0xC450034C
	UINT32                                                  reserved193;	//0xC4500350
	UINT32                                                  reserved194;	//0xC4500354
	UINT32                                                  reserved195;	//0xC4500358
	UINT32                                                  reserved196;	//0xC450035C
	UINT32                                                  reserved197;	//0xC4500360
	UINT32                                                  reserved198;	//0xC4500364
	UINT32                                                  reserved199;	//0xC4500368
	UINT32                                                  reserved200;	//0xC450036C
	UINT32                                                  reserved201;	//0xC4500370
	UINT32                                                  reserved202;	//0xC4500374
	UINT32                                                  reserved203;	//0xC4500378
	UINT32                                                  reserved204;	//0xC450037C
	UINT32                                                  reserved205;	//0xC4500380
	UINT32                                                  reserved206;	//0xC4500384
	UINT32                                                  reserved207;	//0xC4500388
	UINT32                                                  reserved208;	//0xC450038C
	UINT32                                                  reserved209;	//0xC4500390
	UINT32                                                  reserved210;	//0xC4500394
	UINT32                                                  reserved211;	//0xC4500398
	UINT32                                                  reserved212;	//0xC450039C
	UINT32                                                  reserved213;	//0xC45003A0
	UINT32                                                  reserved214;	//0xC45003A4
	UINT32                                                  reserved215;	//0xC45003A8
	UINT32                                                  reserved216;	//0xC45003AC
	UINT32                                                  reserved217;	//0xC45003B0
	UINT32                                                  reserved218;	//0xC45003B4
	UINT32                                                  reserved219;	//0xC45003B8
	UINT32                                                  reserved220;	//0xC45003BC
	UINT32                                                  reserved221;	//0xC45003C0
	UINT32                                                  reserved222;	//0xC45003C4
	UINT32                                                  reserved223;	//0xC45003C8
	UINT32                                                  reserved224;	//0xC45003CC
	UINT32                                                  reserved225;	//0xC45003D0
	UINT32                                                  reserved226;	//0xC45003D4
	UINT32                                                  reserved227;	//0xC45003D8
	UINT32                                                  reserved228;	//0xC45003DC
	UINT32                                                  reserved229;	//0xC45003E0
	UINT32                                                  reserved230;	//0xC45003E4
	UINT32                                                  reserved231;	//0xC45003E8
	UINT32                                                  reserved232;	//0xC45003EC
	UINT32                                                  reserved233;	//0xC45003F0
	UINT32                                                  reserved234;	//0xC45003F4
	UINT32                                                  reserved235;	//0xC45003F8
	UINT32                                                  reserved236;	//0xC45003FC
	REG_DDRC_M2_ADDR_MAP_T                                     addr_map;	//0xC4500400
	REG_DDRC_M2_COMMON_T                                         common;	//0xC4500404
	REG_DDRC_M2_DATA_ENC0_T                                   data_enc0;	//0xC4500408
	REG_DDRC_M2_DATA_ENC1_T                                   data_enc1;	//0xC450040C
	UINT32                                                  reserved237;	//0xC4500410
	UINT32                                                  reserved238;	//0xC4500414
	UINT32                                                  reserved239;	//0xC4500418
	UINT32                                                  reserved240;	//0xC450041C
	UINT32                                                  reserved241;	//0xC4500420
	UINT32                                                  reserved242;	//0xC4500424
	UINT32                                                  reserved243;	//0xC4500428
	UINT32                                                  reserved244;	//0xC450042C
	UINT32                                                  reserved245;	//0xC4500430
	UINT32                                                  reserved246;	//0xC4500434
	UINT32                                                  reserved247;	//0xC4500438
	UINT32                                                  reserved248;	//0xC450043C
	UINT32                                                  reserved249;	//0xC4500440
	UINT32                                                  reserved250;	//0xC4500444
	UINT32                                                  reserved251;	//0xC4500448
	UINT32                                                  reserved252;	//0xC450044C
	UINT32                                                  reserved253;	//0xC4500450
	UINT32                                                  reserved254;	//0xC4500454
	UINT32                                                  reserved255;	//0xC4500458
	UINT32                                                  reserved256;	//0xC450045C
	UINT32                                                  reserved257;	//0xC4500460
	UINT32                                                  reserved258;	//0xC4500464
	UINT32                                                  reserved259;	//0xC4500468
	UINT32                                                  reserved260;	//0xC450046C
	UINT32                                                  reserved261;	//0xC4500470
	UINT32                                                  reserved262;	//0xC4500474
	UINT32                                                  reserved263;	//0xC4500478
	UINT32                                                  reserved264;	//0xC450047C
	UINT32                                                  reserved265;	//0xC4500480
	UINT32                                                  reserved266;	//0xC4500484
	UINT32                                                  reserved267;	//0xC4500488
	UINT32                                                  reserved268;	//0xC450048C
	UINT32                                                  reserved269;	//0xC4500490
	UINT32                                                  reserved270;	//0xC4500494
	UINT32                                                  reserved271;	//0xC4500498
	UINT32                                                  reserved272;	//0xC450049C
	UINT32                                                  reserved273;	//0xC45004A0
	UINT32                                                  reserved274;	//0xC45004A4
	UINT32                                                  reserved275;	//0xC45004A8
	UINT32                                                  reserved276;	//0xC45004AC
	UINT32                                                  reserved277;	//0xC45004B0
	UINT32                                                  reserved278;	//0xC45004B4
	UINT32                                                  reserved279;	//0xC45004B8
	UINT32                                                  reserved280;	//0xC45004BC
	UINT32                                                  reserved281;	//0xC45004C0
	UINT32                                                  reserved282;	//0xC45004C4
	UINT32                                                  reserved283;	//0xC45004C8
	UINT32                                                  reserved284;	//0xC45004CC
	UINT32                                                  reserved285;	//0xC45004D0
	UINT32                                                  reserved286;	//0xC45004D4
	UINT32                                                  reserved287;	//0xC45004D8
	UINT32                                                  reserved288;	//0xC45004DC
	UINT32                                                  reserved289;	//0xC45004E0
	UINT32                                                  reserved290;	//0xC45004E4
	UINT32                                                  reserved291;	//0xC45004E8
	UINT32                                                  reserved292;	//0xC45004EC
	UINT32                                                  reserved293;	//0xC45004F0
	UINT32                                                  reserved294;	//0xC45004F4
	UINT32                                                  reserved295;	//0xC45004F8
	UINT32                                                  reserved296;	//0xC45004FC
	REG_DDRC_M2_RD_URG_T                                         rd_urg;	//0xC4500500
	REG_DDRC_M2_WR_URG_T                                         wr_urg;	//0xC4500504
	UINT32                                                  reserved297;	//0xC4500508
	UINT32                                                  reserved298;	//0xC450050C
	UINT32                                                  reserved299;	//0xC4500510
	UINT32                                                  reserved300;	//0xC4500514
	UINT32                                                  reserved301;	//0xC4500518
	UINT32                                                  reserved302;	//0xC450051C
	UINT32                                                  reserved303;	//0xC4500520
	UINT32                                                  reserved304;	//0xC4500524
	UINT32                                                  reserved305;	//0xC4500528
	UINT32                                                  reserved306;	//0xC450052C
	UINT32                                                  reserved307;	//0xC4500530
	UINT32                                                  reserved308;	//0xC4500534
	UINT32                                                  reserved309;	//0xC4500538
	UINT32                                                  reserved310;	//0xC450053C
	UINT32                                                  reserved311;	//0xC4500540
	UINT32                                                  reserved312;	//0xC4500544
	UINT32                                                  reserved313;	//0xC4500548
	UINT32                                                  reserved314;	//0xC450054C
	UINT32                                                  reserved315;	//0xC4500550
	UINT32                                                  reserved316;	//0xC4500554
	UINT32                                                  reserved317;	//0xC4500558
	UINT32                                                  reserved318;	//0xC450055C
	UINT32                                                  reserved319;	//0xC4500560
	UINT32                                                  reserved320;	//0xC4500564
	UINT32                                                  reserved321;	//0xC4500568
	UINT32                                                  reserved322;	//0xC450056C
	UINT32                                                  reserved323;	//0xC4500570
	UINT32                                                  reserved324;	//0xC4500574
	UINT32                                                  reserved325;	//0xC4500578
	UINT32                                                  reserved326;	//0xC450057C
	UINT32                                                  reserved327;	//0xC4500580
	UINT32                                                  reserved328;	//0xC4500584
	UINT32                                                  reserved329;	//0xC4500588
	UINT32                                                  reserved330;	//0xC450058C
	UINT32                                                  reserved331;	//0xC4500590
	UINT32                                                  reserved332;	//0xC4500594
	UINT32                                                  reserved333;	//0xC4500598
	UINT32                                                  reserved334;	//0xC450059C
	UINT32                                                  reserved335;	//0xC45005A0
	UINT32                                                  reserved336;	//0xC45005A4
	UINT32                                                  reserved337;	//0xC45005A8
	UINT32                                                  reserved338;	//0xC45005AC
	UINT32                                                  reserved339;	//0xC45005B0
	UINT32                                                  reserved340;	//0xC45005B4
	UINT32                                                  reserved341;	//0xC45005B8
	UINT32                                                  reserved342;	//0xC45005BC
	UINT32                                                  reserved343;	//0xC45005C0
	UINT32                                                  reserved344;	//0xC45005C4
	UINT32                                                  reserved345;	//0xC45005C8
	UINT32                                                  reserved346;	//0xC45005CC
	UINT32                                                  reserved347;	//0xC45005D0
	UINT32                                                  reserved348;	//0xC45005D4
	UINT32                                                  reserved349;	//0xC45005D8
	UINT32                                                  reserved350;	//0xC45005DC
	UINT32                                                  reserved351;	//0xC45005E0
	UINT32                                                  reserved352;	//0xC45005E4
	UINT32                                                  reserved353;	//0xC45005E8
	UINT32                                                  reserved354;	//0xC45005EC
	UINT32                                                  reserved355;	//0xC45005F0
	UINT32                                                  reserved356;	//0xC45005F4
	UINT32                                                  reserved357;	//0xC45005F8
	UINT32                                                  reserved358;	//0xC45005FC
	UINT32                                                  reserved359;	//0xC4500600
	UINT32                                                  reserved360;	//0xC4500604
	UINT32                                                  reserved361;	//0xC4500608
	UINT32                                                  reserved362;	//0xC450060C
	UINT32                                                  reserved363;	//0xC4500610
	UINT32                                                  reserved364;	//0xC4500614
	UINT32                                                  reserved365;	//0xC4500618
	UINT32                                                  reserved366;	//0xC450061C
	UINT32                                                  reserved367;	//0xC4500620
	UINT32                                                  reserved368;	//0xC4500624
	UINT32                                                  reserved369;	//0xC4500628
	UINT32                                                  reserved370;	//0xC450062C
	UINT32                                                  reserved371;	//0xC4500630
	UINT32                                                  reserved372;	//0xC4500634
	UINT32                                                  reserved373;	//0xC4500638
	UINT32                                                  reserved374;	//0xC450063C
	UINT32                                                  reserved375;	//0xC4500640
	UINT32                                                  reserved376;	//0xC4500644
	UINT32                                                  reserved377;	//0xC4500648
	UINT32                                                  reserved378;	//0xC450064C
	UINT32                                                  reserved379;	//0xC4500650
	UINT32                                                  reserved380;	//0xC4500654
	UINT32                                                  reserved381;	//0xC4500658
	UINT32                                                  reserved382;	//0xC450065C
	UINT32                                                  reserved383;	//0xC4500660
	UINT32                                                  reserved384;	//0xC4500664
	UINT32                                                  reserved385;	//0xC4500668
	UINT32                                                  reserved386;	//0xC450066C
	UINT32                                                  reserved387;	//0xC4500670
	UINT32                                                  reserved388;	//0xC4500674
	UINT32                                                  reserved389;	//0xC4500678
	UINT32                                                  reserved390;	//0xC450067C
	UINT32                                                  reserved391;	//0xC4500680
	UINT32                                                  reserved392;	//0xC4500684
	UINT32                                                  reserved393;	//0xC4500688
	UINT32                                                  reserved394;	//0xC450068C
	UINT32                                                  reserved395;	//0xC4500690
	UINT32                                                  reserved396;	//0xC4500694
	UINT32                                                  reserved397;	//0xC4500698
	UINT32                                                  reserved398;	//0xC450069C
	UINT32                                                  reserved399;	//0xC45006A0
	UINT32                                                  reserved400;	//0xC45006A4
	UINT32                                                  reserved401;	//0xC45006A8
	UINT32                                                  reserved402;	//0xC45006AC
	UINT32                                                  reserved403;	//0xC45006B0
	UINT32                                                  reserved404;	//0xC45006B4
	UINT32                                                  reserved405;	//0xC45006B8
	UINT32                                                  reserved406;	//0xC45006BC
	UINT32                                                  reserved407;	//0xC45006C0
	UINT32                                                  reserved408;	//0xC45006C4
	UINT32                                                  reserved409;	//0xC45006C8
	UINT32                                                  reserved410;	//0xC45006CC
	UINT32                                                  reserved411;	//0xC45006D0
	UINT32                                                  reserved412;	//0xC45006D4
	UINT32                                                  reserved413;	//0xC45006D8
	UINT32                                                  reserved414;	//0xC45006DC
	UINT32                                                  reserved415;	//0xC45006E0
	UINT32                                                  reserved416;	//0xC45006E4
	UINT32                                                  reserved417;	//0xC45006E8
	UINT32                                                  reserved418;	//0xC45006EC
	UINT32                                                  reserved419;	//0xC45006F0
	UINT32                                                  reserved420;	//0xC45006F4
	UINT32                                                  reserved421;	//0xC45006F8
	UINT32                                                  reserved422;	//0xC45006FC
	UINT32                                                  reserved423;	//0xC4500700
	UINT32                                                  reserved424;	//0xC4500704
	UINT32                                                  reserved425;	//0xC4500708
	UINT32                                                  reserved426;	//0xC450070C
	UINT32                                                  reserved427;	//0xC4500710
	UINT32                                                  reserved428;	//0xC4500714
	UINT32                                                  reserved429;	//0xC4500718
	UINT32                                                  reserved430;	//0xC450071C
	UINT32                                                  reserved431;	//0xC4500720
	UINT32                                                  reserved432;	//0xC4500724
	UINT32                                                  reserved433;	//0xC4500728
	UINT32                                                  reserved434;	//0xC450072C
	UINT32                                                  reserved435;	//0xC4500730
	UINT32                                                  reserved436;	//0xC4500734
	UINT32                                                  reserved437;	//0xC4500738
	UINT32                                                  reserved438;	//0xC450073C
	UINT32                                                  reserved439;	//0xC4500740
	UINT32                                                  reserved440;	//0xC4500744
	UINT32                                                  reserved441;	//0xC4500748
	UINT32                                                  reserved442;	//0xC450074C
	UINT32                                                  reserved443;	//0xC4500750
	UINT32                                                  reserved444;	//0xC4500754
	UINT32                                                  reserved445;	//0xC4500758
	UINT32                                                  reserved446;	//0xC450075C
	UINT32                                                  reserved447;	//0xC4500760
	UINT32                                                  reserved448;	//0xC4500764
	UINT32                                                  reserved449;	//0xC4500768
	UINT32                                                  reserved450;	//0xC450076C
	UINT32                                                  reserved451;	//0xC4500770
	UINT32                                                  reserved452;	//0xC4500774
	UINT32                                                  reserved453;	//0xC4500778
	UINT32                                                  reserved454;	//0xC450077C
	UINT32                                                  reserved455;	//0xC4500780
	UINT32                                                  reserved456;	//0xC4500784
	UINT32                                                  reserved457;	//0xC4500788
	UINT32                                                  reserved458;	//0xC450078C
	UINT32                                                  reserved459;	//0xC4500790
	UINT32                                                  reserved460;	//0xC4500794
	UINT32                                                  reserved461;	//0xC4500798
	UINT32                                                  reserved462;	//0xC450079C
	UINT32                                                  reserved463;	//0xC45007A0
	UINT32                                                  reserved464;	//0xC45007A4
	UINT32                                                  reserved465;	//0xC45007A8
	UINT32                                                  reserved466;	//0xC45007AC
	UINT32                                                  reserved467;	//0xC45007B0
	UINT32                                                  reserved468;	//0xC45007B4
	UINT32                                                  reserved469;	//0xC45007B8
	UINT32                                                  reserved470;	//0xC45007BC
	UINT32                                                  reserved471;	//0xC45007C0
	UINT32                                                  reserved472;	//0xC45007C4
	UINT32                                                  reserved473;	//0xC45007C8
	UINT32                                                  reserved474;	//0xC45007CC
	UINT32                                                  reserved475;	//0xC45007D0
	UINT32                                                  reserved476;	//0xC45007D4
	UINT32                                                  reserved477;	//0xC45007D8
	UINT32                                                  reserved478;	//0xC45007DC
	UINT32                                                  reserved479;	//0xC45007E0
	UINT32                                                  reserved480;	//0xC45007E4
	UINT32                                                  reserved481;	//0xC45007E8
	UINT32                                                  reserved482;	//0xC45007EC
	UINT32                                                  reserved483;	//0xC45007F0
	UINT32                                                  reserved484;	//0xC45007F4
	UINT32                                                  reserved485;	//0xC45007F8
	UINT32                                                  reserved486;	//0xC45007FC
	UINT32                                                  reserved487;	//0xC4500800
	UINT32                                                  reserved488;	//0xC4500804
	UINT32                                                  reserved489;	//0xC4500808
	UINT32                                                  reserved490;	//0xC450080C
	UINT32                                                  reserved491;	//0xC4500810
	UINT32                                                  reserved492;	//0xC4500814
	UINT32                                                  reserved493;	//0xC4500818
	UINT32                                                  reserved494;	//0xC450081C
	UINT32                                                  reserved495;	//0xC4500820
	UINT32                                                  reserved496;	//0xC4500824
	UINT32                                                  reserved497;	//0xC4500828
	UINT32                                                  reserved498;	//0xC450082C
	UINT32                                                  reserved499;	//0xC4500830
	UINT32                                                  reserved500;	//0xC4500834
	UINT32                                                  reserved501;	//0xC4500838
	UINT32                                                  reserved502;	//0xC450083C
	UINT32                                                  reserved503;	//0xC4500840
	UINT32                                                  reserved504;	//0xC4500844
	UINT32                                                  reserved505;	//0xC4500848
	UINT32                                                  reserved506;	//0xC450084C
	UINT32                                                  reserved507;	//0xC4500850
	UINT32                                                  reserved508;	//0xC4500854
	UINT32                                                  reserved509;	//0xC4500858
	UINT32                                                  reserved510;	//0xC450085C
	UINT32                                                  reserved511;	//0xC4500860
	UINT32                                                  reserved512;	//0xC4500864
	UINT32                                                  reserved513;	//0xC4500868
	UINT32                                                  reserved514;	//0xC450086C
	UINT32                                                  reserved515;	//0xC4500870
	UINT32                                                  reserved516;	//0xC4500874
	UINT32                                                  reserved517;	//0xC4500878
	UINT32                                                  reserved518;	//0xC450087C
	UINT32                                                  reserved519;	//0xC4500880
	UINT32                                                  reserved520;	//0xC4500884
	UINT32                                                  reserved521;	//0xC4500888
	UINT32                                                  reserved522;	//0xC450088C
	UINT32                                                  reserved523;	//0xC4500890
	UINT32                                                  reserved524;	//0xC4500894
	UINT32                                                  reserved525;	//0xC4500898
	UINT32                                                  reserved526;	//0xC450089C
	UINT32                                                  reserved527;	//0xC45008A0
	UINT32                                                  reserved528;	//0xC45008A4
	UINT32                                                  reserved529;	//0xC45008A8
	UINT32                                                  reserved530;	//0xC45008AC
	UINT32                                                  reserved531;	//0xC45008B0
	UINT32                                                  reserved532;	//0xC45008B4
	UINT32                                                  reserved533;	//0xC45008B8
	UINT32                                                  reserved534;	//0xC45008BC
	UINT32                                                  reserved535;	//0xC45008C0
	UINT32                                                  reserved536;	//0xC45008C4
	UINT32                                                  reserved537;	//0xC45008C8
	UINT32                                                  reserved538;	//0xC45008CC
	UINT32                                                  reserved539;	//0xC45008D0
	UINT32                                                  reserved540;	//0xC45008D4
	UINT32                                                  reserved541;	//0xC45008D8
	UINT32                                                  reserved542;	//0xC45008DC
	UINT32                                                  reserved543;	//0xC45008E0
	UINT32                                                  reserved544;	//0xC45008E4
	UINT32                                                  reserved545;	//0xC45008E8
	UINT32                                                  reserved546;	//0xC45008EC
	UINT32                                                  reserved547;	//0xC45008F0
	UINT32                                                  reserved548;	//0xC45008F4
	UINT32                                                  reserved549;	//0xC45008F8
	UINT32                                                  reserved550;	//0xC45008FC
	UINT32                                                  reserved551;	//0xC4500900
	UINT32                                                  reserved552;	//0xC4500904
	UINT32                                                  reserved553;	//0xC4500908
	UINT32                                                  reserved554;	//0xC450090C
	UINT32                                                  reserved555;	//0xC4500910
	UINT32                                                  reserved556;	//0xC4500914
	UINT32                                                  reserved557;	//0xC4500918
	UINT32                                                  reserved558;	//0xC450091C
	UINT32                                                  reserved559;	//0xC4500920
	UINT32                                                  reserved560;	//0xC4500924
	UINT32                                                  reserved561;	//0xC4500928
	UINT32                                                  reserved562;	//0xC450092C
	UINT32                                                  reserved563;	//0xC4500930
	UINT32                                                  reserved564;	//0xC4500934
	UINT32                                                  reserved565;	//0xC4500938
	UINT32                                                  reserved566;	//0xC450093C
	UINT32                                                  reserved567;	//0xC4500940
	UINT32                                                  reserved568;	//0xC4500944
	UINT32                                                  reserved569;	//0xC4500948
	UINT32                                                  reserved570;	//0xC450094C
	UINT32                                                  reserved571;	//0xC4500950
	UINT32                                                  reserved572;	//0xC4500954
	UINT32                                                  reserved573;	//0xC4500958
	UINT32                                                  reserved574;	//0xC450095C
	UINT32                                                  reserved575;	//0xC4500960
	UINT32                                                  reserved576;	//0xC4500964
	UINT32                                                  reserved577;	//0xC4500968
	UINT32                                                  reserved578;	//0xC450096C
	UINT32                                                  reserved579;	//0xC4500970
	UINT32                                                  reserved580;	//0xC4500974
	UINT32                                                  reserved581;	//0xC4500978
	UINT32                                                  reserved582;	//0xC450097C
	UINT32                                                  reserved583;	//0xC4500980
	UINT32                                                  reserved584;	//0xC4500984
	UINT32                                                  reserved585;	//0xC4500988
	UINT32                                                  reserved586;	//0xC450098C
	UINT32                                                  reserved587;	//0xC4500990
	UINT32                                                  reserved588;	//0xC4500994
	UINT32                                                  reserved589;	//0xC4500998
	UINT32                                                  reserved590;	//0xC450099C
	UINT32                                                  reserved591;	//0xC45009A0
	UINT32                                                  reserved592;	//0xC45009A4
	UINT32                                                  reserved593;	//0xC45009A8
	UINT32                                                  reserved594;	//0xC45009AC
	UINT32                                                  reserved595;	//0xC45009B0
	UINT32                                                  reserved596;	//0xC45009B4
	UINT32                                                  reserved597;	//0xC45009B8
	UINT32                                                  reserved598;	//0xC45009BC
	UINT32                                                  reserved599;	//0xC45009C0
	UINT32                                                  reserved600;	//0xC45009C4
	UINT32                                                  reserved601;	//0xC45009C8
	UINT32                                                  reserved602;	//0xC45009CC
	UINT32                                                  reserved603;	//0xC45009D0
	UINT32                                                  reserved604;	//0xC45009D4
	UINT32                                                  reserved605;	//0xC45009D8
	UINT32                                                  reserved606;	//0xC45009DC
	UINT32                                                  reserved607;	//0xC45009E0
	UINT32                                                  reserved608;	//0xC45009E4
	UINT32                                                  reserved609;	//0xC45009E8
	UINT32                                                  reserved610;	//0xC45009EC
	UINT32                                                  reserved611;	//0xC45009F0
	UINT32                                                  reserved612;	//0xC45009F4
	UINT32                                                  reserved613;	//0xC45009F8
	UINT32                                                  reserved614;	//0xC45009FC
	UINT32                                                  reserved615;	//0xC4500A00
	UINT32                                                  reserved616;	//0xC4500A04
	UINT32                                                  reserved617;	//0xC4500A08
	UINT32                                                  reserved618;	//0xC4500A0C
	UINT32                                                  reserved619;	//0xC4500A10
	UINT32                                                  reserved620;	//0xC4500A14
	UINT32                                                  reserved621;	//0xC4500A18
	UINT32                                                  reserved622;	//0xC4500A1C
	UINT32                                                  reserved623;	//0xC4500A20
	UINT32                                                  reserved624;	//0xC4500A24
	UINT32                                                  reserved625;	//0xC4500A28
	UINT32                                                  reserved626;	//0xC4500A2C
	UINT32                                                  reserved627;	//0xC4500A30
	UINT32                                                  reserved628;	//0xC4500A34
	UINT32                                                  reserved629;	//0xC4500A38
	UINT32                                                  reserved630;	//0xC4500A3C
	UINT32                                                  reserved631;	//0xC4500A40
	UINT32                                                  reserved632;	//0xC4500A44
	UINT32                                                  reserved633;	//0xC4500A48
	UINT32                                                  reserved634;	//0xC4500A4C
	UINT32                                                  reserved635;	//0xC4500A50
	UINT32                                                  reserved636;	//0xC4500A54
	UINT32                                                  reserved637;	//0xC4500A58
	UINT32                                                  reserved638;	//0xC4500A5C
	UINT32                                                  reserved639;	//0xC4500A60
	UINT32                                                  reserved640;	//0xC4500A64
	UINT32                                                  reserved641;	//0xC4500A68
	UINT32                                                  reserved642;	//0xC4500A6C
	UINT32                                                  reserved643;	//0xC4500A70
	UINT32                                                  reserved644;	//0xC4500A74
	UINT32                                                  reserved645;	//0xC4500A78
	UINT32                                                  reserved646;	//0xC4500A7C
	UINT32                                                  reserved647;	//0xC4500A80
	UINT32                                                  reserved648;	//0xC4500A84
	UINT32                                                  reserved649;	//0xC4500A88
	UINT32                                                  reserved650;	//0xC4500A8C
	UINT32                                                  reserved651;	//0xC4500A90
	UINT32                                                  reserved652;	//0xC4500A94
	UINT32                                                  reserved653;	//0xC4500A98
	UINT32                                                  reserved654;	//0xC4500A9C
	UINT32                                                  reserved655;	//0xC4500AA0
	UINT32                                                  reserved656;	//0xC4500AA4
	UINT32                                                  reserved657;	//0xC4500AA8
	UINT32                                                  reserved658;	//0xC4500AAC
	UINT32                                                  reserved659;	//0xC4500AB0
	UINT32                                                  reserved660;	//0xC4500AB4
	UINT32                                                  reserved661;	//0xC4500AB8
	UINT32                                                  reserved662;	//0xC4500ABC
	UINT32                                                  reserved663;	//0xC4500AC0
	UINT32                                                  reserved664;	//0xC4500AC4
	UINT32                                                  reserved665;	//0xC4500AC8
	UINT32                                                  reserved666;	//0xC4500ACC
	UINT32                                                  reserved667;	//0xC4500AD0
	UINT32                                                  reserved668;	//0xC4500AD4
	UINT32                                                  reserved669;	//0xC4500AD8
	UINT32                                                  reserved670;	//0xC4500ADC
	UINT32                                                  reserved671;	//0xC4500AE0
	UINT32                                                  reserved672;	//0xC4500AE4
	UINT32                                                  reserved673;	//0xC4500AE8
	UINT32                                                  reserved674;	//0xC4500AEC
	UINT32                                                  reserved675;	//0xC4500AF0
	UINT32                                                  reserved676;	//0xC4500AF4
	UINT32                                                  reserved677;	//0xC4500AF8
	UINT32                                                  reserved678;	//0xC4500AFC
	UINT32                                                  reserved679;	//0xC4500B00
	UINT32                                                  reserved680;	//0xC4500B04
	UINT32                                                  reserved681;	//0xC4500B08
	UINT32                                                  reserved682;	//0xC4500B0C
	UINT32                                                  reserved683;	//0xC4500B10
	UINT32                                                  reserved684;	//0xC4500B14
	UINT32                                                  reserved685;	//0xC4500B18
	UINT32                                                  reserved686;	//0xC4500B1C
	UINT32                                                  reserved687;	//0xC4500B20
	UINT32                                                  reserved688;	//0xC4500B24
	UINT32                                                  reserved689;	//0xC4500B28
	UINT32                                                  reserved690;	//0xC4500B2C
	UINT32                                                  reserved691;	//0xC4500B30
	UINT32                                                  reserved692;	//0xC4500B34
	UINT32                                                  reserved693;	//0xC4500B38
	UINT32                                                  reserved694;	//0xC4500B3C
	UINT32                                                  reserved695;	//0xC4500B40
	UINT32                                                  reserved696;	//0xC4500B44
	UINT32                                                  reserved697;	//0xC4500B48
	UINT32                                                  reserved698;	//0xC4500B4C
	UINT32                                                  reserved699;	//0xC4500B50
	UINT32                                                  reserved700;	//0xC4500B54
	UINT32                                                  reserved701;	//0xC4500B58
	UINT32                                                  reserved702;	//0xC4500B5C
	UINT32                                                  reserved703;	//0xC4500B60
	UINT32                                                  reserved704;	//0xC4500B64
	UINT32                                                  reserved705;	//0xC4500B68
	UINT32                                                  reserved706;	//0xC4500B6C
	UINT32                                                  reserved707;	//0xC4500B70
	UINT32                                                  reserved708;	//0xC4500B74
	UINT32                                                  reserved709;	//0xC4500B78
	UINT32                                                  reserved710;	//0xC4500B7C
	UINT32                                                  reserved711;	//0xC4500B80
	UINT32                                                  reserved712;	//0xC4500B84
	UINT32                                                  reserved713;	//0xC4500B88
	UINT32                                                  reserved714;	//0xC4500B8C
	UINT32                                                  reserved715;	//0xC4500B90
	UINT32                                                  reserved716;	//0xC4500B94
	UINT32                                                  reserved717;	//0xC4500B98
	UINT32                                                  reserved718;	//0xC4500B9C
	UINT32                                                  reserved719;	//0xC4500BA0
	UINT32                                                  reserved720;	//0xC4500BA4
	UINT32                                                  reserved721;	//0xC4500BA8
	UINT32                                                  reserved722;	//0xC4500BAC
	UINT32                                                  reserved723;	//0xC4500BB0
	UINT32                                                  reserved724;	//0xC4500BB4
	UINT32                                                  reserved725;	//0xC4500BB8
	UINT32                                                  reserved726;	//0xC4500BBC
	UINT32                                                  reserved727;	//0xC4500BC0
	UINT32                                                  reserved728;	//0xC4500BC4
	UINT32                                                  reserved729;	//0xC4500BC8
	UINT32                                                  reserved730;	//0xC4500BCC
	UINT32                                                  reserved731;	//0xC4500BD0
	UINT32                                                  reserved732;	//0xC4500BD4
	UINT32                                                  reserved733;	//0xC4500BD8
	UINT32                                                  reserved734;	//0xC4500BDC
	UINT32                                                  reserved735;	//0xC4500BE0
	UINT32                                                  reserved736;	//0xC4500BE4
	UINT32                                                  reserved737;	//0xC4500BE8
	UINT32                                                  reserved738;	//0xC4500BEC
	UINT32                                                  reserved739;	//0xC4500BF0
	UINT32                                                  reserved740;	//0xC4500BF4
	UINT32                                                  reserved741;	//0xC4500BF8
	UINT32                                                  reserved742;	//0xC4500BFC
	UINT32                                                  reserved743;	//0xC4500C00
	UINT32                                                  reserved744;	//0xC4500C04
	UINT32                                                  reserved745;	//0xC4500C08
	UINT32                                                  reserved746;	//0xC4500C0C
	UINT32                                                  reserved747;	//0xC4500C10
	UINT32                                                  reserved748;	//0xC4500C14
	UINT32                                                  reserved749;	//0xC4500C18
	UINT32                                                  reserved750;	//0xC4500C1C
	UINT32                                                  reserved751;	//0xC4500C20
	UINT32                                                  reserved752;	//0xC4500C24
	UINT32                                                  reserved753;	//0xC4500C28
	UINT32                                                  reserved754;	//0xC4500C2C
	UINT32                                                  reserved755;	//0xC4500C30
	UINT32                                                  reserved756;	//0xC4500C34
	UINT32                                                  reserved757;	//0xC4500C38
	UINT32                                                  reserved758;	//0xC4500C3C
	UINT32                                                  reserved759;	//0xC4500C40
	UINT32                                                  reserved760;	//0xC4500C44
	UINT32                                                  reserved761;	//0xC4500C48
	UINT32                                                  reserved762;	//0xC4500C4C
	UINT32                                                  reserved763;	//0xC4500C50
	UINT32                                                  reserved764;	//0xC4500C54
	UINT32                                                  reserved765;	//0xC4500C58
	UINT32                                                  reserved766;	//0xC4500C5C
	UINT32                                                  reserved767;	//0xC4500C60
	UINT32                                                  reserved768;	//0xC4500C64
	UINT32                                                  reserved769;	//0xC4500C68
	UINT32                                                  reserved770;	//0xC4500C6C
	UINT32                                                  reserved771;	//0xC4500C70
	UINT32                                                  reserved772;	//0xC4500C74
	UINT32                                                  reserved773;	//0xC4500C78
	UINT32                                                  reserved774;	//0xC4500C7C
	UINT32                                                  reserved775;	//0xC4500C80
	UINT32                                                  reserved776;	//0xC4500C84
	UINT32                                                  reserved777;	//0xC4500C88
	UINT32                                                  reserved778;	//0xC4500C8C
	UINT32                                                  reserved779;	//0xC4500C90
	UINT32                                                  reserved780;	//0xC4500C94
	UINT32                                                  reserved781;	//0xC4500C98
	UINT32                                                  reserved782;	//0xC4500C9C
	UINT32                                                  reserved783;	//0xC4500CA0
	UINT32                                                  reserved784;	//0xC4500CA4
	UINT32                                                  reserved785;	//0xC4500CA8
	UINT32                                                  reserved786;	//0xC4500CAC
	UINT32                                                  reserved787;	//0xC4500CB0
	UINT32                                                  reserved788;	//0xC4500CB4
	UINT32                                                  reserved789;	//0xC4500CB8
	UINT32                                                  reserved790;	//0xC4500CBC
	UINT32                                                  reserved791;	//0xC4500CC0
	UINT32                                                  reserved792;	//0xC4500CC4
	UINT32                                                  reserved793;	//0xC4500CC8
	UINT32                                                  reserved794;	//0xC4500CCC
	UINT32                                                  reserved795;	//0xC4500CD0
	UINT32                                                  reserved796;	//0xC4500CD4
	UINT32                                                  reserved797;	//0xC4500CD8
	UINT32                                                  reserved798;	//0xC4500CDC
	UINT32                                                  reserved799;	//0xC4500CE0
	UINT32                                                  reserved800;	//0xC4500CE4
	UINT32                                                  reserved801;	//0xC4500CE8
	UINT32                                                  reserved802;	//0xC4500CEC
	UINT32                                                  reserved803;	//0xC4500CF0
	UINT32                                                  reserved804;	//0xC4500CF4
	UINT32                                                  reserved805;	//0xC4500CF8
	UINT32                                                  reserved806;	//0xC4500CFC
	UINT32                                                  reserved807;	//0xC4500D00
	UINT32                                                  reserved808;	//0xC4500D04
	UINT32                                                  reserved809;	//0xC4500D08
	UINT32                                                  reserved810;	//0xC4500D0C
	UINT32                                                  reserved811;	//0xC4500D10
	UINT32                                                  reserved812;	//0xC4500D14
	UINT32                                                  reserved813;	//0xC4500D18
	UINT32                                                  reserved814;	//0xC4500D1C
	UINT32                                                  reserved815;	//0xC4500D20
	UINT32                                                  reserved816;	//0xC4500D24
	UINT32                                                  reserved817;	//0xC4500D28
	UINT32                                                  reserved818;	//0xC4500D2C
	UINT32                                                  reserved819;	//0xC4500D30
	UINT32                                                  reserved820;	//0xC4500D34
	UINT32                                                  reserved821;	//0xC4500D38
	UINT32                                                  reserved822;	//0xC4500D3C
	UINT32                                                  reserved823;	//0xC4500D40
	UINT32                                                  reserved824;	//0xC4500D44
	UINT32                                                  reserved825;	//0xC4500D48
	UINT32                                                  reserved826;	//0xC4500D4C
	UINT32                                                  reserved827;	//0xC4500D50
	UINT32                                                  reserved828;	//0xC4500D54
	UINT32                                                  reserved829;	//0xC4500D58
	UINT32                                                  reserved830;	//0xC4500D5C
	UINT32                                                  reserved831;	//0xC4500D60
	UINT32                                                  reserved832;	//0xC4500D64
	UINT32                                                  reserved833;	//0xC4500D68
	UINT32                                                  reserved834;	//0xC4500D6C
	UINT32                                                  reserved835;	//0xC4500D70
	UINT32                                                  reserved836;	//0xC4500D74
	UINT32                                                  reserved837;	//0xC4500D78
	UINT32                                                  reserved838;	//0xC4500D7C
	UINT32                                                  reserved839;	//0xC4500D80
	UINT32                                                  reserved840;	//0xC4500D84
	UINT32                                                  reserved841;	//0xC4500D88
	UINT32                                                  reserved842;	//0xC4500D8C
	UINT32                                                  reserved843;	//0xC4500D90
	UINT32                                                  reserved844;	//0xC4500D94
	UINT32                                                  reserved845;	//0xC4500D98
	UINT32                                                  reserved846;	//0xC4500D9C
	UINT32                                                  reserved847;	//0xC4500DA0
	UINT32                                                  reserved848;	//0xC4500DA4
	UINT32                                                  reserved849;	//0xC4500DA8
	UINT32                                                  reserved850;	//0xC4500DAC
	UINT32                                                  reserved851;	//0xC4500DB0
	UINT32                                                  reserved852;	//0xC4500DB4
	UINT32                                                  reserved853;	//0xC4500DB8
	UINT32                                                  reserved854;	//0xC4500DBC
	UINT32                                                  reserved855;	//0xC4500DC0
	UINT32                                                  reserved856;	//0xC4500DC4
	UINT32                                                  reserved857;	//0xC4500DC8
	UINT32                                                  reserved858;	//0xC4500DCC
	UINT32                                                  reserved859;	//0xC4500DD0
	UINT32                                                  reserved860;	//0xC4500DD4
	UINT32                                                  reserved861;	//0xC4500DD8
	UINT32                                                  reserved862;	//0xC4500DDC
	UINT32                                                  reserved863;	//0xC4500DE0
	UINT32                                                  reserved864;	//0xC4500DE4
	UINT32                                                  reserved865;	//0xC4500DE8
	UINT32                                                  reserved866;	//0xC4500DEC
	UINT32                                                  reserved867;	//0xC4500DF0
	UINT32                                                  reserved868;	//0xC4500DF4
	UINT32                                                  reserved869;	//0xC4500DF8
	UINT32                                                  reserved870;	//0xC4500DFC
	UINT32                                                  reserved871;	//0xC4500E00
	UINT32                                                  reserved872;	//0xC4500E04
	UINT32                                                  reserved873;	//0xC4500E08
	UINT32                                                  reserved874;	//0xC4500E0C
	UINT32                                                  reserved875;	//0xC4500E10
	UINT32                                                  reserved876;	//0xC4500E14
	UINT32                                                  reserved877;	//0xC4500E18
	UINT32                                                  reserved878;	//0xC4500E1C
	UINT32                                                  reserved879;	//0xC4500E20
	UINT32                                                  reserved880;	//0xC4500E24
	UINT32                                                  reserved881;	//0xC4500E28
	UINT32                                                  reserved882;	//0xC4500E2C
	UINT32                                                  reserved883;	//0xC4500E30
	UINT32                                                  reserved884;	//0xC4500E34
	UINT32                                                  reserved885;	//0xC4500E38
	UINT32                                                  reserved886;	//0xC4500E3C
	UINT32                                                  reserved887;	//0xC4500E40
	UINT32                                                  reserved888;	//0xC4500E44
	UINT32                                                  reserved889;	//0xC4500E48
	UINT32                                                  reserved890;	//0xC4500E4C
	UINT32                                                  reserved891;	//0xC4500E50
	UINT32                                                  reserved892;	//0xC4500E54
	UINT32                                                  reserved893;	//0xC4500E58
	UINT32                                                  reserved894;	//0xC4500E5C
	UINT32                                                  reserved895;	//0xC4500E60
	UINT32                                                  reserved896;	//0xC4500E64
	UINT32                                                  reserved897;	//0xC4500E68
	UINT32                                                  reserved898;	//0xC4500E6C
	UINT32                                                  reserved899;	//0xC4500E70
	UINT32                                                  reserved900;	//0xC4500E74
	UINT32                                                  reserved901;	//0xC4500E78
	UINT32                                                  reserved902;	//0xC4500E7C
	UINT32                                                  reserved903;	//0xC4500E80
	UINT32                                                  reserved904;	//0xC4500E84
	UINT32                                                  reserved905;	//0xC4500E88
	UINT32                                                  reserved906;	//0xC4500E8C
	UINT32                                                  reserved907;	//0xC4500E90
	UINT32                                                  reserved908;	//0xC4500E94
	UINT32                                                  reserved909;	//0xC4500E98
	UINT32                                                  reserved910;	//0xC4500E9C
	UINT32                                                  reserved911;	//0xC4500EA0
	UINT32                                                  reserved912;	//0xC4500EA4
	UINT32                                                  reserved913;	//0xC4500EA8
	UINT32                                                  reserved914;	//0xC4500EAC
	UINT32                                                  reserved915;	//0xC4500EB0
	UINT32                                                  reserved916;	//0xC4500EB4
	UINT32                                                  reserved917;	//0xC4500EB8
	UINT32                                                  reserved918;	//0xC4500EBC
	UINT32                                                  reserved919;	//0xC4500EC0
	UINT32                                                  reserved920;	//0xC4500EC4
	UINT32                                                  reserved921;	//0xC4500EC8
	UINT32                                                  reserved922;	//0xC4500ECC
	UINT32                                                  reserved923;	//0xC4500ED0
	UINT32                                                  reserved924;	//0xC4500ED4
	UINT32                                                  reserved925;	//0xC4500ED8
	UINT32                                                  reserved926;	//0xC4500EDC
	UINT32                                                  reserved927;	//0xC4500EE0
	UINT32                                                  reserved928;	//0xC4500EE4
	UINT32                                                  reserved929;	//0xC4500EE8
	UINT32                                                  reserved930;	//0xC4500EEC
	UINT32                                                  reserved931;	//0xC4500EF0
	UINT32                                                  reserved932;	//0xC4500EF4
	UINT32                                                  reserved933;	//0xC4500EF8
	UINT32                                                  reserved934;	//0xC4500EFC
	UINT32                                                  reserved935;	//0xC4500F00
	UINT32                                                  reserved936;	//0xC4500F04
	UINT32                                                  reserved937;	//0xC4500F08
	UINT32                                                  reserved938;	//0xC4500F0C
	UINT32                                                  reserved939;	//0xC4500F10
	UINT32                                                  reserved940;	//0xC4500F14
	UINT32                                                  reserved941;	//0xC4500F18
	UINT32                                                  reserved942;	//0xC4500F1C
	UINT32                                                  reserved943;	//0xC4500F20
	UINT32                                                  reserved944;	//0xC4500F24
	UINT32                                                  reserved945;	//0xC4500F28
	UINT32                                                  reserved946;	//0xC4500F2C
	UINT32                                                  reserved947;	//0xC4500F30
	UINT32                                                  reserved948;	//0xC4500F34
	UINT32                                                  reserved949;	//0xC4500F38
	UINT32                                                  reserved950;	//0xC4500F3C
	UINT32                                                  reserved951;	//0xC4500F40
	UINT32                                                  reserved952;	//0xC4500F44
	UINT32                                                  reserved953;	//0xC4500F48
	UINT32                                                  reserved954;	//0xC4500F4C
	UINT32                                                  reserved955;	//0xC4500F50
	UINT32                                                  reserved956;	//0xC4500F54
	UINT32                                                  reserved957;	//0xC4500F58
	UINT32                                                  reserved958;	//0xC4500F5C
	UINT32                                                  reserved959;	//0xC4500F60
	UINT32                                                  reserved960;	//0xC4500F64
	UINT32                                                  reserved961;	//0xC4500F68
	UINT32                                                  reserved962;	//0xC4500F6C
	UINT32                                                  reserved963;	//0xC4500F70
	UINT32                                                  reserved964;	//0xC4500F74
	UINT32                                                  reserved965;	//0xC4500F78
	UINT32                                                  reserved966;	//0xC4500F7C
	UINT32                                                  reserved967;	//0xC4500F80
	UINT32                                                  reserved968;	//0xC4500F84
	UINT32                                                  reserved969;	//0xC4500F88
	UINT32                                                  reserved970;	//0xC4500F8C
	UINT32                                                  reserved971;	//0xC4500F90
	UINT32                                                  reserved972;	//0xC4500F94
	UINT32                                                  reserved973;	//0xC4500F98
	UINT32                                                  reserved974;	//0xC4500F9C
	UINT32                                                  reserved975;	//0xC4500FA0
	UINT32                                                  reserved976;	//0xC4500FA4
	UINT32                                                  reserved977;	//0xC4500FA8
	UINT32                                                  reserved978;	//0xC4500FAC
	UINT32                                                  reserved979;	//0xC4500FB0
	UINT32                                                  reserved980;	//0xC4500FB4
	UINT32                                                  reserved981;	//0xC4500FB8
	UINT32                                                  reserved982;	//0xC4500FBC
	UINT32                                                  reserved983;	//0xC4500FC0
	UINT32                                                  reserved984;	//0xC4500FC4
	UINT32                                                  reserved985;	//0xC4500FC8
	UINT32                                                  reserved986;	//0xC4500FCC
	UINT32                                                  reserved987;	//0xC4500FD0
	UINT32                                                  reserved988;	//0xC4500FD4
	UINT32                                                  reserved989;	//0xC4500FD8
	UINT32                                                  reserved990;	//0xC4500FDC
	UINT32                                                  reserved991;	//0xC4500FE0
	UINT32                                                  reserved992;	//0xC4500FE4
	UINT32                                                  reserved993;	//0xC4500FE8
	UINT32                                                  reserved994;	//0xC4500FEC
	UINT32                                                  reserved995;	//0xC4500FF0
	UINT32                                                  reserved996;	//0xC4500FF4
	UINT32                                                  reserved997;	//0xC4500FF8
	UINT32                                                  reserved998;	//0xC4500FFC
	REG_DDRC_M2_FIFO_RDY_T                                     fifo_rdy;	//0xC4501000
	REG_DDRC_M2_FIFO_STATUS_T                               fifo_status;	//0xC4501004
	REG_DDRC_M2_FIFO_CONF_T                                   fifo_conf;	//0xC4501008
	UINT32                                                  reserved999;	//0xC450100C
	REG_DDRC_M2_LIMITER_EN_T                                 limiter_en;	//0xC4501010
	REG_DDRC_M2_LIMITER_AW_THR_T                         limiter_aw_thr;	//0xC4501014
	REG_DDRC_M2_LIMITER_W_THR_T                           limiter_w_thr;	//0xC4501018
	UINT32                                                 reserved1000;	//0xC450101C
	UINT32                                                 reserved1001;	//0xC4501020
	REG_DDRC_M2_LIMITER_AR_THR_T                         limiter_ar_thr;	//0xC4501024
	REG_DDRC_M2_LIMITER_R_THR_T                           limiter_r_thr;	//0xC4501028
	UINT32                                                 reserved1002;	//0xC450102C
	UINT32                                                 reserved1003;	//0xC4501030
	UINT32                                                 reserved1004;	//0xC4501034
	UINT32                                                 reserved1005;	//0xC4501038
	UINT32                                                 reserved1006;	//0xC450103C
	UINT32                                                 reserved1007;	//0xC4501040
	UINT32                                                 reserved1008;	//0xC4501044
	UINT32                                                 reserved1009;	//0xC4501048
	UINT32                                                 reserved1010;	//0xC450104C
	UINT32                                                 reserved1011;	//0xC4501050
	UINT32                                                 reserved1012;	//0xC4501054
	UINT32                                                 reserved1013;	//0xC4501058
	UINT32                                                 reserved1014;	//0xC450105C
	UINT32                                                 reserved1015;	//0xC4501060
	UINT32                                                 reserved1016;	//0xC4501064
	UINT32                                                 reserved1017;	//0xC4501068
	UINT32                                                 reserved1018;	//0xC450106C
	UINT32                                                 reserved1019;	//0xC4501070
	UINT32                                                 reserved1020;	//0xC4501074
	UINT32                                                 reserved1021;	//0xC4501078
	UINT32                                                 reserved1022;	//0xC450107C
	UINT32                                                 reserved1023;	//0xC4501080
	UINT32                                                 reserved1024;	//0xC4501084
	UINT32                                                 reserved1025;	//0xC4501088
	UINT32                                                 reserved1026;	//0xC450108C
	UINT32                                                 reserved1027;	//0xC4501090
	UINT32                                                 reserved1028;	//0xC4501094
	UINT32                                                 reserved1029;	//0xC4501098
	UINT32                                                 reserved1030;	//0xC450109C
	UINT32                                                 reserved1031;	//0xC45010A0
	UINT32                                                 reserved1032;	//0xC45010A4
	UINT32                                                 reserved1033;	//0xC45010A8
	UINT32                                                 reserved1034;	//0xC45010AC
	UINT32                                                 reserved1035;	//0xC45010B0
	UINT32                                                 reserved1036;	//0xC45010B4
	UINT32                                                 reserved1037;	//0xC45010B8
	UINT32                                                 reserved1038;	//0xC45010BC
	UINT32                                                 reserved1039;	//0xC45010C0
	UINT32                                                 reserved1040;	//0xC45010C4
	UINT32                                                 reserved1041;	//0xC45010C8
	UINT32                                                 reserved1042;	//0xC45010CC
	UINT32                                                 reserved1043;	//0xC45010D0
	UINT32                                                 reserved1044;	//0xC45010D4
	UINT32                                                 reserved1045;	//0xC45010D8
	UINT32                                                 reserved1046;	//0xC45010DC
	UINT32                                                 reserved1047;	//0xC45010E0
	UINT32                                                 reserved1048;	//0xC45010E4
	UINT32                                                 reserved1049;	//0xC45010E8
	UINT32                                                 reserved1050;	//0xC45010EC
	UINT32                                                 reserved1051;	//0xC45010F0
	UINT32                                                 reserved1052;	//0xC45010F4
	UINT32                                                 reserved1053;	//0xC45010F8
	UINT32                                                 reserved1054;	//0xC45010FC
	REG_DDRC_M2_FIFO_MUX_T                                     fifo_mux;	//0xC4501100
	REG_DDRC_M2_FIFO_MUX_MAX_T                             fifo_mux_max;	//0xC4501104
	REG_DDRC_M2_FIFO_MUX_WR_PRT_T                       fifo_mux_wr_prt;	//0xC4501108
	REG_DDRC_M2_FIFO_MUX_RD_PRT_T                       fifo_mux_rd_prt;	//0xC450110C
	REG_DDRC_M2_FIFO_MUX_PRT_MAX_T                     fifo_mux_prt_max;	//0xC4501110
	UINT32                                                 reserved1055;	//0xC4501114
	UINT32                                                 reserved1056;	//0xC4501118
	UINT32                                                 reserved1057;	//0xC450111C
	UINT32                                                 reserved1058;	//0xC4501120
	UINT32                                                 reserved1059;	//0xC4501124
	UINT32                                                 reserved1060;	//0xC4501128
	UINT32                                                 reserved1061;	//0xC450112C
	UINT32                                                 reserved1062;	//0xC4501130
	UINT32                                                 reserved1063;	//0xC4501134
	UINT32                                                 reserved1064;	//0xC4501138
	UINT32                                                 reserved1065;	//0xC450113C
	UINT32                                                 reserved1066;	//0xC4501140
	UINT32                                                 reserved1067;	//0xC4501144
	UINT32                                                 reserved1068;	//0xC4501148
	UINT32                                                 reserved1069;	//0xC450114C
	UINT32                                                 reserved1070;	//0xC4501150
	UINT32                                                 reserved1071;	//0xC4501154
	UINT32                                                 reserved1072;	//0xC4501158
	UINT32                                                 reserved1073;	//0xC450115C
	UINT32                                                 reserved1074;	//0xC4501160
	UINT32                                                 reserved1075;	//0xC4501164
	UINT32                                                 reserved1076;	//0xC4501168
	UINT32                                                 reserved1077;	//0xC450116C
	UINT32                                                 reserved1078;	//0xC4501170
	UINT32                                                 reserved1079;	//0xC4501174
	UINT32                                                 reserved1080;	//0xC4501178
	UINT32                                                 reserved1081;	//0xC450117C
	UINT32                                                 reserved1082;	//0xC4501180
	UINT32                                                 reserved1083;	//0xC4501184
	UINT32                                                 reserved1084;	//0xC4501188
	UINT32                                                 reserved1085;	//0xC450118C
	UINT32                                                 reserved1086;	//0xC4501190
	UINT32                                                 reserved1087;	//0xC4501194
	UINT32                                                 reserved1088;	//0xC4501198
	UINT32                                                 reserved1089;	//0xC450119C
	UINT32                                                 reserved1090;	//0xC45011A0
	UINT32                                                 reserved1091;	//0xC45011A4
	UINT32                                                 reserved1092;	//0xC45011A8
	UINT32                                                 reserved1093;	//0xC45011AC
	UINT32                                                 reserved1094;	//0xC45011B0
	UINT32                                                 reserved1095;	//0xC45011B4
	UINT32                                                 reserved1096;	//0xC45011B8
	UINT32                                                 reserved1097;	//0xC45011BC
	UINT32                                                 reserved1098;	//0xC45011C0
	UINT32                                                 reserved1099;	//0xC45011C4
	UINT32                                                 reserved1100;	//0xC45011C8
	UINT32                                                 reserved1101;	//0xC45011CC
	UINT32                                                 reserved1102;	//0xC45011D0
	UINT32                                                 reserved1103;	//0xC45011D4
	UINT32                                                 reserved1104;	//0xC45011D8
	UINT32                                                 reserved1105;	//0xC45011DC
	UINT32                                                 reserved1106;	//0xC45011E0
	UINT32                                                 reserved1107;	//0xC45011E4
	UINT32                                                 reserved1108;	//0xC45011E8
	UINT32                                                 reserved1109;	//0xC45011EC
	UINT32                                                 reserved1110;	//0xC45011F0
	UINT32                                                 reserved1111;	//0xC45011F4
	UINT32                                                 reserved1112;	//0xC45011F8
	UINT32                                                 reserved1113;	//0xC45011FC
	UINT32                                                 reserved1114;	//0xC4501200
	UINT32                                                 reserved1115;	//0xC4501204
	UINT32                                                 reserved1116;	//0xC4501208
	UINT32                                                 reserved1117;	//0xC450120C
	UINT32                                                 reserved1118;	//0xC4501210
	UINT32                                                 reserved1119;	//0xC4501214
	UINT32                                                 reserved1120;	//0xC4501218
	UINT32                                                 reserved1121;	//0xC450121C
	UINT32                                                 reserved1122;	//0xC4501220
	UINT32                                                 reserved1123;	//0xC4501224
	UINT32                                                 reserved1124;	//0xC4501228
	UINT32                                                 reserved1125;	//0xC450122C
	UINT32                                                 reserved1126;	//0xC4501230
	UINT32                                                 reserved1127;	//0xC4501234
	UINT32                                                 reserved1128;	//0xC4501238
	UINT32                                                 reserved1129;	//0xC450123C
	UINT32                                                 reserved1130;	//0xC4501240
	UINT32                                                 reserved1131;	//0xC4501244
	UINT32                                                 reserved1132;	//0xC4501248
	UINT32                                                 reserved1133;	//0xC450124C
	UINT32                                                 reserved1134;	//0xC4501250
	UINT32                                                 reserved1135;	//0xC4501254
	UINT32                                                 reserved1136;	//0xC4501258
	UINT32                                                 reserved1137;	//0xC450125C
	UINT32                                                 reserved1138;	//0xC4501260
	UINT32                                                 reserved1139;	//0xC4501264
	UINT32                                                 reserved1140;	//0xC4501268
	UINT32                                                 reserved1141;	//0xC450126C
	UINT32                                                 reserved1142;	//0xC4501270
	UINT32                                                 reserved1143;	//0xC4501274
	UINT32                                                 reserved1144;	//0xC4501278
	UINT32                                                 reserved1145;	//0xC450127C
	UINT32                                                 reserved1146;	//0xC4501280
	UINT32                                                 reserved1147;	//0xC4501284
	UINT32                                                 reserved1148;	//0xC4501288
	UINT32                                                 reserved1149;	//0xC450128C
	UINT32                                                 reserved1150;	//0xC4501290
	UINT32                                                 reserved1151;	//0xC4501294
	UINT32                                                 reserved1152;	//0xC4501298
	UINT32                                                 reserved1153;	//0xC450129C
	UINT32                                                 reserved1154;	//0xC45012A0
	UINT32                                                 reserved1155;	//0xC45012A4
	UINT32                                                 reserved1156;	//0xC45012A8
	UINT32                                                 reserved1157;	//0xC45012AC
	UINT32                                                 reserved1158;	//0xC45012B0
	UINT32                                                 reserved1159;	//0xC45012B4
	UINT32                                                 reserved1160;	//0xC45012B8
	UINT32                                                 reserved1161;	//0xC45012BC
	UINT32                                                 reserved1162;	//0xC45012C0
	UINT32                                                 reserved1163;	//0xC45012C4
	UINT32                                                 reserved1164;	//0xC45012C8
	UINT32                                                 reserved1165;	//0xC45012CC
	UINT32                                                 reserved1166;	//0xC45012D0
	UINT32                                                 reserved1167;	//0xC45012D4
	UINT32                                                 reserved1168;	//0xC45012D8
	UINT32                                                 reserved1169;	//0xC45012DC
	UINT32                                                 reserved1170;	//0xC45012E0
	UINT32                                                 reserved1171;	//0xC45012E4
	UINT32                                                 reserved1172;	//0xC45012E8
	UINT32                                                 reserved1173;	//0xC45012EC
	UINT32                                                 reserved1174;	//0xC45012F0
	UINT32                                                 reserved1175;	//0xC45012F4
	UINT32                                                 reserved1176;	//0xC45012F8
	UINT32                                                 reserved1177;	//0xC45012FC
	UINT32                                                 reserved1178;	//0xC4501300
	UINT32                                                 reserved1179;	//0xC4501304
	UINT32                                                 reserved1180;	//0xC4501308
	UINT32                                                 reserved1181;	//0xC450130C
	UINT32                                                 reserved1182;	//0xC4501310
	UINT32                                                 reserved1183;	//0xC4501314
	UINT32                                                 reserved1184;	//0xC4501318
	UINT32                                                 reserved1185;	//0xC450131C
	UINT32                                                 reserved1186;	//0xC4501320
	UINT32                                                 reserved1187;	//0xC4501324
	UINT32                                                 reserved1188;	//0xC4501328
	UINT32                                                 reserved1189;	//0xC450132C
	UINT32                                                 reserved1190;	//0xC4501330
	UINT32                                                 reserved1191;	//0xC4501334
	UINT32                                                 reserved1192;	//0xC4501338
	UINT32                                                 reserved1193;	//0xC450133C
	UINT32                                                 reserved1194;	//0xC4501340
	UINT32                                                 reserved1195;	//0xC4501344
	UINT32                                                 reserved1196;	//0xC4501348
	UINT32                                                 reserved1197;	//0xC450134C
	UINT32                                                 reserved1198;	//0xC4501350
	UINT32                                                 reserved1199;	//0xC4501354
	UINT32                                                 reserved1200;	//0xC4501358
	UINT32                                                 reserved1201;	//0xC450135C
	UINT32                                                 reserved1202;	//0xC4501360
	UINT32                                                 reserved1203;	//0xC4501364
	UINT32                                                 reserved1204;	//0xC4501368
	UINT32                                                 reserved1205;	//0xC450136C
	UINT32                                                 reserved1206;	//0xC4501370
	UINT32                                                 reserved1207;	//0xC4501374
	UINT32                                                 reserved1208;	//0xC4501378
	UINT32                                                 reserved1209;	//0xC450137C
	UINT32                                                 reserved1210;	//0xC4501380
	UINT32                                                 reserved1211;	//0xC4501384
	UINT32                                                 reserved1212;	//0xC4501388
	UINT32                                                 reserved1213;	//0xC450138C
	UINT32                                                 reserved1214;	//0xC4501390
	UINT32                                                 reserved1215;	//0xC4501394
	UINT32                                                 reserved1216;	//0xC4501398
	UINT32                                                 reserved1217;	//0xC450139C
	UINT32                                                 reserved1218;	//0xC45013A0
	UINT32                                                 reserved1219;	//0xC45013A4
	UINT32                                                 reserved1220;	//0xC45013A8
	UINT32                                                 reserved1221;	//0xC45013AC
	UINT32                                                 reserved1222;	//0xC45013B0
	UINT32                                                 reserved1223;	//0xC45013B4
	UINT32                                                 reserved1224;	//0xC45013B8
	UINT32                                                 reserved1225;	//0xC45013BC
	UINT32                                                 reserved1226;	//0xC45013C0
	UINT32                                                 reserved1227;	//0xC45013C4
	UINT32                                                 reserved1228;	//0xC45013C8
	UINT32                                                 reserved1229;	//0xC45013CC
	UINT32                                                 reserved1230;	//0xC45013D0
	UINT32                                                 reserved1231;	//0xC45013D4
	UINT32                                                 reserved1232;	//0xC45013D8
	UINT32                                                 reserved1233;	//0xC45013DC
	UINT32                                                 reserved1234;	//0xC45013E0
	UINT32                                                 reserved1235;	//0xC45013E4
	UINT32                                                 reserved1236;	//0xC45013E8
	UINT32                                                 reserved1237;	//0xC45013EC
	UINT32                                                 reserved1238;	//0xC45013F0
	UINT32                                                 reserved1239;	//0xC45013F4
	UINT32                                                 reserved1240;	//0xC45013F8
	UINT32                                                 reserved1241;	//0xC45013FC
	UINT32                                                 reserved1242;	//0xC4501400
	UINT32                                                 reserved1243;	//0xC4501404
	UINT32                                                 reserved1244;	//0xC4501408
	UINT32                                                 reserved1245;	//0xC450140C
	UINT32                                                 reserved1246;	//0xC4501410
	UINT32                                                 reserved1247;	//0xC4501414
	UINT32                                                 reserved1248;	//0xC4501418
	UINT32                                                 reserved1249;	//0xC450141C
	UINT32                                                 reserved1250;	//0xC4501420
	UINT32                                                 reserved1251;	//0xC4501424
	UINT32                                                 reserved1252;	//0xC4501428
	UINT32                                                 reserved1253;	//0xC450142C
	UINT32                                                 reserved1254;	//0xC4501430
	UINT32                                                 reserved1255;	//0xC4501434
	UINT32                                                 reserved1256;	//0xC4501438
	UINT32                                                 reserved1257;	//0xC450143C
	UINT32                                                 reserved1258;	//0xC4501440
	UINT32                                                 reserved1259;	//0xC4501444
	UINT32                                                 reserved1260;	//0xC4501448
	UINT32                                                 reserved1261;	//0xC450144C
	UINT32                                                 reserved1262;	//0xC4501450
	UINT32                                                 reserved1263;	//0xC4501454
	UINT32                                                 reserved1264;	//0xC4501458
	UINT32                                                 reserved1265;	//0xC450145C
	UINT32                                                 reserved1266;	//0xC4501460
	UINT32                                                 reserved1267;	//0xC4501464
	UINT32                                                 reserved1268;	//0xC4501468
	UINT32                                                 reserved1269;	//0xC450146C
	UINT32                                                 reserved1270;	//0xC4501470
	UINT32                                                 reserved1271;	//0xC4501474
	UINT32                                                 reserved1272;	//0xC4501478
	UINT32                                                 reserved1273;	//0xC450147C
	UINT32                                                 reserved1274;	//0xC4501480
	UINT32                                                 reserved1275;	//0xC4501484
	UINT32                                                 reserved1276;	//0xC4501488
	UINT32                                                 reserved1277;	//0xC450148C
	UINT32                                                 reserved1278;	//0xC4501490
	UINT32                                                 reserved1279;	//0xC4501494
	UINT32                                                 reserved1280;	//0xC4501498
	UINT32                                                 reserved1281;	//0xC450149C
	UINT32                                                 reserved1282;	//0xC45014A0
	UINT32                                                 reserved1283;	//0xC45014A4
	UINT32                                                 reserved1284;	//0xC45014A8
	UINT32                                                 reserved1285;	//0xC45014AC
	UINT32                                                 reserved1286;	//0xC45014B0
	UINT32                                                 reserved1287;	//0xC45014B4
	UINT32                                                 reserved1288;	//0xC45014B8
	UINT32                                                 reserved1289;	//0xC45014BC
	UINT32                                                 reserved1290;	//0xC45014C0
	UINT32                                                 reserved1291;	//0xC45014C4
	UINT32                                                 reserved1292;	//0xC45014C8
	UINT32                                                 reserved1293;	//0xC45014CC
	UINT32                                                 reserved1294;	//0xC45014D0
	UINT32                                                 reserved1295;	//0xC45014D4
	UINT32                                                 reserved1296;	//0xC45014D8
	UINT32                                                 reserved1297;	//0xC45014DC
	UINT32                                                 reserved1298;	//0xC45014E0
	UINT32                                                 reserved1299;	//0xC45014E4
	UINT32                                                 reserved1300;	//0xC45014E8
	UINT32                                                 reserved1301;	//0xC45014EC
	UINT32                                                 reserved1302;	//0xC45014F0
	UINT32                                                 reserved1303;	//0xC45014F4
	UINT32                                                 reserved1304;	//0xC45014F8
	UINT32                                                 reserved1305;	//0xC45014FC
	UINT32                                                 reserved1306;	//0xC4501500
	UINT32                                                 reserved1307;	//0xC4501504
	UINT32                                                 reserved1308;	//0xC4501508
	UINT32                                                 reserved1309;	//0xC450150C
	UINT32                                                 reserved1310;	//0xC4501510
	UINT32                                                 reserved1311;	//0xC4501514
	UINT32                                                 reserved1312;	//0xC4501518
	UINT32                                                 reserved1313;	//0xC450151C
	UINT32                                                 reserved1314;	//0xC4501520
	UINT32                                                 reserved1315;	//0xC4501524
	UINT32                                                 reserved1316;	//0xC4501528
	UINT32                                                 reserved1317;	//0xC450152C
	UINT32                                                 reserved1318;	//0xC4501530
	UINT32                                                 reserved1319;	//0xC4501534
	UINT32                                                 reserved1320;	//0xC4501538
	UINT32                                                 reserved1321;	//0xC450153C
	UINT32                                                 reserved1322;	//0xC4501540
	UINT32                                                 reserved1323;	//0xC4501544
	UINT32                                                 reserved1324;	//0xC4501548
	UINT32                                                 reserved1325;	//0xC450154C
	UINT32                                                 reserved1326;	//0xC4501550
	UINT32                                                 reserved1327;	//0xC4501554
	UINT32                                                 reserved1328;	//0xC4501558
	UINT32                                                 reserved1329;	//0xC450155C
	UINT32                                                 reserved1330;	//0xC4501560
	UINT32                                                 reserved1331;	//0xC4501564
	UINT32                                                 reserved1332;	//0xC4501568
	UINT32                                                 reserved1333;	//0xC450156C
	UINT32                                                 reserved1334;	//0xC4501570
	UINT32                                                 reserved1335;	//0xC4501574
	UINT32                                                 reserved1336;	//0xC4501578
	UINT32                                                 reserved1337;	//0xC450157C
	UINT32                                                 reserved1338;	//0xC4501580
	UINT32                                                 reserved1339;	//0xC4501584
	UINT32                                                 reserved1340;	//0xC4501588
	UINT32                                                 reserved1341;	//0xC450158C
	UINT32                                                 reserved1342;	//0xC4501590
	UINT32                                                 reserved1343;	//0xC4501594
	UINT32                                                 reserved1344;	//0xC4501598
	UINT32                                                 reserved1345;	//0xC450159C
	UINT32                                                 reserved1346;	//0xC45015A0
	UINT32                                                 reserved1347;	//0xC45015A4
	UINT32                                                 reserved1348;	//0xC45015A8
	UINT32                                                 reserved1349;	//0xC45015AC
	UINT32                                                 reserved1350;	//0xC45015B0
	UINT32                                                 reserved1351;	//0xC45015B4
	UINT32                                                 reserved1352;	//0xC45015B8
	UINT32                                                 reserved1353;	//0xC45015BC
	UINT32                                                 reserved1354;	//0xC45015C0
	UINT32                                                 reserved1355;	//0xC45015C4
	UINT32                                                 reserved1356;	//0xC45015C8
	UINT32                                                 reserved1357;	//0xC45015CC
	UINT32                                                 reserved1358;	//0xC45015D0
	UINT32                                                 reserved1359;	//0xC45015D4
	UINT32                                                 reserved1360;	//0xC45015D8
	UINT32                                                 reserved1361;	//0xC45015DC
	UINT32                                                 reserved1362;	//0xC45015E0
	UINT32                                                 reserved1363;	//0xC45015E4
	UINT32                                                 reserved1364;	//0xC45015E8
	UINT32                                                 reserved1365;	//0xC45015EC
	UINT32                                                 reserved1366;	//0xC45015F0
	UINT32                                                 reserved1367;	//0xC45015F4
	UINT32                                                 reserved1368;	//0xC45015F8
	UINT32                                                 reserved1369;	//0xC45015FC
	UINT32                                                 reserved1370;	//0xC4501600
	UINT32                                                 reserved1371;	//0xC4501604
	UINT32                                                 reserved1372;	//0xC4501608
	UINT32                                                 reserved1373;	//0xC450160C
	UINT32                                                 reserved1374;	//0xC4501610
	UINT32                                                 reserved1375;	//0xC4501614
	UINT32                                                 reserved1376;	//0xC4501618
	UINT32                                                 reserved1377;	//0xC450161C
	UINT32                                                 reserved1378;	//0xC4501620
	UINT32                                                 reserved1379;	//0xC4501624
	UINT32                                                 reserved1380;	//0xC4501628
	UINT32                                                 reserved1381;	//0xC450162C
	UINT32                                                 reserved1382;	//0xC4501630
	UINT32                                                 reserved1383;	//0xC4501634
	UINT32                                                 reserved1384;	//0xC4501638
	UINT32                                                 reserved1385;	//0xC450163C
	UINT32                                                 reserved1386;	//0xC4501640
	UINT32                                                 reserved1387;	//0xC4501644
	UINT32                                                 reserved1388;	//0xC4501648
	UINT32                                                 reserved1389;	//0xC450164C
	UINT32                                                 reserved1390;	//0xC4501650
	UINT32                                                 reserved1391;	//0xC4501654
	UINT32                                                 reserved1392;	//0xC4501658
	UINT32                                                 reserved1393;	//0xC450165C
	UINT32                                                 reserved1394;	//0xC4501660
	UINT32                                                 reserved1395;	//0xC4501664
	UINT32                                                 reserved1396;	//0xC4501668
	UINT32                                                 reserved1397;	//0xC450166C
	UINT32                                                 reserved1398;	//0xC4501670
	UINT32                                                 reserved1399;	//0xC4501674
	UINT32                                                 reserved1400;	//0xC4501678
	UINT32                                                 reserved1401;	//0xC450167C
	UINT32                                                 reserved1402;	//0xC4501680
	UINT32                                                 reserved1403;	//0xC4501684
	UINT32                                                 reserved1404;	//0xC4501688
	UINT32                                                 reserved1405;	//0xC450168C
	UINT32                                                 reserved1406;	//0xC4501690
	UINT32                                                 reserved1407;	//0xC4501694
	UINT32                                                 reserved1408;	//0xC4501698
	UINT32                                                 reserved1409;	//0xC450169C
	UINT32                                                 reserved1410;	//0xC45016A0
	UINT32                                                 reserved1411;	//0xC45016A4
	UINT32                                                 reserved1412;	//0xC45016A8
	UINT32                                                 reserved1413;	//0xC45016AC
	UINT32                                                 reserved1414;	//0xC45016B0
	UINT32                                                 reserved1415;	//0xC45016B4
	UINT32                                                 reserved1416;	//0xC45016B8
	UINT32                                                 reserved1417;	//0xC45016BC
	UINT32                                                 reserved1418;	//0xC45016C0
	UINT32                                                 reserved1419;	//0xC45016C4
	UINT32                                                 reserved1420;	//0xC45016C8
	UINT32                                                 reserved1421;	//0xC45016CC
	UINT32                                                 reserved1422;	//0xC45016D0
	UINT32                                                 reserved1423;	//0xC45016D4
	UINT32                                                 reserved1424;	//0xC45016D8
	UINT32                                                 reserved1425;	//0xC45016DC
	UINT32                                                 reserved1426;	//0xC45016E0
	UINT32                                                 reserved1427;	//0xC45016E4
	UINT32                                                 reserved1428;	//0xC45016E8
	UINT32                                                 reserved1429;	//0xC45016EC
	UINT32                                                 reserved1430;	//0xC45016F0
	UINT32                                                 reserved1431;	//0xC45016F4
	UINT32                                                 reserved1432;	//0xC45016F8
	UINT32                                                 reserved1433;	//0xC45016FC
	UINT32                                                 reserved1434;	//0xC4501700
	UINT32                                                 reserved1435;	//0xC4501704
	UINT32                                                 reserved1436;	//0xC4501708
	UINT32                                                 reserved1437;	//0xC450170C
	UINT32                                                 reserved1438;	//0xC4501710
	UINT32                                                 reserved1439;	//0xC4501714
	UINT32                                                 reserved1440;	//0xC4501718
	UINT32                                                 reserved1441;	//0xC450171C
	UINT32                                                 reserved1442;	//0xC4501720
	UINT32                                                 reserved1443;	//0xC4501724
	UINT32                                                 reserved1444;	//0xC4501728
	UINT32                                                 reserved1445;	//0xC450172C
	UINT32                                                 reserved1446;	//0xC4501730
	UINT32                                                 reserved1447;	//0xC4501734
	UINT32                                                 reserved1448;	//0xC4501738
	UINT32                                                 reserved1449;	//0xC450173C
	UINT32                                                 reserved1450;	//0xC4501740
	UINT32                                                 reserved1451;	//0xC4501744
	UINT32                                                 reserved1452;	//0xC4501748
	UINT32                                                 reserved1453;	//0xC450174C
	UINT32                                                 reserved1454;	//0xC4501750
	UINT32                                                 reserved1455;	//0xC4501754
	UINT32                                                 reserved1456;	//0xC4501758
	UINT32                                                 reserved1457;	//0xC450175C
	UINT32                                                 reserved1458;	//0xC4501760
	UINT32                                                 reserved1459;	//0xC4501764
	UINT32                                                 reserved1460;	//0xC4501768
	UINT32                                                 reserved1461;	//0xC450176C
	UINT32                                                 reserved1462;	//0xC4501770
	UINT32                                                 reserved1463;	//0xC4501774
	UINT32                                                 reserved1464;	//0xC4501778
	UINT32                                                 reserved1465;	//0xC450177C
	UINT32                                                 reserved1466;	//0xC4501780
	UINT32                                                 reserved1467;	//0xC4501784
	UINT32                                                 reserved1468;	//0xC4501788
	UINT32                                                 reserved1469;	//0xC450178C
	UINT32                                                 reserved1470;	//0xC4501790
	UINT32                                                 reserved1471;	//0xC4501794
	UINT32                                                 reserved1472;	//0xC4501798
	UINT32                                                 reserved1473;	//0xC450179C
	UINT32                                                 reserved1474;	//0xC45017A0
	UINT32                                                 reserved1475;	//0xC45017A4
	UINT32                                                 reserved1476;	//0xC45017A8
	UINT32                                                 reserved1477;	//0xC45017AC
	UINT32                                                 reserved1478;	//0xC45017B0
	UINT32                                                 reserved1479;	//0xC45017B4
	UINT32                                                 reserved1480;	//0xC45017B8
	UINT32                                                 reserved1481;	//0xC45017BC
	UINT32                                                 reserved1482;	//0xC45017C0
	UINT32                                                 reserved1483;	//0xC45017C4
	UINT32                                                 reserved1484;	//0xC45017C8
	UINT32                                                 reserved1485;	//0xC45017CC
	UINT32                                                 reserved1486;	//0xC45017D0
	UINT32                                                 reserved1487;	//0xC45017D4
	UINT32                                                 reserved1488;	//0xC45017D8
	UINT32                                                 reserved1489;	//0xC45017DC
	UINT32                                                 reserved1490;	//0xC45017E0
	UINT32                                                 reserved1491;	//0xC45017E4
	UINT32                                                 reserved1492;	//0xC45017E8
	UINT32                                                 reserved1493;	//0xC45017EC
	UINT32                                                 reserved1494;	//0xC45017F0
	UINT32                                                 reserved1495;	//0xC45017F4
	UINT32                                                 reserved1496;	//0xC45017F8
	UINT32                                                 reserved1497;	//0xC45017FC
	UINT32                                                 reserved1498;	//0xC4501800
	UINT32                                                 reserved1499;	//0xC4501804
	UINT32                                                 reserved1500;	//0xC4501808
	UINT32                                                 reserved1501;	//0xC450180C
	UINT32                                                 reserved1502;	//0xC4501810
	UINT32                                                 reserved1503;	//0xC4501814
	UINT32                                                 reserved1504;	//0xC4501818
	UINT32                                                 reserved1505;	//0xC450181C
	UINT32                                                 reserved1506;	//0xC4501820
	UINT32                                                 reserved1507;	//0xC4501824
	UINT32                                                 reserved1508;	//0xC4501828
	UINT32                                                 reserved1509;	//0xC450182C
	UINT32                                                 reserved1510;	//0xC4501830
	UINT32                                                 reserved1511;	//0xC4501834
	UINT32                                                 reserved1512;	//0xC4501838
	UINT32                                                 reserved1513;	//0xC450183C
	UINT32                                                 reserved1514;	//0xC4501840
	UINT32                                                 reserved1515;	//0xC4501844
	UINT32                                                 reserved1516;	//0xC4501848
	UINT32                                                 reserved1517;	//0xC450184C
	UINT32                                                 reserved1518;	//0xC4501850
	UINT32                                                 reserved1519;	//0xC4501854
	UINT32                                                 reserved1520;	//0xC4501858
	UINT32                                                 reserved1521;	//0xC450185C
	UINT32                                                 reserved1522;	//0xC4501860
	UINT32                                                 reserved1523;	//0xC4501864
	UINT32                                                 reserved1524;	//0xC4501868
	UINT32                                                 reserved1525;	//0xC450186C
	UINT32                                                 reserved1526;	//0xC4501870
	UINT32                                                 reserved1527;	//0xC4501874
	UINT32                                                 reserved1528;	//0xC4501878
	UINT32                                                 reserved1529;	//0xC450187C
	UINT32                                                 reserved1530;	//0xC4501880
	UINT32                                                 reserved1531;	//0xC4501884
	UINT32                                                 reserved1532;	//0xC4501888
	UINT32                                                 reserved1533;	//0xC450188C
	UINT32                                                 reserved1534;	//0xC4501890
	UINT32                                                 reserved1535;	//0xC4501894
	UINT32                                                 reserved1536;	//0xC4501898
	UINT32                                                 reserved1537;	//0xC450189C
	UINT32                                                 reserved1538;	//0xC45018A0
	UINT32                                                 reserved1539;	//0xC45018A4
	UINT32                                                 reserved1540;	//0xC45018A8
	UINT32                                                 reserved1541;	//0xC45018AC
	UINT32                                                 reserved1542;	//0xC45018B0
	UINT32                                                 reserved1543;	//0xC45018B4
	UINT32                                                 reserved1544;	//0xC45018B8
	UINT32                                                 reserved1545;	//0xC45018BC
	UINT32                                                 reserved1546;	//0xC45018C0
	UINT32                                                 reserved1547;	//0xC45018C4
	UINT32                                                 reserved1548;	//0xC45018C8
	UINT32                                                 reserved1549;	//0xC45018CC
	UINT32                                                 reserved1550;	//0xC45018D0
	UINT32                                                 reserved1551;	//0xC45018D4
	UINT32                                                 reserved1552;	//0xC45018D8
	UINT32                                                 reserved1553;	//0xC45018DC
	UINT32                                                 reserved1554;	//0xC45018E0
	UINT32                                                 reserved1555;	//0xC45018E4
	UINT32                                                 reserved1556;	//0xC45018E8
	UINT32                                                 reserved1557;	//0xC45018EC
	UINT32                                                 reserved1558;	//0xC45018F0
	UINT32                                                 reserved1559;	//0xC45018F4
	UINT32                                                 reserved1560;	//0xC45018F8
	UINT32                                                 reserved1561;	//0xC45018FC
	UINT32                                                 reserved1562;	//0xC4501900
	UINT32                                                 reserved1563;	//0xC4501904
	UINT32                                                 reserved1564;	//0xC4501908
	UINT32                                                 reserved1565;	//0xC450190C
	UINT32                                                 reserved1566;	//0xC4501910
	UINT32                                                 reserved1567;	//0xC4501914
	UINT32                                                 reserved1568;	//0xC4501918
	UINT32                                                 reserved1569;	//0xC450191C
	UINT32                                                 reserved1570;	//0xC4501920
	UINT32                                                 reserved1571;	//0xC4501924
	UINT32                                                 reserved1572;	//0xC4501928
	UINT32                                                 reserved1573;	//0xC450192C
	UINT32                                                 reserved1574;	//0xC4501930
	UINT32                                                 reserved1575;	//0xC4501934
	UINT32                                                 reserved1576;	//0xC4501938
	UINT32                                                 reserved1577;	//0xC450193C
	UINT32                                                 reserved1578;	//0xC4501940
	UINT32                                                 reserved1579;	//0xC4501944
	UINT32                                                 reserved1580;	//0xC4501948
	UINT32                                                 reserved1581;	//0xC450194C
	UINT32                                                 reserved1582;	//0xC4501950
	UINT32                                                 reserved1583;	//0xC4501954
	UINT32                                                 reserved1584;	//0xC4501958
	UINT32                                                 reserved1585;	//0xC450195C
	UINT32                                                 reserved1586;	//0xC4501960
	UINT32                                                 reserved1587;	//0xC4501964
	UINT32                                                 reserved1588;	//0xC4501968
	UINT32                                                 reserved1589;	//0xC450196C
	UINT32                                                 reserved1590;	//0xC4501970
	UINT32                                                 reserved1591;	//0xC4501974
	UINT32                                                 reserved1592;	//0xC4501978
	UINT32                                                 reserved1593;	//0xC450197C
	UINT32                                                 reserved1594;	//0xC4501980
	UINT32                                                 reserved1595;	//0xC4501984
	UINT32                                                 reserved1596;	//0xC4501988
	UINT32                                                 reserved1597;	//0xC450198C
	UINT32                                                 reserved1598;	//0xC4501990
	UINT32                                                 reserved1599;	//0xC4501994
	UINT32                                                 reserved1600;	//0xC4501998
	UINT32                                                 reserved1601;	//0xC450199C
	UINT32                                                 reserved1602;	//0xC45019A0
	UINT32                                                 reserved1603;	//0xC45019A4
	UINT32                                                 reserved1604;	//0xC45019A8
	UINT32                                                 reserved1605;	//0xC45019AC
	UINT32                                                 reserved1606;	//0xC45019B0
	UINT32                                                 reserved1607;	//0xC45019B4
	UINT32                                                 reserved1608;	//0xC45019B8
	UINT32                                                 reserved1609;	//0xC45019BC
	UINT32                                                 reserved1610;	//0xC45019C0
	UINT32                                                 reserved1611;	//0xC45019C4
	UINT32                                                 reserved1612;	//0xC45019C8
	UINT32                                                 reserved1613;	//0xC45019CC
	UINT32                                                 reserved1614;	//0xC45019D0
	UINT32                                                 reserved1615;	//0xC45019D4
	UINT32                                                 reserved1616;	//0xC45019D8
	UINT32                                                 reserved1617;	//0xC45019DC
	UINT32                                                 reserved1618;	//0xC45019E0
	UINT32                                                 reserved1619;	//0xC45019E4
	UINT32                                                 reserved1620;	//0xC45019E8
	UINT32                                                 reserved1621;	//0xC45019EC
	UINT32                                                 reserved1622;	//0xC45019F0
	UINT32                                                 reserved1623;	//0xC45019F4
	UINT32                                                 reserved1624;	//0xC45019F8
	UINT32                                                 reserved1625;	//0xC45019FC
	UINT32                                                 reserved1626;	//0xC4501A00
	UINT32                                                 reserved1627;	//0xC4501A04
	UINT32                                                 reserved1628;	//0xC4501A08
	UINT32                                                 reserved1629;	//0xC4501A0C
	UINT32                                                 reserved1630;	//0xC4501A10
	UINT32                                                 reserved1631;	//0xC4501A14
	UINT32                                                 reserved1632;	//0xC4501A18
	UINT32                                                 reserved1633;	//0xC4501A1C
	UINT32                                                 reserved1634;	//0xC4501A20
	UINT32                                                 reserved1635;	//0xC4501A24
	UINT32                                                 reserved1636;	//0xC4501A28
	UINT32                                                 reserved1637;	//0xC4501A2C
	UINT32                                                 reserved1638;	//0xC4501A30
	UINT32                                                 reserved1639;	//0xC4501A34
	UINT32                                                 reserved1640;	//0xC4501A38
	UINT32                                                 reserved1641;	//0xC4501A3C
	UINT32                                                 reserved1642;	//0xC4501A40
	UINT32                                                 reserved1643;	//0xC4501A44
	UINT32                                                 reserved1644;	//0xC4501A48
	UINT32                                                 reserved1645;	//0xC4501A4C
	UINT32                                                 reserved1646;	//0xC4501A50
	UINT32                                                 reserved1647;	//0xC4501A54
	UINT32                                                 reserved1648;	//0xC4501A58
	UINT32                                                 reserved1649;	//0xC4501A5C
	UINT32                                                 reserved1650;	//0xC4501A60
	UINT32                                                 reserved1651;	//0xC4501A64
	UINT32                                                 reserved1652;	//0xC4501A68
	UINT32                                                 reserved1653;	//0xC4501A6C
	UINT32                                                 reserved1654;	//0xC4501A70
	UINT32                                                 reserved1655;	//0xC4501A74
	UINT32                                                 reserved1656;	//0xC4501A78
	UINT32                                                 reserved1657;	//0xC4501A7C
	UINT32                                                 reserved1658;	//0xC4501A80
	UINT32                                                 reserved1659;	//0xC4501A84
	UINT32                                                 reserved1660;	//0xC4501A88
	UINT32                                                 reserved1661;	//0xC4501A8C
	UINT32                                                 reserved1662;	//0xC4501A90
	UINT32                                                 reserved1663;	//0xC4501A94
	UINT32                                                 reserved1664;	//0xC4501A98
	UINT32                                                 reserved1665;	//0xC4501A9C
	UINT32                                                 reserved1666;	//0xC4501AA0
	UINT32                                                 reserved1667;	//0xC4501AA4
	UINT32                                                 reserved1668;	//0xC4501AA8
	UINT32                                                 reserved1669;	//0xC4501AAC
	UINT32                                                 reserved1670;	//0xC4501AB0
	UINT32                                                 reserved1671;	//0xC4501AB4
	UINT32                                                 reserved1672;	//0xC4501AB8
	UINT32                                                 reserved1673;	//0xC4501ABC
	UINT32                                                 reserved1674;	//0xC4501AC0
	UINT32                                                 reserved1675;	//0xC4501AC4
	UINT32                                                 reserved1676;	//0xC4501AC8
	UINT32                                                 reserved1677;	//0xC4501ACC
	UINT32                                                 reserved1678;	//0xC4501AD0
	UINT32                                                 reserved1679;	//0xC4501AD4
	UINT32                                                 reserved1680;	//0xC4501AD8
	UINT32                                                 reserved1681;	//0xC4501ADC
	UINT32                                                 reserved1682;	//0xC4501AE0
	UINT32                                                 reserved1683;	//0xC4501AE4
	UINT32                                                 reserved1684;	//0xC4501AE8
	UINT32                                                 reserved1685;	//0xC4501AEC
	UINT32                                                 reserved1686;	//0xC4501AF0
	UINT32                                                 reserved1687;	//0xC4501AF4
	UINT32                                                 reserved1688;	//0xC4501AF8
	UINT32                                                 reserved1689;	//0xC4501AFC
	UINT32                                                 reserved1690;	//0xC4501B00
	UINT32                                                 reserved1691;	//0xC4501B04
	UINT32                                                 reserved1692;	//0xC4501B08
	UINT32                                                 reserved1693;	//0xC4501B0C
	UINT32                                                 reserved1694;	//0xC4501B10
	UINT32                                                 reserved1695;	//0xC4501B14
	UINT32                                                 reserved1696;	//0xC4501B18
	UINT32                                                 reserved1697;	//0xC4501B1C
	UINT32                                                 reserved1698;	//0xC4501B20
	UINT32                                                 reserved1699;	//0xC4501B24
	UINT32                                                 reserved1700;	//0xC4501B28
	UINT32                                                 reserved1701;	//0xC4501B2C
	UINT32                                                 reserved1702;	//0xC4501B30
	UINT32                                                 reserved1703;	//0xC4501B34
	UINT32                                                 reserved1704;	//0xC4501B38
	UINT32                                                 reserved1705;	//0xC4501B3C
	UINT32                                                 reserved1706;	//0xC4501B40
	UINT32                                                 reserved1707;	//0xC4501B44
	UINT32                                                 reserved1708;	//0xC4501B48
	UINT32                                                 reserved1709;	//0xC4501B4C
	UINT32                                                 reserved1710;	//0xC4501B50
	UINT32                                                 reserved1711;	//0xC4501B54
	UINT32                                                 reserved1712;	//0xC4501B58
	UINT32                                                 reserved1713;	//0xC4501B5C
	UINT32                                                 reserved1714;	//0xC4501B60
	UINT32                                                 reserved1715;	//0xC4501B64
	UINT32                                                 reserved1716;	//0xC4501B68
	UINT32                                                 reserved1717;	//0xC4501B6C
	UINT32                                                 reserved1718;	//0xC4501B70
	UINT32                                                 reserved1719;	//0xC4501B74
	UINT32                                                 reserved1720;	//0xC4501B78
	UINT32                                                 reserved1721;	//0xC4501B7C
	UINT32                                                 reserved1722;	//0xC4501B80
	UINT32                                                 reserved1723;	//0xC4501B84
	UINT32                                                 reserved1724;	//0xC4501B88
	UINT32                                                 reserved1725;	//0xC4501B8C
	UINT32                                                 reserved1726;	//0xC4501B90
	UINT32                                                 reserved1727;	//0xC4501B94
	UINT32                                                 reserved1728;	//0xC4501B98
	UINT32                                                 reserved1729;	//0xC4501B9C
	UINT32                                                 reserved1730;	//0xC4501BA0
	UINT32                                                 reserved1731;	//0xC4501BA4
	UINT32                                                 reserved1732;	//0xC4501BA8
	UINT32                                                 reserved1733;	//0xC4501BAC
	UINT32                                                 reserved1734;	//0xC4501BB0
	UINT32                                                 reserved1735;	//0xC4501BB4
	UINT32                                                 reserved1736;	//0xC4501BB8
	UINT32                                                 reserved1737;	//0xC4501BBC
	UINT32                                                 reserved1738;	//0xC4501BC0
	UINT32                                                 reserved1739;	//0xC4501BC4
	UINT32                                                 reserved1740;	//0xC4501BC8
	UINT32                                                 reserved1741;	//0xC4501BCC
	UINT32                                                 reserved1742;	//0xC4501BD0
	UINT32                                                 reserved1743;	//0xC4501BD4
	UINT32                                                 reserved1744;	//0xC4501BD8
	UINT32                                                 reserved1745;	//0xC4501BDC
	UINT32                                                 reserved1746;	//0xC4501BE0
	UINT32                                                 reserved1747;	//0xC4501BE4
	UINT32                                                 reserved1748;	//0xC4501BE8
	UINT32                                                 reserved1749;	//0xC4501BEC
	UINT32                                                 reserved1750;	//0xC4501BF0
	UINT32                                                 reserved1751;	//0xC4501BF4
	UINT32                                                 reserved1752;	//0xC4501BF8
	UINT32                                                 reserved1753;	//0xC4501BFC
	UINT32                                                 reserved1754;	//0xC4501C00
	UINT32                                                 reserved1755;	//0xC4501C04
	UINT32                                                 reserved1756;	//0xC4501C08
	UINT32                                                 reserved1757;	//0xC4501C0C
	UINT32                                                 reserved1758;	//0xC4501C10
	UINT32                                                 reserved1759;	//0xC4501C14
	UINT32                                                 reserved1760;	//0xC4501C18
	UINT32                                                 reserved1761;	//0xC4501C1C
	UINT32                                                 reserved1762;	//0xC4501C20
	UINT32                                                 reserved1763;	//0xC4501C24
	UINT32                                                 reserved1764;	//0xC4501C28
	UINT32                                                 reserved1765;	//0xC4501C2C
	UINT32                                                 reserved1766;	//0xC4501C30
	UINT32                                                 reserved1767;	//0xC4501C34
	UINT32                                                 reserved1768;	//0xC4501C38
	UINT32                                                 reserved1769;	//0xC4501C3C
	UINT32                                                 reserved1770;	//0xC4501C40
	UINT32                                                 reserved1771;	//0xC4501C44
	UINT32                                                 reserved1772;	//0xC4501C48
	UINT32                                                 reserved1773;	//0xC4501C4C
	UINT32                                                 reserved1774;	//0xC4501C50
	UINT32                                                 reserved1775;	//0xC4501C54
	UINT32                                                 reserved1776;	//0xC4501C58
	UINT32                                                 reserved1777;	//0xC4501C5C
	UINT32                                                 reserved1778;	//0xC4501C60
	UINT32                                                 reserved1779;	//0xC4501C64
	UINT32                                                 reserved1780;	//0xC4501C68
	UINT32                                                 reserved1781;	//0xC4501C6C
	UINT32                                                 reserved1782;	//0xC4501C70
	UINT32                                                 reserved1783;	//0xC4501C74
	UINT32                                                 reserved1784;	//0xC4501C78
	UINT32                                                 reserved1785;	//0xC4501C7C
	UINT32                                                 reserved1786;	//0xC4501C80
	UINT32                                                 reserved1787;	//0xC4501C84
	UINT32                                                 reserved1788;	//0xC4501C88
	UINT32                                                 reserved1789;	//0xC4501C8C
	UINT32                                                 reserved1790;	//0xC4501C90
	UINT32                                                 reserved1791;	//0xC4501C94
	UINT32                                                 reserved1792;	//0xC4501C98
	UINT32                                                 reserved1793;	//0xC4501C9C
	UINT32                                                 reserved1794;	//0xC4501CA0
	UINT32                                                 reserved1795;	//0xC4501CA4
	UINT32                                                 reserved1796;	//0xC4501CA8
	UINT32                                                 reserved1797;	//0xC4501CAC
	UINT32                                                 reserved1798;	//0xC4501CB0
	UINT32                                                 reserved1799;	//0xC4501CB4
	UINT32                                                 reserved1800;	//0xC4501CB8
	UINT32                                                 reserved1801;	//0xC4501CBC
	UINT32                                                 reserved1802;	//0xC4501CC0
	UINT32                                                 reserved1803;	//0xC4501CC4
	UINT32                                                 reserved1804;	//0xC4501CC8
	UINT32                                                 reserved1805;	//0xC4501CCC
	UINT32                                                 reserved1806;	//0xC4501CD0
	UINT32                                                 reserved1807;	//0xC4501CD4
	UINT32                                                 reserved1808;	//0xC4501CD8
	UINT32                                                 reserved1809;	//0xC4501CDC
	UINT32                                                 reserved1810;	//0xC4501CE0
	UINT32                                                 reserved1811;	//0xC4501CE4
	UINT32                                                 reserved1812;	//0xC4501CE8
	UINT32                                                 reserved1813;	//0xC4501CEC
	UINT32                                                 reserved1814;	//0xC4501CF0
	UINT32                                                 reserved1815;	//0xC4501CF4
	UINT32                                                 reserved1816;	//0xC4501CF8
	UINT32                                                 reserved1817;	//0xC4501CFC
	UINT32                                                 reserved1818;	//0xC4501D00
	UINT32                                                 reserved1819;	//0xC4501D04
	UINT32                                                 reserved1820;	//0xC4501D08
	UINT32                                                 reserved1821;	//0xC4501D0C
	UINT32                                                 reserved1822;	//0xC4501D10
	UINT32                                                 reserved1823;	//0xC4501D14
	UINT32                                                 reserved1824;	//0xC4501D18
	UINT32                                                 reserved1825;	//0xC4501D1C
	UINT32                                                 reserved1826;	//0xC4501D20
	UINT32                                                 reserved1827;	//0xC4501D24
	UINT32                                                 reserved1828;	//0xC4501D28
	UINT32                                                 reserved1829;	//0xC4501D2C
	UINT32                                                 reserved1830;	//0xC4501D30
	UINT32                                                 reserved1831;	//0xC4501D34
	UINT32                                                 reserved1832;	//0xC4501D38
	UINT32                                                 reserved1833;	//0xC4501D3C
	UINT32                                                 reserved1834;	//0xC4501D40
	UINT32                                                 reserved1835;	//0xC4501D44
	UINT32                                                 reserved1836;	//0xC4501D48
	UINT32                                                 reserved1837;	//0xC4501D4C
	UINT32                                                 reserved1838;	//0xC4501D50
	UINT32                                                 reserved1839;	//0xC4501D54
	UINT32                                                 reserved1840;	//0xC4501D58
	UINT32                                                 reserved1841;	//0xC4501D5C
	UINT32                                                 reserved1842;	//0xC4501D60
	UINT32                                                 reserved1843;	//0xC4501D64
	UINT32                                                 reserved1844;	//0xC4501D68
	UINT32                                                 reserved1845;	//0xC4501D6C
	UINT32                                                 reserved1846;	//0xC4501D70
	UINT32                                                 reserved1847;	//0xC4501D74
	UINT32                                                 reserved1848;	//0xC4501D78
	UINT32                                                 reserved1849;	//0xC4501D7C
	UINT32                                                 reserved1850;	//0xC4501D80
	UINT32                                                 reserved1851;	//0xC4501D84
	UINT32                                                 reserved1852;	//0xC4501D88
	UINT32                                                 reserved1853;	//0xC4501D8C
	UINT32                                                 reserved1854;	//0xC4501D90
	UINT32                                                 reserved1855;	//0xC4501D94
	UINT32                                                 reserved1856;	//0xC4501D98
	UINT32                                                 reserved1857;	//0xC4501D9C
	UINT32                                                 reserved1858;	//0xC4501DA0
	UINT32                                                 reserved1859;	//0xC4501DA4
	UINT32                                                 reserved1860;	//0xC4501DA8
	UINT32                                                 reserved1861;	//0xC4501DAC
	UINT32                                                 reserved1862;	//0xC4501DB0
	UINT32                                                 reserved1863;	//0xC4501DB4
	UINT32                                                 reserved1864;	//0xC4501DB8
	UINT32                                                 reserved1865;	//0xC4501DBC
	UINT32                                                 reserved1866;	//0xC4501DC0
	UINT32                                                 reserved1867;	//0xC4501DC4
	UINT32                                                 reserved1868;	//0xC4501DC8
	UINT32                                                 reserved1869;	//0xC4501DCC
	UINT32                                                 reserved1870;	//0xC4501DD0
	UINT32                                                 reserved1871;	//0xC4501DD4
	UINT32                                                 reserved1872;	//0xC4501DD8
	UINT32                                                 reserved1873;	//0xC4501DDC
	UINT32                                                 reserved1874;	//0xC4501DE0
	UINT32                                                 reserved1875;	//0xC4501DE4
	UINT32                                                 reserved1876;	//0xC4501DE8
	UINT32                                                 reserved1877;	//0xC4501DEC
	UINT32                                                 reserved1878;	//0xC4501DF0
	UINT32                                                 reserved1879;	//0xC4501DF4
	UINT32                                                 reserved1880;	//0xC4501DF8
	UINT32                                                 reserved1881;	//0xC4501DFC
	UINT32                                                 reserved1882;	//0xC4501E00
	UINT32                                                 reserved1883;	//0xC4501E04
	UINT32                                                 reserved1884;	//0xC4501E08
	UINT32                                                 reserved1885;	//0xC4501E0C
	UINT32                                                 reserved1886;	//0xC4501E10
	UINT32                                                 reserved1887;	//0xC4501E14
	UINT32                                                 reserved1888;	//0xC4501E18
	UINT32                                                 reserved1889;	//0xC4501E1C
	UINT32                                                 reserved1890;	//0xC4501E20
	UINT32                                                 reserved1891;	//0xC4501E24
	UINT32                                                 reserved1892;	//0xC4501E28
	UINT32                                                 reserved1893;	//0xC4501E2C
	UINT32                                                 reserved1894;	//0xC4501E30
	UINT32                                                 reserved1895;	//0xC4501E34
	UINT32                                                 reserved1896;	//0xC4501E38
	UINT32                                                 reserved1897;	//0xC4501E3C
	UINT32                                                 reserved1898;	//0xC4501E40
	UINT32                                                 reserved1899;	//0xC4501E44
	UINT32                                                 reserved1900;	//0xC4501E48
	UINT32                                                 reserved1901;	//0xC4501E4C
	UINT32                                                 reserved1902;	//0xC4501E50
	UINT32                                                 reserved1903;	//0xC4501E54
	UINT32                                                 reserved1904;	//0xC4501E58
	UINT32                                                 reserved1905;	//0xC4501E5C
	UINT32                                                 reserved1906;	//0xC4501E60
	UINT32                                                 reserved1907;	//0xC4501E64
	UINT32                                                 reserved1908;	//0xC4501E68
	UINT32                                                 reserved1909;	//0xC4501E6C
	UINT32                                                 reserved1910;	//0xC4501E70
	UINT32                                                 reserved1911;	//0xC4501E74
	UINT32                                                 reserved1912;	//0xC4501E78
	UINT32                                                 reserved1913;	//0xC4501E7C
	UINT32                                                 reserved1914;	//0xC4501E80
	UINT32                                                 reserved1915;	//0xC4501E84
	UINT32                                                 reserved1916;	//0xC4501E88
	UINT32                                                 reserved1917;	//0xC4501E8C
	UINT32                                                 reserved1918;	//0xC4501E90
	UINT32                                                 reserved1919;	//0xC4501E94
	UINT32                                                 reserved1920;	//0xC4501E98
	UINT32                                                 reserved1921;	//0xC4501E9C
	UINT32                                                 reserved1922;	//0xC4501EA0
	UINT32                                                 reserved1923;	//0xC4501EA4
	UINT32                                                 reserved1924;	//0xC4501EA8
	UINT32                                                 reserved1925;	//0xC4501EAC
	UINT32                                                 reserved1926;	//0xC4501EB0
	UINT32                                                 reserved1927;	//0xC4501EB4
	UINT32                                                 reserved1928;	//0xC4501EB8
	UINT32                                                 reserved1929;	//0xC4501EBC
	UINT32                                                 reserved1930;	//0xC4501EC0
	UINT32                                                 reserved1931;	//0xC4501EC4
	UINT32                                                 reserved1932;	//0xC4501EC8
	UINT32                                                 reserved1933;	//0xC4501ECC
	UINT32                                                 reserved1934;	//0xC4501ED0
	UINT32                                                 reserved1935;	//0xC4501ED4
	UINT32                                                 reserved1936;	//0xC4501ED8
	UINT32                                                 reserved1937;	//0xC4501EDC
	UINT32                                                 reserved1938;	//0xC4501EE0
	UINT32                                                 reserved1939;	//0xC4501EE4
	UINT32                                                 reserved1940;	//0xC4501EE8
	UINT32                                                 reserved1941;	//0xC4501EEC
	UINT32                                                 reserved1942;	//0xC4501EF0
	UINT32                                                 reserved1943;	//0xC4501EF4
	UINT32                                                 reserved1944;	//0xC4501EF8
	UINT32                                                 reserved1945;	//0xC4501EFC
	UINT32                                                 reserved1946;	//0xC4501F00
	UINT32                                                 reserved1947;	//0xC4501F04
	UINT32                                                 reserved1948;	//0xC4501F08
	UINT32                                                 reserved1949;	//0xC4501F0C
	UINT32                                                 reserved1950;	//0xC4501F10
	UINT32                                                 reserved1951;	//0xC4501F14
	UINT32                                                 reserved1952;	//0xC4501F18
	UINT32                                                 reserved1953;	//0xC4501F1C
	UINT32                                                 reserved1954;	//0xC4501F20
	UINT32                                                 reserved1955;	//0xC4501F24
	UINT32                                                 reserved1956;	//0xC4501F28
	UINT32                                                 reserved1957;	//0xC4501F2C
	UINT32                                                 reserved1958;	//0xC4501F30
	UINT32                                                 reserved1959;	//0xC4501F34
	UINT32                                                 reserved1960;	//0xC4501F38
	UINT32                                                 reserved1961;	//0xC4501F3C
	UINT32                                                 reserved1962;	//0xC4501F40
	UINT32                                                 reserved1963;	//0xC4501F44
	UINT32                                                 reserved1964;	//0xC4501F48
	UINT32                                                 reserved1965;	//0xC4501F4C
	UINT32                                                 reserved1966;	//0xC4501F50
	UINT32                                                 reserved1967;	//0xC4501F54
	UINT32                                                 reserved1968;	//0xC4501F58
	UINT32                                                 reserved1969;	//0xC4501F5C
	UINT32                                                 reserved1970;	//0xC4501F60
	UINT32                                                 reserved1971;	//0xC4501F64
	UINT32                                                 reserved1972;	//0xC4501F68
	UINT32                                                 reserved1973;	//0xC4501F6C
	UINT32                                                 reserved1974;	//0xC4501F70
	UINT32                                                 reserved1975;	//0xC4501F74
	UINT32                                                 reserved1976;	//0xC4501F78
	UINT32                                                 reserved1977;	//0xC4501F7C
	UINT32                                                 reserved1978;	//0xC4501F80
	UINT32                                                 reserved1979;	//0xC4501F84
	UINT32                                                 reserved1980;	//0xC4501F88
	UINT32                                                 reserved1981;	//0xC4501F8C
	UINT32                                                 reserved1982;	//0xC4501F90
	UINT32                                                 reserved1983;	//0xC4501F94
	UINT32                                                 reserved1984;	//0xC4501F98
	UINT32                                                 reserved1985;	//0xC4501F9C
	UINT32                                                 reserved1986;	//0xC4501FA0
	UINT32                                                 reserved1987;	//0xC4501FA4
	UINT32                                                 reserved1988;	//0xC4501FA8
	UINT32                                                 reserved1989;	//0xC4501FAC
	UINT32                                                 reserved1990;	//0xC4501FB0
	UINT32                                                 reserved1991;	//0xC4501FB4
	UINT32                                                 reserved1992;	//0xC4501FB8
	UINT32                                                 reserved1993;	//0xC4501FBC
	UINT32                                                 reserved1994;	//0xC4501FC0
	UINT32                                                 reserved1995;	//0xC4501FC4
	UINT32                                                 reserved1996;	//0xC4501FC8
	UINT32                                                 reserved1997;	//0xC4501FCC
	UINT32                                                 reserved1998;	//0xC4501FD0
	UINT32                                                 reserved1999;	//0xC4501FD4
	UINT32                                                 reserved2000;	//0xC4501FD8
	UINT32                                                 reserved2001;	//0xC4501FDC
	UINT32                                                 reserved2002;	//0xC4501FE0
	UINT32                                                 reserved2003;	//0xC4501FE4
	UINT32                                                 reserved2004;	//0xC4501FE8
	UINT32                                                 reserved2005;	//0xC4501FEC
	UINT32                                                 reserved2006;	//0xC4501FF0
	UINT32                                                 reserved2007;	//0xC4501FF4
	UINT32                                                 reserved2008;	//0xC4501FF8
	UINT32                                                 reserved2009;	//0xC4501FFC
	REG_DDRC_M2_PQ_T                                                 pq;	//0xC4502000
	REG_DDRC_M2_BQ_T                                                 bq;	//0xC4502004
	REG_DDRC_M2_BQ_RW_THR_T                                   bq_rw_thr;	//0xC4502008
	REG_DDRC_M2_BQ_HYB_STV_T                                 bq_hyb_stv;	//0xC450200C
	UINT32                                                 reserved2010;	//0xC4502010
	UINT32                                                 reserved2011;	//0xC4502014
	UINT32                                                 reserved2012;	//0xC4502018
	UINT32                                                 reserved2013;	//0xC450201C
	UINT32                                                 reserved2014;	//0xC4502020
	UINT32                                                 reserved2015;	//0xC4502024
	UINT32                                                 reserved2016;	//0xC4502028
	UINT32                                                 reserved2017;	//0xC450202C
	UINT32                                                 reserved2018;	//0xC4502030
	UINT32                                                 reserved2019;	//0xC4502034
	UINT32                                                 reserved2020;	//0xC4502038
	UINT32                                                 reserved2021;	//0xC450203C
	UINT32                                                 reserved2022;	//0xC4502040
	UINT32                                                 reserved2023;	//0xC4502044
	UINT32                                                 reserved2024;	//0xC4502048
	UINT32                                                 reserved2025;	//0xC450204C
	UINT32                                                 reserved2026;	//0xC4502050
	UINT32                                                 reserved2027;	//0xC4502054
	UINT32                                                 reserved2028;	//0xC4502058
	UINT32                                                 reserved2029;	//0xC450205C
	UINT32                                                 reserved2030;	//0xC4502060
	UINT32                                                 reserved2031;	//0xC4502064
	UINT32                                                 reserved2032;	//0xC4502068
	UINT32                                                 reserved2033;	//0xC450206C
	UINT32                                                 reserved2034;	//0xC4502070
	UINT32                                                 reserved2035;	//0xC4502074
	UINT32                                                 reserved2036;	//0xC4502078
	UINT32                                                 reserved2037;	//0xC450207C
	UINT32                                                 reserved2038;	//0xC4502080
	UINT32                                                 reserved2039;	//0xC4502084
	UINT32                                                 reserved2040;	//0xC4502088
	UINT32                                                 reserved2041;	//0xC450208C
	UINT32                                                 reserved2042;	//0xC4502090
	UINT32                                                 reserved2043;	//0xC4502094
	UINT32                                                 reserved2044;	//0xC4502098
	UINT32                                                 reserved2045;	//0xC450209C
	UINT32                                                 reserved2046;	//0xC45020A0
	UINT32                                                 reserved2047;	//0xC45020A4
	UINT32                                                 reserved2048;	//0xC45020A8
	UINT32                                                 reserved2049;	//0xC45020AC
	UINT32                                                 reserved2050;	//0xC45020B0
	UINT32                                                 reserved2051;	//0xC45020B4
	UINT32                                                 reserved2052;	//0xC45020B8
	UINT32                                                 reserved2053;	//0xC45020BC
	UINT32                                                 reserved2054;	//0xC45020C0
	UINT32                                                 reserved2055;	//0xC45020C4
	UINT32                                                 reserved2056;	//0xC45020C8
	UINT32                                                 reserved2057;	//0xC45020CC
	UINT32                                                 reserved2058;	//0xC45020D0
	UINT32                                                 reserved2059;	//0xC45020D4
	UINT32                                                 reserved2060;	//0xC45020D8
	UINT32                                                 reserved2061;	//0xC45020DC
	UINT32                                                 reserved2062;	//0xC45020E0
	UINT32                                                 reserved2063;	//0xC45020E4
	UINT32                                                 reserved2064;	//0xC45020E8
	UINT32                                                 reserved2065;	//0xC45020EC
	UINT32                                                 reserved2066;	//0xC45020F0
	UINT32                                                 reserved2067;	//0xC45020F4
	UINT32                                                 reserved2068;	//0xC45020F8
	UINT32                                                 reserved2069;	//0xC45020FC
	UINT32                                                 reserved2070;	//0xC4502100
	UINT32                                                 reserved2071;	//0xC4502104
	UINT32                                                 reserved2072;	//0xC4502108
	UINT32                                                 reserved2073;	//0xC450210C
	UINT32                                                 reserved2074;	//0xC4502110
	UINT32                                                 reserved2075;	//0xC4502114
	UINT32                                                 reserved2076;	//0xC4502118
	UINT32                                                 reserved2077;	//0xC450211C
	UINT32                                                 reserved2078;	//0xC4502120
	UINT32                                                 reserved2079;	//0xC4502124
	UINT32                                                 reserved2080;	//0xC4502128
	UINT32                                                 reserved2081;	//0xC450212C
	UINT32                                                 reserved2082;	//0xC4502130
	UINT32                                                 reserved2083;	//0xC4502134
	UINT32                                                 reserved2084;	//0xC4502138
	UINT32                                                 reserved2085;	//0xC450213C
	UINT32                                                 reserved2086;	//0xC4502140
	UINT32                                                 reserved2087;	//0xC4502144
	UINT32                                                 reserved2088;	//0xC4502148
	UINT32                                                 reserved2089;	//0xC450214C
	UINT32                                                 reserved2090;	//0xC4502150
	UINT32                                                 reserved2091;	//0xC4502154
	UINT32                                                 reserved2092;	//0xC4502158
	UINT32                                                 reserved2093;	//0xC450215C
	UINT32                                                 reserved2094;	//0xC4502160
	UINT32                                                 reserved2095;	//0xC4502164
	UINT32                                                 reserved2096;	//0xC4502168
	UINT32                                                 reserved2097;	//0xC450216C
	UINT32                                                 reserved2098;	//0xC4502170
	UINT32                                                 reserved2099;	//0xC4502174
	UINT32                                                 reserved2100;	//0xC4502178
	UINT32                                                 reserved2101;	//0xC450217C
	UINT32                                                 reserved2102;	//0xC4502180
	UINT32                                                 reserved2103;	//0xC4502184
	UINT32                                                 reserved2104;	//0xC4502188
	UINT32                                                 reserved2105;	//0xC450218C
	UINT32                                                 reserved2106;	//0xC4502190
	UINT32                                                 reserved2107;	//0xC4502194
	UINT32                                                 reserved2108;	//0xC4502198
	UINT32                                                 reserved2109;	//0xC450219C
	UINT32                                                 reserved2110;	//0xC45021A0
	UINT32                                                 reserved2111;	//0xC45021A4
	UINT32                                                 reserved2112;	//0xC45021A8
	UINT32                                                 reserved2113;	//0xC45021AC
	UINT32                                                 reserved2114;	//0xC45021B0
	UINT32                                                 reserved2115;	//0xC45021B4
	UINT32                                                 reserved2116;	//0xC45021B8
	UINT32                                                 reserved2117;	//0xC45021BC
	UINT32                                                 reserved2118;	//0xC45021C0
	UINT32                                                 reserved2119;	//0xC45021C4
	UINT32                                                 reserved2120;	//0xC45021C8
	UINT32                                                 reserved2121;	//0xC45021CC
	UINT32                                                 reserved2122;	//0xC45021D0
	UINT32                                                 reserved2123;	//0xC45021D4
	UINT32                                                 reserved2124;	//0xC45021D8
	UINT32                                                 reserved2125;	//0xC45021DC
	UINT32                                                 reserved2126;	//0xC45021E0
	UINT32                                                 reserved2127;	//0xC45021E4
	UINT32                                                 reserved2128;	//0xC45021E8
	UINT32                                                 reserved2129;	//0xC45021EC
	UINT32                                                 reserved2130;	//0xC45021F0
	UINT32                                                 reserved2131;	//0xC45021F4
	UINT32                                                 reserved2132;	//0xC45021F8
	UINT32                                                 reserved2133;	//0xC45021FC
	UINT32                                                 reserved2134;	//0xC4502200
	UINT32                                                 reserved2135;	//0xC4502204
	UINT32                                                 reserved2136;	//0xC4502208
	UINT32                                                 reserved2137;	//0xC450220C
	UINT32                                                 reserved2138;	//0xC4502210
	UINT32                                                 reserved2139;	//0xC4502214
	UINT32                                                 reserved2140;	//0xC4502218
	UINT32                                                 reserved2141;	//0xC450221C
	UINT32                                                 reserved2142;	//0xC4502220
	UINT32                                                 reserved2143;	//0xC4502224
	UINT32                                                 reserved2144;	//0xC4502228
	UINT32                                                 reserved2145;	//0xC450222C
	UINT32                                                 reserved2146;	//0xC4502230
	UINT32                                                 reserved2147;	//0xC4502234
	UINT32                                                 reserved2148;	//0xC4502238
	UINT32                                                 reserved2149;	//0xC450223C
	UINT32                                                 reserved2150;	//0xC4502240
	UINT32                                                 reserved2151;	//0xC4502244
	UINT32                                                 reserved2152;	//0xC4502248
	UINT32                                                 reserved2153;	//0xC450224C
	UINT32                                                 reserved2154;	//0xC4502250
	UINT32                                                 reserved2155;	//0xC4502254
	UINT32                                                 reserved2156;	//0xC4502258
	UINT32                                                 reserved2157;	//0xC450225C
	UINT32                                                 reserved2158;	//0xC4502260
	UINT32                                                 reserved2159;	//0xC4502264
	UINT32                                                 reserved2160;	//0xC4502268
	UINT32                                                 reserved2161;	//0xC450226C
	UINT32                                                 reserved2162;	//0xC4502270
	UINT32                                                 reserved2163;	//0xC4502274
	UINT32                                                 reserved2164;	//0xC4502278
	UINT32                                                 reserved2165;	//0xC450227C
	UINT32                                                 reserved2166;	//0xC4502280
	UINT32                                                 reserved2167;	//0xC4502284
	UINT32                                                 reserved2168;	//0xC4502288
	UINT32                                                 reserved2169;	//0xC450228C
	UINT32                                                 reserved2170;	//0xC4502290
	UINT32                                                 reserved2171;	//0xC4502294
	UINT32                                                 reserved2172;	//0xC4502298
	UINT32                                                 reserved2173;	//0xC450229C
	UINT32                                                 reserved2174;	//0xC45022A0
	UINT32                                                 reserved2175;	//0xC45022A4
	UINT32                                                 reserved2176;	//0xC45022A8
	UINT32                                                 reserved2177;	//0xC45022AC
	UINT32                                                 reserved2178;	//0xC45022B0
	UINT32                                                 reserved2179;	//0xC45022B4
	UINT32                                                 reserved2180;	//0xC45022B8
	UINT32                                                 reserved2181;	//0xC45022BC
	UINT32                                                 reserved2182;	//0xC45022C0
	UINT32                                                 reserved2183;	//0xC45022C4
	UINT32                                                 reserved2184;	//0xC45022C8
	UINT32                                                 reserved2185;	//0xC45022CC
	UINT32                                                 reserved2186;	//0xC45022D0
	UINT32                                                 reserved2187;	//0xC45022D4
	UINT32                                                 reserved2188;	//0xC45022D8
	UINT32                                                 reserved2189;	//0xC45022DC
	UINT32                                                 reserved2190;	//0xC45022E0
	UINT32                                                 reserved2191;	//0xC45022E4
	UINT32                                                 reserved2192;	//0xC45022E8
	UINT32                                                 reserved2193;	//0xC45022EC
	UINT32                                                 reserved2194;	//0xC45022F0
	UINT32                                                 reserved2195;	//0xC45022F4
	UINT32                                                 reserved2196;	//0xC45022F8
	UINT32                                                 reserved2197;	//0xC45022FC
	UINT32                                                 reserved2198;	//0xC4502300
	UINT32                                                 reserved2199;	//0xC4502304
	UINT32                                                 reserved2200;	//0xC4502308
	UINT32                                                 reserved2201;	//0xC450230C
	UINT32                                                 reserved2202;	//0xC4502310
	UINT32                                                 reserved2203;	//0xC4502314
	UINT32                                                 reserved2204;	//0xC4502318
	UINT32                                                 reserved2205;	//0xC450231C
	UINT32                                                 reserved2206;	//0xC4502320
	UINT32                                                 reserved2207;	//0xC4502324
	UINT32                                                 reserved2208;	//0xC4502328
	UINT32                                                 reserved2209;	//0xC450232C
	UINT32                                                 reserved2210;	//0xC4502330
	UINT32                                                 reserved2211;	//0xC4502334
	UINT32                                                 reserved2212;	//0xC4502338
	UINT32                                                 reserved2213;	//0xC450233C
	UINT32                                                 reserved2214;	//0xC4502340
	UINT32                                                 reserved2215;	//0xC4502344
	UINT32                                                 reserved2216;	//0xC4502348
	UINT32                                                 reserved2217;	//0xC450234C
	UINT32                                                 reserved2218;	//0xC4502350
	UINT32                                                 reserved2219;	//0xC4502354
	UINT32                                                 reserved2220;	//0xC4502358
	UINT32                                                 reserved2221;	//0xC450235C
	UINT32                                                 reserved2222;	//0xC4502360
	UINT32                                                 reserved2223;	//0xC4502364
	UINT32                                                 reserved2224;	//0xC4502368
	UINT32                                                 reserved2225;	//0xC450236C
	UINT32                                                 reserved2226;	//0xC4502370
	UINT32                                                 reserved2227;	//0xC4502374
	UINT32                                                 reserved2228;	//0xC4502378
	UINT32                                                 reserved2229;	//0xC450237C
	UINT32                                                 reserved2230;	//0xC4502380
	UINT32                                                 reserved2231;	//0xC4502384
	UINT32                                                 reserved2232;	//0xC4502388
	UINT32                                                 reserved2233;	//0xC450238C
	UINT32                                                 reserved2234;	//0xC4502390
	UINT32                                                 reserved2235;	//0xC4502394
	UINT32                                                 reserved2236;	//0xC4502398
	UINT32                                                 reserved2237;	//0xC450239C
	UINT32                                                 reserved2238;	//0xC45023A0
	UINT32                                                 reserved2239;	//0xC45023A4
	UINT32                                                 reserved2240;	//0xC45023A8
	UINT32                                                 reserved2241;	//0xC45023AC
	UINT32                                                 reserved2242;	//0xC45023B0
	UINT32                                                 reserved2243;	//0xC45023B4
	UINT32                                                 reserved2244;	//0xC45023B8
	UINT32                                                 reserved2245;	//0xC45023BC
	UINT32                                                 reserved2246;	//0xC45023C0
	UINT32                                                 reserved2247;	//0xC45023C4
	UINT32                                                 reserved2248;	//0xC45023C8
	UINT32                                                 reserved2249;	//0xC45023CC
	UINT32                                                 reserved2250;	//0xC45023D0
	UINT32                                                 reserved2251;	//0xC45023D4
	UINT32                                                 reserved2252;	//0xC45023D8
	UINT32                                                 reserved2253;	//0xC45023DC
	UINT32                                                 reserved2254;	//0xC45023E0
	UINT32                                                 reserved2255;	//0xC45023E4
	UINT32                                                 reserved2256;	//0xC45023E8
	UINT32                                                 reserved2257;	//0xC45023EC
	UINT32                                                 reserved2258;	//0xC45023F0
	UINT32                                                 reserved2259;	//0xC45023F4
	UINT32                                                 reserved2260;	//0xC45023F8
	UINT32                                                 reserved2261;	//0xC45023FC
	UINT32                                                 reserved2262;	//0xC4502400
	UINT32                                                 reserved2263;	//0xC4502404
	UINT32                                                 reserved2264;	//0xC4502408
	UINT32                                                 reserved2265;	//0xC450240C
	UINT32                                                 reserved2266;	//0xC4502410
	UINT32                                                 reserved2267;	//0xC4502414
	UINT32                                                 reserved2268;	//0xC4502418
	UINT32                                                 reserved2269;	//0xC450241C
	UINT32                                                 reserved2270;	//0xC4502420
	UINT32                                                 reserved2271;	//0xC4502424
	UINT32                                                 reserved2272;	//0xC4502428
	UINT32                                                 reserved2273;	//0xC450242C
	UINT32                                                 reserved2274;	//0xC4502430
	UINT32                                                 reserved2275;	//0xC4502434
	UINT32                                                 reserved2276;	//0xC4502438
	UINT32                                                 reserved2277;	//0xC450243C
	UINT32                                                 reserved2278;	//0xC4502440
	UINT32                                                 reserved2279;	//0xC4502444
	UINT32                                                 reserved2280;	//0xC4502448
	UINT32                                                 reserved2281;	//0xC450244C
	UINT32                                                 reserved2282;	//0xC4502450
	UINT32                                                 reserved2283;	//0xC4502454
	UINT32                                                 reserved2284;	//0xC4502458
	UINT32                                                 reserved2285;	//0xC450245C
	UINT32                                                 reserved2286;	//0xC4502460
	UINT32                                                 reserved2287;	//0xC4502464
	UINT32                                                 reserved2288;	//0xC4502468
	UINT32                                                 reserved2289;	//0xC450246C
	UINT32                                                 reserved2290;	//0xC4502470
	UINT32                                                 reserved2291;	//0xC4502474
	UINT32                                                 reserved2292;	//0xC4502478
	UINT32                                                 reserved2293;	//0xC450247C
	UINT32                                                 reserved2294;	//0xC4502480
	UINT32                                                 reserved2295;	//0xC4502484
	UINT32                                                 reserved2296;	//0xC4502488
	UINT32                                                 reserved2297;	//0xC450248C
	UINT32                                                 reserved2298;	//0xC4502490
	UINT32                                                 reserved2299;	//0xC4502494
	UINT32                                                 reserved2300;	//0xC4502498
	UINT32                                                 reserved2301;	//0xC450249C
	UINT32                                                 reserved2302;	//0xC45024A0
	UINT32                                                 reserved2303;	//0xC45024A4
	UINT32                                                 reserved2304;	//0xC45024A8
	UINT32                                                 reserved2305;	//0xC45024AC
	UINT32                                                 reserved2306;	//0xC45024B0
	UINT32                                                 reserved2307;	//0xC45024B4
	UINT32                                                 reserved2308;	//0xC45024B8
	UINT32                                                 reserved2309;	//0xC45024BC
	UINT32                                                 reserved2310;	//0xC45024C0
	UINT32                                                 reserved2311;	//0xC45024C4
	UINT32                                                 reserved2312;	//0xC45024C8
	UINT32                                                 reserved2313;	//0xC45024CC
	UINT32                                                 reserved2314;	//0xC45024D0
	UINT32                                                 reserved2315;	//0xC45024D4
	UINT32                                                 reserved2316;	//0xC45024D8
	UINT32                                                 reserved2317;	//0xC45024DC
	UINT32                                                 reserved2318;	//0xC45024E0
	UINT32                                                 reserved2319;	//0xC45024E4
	UINT32                                                 reserved2320;	//0xC45024E8
	UINT32                                                 reserved2321;	//0xC45024EC
	UINT32                                                 reserved2322;	//0xC45024F0
	UINT32                                                 reserved2323;	//0xC45024F4
	UINT32                                                 reserved2324;	//0xC45024F8
	UINT32                                                 reserved2325;	//0xC45024FC
	UINT32                                                 reserved2326;	//0xC4502500
	UINT32                                                 reserved2327;	//0xC4502504
	UINT32                                                 reserved2328;	//0xC4502508
	UINT32                                                 reserved2329;	//0xC450250C
	UINT32                                                 reserved2330;	//0xC4502510
	UINT32                                                 reserved2331;	//0xC4502514
	UINT32                                                 reserved2332;	//0xC4502518
	UINT32                                                 reserved2333;	//0xC450251C
	UINT32                                                 reserved2334;	//0xC4502520
	UINT32                                                 reserved2335;	//0xC4502524
	UINT32                                                 reserved2336;	//0xC4502528
	UINT32                                                 reserved2337;	//0xC450252C
	UINT32                                                 reserved2338;	//0xC4502530
	UINT32                                                 reserved2339;	//0xC4502534
	UINT32                                                 reserved2340;	//0xC4502538
	UINT32                                                 reserved2341;	//0xC450253C
	UINT32                                                 reserved2342;	//0xC4502540
	UINT32                                                 reserved2343;	//0xC4502544
	UINT32                                                 reserved2344;	//0xC4502548
	UINT32                                                 reserved2345;	//0xC450254C
	UINT32                                                 reserved2346;	//0xC4502550
	UINT32                                                 reserved2347;	//0xC4502554
	UINT32                                                 reserved2348;	//0xC4502558
	UINT32                                                 reserved2349;	//0xC450255C
	UINT32                                                 reserved2350;	//0xC4502560
	UINT32                                                 reserved2351;	//0xC4502564
	UINT32                                                 reserved2352;	//0xC4502568
	UINT32                                                 reserved2353;	//0xC450256C
	UINT32                                                 reserved2354;	//0xC4502570
	UINT32                                                 reserved2355;	//0xC4502574
	UINT32                                                 reserved2356;	//0xC4502578
	UINT32                                                 reserved2357;	//0xC450257C
	UINT32                                                 reserved2358;	//0xC4502580
	UINT32                                                 reserved2359;	//0xC4502584
	UINT32                                                 reserved2360;	//0xC4502588
	UINT32                                                 reserved2361;	//0xC450258C
	UINT32                                                 reserved2362;	//0xC4502590
	UINT32                                                 reserved2363;	//0xC4502594
	UINT32                                                 reserved2364;	//0xC4502598
	UINT32                                                 reserved2365;	//0xC450259C
	UINT32                                                 reserved2366;	//0xC45025A0
	UINT32                                                 reserved2367;	//0xC45025A4
	UINT32                                                 reserved2368;	//0xC45025A8
	UINT32                                                 reserved2369;	//0xC45025AC
	UINT32                                                 reserved2370;	//0xC45025B0
	UINT32                                                 reserved2371;	//0xC45025B4
	UINT32                                                 reserved2372;	//0xC45025B8
	UINT32                                                 reserved2373;	//0xC45025BC
	UINT32                                                 reserved2374;	//0xC45025C0
	UINT32                                                 reserved2375;	//0xC45025C4
	UINT32                                                 reserved2376;	//0xC45025C8
	UINT32                                                 reserved2377;	//0xC45025CC
	UINT32                                                 reserved2378;	//0xC45025D0
	UINT32                                                 reserved2379;	//0xC45025D4
	UINT32                                                 reserved2380;	//0xC45025D8
	UINT32                                                 reserved2381;	//0xC45025DC
	UINT32                                                 reserved2382;	//0xC45025E0
	UINT32                                                 reserved2383;	//0xC45025E4
	UINT32                                                 reserved2384;	//0xC45025E8
	UINT32                                                 reserved2385;	//0xC45025EC
	UINT32                                                 reserved2386;	//0xC45025F0
	UINT32                                                 reserved2387;	//0xC45025F4
	UINT32                                                 reserved2388;	//0xC45025F8
	UINT32                                                 reserved2389;	//0xC45025FC
	UINT32                                                 reserved2390;	//0xC4502600
	UINT32                                                 reserved2391;	//0xC4502604
	UINT32                                                 reserved2392;	//0xC4502608
	UINT32                                                 reserved2393;	//0xC450260C
	UINT32                                                 reserved2394;	//0xC4502610
	UINT32                                                 reserved2395;	//0xC4502614
	UINT32                                                 reserved2396;	//0xC4502618
	UINT32                                                 reserved2397;	//0xC450261C
	UINT32                                                 reserved2398;	//0xC4502620
	UINT32                                                 reserved2399;	//0xC4502624
	UINT32                                                 reserved2400;	//0xC4502628
	UINT32                                                 reserved2401;	//0xC450262C
	UINT32                                                 reserved2402;	//0xC4502630
	UINT32                                                 reserved2403;	//0xC4502634
	UINT32                                                 reserved2404;	//0xC4502638
	UINT32                                                 reserved2405;	//0xC450263C
	UINT32                                                 reserved2406;	//0xC4502640
	UINT32                                                 reserved2407;	//0xC4502644
	UINT32                                                 reserved2408;	//0xC4502648
	UINT32                                                 reserved2409;	//0xC450264C
	UINT32                                                 reserved2410;	//0xC4502650
	UINT32                                                 reserved2411;	//0xC4502654
	UINT32                                                 reserved2412;	//0xC4502658
	UINT32                                                 reserved2413;	//0xC450265C
	UINT32                                                 reserved2414;	//0xC4502660
	UINT32                                                 reserved2415;	//0xC4502664
	UINT32                                                 reserved2416;	//0xC4502668
	UINT32                                                 reserved2417;	//0xC450266C
	UINT32                                                 reserved2418;	//0xC4502670
	UINT32                                                 reserved2419;	//0xC4502674
	UINT32                                                 reserved2420;	//0xC4502678
	UINT32                                                 reserved2421;	//0xC450267C
	UINT32                                                 reserved2422;	//0xC4502680
	UINT32                                                 reserved2423;	//0xC4502684
	UINT32                                                 reserved2424;	//0xC4502688
	UINT32                                                 reserved2425;	//0xC450268C
	UINT32                                                 reserved2426;	//0xC4502690
	UINT32                                                 reserved2427;	//0xC4502694
	UINT32                                                 reserved2428;	//0xC4502698
	UINT32                                                 reserved2429;	//0xC450269C
	UINT32                                                 reserved2430;	//0xC45026A0
	UINT32                                                 reserved2431;	//0xC45026A4
	UINT32                                                 reserved2432;	//0xC45026A8
	UINT32                                                 reserved2433;	//0xC45026AC
	UINT32                                                 reserved2434;	//0xC45026B0
	UINT32                                                 reserved2435;	//0xC45026B4
	UINT32                                                 reserved2436;	//0xC45026B8
	UINT32                                                 reserved2437;	//0xC45026BC
	UINT32                                                 reserved2438;	//0xC45026C0
	UINT32                                                 reserved2439;	//0xC45026C4
	UINT32                                                 reserved2440;	//0xC45026C8
	UINT32                                                 reserved2441;	//0xC45026CC
	UINT32                                                 reserved2442;	//0xC45026D0
	UINT32                                                 reserved2443;	//0xC45026D4
	UINT32                                                 reserved2444;	//0xC45026D8
	UINT32                                                 reserved2445;	//0xC45026DC
	UINT32                                                 reserved2446;	//0xC45026E0
	UINT32                                                 reserved2447;	//0xC45026E4
	UINT32                                                 reserved2448;	//0xC45026E8
	UINT32                                                 reserved2449;	//0xC45026EC
	UINT32                                                 reserved2450;	//0xC45026F0
	UINT32                                                 reserved2451;	//0xC45026F4
	UINT32                                                 reserved2452;	//0xC45026F8
	UINT32                                                 reserved2453;	//0xC45026FC
	UINT32                                                 reserved2454;	//0xC4502700
	UINT32                                                 reserved2455;	//0xC4502704
	UINT32                                                 reserved2456;	//0xC4502708
	UINT32                                                 reserved2457;	//0xC450270C
	UINT32                                                 reserved2458;	//0xC4502710
	UINT32                                                 reserved2459;	//0xC4502714
	UINT32                                                 reserved2460;	//0xC4502718
	UINT32                                                 reserved2461;	//0xC450271C
	UINT32                                                 reserved2462;	//0xC4502720
	UINT32                                                 reserved2463;	//0xC4502724
	UINT32                                                 reserved2464;	//0xC4502728
	UINT32                                                 reserved2465;	//0xC450272C
	UINT32                                                 reserved2466;	//0xC4502730
	UINT32                                                 reserved2467;	//0xC4502734
	UINT32                                                 reserved2468;	//0xC4502738
	UINT32                                                 reserved2469;	//0xC450273C
	UINT32                                                 reserved2470;	//0xC4502740
	UINT32                                                 reserved2471;	//0xC4502744
	UINT32                                                 reserved2472;	//0xC4502748
	UINT32                                                 reserved2473;	//0xC450274C
	UINT32                                                 reserved2474;	//0xC4502750
	UINT32                                                 reserved2475;	//0xC4502754
	UINT32                                                 reserved2476;	//0xC4502758
	UINT32                                                 reserved2477;	//0xC450275C
	UINT32                                                 reserved2478;	//0xC4502760
	UINT32                                                 reserved2479;	//0xC4502764
	UINT32                                                 reserved2480;	//0xC4502768
	UINT32                                                 reserved2481;	//0xC450276C
	UINT32                                                 reserved2482;	//0xC4502770
	UINT32                                                 reserved2483;	//0xC4502774
	UINT32                                                 reserved2484;	//0xC4502778
	UINT32                                                 reserved2485;	//0xC450277C
	UINT32                                                 reserved2486;	//0xC4502780
	UINT32                                                 reserved2487;	//0xC4502784
	UINT32                                                 reserved2488;	//0xC4502788
	UINT32                                                 reserved2489;	//0xC450278C
	UINT32                                                 reserved2490;	//0xC4502790
	UINT32                                                 reserved2491;	//0xC4502794
	UINT32                                                 reserved2492;	//0xC4502798
	UINT32                                                 reserved2493;	//0xC450279C
	UINT32                                                 reserved2494;	//0xC45027A0
	UINT32                                                 reserved2495;	//0xC45027A4
	UINT32                                                 reserved2496;	//0xC45027A8
	UINT32                                                 reserved2497;	//0xC45027AC
	UINT32                                                 reserved2498;	//0xC45027B0
	UINT32                                                 reserved2499;	//0xC45027B4
	UINT32                                                 reserved2500;	//0xC45027B8
	UINT32                                                 reserved2501;	//0xC45027BC
	UINT32                                                 reserved2502;	//0xC45027C0
	UINT32                                                 reserved2503;	//0xC45027C4
	UINT32                                                 reserved2504;	//0xC45027C8
	UINT32                                                 reserved2505;	//0xC45027CC
	UINT32                                                 reserved2506;	//0xC45027D0
	UINT32                                                 reserved2507;	//0xC45027D4
	UINT32                                                 reserved2508;	//0xC45027D8
	UINT32                                                 reserved2509;	//0xC45027DC
	UINT32                                                 reserved2510;	//0xC45027E0
	UINT32                                                 reserved2511;	//0xC45027E4
	UINT32                                                 reserved2512;	//0xC45027E8
	UINT32                                                 reserved2513;	//0xC45027EC
	UINT32                                                 reserved2514;	//0xC45027F0
	UINT32                                                 reserved2515;	//0xC45027F4
	UINT32                                                 reserved2516;	//0xC45027F8
	UINT32                                                 reserved2517;	//0xC45027FC
	UINT32                                                 reserved2518;	//0xC4502800
	UINT32                                                 reserved2519;	//0xC4502804
	UINT32                                                 reserved2520;	//0xC4502808
	UINT32                                                 reserved2521;	//0xC450280C
	UINT32                                                 reserved2522;	//0xC4502810
	UINT32                                                 reserved2523;	//0xC4502814
	UINT32                                                 reserved2524;	//0xC4502818
	UINT32                                                 reserved2525;	//0xC450281C
	UINT32                                                 reserved2526;	//0xC4502820
	UINT32                                                 reserved2527;	//0xC4502824
	UINT32                                                 reserved2528;	//0xC4502828
	UINT32                                                 reserved2529;	//0xC450282C
	UINT32                                                 reserved2530;	//0xC4502830
	UINT32                                                 reserved2531;	//0xC4502834
	UINT32                                                 reserved2532;	//0xC4502838
	UINT32                                                 reserved2533;	//0xC450283C
	UINT32                                                 reserved2534;	//0xC4502840
	UINT32                                                 reserved2535;	//0xC4502844
	UINT32                                                 reserved2536;	//0xC4502848
	UINT32                                                 reserved2537;	//0xC450284C
	UINT32                                                 reserved2538;	//0xC4502850
	UINT32                                                 reserved2539;	//0xC4502854
	UINT32                                                 reserved2540;	//0xC4502858
	UINT32                                                 reserved2541;	//0xC450285C
	UINT32                                                 reserved2542;	//0xC4502860
	UINT32                                                 reserved2543;	//0xC4502864
	UINT32                                                 reserved2544;	//0xC4502868
	UINT32                                                 reserved2545;	//0xC450286C
	UINT32                                                 reserved2546;	//0xC4502870
	UINT32                                                 reserved2547;	//0xC4502874
	UINT32                                                 reserved2548;	//0xC4502878
	UINT32                                                 reserved2549;	//0xC450287C
	UINT32                                                 reserved2550;	//0xC4502880
	UINT32                                                 reserved2551;	//0xC4502884
	UINT32                                                 reserved2552;	//0xC4502888
	UINT32                                                 reserved2553;	//0xC450288C
	UINT32                                                 reserved2554;	//0xC4502890
	UINT32                                                 reserved2555;	//0xC4502894
	UINT32                                                 reserved2556;	//0xC4502898
	UINT32                                                 reserved2557;	//0xC450289C
	UINT32                                                 reserved2558;	//0xC45028A0
	UINT32                                                 reserved2559;	//0xC45028A4
	UINT32                                                 reserved2560;	//0xC45028A8
	UINT32                                                 reserved2561;	//0xC45028AC
	UINT32                                                 reserved2562;	//0xC45028B0
	UINT32                                                 reserved2563;	//0xC45028B4
	UINT32                                                 reserved2564;	//0xC45028B8
	UINT32                                                 reserved2565;	//0xC45028BC
	UINT32                                                 reserved2566;	//0xC45028C0
	UINT32                                                 reserved2567;	//0xC45028C4
	UINT32                                                 reserved2568;	//0xC45028C8
	UINT32                                                 reserved2569;	//0xC45028CC
	UINT32                                                 reserved2570;	//0xC45028D0
	UINT32                                                 reserved2571;	//0xC45028D4
	UINT32                                                 reserved2572;	//0xC45028D8
	UINT32                                                 reserved2573;	//0xC45028DC
	UINT32                                                 reserved2574;	//0xC45028E0
	UINT32                                                 reserved2575;	//0xC45028E4
	UINT32                                                 reserved2576;	//0xC45028E8
	UINT32                                                 reserved2577;	//0xC45028EC
	UINT32                                                 reserved2578;	//0xC45028F0
	UINT32                                                 reserved2579;	//0xC45028F4
	UINT32                                                 reserved2580;	//0xC45028F8
	UINT32                                                 reserved2581;	//0xC45028FC
	UINT32                                                 reserved2582;	//0xC4502900
	UINT32                                                 reserved2583;	//0xC4502904
	UINT32                                                 reserved2584;	//0xC4502908
	UINT32                                                 reserved2585;	//0xC450290C
	UINT32                                                 reserved2586;	//0xC4502910
	UINT32                                                 reserved2587;	//0xC4502914
	UINT32                                                 reserved2588;	//0xC4502918
	UINT32                                                 reserved2589;	//0xC450291C
	UINT32                                                 reserved2590;	//0xC4502920
	UINT32                                                 reserved2591;	//0xC4502924
	UINT32                                                 reserved2592;	//0xC4502928
	UINT32                                                 reserved2593;	//0xC450292C
	UINT32                                                 reserved2594;	//0xC4502930
	UINT32                                                 reserved2595;	//0xC4502934
	UINT32                                                 reserved2596;	//0xC4502938
	UINT32                                                 reserved2597;	//0xC450293C
	UINT32                                                 reserved2598;	//0xC4502940
	UINT32                                                 reserved2599;	//0xC4502944
	UINT32                                                 reserved2600;	//0xC4502948
	UINT32                                                 reserved2601;	//0xC450294C
	UINT32                                                 reserved2602;	//0xC4502950
	UINT32                                                 reserved2603;	//0xC4502954
	UINT32                                                 reserved2604;	//0xC4502958
	UINT32                                                 reserved2605;	//0xC450295C
	UINT32                                                 reserved2606;	//0xC4502960
	UINT32                                                 reserved2607;	//0xC4502964
	UINT32                                                 reserved2608;	//0xC4502968
	UINT32                                                 reserved2609;	//0xC450296C
	UINT32                                                 reserved2610;	//0xC4502970
	UINT32                                                 reserved2611;	//0xC4502974
	UINT32                                                 reserved2612;	//0xC4502978
	UINT32                                                 reserved2613;	//0xC450297C
	UINT32                                                 reserved2614;	//0xC4502980
	UINT32                                                 reserved2615;	//0xC4502984
	UINT32                                                 reserved2616;	//0xC4502988
	UINT32                                                 reserved2617;	//0xC450298C
	UINT32                                                 reserved2618;	//0xC4502990
	UINT32                                                 reserved2619;	//0xC4502994
	UINT32                                                 reserved2620;	//0xC4502998
	UINT32                                                 reserved2621;	//0xC450299C
	UINT32                                                 reserved2622;	//0xC45029A0
	UINT32                                                 reserved2623;	//0xC45029A4
	UINT32                                                 reserved2624;	//0xC45029A8
	UINT32                                                 reserved2625;	//0xC45029AC
	UINT32                                                 reserved2626;	//0xC45029B0
	UINT32                                                 reserved2627;	//0xC45029B4
	UINT32                                                 reserved2628;	//0xC45029B8
	UINT32                                                 reserved2629;	//0xC45029BC
	UINT32                                                 reserved2630;	//0xC45029C0
	UINT32                                                 reserved2631;	//0xC45029C4
	UINT32                                                 reserved2632;	//0xC45029C8
	UINT32                                                 reserved2633;	//0xC45029CC
	UINT32                                                 reserved2634;	//0xC45029D0
	UINT32                                                 reserved2635;	//0xC45029D4
	UINT32                                                 reserved2636;	//0xC45029D8
	UINT32                                                 reserved2637;	//0xC45029DC
	UINT32                                                 reserved2638;	//0xC45029E0
	UINT32                                                 reserved2639;	//0xC45029E4
	UINT32                                                 reserved2640;	//0xC45029E8
	UINT32                                                 reserved2641;	//0xC45029EC
	UINT32                                                 reserved2642;	//0xC45029F0
	UINT32                                                 reserved2643;	//0xC45029F4
	UINT32                                                 reserved2644;	//0xC45029F8
	UINT32                                                 reserved2645;	//0xC45029FC
	UINT32                                                 reserved2646;	//0xC4502A00
	UINT32                                                 reserved2647;	//0xC4502A04
	UINT32                                                 reserved2648;	//0xC4502A08
	UINT32                                                 reserved2649;	//0xC4502A0C
	UINT32                                                 reserved2650;	//0xC4502A10
	UINT32                                                 reserved2651;	//0xC4502A14
	UINT32                                                 reserved2652;	//0xC4502A18
	UINT32                                                 reserved2653;	//0xC4502A1C
	UINT32                                                 reserved2654;	//0xC4502A20
	UINT32                                                 reserved2655;	//0xC4502A24
	UINT32                                                 reserved2656;	//0xC4502A28
	UINT32                                                 reserved2657;	//0xC4502A2C
	UINT32                                                 reserved2658;	//0xC4502A30
	UINT32                                                 reserved2659;	//0xC4502A34
	UINT32                                                 reserved2660;	//0xC4502A38
	UINT32                                                 reserved2661;	//0xC4502A3C
	UINT32                                                 reserved2662;	//0xC4502A40
	UINT32                                                 reserved2663;	//0xC4502A44
	UINT32                                                 reserved2664;	//0xC4502A48
	UINT32                                                 reserved2665;	//0xC4502A4C
	UINT32                                                 reserved2666;	//0xC4502A50
	UINT32                                                 reserved2667;	//0xC4502A54
	UINT32                                                 reserved2668;	//0xC4502A58
	UINT32                                                 reserved2669;	//0xC4502A5C
	UINT32                                                 reserved2670;	//0xC4502A60
	UINT32                                                 reserved2671;	//0xC4502A64
	UINT32                                                 reserved2672;	//0xC4502A68
	UINT32                                                 reserved2673;	//0xC4502A6C
	UINT32                                                 reserved2674;	//0xC4502A70
	UINT32                                                 reserved2675;	//0xC4502A74
	UINT32                                                 reserved2676;	//0xC4502A78
	UINT32                                                 reserved2677;	//0xC4502A7C
	UINT32                                                 reserved2678;	//0xC4502A80
	UINT32                                                 reserved2679;	//0xC4502A84
	UINT32                                                 reserved2680;	//0xC4502A88
	UINT32                                                 reserved2681;	//0xC4502A8C
	UINT32                                                 reserved2682;	//0xC4502A90
	UINT32                                                 reserved2683;	//0xC4502A94
	UINT32                                                 reserved2684;	//0xC4502A98
	UINT32                                                 reserved2685;	//0xC4502A9C
	UINT32                                                 reserved2686;	//0xC4502AA0
	UINT32                                                 reserved2687;	//0xC4502AA4
	UINT32                                                 reserved2688;	//0xC4502AA8
	UINT32                                                 reserved2689;	//0xC4502AAC
	UINT32                                                 reserved2690;	//0xC4502AB0
	UINT32                                                 reserved2691;	//0xC4502AB4
	UINT32                                                 reserved2692;	//0xC4502AB8
	UINT32                                                 reserved2693;	//0xC4502ABC
	UINT32                                                 reserved2694;	//0xC4502AC0
	UINT32                                                 reserved2695;	//0xC4502AC4
	UINT32                                                 reserved2696;	//0xC4502AC8
	UINT32                                                 reserved2697;	//0xC4502ACC
	UINT32                                                 reserved2698;	//0xC4502AD0
	UINT32                                                 reserved2699;	//0xC4502AD4
	UINT32                                                 reserved2700;	//0xC4502AD8
	UINT32                                                 reserved2701;	//0xC4502ADC
	UINT32                                                 reserved2702;	//0xC4502AE0
	UINT32                                                 reserved2703;	//0xC4502AE4
	UINT32                                                 reserved2704;	//0xC4502AE8
	UINT32                                                 reserved2705;	//0xC4502AEC
	UINT32                                                 reserved2706;	//0xC4502AF0
	UINT32                                                 reserved2707;	//0xC4502AF4
	UINT32                                                 reserved2708;	//0xC4502AF8
	UINT32                                                 reserved2709;	//0xC4502AFC
	UINT32                                                 reserved2710;	//0xC4502B00
	UINT32                                                 reserved2711;	//0xC4502B04
	UINT32                                                 reserved2712;	//0xC4502B08
	UINT32                                                 reserved2713;	//0xC4502B0C
	UINT32                                                 reserved2714;	//0xC4502B10
	UINT32                                                 reserved2715;	//0xC4502B14
	UINT32                                                 reserved2716;	//0xC4502B18
	UINT32                                                 reserved2717;	//0xC4502B1C
	UINT32                                                 reserved2718;	//0xC4502B20
	UINT32                                                 reserved2719;	//0xC4502B24
	UINT32                                                 reserved2720;	//0xC4502B28
	UINT32                                                 reserved2721;	//0xC4502B2C
	UINT32                                                 reserved2722;	//0xC4502B30
	UINT32                                                 reserved2723;	//0xC4502B34
	UINT32                                                 reserved2724;	//0xC4502B38
	UINT32                                                 reserved2725;	//0xC4502B3C
	UINT32                                                 reserved2726;	//0xC4502B40
	UINT32                                                 reserved2727;	//0xC4502B44
	UINT32                                                 reserved2728;	//0xC4502B48
	UINT32                                                 reserved2729;	//0xC4502B4C
	UINT32                                                 reserved2730;	//0xC4502B50
	UINT32                                                 reserved2731;	//0xC4502B54
	UINT32                                                 reserved2732;	//0xC4502B58
	UINT32                                                 reserved2733;	//0xC4502B5C
	UINT32                                                 reserved2734;	//0xC4502B60
	UINT32                                                 reserved2735;	//0xC4502B64
	UINT32                                                 reserved2736;	//0xC4502B68
	UINT32                                                 reserved2737;	//0xC4502B6C
	UINT32                                                 reserved2738;	//0xC4502B70
	UINT32                                                 reserved2739;	//0xC4502B74
	UINT32                                                 reserved2740;	//0xC4502B78
	UINT32                                                 reserved2741;	//0xC4502B7C
	UINT32                                                 reserved2742;	//0xC4502B80
	UINT32                                                 reserved2743;	//0xC4502B84
	UINT32                                                 reserved2744;	//0xC4502B88
	UINT32                                                 reserved2745;	//0xC4502B8C
	UINT32                                                 reserved2746;	//0xC4502B90
	UINT32                                                 reserved2747;	//0xC4502B94
	UINT32                                                 reserved2748;	//0xC4502B98
	UINT32                                                 reserved2749;	//0xC4502B9C
	UINT32                                                 reserved2750;	//0xC4502BA0
	UINT32                                                 reserved2751;	//0xC4502BA4
	UINT32                                                 reserved2752;	//0xC4502BA8
	UINT32                                                 reserved2753;	//0xC4502BAC
	UINT32                                                 reserved2754;	//0xC4502BB0
	UINT32                                                 reserved2755;	//0xC4502BB4
	UINT32                                                 reserved2756;	//0xC4502BB8
	UINT32                                                 reserved2757;	//0xC4502BBC
	UINT32                                                 reserved2758;	//0xC4502BC0
	UINT32                                                 reserved2759;	//0xC4502BC4
	UINT32                                                 reserved2760;	//0xC4502BC8
	UINT32                                                 reserved2761;	//0xC4502BCC
	UINT32                                                 reserved2762;	//0xC4502BD0
	UINT32                                                 reserved2763;	//0xC4502BD4
	UINT32                                                 reserved2764;	//0xC4502BD8
	UINT32                                                 reserved2765;	//0xC4502BDC
	UINT32                                                 reserved2766;	//0xC4502BE0
	UINT32                                                 reserved2767;	//0xC4502BE4
	UINT32                                                 reserved2768;	//0xC4502BE8
	UINT32                                                 reserved2769;	//0xC4502BEC
	UINT32                                                 reserved2770;	//0xC4502BF0
	UINT32                                                 reserved2771;	//0xC4502BF4
	UINT32                                                 reserved2772;	//0xC4502BF8
	UINT32                                                 reserved2773;	//0xC4502BFC
	UINT32                                                 reserved2774;	//0xC4502C00
	UINT32                                                 reserved2775;	//0xC4502C04
	UINT32                                                 reserved2776;	//0xC4502C08
	UINT32                                                 reserved2777;	//0xC4502C0C
	UINT32                                                 reserved2778;	//0xC4502C10
	UINT32                                                 reserved2779;	//0xC4502C14
	UINT32                                                 reserved2780;	//0xC4502C18
	UINT32                                                 reserved2781;	//0xC4502C1C
	UINT32                                                 reserved2782;	//0xC4502C20
	UINT32                                                 reserved2783;	//0xC4502C24
	UINT32                                                 reserved2784;	//0xC4502C28
	UINT32                                                 reserved2785;	//0xC4502C2C
	UINT32                                                 reserved2786;	//0xC4502C30
	UINT32                                                 reserved2787;	//0xC4502C34
	UINT32                                                 reserved2788;	//0xC4502C38
	UINT32                                                 reserved2789;	//0xC4502C3C
	UINT32                                                 reserved2790;	//0xC4502C40
	UINT32                                                 reserved2791;	//0xC4502C44
	UINT32                                                 reserved2792;	//0xC4502C48
	UINT32                                                 reserved2793;	//0xC4502C4C
	UINT32                                                 reserved2794;	//0xC4502C50
	UINT32                                                 reserved2795;	//0xC4502C54
	UINT32                                                 reserved2796;	//0xC4502C58
	UINT32                                                 reserved2797;	//0xC4502C5C
	UINT32                                                 reserved2798;	//0xC4502C60
	UINT32                                                 reserved2799;	//0xC4502C64
	UINT32                                                 reserved2800;	//0xC4502C68
	UINT32                                                 reserved2801;	//0xC4502C6C
	UINT32                                                 reserved2802;	//0xC4502C70
	UINT32                                                 reserved2803;	//0xC4502C74
	UINT32                                                 reserved2804;	//0xC4502C78
	UINT32                                                 reserved2805;	//0xC4502C7C
	UINT32                                                 reserved2806;	//0xC4502C80
	UINT32                                                 reserved2807;	//0xC4502C84
	UINT32                                                 reserved2808;	//0xC4502C88
	UINT32                                                 reserved2809;	//0xC4502C8C
	UINT32                                                 reserved2810;	//0xC4502C90
	UINT32                                                 reserved2811;	//0xC4502C94
	UINT32                                                 reserved2812;	//0xC4502C98
	UINT32                                                 reserved2813;	//0xC4502C9C
	UINT32                                                 reserved2814;	//0xC4502CA0
	UINT32                                                 reserved2815;	//0xC4502CA4
	UINT32                                                 reserved2816;	//0xC4502CA8
	UINT32                                                 reserved2817;	//0xC4502CAC
	UINT32                                                 reserved2818;	//0xC4502CB0
	UINT32                                                 reserved2819;	//0xC4502CB4
	UINT32                                                 reserved2820;	//0xC4502CB8
	UINT32                                                 reserved2821;	//0xC4502CBC
	UINT32                                                 reserved2822;	//0xC4502CC0
	UINT32                                                 reserved2823;	//0xC4502CC4
	UINT32                                                 reserved2824;	//0xC4502CC8
	UINT32                                                 reserved2825;	//0xC4502CCC
	UINT32                                                 reserved2826;	//0xC4502CD0
	UINT32                                                 reserved2827;	//0xC4502CD4
	UINT32                                                 reserved2828;	//0xC4502CD8
	UINT32                                                 reserved2829;	//0xC4502CDC
	UINT32                                                 reserved2830;	//0xC4502CE0
	UINT32                                                 reserved2831;	//0xC4502CE4
	UINT32                                                 reserved2832;	//0xC4502CE8
	UINT32                                                 reserved2833;	//0xC4502CEC
	UINT32                                                 reserved2834;	//0xC4502CF0
	UINT32                                                 reserved2835;	//0xC4502CF4
	UINT32                                                 reserved2836;	//0xC4502CF8
	UINT32                                                 reserved2837;	//0xC4502CFC
	UINT32                                                 reserved2838;	//0xC4502D00
	UINT32                                                 reserved2839;	//0xC4502D04
	UINT32                                                 reserved2840;	//0xC4502D08
	UINT32                                                 reserved2841;	//0xC4502D0C
	UINT32                                                 reserved2842;	//0xC4502D10
	UINT32                                                 reserved2843;	//0xC4502D14
	UINT32                                                 reserved2844;	//0xC4502D18
	UINT32                                                 reserved2845;	//0xC4502D1C
	UINT32                                                 reserved2846;	//0xC4502D20
	UINT32                                                 reserved2847;	//0xC4502D24
	UINT32                                                 reserved2848;	//0xC4502D28
	UINT32                                                 reserved2849;	//0xC4502D2C
	UINT32                                                 reserved2850;	//0xC4502D30
	UINT32                                                 reserved2851;	//0xC4502D34
	UINT32                                                 reserved2852;	//0xC4502D38
	UINT32                                                 reserved2853;	//0xC4502D3C
	UINT32                                                 reserved2854;	//0xC4502D40
	UINT32                                                 reserved2855;	//0xC4502D44
	UINT32                                                 reserved2856;	//0xC4502D48
	UINT32                                                 reserved2857;	//0xC4502D4C
	UINT32                                                 reserved2858;	//0xC4502D50
	UINT32                                                 reserved2859;	//0xC4502D54
	UINT32                                                 reserved2860;	//0xC4502D58
	UINT32                                                 reserved2861;	//0xC4502D5C
	UINT32                                                 reserved2862;	//0xC4502D60
	UINT32                                                 reserved2863;	//0xC4502D64
	UINT32                                                 reserved2864;	//0xC4502D68
	UINT32                                                 reserved2865;	//0xC4502D6C
	UINT32                                                 reserved2866;	//0xC4502D70
	UINT32                                                 reserved2867;	//0xC4502D74
	UINT32                                                 reserved2868;	//0xC4502D78
	UINT32                                                 reserved2869;	//0xC4502D7C
	UINT32                                                 reserved2870;	//0xC4502D80
	UINT32                                                 reserved2871;	//0xC4502D84
	UINT32                                                 reserved2872;	//0xC4502D88
	UINT32                                                 reserved2873;	//0xC4502D8C
	UINT32                                                 reserved2874;	//0xC4502D90
	UINT32                                                 reserved2875;	//0xC4502D94
	UINT32                                                 reserved2876;	//0xC4502D98
	UINT32                                                 reserved2877;	//0xC4502D9C
	UINT32                                                 reserved2878;	//0xC4502DA0
	UINT32                                                 reserved2879;	//0xC4502DA4
	UINT32                                                 reserved2880;	//0xC4502DA8
	UINT32                                                 reserved2881;	//0xC4502DAC
	UINT32                                                 reserved2882;	//0xC4502DB0
	UINT32                                                 reserved2883;	//0xC4502DB4
	UINT32                                                 reserved2884;	//0xC4502DB8
	UINT32                                                 reserved2885;	//0xC4502DBC
	UINT32                                                 reserved2886;	//0xC4502DC0
	UINT32                                                 reserved2887;	//0xC4502DC4
	UINT32                                                 reserved2888;	//0xC4502DC8
	UINT32                                                 reserved2889;	//0xC4502DCC
	UINT32                                                 reserved2890;	//0xC4502DD0
	UINT32                                                 reserved2891;	//0xC4502DD4
	UINT32                                                 reserved2892;	//0xC4502DD8
	UINT32                                                 reserved2893;	//0xC4502DDC
	UINT32                                                 reserved2894;	//0xC4502DE0
	UINT32                                                 reserved2895;	//0xC4502DE4
	UINT32                                                 reserved2896;	//0xC4502DE8
	UINT32                                                 reserved2897;	//0xC4502DEC
	UINT32                                                 reserved2898;	//0xC4502DF0
	UINT32                                                 reserved2899;	//0xC4502DF4
	UINT32                                                 reserved2900;	//0xC4502DF8
	UINT32                                                 reserved2901;	//0xC4502DFC
	UINT32                                                 reserved2902;	//0xC4502E00
	UINT32                                                 reserved2903;	//0xC4502E04
	UINT32                                                 reserved2904;	//0xC4502E08
	UINT32                                                 reserved2905;	//0xC4502E0C
	UINT32                                                 reserved2906;	//0xC4502E10
	UINT32                                                 reserved2907;	//0xC4502E14
	UINT32                                                 reserved2908;	//0xC4502E18
	UINT32                                                 reserved2909;	//0xC4502E1C
	UINT32                                                 reserved2910;	//0xC4502E20
	UINT32                                                 reserved2911;	//0xC4502E24
	UINT32                                                 reserved2912;	//0xC4502E28
	UINT32                                                 reserved2913;	//0xC4502E2C
	UINT32                                                 reserved2914;	//0xC4502E30
	UINT32                                                 reserved2915;	//0xC4502E34
	UINT32                                                 reserved2916;	//0xC4502E38
	UINT32                                                 reserved2917;	//0xC4502E3C
	UINT32                                                 reserved2918;	//0xC4502E40
	UINT32                                                 reserved2919;	//0xC4502E44
	UINT32                                                 reserved2920;	//0xC4502E48
	UINT32                                                 reserved2921;	//0xC4502E4C
	UINT32                                                 reserved2922;	//0xC4502E50
	UINT32                                                 reserved2923;	//0xC4502E54
	UINT32                                                 reserved2924;	//0xC4502E58
	UINT32                                                 reserved2925;	//0xC4502E5C
	UINT32                                                 reserved2926;	//0xC4502E60
	UINT32                                                 reserved2927;	//0xC4502E64
	UINT32                                                 reserved2928;	//0xC4502E68
	UINT32                                                 reserved2929;	//0xC4502E6C
	UINT32                                                 reserved2930;	//0xC4502E70
	UINT32                                                 reserved2931;	//0xC4502E74
	UINT32                                                 reserved2932;	//0xC4502E78
	UINT32                                                 reserved2933;	//0xC4502E7C
	UINT32                                                 reserved2934;	//0xC4502E80
	UINT32                                                 reserved2935;	//0xC4502E84
	UINT32                                                 reserved2936;	//0xC4502E88
	UINT32                                                 reserved2937;	//0xC4502E8C
	UINT32                                                 reserved2938;	//0xC4502E90
	UINT32                                                 reserved2939;	//0xC4502E94
	UINT32                                                 reserved2940;	//0xC4502E98
	UINT32                                                 reserved2941;	//0xC4502E9C
	UINT32                                                 reserved2942;	//0xC4502EA0
	UINT32                                                 reserved2943;	//0xC4502EA4
	UINT32                                                 reserved2944;	//0xC4502EA8
	UINT32                                                 reserved2945;	//0xC4502EAC
	UINT32                                                 reserved2946;	//0xC4502EB0
	UINT32                                                 reserved2947;	//0xC4502EB4
	UINT32                                                 reserved2948;	//0xC4502EB8
	UINT32                                                 reserved2949;	//0xC4502EBC
	UINT32                                                 reserved2950;	//0xC4502EC0
	UINT32                                                 reserved2951;	//0xC4502EC4
	UINT32                                                 reserved2952;	//0xC4502EC8
	UINT32                                                 reserved2953;	//0xC4502ECC
	UINT32                                                 reserved2954;	//0xC4502ED0
	UINT32                                                 reserved2955;	//0xC4502ED4
	UINT32                                                 reserved2956;	//0xC4502ED8
	UINT32                                                 reserved2957;	//0xC4502EDC
	UINT32                                                 reserved2958;	//0xC4502EE0
	UINT32                                                 reserved2959;	//0xC4502EE4
	UINT32                                                 reserved2960;	//0xC4502EE8
	UINT32                                                 reserved2961;	//0xC4502EEC
	UINT32                                                 reserved2962;	//0xC4502EF0
	UINT32                                                 reserved2963;	//0xC4502EF4
	UINT32                                                 reserved2964;	//0xC4502EF8
	UINT32                                                 reserved2965;	//0xC4502EFC
	UINT32                                                 reserved2966;	//0xC4502F00
	UINT32                                                 reserved2967;	//0xC4502F04
	UINT32                                                 reserved2968;	//0xC4502F08
	UINT32                                                 reserved2969;	//0xC4502F0C
	UINT32                                                 reserved2970;	//0xC4502F10
	UINT32                                                 reserved2971;	//0xC4502F14
	UINT32                                                 reserved2972;	//0xC4502F18
	UINT32                                                 reserved2973;	//0xC4502F1C
	UINT32                                                 reserved2974;	//0xC4502F20
	UINT32                                                 reserved2975;	//0xC4502F24
	UINT32                                                 reserved2976;	//0xC4502F28
	UINT32                                                 reserved2977;	//0xC4502F2C
	UINT32                                                 reserved2978;	//0xC4502F30
	UINT32                                                 reserved2979;	//0xC4502F34
	UINT32                                                 reserved2980;	//0xC4502F38
	UINT32                                                 reserved2981;	//0xC4502F3C
	UINT32                                                 reserved2982;	//0xC4502F40
	UINT32                                                 reserved2983;	//0xC4502F44
	UINT32                                                 reserved2984;	//0xC4502F48
	UINT32                                                 reserved2985;	//0xC4502F4C
	UINT32                                                 reserved2986;	//0xC4502F50
	UINT32                                                 reserved2987;	//0xC4502F54
	UINT32                                                 reserved2988;	//0xC4502F58
	UINT32                                                 reserved2989;	//0xC4502F5C
	UINT32                                                 reserved2990;	//0xC4502F60
	UINT32                                                 reserved2991;	//0xC4502F64
	UINT32                                                 reserved2992;	//0xC4502F68
	UINT32                                                 reserved2993;	//0xC4502F6C
	UINT32                                                 reserved2994;	//0xC4502F70
	UINT32                                                 reserved2995;	//0xC4502F74
	UINT32                                                 reserved2996;	//0xC4502F78
	UINT32                                                 reserved2997;	//0xC4502F7C
	UINT32                                                 reserved2998;	//0xC4502F80
	UINT32                                                 reserved2999;	//0xC4502F84
	UINT32                                                 reserved3000;	//0xC4502F88
	UINT32                                                 reserved3001;	//0xC4502F8C
	UINT32                                                 reserved3002;	//0xC4502F90
	UINT32                                                 reserved3003;	//0xC4502F94
	UINT32                                                 reserved3004;	//0xC4502F98
	UINT32                                                 reserved3005;	//0xC4502F9C
	UINT32                                                 reserved3006;	//0xC4502FA0
	UINT32                                                 reserved3007;	//0xC4502FA4
	UINT32                                                 reserved3008;	//0xC4502FA8
	UINT32                                                 reserved3009;	//0xC4502FAC
	UINT32                                                 reserved3010;	//0xC4502FB0
	UINT32                                                 reserved3011;	//0xC4502FB4
	UINT32                                                 reserved3012;	//0xC4502FB8
	UINT32                                                 reserved3013;	//0xC4502FBC
	UINT32                                                 reserved3014;	//0xC4502FC0
	UINT32                                                 reserved3015;	//0xC4502FC4
	UINT32                                                 reserved3016;	//0xC4502FC8
	UINT32                                                 reserved3017;	//0xC4502FCC
	UINT32                                                 reserved3018;	//0xC4502FD0
	UINT32                                                 reserved3019;	//0xC4502FD4
	UINT32                                                 reserved3020;	//0xC4502FD8
	UINT32                                                 reserved3021;	//0xC4502FDC
	UINT32                                                 reserved3022;	//0xC4502FE0
	UINT32                                                 reserved3023;	//0xC4502FE4
	UINT32                                                 reserved3024;	//0xC4502FE8
	UINT32                                                 reserved3025;	//0xC4502FEC
	UINT32                                                 reserved3026;	//0xC4502FF0
	UINT32                                                 reserved3027;	//0xC4502FF4
	UINT32                                                 reserved3028;	//0xC4502FF8
	UINT32                                                 reserved3029;	//0xC4502FFC
	REG_DDRC_M2_LPD4_MAIN_FSM_INIT_0_T             lpd4_main_fsm_init_0;	//0xC4503000
	REG_DDRC_M2_LPD4_MAIN_FSM_INIT_1_T             lpd4_main_fsm_init_1;	//0xC4503004
	REG_DDRC_M2_LPD4_MAIN_FSM_INIT_2_T             lpd4_main_fsm_init_2;	//0xC4503008
	REG_DDRC_M2_LPD4_MAIN_FSM_CTRL_T                 lpd4_main_fsm_ctrl;	//0xC450300C
	REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_0_T     lpd4_main_fsm_dir_ctrl_0;	//0xC4503010
	REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_1_T     lpd4_main_fsm_dir_ctrl_1;	//0xC4503014
	REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_2_T     lpd4_main_fsm_dir_ctrl_2;	//0xC4503018
	REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_3_T     lpd4_main_fsm_dir_ctrl_3;	//0xC450301C
	REG_DDRC_M2_LPD4_MAIN_FSM_DIR_CTRL_4_T     lpd4_main_fsm_dir_ctrl_4;	//0xC4503020
	REG_DDRC_M2_LPD4_MAIN_FSM_DFS_MRW_T           lpd4_main_fsm_dfs_mrw;	//0xC4503024
	REG_DDRC_M2_LPD4_MAIN_FSM_CTRLUPD_T           lpd4_main_fsm_ctrlupd;	//0xC4503028
	REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_0_T     lpd4_main_fsm_mpc_fifo_0;	//0xC450302C
	REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_1_T     lpd4_main_fsm_mpc_fifo_1;	//0xC4503030
	REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_2_T     lpd4_main_fsm_mpc_fifo_2;	//0xC4503034
	REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_3_T     lpd4_main_fsm_mpc_fifo_3;	//0xC4503038
	REG_DDRC_M2_LPD4_MAIN_FSM_MPC_FIFO_4_T     lpd4_main_fsm_mpc_fifo_4;	//0xC450303C
	UINT32                                                 reserved3030;	//0xC4503040
	UINT32                                                 reserved3031;	//0xC4503044
	UINT32                                                 reserved3032;	//0xC4503048
	UINT32                                                 reserved3033;	//0xC450304C
	REG_DDRC_M2_LPD4_MR_CTRL_0_T                         lpd4_mr_ctrl_0;	//0xC4503050
	REG_DDRC_M2_LPD4_MR_CTRL_1_T                         lpd4_mr_ctrl_1;	//0xC4503054
	REG_DDRC_M2_LPD4_MR_CTRL_2_T                         lpd4_mr_ctrl_2;	//0xC4503058
	UINT32                                                 reserved3034;	//0xC450305C
	REG_DDRC_M2_LPD4_REF_REQ_CTRL_T                   lpd4_ref_req_ctrl;	//0xC4503060
	UINT32                                                 reserved3035;	//0xC4503064
	UINT32                                                 reserved3036;	//0xC4503068
	UINT32                                                 reserved3037;	//0xC450306C
	REG_DDRC_M2_LPD4_REF_CTRL_T                           lpd4_ref_ctrl;	//0xC4503070
	UINT32                                                 reserved3038;	//0xC4503074
	UINT32                                                 reserved3039;	//0xC4503078
	UINT32                                                 reserved3040;	//0xC450307C
	REG_DDRC_M2_LPD4_BANK_FSM_T                           lpd4_bank_fsm;	//0xC4503080
	UINT32                                                 reserved3041;	//0xC4503084
	UINT32                                                 reserved3042;	//0xC4503088
	UINT32                                                 reserved3043;	//0xC450308C
	UINT32                                                 reserved3044;	//0xC4503090
	UINT32                                                 reserved3045;	//0xC4503094
	UINT32                                                 reserved3046;	//0xC4503098
	UINT32                                                 reserved3047;	//0xC450309C
	REG_DDRC_M2_LPD4_BANK_STATUS_T                     lpd4_bank_status;	//0xC45030A0
	UINT32                                                 reserved3048;	//0xC45030A4
	UINT32                                                 reserved3049;	//0xC45030A8
	UINT32                                                 reserved3050;	//0xC45030AC
	UINT32                                                 reserved3051;	//0xC45030B0
	UINT32                                                 reserved3052;	//0xC45030B4
	UINT32                                                 reserved3053;	//0xC45030B8
	UINT32                                                 reserved3054;	//0xC45030BC
	REG_DDRC_M2_LPD4_PHY_IF_T                               lpd4_phy_if;	//0xC45030C0
	UINT32                                                 reserved3055;	//0xC45030C4
	UINT32                                                 reserved3056;	//0xC45030C8
	UINT32                                                 reserved3057;	//0xC45030CC
	UINT32                                                 reserved3058;	//0xC45030D0
	UINT32                                                 reserved3059;	//0xC45030D4
	UINT32                                                 reserved3060;	//0xC45030D8
	UINT32                                                 reserved3061;	//0xC45030DC
	UINT32                                                 reserved3062;	//0xC45030E0
	UINT32                                                 reserved3063;	//0xC45030E4
	UINT32                                                 reserved3064;	//0xC45030E8
	UINT32                                                 reserved3065;	//0xC45030EC
	UINT32                                                 reserved3066;	//0xC45030F0
	UINT32                                                 reserved3067;	//0xC45030F4
	UINT32                                                 reserved3068;	//0xC45030F8
	UINT32                                                 reserved3069;	//0xC45030FC
	REG_DDRC_M2_LPD4_DFS0_MR_0_CH0_T                 lpd4_dfs0_mr_0_ch0;	//0xC4503100
	REG_DDRC_M2_LPD4_DFS0_MR_1_CH0_T                 lpd4_dfs0_mr_1_ch0;	//0xC4503104
	REG_DDRC_M2_LPD4_DFS0_MR_2_CH0_T                 lpd4_dfs0_mr_2_ch0;	//0xC4503108
	REG_DDRC_M2_LPD4_DFS0_MR_3_CH0_T                 lpd4_dfs0_mr_3_ch0;	//0xC450310C
	REG_DDRC_M2_LPD4_DFS0_MR_4_CH0_T                 lpd4_dfs0_mr_4_ch0;	//0xC4503110
	REG_DDRC_M2_LPD4_DFS0_MR_5_CH0_T                 lpd4_dfs0_mr_5_ch0;	//0xC4503114
	REG_DDRC_M2_LPD4_DFS0_MR_6_CH0_T                 lpd4_dfs0_mr_6_ch0;	//0xC4503118
	UINT32                                                 reserved3070;	//0xC450311C
	REG_DDRC_M2_LPD4_DFS0_MR_0_CH1_T                 lpd4_dfs0_mr_0_ch1;	//0xC4503120
	REG_DDRC_M2_LPD4_DFS0_MR_1_CH1_T                 lpd4_dfs0_mr_1_ch1;	//0xC4503124
	REG_DDRC_M2_LPD4_DFS0_MR_2_CH1_T                 lpd4_dfs0_mr_2_ch1;	//0xC4503128
	REG_DDRC_M2_LPD4_DFS0_MR_3_CH1_T                 lpd4_dfs0_mr_3_ch1;	//0xC450312C
	REG_DDRC_M2_LPD4_DFS0_MR_4_CH1_T                 lpd4_dfs0_mr_4_ch1;	//0xC4503130
	REG_DDRC_M2_LPD4_DFS0_MR_5_CH1_T                 lpd4_dfs0_mr_5_ch1;	//0xC4503134
	REG_DDRC_M2_LPD4_DFS0_MR_6_CH1_T                 lpd4_dfs0_mr_6_ch1;	//0xC4503138
	UINT32                                                 reserved3071;	//0xC450313C
	REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_0_T             lpd4_dfs0_main_fsm_0;	//0xC4503140
	REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_1_T             lpd4_dfs0_main_fsm_1;	//0xC4503144
	REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_2_T             lpd4_dfs0_main_fsm_2;	//0xC4503148
	REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_3_T             lpd4_dfs0_main_fsm_3;	//0xC450314C
	REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_4_T             lpd4_dfs0_main_fsm_4;	//0xC4503150
	REG_DDRC_M2_LPD4_DFS0_MAIN_FSM_5_T             lpd4_dfs0_main_fsm_5;	//0xC4503154
	UINT32                                                 reserved3072;	//0xC4503158
	UINT32                                                 reserved3073;	//0xC450315C
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_0_T     lpd4_dfs0_ref_req_ctrl_0;	//0xC4503160
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_1_T     lpd4_dfs0_ref_req_ctrl_1;	//0xC4503164
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_2_T     lpd4_dfs0_ref_req_ctrl_2;	//0xC4503168
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_3_T     lpd4_dfs0_ref_req_ctrl_3;	//0xC450316C
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_4_T     lpd4_dfs0_ref_req_ctrl_4;	//0xC4503170
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_5_T     lpd4_dfs0_ref_req_ctrl_5;	//0xC4503174
	REG_DDRC_M2_LPD4_DFS0_REF_REQ_CTRL_6_T     lpd4_dfs0_ref_req_ctrl_6;	//0xC4503178
	UINT32                                                 reserved3074;	//0xC450317C
	UINT32                                                 reserved3075;	//0xC4503180
	UINT32                                                 reserved3076;	//0xC4503184
	UINT32                                                 reserved3077;	//0xC4503188
	UINT32                                                 reserved3078;	//0xC450318C
	REG_DDRC_M2_LPD4_DFS0_REF_CTRL_T                 lpd4_dfs0_ref_ctrl;	//0xC4503190
	UINT32                                                 reserved3079;	//0xC4503194
	UINT32                                                 reserved3080;	//0xC4503198
	UINT32                                                 reserved3081;	//0xC450319C
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_0_T       lpd4_dfs0_bank_status_0;	//0xC45031A0
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_1_T       lpd4_dfs0_bank_status_1;	//0xC45031A4
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_2_T       lpd4_dfs0_bank_status_2;	//0xC45031A8
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_3_T       lpd4_dfs0_bank_status_3;	//0xC45031AC
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_4_T       lpd4_dfs0_bank_status_4;	//0xC45031B0
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_5_T       lpd4_dfs0_bank_status_5;	//0xC45031B4
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_6_T       lpd4_dfs0_bank_status_6;	//0xC45031B8
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_7_T       lpd4_dfs0_bank_status_7;	//0xC45031BC
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_8_T       lpd4_dfs0_bank_status_8;	//0xC45031C0
	REG_DDRC_M2_LPD4_DFS0_BANK_STATUS_9_T       lpd4_dfs0_bank_status_9;	//0xC45031C4
	UINT32                                                 reserved3082;	//0xC45031C8
	UINT32                                                 reserved3083;	//0xC45031CC
	UINT32                                                 reserved3084;	//0xC45031D0
	UINT32                                                 reserved3085;	//0xC45031D4
	UINT32                                                 reserved3086;	//0xC45031D8
	UINT32                                                 reserved3087;	//0xC45031DC
	REG_DDRC_M2_LPD4_DFS0_PHY_IF_T                     lpd4_dfs0_phy_if;	//0xC45031E0
	UINT32                                                 reserved3088;	//0xC45031E4
	UINT32                                                 reserved3089;	//0xC45031E8
	UINT32                                                 reserved3090;	//0xC45031EC
	UINT32                                                 reserved3091;	//0xC45031F0
	UINT32                                                 reserved3092;	//0xC45031F4
	UINT32                                                 reserved3093;	//0xC45031F8
	UINT32                                                 reserved3094;	//0xC45031FC
	REG_DDRC_M2_LPD4_DFS1_MR_0_CH0_T                 lpd4_dfs1_mr_0_ch0;	//0xC4503200
	REG_DDRC_M2_LPD4_DFS1_MR_1_CH0_T                 lpd4_dfs1_mr_1_ch0;	//0xC4503204
	REG_DDRC_M2_LPD4_DFS1_MR_2_CH0_T                 lpd4_dfs1_mr_2_ch0;	//0xC4503208
	REG_DDRC_M2_LPD4_DFS1_MR_3_CH0_T                 lpd4_dfs1_mr_3_ch0;	//0xC450320C
	REG_DDRC_M2_LPD4_DFS1_MR_4_CH0_T                 lpd4_dfs1_mr_4_ch0;	//0xC4503210
	REG_DDRC_M2_LPD4_DFS1_MR_5_CH0_T                 lpd4_dfs1_mr_5_ch0;	//0xC4503214
	REG_DDRC_M2_LPD4_DFS1_MR_6_CH0_T                 lpd4_dfs1_mr_6_ch0;	//0xC4503218
	UINT32                                                 reserved3095;	//0xC450321C
	REG_DDRC_M2_LPD4_DFS1_MR_0_CH1_T                 lpd4_dfs1_mr_0_ch1;	//0xC4503220
	REG_DDRC_M2_LPD4_DFS1_MR_1_CH1_T                 lpd4_dfs1_mr_1_ch1;	//0xC4503224
	REG_DDRC_M2_LPD4_DFS1_MR_2_CH1_T                 lpd4_dfs1_mr_2_ch1;	//0xC4503228
	REG_DDRC_M2_LPD4_DFS1_MR_3_CH1_T                 lpd4_dfs1_mr_3_ch1;	//0xC450322C
	REG_DDRC_M2_LPD4_DFS1_MR_4_CH1_T                 lpd4_dfs1_mr_4_ch1;	//0xC4503230
	REG_DDRC_M2_LPD4_DFS1_MR_5_CH1_T                 lpd4_dfs1_mr_5_ch1;	//0xC4503234
	REG_DDRC_M2_LPD4_DFS1_MR_6_CH1_T                 lpd4_dfs1_mr_6_ch1;	//0xC4503238
	UINT32                                                 reserved3096;	//0xC450323C
	REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_0_T             lpd4_dfs1_main_fsm_0;	//0xC4503240
	REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_1_T             lpd4_dfs1_main_fsm_1;	//0xC4503244
	REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_2_T             lpd4_dfs1_main_fsm_2;	//0xC4503248
	REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_3_T             lpd4_dfs1_main_fsm_3;	//0xC450324C
	REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_4_T             lpd4_dfs1_main_fsm_4;	//0xC4503250
	REG_DDRC_M2_LPD4_DFS1_MAIN_FSM_5_T             lpd4_dfs1_main_fsm_5;	//0xC4503254
	UINT32                                                 reserved3097;	//0xC4503258
	UINT32                                                 reserved3098;	//0xC450325C
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_0_T     lpd4_dfs1_ref_req_ctrl_0;	//0xC4503260
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_1_T     lpd4_dfs1_ref_req_ctrl_1;	//0xC4503264
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_2_T     lpd4_dfs1_ref_req_ctrl_2;	//0xC4503268
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_3_T     lpd4_dfs1_ref_req_ctrl_3;	//0xC450326C
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_4_T     lpd4_dfs1_ref_req_ctrl_4;	//0xC4503270
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_5_T     lpd4_dfs1_ref_req_ctrl_5;	//0xC4503274
	REG_DDRC_M2_LPD4_DFS1_REF_REQ_CTRL_6_T     lpd4_dfs1_ref_req_ctrl_6;	//0xC4503278
	UINT32                                                 reserved3099;	//0xC450327C
	UINT32                                                 reserved3100;	//0xC4503280
	UINT32                                                 reserved3101;	//0xC4503284
	UINT32                                                 reserved3102;	//0xC4503288
	UINT32                                                 reserved3103;	//0xC450328C
	REG_DDRC_M2_LPD4_DFS1_REF_CTRL_T                 lpd4_dfs1_ref_ctrl;	//0xC4503290
	UINT32                                                 reserved3104;	//0xC4503294
	UINT32                                                 reserved3105;	//0xC4503298
	UINT32                                                 reserved3106;	//0xC450329C
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_0_T       lpd4_dfs1_bank_status_0;	//0xC45032A0
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_1_T       lpd4_dfs1_bank_status_1;	//0xC45032A4
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_2_T       lpd4_dfs1_bank_status_2;	//0xC45032A8
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_3_T       lpd4_dfs1_bank_status_3;	//0xC45032AC
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_4_T       lpd4_dfs1_bank_status_4;	//0xC45032B0
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_5_T       lpd4_dfs1_bank_status_5;	//0xC45032B4
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_6_T       lpd4_dfs1_bank_status_6;	//0xC45032B8
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_7_T       lpd4_dfs1_bank_status_7;	//0xC45032BC
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_8_T       lpd4_dfs1_bank_status_8;	//0xC45032C0
	REG_DDRC_M2_LPD4_DFS1_BANK_STATUS_9_T       lpd4_dfs1_bank_status_9;	//0xC45032C4
	UINT32                                                 reserved3107;	//0xC45032C8
	UINT32                                                 reserved3108;	//0xC45032CC
	UINT32                                                 reserved3109;	//0xC45032D0
	UINT32                                                 reserved3110;	//0xC45032D4
	UINT32                                                 reserved3111;	//0xC45032D8
	UINT32                                                 reserved3112;	//0xC45032DC
	REG_DDRC_M2_LPD4_DFS1_PHY_IF_T                     lpd4_dfs1_phy_if;	//0xC45032E0
	UINT32                                                 reserved3113;	//0xC45032E4
	UINT32                                                 reserved3114;	//0xC45032E8
	UINT32                                                 reserved3115;	//0xC45032EC
	UINT32                                                 reserved3116;	//0xC45032F0
	UINT32                                                 reserved3117;	//0xC45032F4
	UINT32                                                 reserved3118;	//0xC45032F8
	UINT32                                                 reserved3119;	//0xC45032FC
	REG_DDRC_M2_LPD4_DFS2_MR_0_CH0_T                 lpd4_dfs2_mr_0_ch0;	//0xC4503300
	REG_DDRC_M2_LPD4_DFS2_MR_1_CH0_T                 lpd4_dfs2_mr_1_ch0;	//0xC4503304
	REG_DDRC_M2_LPD4_DFS2_MR_2_CH0_T                 lpd4_dfs2_mr_2_ch0;	//0xC4503308
	REG_DDRC_M2_LPD4_DFS2_MR_3_CH0_T                 lpd4_dfs2_mr_3_ch0;	//0xC450330C
	REG_DDRC_M2_LPD4_DFS2_MR_4_CH0_T                 lpd4_dfs2_mr_4_ch0;	//0xC4503310
	REG_DDRC_M2_LPD4_DFS2_MR_5_CH0_T                 lpd4_dfs2_mr_5_ch0;	//0xC4503314
	REG_DDRC_M2_LPD4_DFS2_MR_6_CH0_T                 lpd4_dfs2_mr_6_ch0;	//0xC4503318
	UINT32                                                 reserved3120;	//0xC450331C
	REG_DDRC_M2_LPD4_DFS2_MR_0_CH1_T                 lpd4_dfs2_mr_0_ch1;	//0xC4503320
	REG_DDRC_M2_LPD4_DFS2_MR_1_CH1_T                 lpd4_dfs2_mr_1_ch1;	//0xC4503324
	REG_DDRC_M2_LPD4_DFS2_MR_2_CH1_T                 lpd4_dfs2_mr_2_ch1;	//0xC4503328
	REG_DDRC_M2_LPD4_DFS2_MR_3_CH1_T                 lpd4_dfs2_mr_3_ch1;	//0xC450332C
	REG_DDRC_M2_LPD4_DFS2_MR_4_CH1_T                 lpd4_dfs2_mr_4_ch1;	//0xC4503330
	REG_DDRC_M2_LPD4_DFS2_MR_5_CH1_T                 lpd4_dfs2_mr_5_ch1;	//0xC4503334
	REG_DDRC_M2_LPD4_DFS2_MR_6_CH1_T                 lpd4_dfs2_mr_6_ch1;	//0xC4503338
	UINT32                                                 reserved3121;	//0xC450333C
	REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_0_T             lpd4_dfs2_main_fsm_0;	//0xC4503340
	REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_1_T             lpd4_dfs2_main_fsm_1;	//0xC4503344
	REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_2_T             lpd4_dfs2_main_fsm_2;	//0xC4503348
	REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_3_T             lpd4_dfs2_main_fsm_3;	//0xC450334C
	REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_4_T             lpd4_dfs2_main_fsm_4;	//0xC4503350
	REG_DDRC_M2_LPD4_DFS2_MAIN_FSM_5_T             lpd4_dfs2_main_fsm_5;	//0xC4503354
	UINT32                                                 reserved3122;	//0xC4503358
	UINT32                                                 reserved3123;	//0xC450335C
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_0_T     lpd4_dfs2_ref_req_ctrl_0;	//0xC4503360
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_1_T     lpd4_dfs2_ref_req_ctrl_1;	//0xC4503364
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_2_T     lpd4_dfs2_ref_req_ctrl_2;	//0xC4503368
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_3_T     lpd4_dfs2_ref_req_ctrl_3;	//0xC450336C
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_4_T     lpd4_dfs2_ref_req_ctrl_4;	//0xC4503370
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_5_T     lpd4_dfs2_ref_req_ctrl_5;	//0xC4503374
	REG_DDRC_M2_LPD4_DFS2_REF_REQ_CTRL_6_T     lpd4_dfs2_ref_req_ctrl_6;	//0xC4503378
	UINT32                                                 reserved3124;	//0xC450337C
	UINT32                                                 reserved3125;	//0xC4503380
	UINT32                                                 reserved3126;	//0xC4503384
	UINT32                                                 reserved3127;	//0xC4503388
	UINT32                                                 reserved3128;	//0xC450338C
	REG_DDRC_M2_LPD4_DFS2_REF_CTRL_T                 lpd4_dfs2_ref_ctrl;	//0xC4503390
	UINT32                                                 reserved3129;	//0xC4503394
	UINT32                                                 reserved3130;	//0xC4503398
	UINT32                                                 reserved3131;	//0xC450339C
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_0_T       lpd4_dfs2_bank_status_0;	//0xC45033A0
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_1_T       lpd4_dfs2_bank_status_1;	//0xC45033A4
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_2_T       lpd4_dfs2_bank_status_2;	//0xC45033A8
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_3_T       lpd4_dfs2_bank_status_3;	//0xC45033AC
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_4_T       lpd4_dfs2_bank_status_4;	//0xC45033B0
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_5_T       lpd4_dfs2_bank_status_5;	//0xC45033B4
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_6_T       lpd4_dfs2_bank_status_6;	//0xC45033B8
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_7_T       lpd4_dfs2_bank_status_7;	//0xC45033BC
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_8_T       lpd4_dfs2_bank_status_8;	//0xC45033C0
	REG_DDRC_M2_LPD4_DFS2_BANK_STATUS_9_T       lpd4_dfs2_bank_status_9;	//0xC45033C4
	UINT32                                                 reserved3132;	//0xC45033C8
	UINT32                                                 reserved3133;	//0xC45033CC
	UINT32                                                 reserved3134;	//0xC45033D0
	UINT32                                                 reserved3135;	//0xC45033D4
	UINT32                                                 reserved3136;	//0xC45033D8
	UINT32                                                 reserved3137;	//0xC45033DC
	REG_DDRC_M2_LPD4_DFS2_PHY_IF_T                     lpd4_dfs2_phy_if;	//0xC45033E0
	UINT32                                                 reserved3138;	//0xC45033E4
	UINT32                                                 reserved3139;	//0xC45033E8
	UINT32                                                 reserved3140;	//0xC45033EC
	UINT32                                                 reserved3141;	//0xC45033F0
	UINT32                                                 reserved3142;	//0xC45033F4
	UINT32                                                 reserved3143;	//0xC45033F8
	UINT32                                                 reserved3144;	//0xC45033FC
	UINT32                                                 reserved3145;	//0xC4503400
	UINT32                                                 reserved3146;	//0xC4503404
	UINT32                                                 reserved3147;	//0xC4503408
	UINT32                                                 reserved3148;	//0xC450340C
	UINT32                                                 reserved3149;	//0xC4503410
	UINT32                                                 reserved3150;	//0xC4503414
	UINT32                                                 reserved3151;	//0xC4503418
	UINT32                                                 reserved3152;	//0xC450341C
	UINT32                                                 reserved3153;	//0xC4503420
	UINT32                                                 reserved3154;	//0xC4503424
	UINT32                                                 reserved3155;	//0xC4503428
	UINT32                                                 reserved3156;	//0xC450342C
	UINT32                                                 reserved3157;	//0xC4503430
	UINT32                                                 reserved3158;	//0xC4503434
	UINT32                                                 reserved3159;	//0xC4503438
	UINT32                                                 reserved3160;	//0xC450343C
	UINT32                                                 reserved3161;	//0xC4503440
	UINT32                                                 reserved3162;	//0xC4503444
	UINT32                                                 reserved3163;	//0xC4503448
	UINT32                                                 reserved3164;	//0xC450344C
	UINT32                                                 reserved3165;	//0xC4503450
	UINT32                                                 reserved3166;	//0xC4503454
	UINT32                                                 reserved3167;	//0xC4503458
	UINT32                                                 reserved3168;	//0xC450345C
	UINT32                                                 reserved3169;	//0xC4503460
	UINT32                                                 reserved3170;	//0xC4503464
	UINT32                                                 reserved3171;	//0xC4503468
	UINT32                                                 reserved3172;	//0xC450346C
	UINT32                                                 reserved3173;	//0xC4503470
	UINT32                                                 reserved3174;	//0xC4503474
	UINT32                                                 reserved3175;	//0xC4503478
	UINT32                                                 reserved3176;	//0xC450347C
	UINT32                                                 reserved3177;	//0xC4503480
	UINT32                                                 reserved3178;	//0xC4503484
	UINT32                                                 reserved3179;	//0xC4503488
	UINT32                                                 reserved3180;	//0xC450348C
	UINT32                                                 reserved3181;	//0xC4503490
	UINT32                                                 reserved3182;	//0xC4503494
	UINT32                                                 reserved3183;	//0xC4503498
	UINT32                                                 reserved3184;	//0xC450349C
	UINT32                                                 reserved3185;	//0xC45034A0
	UINT32                                                 reserved3186;	//0xC45034A4
	UINT32                                                 reserved3187;	//0xC45034A8
	UINT32                                                 reserved3188;	//0xC45034AC
	UINT32                                                 reserved3189;	//0xC45034B0
	UINT32                                                 reserved3190;	//0xC45034B4
	UINT32                                                 reserved3191;	//0xC45034B8
	UINT32                                                 reserved3192;	//0xC45034BC
	UINT32                                                 reserved3193;	//0xC45034C0
	UINT32                                                 reserved3194;	//0xC45034C4
	UINT32                                                 reserved3195;	//0xC45034C8
	UINT32                                                 reserved3196;	//0xC45034CC
	UINT32                                                 reserved3197;	//0xC45034D0
	UINT32                                                 reserved3198;	//0xC45034D4
	UINT32                                                 reserved3199;	//0xC45034D8
	UINT32                                                 reserved3200;	//0xC45034DC
	UINT32                                                 reserved3201;	//0xC45034E0
	UINT32                                                 reserved3202;	//0xC45034E4
	UINT32                                                 reserved3203;	//0xC45034E8
	UINT32                                                 reserved3204;	//0xC45034EC
	UINT32                                                 reserved3205;	//0xC45034F0
	UINT32                                                 reserved3206;	//0xC45034F4
	UINT32                                                 reserved3207;	//0xC45034F8
	UINT32                                                 reserved3208;	//0xC45034FC
	UINT32                                                 reserved3209;	//0xC4503500
	UINT32                                                 reserved3210;	//0xC4503504
	UINT32                                                 reserved3211;	//0xC4503508
	UINT32                                                 reserved3212;	//0xC450350C
	UINT32                                                 reserved3213;	//0xC4503510
	UINT32                                                 reserved3214;	//0xC4503514
	UINT32                                                 reserved3215;	//0xC4503518
	UINT32                                                 reserved3216;	//0xC450351C
	UINT32                                                 reserved3217;	//0xC4503520
	UINT32                                                 reserved3218;	//0xC4503524
	UINT32                                                 reserved3219;	//0xC4503528
	UINT32                                                 reserved3220;	//0xC450352C
	UINT32                                                 reserved3221;	//0xC4503530
	UINT32                                                 reserved3222;	//0xC4503534
	UINT32                                                 reserved3223;	//0xC4503538
	UINT32                                                 reserved3224;	//0xC450353C
	UINT32                                                 reserved3225;	//0xC4503540
	UINT32                                                 reserved3226;	//0xC4503544
	UINT32                                                 reserved3227;	//0xC4503548
	UINT32                                                 reserved3228;	//0xC450354C
	UINT32                                                 reserved3229;	//0xC4503550
	UINT32                                                 reserved3230;	//0xC4503554
	UINT32                                                 reserved3231;	//0xC4503558
	UINT32                                                 reserved3232;	//0xC450355C
	UINT32                                                 reserved3233;	//0xC4503560
	UINT32                                                 reserved3234;	//0xC4503564
	UINT32                                                 reserved3235;	//0xC4503568
	UINT32                                                 reserved3236;	//0xC450356C
	UINT32                                                 reserved3237;	//0xC4503570
	UINT32                                                 reserved3238;	//0xC4503574
	UINT32                                                 reserved3239;	//0xC4503578
	UINT32                                                 reserved3240;	//0xC450357C
	UINT32                                                 reserved3241;	//0xC4503580
	UINT32                                                 reserved3242;	//0xC4503584
	UINT32                                                 reserved3243;	//0xC4503588
	UINT32                                                 reserved3244;	//0xC450358C
	UINT32                                                 reserved3245;	//0xC4503590
	UINT32                                                 reserved3246;	//0xC4503594
	UINT32                                                 reserved3247;	//0xC4503598
	UINT32                                                 reserved3248;	//0xC450359C
	UINT32                                                 reserved3249;	//0xC45035A0
	UINT32                                                 reserved3250;	//0xC45035A4
	UINT32                                                 reserved3251;	//0xC45035A8
	UINT32                                                 reserved3252;	//0xC45035AC
	UINT32                                                 reserved3253;	//0xC45035B0
	UINT32                                                 reserved3254;	//0xC45035B4
	UINT32                                                 reserved3255;	//0xC45035B8
	UINT32                                                 reserved3256;	//0xC45035BC
	UINT32                                                 reserved3257;	//0xC45035C0
	UINT32                                                 reserved3258;	//0xC45035C4
	UINT32                                                 reserved3259;	//0xC45035C8
	UINT32                                                 reserved3260;	//0xC45035CC
	UINT32                                                 reserved3261;	//0xC45035D0
	UINT32                                                 reserved3262;	//0xC45035D4
	UINT32                                                 reserved3263;	//0xC45035D8
	UINT32                                                 reserved3264;	//0xC45035DC
	UINT32                                                 reserved3265;	//0xC45035E0
	UINT32                                                 reserved3266;	//0xC45035E4
	UINT32                                                 reserved3267;	//0xC45035E8
	UINT32                                                 reserved3268;	//0xC45035EC
	UINT32                                                 reserved3269;	//0xC45035F0
	UINT32                                                 reserved3270;	//0xC45035F4
	UINT32                                                 reserved3271;	//0xC45035F8
	UINT32                                                 reserved3272;	//0xC45035FC
	UINT32                                                 reserved3273;	//0xC4503600
	UINT32                                                 reserved3274;	//0xC4503604
	UINT32                                                 reserved3275;	//0xC4503608
	UINT32                                                 reserved3276;	//0xC450360C
	UINT32                                                 reserved3277;	//0xC4503610
	UINT32                                                 reserved3278;	//0xC4503614
	UINT32                                                 reserved3279;	//0xC4503618
	UINT32                                                 reserved3280;	//0xC450361C
	UINT32                                                 reserved3281;	//0xC4503620
	UINT32                                                 reserved3282;	//0xC4503624
	UINT32                                                 reserved3283;	//0xC4503628
	UINT32                                                 reserved3284;	//0xC450362C
	UINT32                                                 reserved3285;	//0xC4503630
	UINT32                                                 reserved3286;	//0xC4503634
	UINT32                                                 reserved3287;	//0xC4503638
	UINT32                                                 reserved3288;	//0xC450363C
	UINT32                                                 reserved3289;	//0xC4503640
	UINT32                                                 reserved3290;	//0xC4503644
	UINT32                                                 reserved3291;	//0xC4503648
	UINT32                                                 reserved3292;	//0xC450364C
	UINT32                                                 reserved3293;	//0xC4503650
	UINT32                                                 reserved3294;	//0xC4503654
	UINT32                                                 reserved3295;	//0xC4503658
	UINT32                                                 reserved3296;	//0xC450365C
	UINT32                                                 reserved3297;	//0xC4503660
	UINT32                                                 reserved3298;	//0xC4503664
	UINT32                                                 reserved3299;	//0xC4503668
	UINT32                                                 reserved3300;	//0xC450366C
	UINT32                                                 reserved3301;	//0xC4503670
	UINT32                                                 reserved3302;	//0xC4503674
	UINT32                                                 reserved3303;	//0xC4503678
	UINT32                                                 reserved3304;	//0xC450367C
	UINT32                                                 reserved3305;	//0xC4503680
	UINT32                                                 reserved3306;	//0xC4503684
	UINT32                                                 reserved3307;	//0xC4503688
	UINT32                                                 reserved3308;	//0xC450368C
	UINT32                                                 reserved3309;	//0xC4503690
	UINT32                                                 reserved3310;	//0xC4503694
	UINT32                                                 reserved3311;	//0xC4503698
	UINT32                                                 reserved3312;	//0xC450369C
	UINT32                                                 reserved3313;	//0xC45036A0
	UINT32                                                 reserved3314;	//0xC45036A4
	UINT32                                                 reserved3315;	//0xC45036A8
	UINT32                                                 reserved3316;	//0xC45036AC
	UINT32                                                 reserved3317;	//0xC45036B0
	UINT32                                                 reserved3318;	//0xC45036B4
	UINT32                                                 reserved3319;	//0xC45036B8
	UINT32                                                 reserved3320;	//0xC45036BC
	UINT32                                                 reserved3321;	//0xC45036C0
	UINT32                                                 reserved3322;	//0xC45036C4
	UINT32                                                 reserved3323;	//0xC45036C8
	UINT32                                                 reserved3324;	//0xC45036CC
	UINT32                                                 reserved3325;	//0xC45036D0
	UINT32                                                 reserved3326;	//0xC45036D4
	UINT32                                                 reserved3327;	//0xC45036D8
	UINT32                                                 reserved3328;	//0xC45036DC
	UINT32                                                 reserved3329;	//0xC45036E0
	UINT32                                                 reserved3330;	//0xC45036E4
	UINT32                                                 reserved3331;	//0xC45036E8
	UINT32                                                 reserved3332;	//0xC45036EC
	UINT32                                                 reserved3333;	//0xC45036F0
	UINT32                                                 reserved3334;	//0xC45036F4
	UINT32                                                 reserved3335;	//0xC45036F8
	UINT32                                                 reserved3336;	//0xC45036FC
	UINT32                                                 reserved3337;	//0xC4503700
	UINT32                                                 reserved3338;	//0xC4503704
	UINT32                                                 reserved3339;	//0xC4503708
	UINT32                                                 reserved3340;	//0xC450370C
	UINT32                                                 reserved3341;	//0xC4503710
	UINT32                                                 reserved3342;	//0xC4503714
	UINT32                                                 reserved3343;	//0xC4503718
	UINT32                                                 reserved3344;	//0xC450371C
	UINT32                                                 reserved3345;	//0xC4503720
	UINT32                                                 reserved3346;	//0xC4503724
	UINT32                                                 reserved3347;	//0xC4503728
	UINT32                                                 reserved3348;	//0xC450372C
	UINT32                                                 reserved3349;	//0xC4503730
	UINT32                                                 reserved3350;	//0xC4503734
	UINT32                                                 reserved3351;	//0xC4503738
	UINT32                                                 reserved3352;	//0xC450373C
	UINT32                                                 reserved3353;	//0xC4503740
	UINT32                                                 reserved3354;	//0xC4503744
	UINT32                                                 reserved3355;	//0xC4503748
	UINT32                                                 reserved3356;	//0xC450374C
	UINT32                                                 reserved3357;	//0xC4503750
	UINT32                                                 reserved3358;	//0xC4503754
	UINT32                                                 reserved3359;	//0xC4503758
	UINT32                                                 reserved3360;	//0xC450375C
	UINT32                                                 reserved3361;	//0xC4503760
	UINT32                                                 reserved3362;	//0xC4503764
	UINT32                                                 reserved3363;	//0xC4503768
	UINT32                                                 reserved3364;	//0xC450376C
	UINT32                                                 reserved3365;	//0xC4503770
	UINT32                                                 reserved3366;	//0xC4503774
	UINT32                                                 reserved3367;	//0xC4503778
	UINT32                                                 reserved3368;	//0xC450377C
	UINT32                                                 reserved3369;	//0xC4503780
	UINT32                                                 reserved3370;	//0xC4503784
	UINT32                                                 reserved3371;	//0xC4503788
	UINT32                                                 reserved3372;	//0xC450378C
	UINT32                                                 reserved3373;	//0xC4503790
	UINT32                                                 reserved3374;	//0xC4503794
	UINT32                                                 reserved3375;	//0xC4503798
	UINT32                                                 reserved3376;	//0xC450379C
	UINT32                                                 reserved3377;	//0xC45037A0
	UINT32                                                 reserved3378;	//0xC45037A4
	UINT32                                                 reserved3379;	//0xC45037A8
	UINT32                                                 reserved3380;	//0xC45037AC
	UINT32                                                 reserved3381;	//0xC45037B0
	UINT32                                                 reserved3382;	//0xC45037B4
	UINT32                                                 reserved3383;	//0xC45037B8
	UINT32                                                 reserved3384;	//0xC45037BC
	UINT32                                                 reserved3385;	//0xC45037C0
	UINT32                                                 reserved3386;	//0xC45037C4
	UINT32                                                 reserved3387;	//0xC45037C8
	UINT32                                                 reserved3388;	//0xC45037CC
	UINT32                                                 reserved3389;	//0xC45037D0
	UINT32                                                 reserved3390;	//0xC45037D4
	UINT32                                                 reserved3391;	//0xC45037D8
	UINT32                                                 reserved3392;	//0xC45037DC
	UINT32                                                 reserved3393;	//0xC45037E0
	UINT32                                                 reserved3394;	//0xC45037E4
	UINT32                                                 reserved3395;	//0xC45037E8
	UINT32                                                 reserved3396;	//0xC45037EC
	UINT32                                                 reserved3397;	//0xC45037F0
	UINT32                                                 reserved3398;	//0xC45037F4
	UINT32                                                 reserved3399;	//0xC45037F8
	UINT32                                                 reserved3400;	//0xC45037FC
	UINT32                                                 reserved3401;	//0xC4503800
	UINT32                                                 reserved3402;	//0xC4503804
	UINT32                                                 reserved3403;	//0xC4503808
	UINT32                                                 reserved3404;	//0xC450380C
	UINT32                                                 reserved3405;	//0xC4503810
	UINT32                                                 reserved3406;	//0xC4503814
	UINT32                                                 reserved3407;	//0xC4503818
	UINT32                                                 reserved3408;	//0xC450381C
	UINT32                                                 reserved3409;	//0xC4503820
	UINT32                                                 reserved3410;	//0xC4503824
	UINT32                                                 reserved3411;	//0xC4503828
	UINT32                                                 reserved3412;	//0xC450382C
	UINT32                                                 reserved3413;	//0xC4503830
	UINT32                                                 reserved3414;	//0xC4503834
	UINT32                                                 reserved3415;	//0xC4503838
	UINT32                                                 reserved3416;	//0xC450383C
	UINT32                                                 reserved3417;	//0xC4503840
	UINT32                                                 reserved3418;	//0xC4503844
	UINT32                                                 reserved3419;	//0xC4503848
	UINT32                                                 reserved3420;	//0xC450384C
	UINT32                                                 reserved3421;	//0xC4503850
	UINT32                                                 reserved3422;	//0xC4503854
	UINT32                                                 reserved3423;	//0xC4503858
	UINT32                                                 reserved3424;	//0xC450385C
	UINT32                                                 reserved3425;	//0xC4503860
	UINT32                                                 reserved3426;	//0xC4503864
	UINT32                                                 reserved3427;	//0xC4503868
	UINT32                                                 reserved3428;	//0xC450386C
	UINT32                                                 reserved3429;	//0xC4503870
	UINT32                                                 reserved3430;	//0xC4503874
	UINT32                                                 reserved3431;	//0xC4503878
	UINT32                                                 reserved3432;	//0xC450387C
	UINT32                                                 reserved3433;	//0xC4503880
	UINT32                                                 reserved3434;	//0xC4503884
	UINT32                                                 reserved3435;	//0xC4503888
	UINT32                                                 reserved3436;	//0xC450388C
	UINT32                                                 reserved3437;	//0xC4503890
	UINT32                                                 reserved3438;	//0xC4503894
	UINT32                                                 reserved3439;	//0xC4503898
	UINT32                                                 reserved3440;	//0xC450389C
	UINT32                                                 reserved3441;	//0xC45038A0
	UINT32                                                 reserved3442;	//0xC45038A4
	UINT32                                                 reserved3443;	//0xC45038A8
	UINT32                                                 reserved3444;	//0xC45038AC
	UINT32                                                 reserved3445;	//0xC45038B0
	UINT32                                                 reserved3446;	//0xC45038B4
	UINT32                                                 reserved3447;	//0xC45038B8
	UINT32                                                 reserved3448;	//0xC45038BC
	UINT32                                                 reserved3449;	//0xC45038C0
	UINT32                                                 reserved3450;	//0xC45038C4
	UINT32                                                 reserved3451;	//0xC45038C8
	UINT32                                                 reserved3452;	//0xC45038CC
	UINT32                                                 reserved3453;	//0xC45038D0
	UINT32                                                 reserved3454;	//0xC45038D4
	UINT32                                                 reserved3455;	//0xC45038D8
	UINT32                                                 reserved3456;	//0xC45038DC
	UINT32                                                 reserved3457;	//0xC45038E0
	UINT32                                                 reserved3458;	//0xC45038E4
	UINT32                                                 reserved3459;	//0xC45038E8
	UINT32                                                 reserved3460;	//0xC45038EC
	UINT32                                                 reserved3461;	//0xC45038F0
	UINT32                                                 reserved3462;	//0xC45038F4
	UINT32                                                 reserved3463;	//0xC45038F8
	UINT32                                                 reserved3464;	//0xC45038FC
	UINT32                                                 reserved3465;	//0xC4503900
	UINT32                                                 reserved3466;	//0xC4503904
	UINT32                                                 reserved3467;	//0xC4503908
	UINT32                                                 reserved3468;	//0xC450390C
	UINT32                                                 reserved3469;	//0xC4503910
	UINT32                                                 reserved3470;	//0xC4503914
	UINT32                                                 reserved3471;	//0xC4503918
	UINT32                                                 reserved3472;	//0xC450391C
	UINT32                                                 reserved3473;	//0xC4503920
	UINT32                                                 reserved3474;	//0xC4503924
	UINT32                                                 reserved3475;	//0xC4503928
	UINT32                                                 reserved3476;	//0xC450392C
	UINT32                                                 reserved3477;	//0xC4503930
	UINT32                                                 reserved3478;	//0xC4503934
	UINT32                                                 reserved3479;	//0xC4503938
	UINT32                                                 reserved3480;	//0xC450393C
	UINT32                                                 reserved3481;	//0xC4503940
	UINT32                                                 reserved3482;	//0xC4503944
	UINT32                                                 reserved3483;	//0xC4503948
	UINT32                                                 reserved3484;	//0xC450394C
	UINT32                                                 reserved3485;	//0xC4503950
	UINT32                                                 reserved3486;	//0xC4503954
	UINT32                                                 reserved3487;	//0xC4503958
	UINT32                                                 reserved3488;	//0xC450395C
	UINT32                                                 reserved3489;	//0xC4503960
	UINT32                                                 reserved3490;	//0xC4503964
	UINT32                                                 reserved3491;	//0xC4503968
	UINT32                                                 reserved3492;	//0xC450396C
	UINT32                                                 reserved3493;	//0xC4503970
	UINT32                                                 reserved3494;	//0xC4503974
	UINT32                                                 reserved3495;	//0xC4503978
	UINT32                                                 reserved3496;	//0xC450397C
	UINT32                                                 reserved3497;	//0xC4503980
	UINT32                                                 reserved3498;	//0xC4503984
	UINT32                                                 reserved3499;	//0xC4503988
	UINT32                                                 reserved3500;	//0xC450398C
	UINT32                                                 reserved3501;	//0xC4503990
	UINT32                                                 reserved3502;	//0xC4503994
	UINT32                                                 reserved3503;	//0xC4503998
	UINT32                                                 reserved3504;	//0xC450399C
	UINT32                                                 reserved3505;	//0xC45039A0
	UINT32                                                 reserved3506;	//0xC45039A4
	UINT32                                                 reserved3507;	//0xC45039A8
	UINT32                                                 reserved3508;	//0xC45039AC
	UINT32                                                 reserved3509;	//0xC45039B0
	UINT32                                                 reserved3510;	//0xC45039B4
	UINT32                                                 reserved3511;	//0xC45039B8
	UINT32                                                 reserved3512;	//0xC45039BC
	UINT32                                                 reserved3513;	//0xC45039C0
	UINT32                                                 reserved3514;	//0xC45039C4
	UINT32                                                 reserved3515;	//0xC45039C8
	UINT32                                                 reserved3516;	//0xC45039CC
	UINT32                                                 reserved3517;	//0xC45039D0
	UINT32                                                 reserved3518;	//0xC45039D4
	UINT32                                                 reserved3519;	//0xC45039D8
	UINT32                                                 reserved3520;	//0xC45039DC
	UINT32                                                 reserved3521;	//0xC45039E0
	UINT32                                                 reserved3522;	//0xC45039E4
	UINT32                                                 reserved3523;	//0xC45039E8
	UINT32                                                 reserved3524;	//0xC45039EC
	UINT32                                                 reserved3525;	//0xC45039F0
	UINT32                                                 reserved3526;	//0xC45039F4
	UINT32                                                 reserved3527;	//0xC45039F8
	UINT32                                                 reserved3528;	//0xC45039FC
	UINT32                                                 reserved3529;	//0xC4503A00
	UINT32                                                 reserved3530;	//0xC4503A04
	UINT32                                                 reserved3531;	//0xC4503A08
	UINT32                                                 reserved3532;	//0xC4503A0C
	UINT32                                                 reserved3533;	//0xC4503A10
	UINT32                                                 reserved3534;	//0xC4503A14
	UINT32                                                 reserved3535;	//0xC4503A18
	UINT32                                                 reserved3536;	//0xC4503A1C
	UINT32                                                 reserved3537;	//0xC4503A20
	UINT32                                                 reserved3538;	//0xC4503A24
	UINT32                                                 reserved3539;	//0xC4503A28
	UINT32                                                 reserved3540;	//0xC4503A2C
	UINT32                                                 reserved3541;	//0xC4503A30
	UINT32                                                 reserved3542;	//0xC4503A34
	UINT32                                                 reserved3543;	//0xC4503A38
	UINT32                                                 reserved3544;	//0xC4503A3C
	UINT32                                                 reserved3545;	//0xC4503A40
	UINT32                                                 reserved3546;	//0xC4503A44
	UINT32                                                 reserved3547;	//0xC4503A48
	UINT32                                                 reserved3548;	//0xC4503A4C
	UINT32                                                 reserved3549;	//0xC4503A50
	UINT32                                                 reserved3550;	//0xC4503A54
	UINT32                                                 reserved3551;	//0xC4503A58
	UINT32                                                 reserved3552;	//0xC4503A5C
	UINT32                                                 reserved3553;	//0xC4503A60
	UINT32                                                 reserved3554;	//0xC4503A64
	UINT32                                                 reserved3555;	//0xC4503A68
	UINT32                                                 reserved3556;	//0xC4503A6C
	UINT32                                                 reserved3557;	//0xC4503A70
	UINT32                                                 reserved3558;	//0xC4503A74
	UINT32                                                 reserved3559;	//0xC4503A78
	UINT32                                                 reserved3560;	//0xC4503A7C
	UINT32                                                 reserved3561;	//0xC4503A80
	UINT32                                                 reserved3562;	//0xC4503A84
	UINT32                                                 reserved3563;	//0xC4503A88
	UINT32                                                 reserved3564;	//0xC4503A8C
	UINT32                                                 reserved3565;	//0xC4503A90
	UINT32                                                 reserved3566;	//0xC4503A94
	UINT32                                                 reserved3567;	//0xC4503A98
	UINT32                                                 reserved3568;	//0xC4503A9C
	UINT32                                                 reserved3569;	//0xC4503AA0
	UINT32                                                 reserved3570;	//0xC4503AA4
	UINT32                                                 reserved3571;	//0xC4503AA8
	UINT32                                                 reserved3572;	//0xC4503AAC
	UINT32                                                 reserved3573;	//0xC4503AB0
	UINT32                                                 reserved3574;	//0xC4503AB4
	UINT32                                                 reserved3575;	//0xC4503AB8
	UINT32                                                 reserved3576;	//0xC4503ABC
	UINT32                                                 reserved3577;	//0xC4503AC0
	UINT32                                                 reserved3578;	//0xC4503AC4
	UINT32                                                 reserved3579;	//0xC4503AC8
	UINT32                                                 reserved3580;	//0xC4503ACC
	UINT32                                                 reserved3581;	//0xC4503AD0
	UINT32                                                 reserved3582;	//0xC4503AD4
	UINT32                                                 reserved3583;	//0xC4503AD8
	UINT32                                                 reserved3584;	//0xC4503ADC
	UINT32                                                 reserved3585;	//0xC4503AE0
	UINT32                                                 reserved3586;	//0xC4503AE4
	UINT32                                                 reserved3587;	//0xC4503AE8
	UINT32                                                 reserved3588;	//0xC4503AEC
	UINT32                                                 reserved3589;	//0xC4503AF0
	UINT32                                                 reserved3590;	//0xC4503AF4
	UINT32                                                 reserved3591;	//0xC4503AF8
	UINT32                                                 reserved3592;	//0xC4503AFC
	UINT32                                                 reserved3593;	//0xC4503B00
	UINT32                                                 reserved3594;	//0xC4503B04
	UINT32                                                 reserved3595;	//0xC4503B08
	UINT32                                                 reserved3596;	//0xC4503B0C
	UINT32                                                 reserved3597;	//0xC4503B10
	UINT32                                                 reserved3598;	//0xC4503B14
	UINT32                                                 reserved3599;	//0xC4503B18
	UINT32                                                 reserved3600;	//0xC4503B1C
	UINT32                                                 reserved3601;	//0xC4503B20
	UINT32                                                 reserved3602;	//0xC4503B24
	UINT32                                                 reserved3603;	//0xC4503B28
	UINT32                                                 reserved3604;	//0xC4503B2C
	UINT32                                                 reserved3605;	//0xC4503B30
	UINT32                                                 reserved3606;	//0xC4503B34
	UINT32                                                 reserved3607;	//0xC4503B38
	UINT32                                                 reserved3608;	//0xC4503B3C
	UINT32                                                 reserved3609;	//0xC4503B40
	UINT32                                                 reserved3610;	//0xC4503B44
	UINT32                                                 reserved3611;	//0xC4503B48
	UINT32                                                 reserved3612;	//0xC4503B4C
	UINT32                                                 reserved3613;	//0xC4503B50
	UINT32                                                 reserved3614;	//0xC4503B54
	UINT32                                                 reserved3615;	//0xC4503B58
	UINT32                                                 reserved3616;	//0xC4503B5C
	UINT32                                                 reserved3617;	//0xC4503B60
	UINT32                                                 reserved3618;	//0xC4503B64
	UINT32                                                 reserved3619;	//0xC4503B68
	UINT32                                                 reserved3620;	//0xC4503B6C
	UINT32                                                 reserved3621;	//0xC4503B70
	UINT32                                                 reserved3622;	//0xC4503B74
	UINT32                                                 reserved3623;	//0xC4503B78
	UINT32                                                 reserved3624;	//0xC4503B7C
	UINT32                                                 reserved3625;	//0xC4503B80
	UINT32                                                 reserved3626;	//0xC4503B84
	UINT32                                                 reserved3627;	//0xC4503B88
	UINT32                                                 reserved3628;	//0xC4503B8C
	UINT32                                                 reserved3629;	//0xC4503B90
	UINT32                                                 reserved3630;	//0xC4503B94
	UINT32                                                 reserved3631;	//0xC4503B98
	UINT32                                                 reserved3632;	//0xC4503B9C
	UINT32                                                 reserved3633;	//0xC4503BA0
	UINT32                                                 reserved3634;	//0xC4503BA4
	UINT32                                                 reserved3635;	//0xC4503BA8
	UINT32                                                 reserved3636;	//0xC4503BAC
	UINT32                                                 reserved3637;	//0xC4503BB0
	UINT32                                                 reserved3638;	//0xC4503BB4
	UINT32                                                 reserved3639;	//0xC4503BB8
	UINT32                                                 reserved3640;	//0xC4503BBC
	UINT32                                                 reserved3641;	//0xC4503BC0
	UINT32                                                 reserved3642;	//0xC4503BC4
	UINT32                                                 reserved3643;	//0xC4503BC8
	UINT32                                                 reserved3644;	//0xC4503BCC
	UINT32                                                 reserved3645;	//0xC4503BD0
	UINT32                                                 reserved3646;	//0xC4503BD4
	UINT32                                                 reserved3647;	//0xC4503BD8
	UINT32                                                 reserved3648;	//0xC4503BDC
	UINT32                                                 reserved3649;	//0xC4503BE0
	UINT32                                                 reserved3650;	//0xC4503BE4
	UINT32                                                 reserved3651;	//0xC4503BE8
	UINT32                                                 reserved3652;	//0xC4503BEC
	UINT32                                                 reserved3653;	//0xC4503BF0
	UINT32                                                 reserved3654;	//0xC4503BF4
	UINT32                                                 reserved3655;	//0xC4503BF8
	UINT32                                                 reserved3656;	//0xC4503BFC
	UINT32                                                 reserved3657;	//0xC4503C00
	UINT32                                                 reserved3658;	//0xC4503C04
	UINT32                                                 reserved3659;	//0xC4503C08
	UINT32                                                 reserved3660;	//0xC4503C0C
	UINT32                                                 reserved3661;	//0xC4503C10
	UINT32                                                 reserved3662;	//0xC4503C14
	UINT32                                                 reserved3663;	//0xC4503C18
	UINT32                                                 reserved3664;	//0xC4503C1C
	UINT32                                                 reserved3665;	//0xC4503C20
	UINT32                                                 reserved3666;	//0xC4503C24
	UINT32                                                 reserved3667;	//0xC4503C28
	UINT32                                                 reserved3668;	//0xC4503C2C
	UINT32                                                 reserved3669;	//0xC4503C30
	UINT32                                                 reserved3670;	//0xC4503C34
	UINT32                                                 reserved3671;	//0xC4503C38
	UINT32                                                 reserved3672;	//0xC4503C3C
	UINT32                                                 reserved3673;	//0xC4503C40
	UINT32                                                 reserved3674;	//0xC4503C44
	UINT32                                                 reserved3675;	//0xC4503C48
	UINT32                                                 reserved3676;	//0xC4503C4C
	UINT32                                                 reserved3677;	//0xC4503C50
	UINT32                                                 reserved3678;	//0xC4503C54
	UINT32                                                 reserved3679;	//0xC4503C58
	UINT32                                                 reserved3680;	//0xC4503C5C
	UINT32                                                 reserved3681;	//0xC4503C60
	UINT32                                                 reserved3682;	//0xC4503C64
	UINT32                                                 reserved3683;	//0xC4503C68
	UINT32                                                 reserved3684;	//0xC4503C6C
	UINT32                                                 reserved3685;	//0xC4503C70
	UINT32                                                 reserved3686;	//0xC4503C74
	UINT32                                                 reserved3687;	//0xC4503C78
	UINT32                                                 reserved3688;	//0xC4503C7C
	UINT32                                                 reserved3689;	//0xC4503C80
	UINT32                                                 reserved3690;	//0xC4503C84
	UINT32                                                 reserved3691;	//0xC4503C88
	UINT32                                                 reserved3692;	//0xC4503C8C
	UINT32                                                 reserved3693;	//0xC4503C90
	UINT32                                                 reserved3694;	//0xC4503C94
	UINT32                                                 reserved3695;	//0xC4503C98
	UINT32                                                 reserved3696;	//0xC4503C9C
	UINT32                                                 reserved3697;	//0xC4503CA0
	UINT32                                                 reserved3698;	//0xC4503CA4
	UINT32                                                 reserved3699;	//0xC4503CA8
	UINT32                                                 reserved3700;	//0xC4503CAC
	UINT32                                                 reserved3701;	//0xC4503CB0
	UINT32                                                 reserved3702;	//0xC4503CB4
	UINT32                                                 reserved3703;	//0xC4503CB8
	UINT32                                                 reserved3704;	//0xC4503CBC
	UINT32                                                 reserved3705;	//0xC4503CC0
	UINT32                                                 reserved3706;	//0xC4503CC4
	UINT32                                                 reserved3707;	//0xC4503CC8
	UINT32                                                 reserved3708;	//0xC4503CCC
	UINT32                                                 reserved3709;	//0xC4503CD0
	UINT32                                                 reserved3710;	//0xC4503CD4
	UINT32                                                 reserved3711;	//0xC4503CD8
	UINT32                                                 reserved3712;	//0xC4503CDC
	UINT32                                                 reserved3713;	//0xC4503CE0
	UINT32                                                 reserved3714;	//0xC4503CE4
	UINT32                                                 reserved3715;	//0xC4503CE8
	UINT32                                                 reserved3716;	//0xC4503CEC
	UINT32                                                 reserved3717;	//0xC4503CF0
	UINT32                                                 reserved3718;	//0xC4503CF4
	UINT32                                                 reserved3719;	//0xC4503CF8
	UINT32                                                 reserved3720;	//0xC4503CFC
	UINT32                                                 reserved3721;	//0xC4503D00
	UINT32                                                 reserved3722;	//0xC4503D04
	UINT32                                                 reserved3723;	//0xC4503D08
	UINT32                                                 reserved3724;	//0xC4503D0C
	UINT32                                                 reserved3725;	//0xC4503D10
	UINT32                                                 reserved3726;	//0xC4503D14
	UINT32                                                 reserved3727;	//0xC4503D18
	UINT32                                                 reserved3728;	//0xC4503D1C
	UINT32                                                 reserved3729;	//0xC4503D20
	UINT32                                                 reserved3730;	//0xC4503D24
	UINT32                                                 reserved3731;	//0xC4503D28
	UINT32                                                 reserved3732;	//0xC4503D2C
	UINT32                                                 reserved3733;	//0xC4503D30
	UINT32                                                 reserved3734;	//0xC4503D34
	UINT32                                                 reserved3735;	//0xC4503D38
	UINT32                                                 reserved3736;	//0xC4503D3C
	UINT32                                                 reserved3737;	//0xC4503D40
	UINT32                                                 reserved3738;	//0xC4503D44
	UINT32                                                 reserved3739;	//0xC4503D48
	UINT32                                                 reserved3740;	//0xC4503D4C
	UINT32                                                 reserved3741;	//0xC4503D50
	UINT32                                                 reserved3742;	//0xC4503D54
	UINT32                                                 reserved3743;	//0xC4503D58
	UINT32                                                 reserved3744;	//0xC4503D5C
	UINT32                                                 reserved3745;	//0xC4503D60
	UINT32                                                 reserved3746;	//0xC4503D64
	UINT32                                                 reserved3747;	//0xC4503D68
	UINT32                                                 reserved3748;	//0xC4503D6C
	UINT32                                                 reserved3749;	//0xC4503D70
	UINT32                                                 reserved3750;	//0xC4503D74
	UINT32                                                 reserved3751;	//0xC4503D78
	UINT32                                                 reserved3752;	//0xC4503D7C
	UINT32                                                 reserved3753;	//0xC4503D80
	UINT32                                                 reserved3754;	//0xC4503D84
	UINT32                                                 reserved3755;	//0xC4503D88
	UINT32                                                 reserved3756;	//0xC4503D8C
	UINT32                                                 reserved3757;	//0xC4503D90
	UINT32                                                 reserved3758;	//0xC4503D94
	UINT32                                                 reserved3759;	//0xC4503D98
	UINT32                                                 reserved3760;	//0xC4503D9C
	UINT32                                                 reserved3761;	//0xC4503DA0
	UINT32                                                 reserved3762;	//0xC4503DA4
	UINT32                                                 reserved3763;	//0xC4503DA8
	UINT32                                                 reserved3764;	//0xC4503DAC
	UINT32                                                 reserved3765;	//0xC4503DB0
	UINT32                                                 reserved3766;	//0xC4503DB4
	UINT32                                                 reserved3767;	//0xC4503DB8
	UINT32                                                 reserved3768;	//0xC4503DBC
	UINT32                                                 reserved3769;	//0xC4503DC0
	UINT32                                                 reserved3770;	//0xC4503DC4
	UINT32                                                 reserved3771;	//0xC4503DC8
	UINT32                                                 reserved3772;	//0xC4503DCC
	UINT32                                                 reserved3773;	//0xC4503DD0
	UINT32                                                 reserved3774;	//0xC4503DD4
	UINT32                                                 reserved3775;	//0xC4503DD8
	UINT32                                                 reserved3776;	//0xC4503DDC
	UINT32                                                 reserved3777;	//0xC4503DE0
	UINT32                                                 reserved3778;	//0xC4503DE4
	UINT32                                                 reserved3779;	//0xC4503DE8
	UINT32                                                 reserved3780;	//0xC4503DEC
	UINT32                                                 reserved3781;	//0xC4503DF0
	UINT32                                                 reserved3782;	//0xC4503DF4
	UINT32                                                 reserved3783;	//0xC4503DF8
	UINT32                                                 reserved3784;	//0xC4503DFC
	UINT32                                                 reserved3785;	//0xC4503E00
	UINT32                                                 reserved3786;	//0xC4503E04
	UINT32                                                 reserved3787;	//0xC4503E08
	UINT32                                                 reserved3788;	//0xC4503E0C
	UINT32                                                 reserved3789;	//0xC4503E10
	UINT32                                                 reserved3790;	//0xC4503E14
	UINT32                                                 reserved3791;	//0xC4503E18
	UINT32                                                 reserved3792;	//0xC4503E1C
	UINT32                                                 reserved3793;	//0xC4503E20
	UINT32                                                 reserved3794;	//0xC4503E24
	UINT32                                                 reserved3795;	//0xC4503E28
	UINT32                                                 reserved3796;	//0xC4503E2C
	UINT32                                                 reserved3797;	//0xC4503E30
	UINT32                                                 reserved3798;	//0xC4503E34
	UINT32                                                 reserved3799;	//0xC4503E38
	UINT32                                                 reserved3800;	//0xC4503E3C
	UINT32                                                 reserved3801;	//0xC4503E40
	UINT32                                                 reserved3802;	//0xC4503E44
	UINT32                                                 reserved3803;	//0xC4503E48
	UINT32                                                 reserved3804;	//0xC4503E4C
	UINT32                                                 reserved3805;	//0xC4503E50
	UINT32                                                 reserved3806;	//0xC4503E54
	UINT32                                                 reserved3807;	//0xC4503E58
	UINT32                                                 reserved3808;	//0xC4503E5C
	UINT32                                                 reserved3809;	//0xC4503E60
	UINT32                                                 reserved3810;	//0xC4503E64
	UINT32                                                 reserved3811;	//0xC4503E68
	UINT32                                                 reserved3812;	//0xC4503E6C
	UINT32                                                 reserved3813;	//0xC4503E70
	UINT32                                                 reserved3814;	//0xC4503E74
	UINT32                                                 reserved3815;	//0xC4503E78
	UINT32                                                 reserved3816;	//0xC4503E7C
	UINT32                                                 reserved3817;	//0xC4503E80
	UINT32                                                 reserved3818;	//0xC4503E84
	UINT32                                                 reserved3819;	//0xC4503E88
	UINT32                                                 reserved3820;	//0xC4503E8C
	UINT32                                                 reserved3821;	//0xC4503E90
	UINT32                                                 reserved3822;	//0xC4503E94
	UINT32                                                 reserved3823;	//0xC4503E98
	UINT32                                                 reserved3824;	//0xC4503E9C
	UINT32                                                 reserved3825;	//0xC4503EA0
	UINT32                                                 reserved3826;	//0xC4503EA4
	UINT32                                                 reserved3827;	//0xC4503EA8
	UINT32                                                 reserved3828;	//0xC4503EAC
	UINT32                                                 reserved3829;	//0xC4503EB0
	UINT32                                                 reserved3830;	//0xC4503EB4
	UINT32                                                 reserved3831;	//0xC4503EB8
	UINT32                                                 reserved3832;	//0xC4503EBC
	UINT32                                                 reserved3833;	//0xC4503EC0
	UINT32                                                 reserved3834;	//0xC4503EC4
	UINT32                                                 reserved3835;	//0xC4503EC8
	UINT32                                                 reserved3836;	//0xC4503ECC
	UINT32                                                 reserved3837;	//0xC4503ED0
	UINT32                                                 reserved3838;	//0xC4503ED4
	UINT32                                                 reserved3839;	//0xC4503ED8
	UINT32                                                 reserved3840;	//0xC4503EDC
	UINT32                                                 reserved3841;	//0xC4503EE0
	UINT32                                                 reserved3842;	//0xC4503EE4
	UINT32                                                 reserved3843;	//0xC4503EE8
	UINT32                                                 reserved3844;	//0xC4503EEC
	UINT32                                                 reserved3845;	//0xC4503EF0
	UINT32                                                 reserved3846;	//0xC4503EF4
	UINT32                                                 reserved3847;	//0xC4503EF8
	UINT32                                                 reserved3848;	//0xC4503EFC
	UINT32                                                 reserved3849;	//0xC4503F00
	UINT32                                                 reserved3850;	//0xC4503F04
	UINT32                                                 reserved3851;	//0xC4503F08
	UINT32                                                 reserved3852;	//0xC4503F0C
	UINT32                                                 reserved3853;	//0xC4503F10
	UINT32                                                 reserved3854;	//0xC4503F14
	UINT32                                                 reserved3855;	//0xC4503F18
	UINT32                                                 reserved3856;	//0xC4503F1C
	UINT32                                                 reserved3857;	//0xC4503F20
	UINT32                                                 reserved3858;	//0xC4503F24
	UINT32                                                 reserved3859;	//0xC4503F28
	UINT32                                                 reserved3860;	//0xC4503F2C
	UINT32                                                 reserved3861;	//0xC4503F30
	UINT32                                                 reserved3862;	//0xC4503F34
	UINT32                                                 reserved3863;	//0xC4503F38
	UINT32                                                 reserved3864;	//0xC4503F3C
	UINT32                                                 reserved3865;	//0xC4503F40
	UINT32                                                 reserved3866;	//0xC4503F44
	UINT32                                                 reserved3867;	//0xC4503F48
	UINT32                                                 reserved3868;	//0xC4503F4C
	UINT32                                                 reserved3869;	//0xC4503F50
	UINT32                                                 reserved3870;	//0xC4503F54
	UINT32                                                 reserved3871;	//0xC4503F58
	UINT32                                                 reserved3872;	//0xC4503F5C
	UINT32                                                 reserved3873;	//0xC4503F60
	UINT32                                                 reserved3874;	//0xC4503F64
	UINT32                                                 reserved3875;	//0xC4503F68
	UINT32                                                 reserved3876;	//0xC4503F6C
	UINT32                                                 reserved3877;	//0xC4503F70
	UINT32                                                 reserved3878;	//0xC4503F74
	UINT32                                                 reserved3879;	//0xC4503F78
	UINT32                                                 reserved3880;	//0xC4503F7C
	UINT32                                                 reserved3881;	//0xC4503F80
	UINT32                                                 reserved3882;	//0xC4503F84
	UINT32                                                 reserved3883;	//0xC4503F88
	UINT32                                                 reserved3884;	//0xC4503F8C
	UINT32                                                 reserved3885;	//0xC4503F90
	UINT32                                                 reserved3886;	//0xC4503F94
	UINT32                                                 reserved3887;	//0xC4503F98
	UINT32                                                 reserved3888;	//0xC4503F9C
	UINT32                                                 reserved3889;	//0xC4503FA0
	UINT32                                                 reserved3890;	//0xC4503FA4
	UINT32                                                 reserved3891;	//0xC4503FA8
	UINT32                                                 reserved3892;	//0xC4503FAC
	UINT32                                                 reserved3893;	//0xC4503FB0
	UINT32                                                 reserved3894;	//0xC4503FB4
	UINT32                                                 reserved3895;	//0xC4503FB8
	UINT32                                                 reserved3896;	//0xC4503FBC
	UINT32                                                 reserved3897;	//0xC4503FC0
	UINT32                                                 reserved3898;	//0xC4503FC4
	UINT32                                                 reserved3899;	//0xC4503FC8
	UINT32                                                 reserved3900;	//0xC4503FCC
	UINT32                                                 reserved3901;	//0xC4503FD0
	UINT32                                                 reserved3902;	//0xC4503FD4
	UINT32                                                 reserved3903;	//0xC4503FD8
	UINT32                                                 reserved3904;	//0xC4503FDC
	UINT32                                                 reserved3905;	//0xC4503FE0
	UINT32                                                 reserved3906;	//0xC4503FE4
	UINT32                                                 reserved3907;	//0xC4503FE8
	UINT32                                                 reserved3908;	//0xC4503FEC
	UINT32                                                 reserved3909;	//0xC4503FF0
	UINT32                                                 reserved3910;	//0xC4503FF4
	UINT32                                                 reserved3911;	//0xC4503FF8
	UINT32                                                 reserved3912;	//0xC4503FFC
	UINT32                                                 reserved3913;	//0xC4504000
	UINT32                                                 reserved3914;	//0xC4504004
	UINT32                                                 reserved3915;	//0xC4504008
	UINT32                                                 reserved3916;	//0xC450400C
	UINT32                                                 reserved3917;	//0xC4504010
	UINT32                                                 reserved3918;	//0xC4504014
	UINT32                                                 reserved3919;	//0xC4504018
	UINT32                                                 reserved3920;	//0xC450401C
	UINT32                                                 reserved3921;	//0xC4504020
	UINT32                                                 reserved3922;	//0xC4504024
	UINT32                                                 reserved3923;	//0xC4504028
	UINT32                                                 reserved3924;	//0xC450402C
	UINT32                                                 reserved3925;	//0xC4504030
	UINT32                                                 reserved3926;	//0xC4504034
	UINT32                                                 reserved3927;	//0xC4504038
	UINT32                                                 reserved3928;	//0xC450403C
	UINT32                                                 reserved3929;	//0xC4504040
	UINT32                                                 reserved3930;	//0xC4504044
	UINT32                                                 reserved3931;	//0xC4504048
	UINT32                                                 reserved3932;	//0xC450404C
	UINT32                                                 reserved3933;	//0xC4504050
	UINT32                                                 reserved3934;	//0xC4504054
	UINT32                                                 reserved3935;	//0xC4504058
	UINT32                                                 reserved3936;	//0xC450405C
	UINT32                                                 reserved3937;	//0xC4504060
	UINT32                                                 reserved3938;	//0xC4504064
	UINT32                                                 reserved3939;	//0xC4504068
	UINT32                                                 reserved3940;	//0xC450406C
	UINT32                                                 reserved3941;	//0xC4504070
	UINT32                                                 reserved3942;	//0xC4504074
	UINT32                                                 reserved3943;	//0xC4504078
	UINT32                                                 reserved3944;	//0xC450407C
	UINT32                                                 reserved3945;	//0xC4504080
	UINT32                                                 reserved3946;	//0xC4504084
	UINT32                                                 reserved3947;	//0xC4504088
	UINT32                                                 reserved3948;	//0xC450408C
	UINT32                                                 reserved3949;	//0xC4504090
	UINT32                                                 reserved3950;	//0xC4504094
	UINT32                                                 reserved3951;	//0xC4504098
	UINT32                                                 reserved3952;	//0xC450409C
	UINT32                                                 reserved3953;	//0xC45040A0
	UINT32                                                 reserved3954;	//0xC45040A4
	UINT32                                                 reserved3955;	//0xC45040A8
	UINT32                                                 reserved3956;	//0xC45040AC
	UINT32                                                 reserved3957;	//0xC45040B0
	UINT32                                                 reserved3958;	//0xC45040B4
	UINT32                                                 reserved3959;	//0xC45040B8
	UINT32                                                 reserved3960;	//0xC45040BC
	UINT32                                                 reserved3961;	//0xC45040C0
	UINT32                                                 reserved3962;	//0xC45040C4
	UINT32                                                 reserved3963;	//0xC45040C8
	UINT32                                                 reserved3964;	//0xC45040CC
	UINT32                                                 reserved3965;	//0xC45040D0
	UINT32                                                 reserved3966;	//0xC45040D4
	UINT32                                                 reserved3967;	//0xC45040D8
	UINT32                                                 reserved3968;	//0xC45040DC
	UINT32                                                 reserved3969;	//0xC45040E0
	UINT32                                                 reserved3970;	//0xC45040E4
	UINT32                                                 reserved3971;	//0xC45040E8
	UINT32                                                 reserved3972;	//0xC45040EC
	UINT32                                                 reserved3973;	//0xC45040F0
	UINT32                                                 reserved3974;	//0xC45040F4
	UINT32                                                 reserved3975;	//0xC45040F8
	UINT32                                                 reserved3976;	//0xC45040FC
	UINT32                                                 reserved3977;	//0xC4504100
	UINT32                                                 reserved3978;	//0xC4504104
	UINT32                                                 reserved3979;	//0xC4504108
	UINT32                                                 reserved3980;	//0xC450410C
	UINT32                                                 reserved3981;	//0xC4504110
	UINT32                                                 reserved3982;	//0xC4504114
	UINT32                                                 reserved3983;	//0xC4504118
	UINT32                                                 reserved3984;	//0xC450411C
	UINT32                                                 reserved3985;	//0xC4504120
	UINT32                                                 reserved3986;	//0xC4504124
	UINT32                                                 reserved3987;	//0xC4504128
	UINT32                                                 reserved3988;	//0xC450412C
	UINT32                                                 reserved3989;	//0xC4504130
	UINT32                                                 reserved3990;	//0xC4504134
	UINT32                                                 reserved3991;	//0xC4504138
	UINT32                                                 reserved3992;	//0xC450413C
	UINT32                                                 reserved3993;	//0xC4504140
	UINT32                                                 reserved3994;	//0xC4504144
	UINT32                                                 reserved3995;	//0xC4504148
	UINT32                                                 reserved3996;	//0xC450414C
	UINT32                                                 reserved3997;	//0xC4504150
	UINT32                                                 reserved3998;	//0xC4504154
	UINT32                                                 reserved3999;	//0xC4504158
	UINT32                                                 reserved4000;	//0xC450415C
	UINT32                                                 reserved4001;	//0xC4504160
	UINT32                                                 reserved4002;	//0xC4504164
	UINT32                                                 reserved4003;	//0xC4504168
	UINT32                                                 reserved4004;	//0xC450416C
	UINT32                                                 reserved4005;	//0xC4504170
	UINT32                                                 reserved4006;	//0xC4504174
	UINT32                                                 reserved4007;	//0xC4504178
	UINT32                                                 reserved4008;	//0xC450417C
	UINT32                                                 reserved4009;	//0xC4504180
	UINT32                                                 reserved4010;	//0xC4504184
	UINT32                                                 reserved4011;	//0xC4504188
	UINT32                                                 reserved4012;	//0xC450418C
	UINT32                                                 reserved4013;	//0xC4504190
	UINT32                                                 reserved4014;	//0xC4504194
	UINT32                                                 reserved4015;	//0xC4504198
	UINT32                                                 reserved4016;	//0xC450419C
	UINT32                                                 reserved4017;	//0xC45041A0
	UINT32                                                 reserved4018;	//0xC45041A4
	UINT32                                                 reserved4019;	//0xC45041A8
	UINT32                                                 reserved4020;	//0xC45041AC
	UINT32                                                 reserved4021;	//0xC45041B0
	UINT32                                                 reserved4022;	//0xC45041B4
	UINT32                                                 reserved4023;	//0xC45041B8
	UINT32                                                 reserved4024;	//0xC45041BC
	UINT32                                                 reserved4025;	//0xC45041C0
	UINT32                                                 reserved4026;	//0xC45041C4
	UINT32                                                 reserved4027;	//0xC45041C8
	UINT32                                                 reserved4028;	//0xC45041CC
	UINT32                                                 reserved4029;	//0xC45041D0
	UINT32                                                 reserved4030;	//0xC45041D4
	UINT32                                                 reserved4031;	//0xC45041D8
	UINT32                                                 reserved4032;	//0xC45041DC
	UINT32                                                 reserved4033;	//0xC45041E0
	UINT32                                                 reserved4034;	//0xC45041E4
	UINT32                                                 reserved4035;	//0xC45041E8
	UINT32                                                 reserved4036;	//0xC45041EC
	UINT32                                                 reserved4037;	//0xC45041F0
	UINT32                                                 reserved4038;	//0xC45041F4
	UINT32                                                 reserved4039;	//0xC45041F8
	UINT32                                                 reserved4040;	//0xC45041FC
	UINT32                                                 reserved4041;	//0xC4504200
	UINT32                                                 reserved4042;	//0xC4504204
	UINT32                                                 reserved4043;	//0xC4504208
	UINT32                                                 reserved4044;	//0xC450420C
	UINT32                                                 reserved4045;	//0xC4504210
	UINT32                                                 reserved4046;	//0xC4504214
	UINT32                                                 reserved4047;	//0xC4504218
	UINT32                                                 reserved4048;	//0xC450421C
	UINT32                                                 reserved4049;	//0xC4504220
	UINT32                                                 reserved4050;	//0xC4504224
	UINT32                                                 reserved4051;	//0xC4504228
	UINT32                                                 reserved4052;	//0xC450422C
	UINT32                                                 reserved4053;	//0xC4504230
	UINT32                                                 reserved4054;	//0xC4504234
	UINT32                                                 reserved4055;	//0xC4504238
	UINT32                                                 reserved4056;	//0xC450423C
	UINT32                                                 reserved4057;	//0xC4504240
	UINT32                                                 reserved4058;	//0xC4504244
	UINT32                                                 reserved4059;	//0xC4504248
	UINT32                                                 reserved4060;	//0xC450424C
	UINT32                                                 reserved4061;	//0xC4504250
	UINT32                                                 reserved4062;	//0xC4504254
	UINT32                                                 reserved4063;	//0xC4504258
	UINT32                                                 reserved4064;	//0xC450425C
	UINT32                                                 reserved4065;	//0xC4504260
	UINT32                                                 reserved4066;	//0xC4504264
	UINT32                                                 reserved4067;	//0xC4504268
	UINT32                                                 reserved4068;	//0xC450426C
	UINT32                                                 reserved4069;	//0xC4504270
	UINT32                                                 reserved4070;	//0xC4504274
	UINT32                                                 reserved4071;	//0xC4504278
	UINT32                                                 reserved4072;	//0xC450427C
	UINT32                                                 reserved4073;	//0xC4504280
	UINT32                                                 reserved4074;	//0xC4504284
	UINT32                                                 reserved4075;	//0xC4504288
	UINT32                                                 reserved4076;	//0xC450428C
	UINT32                                                 reserved4077;	//0xC4504290
	UINT32                                                 reserved4078;	//0xC4504294
	UINT32                                                 reserved4079;	//0xC4504298
	UINT32                                                 reserved4080;	//0xC450429C
	UINT32                                                 reserved4081;	//0xC45042A0
	UINT32                                                 reserved4082;	//0xC45042A4
	UINT32                                                 reserved4083;	//0xC45042A8
	UINT32                                                 reserved4084;	//0xC45042AC
	UINT32                                                 reserved4085;	//0xC45042B0
	UINT32                                                 reserved4086;	//0xC45042B4
	UINT32                                                 reserved4087;	//0xC45042B8
	UINT32                                                 reserved4088;	//0xC45042BC
	UINT32                                                 reserved4089;	//0xC45042C0
	UINT32                                                 reserved4090;	//0xC45042C4
	UINT32                                                 reserved4091;	//0xC45042C8
	UINT32                                                 reserved4092;	//0xC45042CC
	UINT32                                                 reserved4093;	//0xC45042D0
	UINT32                                                 reserved4094;	//0xC45042D4
	UINT32                                                 reserved4095;	//0xC45042D8
	UINT32                                                 reserved4096;	//0xC45042DC
	UINT32                                                 reserved4097;	//0xC45042E0
	UINT32                                                 reserved4098;	//0xC45042E4
	UINT32                                                 reserved4099;	//0xC45042E8
	UINT32                                                 reserved4100;	//0xC45042EC
	UINT32                                                 reserved4101;	//0xC45042F0
	UINT32                                                 reserved4102;	//0xC45042F4
	UINT32                                                 reserved4103;	//0xC45042F8
	UINT32                                                 reserved4104;	//0xC45042FC
	UINT32                                                 reserved4105;	//0xC4504300
	UINT32                                                 reserved4106;	//0xC4504304
	UINT32                                                 reserved4107;	//0xC4504308
	UINT32                                                 reserved4108;	//0xC450430C
	UINT32                                                 reserved4109;	//0xC4504310
	UINT32                                                 reserved4110;	//0xC4504314
	UINT32                                                 reserved4111;	//0xC4504318
	UINT32                                                 reserved4112;	//0xC450431C
	UINT32                                                 reserved4113;	//0xC4504320
	UINT32                                                 reserved4114;	//0xC4504324
	UINT32                                                 reserved4115;	//0xC4504328
	UINT32                                                 reserved4116;	//0xC450432C
	UINT32                                                 reserved4117;	//0xC4504330
	UINT32                                                 reserved4118;	//0xC4504334
	UINT32                                                 reserved4119;	//0xC4504338
	UINT32                                                 reserved4120;	//0xC450433C
	UINT32                                                 reserved4121;	//0xC4504340
	UINT32                                                 reserved4122;	//0xC4504344
	UINT32                                                 reserved4123;	//0xC4504348
	UINT32                                                 reserved4124;	//0xC450434C
	UINT32                                                 reserved4125;	//0xC4504350
	UINT32                                                 reserved4126;	//0xC4504354
	UINT32                                                 reserved4127;	//0xC4504358
	UINT32                                                 reserved4128;	//0xC450435C
	UINT32                                                 reserved4129;	//0xC4504360
	UINT32                                                 reserved4130;	//0xC4504364
	UINT32                                                 reserved4131;	//0xC4504368
	UINT32                                                 reserved4132;	//0xC450436C
	UINT32                                                 reserved4133;	//0xC4504370
	UINT32                                                 reserved4134;	//0xC4504374
	UINT32                                                 reserved4135;	//0xC4504378
	UINT32                                                 reserved4136;	//0xC450437C
	UINT32                                                 reserved4137;	//0xC4504380
	UINT32                                                 reserved4138;	//0xC4504384
	UINT32                                                 reserved4139;	//0xC4504388
	UINT32                                                 reserved4140;	//0xC450438C
	UINT32                                                 reserved4141;	//0xC4504390
	UINT32                                                 reserved4142;	//0xC4504394
	UINT32                                                 reserved4143;	//0xC4504398
	UINT32                                                 reserved4144;	//0xC450439C
	UINT32                                                 reserved4145;	//0xC45043A0
	UINT32                                                 reserved4146;	//0xC45043A4
	UINT32                                                 reserved4147;	//0xC45043A8
	UINT32                                                 reserved4148;	//0xC45043AC
	UINT32                                                 reserved4149;	//0xC45043B0
	UINT32                                                 reserved4150;	//0xC45043B4
	UINT32                                                 reserved4151;	//0xC45043B8
	UINT32                                                 reserved4152;	//0xC45043BC
	UINT32                                                 reserved4153;	//0xC45043C0
	UINT32                                                 reserved4154;	//0xC45043C4
	UINT32                                                 reserved4155;	//0xC45043C8
	UINT32                                                 reserved4156;	//0xC45043CC
	UINT32                                                 reserved4157;	//0xC45043D0
	UINT32                                                 reserved4158;	//0xC45043D4
	UINT32                                                 reserved4159;	//0xC45043D8
	UINT32                                                 reserved4160;	//0xC45043DC
	UINT32                                                 reserved4161;	//0xC45043E0
	UINT32                                                 reserved4162;	//0xC45043E4
	UINT32                                                 reserved4163;	//0xC45043E8
	UINT32                                                 reserved4164;	//0xC45043EC
	UINT32                                                 reserved4165;	//0xC45043F0
	UINT32                                                 reserved4166;	//0xC45043F4
	UINT32                                                 reserved4167;	//0xC45043F8
	UINT32                                                 reserved4168;	//0xC45043FC
	UINT32                                                 reserved4169;	//0xC4504400
	UINT32                                                 reserved4170;	//0xC4504404
	UINT32                                                 reserved4171;	//0xC4504408
	UINT32                                                 reserved4172;	//0xC450440C
	UINT32                                                 reserved4173;	//0xC4504410
	UINT32                                                 reserved4174;	//0xC4504414
	UINT32                                                 reserved4175;	//0xC4504418
	UINT32                                                 reserved4176;	//0xC450441C
	UINT32                                                 reserved4177;	//0xC4504420
	UINT32                                                 reserved4178;	//0xC4504424
	UINT32                                                 reserved4179;	//0xC4504428
	UINT32                                                 reserved4180;	//0xC450442C
	UINT32                                                 reserved4181;	//0xC4504430
	UINT32                                                 reserved4182;	//0xC4504434
	UINT32                                                 reserved4183;	//0xC4504438
	UINT32                                                 reserved4184;	//0xC450443C
	UINT32                                                 reserved4185;	//0xC4504440
	UINT32                                                 reserved4186;	//0xC4504444
	UINT32                                                 reserved4187;	//0xC4504448
	UINT32                                                 reserved4188;	//0xC450444C
	UINT32                                                 reserved4189;	//0xC4504450
	UINT32                                                 reserved4190;	//0xC4504454
	UINT32                                                 reserved4191;	//0xC4504458
	UINT32                                                 reserved4192;	//0xC450445C
	UINT32                                                 reserved4193;	//0xC4504460
	UINT32                                                 reserved4194;	//0xC4504464
	UINT32                                                 reserved4195;	//0xC4504468
	UINT32                                                 reserved4196;	//0xC450446C
	UINT32                                                 reserved4197;	//0xC4504470
	UINT32                                                 reserved4198;	//0xC4504474
	UINT32                                                 reserved4199;	//0xC4504478
	UINT32                                                 reserved4200;	//0xC450447C
	UINT32                                                 reserved4201;	//0xC4504480
	UINT32                                                 reserved4202;	//0xC4504484
	UINT32                                                 reserved4203;	//0xC4504488
	UINT32                                                 reserved4204;	//0xC450448C
	UINT32                                                 reserved4205;	//0xC4504490
	UINT32                                                 reserved4206;	//0xC4504494
	UINT32                                                 reserved4207;	//0xC4504498
	UINT32                                                 reserved4208;	//0xC450449C
	UINT32                                                 reserved4209;	//0xC45044A0
	UINT32                                                 reserved4210;	//0xC45044A4
	UINT32                                                 reserved4211;	//0xC45044A8
	UINT32                                                 reserved4212;	//0xC45044AC
	UINT32                                                 reserved4213;	//0xC45044B0
	UINT32                                                 reserved4214;	//0xC45044B4
	UINT32                                                 reserved4215;	//0xC45044B8
	UINT32                                                 reserved4216;	//0xC45044BC
	UINT32                                                 reserved4217;	//0xC45044C0
	UINT32                                                 reserved4218;	//0xC45044C4
	UINT32                                                 reserved4219;	//0xC45044C8
	UINT32                                                 reserved4220;	//0xC45044CC
	UINT32                                                 reserved4221;	//0xC45044D0
	UINT32                                                 reserved4222;	//0xC45044D4
	UINT32                                                 reserved4223;	//0xC45044D8
	UINT32                                                 reserved4224;	//0xC45044DC
	UINT32                                                 reserved4225;	//0xC45044E0
	UINT32                                                 reserved4226;	//0xC45044E4
	UINT32                                                 reserved4227;	//0xC45044E8
	UINT32                                                 reserved4228;	//0xC45044EC
	UINT32                                                 reserved4229;	//0xC45044F0
	UINT32                                                 reserved4230;	//0xC45044F4
	UINT32                                                 reserved4231;	//0xC45044F8
	UINT32                                                 reserved4232;	//0xC45044FC
	UINT32                                                 reserved4233;	//0xC4504500
	UINT32                                                 reserved4234;	//0xC4504504
	UINT32                                                 reserved4235;	//0xC4504508
	UINT32                                                 reserved4236;	//0xC450450C
	UINT32                                                 reserved4237;	//0xC4504510
	UINT32                                                 reserved4238;	//0xC4504514
	UINT32                                                 reserved4239;	//0xC4504518
	UINT32                                                 reserved4240;	//0xC450451C
	UINT32                                                 reserved4241;	//0xC4504520
	UINT32                                                 reserved4242;	//0xC4504524
	UINT32                                                 reserved4243;	//0xC4504528
	UINT32                                                 reserved4244;	//0xC450452C
	UINT32                                                 reserved4245;	//0xC4504530
	UINT32                                                 reserved4246;	//0xC4504534
	UINT32                                                 reserved4247;	//0xC4504538
	UINT32                                                 reserved4248;	//0xC450453C
	UINT32                                                 reserved4249;	//0xC4504540
	UINT32                                                 reserved4250;	//0xC4504544
	UINT32                                                 reserved4251;	//0xC4504548
	UINT32                                                 reserved4252;	//0xC450454C
	UINT32                                                 reserved4253;	//0xC4504550
	UINT32                                                 reserved4254;	//0xC4504554
	UINT32                                                 reserved4255;	//0xC4504558
	UINT32                                                 reserved4256;	//0xC450455C
	UINT32                                                 reserved4257;	//0xC4504560
	UINT32                                                 reserved4258;	//0xC4504564
	UINT32                                                 reserved4259;	//0xC4504568
	UINT32                                                 reserved4260;	//0xC450456C
	UINT32                                                 reserved4261;	//0xC4504570
	UINT32                                                 reserved4262;	//0xC4504574
	UINT32                                                 reserved4263;	//0xC4504578
	UINT32                                                 reserved4264;	//0xC450457C
	UINT32                                                 reserved4265;	//0xC4504580
	UINT32                                                 reserved4266;	//0xC4504584
	UINT32                                                 reserved4267;	//0xC4504588
	UINT32                                                 reserved4268;	//0xC450458C
	UINT32                                                 reserved4269;	//0xC4504590
	UINT32                                                 reserved4270;	//0xC4504594
	UINT32                                                 reserved4271;	//0xC4504598
	UINT32                                                 reserved4272;	//0xC450459C
	UINT32                                                 reserved4273;	//0xC45045A0
	UINT32                                                 reserved4274;	//0xC45045A4
	UINT32                                                 reserved4275;	//0xC45045A8
	UINT32                                                 reserved4276;	//0xC45045AC
	UINT32                                                 reserved4277;	//0xC45045B0
	UINT32                                                 reserved4278;	//0xC45045B4
	UINT32                                                 reserved4279;	//0xC45045B8
	UINT32                                                 reserved4280;	//0xC45045BC
	UINT32                                                 reserved4281;	//0xC45045C0
	UINT32                                                 reserved4282;	//0xC45045C4
	UINT32                                                 reserved4283;	//0xC45045C8
	UINT32                                                 reserved4284;	//0xC45045CC
	UINT32                                                 reserved4285;	//0xC45045D0
	UINT32                                                 reserved4286;	//0xC45045D4
	UINT32                                                 reserved4287;	//0xC45045D8
	UINT32                                                 reserved4288;	//0xC45045DC
	UINT32                                                 reserved4289;	//0xC45045E0
	UINT32                                                 reserved4290;	//0xC45045E4
	UINT32                                                 reserved4291;	//0xC45045E8
	UINT32                                                 reserved4292;	//0xC45045EC
	UINT32                                                 reserved4293;	//0xC45045F0
	UINT32                                                 reserved4294;	//0xC45045F4
	UINT32                                                 reserved4295;	//0xC45045F8
	UINT32                                                 reserved4296;	//0xC45045FC
	UINT32                                                 reserved4297;	//0xC4504600
	UINT32                                                 reserved4298;	//0xC4504604
	UINT32                                                 reserved4299;	//0xC4504608
	UINT32                                                 reserved4300;	//0xC450460C
	UINT32                                                 reserved4301;	//0xC4504610
	UINT32                                                 reserved4302;	//0xC4504614
	UINT32                                                 reserved4303;	//0xC4504618
	UINT32                                                 reserved4304;	//0xC450461C
	UINT32                                                 reserved4305;	//0xC4504620
	UINT32                                                 reserved4306;	//0xC4504624
	UINT32                                                 reserved4307;	//0xC4504628
	UINT32                                                 reserved4308;	//0xC450462C
	UINT32                                                 reserved4309;	//0xC4504630
	UINT32                                                 reserved4310;	//0xC4504634
	UINT32                                                 reserved4311;	//0xC4504638
	UINT32                                                 reserved4312;	//0xC450463C
	UINT32                                                 reserved4313;	//0xC4504640
	UINT32                                                 reserved4314;	//0xC4504644
	UINT32                                                 reserved4315;	//0xC4504648
	UINT32                                                 reserved4316;	//0xC450464C
	UINT32                                                 reserved4317;	//0xC4504650
	UINT32                                                 reserved4318;	//0xC4504654
	UINT32                                                 reserved4319;	//0xC4504658
	UINT32                                                 reserved4320;	//0xC450465C
	UINT32                                                 reserved4321;	//0xC4504660
	UINT32                                                 reserved4322;	//0xC4504664
	UINT32                                                 reserved4323;	//0xC4504668
	UINT32                                                 reserved4324;	//0xC450466C
	UINT32                                                 reserved4325;	//0xC4504670
	UINT32                                                 reserved4326;	//0xC4504674
	UINT32                                                 reserved4327;	//0xC4504678
	UINT32                                                 reserved4328;	//0xC450467C
	UINT32                                                 reserved4329;	//0xC4504680
	UINT32                                                 reserved4330;	//0xC4504684
	UINT32                                                 reserved4331;	//0xC4504688
	UINT32                                                 reserved4332;	//0xC450468C
	UINT32                                                 reserved4333;	//0xC4504690
	UINT32                                                 reserved4334;	//0xC4504694
	UINT32                                                 reserved4335;	//0xC4504698
	UINT32                                                 reserved4336;	//0xC450469C
	UINT32                                                 reserved4337;	//0xC45046A0
	UINT32                                                 reserved4338;	//0xC45046A4
	UINT32                                                 reserved4339;	//0xC45046A8
	UINT32                                                 reserved4340;	//0xC45046AC
	UINT32                                                 reserved4341;	//0xC45046B0
	UINT32                                                 reserved4342;	//0xC45046B4
	UINT32                                                 reserved4343;	//0xC45046B8
	UINT32                                                 reserved4344;	//0xC45046BC
	UINT32                                                 reserved4345;	//0xC45046C0
	UINT32                                                 reserved4346;	//0xC45046C4
	UINT32                                                 reserved4347;	//0xC45046C8
	UINT32                                                 reserved4348;	//0xC45046CC
	UINT32                                                 reserved4349;	//0xC45046D0
	UINT32                                                 reserved4350;	//0xC45046D4
	UINT32                                                 reserved4351;	//0xC45046D8
	UINT32                                                 reserved4352;	//0xC45046DC
	UINT32                                                 reserved4353;	//0xC45046E0
	UINT32                                                 reserved4354;	//0xC45046E4
	UINT32                                                 reserved4355;	//0xC45046E8
	UINT32                                                 reserved4356;	//0xC45046EC
	UINT32                                                 reserved4357;	//0xC45046F0
	UINT32                                                 reserved4358;	//0xC45046F4
	UINT32                                                 reserved4359;	//0xC45046F8
	UINT32                                                 reserved4360;	//0xC45046FC
	UINT32                                                 reserved4361;	//0xC4504700
	UINT32                                                 reserved4362;	//0xC4504704
	UINT32                                                 reserved4363;	//0xC4504708
	UINT32                                                 reserved4364;	//0xC450470C
	UINT32                                                 reserved4365;	//0xC4504710
	UINT32                                                 reserved4366;	//0xC4504714
	UINT32                                                 reserved4367;	//0xC4504718
	UINT32                                                 reserved4368;	//0xC450471C
	UINT32                                                 reserved4369;	//0xC4504720
	UINT32                                                 reserved4370;	//0xC4504724
	UINT32                                                 reserved4371;	//0xC4504728
	UINT32                                                 reserved4372;	//0xC450472C
	UINT32                                                 reserved4373;	//0xC4504730
	UINT32                                                 reserved4374;	//0xC4504734
	UINT32                                                 reserved4375;	//0xC4504738
	UINT32                                                 reserved4376;	//0xC450473C
	UINT32                                                 reserved4377;	//0xC4504740
	UINT32                                                 reserved4378;	//0xC4504744
	UINT32                                                 reserved4379;	//0xC4504748
	UINT32                                                 reserved4380;	//0xC450474C
	UINT32                                                 reserved4381;	//0xC4504750
	UINT32                                                 reserved4382;	//0xC4504754
	UINT32                                                 reserved4383;	//0xC4504758
	UINT32                                                 reserved4384;	//0xC450475C
	UINT32                                                 reserved4385;	//0xC4504760
	UINT32                                                 reserved4386;	//0xC4504764
	UINT32                                                 reserved4387;	//0xC4504768
	UINT32                                                 reserved4388;	//0xC450476C
	UINT32                                                 reserved4389;	//0xC4504770
	UINT32                                                 reserved4390;	//0xC4504774
	UINT32                                                 reserved4391;	//0xC4504778
	UINT32                                                 reserved4392;	//0xC450477C
	UINT32                                                 reserved4393;	//0xC4504780
	UINT32                                                 reserved4394;	//0xC4504784
	UINT32                                                 reserved4395;	//0xC4504788
	UINT32                                                 reserved4396;	//0xC450478C
	UINT32                                                 reserved4397;	//0xC4504790
	UINT32                                                 reserved4398;	//0xC4504794
	UINT32                                                 reserved4399;	//0xC4504798
	UINT32                                                 reserved4400;	//0xC450479C
	UINT32                                                 reserved4401;	//0xC45047A0
	UINT32                                                 reserved4402;	//0xC45047A4
	UINT32                                                 reserved4403;	//0xC45047A8
	UINT32                                                 reserved4404;	//0xC45047AC
	UINT32                                                 reserved4405;	//0xC45047B0
	UINT32                                                 reserved4406;	//0xC45047B4
	UINT32                                                 reserved4407;	//0xC45047B8
	UINT32                                                 reserved4408;	//0xC45047BC
	UINT32                                                 reserved4409;	//0xC45047C0
	UINT32                                                 reserved4410;	//0xC45047C4
	UINT32                                                 reserved4411;	//0xC45047C8
	UINT32                                                 reserved4412;	//0xC45047CC
	UINT32                                                 reserved4413;	//0xC45047D0
	UINT32                                                 reserved4414;	//0xC45047D4
	UINT32                                                 reserved4415;	//0xC45047D8
	UINT32                                                 reserved4416;	//0xC45047DC
	UINT32                                                 reserved4417;	//0xC45047E0
	UINT32                                                 reserved4418;	//0xC45047E4
	UINT32                                                 reserved4419;	//0xC45047E8
	UINT32                                                 reserved4420;	//0xC45047EC
	UINT32                                                 reserved4421;	//0xC45047F0
	UINT32                                                 reserved4422;	//0xC45047F4
	UINT32                                                 reserved4423;	//0xC45047F8
	UINT32                                                 reserved4424;	//0xC45047FC
	UINT32                                                 reserved4425;	//0xC4504800
	UINT32                                                 reserved4426;	//0xC4504804
	UINT32                                                 reserved4427;	//0xC4504808
	UINT32                                                 reserved4428;	//0xC450480C
	UINT32                                                 reserved4429;	//0xC4504810
	UINT32                                                 reserved4430;	//0xC4504814
	UINT32                                                 reserved4431;	//0xC4504818
	UINT32                                                 reserved4432;	//0xC450481C
	UINT32                                                 reserved4433;	//0xC4504820
	UINT32                                                 reserved4434;	//0xC4504824
	UINT32                                                 reserved4435;	//0xC4504828
	UINT32                                                 reserved4436;	//0xC450482C
	UINT32                                                 reserved4437;	//0xC4504830
	UINT32                                                 reserved4438;	//0xC4504834
	UINT32                                                 reserved4439;	//0xC4504838
	UINT32                                                 reserved4440;	//0xC450483C
	UINT32                                                 reserved4441;	//0xC4504840
	UINT32                                                 reserved4442;	//0xC4504844
	UINT32                                                 reserved4443;	//0xC4504848
	UINT32                                                 reserved4444;	//0xC450484C
	UINT32                                                 reserved4445;	//0xC4504850
	UINT32                                                 reserved4446;	//0xC4504854
	UINT32                                                 reserved4447;	//0xC4504858
	UINT32                                                 reserved4448;	//0xC450485C
	UINT32                                                 reserved4449;	//0xC4504860
	UINT32                                                 reserved4450;	//0xC4504864
	UINT32                                                 reserved4451;	//0xC4504868
	UINT32                                                 reserved4452;	//0xC450486C
	UINT32                                                 reserved4453;	//0xC4504870
	UINT32                                                 reserved4454;	//0xC4504874
	UINT32                                                 reserved4455;	//0xC4504878
	UINT32                                                 reserved4456;	//0xC450487C
	UINT32                                                 reserved4457;	//0xC4504880
	UINT32                                                 reserved4458;	//0xC4504884
	UINT32                                                 reserved4459;	//0xC4504888
	UINT32                                                 reserved4460;	//0xC450488C
	UINT32                                                 reserved4461;	//0xC4504890
	UINT32                                                 reserved4462;	//0xC4504894
	UINT32                                                 reserved4463;	//0xC4504898
	UINT32                                                 reserved4464;	//0xC450489C
	UINT32                                                 reserved4465;	//0xC45048A0
	UINT32                                                 reserved4466;	//0xC45048A4
	UINT32                                                 reserved4467;	//0xC45048A8
	UINT32                                                 reserved4468;	//0xC45048AC
	UINT32                                                 reserved4469;	//0xC45048B0
	UINT32                                                 reserved4470;	//0xC45048B4
	UINT32                                                 reserved4471;	//0xC45048B8
	UINT32                                                 reserved4472;	//0xC45048BC
	UINT32                                                 reserved4473;	//0xC45048C0
	UINT32                                                 reserved4474;	//0xC45048C4
	UINT32                                                 reserved4475;	//0xC45048C8
	UINT32                                                 reserved4476;	//0xC45048CC
	UINT32                                                 reserved4477;	//0xC45048D0
	UINT32                                                 reserved4478;	//0xC45048D4
	UINT32                                                 reserved4479;	//0xC45048D8
	UINT32                                                 reserved4480;	//0xC45048DC
	UINT32                                                 reserved4481;	//0xC45048E0
	UINT32                                                 reserved4482;	//0xC45048E4
	UINT32                                                 reserved4483;	//0xC45048E8
	UINT32                                                 reserved4484;	//0xC45048EC
	UINT32                                                 reserved4485;	//0xC45048F0
	UINT32                                                 reserved4486;	//0xC45048F4
	UINT32                                                 reserved4487;	//0xC45048F8
	UINT32                                                 reserved4488;	//0xC45048FC
	UINT32                                                 reserved4489;	//0xC4504900
	UINT32                                                 reserved4490;	//0xC4504904
	UINT32                                                 reserved4491;	//0xC4504908
	UINT32                                                 reserved4492;	//0xC450490C
	UINT32                                                 reserved4493;	//0xC4504910
	UINT32                                                 reserved4494;	//0xC4504914
	UINT32                                                 reserved4495;	//0xC4504918
	UINT32                                                 reserved4496;	//0xC450491C
	UINT32                                                 reserved4497;	//0xC4504920
	UINT32                                                 reserved4498;	//0xC4504924
	UINT32                                                 reserved4499;	//0xC4504928
	UINT32                                                 reserved4500;	//0xC450492C
	UINT32                                                 reserved4501;	//0xC4504930
	UINT32                                                 reserved4502;	//0xC4504934
	UINT32                                                 reserved4503;	//0xC4504938
	UINT32                                                 reserved4504;	//0xC450493C
	UINT32                                                 reserved4505;	//0xC4504940
	UINT32                                                 reserved4506;	//0xC4504944
	UINT32                                                 reserved4507;	//0xC4504948
	UINT32                                                 reserved4508;	//0xC450494C
	UINT32                                                 reserved4509;	//0xC4504950
	UINT32                                                 reserved4510;	//0xC4504954
	UINT32                                                 reserved4511;	//0xC4504958
	UINT32                                                 reserved4512;	//0xC450495C
	UINT32                                                 reserved4513;	//0xC4504960
	UINT32                                                 reserved4514;	//0xC4504964
	UINT32                                                 reserved4515;	//0xC4504968
	UINT32                                                 reserved4516;	//0xC450496C
	UINT32                                                 reserved4517;	//0xC4504970
	UINT32                                                 reserved4518;	//0xC4504974
	UINT32                                                 reserved4519;	//0xC4504978
	UINT32                                                 reserved4520;	//0xC450497C
	UINT32                                                 reserved4521;	//0xC4504980
	UINT32                                                 reserved4522;	//0xC4504984
	UINT32                                                 reserved4523;	//0xC4504988
	UINT32                                                 reserved4524;	//0xC450498C
	UINT32                                                 reserved4525;	//0xC4504990
	UINT32                                                 reserved4526;	//0xC4504994
	UINT32                                                 reserved4527;	//0xC4504998
	UINT32                                                 reserved4528;	//0xC450499C
	UINT32                                                 reserved4529;	//0xC45049A0
	UINT32                                                 reserved4530;	//0xC45049A4
	UINT32                                                 reserved4531;	//0xC45049A8
	UINT32                                                 reserved4532;	//0xC45049AC
	UINT32                                                 reserved4533;	//0xC45049B0
	UINT32                                                 reserved4534;	//0xC45049B4
	UINT32                                                 reserved4535;	//0xC45049B8
	UINT32                                                 reserved4536;	//0xC45049BC
	UINT32                                                 reserved4537;	//0xC45049C0
	UINT32                                                 reserved4538;	//0xC45049C4
	UINT32                                                 reserved4539;	//0xC45049C8
	UINT32                                                 reserved4540;	//0xC45049CC
	UINT32                                                 reserved4541;	//0xC45049D0
	UINT32                                                 reserved4542;	//0xC45049D4
	UINT32                                                 reserved4543;	//0xC45049D8
	UINT32                                                 reserved4544;	//0xC45049DC
	UINT32                                                 reserved4545;	//0xC45049E0
	UINT32                                                 reserved4546;	//0xC45049E4
	UINT32                                                 reserved4547;	//0xC45049E8
	UINT32                                                 reserved4548;	//0xC45049EC
	UINT32                                                 reserved4549;	//0xC45049F0
	UINT32                                                 reserved4550;	//0xC45049F4
	UINT32                                                 reserved4551;	//0xC45049F8
	UINT32                                                 reserved4552;	//0xC45049FC
	UINT32                                                 reserved4553;	//0xC4504A00
	UINT32                                                 reserved4554;	//0xC4504A04
	UINT32                                                 reserved4555;	//0xC4504A08
	UINT32                                                 reserved4556;	//0xC4504A0C
	UINT32                                                 reserved4557;	//0xC4504A10
	UINT32                                                 reserved4558;	//0xC4504A14
	UINT32                                                 reserved4559;	//0xC4504A18
	UINT32                                                 reserved4560;	//0xC4504A1C
	UINT32                                                 reserved4561;	//0xC4504A20
	UINT32                                                 reserved4562;	//0xC4504A24
	UINT32                                                 reserved4563;	//0xC4504A28
	UINT32                                                 reserved4564;	//0xC4504A2C
	UINT32                                                 reserved4565;	//0xC4504A30
	UINT32                                                 reserved4566;	//0xC4504A34
	UINT32                                                 reserved4567;	//0xC4504A38
	UINT32                                                 reserved4568;	//0xC4504A3C
	UINT32                                                 reserved4569;	//0xC4504A40
	UINT32                                                 reserved4570;	//0xC4504A44
	UINT32                                                 reserved4571;	//0xC4504A48
	UINT32                                                 reserved4572;	//0xC4504A4C
	UINT32                                                 reserved4573;	//0xC4504A50
	UINT32                                                 reserved4574;	//0xC4504A54
	UINT32                                                 reserved4575;	//0xC4504A58
	UINT32                                                 reserved4576;	//0xC4504A5C
	UINT32                                                 reserved4577;	//0xC4504A60
	UINT32                                                 reserved4578;	//0xC4504A64
	UINT32                                                 reserved4579;	//0xC4504A68
	UINT32                                                 reserved4580;	//0xC4504A6C
	UINT32                                                 reserved4581;	//0xC4504A70
	UINT32                                                 reserved4582;	//0xC4504A74
	UINT32                                                 reserved4583;	//0xC4504A78
	UINT32                                                 reserved4584;	//0xC4504A7C
	UINT32                                                 reserved4585;	//0xC4504A80
	UINT32                                                 reserved4586;	//0xC4504A84
	UINT32                                                 reserved4587;	//0xC4504A88
	UINT32                                                 reserved4588;	//0xC4504A8C
	UINT32                                                 reserved4589;	//0xC4504A90
	UINT32                                                 reserved4590;	//0xC4504A94
	UINT32                                                 reserved4591;	//0xC4504A98
	UINT32                                                 reserved4592;	//0xC4504A9C
	UINT32                                                 reserved4593;	//0xC4504AA0
	UINT32                                                 reserved4594;	//0xC4504AA4
	UINT32                                                 reserved4595;	//0xC4504AA8
	UINT32                                                 reserved4596;	//0xC4504AAC
	UINT32                                                 reserved4597;	//0xC4504AB0
	UINT32                                                 reserved4598;	//0xC4504AB4
	UINT32                                                 reserved4599;	//0xC4504AB8
	UINT32                                                 reserved4600;	//0xC4504ABC
	UINT32                                                 reserved4601;	//0xC4504AC0
	UINT32                                                 reserved4602;	//0xC4504AC4
	UINT32                                                 reserved4603;	//0xC4504AC8
	UINT32                                                 reserved4604;	//0xC4504ACC
	UINT32                                                 reserved4605;	//0xC4504AD0
	UINT32                                                 reserved4606;	//0xC4504AD4
	UINT32                                                 reserved4607;	//0xC4504AD8
	UINT32                                                 reserved4608;	//0xC4504ADC
	UINT32                                                 reserved4609;	//0xC4504AE0
	UINT32                                                 reserved4610;	//0xC4504AE4
	UINT32                                                 reserved4611;	//0xC4504AE8
	UINT32                                                 reserved4612;	//0xC4504AEC
	UINT32                                                 reserved4613;	//0xC4504AF0
	UINT32                                                 reserved4614;	//0xC4504AF4
	UINT32                                                 reserved4615;	//0xC4504AF8
	UINT32                                                 reserved4616;	//0xC4504AFC
	UINT32                                                 reserved4617;	//0xC4504B00
	UINT32                                                 reserved4618;	//0xC4504B04
	UINT32                                                 reserved4619;	//0xC4504B08
	UINT32                                                 reserved4620;	//0xC4504B0C
	UINT32                                                 reserved4621;	//0xC4504B10
	UINT32                                                 reserved4622;	//0xC4504B14
	UINT32                                                 reserved4623;	//0xC4504B18
	UINT32                                                 reserved4624;	//0xC4504B1C
	UINT32                                                 reserved4625;	//0xC4504B20
	UINT32                                                 reserved4626;	//0xC4504B24
	UINT32                                                 reserved4627;	//0xC4504B28
	UINT32                                                 reserved4628;	//0xC4504B2C
	UINT32                                                 reserved4629;	//0xC4504B30
	UINT32                                                 reserved4630;	//0xC4504B34
	UINT32                                                 reserved4631;	//0xC4504B38
	UINT32                                                 reserved4632;	//0xC4504B3C
	UINT32                                                 reserved4633;	//0xC4504B40
	UINT32                                                 reserved4634;	//0xC4504B44
	UINT32                                                 reserved4635;	//0xC4504B48
	UINT32                                                 reserved4636;	//0xC4504B4C
	UINT32                                                 reserved4637;	//0xC4504B50
	UINT32                                                 reserved4638;	//0xC4504B54
	UINT32                                                 reserved4639;	//0xC4504B58
	UINT32                                                 reserved4640;	//0xC4504B5C
	UINT32                                                 reserved4641;	//0xC4504B60
	UINT32                                                 reserved4642;	//0xC4504B64
	UINT32                                                 reserved4643;	//0xC4504B68
	UINT32                                                 reserved4644;	//0xC4504B6C
	UINT32                                                 reserved4645;	//0xC4504B70
	UINT32                                                 reserved4646;	//0xC4504B74
	UINT32                                                 reserved4647;	//0xC4504B78
	UINT32                                                 reserved4648;	//0xC4504B7C
	UINT32                                                 reserved4649;	//0xC4504B80
	UINT32                                                 reserved4650;	//0xC4504B84
	UINT32                                                 reserved4651;	//0xC4504B88
	UINT32                                                 reserved4652;	//0xC4504B8C
	UINT32                                                 reserved4653;	//0xC4504B90
	UINT32                                                 reserved4654;	//0xC4504B94
	UINT32                                                 reserved4655;	//0xC4504B98
	UINT32                                                 reserved4656;	//0xC4504B9C
	UINT32                                                 reserved4657;	//0xC4504BA0
	UINT32                                                 reserved4658;	//0xC4504BA4
	UINT32                                                 reserved4659;	//0xC4504BA8
	UINT32                                                 reserved4660;	//0xC4504BAC
	UINT32                                                 reserved4661;	//0xC4504BB0
	UINT32                                                 reserved4662;	//0xC4504BB4
	UINT32                                                 reserved4663;	//0xC4504BB8
	UINT32                                                 reserved4664;	//0xC4504BBC
	UINT32                                                 reserved4665;	//0xC4504BC0
	UINT32                                                 reserved4666;	//0xC4504BC4
	UINT32                                                 reserved4667;	//0xC4504BC8
	UINT32                                                 reserved4668;	//0xC4504BCC
	UINT32                                                 reserved4669;	//0xC4504BD0
	UINT32                                                 reserved4670;	//0xC4504BD4
	UINT32                                                 reserved4671;	//0xC4504BD8
	UINT32                                                 reserved4672;	//0xC4504BDC
	UINT32                                                 reserved4673;	//0xC4504BE0
	UINT32                                                 reserved4674;	//0xC4504BE4
	UINT32                                                 reserved4675;	//0xC4504BE8
	UINT32                                                 reserved4676;	//0xC4504BEC
	UINT32                                                 reserved4677;	//0xC4504BF0
	UINT32                                                 reserved4678;	//0xC4504BF4
	UINT32                                                 reserved4679;	//0xC4504BF8
	UINT32                                                 reserved4680;	//0xC4504BFC
	UINT32                                                 reserved4681;	//0xC4504C00
	UINT32                                                 reserved4682;	//0xC4504C04
	UINT32                                                 reserved4683;	//0xC4504C08
	UINT32                                                 reserved4684;	//0xC4504C0C
	UINT32                                                 reserved4685;	//0xC4504C10
	UINT32                                                 reserved4686;	//0xC4504C14
	UINT32                                                 reserved4687;	//0xC4504C18
	UINT32                                                 reserved4688;	//0xC4504C1C
	UINT32                                                 reserved4689;	//0xC4504C20
	UINT32                                                 reserved4690;	//0xC4504C24
	UINT32                                                 reserved4691;	//0xC4504C28
	UINT32                                                 reserved4692;	//0xC4504C2C
	UINT32                                                 reserved4693;	//0xC4504C30
	UINT32                                                 reserved4694;	//0xC4504C34
	UINT32                                                 reserved4695;	//0xC4504C38
	UINT32                                                 reserved4696;	//0xC4504C3C
	UINT32                                                 reserved4697;	//0xC4504C40
	UINT32                                                 reserved4698;	//0xC4504C44
	UINT32                                                 reserved4699;	//0xC4504C48
	UINT32                                                 reserved4700;	//0xC4504C4C
	UINT32                                                 reserved4701;	//0xC4504C50
	UINT32                                                 reserved4702;	//0xC4504C54
	UINT32                                                 reserved4703;	//0xC4504C58
	UINT32                                                 reserved4704;	//0xC4504C5C
	UINT32                                                 reserved4705;	//0xC4504C60
	UINT32                                                 reserved4706;	//0xC4504C64
	UINT32                                                 reserved4707;	//0xC4504C68
	UINT32                                                 reserved4708;	//0xC4504C6C
	UINT32                                                 reserved4709;	//0xC4504C70
	UINT32                                                 reserved4710;	//0xC4504C74
	UINT32                                                 reserved4711;	//0xC4504C78
	UINT32                                                 reserved4712;	//0xC4504C7C
	UINT32                                                 reserved4713;	//0xC4504C80
	UINT32                                                 reserved4714;	//0xC4504C84
	UINT32                                                 reserved4715;	//0xC4504C88
	UINT32                                                 reserved4716;	//0xC4504C8C
	UINT32                                                 reserved4717;	//0xC4504C90
	UINT32                                                 reserved4718;	//0xC4504C94
	UINT32                                                 reserved4719;	//0xC4504C98
	UINT32                                                 reserved4720;	//0xC4504C9C
	UINT32                                                 reserved4721;	//0xC4504CA0
	UINT32                                                 reserved4722;	//0xC4504CA4
	UINT32                                                 reserved4723;	//0xC4504CA8
	UINT32                                                 reserved4724;	//0xC4504CAC
	UINT32                                                 reserved4725;	//0xC4504CB0
	UINT32                                                 reserved4726;	//0xC4504CB4
	UINT32                                                 reserved4727;	//0xC4504CB8
	UINT32                                                 reserved4728;	//0xC4504CBC
	UINT32                                                 reserved4729;	//0xC4504CC0
	UINT32                                                 reserved4730;	//0xC4504CC4
	UINT32                                                 reserved4731;	//0xC4504CC8
	UINT32                                                 reserved4732;	//0xC4504CCC
	UINT32                                                 reserved4733;	//0xC4504CD0
	UINT32                                                 reserved4734;	//0xC4504CD4
	UINT32                                                 reserved4735;	//0xC4504CD8
	UINT32                                                 reserved4736;	//0xC4504CDC
	UINT32                                                 reserved4737;	//0xC4504CE0
	UINT32                                                 reserved4738;	//0xC4504CE4
	UINT32                                                 reserved4739;	//0xC4504CE8
	UINT32                                                 reserved4740;	//0xC4504CEC
	UINT32                                                 reserved4741;	//0xC4504CF0
	UINT32                                                 reserved4742;	//0xC4504CF4
	UINT32                                                 reserved4743;	//0xC4504CF8
	UINT32                                                 reserved4744;	//0xC4504CFC
	UINT32                                                 reserved4745;	//0xC4504D00
	UINT32                                                 reserved4746;	//0xC4504D04
	UINT32                                                 reserved4747;	//0xC4504D08
	UINT32                                                 reserved4748;	//0xC4504D0C
	UINT32                                                 reserved4749;	//0xC4504D10
	UINT32                                                 reserved4750;	//0xC4504D14
	UINT32                                                 reserved4751;	//0xC4504D18
	UINT32                                                 reserved4752;	//0xC4504D1C
	UINT32                                                 reserved4753;	//0xC4504D20
	UINT32                                                 reserved4754;	//0xC4504D24
	UINT32                                                 reserved4755;	//0xC4504D28
	UINT32                                                 reserved4756;	//0xC4504D2C
	UINT32                                                 reserved4757;	//0xC4504D30
	UINT32                                                 reserved4758;	//0xC4504D34
	UINT32                                                 reserved4759;	//0xC4504D38
	UINT32                                                 reserved4760;	//0xC4504D3C
	UINT32                                                 reserved4761;	//0xC4504D40
	UINT32                                                 reserved4762;	//0xC4504D44
	UINT32                                                 reserved4763;	//0xC4504D48
	UINT32                                                 reserved4764;	//0xC4504D4C
	UINT32                                                 reserved4765;	//0xC4504D50
	UINT32                                                 reserved4766;	//0xC4504D54
	UINT32                                                 reserved4767;	//0xC4504D58
	UINT32                                                 reserved4768;	//0xC4504D5C
	UINT32                                                 reserved4769;	//0xC4504D60
	UINT32                                                 reserved4770;	//0xC4504D64
	UINT32                                                 reserved4771;	//0xC4504D68
	UINT32                                                 reserved4772;	//0xC4504D6C
	UINT32                                                 reserved4773;	//0xC4504D70
	UINT32                                                 reserved4774;	//0xC4504D74
	UINT32                                                 reserved4775;	//0xC4504D78
	UINT32                                                 reserved4776;	//0xC4504D7C
	UINT32                                                 reserved4777;	//0xC4504D80
	UINT32                                                 reserved4778;	//0xC4504D84
	UINT32                                                 reserved4779;	//0xC4504D88
	UINT32                                                 reserved4780;	//0xC4504D8C
	UINT32                                                 reserved4781;	//0xC4504D90
	UINT32                                                 reserved4782;	//0xC4504D94
	UINT32                                                 reserved4783;	//0xC4504D98
	UINT32                                                 reserved4784;	//0xC4504D9C
	UINT32                                                 reserved4785;	//0xC4504DA0
	UINT32                                                 reserved4786;	//0xC4504DA4
	UINT32                                                 reserved4787;	//0xC4504DA8
	UINT32                                                 reserved4788;	//0xC4504DAC
	UINT32                                                 reserved4789;	//0xC4504DB0
	UINT32                                                 reserved4790;	//0xC4504DB4
	UINT32                                                 reserved4791;	//0xC4504DB8
	UINT32                                                 reserved4792;	//0xC4504DBC
	UINT32                                                 reserved4793;	//0xC4504DC0
	UINT32                                                 reserved4794;	//0xC4504DC4
	UINT32                                                 reserved4795;	//0xC4504DC8
	UINT32                                                 reserved4796;	//0xC4504DCC
	UINT32                                                 reserved4797;	//0xC4504DD0
	UINT32                                                 reserved4798;	//0xC4504DD4
	UINT32                                                 reserved4799;	//0xC4504DD8
	UINT32                                                 reserved4800;	//0xC4504DDC
	UINT32                                                 reserved4801;	//0xC4504DE0
	UINT32                                                 reserved4802;	//0xC4504DE4
	UINT32                                                 reserved4803;	//0xC4504DE8
	UINT32                                                 reserved4804;	//0xC4504DEC
	UINT32                                                 reserved4805;	//0xC4504DF0
	UINT32                                                 reserved4806;	//0xC4504DF4
	UINT32                                                 reserved4807;	//0xC4504DF8
	UINT32                                                 reserved4808;	//0xC4504DFC
	UINT32                                                 reserved4809;	//0xC4504E00
	UINT32                                                 reserved4810;	//0xC4504E04
	UINT32                                                 reserved4811;	//0xC4504E08
	UINT32                                                 reserved4812;	//0xC4504E0C
	UINT32                                                 reserved4813;	//0xC4504E10
	UINT32                                                 reserved4814;	//0xC4504E14
	UINT32                                                 reserved4815;	//0xC4504E18
	UINT32                                                 reserved4816;	//0xC4504E1C
	UINT32                                                 reserved4817;	//0xC4504E20
	UINT32                                                 reserved4818;	//0xC4504E24
	UINT32                                                 reserved4819;	//0xC4504E28
	UINT32                                                 reserved4820;	//0xC4504E2C
	UINT32                                                 reserved4821;	//0xC4504E30
	UINT32                                                 reserved4822;	//0xC4504E34
	UINT32                                                 reserved4823;	//0xC4504E38
	UINT32                                                 reserved4824;	//0xC4504E3C
	UINT32                                                 reserved4825;	//0xC4504E40
	UINT32                                                 reserved4826;	//0xC4504E44
	UINT32                                                 reserved4827;	//0xC4504E48
	UINT32                                                 reserved4828;	//0xC4504E4C
	UINT32                                                 reserved4829;	//0xC4504E50
	UINT32                                                 reserved4830;	//0xC4504E54
	UINT32                                                 reserved4831;	//0xC4504E58
	UINT32                                                 reserved4832;	//0xC4504E5C
	UINT32                                                 reserved4833;	//0xC4504E60
	UINT32                                                 reserved4834;	//0xC4504E64
	UINT32                                                 reserved4835;	//0xC4504E68
	UINT32                                                 reserved4836;	//0xC4504E6C
	UINT32                                                 reserved4837;	//0xC4504E70
	UINT32                                                 reserved4838;	//0xC4504E74
	UINT32                                                 reserved4839;	//0xC4504E78
	UINT32                                                 reserved4840;	//0xC4504E7C
	UINT32                                                 reserved4841;	//0xC4504E80
	UINT32                                                 reserved4842;	//0xC4504E84
	UINT32                                                 reserved4843;	//0xC4504E88
	UINT32                                                 reserved4844;	//0xC4504E8C
	UINT32                                                 reserved4845;	//0xC4504E90
	UINT32                                                 reserved4846;	//0xC4504E94
	UINT32                                                 reserved4847;	//0xC4504E98
	UINT32                                                 reserved4848;	//0xC4504E9C
	UINT32                                                 reserved4849;	//0xC4504EA0
	UINT32                                                 reserved4850;	//0xC4504EA4
	UINT32                                                 reserved4851;	//0xC4504EA8
	UINT32                                                 reserved4852;	//0xC4504EAC
	UINT32                                                 reserved4853;	//0xC4504EB0
	UINT32                                                 reserved4854;	//0xC4504EB4
	UINT32                                                 reserved4855;	//0xC4504EB8
	UINT32                                                 reserved4856;	//0xC4504EBC
	UINT32                                                 reserved4857;	//0xC4504EC0
	UINT32                                                 reserved4858;	//0xC4504EC4
	UINT32                                                 reserved4859;	//0xC4504EC8
	UINT32                                                 reserved4860;	//0xC4504ECC
	UINT32                                                 reserved4861;	//0xC4504ED0
	UINT32                                                 reserved4862;	//0xC4504ED4
	UINT32                                                 reserved4863;	//0xC4504ED8
	UINT32                                                 reserved4864;	//0xC4504EDC
	UINT32                                                 reserved4865;	//0xC4504EE0
	UINT32                                                 reserved4866;	//0xC4504EE4
	UINT32                                                 reserved4867;	//0xC4504EE8
	UINT32                                                 reserved4868;	//0xC4504EEC
	UINT32                                                 reserved4869;	//0xC4504EF0
	UINT32                                                 reserved4870;	//0xC4504EF4
	UINT32                                                 reserved4871;	//0xC4504EF8
	UINT32                                                 reserved4872;	//0xC4504EFC
	UINT32                                                 reserved4873;	//0xC4504F00
	UINT32                                                 reserved4874;	//0xC4504F04
	UINT32                                                 reserved4875;	//0xC4504F08
	UINT32                                                 reserved4876;	//0xC4504F0C
	UINT32                                                 reserved4877;	//0xC4504F10
	UINT32                                                 reserved4878;	//0xC4504F14
	UINT32                                                 reserved4879;	//0xC4504F18
	UINT32                                                 reserved4880;	//0xC4504F1C
	UINT32                                                 reserved4881;	//0xC4504F20
	UINT32                                                 reserved4882;	//0xC4504F24
	UINT32                                                 reserved4883;	//0xC4504F28
	UINT32                                                 reserved4884;	//0xC4504F2C
	UINT32                                                 reserved4885;	//0xC4504F30
	UINT32                                                 reserved4886;	//0xC4504F34
	UINT32                                                 reserved4887;	//0xC4504F38
	UINT32                                                 reserved4888;	//0xC4504F3C
	UINT32                                                 reserved4889;	//0xC4504F40
	UINT32                                                 reserved4890;	//0xC4504F44
	UINT32                                                 reserved4891;	//0xC4504F48
	UINT32                                                 reserved4892;	//0xC4504F4C
	UINT32                                                 reserved4893;	//0xC4504F50
	UINT32                                                 reserved4894;	//0xC4504F54
	UINT32                                                 reserved4895;	//0xC4504F58
	UINT32                                                 reserved4896;	//0xC4504F5C
	UINT32                                                 reserved4897;	//0xC4504F60
	UINT32                                                 reserved4898;	//0xC4504F64
	UINT32                                                 reserved4899;	//0xC4504F68
	UINT32                                                 reserved4900;	//0xC4504F6C
	UINT32                                                 reserved4901;	//0xC4504F70
	UINT32                                                 reserved4902;	//0xC4504F74
	UINT32                                                 reserved4903;	//0xC4504F78
	UINT32                                                 reserved4904;	//0xC4504F7C
	UINT32                                                 reserved4905;	//0xC4504F80
	UINT32                                                 reserved4906;	//0xC4504F84
	UINT32                                                 reserved4907;	//0xC4504F88
	UINT32                                                 reserved4908;	//0xC4504F8C
	UINT32                                                 reserved4909;	//0xC4504F90
	UINT32                                                 reserved4910;	//0xC4504F94
	UINT32                                                 reserved4911;	//0xC4504F98
	UINT32                                                 reserved4912;	//0xC4504F9C
	UINT32                                                 reserved4913;	//0xC4504FA0
	UINT32                                                 reserved4914;	//0xC4504FA4
	UINT32                                                 reserved4915;	//0xC4504FA8
	UINT32                                                 reserved4916;	//0xC4504FAC
	UINT32                                                 reserved4917;	//0xC4504FB0
	UINT32                                                 reserved4918;	//0xC4504FB4
	UINT32                                                 reserved4919;	//0xC4504FB8
	UINT32                                                 reserved4920;	//0xC4504FBC
	UINT32                                                 reserved4921;	//0xC4504FC0
	UINT32                                                 reserved4922;	//0xC4504FC4
	UINT32                                                 reserved4923;	//0xC4504FC8
	UINT32                                                 reserved4924;	//0xC4504FCC
	UINT32                                                 reserved4925;	//0xC4504FD0
	UINT32                                                 reserved4926;	//0xC4504FD4
	UINT32                                                 reserved4927;	//0xC4504FD8
	UINT32                                                 reserved4928;	//0xC4504FDC
	UINT32                                                 reserved4929;	//0xC4504FE0
	UINT32                                                 reserved4930;	//0xC4504FE4
	UINT32                                                 reserved4931;	//0xC4504FE8
	UINT32                                                 reserved4932;	//0xC4504FEC
	UINT32                                                 reserved4933;	//0xC4504FF0
	UINT32                                                 reserved4934;	//0xC4504FF4
	UINT32                                                 reserved4935;	//0xC4504FF8
	UINT32                                                 reserved4936;	//0xC4504FFC
	REG_DDRC_M2_DEBUG_COMMON_T                             debug_common;	//0xC4505000
	REG_DDRC_M2_DEBUG_PERIOD_T                             debug_period;	//0xC4505004
	UINT32                                                 reserved4937;	//0xC4505008
	UINT32                                                 reserved4938;	//0xC450500C
	REG_DDRC_M2_IRQ_MASK_T                                     irq_mask;	//0xC4505010
	REG_DDRC_M2_IRQ_STATUS_T                                 irq_status;	//0xC4505014
	UINT32                                                 reserved4939;	//0xC4505018
	UINT32                                                 reserved4940;	//0xC450501C
	UINT32                                                 reserved4941;	//0xC4505020
	UINT32                                                 reserved4942;	//0xC4505024
	UINT32                                                 reserved4943;	//0xC4505028
	UINT32                                                 reserved4944;	//0xC450502C
	UINT32                                                 reserved4945;	//0xC4505030
	UINT32                                                 reserved4946;	//0xC4505034
	UINT32                                                 reserved4947;	//0xC4505038
	UINT32                                                 reserved4948;	//0xC450503C
	UINT32                                                 reserved4949;	//0xC4505040
	UINT32                                                 reserved4950;	//0xC4505044
	UINT32                                                 reserved4951;	//0xC4505048
	UINT32                                                 reserved4952;	//0xC450504C
	UINT32                                                 reserved4953;	//0xC4505050
	UINT32                                                 reserved4954;	//0xC4505054
	UINT32                                                 reserved4955;	//0xC4505058
	UINT32                                                 reserved4956;	//0xC450505C
	UINT32                                                 reserved4957;	//0xC4505060
	UINT32                                                 reserved4958;	//0xC4505064
	UINT32                                                 reserved4959;	//0xC4505068
	UINT32                                                 reserved4960;	//0xC450506C
	UINT32                                                 reserved4961;	//0xC4505070
	UINT32                                                 reserved4962;	//0xC4505074
	UINT32                                                 reserved4963;	//0xC4505078
	UINT32                                                 reserved4964;	//0xC450507C
	UINT32                                                 reserved4965;	//0xC4505080
	UINT32                                                 reserved4966;	//0xC4505084
	UINT32                                                 reserved4967;	//0xC4505088
	UINT32                                                 reserved4968;	//0xC450508C
	UINT32                                                 reserved4969;	//0xC4505090
	UINT32                                                 reserved4970;	//0xC4505094
	UINT32                                                 reserved4971;	//0xC4505098
	UINT32                                                 reserved4972;	//0xC450509C
	UINT32                                                 reserved4973;	//0xC45050A0
	UINT32                                                 reserved4974;	//0xC45050A4
	UINT32                                                 reserved4975;	//0xC45050A8
	UINT32                                                 reserved4976;	//0xC45050AC
	UINT32                                                 reserved4977;	//0xC45050B0
	UINT32                                                 reserved4978;	//0xC45050B4
	UINT32                                                 reserved4979;	//0xC45050B8
	UINT32                                                 reserved4980;	//0xC45050BC
	UINT32                                                 reserved4981;	//0xC45050C0
	UINT32                                                 reserved4982;	//0xC45050C4
	UINT32                                                 reserved4983;	//0xC45050C8
	UINT32                                                 reserved4984;	//0xC45050CC
	UINT32                                                 reserved4985;	//0xC45050D0
	UINT32                                                 reserved4986;	//0xC45050D4
	UINT32                                                 reserved4987;	//0xC45050D8
	UINT32                                                 reserved4988;	//0xC45050DC
	UINT32                                                 reserved4989;	//0xC45050E0
	UINT32                                                 reserved4990;	//0xC45050E4
	UINT32                                                 reserved4991;	//0xC45050E8
	UINT32                                                 reserved4992;	//0xC45050EC
	UINT32                                                 reserved4993;	//0xC45050F0
	UINT32                                                 reserved4994;	//0xC45050F4
	UINT32                                                 reserved4995;	//0xC45050F8
	UINT32                                                 reserved4996;	//0xC45050FC
	REG_DDRC_M2_DEBUG_BUS_IF_T                             debug_bus_if;	//0xC4505100
	UINT32                                                 reserved4997;	//0xC4505104
	UINT32                                                 reserved4998;	//0xC4505108
	UINT32                                                 reserved4999;	//0xC450510C
	UINT32                                                 reserved5000;	//0xC4505110
	UINT32                                                 reserved5001;	//0xC4505114
	UINT32                                                 reserved5002;	//0xC4505118
	UINT32                                                 reserved5003;	//0xC450511C
	UINT32                                                 reserved5004;	//0xC4505120
	UINT32                                                 reserved5005;	//0xC4505124
	UINT32                                                 reserved5006;	//0xC4505128
	UINT32                                                 reserved5007;	//0xC450512C
	UINT32                                                 reserved5008;	//0xC4505130
	UINT32                                                 reserved5009;	//0xC4505134
	UINT32                                                 reserved5010;	//0xC4505138
	UINT32                                                 reserved5011;	//0xC450513C
	UINT32                                                 reserved5012;	//0xC4505140
	UINT32                                                 reserved5013;	//0xC4505144
	UINT32                                                 reserved5014;	//0xC4505148
	UINT32                                                 reserved5015;	//0xC450514C
	UINT32                                                 reserved5016;	//0xC4505150
	UINT32                                                 reserved5017;	//0xC4505154
	UINT32                                                 reserved5018;	//0xC4505158
	UINT32                                                 reserved5019;	//0xC450515C
	UINT32                                                 reserved5020;	//0xC4505160
	UINT32                                                 reserved5021;	//0xC4505164
	UINT32                                                 reserved5022;	//0xC4505168
	UINT32                                                 reserved5023;	//0xC450516C
	UINT32                                                 reserved5024;	//0xC4505170
	UINT32                                                 reserved5025;	//0xC4505174
	UINT32                                                 reserved5026;	//0xC4505178
	UINT32                                                 reserved5027;	//0xC450517C
	UINT32                                                 reserved5028;	//0xC4505180
	UINT32                                                 reserved5029;	//0xC4505184
	UINT32                                                 reserved5030;	//0xC4505188
	UINT32                                                 reserved5031;	//0xC450518C
	UINT32                                                 reserved5032;	//0xC4505190
	UINT32                                                 reserved5033;	//0xC4505194
	UINT32                                                 reserved5034;	//0xC4505198
	UINT32                                                 reserved5035;	//0xC450519C
	UINT32                                                 reserved5036;	//0xC45051A0
	UINT32                                                 reserved5037;	//0xC45051A4
	UINT32                                                 reserved5038;	//0xC45051A8
	UINT32                                                 reserved5039;	//0xC45051AC
	UINT32                                                 reserved5040;	//0xC45051B0
	UINT32                                                 reserved5041;	//0xC45051B4
	UINT32                                                 reserved5042;	//0xC45051B8
	UINT32                                                 reserved5043;	//0xC45051BC
	UINT32                                                 reserved5044;	//0xC45051C0
	UINT32                                                 reserved5045;	//0xC45051C4
	UINT32                                                 reserved5046;	//0xC45051C8
	UINT32                                                 reserved5047;	//0xC45051CC
	UINT32                                                 reserved5048;	//0xC45051D0
	UINT32                                                 reserved5049;	//0xC45051D4
	UINT32                                                 reserved5050;	//0xC45051D8
	UINT32                                                 reserved5051;	//0xC45051DC
	UINT32                                                 reserved5052;	//0xC45051E0
	UINT32                                                 reserved5053;	//0xC45051E4
	UINT32                                                 reserved5054;	//0xC45051E8
	UINT32                                                 reserved5055;	//0xC45051EC
	UINT32                                                 reserved5056;	//0xC45051F0
	UINT32                                                 reserved5057;	//0xC45051F4
	UINT32                                                 reserved5058;	//0xC45051F8
	UINT32                                                 reserved5059;	//0xC45051FC
	REG_DDRC_M2_DEBUG_PORT_IF_0_T                       debug_port_if_0;	//0xC4505200
	REG_DDRC_M2_DEBUG_PORT_IF_1_T                       debug_port_if_1;	//0xC4505204
	REG_DDRC_M2_DEBUG_PORT_IF_2_T                       debug_port_if_2;	//0xC4505208
	REG_DDRC_M2_DEBUG_PORT_IF_3_T                       debug_port_if_3;	//0xC450520C
	REG_DDRC_M2_DEBUG_PORT_IF_4_T                       debug_port_if_4;	//0xC4505210
	REG_DDRC_M2_DEBUG_PORT_IF_5_T                       debug_port_if_5;	//0xC4505214
	REG_DDRC_M2_DEBUG_PORT_IF_6_T                       debug_port_if_6;	//0xC4505218
	REG_DDRC_M2_DEBUG_PORT_IF_7_T                       debug_port_if_7;	//0xC450521C
	UINT32                                                 reserved5060;	//0xC4505220
	UINT32                                                 reserved5061;	//0xC4505224
	UINT32                                                 reserved5062;	//0xC4505228
	UINT32                                                 reserved5063;	//0xC450522C
	UINT32                                                 reserved5064;	//0xC4505230
	UINT32                                                 reserved5065;	//0xC4505234
	UINT32                                                 reserved5066;	//0xC4505238
	UINT32                                                 reserved5067;	//0xC450523C
	UINT32                                                 reserved5068;	//0xC4505240
	UINT32                                                 reserved5069;	//0xC4505244
	UINT32                                                 reserved5070;	//0xC4505248
	UINT32                                                 reserved5071;	//0xC450524C
	UINT32                                                 reserved5072;	//0xC4505250
	UINT32                                                 reserved5073;	//0xC4505254
	UINT32                                                 reserved5074;	//0xC4505258
	UINT32                                                 reserved5075;	//0xC450525C
	UINT32                                                 reserved5076;	//0xC4505260
	UINT32                                                 reserved5077;	//0xC4505264
	UINT32                                                 reserved5078;	//0xC4505268
	UINT32                                                 reserved5079;	//0xC450526C
	UINT32                                                 reserved5080;	//0xC4505270
	UINT32                                                 reserved5081;	//0xC4505274
	UINT32                                                 reserved5082;	//0xC4505278
	UINT32                                                 reserved5083;	//0xC450527C
	UINT32                                                 reserved5084;	//0xC4505280
	UINT32                                                 reserved5085;	//0xC4505284
	UINT32                                                 reserved5086;	//0xC4505288
	UINT32                                                 reserved5087;	//0xC450528C
	UINT32                                                 reserved5088;	//0xC4505290
	UINT32                                                 reserved5089;	//0xC4505294
	UINT32                                                 reserved5090;	//0xC4505298
	UINT32                                                 reserved5091;	//0xC450529C
	UINT32                                                 reserved5092;	//0xC45052A0
	UINT32                                                 reserved5093;	//0xC45052A4
	UINT32                                                 reserved5094;	//0xC45052A8
	UINT32                                                 reserved5095;	//0xC45052AC
	UINT32                                                 reserved5096;	//0xC45052B0
	UINT32                                                 reserved5097;	//0xC45052B4
	UINT32                                                 reserved5098;	//0xC45052B8
	UINT32                                                 reserved5099;	//0xC45052BC
	UINT32                                                 reserved5100;	//0xC45052C0
	UINT32                                                 reserved5101;	//0xC45052C4
	UINT32                                                 reserved5102;	//0xC45052C8
	UINT32                                                 reserved5103;	//0xC45052CC
	UINT32                                                 reserved5104;	//0xC45052D0
	UINT32                                                 reserved5105;	//0xC45052D4
	UINT32                                                 reserved5106;	//0xC45052D8
	UINT32                                                 reserved5107;	//0xC45052DC
	UINT32                                                 reserved5108;	//0xC45052E0
	UINT32                                                 reserved5109;	//0xC45052E4
	UINT32                                                 reserved5110;	//0xC45052E8
	UINT32                                                 reserved5111;	//0xC45052EC
	UINT32                                                 reserved5112;	//0xC45052F0
	UINT32                                                 reserved5113;	//0xC45052F4
	UINT32                                                 reserved5114;	//0xC45052F8
	UINT32                                                 reserved5115;	//0xC45052FC
	REG_DDRC_M2_DEBUG_UQ_1_T                                 debug_uq_1;	//0xC4505300
	REG_DDRC_M2_DEBUG_UQ_2_T                                 debug_uq_2;	//0xC4505304
	UINT32                                                 reserved5116;	//0xC4505308
	UINT32                                                 reserved5117;	//0xC450530C
	UINT32                                                 reserved5118;	//0xC4505310
	UINT32                                                 reserved5119;	//0xC4505314
	UINT32                                                 reserved5120;	//0xC4505318
	UINT32                                                 reserved5121;	//0xC450531C
	UINT32                                                 reserved5122;	//0xC4505320
	UINT32                                                 reserved5123;	//0xC4505324
	UINT32                                                 reserved5124;	//0xC4505328
	UINT32                                                 reserved5125;	//0xC450532C
	UINT32                                                 reserved5126;	//0xC4505330
	UINT32                                                 reserved5127;	//0xC4505334
	UINT32                                                 reserved5128;	//0xC4505338
	UINT32                                                 reserved5129;	//0xC450533C
	UINT32                                                 reserved5130;	//0xC4505340
	UINT32                                                 reserved5131;	//0xC4505344
	UINT32                                                 reserved5132;	//0xC4505348
	UINT32                                                 reserved5133;	//0xC450534C
	UINT32                                                 reserved5134;	//0xC4505350
	UINT32                                                 reserved5135;	//0xC4505354
	UINT32                                                 reserved5136;	//0xC4505358
	UINT32                                                 reserved5137;	//0xC450535C
	UINT32                                                 reserved5138;	//0xC4505360
	UINT32                                                 reserved5139;	//0xC4505364
	UINT32                                                 reserved5140;	//0xC4505368
	UINT32                                                 reserved5141;	//0xC450536C
	UINT32                                                 reserved5142;	//0xC4505370
	UINT32                                                 reserved5143;	//0xC4505374
	UINT32                                                 reserved5144;	//0xC4505378
	UINT32                                                 reserved5145;	//0xC450537C
	UINT32                                                 reserved5146;	//0xC4505380
	UINT32                                                 reserved5147;	//0xC4505384
	UINT32                                                 reserved5148;	//0xC4505388
	UINT32                                                 reserved5149;	//0xC450538C
	UINT32                                                 reserved5150;	//0xC4505390
	UINT32                                                 reserved5151;	//0xC4505394
	UINT32                                                 reserved5152;	//0xC4505398
	UINT32                                                 reserved5153;	//0xC450539C
	UINT32                                                 reserved5154;	//0xC45053A0
	UINT32                                                 reserved5155;	//0xC45053A4
	UINT32                                                 reserved5156;	//0xC45053A8
	UINT32                                                 reserved5157;	//0xC45053AC
	UINT32                                                 reserved5158;	//0xC45053B0
	UINT32                                                 reserved5159;	//0xC45053B4
	UINT32                                                 reserved5160;	//0xC45053B8
	UINT32                                                 reserved5161;	//0xC45053BC
	UINT32                                                 reserved5162;	//0xC45053C0
	UINT32                                                 reserved5163;	//0xC45053C4
	UINT32                                                 reserved5164;	//0xC45053C8
	UINT32                                                 reserved5165;	//0xC45053CC
	UINT32                                                 reserved5166;	//0xC45053D0
	UINT32                                                 reserved5167;	//0xC45053D4
	UINT32                                                 reserved5168;	//0xC45053D8
	UINT32                                                 reserved5169;	//0xC45053DC
	UINT32                                                 reserved5170;	//0xC45053E0
	UINT32                                                 reserved5171;	//0xC45053E4
	UINT32                                                 reserved5172;	//0xC45053E8
	UINT32                                                 reserved5173;	//0xC45053EC
	UINT32                                                 reserved5174;	//0xC45053F0
	UINT32                                                 reserved5175;	//0xC45053F4
	UINT32                                                 reserved5176;	//0xC45053F8
	UINT32                                                 reserved5177;	//0xC45053FC
	REG_DDRC_M2_DEBUG_SCH0_T                                 debug_sch0;	//0xC4505400
	REG_DDRC_M2_DEBUG_SCH1_T                                 debug_sch1;	//0xC4505404
	UINT32                                                 reserved5178;	//0xC4505408
	UINT32                                                 reserved5179;	//0xC450540C
	UINT32                                                 reserved5180;	//0xC4505410
	UINT32                                                 reserved5181;	//0xC4505414
	UINT32                                                 reserved5182;	//0xC4505418
	UINT32                                                 reserved5183;	//0xC450541C
	UINT32                                                 reserved5184;	//0xC4505420
	UINT32                                                 reserved5185;	//0xC4505424
	UINT32                                                 reserved5186;	//0xC4505428
	UINT32                                                 reserved5187;	//0xC450542C
	UINT32                                                 reserved5188;	//0xC4505430
	UINT32                                                 reserved5189;	//0xC4505434
	UINT32                                                 reserved5190;	//0xC4505438
	UINT32                                                 reserved5191;	//0xC450543C
	UINT32                                                 reserved5192;	//0xC4505440
	UINT32                                                 reserved5193;	//0xC4505444
	UINT32                                                 reserved5194;	//0xC4505448
	UINT32                                                 reserved5195;	//0xC450544C
	UINT32                                                 reserved5196;	//0xC4505450
	UINT32                                                 reserved5197;	//0xC4505454
	UINT32                                                 reserved5198;	//0xC4505458
	UINT32                                                 reserved5199;	//0xC450545C
	UINT32                                                 reserved5200;	//0xC4505460
	UINT32                                                 reserved5201;	//0xC4505464
	UINT32                                                 reserved5202;	//0xC4505468
	UINT32                                                 reserved5203;	//0xC450546C
	UINT32                                                 reserved5204;	//0xC4505470
	UINT32                                                 reserved5205;	//0xC4505474
	UINT32                                                 reserved5206;	//0xC4505478
	UINT32                                                 reserved5207;	//0xC450547C
	UINT32                                                 reserved5208;	//0xC4505480
	UINT32                                                 reserved5209;	//0xC4505484
	UINT32                                                 reserved5210;	//0xC4505488
	UINT32                                                 reserved5211;	//0xC450548C
	UINT32                                                 reserved5212;	//0xC4505490
	UINT32                                                 reserved5213;	//0xC4505494
	UINT32                                                 reserved5214;	//0xC4505498
	UINT32                                                 reserved5215;	//0xC450549C
	UINT32                                                 reserved5216;	//0xC45054A0
	UINT32                                                 reserved5217;	//0xC45054A4
	UINT32                                                 reserved5218;	//0xC45054A8
	UINT32                                                 reserved5219;	//0xC45054AC
	UINT32                                                 reserved5220;	//0xC45054B0
	UINT32                                                 reserved5221;	//0xC45054B4
	UINT32                                                 reserved5222;	//0xC45054B8
	UINT32                                                 reserved5223;	//0xC45054BC
	UINT32                                                 reserved5224;	//0xC45054C0
	UINT32                                                 reserved5225;	//0xC45054C4
	UINT32                                                 reserved5226;	//0xC45054C8
	UINT32                                                 reserved5227;	//0xC45054CC
	UINT32                                                 reserved5228;	//0xC45054D0
	UINT32                                                 reserved5229;	//0xC45054D4
	UINT32                                                 reserved5230;	//0xC45054D8
	UINT32                                                 reserved5231;	//0xC45054DC
	UINT32                                                 reserved5232;	//0xC45054E0
	UINT32                                                 reserved5233;	//0xC45054E4
	UINT32                                                 reserved5234;	//0xC45054E8
	UINT32                                                 reserved5235;	//0xC45054EC
	UINT32                                                 reserved5236;	//0xC45054F0
	UINT32                                                 reserved5237;	//0xC45054F4
	UINT32                                                 reserved5238;	//0xC45054F8
	UINT32                                                 reserved5239;	//0xC45054FC
	REG_DDRC_M2_DEBUG_ALP_T                                   debug_alp;	//0xC4505500
	REG_DDRC_M2_DEBUG_ALP_ENTRY_NUM_T               debug_alp_entry_num;	//0xC4505504
	REG_DDRC_M2_DEBUG_ALP_TIME_T                         debug_alp_time;	//0xC4505508
	REG_DDRC_M2_DEBUG_ALP_WAIT_CNT_T                 debug_alp_wait_cnt;	//0xC450550C
	UINT32                                                 reserved5240;	//0xC4505510
	UINT32                                                 reserved5241;	//0xC4505514
	UINT32                                                 reserved5242;	//0xC4505518
	UINT32                                                 reserved5243;	//0xC450551C
	UINT32                                                 reserved5244;	//0xC4505520
	UINT32                                                 reserved5245;	//0xC4505524
	UINT32                                                 reserved5246;	//0xC4505528
	UINT32                                                 reserved5247;	//0xC450552C
	UINT32                                                 reserved5248;	//0xC4505530
	UINT32                                                 reserved5249;	//0xC4505534
	UINT32                                                 reserved5250;	//0xC4505538
	UINT32                                                 reserved5251;	//0xC450553C
	UINT32                                                 reserved5252;	//0xC4505540
	UINT32                                                 reserved5253;	//0xC4505544
	UINT32                                                 reserved5254;	//0xC4505548
	UINT32                                                 reserved5255;	//0xC450554C
	UINT32                                                 reserved5256;	//0xC4505550
	UINT32                                                 reserved5257;	//0xC4505554
	UINT32                                                 reserved5258;	//0xC4505558
	UINT32                                                 reserved5259;	//0xC450555C
	UINT32                                                 reserved5260;	//0xC4505560
	UINT32                                                 reserved5261;	//0xC4505564
	UINT32                                                 reserved5262;	//0xC4505568
	UINT32                                                 reserved5263;	//0xC450556C
	UINT32                                                 reserved5264;	//0xC4505570
	UINT32                                                 reserved5265;	//0xC4505574
	UINT32                                                 reserved5266;	//0xC4505578
	UINT32                                                 reserved5267;	//0xC450557C
	UINT32                                                 reserved5268;	//0xC4505580
	UINT32                                                 reserved5269;	//0xC4505584
	UINT32                                                 reserved5270;	//0xC4505588
	UINT32                                                 reserved5271;	//0xC450558C
	UINT32                                                 reserved5272;	//0xC4505590
	UINT32                                                 reserved5273;	//0xC4505594
	UINT32                                                 reserved5274;	//0xC4505598
	UINT32                                                 reserved5275;	//0xC450559C
	UINT32                                                 reserved5276;	//0xC45055A0
	UINT32                                                 reserved5277;	//0xC45055A4
	UINT32                                                 reserved5278;	//0xC45055A8
	UINT32                                                 reserved5279;	//0xC45055AC
	UINT32                                                 reserved5280;	//0xC45055B0
	UINT32                                                 reserved5281;	//0xC45055B4
	UINT32                                                 reserved5282;	//0xC45055B8
	UINT32                                                 reserved5283;	//0xC45055BC
	UINT32                                                 reserved5284;	//0xC45055C0
	UINT32                                                 reserved5285;	//0xC45055C4
	UINT32                                                 reserved5286;	//0xC45055C8
	UINT32                                                 reserved5287;	//0xC45055CC
	UINT32                                                 reserved5288;	//0xC45055D0
	UINT32                                                 reserved5289;	//0xC45055D4
	UINT32                                                 reserved5290;	//0xC45055D8
	UINT32                                                 reserved5291;	//0xC45055DC
	UINT32                                                 reserved5292;	//0xC45055E0
	UINT32                                                 reserved5293;	//0xC45055E4
	UINT32                                                 reserved5294;	//0xC45055E8
	UINT32                                                 reserved5295;	//0xC45055EC
	UINT32                                                 reserved5296;	//0xC45055F0
	UINT32                                                 reserved5297;	//0xC45055F4
	UINT32                                                 reserved5298;	//0xC45055F8
	UINT32                                                 reserved5299;	//0xC45055FC
	REG_DDRC_M2_DEBUG_DFS_T                                   debug_dfs;	//0xC4505600
	UINT32                                                 reserved5300;	//0xC4505604
	UINT32                                                 reserved5301;	//0xC4505608
	UINT32                                                 reserved5302;	//0xC450560C
	UINT32                                                 reserved5303;	//0xC4505610
	UINT32                                                 reserved5304;	//0xC4505614
	UINT32                                                 reserved5305;	//0xC4505618
	UINT32                                                 reserved5306;	//0xC450561C
	UINT32                                                 reserved5307;	//0xC4505620
	UINT32                                                 reserved5308;	//0xC4505624
	UINT32                                                 reserved5309;	//0xC4505628
	UINT32                                                 reserved5310;	//0xC450562C
	UINT32                                                 reserved5311;	//0xC4505630
	UINT32                                                 reserved5312;	//0xC4505634
	UINT32                                                 reserved5313;	//0xC4505638
	UINT32                                                 reserved5314;	//0xC450563C
	UINT32                                                 reserved5315;	//0xC4505640
	UINT32                                                 reserved5316;	//0xC4505644
	UINT32                                                 reserved5317;	//0xC4505648
	UINT32                                                 reserved5318;	//0xC450564C
	UINT32                                                 reserved5319;	//0xC4505650
	UINT32                                                 reserved5320;	//0xC4505654
	UINT32                                                 reserved5321;	//0xC4505658
	UINT32                                                 reserved5322;	//0xC450565C
	UINT32                                                 reserved5323;	//0xC4505660
	UINT32                                                 reserved5324;	//0xC4505664
	UINT32                                                 reserved5325;	//0xC4505668
	UINT32                                                 reserved5326;	//0xC450566C
	UINT32                                                 reserved5327;	//0xC4505670
	UINT32                                                 reserved5328;	//0xC4505674
	UINT32                                                 reserved5329;	//0xC4505678
	UINT32                                                 reserved5330;	//0xC450567C
	UINT32                                                 reserved5331;	//0xC4505680
	UINT32                                                 reserved5332;	//0xC4505684
	UINT32                                                 reserved5333;	//0xC4505688
	UINT32                                                 reserved5334;	//0xC450568C
	UINT32                                                 reserved5335;	//0xC4505690
	UINT32                                                 reserved5336;	//0xC4505694
	UINT32                                                 reserved5337;	//0xC4505698
	UINT32                                                 reserved5338;	//0xC450569C
	UINT32                                                 reserved5339;	//0xC45056A0
	UINT32                                                 reserved5340;	//0xC45056A4
	UINT32                                                 reserved5341;	//0xC45056A8
	UINT32                                                 reserved5342;	//0xC45056AC
	UINT32                                                 reserved5343;	//0xC45056B0
	UINT32                                                 reserved5344;	//0xC45056B4
	UINT32                                                 reserved5345;	//0xC45056B8
	UINT32                                                 reserved5346;	//0xC45056BC
	UINT32                                                 reserved5347;	//0xC45056C0
	UINT32                                                 reserved5348;	//0xC45056C4
	UINT32                                                 reserved5349;	//0xC45056C8
	UINT32                                                 reserved5350;	//0xC45056CC
	UINT32                                                 reserved5351;	//0xC45056D0
	UINT32                                                 reserved5352;	//0xC45056D4
	UINT32                                                 reserved5353;	//0xC45056D8
	UINT32                                                 reserved5354;	//0xC45056DC
	UINT32                                                 reserved5355;	//0xC45056E0
	UINT32                                                 reserved5356;	//0xC45056E4
	UINT32                                                 reserved5357;	//0xC45056E8
	UINT32                                                 reserved5358;	//0xC45056EC
	UINT32                                                 reserved5359;	//0xC45056F0
	UINT32                                                 reserved5360;	//0xC45056F4
	UINT32                                                 reserved5361;	//0xC45056F8
	UINT32                                                 reserved5362;	//0xC45056FC
	REG_DDRC_M2_DEBUG_IDLE_CNT_T                         debug_idle_cnt;	//0xC4505700
	REG_DDRC_M2_DEBUG_RD_CNT_T                             debug_rd_cnt;	//0xC4505704
	REG_DDRC_M2_DEBUG_RDL_CNT_T                           debug_rdl_cnt;	//0xC4505708
	UINT32                                                 reserved5363;	//0xC450570C
	REG_DDRC_M2_DEBUG_RWR_CNT_T                           debug_rwr_cnt;	//0xC4505710
	REG_DDRC_M2_DEBUG_MWR_CNT_T                           debug_mwr_cnt;	//0xC4505714
	REG_DDRC_M2_DEBUG_WRL_CNT_T                           debug_wrl_cnt;	//0xC4505718
	UINT32                                                 reserved5364;	//0xC450571C
	REG_DDRC_M2_DEBUG_PRG_CNT_T                           debug_prg_cnt;	//0xC4505720
	REG_DDRC_M2_DEBUG_REF_CNT_T                           debug_ref_cnt;	//0xC4505724
	REG_DDRC_M2_DEBUG_ACT_CNT_T                           debug_act_cnt;	//0xC4505728
	REG_DDRC_M2_DEBUG_RW_SWC_CNT_T                     debug_rw_swc_cnt;	//0xC450572C
	REG_DDRC_M2_DEBUG_R_URG_SWC_CNT_T               debug_r_urg_swc_cnt;	//0xC4505730
	REG_DDRC_M2_DEBUG_R_REQ_ROW_HIT_CNT_T       debug_r_req_row_hit_cnt;	//0xC4505734
	REG_DDRC_M2_DEBUG_R_REQ_HIT_CNT_T               debug_r_req_hit_cnt;	//0xC4505738
	REG_DDRC_M2_DEBUG_R_URG_ROW_HIT_CNT_T       debug_r_urg_row_hit_cnt;	//0xC450573C
	REG_DDRC_M2_DEBUG_R_URG_HIT_CNT_T               debug_r_urg_hit_cnt;	//0xC4505740
	REG_DDRC_M2_DEBUG_R_ROW_HIT_CNT_T               debug_r_row_hit_cnt;	//0xC4505744
	REG_DDRC_M2_DEBUG_R_LUCKY_HIT_CNT_T           debug_r_lucky_hit_cnt;	//0xC4505748
	UINT32                                                 reserved5365;	//0xC450574C
	REG_DDRC_M2_DEBUG_W_URG_SWC_CNT_T               debug_w_urg_swc_cnt;	//0xC4505750
	REG_DDRC_M2_DEBUG_W_REQ_ROW_HIT_CNT_T       debug_w_req_row_hit_cnt;	//0xC4505754
	REG_DDRC_M2_DEBUG_W_REQ_HIT_CNT_T               debug_w_req_hit_cnt;	//0xC4505758
	REG_DDRC_M2_DEBUG_W_URG_ROW_HIT_CNT_T       debug_w_urg_row_hit_cnt;	//0xC450575C
	REG_DDRC_M2_DEBUG_W_URG_HIT_CNT_T               debug_w_urg_hit_cnt;	//0xC4505760
	REG_DDRC_M2_DEBUG_W_ROW_HIT_CNT_T               debug_w_row_hit_cnt;	//0xC4505764
	REG_DDRC_M2_DEBUG_W_LUCKY_HIT_CNT_T           debug_w_lucky_hit_cnt;	//0xC4505768
	UINT32                                                 reserved5366;	//0xC450576C
	REG_DDRC_M2_DEBUG_MAX_LAT_QOS_T                   debug_max_lat_qos;	//0xC4505770
	UINT32                                                 reserved5367;	//0xC4505774
	UINT32                                                 reserved5368;	//0xC4505778
	UINT32                                                 reserved5369;	//0xC450577C
	UINT32                                                 reserved5370;	//0xC4505780
	UINT32                                                 reserved5371;	//0xC4505784
	UINT32                                                 reserved5372;	//0xC4505788
	UINT32                                                 reserved5373;	//0xC450578C
	UINT32                                                 reserved5374;	//0xC4505790
	UINT32                                                 reserved5375;	//0xC4505794
	UINT32                                                 reserved5376;	//0xC4505798
	UINT32                                                 reserved5377;	//0xC450579C
	UINT32                                                 reserved5378;	//0xC45057A0
	UINT32                                                 reserved5379;	//0xC45057A4
	UINT32                                                 reserved5380;	//0xC45057A8
	UINT32                                                 reserved5381;	//0xC45057AC
	UINT32                                                 reserved5382;	//0xC45057B0
	UINT32                                                 reserved5383;	//0xC45057B4
	UINT32                                                 reserved5384;	//0xC45057B8
	UINT32                                                 reserved5385;	//0xC45057BC
	UINT32                                                 reserved5386;	//0xC45057C0
	UINT32                                                 reserved5387;	//0xC45057C4
	UINT32                                                 reserved5388;	//0xC45057C8
	UINT32                                                 reserved5389;	//0xC45057CC
	UINT32                                                 reserved5390;	//0xC45057D0
	UINT32                                                 reserved5391;	//0xC45057D4
	UINT32                                                 reserved5392;	//0xC45057D8
	UINT32                                                 reserved5393;	//0xC45057DC
	UINT32                                                 reserved5394;	//0xC45057E0
	UINT32                                                 reserved5395;	//0xC45057E4
	UINT32                                                 reserved5396;	//0xC45057E8
	UINT32                                                 reserved5397;	//0xC45057EC
	UINT32                                                 reserved5398;	//0xC45057F0
	UINT32                                                 reserved5399;	//0xC45057F4
	UINT32                                                 reserved5400;	//0xC45057F8
	UINT32                                                 reserved5401;	//0xC45057FC
	REG_DDRC_M2_DEBUG_R_HYB_SWC_CNT_T               debug_r_hyb_swc_cnt;	//0xC4505800
	REG_DDRC_M2_DEBUG_W_HYB_SWC_CNT_T               debug_w_hyb_swc_cnt;	//0xC4505804
	UINT32                                                 reserved5402;	//0xC4505808
	UINT32                                                 reserved5403;	//0xC450580C
	UINT32                                                 reserved5404;	//0xC4505810
	UINT32                                                 reserved5405;	//0xC4505814
	UINT32                                                 reserved5406;	//0xC4505818
	UINT32                                                 reserved5407;	//0xC450581C
	UINT32                                                 reserved5408;	//0xC4505820
	UINT32                                                 reserved5409;	//0xC4505824
	UINT32                                                 reserved5410;	//0xC4505828
	UINT32                                                 reserved5411;	//0xC450582C
	UINT32                                                 reserved5412;	//0xC4505830
	UINT32                                                 reserved5413;	//0xC4505834
	UINT32                                                 reserved5414;	//0xC4505838
	UINT32                                                 reserved5415;	//0xC450583C
	UINT32                                                 reserved5416;	//0xC4505840
	UINT32                                                 reserved5417;	//0xC4505844
	UINT32                                                 reserved5418;	//0xC4505848
	UINT32                                                 reserved5419;	//0xC450584C
	UINT32                                                 reserved5420;	//0xC4505850
	UINT32                                                 reserved5421;	//0xC4505854
	UINT32                                                 reserved5422;	//0xC4505858
	UINT32                                                 reserved5423;	//0xC450585C
	UINT32                                                 reserved5424;	//0xC4505860
	UINT32                                                 reserved5425;	//0xC4505864
	UINT32                                                 reserved5426;	//0xC4505868
	UINT32                                                 reserved5427;	//0xC450586C
	UINT32                                                 reserved5428;	//0xC4505870
	UINT32                                                 reserved5429;	//0xC4505874
	UINT32                                                 reserved5430;	//0xC4505878
	UINT32                                                 reserved5431;	//0xC450587C
	UINT32                                                 reserved5432;	//0xC4505880
	UINT32                                                 reserved5433;	//0xC4505884
	UINT32                                                 reserved5434;	//0xC4505888
	UINT32                                                 reserved5435;	//0xC450588C
	UINT32                                                 reserved5436;	//0xC4505890
	UINT32                                                 reserved5437;	//0xC4505894
	UINT32                                                 reserved5438;	//0xC4505898
	UINT32                                                 reserved5439;	//0xC450589C
	UINT32                                                 reserved5440;	//0xC45058A0
	UINT32                                                 reserved5441;	//0xC45058A4
	UINT32                                                 reserved5442;	//0xC45058A8
	UINT32                                                 reserved5443;	//0xC45058AC
	UINT32                                                 reserved5444;	//0xC45058B0
	UINT32                                                 reserved5445;	//0xC45058B4
	UINT32                                                 reserved5446;	//0xC45058B8
	UINT32                                                 reserved5447;	//0xC45058BC
	UINT32                                                 reserved5448;	//0xC45058C0
	UINT32                                                 reserved5449;	//0xC45058C4
	UINT32                                                 reserved5450;	//0xC45058C8
	UINT32                                                 reserved5451;	//0xC45058CC
	UINT32                                                 reserved5452;	//0xC45058D0
	UINT32                                                 reserved5453;	//0xC45058D4
	UINT32                                                 reserved5454;	//0xC45058D8
	UINT32                                                 reserved5455;	//0xC45058DC
	UINT32                                                 reserved5456;	//0xC45058E0
	UINT32                                                 reserved5457;	//0xC45058E4
	UINT32                                                 reserved5458;	//0xC45058E8
	UINT32                                                 reserved5459;	//0xC45058EC
	UINT32                                                 reserved5460;	//0xC45058F0
	UINT32                                                 reserved5461;	//0xC45058F4
	UINT32                                                 reserved5462;	//0xC45058F8
	UINT32                                                 reserved5463;	//0xC45058FC
	REG_DDRC_M2_DEBUG_R_FIFO_0_PRT_CNT_T         debug_r_fifo_0_prt_cnt;	//0xC4505900
	REG_DDRC_M2_DEBUG_R_FIFO_1_PRT_CNT_T         debug_r_fifo_1_prt_cnt;	//0xC4505904
	REG_DDRC_M2_DEBUG_R_FIFO_2_PRT_CNT_T         debug_r_fifo_2_prt_cnt;	//0xC4505908
	REG_DDRC_M2_DEBUG_R_FIFO_3_PRT_CNT_T         debug_r_fifo_3_prt_cnt;	//0xC450590C
	REG_DDRC_M2_DEBUG_W_FIFO_0_PRT_CNT_T         debug_w_fifo_0_prt_cnt;	//0xC4505910
	REG_DDRC_M2_DEBUG_W_FIFO_1_PRT_CNT_T         debug_w_fifo_1_prt_cnt;	//0xC4505914
	REG_DDRC_M2_DEBUG_W_FIFO_2_PRT_CNT_T         debug_w_fifo_2_prt_cnt;	//0xC4505918
	REG_DDRC_M2_DEBUG_W_FIFO_3_PRT_CNT_T         debug_w_fifo_3_prt_cnt;	//0xC450591C
	UINT32                                                 reserved5464;	//0xC4505920
	UINT32                                                 reserved5465;	//0xC4505924
	UINT32                                                 reserved5466;	//0xC4505928
	UINT32                                                 reserved5467;	//0xC450592C
	UINT32                                                 reserved5468;	//0xC4505930
	UINT32                                                 reserved5469;	//0xC4505934
	UINT32                                                 reserved5470;	//0xC4505938
	UINT32                                                 reserved5471;	//0xC450593C
	UINT32                                                 reserved5472;	//0xC4505940
	UINT32                                                 reserved5473;	//0xC4505944
	UINT32                                                 reserved5474;	//0xC4505948
	UINT32                                                 reserved5475;	//0xC450594C
	UINT32                                                 reserved5476;	//0xC4505950
	UINT32                                                 reserved5477;	//0xC4505954
	UINT32                                                 reserved5478;	//0xC4505958
	UINT32                                                 reserved5479;	//0xC450595C
	UINT32                                                 reserved5480;	//0xC4505960
	UINT32                                                 reserved5481;	//0xC4505964
	UINT32                                                 reserved5482;	//0xC4505968
	UINT32                                                 reserved5483;	//0xC450596C
	UINT32                                                 reserved5484;	//0xC4505970
	UINT32                                                 reserved5485;	//0xC4505974
	UINT32                                                 reserved5486;	//0xC4505978
	UINT32                                                 reserved5487;	//0xC450597C
	UINT32                                                 reserved5488;	//0xC4505980
	UINT32                                                 reserved5489;	//0xC4505984
	UINT32                                                 reserved5490;	//0xC4505988
	UINT32                                                 reserved5491;	//0xC450598C
	UINT32                                                 reserved5492;	//0xC4505990
	UINT32                                                 reserved5493;	//0xC4505994
	UINT32                                                 reserved5494;	//0xC4505998
	UINT32                                                 reserved5495;	//0xC450599C
	UINT32                                                 reserved5496;	//0xC45059A0
	UINT32                                                 reserved5497;	//0xC45059A4
	UINT32                                                 reserved5498;	//0xC45059A8
	UINT32                                                 reserved5499;	//0xC45059AC
	UINT32                                                 reserved5500;	//0xC45059B0
	UINT32                                                 reserved5501;	//0xC45059B4
	UINT32                                                 reserved5502;	//0xC45059B8
	UINT32                                                 reserved5503;	//0xC45059BC
	UINT32                                                 reserved5504;	//0xC45059C0
	UINT32                                                 reserved5505;	//0xC45059C4
	UINT32                                                 reserved5506;	//0xC45059C8
	UINT32                                                 reserved5507;	//0xC45059CC
	UINT32                                                 reserved5508;	//0xC45059D0
	UINT32                                                 reserved5509;	//0xC45059D4
	UINT32                                                 reserved5510;	//0xC45059D8
	UINT32                                                 reserved5511;	//0xC45059DC
	UINT32                                                 reserved5512;	//0xC45059E0
	UINT32                                                 reserved5513;	//0xC45059E4
	UINT32                                                 reserved5514;	//0xC45059E8
	UINT32                                                 reserved5515;	//0xC45059EC
	UINT32                                                 reserved5516;	//0xC45059F0
	UINT32                                                 reserved5517;	//0xC45059F4
	UINT32                                                 reserved5518;	//0xC45059F8
	UINT32                                                 reserved5519;	//0xC45059FC
	UINT32                                                 reserved5520;	//0xC4505A00
	UINT32                                                 reserved5521;	//0xC4505A04
	UINT32                                                 reserved5522;	//0xC4505A08
	UINT32                                                 reserved5523;	//0xC4505A0C
	UINT32                                                 reserved5524;	//0xC4505A10
	UINT32                                                 reserved5525;	//0xC4505A14
	UINT32                                                 reserved5526;	//0xC4505A18
	UINT32                                                 reserved5527;	//0xC4505A1C
	UINT32                                                 reserved5528;	//0xC4505A20
	UINT32                                                 reserved5529;	//0xC4505A24
	UINT32                                                 reserved5530;	//0xC4505A28
	UINT32                                                 reserved5531;	//0xC4505A2C
	UINT32                                                 reserved5532;	//0xC4505A30
	UINT32                                                 reserved5533;	//0xC4505A34
	UINT32                                                 reserved5534;	//0xC4505A38
	UINT32                                                 reserved5535;	//0xC4505A3C
	UINT32                                                 reserved5536;	//0xC4505A40
	UINT32                                                 reserved5537;	//0xC4505A44
	UINT32                                                 reserved5538;	//0xC4505A48
	UINT32                                                 reserved5539;	//0xC4505A4C
	UINT32                                                 reserved5540;	//0xC4505A50
	UINT32                                                 reserved5541;	//0xC4505A54
	UINT32                                                 reserved5542;	//0xC4505A58
	UINT32                                                 reserved5543;	//0xC4505A5C
	UINT32                                                 reserved5544;	//0xC4505A60
	UINT32                                                 reserved5545;	//0xC4505A64
	UINT32                                                 reserved5546;	//0xC4505A68
	UINT32                                                 reserved5547;	//0xC4505A6C
	UINT32                                                 reserved5548;	//0xC4505A70
	UINT32                                                 reserved5549;	//0xC4505A74
	UINT32                                                 reserved5550;	//0xC4505A78
	UINT32                                                 reserved5551;	//0xC4505A7C
	UINT32                                                 reserved5552;	//0xC4505A80
	UINT32                                                 reserved5553;	//0xC4505A84
	UINT32                                                 reserved5554;	//0xC4505A88
	UINT32                                                 reserved5555;	//0xC4505A8C
	UINT32                                                 reserved5556;	//0xC4505A90
	UINT32                                                 reserved5557;	//0xC4505A94
	UINT32                                                 reserved5558;	//0xC4505A98
	UINT32                                                 reserved5559;	//0xC4505A9C
	UINT32                                                 reserved5560;	//0xC4505AA0
	UINT32                                                 reserved5561;	//0xC4505AA4
	UINT32                                                 reserved5562;	//0xC4505AA8
	UINT32                                                 reserved5563;	//0xC4505AAC
	UINT32                                                 reserved5564;	//0xC4505AB0
	UINT32                                                 reserved5565;	//0xC4505AB4
	UINT32                                                 reserved5566;	//0xC4505AB8
	UINT32                                                 reserved5567;	//0xC4505ABC
	UINT32                                                 reserved5568;	//0xC4505AC0
	UINT32                                                 reserved5569;	//0xC4505AC4
	UINT32                                                 reserved5570;	//0xC4505AC8
	UINT32                                                 reserved5571;	//0xC4505ACC
	UINT32                                                 reserved5572;	//0xC4505AD0
	UINT32                                                 reserved5573;	//0xC4505AD4
	UINT32                                                 reserved5574;	//0xC4505AD8
	UINT32                                                 reserved5575;	//0xC4505ADC
	UINT32                                                 reserved5576;	//0xC4505AE0
	UINT32                                                 reserved5577;	//0xC4505AE4
	UINT32                                                 reserved5578;	//0xC4505AE8
	UINT32                                                 reserved5579;	//0xC4505AEC
	UINT32                                                 reserved5580;	//0xC4505AF0
	UINT32                                                 reserved5581;	//0xC4505AF4
	UINT32                                                 reserved5582;	//0xC4505AF8
	UINT32                                                 reserved5583;	//0xC4505AFC
	UINT32                                                 reserved5584;	//0xC4505B00
	UINT32                                                 reserved5585;	//0xC4505B04
	UINT32                                                 reserved5586;	//0xC4505B08
	UINT32                                                 reserved5587;	//0xC4505B0C
	UINT32                                                 reserved5588;	//0xC4505B10
	UINT32                                                 reserved5589;	//0xC4505B14
	UINT32                                                 reserved5590;	//0xC4505B18
	UINT32                                                 reserved5591;	//0xC4505B1C
	UINT32                                                 reserved5592;	//0xC4505B20
	UINT32                                                 reserved5593;	//0xC4505B24
	UINT32                                                 reserved5594;	//0xC4505B28
	UINT32                                                 reserved5595;	//0xC4505B2C
	UINT32                                                 reserved5596;	//0xC4505B30
	UINT32                                                 reserved5597;	//0xC4505B34
	UINT32                                                 reserved5598;	//0xC4505B38
	UINT32                                                 reserved5599;	//0xC4505B3C
	UINT32                                                 reserved5600;	//0xC4505B40
	UINT32                                                 reserved5601;	//0xC4505B44
	UINT32                                                 reserved5602;	//0xC4505B48
	UINT32                                                 reserved5603;	//0xC4505B4C
	UINT32                                                 reserved5604;	//0xC4505B50
	UINT32                                                 reserved5605;	//0xC4505B54
	UINT32                                                 reserved5606;	//0xC4505B58
	UINT32                                                 reserved5607;	//0xC4505B5C
	UINT32                                                 reserved5608;	//0xC4505B60
	UINT32                                                 reserved5609;	//0xC4505B64
	UINT32                                                 reserved5610;	//0xC4505B68
	UINT32                                                 reserved5611;	//0xC4505B6C
	UINT32                                                 reserved5612;	//0xC4505B70
	UINT32                                                 reserved5613;	//0xC4505B74
	UINT32                                                 reserved5614;	//0xC4505B78
	UINT32                                                 reserved5615;	//0xC4505B7C
	UINT32                                                 reserved5616;	//0xC4505B80
	UINT32                                                 reserved5617;	//0xC4505B84
	UINT32                                                 reserved5618;	//0xC4505B88
	UINT32                                                 reserved5619;	//0xC4505B8C
	UINT32                                                 reserved5620;	//0xC4505B90
	UINT32                                                 reserved5621;	//0xC4505B94
	UINT32                                                 reserved5622;	//0xC4505B98
	UINT32                                                 reserved5623;	//0xC4505B9C
	UINT32                                                 reserved5624;	//0xC4505BA0
	UINT32                                                 reserved5625;	//0xC4505BA4
	UINT32                                                 reserved5626;	//0xC4505BA8
	UINT32                                                 reserved5627;	//0xC4505BAC
	UINT32                                                 reserved5628;	//0xC4505BB0
	UINT32                                                 reserved5629;	//0xC4505BB4
	UINT32                                                 reserved5630;	//0xC4505BB8
	UINT32                                                 reserved5631;	//0xC4505BBC
	UINT32                                                 reserved5632;	//0xC4505BC0
	UINT32                                                 reserved5633;	//0xC4505BC4
	UINT32                                                 reserved5634;	//0xC4505BC8
	UINT32                                                 reserved5635;	//0xC4505BCC
	UINT32                                                 reserved5636;	//0xC4505BD0
	UINT32                                                 reserved5637;	//0xC4505BD4
	UINT32                                                 reserved5638;	//0xC4505BD8
	UINT32                                                 reserved5639;	//0xC4505BDC
	UINT32                                                 reserved5640;	//0xC4505BE0
	UINT32                                                 reserved5641;	//0xC4505BE4
	UINT32                                                 reserved5642;	//0xC4505BE8
	UINT32                                                 reserved5643;	//0xC4505BEC
	UINT32                                                 reserved5644;	//0xC4505BF0
	UINT32                                                 reserved5645;	//0xC4505BF4
	UINT32                                                 reserved5646;	//0xC4505BF8
	UINT32                                                 reserved5647;	//0xC4505BFC
	UINT32                                                 reserved5648;	//0xC4505C00
	UINT32                                                 reserved5649;	//0xC4505C04
	UINT32                                                 reserved5650;	//0xC4505C08
	UINT32                                                 reserved5651;	//0xC4505C0C
	UINT32                                                 reserved5652;	//0xC4505C10
	UINT32                                                 reserved5653;	//0xC4505C14
	UINT32                                                 reserved5654;	//0xC4505C18
	UINT32                                                 reserved5655;	//0xC4505C1C
	UINT32                                                 reserved5656;	//0xC4505C20
	UINT32                                                 reserved5657;	//0xC4505C24
	UINT32                                                 reserved5658;	//0xC4505C28
	UINT32                                                 reserved5659;	//0xC4505C2C
	UINT32                                                 reserved5660;	//0xC4505C30
	UINT32                                                 reserved5661;	//0xC4505C34
	UINT32                                                 reserved5662;	//0xC4505C38
	UINT32                                                 reserved5663;	//0xC4505C3C
	UINT32                                                 reserved5664;	//0xC4505C40
	UINT32                                                 reserved5665;	//0xC4505C44
	UINT32                                                 reserved5666;	//0xC4505C48
	UINT32                                                 reserved5667;	//0xC4505C4C
	UINT32                                                 reserved5668;	//0xC4505C50
	UINT32                                                 reserved5669;	//0xC4505C54
	UINT32                                                 reserved5670;	//0xC4505C58
	UINT32                                                 reserved5671;	//0xC4505C5C
	UINT32                                                 reserved5672;	//0xC4505C60
	UINT32                                                 reserved5673;	//0xC4505C64
	UINT32                                                 reserved5674;	//0xC4505C68
	UINT32                                                 reserved5675;	//0xC4505C6C
	UINT32                                                 reserved5676;	//0xC4505C70
	UINT32                                                 reserved5677;	//0xC4505C74
	UINT32                                                 reserved5678;	//0xC4505C78
	UINT32                                                 reserved5679;	//0xC4505C7C
	UINT32                                                 reserved5680;	//0xC4505C80
	UINT32                                                 reserved5681;	//0xC4505C84
	UINT32                                                 reserved5682;	//0xC4505C88
	UINT32                                                 reserved5683;	//0xC4505C8C
	UINT32                                                 reserved5684;	//0xC4505C90
	UINT32                                                 reserved5685;	//0xC4505C94
	UINT32                                                 reserved5686;	//0xC4505C98
	UINT32                                                 reserved5687;	//0xC4505C9C
	UINT32                                                 reserved5688;	//0xC4505CA0
	UINT32                                                 reserved5689;	//0xC4505CA4
	UINT32                                                 reserved5690;	//0xC4505CA8
	UINT32                                                 reserved5691;	//0xC4505CAC
	UINT32                                                 reserved5692;	//0xC4505CB0
	UINT32                                                 reserved5693;	//0xC4505CB4
	UINT32                                                 reserved5694;	//0xC4505CB8
	UINT32                                                 reserved5695;	//0xC4505CBC
	UINT32                                                 reserved5696;	//0xC4505CC0
	UINT32                                                 reserved5697;	//0xC4505CC4
	UINT32                                                 reserved5698;	//0xC4505CC8
	UINT32                                                 reserved5699;	//0xC4505CCC
	UINT32                                                 reserved5700;	//0xC4505CD0
	UINT32                                                 reserved5701;	//0xC4505CD4
	UINT32                                                 reserved5702;	//0xC4505CD8
	UINT32                                                 reserved5703;	//0xC4505CDC
	UINT32                                                 reserved5704;	//0xC4505CE0
	UINT32                                                 reserved5705;	//0xC4505CE4
	UINT32                                                 reserved5706;	//0xC4505CE8
	UINT32                                                 reserved5707;	//0xC4505CEC
	UINT32                                                 reserved5708;	//0xC4505CF0
	UINT32                                                 reserved5709;	//0xC4505CF4
	UINT32                                                 reserved5710;	//0xC4505CF8
	UINT32                                                 reserved5711;	//0xC4505CFC
	UINT32                                                 reserved5712;	//0xC4505D00
	UINT32                                                 reserved5713;	//0xC4505D04
	UINT32                                                 reserved5714;	//0xC4505D08
	UINT32                                                 reserved5715;	//0xC4505D0C
	UINT32                                                 reserved5716;	//0xC4505D10
	UINT32                                                 reserved5717;	//0xC4505D14
	UINT32                                                 reserved5718;	//0xC4505D18
	UINT32                                                 reserved5719;	//0xC4505D1C
	UINT32                                                 reserved5720;	//0xC4505D20
	UINT32                                                 reserved5721;	//0xC4505D24
	UINT32                                                 reserved5722;	//0xC4505D28
	UINT32                                                 reserved5723;	//0xC4505D2C
	UINT32                                                 reserved5724;	//0xC4505D30
	UINT32                                                 reserved5725;	//0xC4505D34
	UINT32                                                 reserved5726;	//0xC4505D38
	UINT32                                                 reserved5727;	//0xC4505D3C
	UINT32                                                 reserved5728;	//0xC4505D40
	UINT32                                                 reserved5729;	//0xC4505D44
	UINT32                                                 reserved5730;	//0xC4505D48
	UINT32                                                 reserved5731;	//0xC4505D4C
	UINT32                                                 reserved5732;	//0xC4505D50
	UINT32                                                 reserved5733;	//0xC4505D54
	UINT32                                                 reserved5734;	//0xC4505D58
	UINT32                                                 reserved5735;	//0xC4505D5C
	UINT32                                                 reserved5736;	//0xC4505D60
	UINT32                                                 reserved5737;	//0xC4505D64
	UINT32                                                 reserved5738;	//0xC4505D68
	UINT32                                                 reserved5739;	//0xC4505D6C
	UINT32                                                 reserved5740;	//0xC4505D70
	UINT32                                                 reserved5741;	//0xC4505D74
	UINT32                                                 reserved5742;	//0xC4505D78
	UINT32                                                 reserved5743;	//0xC4505D7C
	UINT32                                                 reserved5744;	//0xC4505D80
	UINT32                                                 reserved5745;	//0xC4505D84
	UINT32                                                 reserved5746;	//0xC4505D88
	UINT32                                                 reserved5747;	//0xC4505D8C
	UINT32                                                 reserved5748;	//0xC4505D90
	UINT32                                                 reserved5749;	//0xC4505D94
	UINT32                                                 reserved5750;	//0xC4505D98
	UINT32                                                 reserved5751;	//0xC4505D9C
	UINT32                                                 reserved5752;	//0xC4505DA0
	UINT32                                                 reserved5753;	//0xC4505DA4
	UINT32                                                 reserved5754;	//0xC4505DA8
	UINT32                                                 reserved5755;	//0xC4505DAC
	UINT32                                                 reserved5756;	//0xC4505DB0
	UINT32                                                 reserved5757;	//0xC4505DB4
	UINT32                                                 reserved5758;	//0xC4505DB8
	UINT32                                                 reserved5759;	//0xC4505DBC
	UINT32                                                 reserved5760;	//0xC4505DC0
	UINT32                                                 reserved5761;	//0xC4505DC4
	UINT32                                                 reserved5762;	//0xC4505DC8
	UINT32                                                 reserved5763;	//0xC4505DCC
	UINT32                                                 reserved5764;	//0xC4505DD0
	UINT32                                                 reserved5765;	//0xC4505DD4
	UINT32                                                 reserved5766;	//0xC4505DD8
	UINT32                                                 reserved5767;	//0xC4505DDC
	UINT32                                                 reserved5768;	//0xC4505DE0
	UINT32                                                 reserved5769;	//0xC4505DE4
	UINT32                                                 reserved5770;	//0xC4505DE8
	UINT32                                                 reserved5771;	//0xC4505DEC
	UINT32                                                 reserved5772;	//0xC4505DF0
	UINT32                                                 reserved5773;	//0xC4505DF4
	UINT32                                                 reserved5774;	//0xC4505DF8
	UINT32                                                 reserved5775;	//0xC4505DFC
	UINT32                                                 reserved5776;	//0xC4505E00
	UINT32                                                 reserved5777;	//0xC4505E04
	UINT32                                                 reserved5778;	//0xC4505E08
	UINT32                                                 reserved5779;	//0xC4505E0C
	UINT32                                                 reserved5780;	//0xC4505E10
	UINT32                                                 reserved5781;	//0xC4505E14
	UINT32                                                 reserved5782;	//0xC4505E18
	UINT32                                                 reserved5783;	//0xC4505E1C
	UINT32                                                 reserved5784;	//0xC4505E20
	UINT32                                                 reserved5785;	//0xC4505E24
	UINT32                                                 reserved5786;	//0xC4505E28
	UINT32                                                 reserved5787;	//0xC4505E2C
	UINT32                                                 reserved5788;	//0xC4505E30
	UINT32                                                 reserved5789;	//0xC4505E34
	UINT32                                                 reserved5790;	//0xC4505E38
	UINT32                                                 reserved5791;	//0xC4505E3C
	UINT32                                                 reserved5792;	//0xC4505E40
	UINT32                                                 reserved5793;	//0xC4505E44
	UINT32                                                 reserved5794;	//0xC4505E48
	UINT32                                                 reserved5795;	//0xC4505E4C
	UINT32                                                 reserved5796;	//0xC4505E50
	UINT32                                                 reserved5797;	//0xC4505E54
	UINT32                                                 reserved5798;	//0xC4505E58
	UINT32                                                 reserved5799;	//0xC4505E5C
	UINT32                                                 reserved5800;	//0xC4505E60
	UINT32                                                 reserved5801;	//0xC4505E64
	UINT32                                                 reserved5802;	//0xC4505E68
	UINT32                                                 reserved5803;	//0xC4505E6C
	UINT32                                                 reserved5804;	//0xC4505E70
	UINT32                                                 reserved5805;	//0xC4505E74
	UINT32                                                 reserved5806;	//0xC4505E78
	UINT32                                                 reserved5807;	//0xC4505E7C
	UINT32                                                 reserved5808;	//0xC4505E80
	UINT32                                                 reserved5809;	//0xC4505E84
	UINT32                                                 reserved5810;	//0xC4505E88
	UINT32                                                 reserved5811;	//0xC4505E8C
	UINT32                                                 reserved5812;	//0xC4505E90
	UINT32                                                 reserved5813;	//0xC4505E94
	UINT32                                                 reserved5814;	//0xC4505E98
	UINT32                                                 reserved5815;	//0xC4505E9C
	UINT32                                                 reserved5816;	//0xC4505EA0
	UINT32                                                 reserved5817;	//0xC4505EA4
	UINT32                                                 reserved5818;	//0xC4505EA8
	UINT32                                                 reserved5819;	//0xC4505EAC
	UINT32                                                 reserved5820;	//0xC4505EB0
	UINT32                                                 reserved5821;	//0xC4505EB4
	UINT32                                                 reserved5822;	//0xC4505EB8
	UINT32                                                 reserved5823;	//0xC4505EBC
	UINT32                                                 reserved5824;	//0xC4505EC0
	UINT32                                                 reserved5825;	//0xC4505EC4
	UINT32                                                 reserved5826;	//0xC4505EC8
	UINT32                                                 reserved5827;	//0xC4505ECC
	UINT32                                                 reserved5828;	//0xC4505ED0
	UINT32                                                 reserved5829;	//0xC4505ED4
	UINT32                                                 reserved5830;	//0xC4505ED8
	UINT32                                                 reserved5831;	//0xC4505EDC
	UINT32                                                 reserved5832;	//0xC4505EE0
	UINT32                                                 reserved5833;	//0xC4505EE4
	UINT32                                                 reserved5834;	//0xC4505EE8
	UINT32                                                 reserved5835;	//0xC4505EEC
	UINT32                                                 reserved5836;	//0xC4505EF0
	UINT32                                                 reserved5837;	//0xC4505EF4
	UINT32                                                 reserved5838;	//0xC4505EF8
	UINT32                                                 reserved5839;	//0xC4505EFC
	UINT32                                                 reserved5840;	//0xC4505F00
	UINT32                                                 reserved5841;	//0xC4505F04
	UINT32                                                 reserved5842;	//0xC4505F08
	UINT32                                                 reserved5843;	//0xC4505F0C
	UINT32                                                 reserved5844;	//0xC4505F10
	UINT32                                                 reserved5845;	//0xC4505F14
	UINT32                                                 reserved5846;	//0xC4505F18
	UINT32                                                 reserved5847;	//0xC4505F1C
	UINT32                                                 reserved5848;	//0xC4505F20
	UINT32                                                 reserved5849;	//0xC4505F24
	UINT32                                                 reserved5850;	//0xC4505F28
	UINT32                                                 reserved5851;	//0xC4505F2C
	UINT32                                                 reserved5852;	//0xC4505F30
	UINT32                                                 reserved5853;	//0xC4505F34
	UINT32                                                 reserved5854;	//0xC4505F38
	UINT32                                                 reserved5855;	//0xC4505F3C
	UINT32                                                 reserved5856;	//0xC4505F40
	UINT32                                                 reserved5857;	//0xC4505F44
	UINT32                                                 reserved5858;	//0xC4505F48
	UINT32                                                 reserved5859;	//0xC4505F4C
	UINT32                                                 reserved5860;	//0xC4505F50
	UINT32                                                 reserved5861;	//0xC4505F54
	UINT32                                                 reserved5862;	//0xC4505F58
	UINT32                                                 reserved5863;	//0xC4505F5C
	UINT32                                                 reserved5864;	//0xC4505F60
	UINT32                                                 reserved5865;	//0xC4505F64
	UINT32                                                 reserved5866;	//0xC4505F68
	UINT32                                                 reserved5867;	//0xC4505F6C
	UINT32                                                 reserved5868;	//0xC4505F70
	UINT32                                                 reserved5869;	//0xC4505F74
	UINT32                                                 reserved5870;	//0xC4505F78
	UINT32                                                 reserved5871;	//0xC4505F7C
	UINT32                                                 reserved5872;	//0xC4505F80
	UINT32                                                 reserved5873;	//0xC4505F84
	UINT32                                                 reserved5874;	//0xC4505F88
	UINT32                                                 reserved5875;	//0xC4505F8C
	UINT32                                                 reserved5876;	//0xC4505F90
	UINT32                                                 reserved5877;	//0xC4505F94
	UINT32                                                 reserved5878;	//0xC4505F98
	UINT32                                                 reserved5879;	//0xC4505F9C
	UINT32                                                 reserved5880;	//0xC4505FA0
	UINT32                                                 reserved5881;	//0xC4505FA4
	UINT32                                                 reserved5882;	//0xC4505FA8
	UINT32                                                 reserved5883;	//0xC4505FAC
	UINT32                                                 reserved5884;	//0xC4505FB0
	UINT32                                                 reserved5885;	//0xC4505FB4
	UINT32                                                 reserved5886;	//0xC4505FB8
	UINT32                                                 reserved5887;	//0xC4505FBC
	UINT32                                                 reserved5888;	//0xC4505FC0
	UINT32                                                 reserved5889;	//0xC4505FC4
	UINT32                                                 reserved5890;	//0xC4505FC8
	UINT32                                                 reserved5891;	//0xC4505FCC
	UINT32                                                 reserved5892;	//0xC4505FD0
	UINT32                                                 reserved5893;	//0xC4505FD4
	UINT32                                                 reserved5894;	//0xC4505FD8
	UINT32                                                 reserved5895;	//0xC4505FDC
	UINT32                                                 reserved5896;	//0xC4505FE0
	UINT32                                                 reserved5897;	//0xC4505FE4
	UINT32                                                 reserved5898;	//0xC4505FE8
	UINT32                                                 reserved5899;	//0xC4505FEC
	UINT32                                                 reserved5900;	//0xC4505FF0
	UINT32                                                 reserved5901;	//0xC4505FF4
	UINT32                                                 reserved5902;	//0xC4505FF8
	UINT32                                                 reserved5903;	//0xC4505FFC
	REG_DDRC_M2_DEBUG_LPD4_0_T                             debug_lpd4_0;	//0xC4506000
	REG_DDRC_M2_DEBUG_LPD4_1_T                             debug_lpd4_1;	//0xC4506004
	REG_DDRC_M2_DEBUG_LPD4_2_T                             debug_lpd4_2;	//0xC4506008
	REG_DDRC_M2_DEBUG_LPD4_3_T                             debug_lpd4_3;	//0xC450600C
	REG_DDRC_M2_DEBUG_LPD4_4_T                             debug_lpd4_4;	//0xC4506010
	REG_DDRC_M2_DEBUG_LPD4_5_T                             debug_lpd4_5;	//0xC4506014
	REG_DDRC_M2_DEBUG_LPD4_6_T                             debug_lpd4_6;	//0xC4506018
	REG_DDRC_M2_DEBUG_LPD4_7_T                             debug_lpd4_7;	//0xC450601C
	REG_DDRC_M2_DEBUG_LPD4_8_T                             debug_lpd4_8;	//0xC4506020
	REG_DDRC_M2_DEBUG_LPD4_9_T                             debug_lpd4_9;	//0xC4506024
	REG_DDRC_M2_DEBUG_LPD4_10_T                           debug_lpd4_10;	//0xC4506028
	REG_DDRC_M2_DEBUG_LPD4_11_T                           debug_lpd4_11;	//0xC450602C
	REG_DDRC_M2_DEBUG_LPD4_12_T                           debug_lpd4_12;	//0xC4506030
	REG_DDRC_M2_DEBUG_LPD4_13_T                           debug_lpd4_13;	//0xC4506034
	REG_DDRC_M2_DEBUG_LPD4_14_T                           debug_lpd4_14;	//0xC4506038
	REG_DDRC_M2_DEBUG_LPD4_15_T                           debug_lpd4_15;	//0xC450603C
	REG_DDRC_M2_DEBUG_LPD4_16_T                           debug_lpd4_16;	//0xC4506040
	UINT32                                                 reserved5904;	//0xC4506044
	UINT32                                                 reserved5905;	//0xC4506048
	UINT32                                                 reserved5906;	//0xC450604C
	UINT32                                                 reserved5907;	//0xC4506050
	UINT32                                                 reserved5908;	//0xC4506054
	UINT32                                                 reserved5909;	//0xC4506058
	UINT32                                                 reserved5910;	//0xC450605C
	UINT32                                                 reserved5911;	//0xC4506060
	UINT32                                                 reserved5912;	//0xC4506064
	UINT32                                                 reserved5913;	//0xC4506068
	UINT32                                                 reserved5914;	//0xC450606C
	UINT32                                                 reserved5915;	//0xC4506070
	UINT32                                                 reserved5916;	//0xC4506074
	UINT32                                                 reserved5917;	//0xC4506078
	UINT32                                                 reserved5918;	//0xC450607C
	UINT32                                                 reserved5919;	//0xC4506080
	UINT32                                                 reserved5920;	//0xC4506084
	UINT32                                                 reserved5921;	//0xC4506088
	UINT32                                                 reserved5922;	//0xC450608C
	UINT32                                                 reserved5923;	//0xC4506090
	UINT32                                                 reserved5924;	//0xC4506094
	UINT32                                                 reserved5925;	//0xC4506098
	UINT32                                                 reserved5926;	//0xC450609C
	UINT32                                                 reserved5927;	//0xC45060A0
	UINT32                                                 reserved5928;	//0xC45060A4
	UINT32                                                 reserved5929;	//0xC45060A8
	UINT32                                                 reserved5930;	//0xC45060AC
	UINT32                                                 reserved5931;	//0xC45060B0
	UINT32                                                 reserved5932;	//0xC45060B4
	UINT32                                                 reserved5933;	//0xC45060B8
	UINT32                                                 reserved5934;	//0xC45060BC
	UINT32                                                 reserved5935;	//0xC45060C0
	UINT32                                                 reserved5936;	//0xC45060C4
	UINT32                                                 reserved5937;	//0xC45060C8
	UINT32                                                 reserved5938;	//0xC45060CC
	UINT32                                                 reserved5939;	//0xC45060D0
	UINT32                                                 reserved5940;	//0xC45060D4
	UINT32                                                 reserved5941;	//0xC45060D8
	UINT32                                                 reserved5942;	//0xC45060DC
	UINT32                                                 reserved5943;	//0xC45060E0
	UINT32                                                 reserved5944;	//0xC45060E4
	UINT32                                                 reserved5945;	//0xC45060E8
	UINT32                                                 reserved5946;	//0xC45060EC
	UINT32                                                 reserved5947;	//0xC45060F0
	UINT32                                                 reserved5948;	//0xC45060F4
	UINT32                                                 reserved5949;	//0xC45060F8
	UINT32                                                 reserved5950;	//0xC45060FC
	REG_DDRC_M2_DEBUG_LPD4_MR_0_T                       debug_lpd4_mr_0;	//0xC4506100
	REG_DDRC_M2_DEBUG_LPD4_MR_1_T                       debug_lpd4_mr_1;	//0xC4506104
	REG_DDRC_M2_DEBUG_LPD4_MR_2_T                       debug_lpd4_mr_2;	//0xC4506108
	REG_DDRC_M2_DEBUG_LPD4_MR_3_T                       debug_lpd4_mr_3;	//0xC450610C
	REG_DDRC_M2_DEBUG_LPD4_MR_4_T                       debug_lpd4_mr_4;	//0xC4506110
	REG_DDRC_M2_DEBUG_LPD4_MR_5_T                       debug_lpd4_mr_5;	//0xC4506114
	REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_0_T           debug_lpd4_mpc_fifo_0;	//0xC4506118
	REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_1_T           debug_lpd4_mpc_fifo_1;	//0xC450611C
	REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_2_T           debug_lpd4_mpc_fifo_2;	//0xC4506120
	REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_3_T           debug_lpd4_mpc_fifo_3;	//0xC4506124
	REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_4_T           debug_lpd4_mpc_fifo_4;	//0xC4506128
	REG_DDRC_M2_DEBUG_LPD4_MPC_FIFO_5_T           debug_lpd4_mpc_fifo_5;	//0xC450612C
	UINT32                                                 reserved5951;	//0xC4506130
	UINT32                                                 reserved5952;	//0xC4506134
	UINT32                                                 reserved5953;	//0xC4506138
	UINT32                                                 reserved5954;	//0xC450613C
	UINT32                                                 reserved5955;	//0xC4506140
	UINT32                                                 reserved5956;	//0xC4506144
	UINT32                                                 reserved5957;	//0xC4506148
	UINT32                                                 reserved5958;	//0xC450614C
	UINT32                                                 reserved5959;	//0xC4506150
	UINT32                                                 reserved5960;	//0xC4506154
	UINT32                                                 reserved5961;	//0xC4506158
	UINT32                                                 reserved5962;	//0xC450615C
	UINT32                                                 reserved5963;	//0xC4506160
	UINT32                                                 reserved5964;	//0xC4506164
	UINT32                                                 reserved5965;	//0xC4506168
	UINT32                                                 reserved5966;	//0xC450616C
	UINT32                                                 reserved5967;	//0xC4506170
	UINT32                                                 reserved5968;	//0xC4506174
	UINT32                                                 reserved5969;	//0xC4506178
	UINT32                                                 reserved5970;	//0xC450617C
	UINT32                                                 reserved5971;	//0xC4506180
	UINT32                                                 reserved5972;	//0xC4506184
	UINT32                                                 reserved5973;	//0xC4506188
	UINT32                                                 reserved5974;	//0xC450618C
	UINT32                                                 reserved5975;	//0xC4506190
	UINT32                                                 reserved5976;	//0xC4506194
	UINT32                                                 reserved5977;	//0xC4506198
	UINT32                                                 reserved5978;	//0xC450619C
	UINT32                                                 reserved5979;	//0xC45061A0
	UINT32                                                 reserved5980;	//0xC45061A4
	UINT32                                                 reserved5981;	//0xC45061A8
	UINT32                                                 reserved5982;	//0xC45061AC
	UINT32                                                 reserved5983;	//0xC45061B0
	UINT32                                                 reserved5984;	//0xC45061B4
	UINT32                                                 reserved5985;	//0xC45061B8
	UINT32                                                 reserved5986;	//0xC45061BC
	UINT32                                                 reserved5987;	//0xC45061C0
	UINT32                                                 reserved5988;	//0xC45061C4
	UINT32                                                 reserved5989;	//0xC45061C8
	UINT32                                                 reserved5990;	//0xC45061CC
	UINT32                                                 reserved5991;	//0xC45061D0
	UINT32                                                 reserved5992;	//0xC45061D4
	UINT32                                                 reserved5993;	//0xC45061D8
	UINT32                                                 reserved5994;	//0xC45061DC
	UINT32                                                 reserved5995;	//0xC45061E0
	UINT32                                                 reserved5996;	//0xC45061E4
	UINT32                                                 reserved5997;	//0xC45061E8
	UINT32                                                 reserved5998;	//0xC45061EC
	UINT32                                                 reserved5999;	//0xC45061F0
	UINT32                                                 reserved6000;	//0xC45061F4
	UINT32                                                 reserved6001;	//0xC45061F8
	UINT32                                                 reserved6002;	//0xC45061FC
	REG_DDRC_M2_DEBUG_CTRL_CMD_MRW1_T               debug_ctrl_cmd_mrw1;	//0xC4506200
	REG_DDRC_M2_DEBUG_CTRL_CMD_MRW0_T               debug_ctrl_cmd_mrw0;	//0xC4506204
	REG_DDRC_M2_DEBUG_CTRL_CMD_LP_EXIT_T         debug_ctrl_cmd_lp_exit;	//0xC4506208
	REG_DDRC_M2_DEBUG_CTRL_CMD_LP_ENTRY_T       debug_ctrl_cmd_lp_entry;	//0xC450620C
	REG_DDRC_M2_DEBUG_CTRL_CMD_SR_PD_EXIT_T   debug_ctrl_cmd_sr_pd_exit;	//0xC4506210
	REG_DDRC_M2_DEBUG_CTRL_CMD_SR_PD_ENTRY_T debug_ctrl_cmd_sr_pd_entry;	//0xC4506214
	REG_DDRC_M2_DEBUG_CTRL_CMD_SR_EXIT_T         debug_ctrl_cmd_sr_exit;	//0xC4506218
	REG_DDRC_M2_DEBUG_CTRL_CMD_SR_ENTRY_T       debug_ctrl_cmd_sr_entry;	//0xC450621C
	REG_DDRC_M2_DEBUG_CTRL_CMD_PD_EXIT_T         debug_ctrl_cmd_pd_exit;	//0xC4506220
	REG_DDRC_M2_DEBUG_CTRL_CMD_PD_ENTRY_T       debug_ctrl_cmd_pd_entry;	//0xC4506224
	REG_DDRC_M2_DEBUG_CTRL_CMD_ZQLAT_T             debug_ctrl_cmd_zqlat;	//0xC4506228
	REG_DDRC_M2_DEBUG_CTRL_CMD_ZQCAL_T             debug_ctrl_cmd_zqcal;	//0xC450622C
	REG_DDRC_M2_DEBUG_CTRL_CMD_CKE1_T               debug_ctrl_cmd_cke1;	//0xC4506230
	REG_DDRC_M2_DEBUG_CTRL_CMD_CKE0_T               debug_ctrl_cmd_cke0;	//0xC4506234
	REG_DDRC_M2_DEBUG_CTRL_CMD_RSTN1_T             debug_ctrl_cmd_rstn1;	//0xC4506238
	REG_DDRC_M2_DEBUG_CTRL_CMD_RSTN0_T             debug_ctrl_cmd_rstn0;	//0xC450623C
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD0_T                 debug_ctrl_cmd_rd0;	//0xC4506240
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD1_T                 debug_ctrl_cmd_rd1;	//0xC4506244
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD2_T                 debug_ctrl_cmd_rd2;	//0xC4506248
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD3_T                 debug_ctrl_cmd_rd3;	//0xC450624C
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD4_T                 debug_ctrl_cmd_rd4;	//0xC4506250
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD5_T                 debug_ctrl_cmd_rd5;	//0xC4506254
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD6_T                 debug_ctrl_cmd_rd6;	//0xC4506258
	REG_DDRC_M2_DEBUG_CTRL_CMD_RD7_T                 debug_ctrl_cmd_rd7;	//0xC450625C
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR0_T               debug_ctrl_cmd_mwr0;	//0xC4506260
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR1_T               debug_ctrl_cmd_mwr1;	//0xC4506264
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR2_T               debug_ctrl_cmd_mwr2;	//0xC4506268
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR3_T               debug_ctrl_cmd_mwr3;	//0xC450626C
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR4_T               debug_ctrl_cmd_mwr4;	//0xC4506270
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR5_T               debug_ctrl_cmd_mwr5;	//0xC4506274
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR6_T               debug_ctrl_cmd_mwr6;	//0xC4506278
	REG_DDRC_M2_DEBUG_CTRL_CMD_MWR7_T               debug_ctrl_cmd_mwr7;	//0xC450627C
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR0_T                 debug_ctrl_cmd_wr0;	//0xC4506280
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR1_T                 debug_ctrl_cmd_wr1;	//0xC4506284
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR2_T                 debug_ctrl_cmd_wr2;	//0xC4506288
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR3_T                 debug_ctrl_cmd_wr3;	//0xC450628C
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR4_T                 debug_ctrl_cmd_wr4;	//0xC4506290
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR5_T                 debug_ctrl_cmd_wr5;	//0xC4506294
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR6_T                 debug_ctrl_cmd_wr6;	//0xC4506298
	REG_DDRC_M2_DEBUG_CTRL_CMD_WR7_T                 debug_ctrl_cmd_wr7;	//0xC450629C
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT0_T               debug_ctrl_cmd_act0;	//0xC45062A0
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT1_T               debug_ctrl_cmd_act1;	//0xC45062A4
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT2_T               debug_ctrl_cmd_act2;	//0xC45062A8
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT3_T               debug_ctrl_cmd_act3;	//0xC45062AC
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT4_T               debug_ctrl_cmd_act4;	//0xC45062B0
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT5_T               debug_ctrl_cmd_act5;	//0xC45062B4
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT6_T               debug_ctrl_cmd_act6;	//0xC45062B8
	REG_DDRC_M2_DEBUG_CTRL_CMD_ACT7_T               debug_ctrl_cmd_act7;	//0xC45062BC
	UINT32                                                 reserved6003;	//0xC45062C0
	UINT32                                                 reserved6004;	//0xC45062C4
	UINT32                                                 reserved6005;	//0xC45062C8
	UINT32                                                 reserved6006;	//0xC45062CC
	UINT32                                                 reserved6007;	//0xC45062D0
	UINT32                                                 reserved6008;	//0xC45062D4
	UINT32                                                 reserved6009;	//0xC45062D8
	UINT32                                                 reserved6010;	//0xC45062DC
	UINT32                                                 reserved6011;	//0xC45062E0
	UINT32                                                 reserved6012;	//0xC45062E4
	UINT32                                                 reserved6013;	//0xC45062E8
	UINT32                                                 reserved6014;	//0xC45062EC
	UINT32                                                 reserved6015;	//0xC45062F0
	UINT32                                                 reserved6016;	//0xC45062F4
	UINT32                                                 reserved6017;	//0xC45062F8
	UINT32                                                 reserved6018;	//0xC45062FC
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB0_T         debug_ctrl_cmd_ref_pb0;	//0xC4506300
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB1_T         debug_ctrl_cmd_ref_pb1;	//0xC4506304
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB2_T         debug_ctrl_cmd_ref_pb2;	//0xC4506308
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB3_T         debug_ctrl_cmd_ref_pb3;	//0xC450630C
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB4_T         debug_ctrl_cmd_ref_pb4;	//0xC4506310
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB5_T         debug_ctrl_cmd_ref_pb5;	//0xC4506314
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB6_T         debug_ctrl_cmd_ref_pb6;	//0xC4506318
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_PB7_T         debug_ctrl_cmd_ref_pb7;	//0xC450631C
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB0_T         debug_ctrl_cmd_prg_pb0;	//0xC4506320
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB1_T         debug_ctrl_cmd_prg_pb1;	//0xC4506324
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB2_T         debug_ctrl_cmd_prg_pb2;	//0xC4506328
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB3_T         debug_ctrl_cmd_prg_pb3;	//0xC450632C
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB4_T         debug_ctrl_cmd_prg_pb4;	//0xC4506330
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB5_T         debug_ctrl_cmd_prg_pb5;	//0xC4506334
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB6_T         debug_ctrl_cmd_prg_pb6;	//0xC4506338
	REG_DDRC_M2_DEBUG_CTRL_CMD_PRG_PB7_T         debug_ctrl_cmd_prg_pb7;	//0xC450633C
	REG_DDRC_M2_DEBUG_CTRL_CMD_CG_REF_AB_T     debug_ctrl_cmd_cg_ref_ab;	//0xC4506340
	REG_DDRC_M2_DEBUG_CTRL_CMD_MF_REF_AB_T     debug_ctrl_cmd_mf_ref_ab;	//0xC4506344
	UINT32                                                 reserved6019;	//0xC4506348
	UINT32                                                 reserved6020;	//0xC450634C
	REG_DDRC_M2_DEBUG_CTRL_CMD_CG_PRG_AB_T     debug_ctrl_cmd_cg_prg_ab;	//0xC4506350
	REG_DDRC_M2_DEBUG_CTRL_CMD_MF_PRG_AB_T     debug_ctrl_cmd_mf_prg_ab;	//0xC4506354
	UINT32                                                 reserved6021;	//0xC4506358
	UINT32                                                 reserved6022;	//0xC450635C
	REG_DDRC_M2_DEBUG_CTRL_CMD_CG_BL_T             debug_ctrl_cmd_cg_bl;	//0xC4506360
	REG_DDRC_M2_DEBUG_CTRL_CMD_CG_AP_T             debug_ctrl_cmd_cg_ap;	//0xC4506364
	REG_DDRC_M2_DEBUG_CTRL_CMD_REF_CYCLE_T     debug_ctrl_cmd_ref_cycle;	//0xC4506368
	UINT32                                                 reserved6023;	//0xC450636C
	UINT32                                                 reserved6024;	//0xC4506370
	UINT32                                                 reserved6025;	//0xC4506374
	UINT32                                                 reserved6026;	//0xC4506378
	UINT32                                                 reserved6027;	//0xC450637C
	UINT32                                                 reserved6028;	//0xC4506380
	UINT32                                                 reserved6029;	//0xC4506384
	UINT32                                                 reserved6030;	//0xC4506388
	UINT32                                                 reserved6031;	//0xC450638C
	UINT32                                                 reserved6032;	//0xC4506390
	UINT32                                                 reserved6033;	//0xC4506394
	UINT32                                                 reserved6034;	//0xC4506398
	UINT32                                                 reserved6035;	//0xC450639C
	UINT32                                                 reserved6036;	//0xC45063A0
	UINT32                                                 reserved6037;	//0xC45063A4
	UINT32                                                 reserved6038;	//0xC45063A8
	UINT32                                                 reserved6039;	//0xC45063AC
	UINT32                                                 reserved6040;	//0xC45063B0
	UINT32                                                 reserved6041;	//0xC45063B4
	UINT32                                                 reserved6042;	//0xC45063B8
	UINT32                                                 reserved6043;	//0xC45063BC
	UINT32                                                 reserved6044;	//0xC45063C0
	UINT32                                                 reserved6045;	//0xC45063C4
	UINT32                                                 reserved6046;	//0xC45063C8
	UINT32                                                 reserved6047;	//0xC45063CC
	UINT32                                                 reserved6048;	//0xC45063D0
	UINT32                                                 reserved6049;	//0xC45063D4
	UINT32                                                 reserved6050;	//0xC45063D8
	UINT32                                                 reserved6051;	//0xC45063DC
	UINT32                                                 reserved6052;	//0xC45063E0
	UINT32                                                 reserved6053;	//0xC45063E4
	UINT32                                                 reserved6054;	//0xC45063E8
	UINT32                                                 reserved6055;	//0xC45063EC
	UINT32                                                 reserved6056;	//0xC45063F0
	UINT32                                                 reserved6057;	//0xC45063F4
	UINT32                                                 reserved6058;	//0xC45063F8
	UINT32                                                 reserved6059;	//0xC45063FC
	UINT32                                                 reserved6060;	//0xC4506400
	UINT32                                                 reserved6061;	//0xC4506404
	UINT32                                                 reserved6062;	//0xC4506408
	UINT32                                                 reserved6063;	//0xC450640C
	UINT32                                                 reserved6064;	//0xC4506410
	UINT32                                                 reserved6065;	//0xC4506414
	UINT32                                                 reserved6066;	//0xC4506418
	UINT32                                                 reserved6067;	//0xC450641C
	UINT32                                                 reserved6068;	//0xC4506420
	UINT32                                                 reserved6069;	//0xC4506424
	UINT32                                                 reserved6070;	//0xC4506428
	UINT32                                                 reserved6071;	//0xC450642C
	UINT32                                                 reserved6072;	//0xC4506430
	UINT32                                                 reserved6073;	//0xC4506434
	UINT32                                                 reserved6074;	//0xC4506438
	UINT32                                                 reserved6075;	//0xC450643C
	UINT32                                                 reserved6076;	//0xC4506440
	UINT32                                                 reserved6077;	//0xC4506444
	UINT32                                                 reserved6078;	//0xC4506448
	UINT32                                                 reserved6079;	//0xC450644C
	UINT32                                                 reserved6080;	//0xC4506450
	UINT32                                                 reserved6081;	//0xC4506454
	UINT32                                                 reserved6082;	//0xC4506458
	UINT32                                                 reserved6083;	//0xC450645C
	UINT32                                                 reserved6084;	//0xC4506460
	UINT32                                                 reserved6085;	//0xC4506464
	UINT32                                                 reserved6086;	//0xC4506468
	UINT32                                                 reserved6087;	//0xC450646C
	UINT32                                                 reserved6088;	//0xC4506470
	UINT32                                                 reserved6089;	//0xC4506474
	UINT32                                                 reserved6090;	//0xC4506478
	UINT32                                                 reserved6091;	//0xC450647C
	UINT32                                                 reserved6092;	//0xC4506480
	UINT32                                                 reserved6093;	//0xC4506484
	UINT32                                                 reserved6094;	//0xC4506488
	UINT32                                                 reserved6095;	//0xC450648C
	UINT32                                                 reserved6096;	//0xC4506490
	UINT32                                                 reserved6097;	//0xC4506494
	UINT32                                                 reserved6098;	//0xC4506498
	UINT32                                                 reserved6099;	//0xC450649C
	UINT32                                                 reserved6100;	//0xC45064A0
	UINT32                                                 reserved6101;	//0xC45064A4
	UINT32                                                 reserved6102;	//0xC45064A8
	UINT32                                                 reserved6103;	//0xC45064AC
	UINT32                                                 reserved6104;	//0xC45064B0
	UINT32                                                 reserved6105;	//0xC45064B4
	UINT32                                                 reserved6106;	//0xC45064B8
	UINT32                                                 reserved6107;	//0xC45064BC
	UINT32                                                 reserved6108;	//0xC45064C0
	UINT32                                                 reserved6109;	//0xC45064C4
	UINT32                                                 reserved6110;	//0xC45064C8
	UINT32                                                 reserved6111;	//0xC45064CC
	UINT32                                                 reserved6112;	//0xC45064D0
	UINT32                                                 reserved6113;	//0xC45064D4
	UINT32                                                 reserved6114;	//0xC45064D8
	UINT32                                                 reserved6115;	//0xC45064DC
	UINT32                                                 reserved6116;	//0xC45064E0
	UINT32                                                 reserved6117;	//0xC45064E4
	UINT32                                                 reserved6118;	//0xC45064E8
	UINT32                                                 reserved6119;	//0xC45064EC
	UINT32                                                 reserved6120;	//0xC45064F0
	UINT32                                                 reserved6121;	//0xC45064F4
	UINT32                                                 reserved6122;	//0xC45064F8
	UINT32                                                 reserved6123;	//0xC45064FC
	UINT32                                                 reserved6124;	//0xC4506500
	UINT32                                                 reserved6125;	//0xC4506504
	UINT32                                                 reserved6126;	//0xC4506508
	UINT32                                                 reserved6127;	//0xC450650C
	UINT32                                                 reserved6128;	//0xC4506510
	UINT32                                                 reserved6129;	//0xC4506514
	UINT32                                                 reserved6130;	//0xC4506518
	UINT32                                                 reserved6131;	//0xC450651C
	UINT32                                                 reserved6132;	//0xC4506520
	UINT32                                                 reserved6133;	//0xC4506524
	UINT32                                                 reserved6134;	//0xC4506528
	UINT32                                                 reserved6135;	//0xC450652C
	UINT32                                                 reserved6136;	//0xC4506530
	UINT32                                                 reserved6137;	//0xC4506534
	UINT32                                                 reserved6138;	//0xC4506538
	UINT32                                                 reserved6139;	//0xC450653C
	UINT32                                                 reserved6140;	//0xC4506540
	UINT32                                                 reserved6141;	//0xC4506544
	UINT32                                                 reserved6142;	//0xC4506548
	UINT32                                                 reserved6143;	//0xC450654C
	UINT32                                                 reserved6144;	//0xC4506550
	UINT32                                                 reserved6145;	//0xC4506554
	UINT32                                                 reserved6146;	//0xC4506558
	UINT32                                                 reserved6147;	//0xC450655C
	UINT32                                                 reserved6148;	//0xC4506560
	UINT32                                                 reserved6149;	//0xC4506564
	UINT32                                                 reserved6150;	//0xC4506568
	UINT32                                                 reserved6151;	//0xC450656C
	UINT32                                                 reserved6152;	//0xC4506570
	UINT32                                                 reserved6153;	//0xC4506574
	UINT32                                                 reserved6154;	//0xC4506578
	UINT32                                                 reserved6155;	//0xC450657C
	UINT32                                                 reserved6156;	//0xC4506580
	UINT32                                                 reserved6157;	//0xC4506584
	UINT32                                                 reserved6158;	//0xC4506588
	UINT32                                                 reserved6159;	//0xC450658C
	UINT32                                                 reserved6160;	//0xC4506590
	UINT32                                                 reserved6161;	//0xC4506594
	UINT32                                                 reserved6162;	//0xC4506598
	UINT32                                                 reserved6163;	//0xC450659C
	UINT32                                                 reserved6164;	//0xC45065A0
	UINT32                                                 reserved6165;	//0xC45065A4
	UINT32                                                 reserved6166;	//0xC45065A8
	UINT32                                                 reserved6167;	//0xC45065AC
	UINT32                                                 reserved6168;	//0xC45065B0
	UINT32                                                 reserved6169;	//0xC45065B4
	UINT32                                                 reserved6170;	//0xC45065B8
	UINT32                                                 reserved6171;	//0xC45065BC
	UINT32                                                 reserved6172;	//0xC45065C0
	UINT32                                                 reserved6173;	//0xC45065C4
	UINT32                                                 reserved6174;	//0xC45065C8
	UINT32                                                 reserved6175;	//0xC45065CC
	UINT32                                                 reserved6176;	//0xC45065D0
	UINT32                                                 reserved6177;	//0xC45065D4
	UINT32                                                 reserved6178;	//0xC45065D8
	UINT32                                                 reserved6179;	//0xC45065DC
	UINT32                                                 reserved6180;	//0xC45065E0
	UINT32                                                 reserved6181;	//0xC45065E4
	UINT32                                                 reserved6182;	//0xC45065E8
	UINT32                                                 reserved6183;	//0xC45065EC
	UINT32                                                 reserved6184;	//0xC45065F0
	UINT32                                                 reserved6185;	//0xC45065F4
	UINT32                                                 reserved6186;	//0xC45065F8
	UINT32                                                 reserved6187;	//0xC45065FC
	UINT32                                                 reserved6188;	//0xC4506600
	UINT32                                                 reserved6189;	//0xC4506604
	UINT32                                                 reserved6190;	//0xC4506608
	UINT32                                                 reserved6191;	//0xC450660C
	UINT32                                                 reserved6192;	//0xC4506610
	UINT32                                                 reserved6193;	//0xC4506614
	UINT32                                                 reserved6194;	//0xC4506618
	UINT32                                                 reserved6195;	//0xC450661C
	UINT32                                                 reserved6196;	//0xC4506620
	UINT32                                                 reserved6197;	//0xC4506624
	UINT32                                                 reserved6198;	//0xC4506628
	UINT32                                                 reserved6199;	//0xC450662C
	UINT32                                                 reserved6200;	//0xC4506630
	UINT32                                                 reserved6201;	//0xC4506634
	UINT32                                                 reserved6202;	//0xC4506638
	UINT32                                                 reserved6203;	//0xC450663C
	UINT32                                                 reserved6204;	//0xC4506640
	UINT32                                                 reserved6205;	//0xC4506644
	UINT32                                                 reserved6206;	//0xC4506648
	UINT32                                                 reserved6207;	//0xC450664C
	UINT32                                                 reserved6208;	//0xC4506650
	UINT32                                                 reserved6209;	//0xC4506654
	UINT32                                                 reserved6210;	//0xC4506658
	UINT32                                                 reserved6211;	//0xC450665C
	UINT32                                                 reserved6212;	//0xC4506660
	UINT32                                                 reserved6213;	//0xC4506664
	UINT32                                                 reserved6214;	//0xC4506668
	UINT32                                                 reserved6215;	//0xC450666C
	UINT32                                                 reserved6216;	//0xC4506670
	UINT32                                                 reserved6217;	//0xC4506674
	UINT32                                                 reserved6218;	//0xC4506678
	UINT32                                                 reserved6219;	//0xC450667C
	UINT32                                                 reserved6220;	//0xC4506680
	UINT32                                                 reserved6221;	//0xC4506684
	UINT32                                                 reserved6222;	//0xC4506688
	UINT32                                                 reserved6223;	//0xC450668C
	UINT32                                                 reserved6224;	//0xC4506690
	UINT32                                                 reserved6225;	//0xC4506694
	UINT32                                                 reserved6226;	//0xC4506698
	UINT32                                                 reserved6227;	//0xC450669C
	UINT32                                                 reserved6228;	//0xC45066A0
	UINT32                                                 reserved6229;	//0xC45066A4
	UINT32                                                 reserved6230;	//0xC45066A8
	UINT32                                                 reserved6231;	//0xC45066AC
	UINT32                                                 reserved6232;	//0xC45066B0
	UINT32                                                 reserved6233;	//0xC45066B4
	UINT32                                                 reserved6234;	//0xC45066B8
	UINT32                                                 reserved6235;	//0xC45066BC
	UINT32                                                 reserved6236;	//0xC45066C0
	UINT32                                                 reserved6237;	//0xC45066C4
	UINT32                                                 reserved6238;	//0xC45066C8
	UINT32                                                 reserved6239;	//0xC45066CC
	UINT32                                                 reserved6240;	//0xC45066D0
	UINT32                                                 reserved6241;	//0xC45066D4
	UINT32                                                 reserved6242;	//0xC45066D8
	UINT32                                                 reserved6243;	//0xC45066DC
	UINT32                                                 reserved6244;	//0xC45066E0
	UINT32                                                 reserved6245;	//0xC45066E4
	UINT32                                                 reserved6246;	//0xC45066E8
	UINT32                                                 reserved6247;	//0xC45066EC
	UINT32                                                 reserved6248;	//0xC45066F0
	UINT32                                                 reserved6249;	//0xC45066F4
	UINT32                                                 reserved6250;	//0xC45066F8
	UINT32                                                 reserved6251;	//0xC45066FC
	REG_DDRC_M2_DEBUG_DFI_T                                   debug_dfi;	//0xC4506700
	UINT32                                                 reserved6252;	//0xC4506704
	UINT32                                                 reserved6253;	//0xC4506708
	UINT32                                                 reserved6254;	//0xC450670C
	UINT32                                                 reserved6255;	//0xC4506710
	UINT32                                                 reserved6256;	//0xC4506714
	UINT32                                                 reserved6257;	//0xC4506718
	UINT32                                                 reserved6258;	//0xC450671C
	UINT32                                                 reserved6259;	//0xC4506720
	UINT32                                                 reserved6260;	//0xC4506724
	UINT32                                                 reserved6261;	//0xC4506728
	UINT32                                                 reserved6262;	//0xC450672C
	UINT32                                                 reserved6263;	//0xC4506730
	UINT32                                                 reserved6264;	//0xC4506734
	UINT32                                                 reserved6265;	//0xC4506738
	UINT32                                                 reserved6266;	//0xC450673C
	UINT32                                                 reserved6267;	//0xC4506740
	UINT32                                                 reserved6268;	//0xC4506744
	UINT32                                                 reserved6269;	//0xC4506748
	UINT32                                                 reserved6270;	//0xC450674C
	UINT32                                                 reserved6271;	//0xC4506750
	UINT32                                                 reserved6272;	//0xC4506754
	UINT32                                                 reserved6273;	//0xC4506758
	UINT32                                                 reserved6274;	//0xC450675C
	UINT32                                                 reserved6275;	//0xC4506760
	UINT32                                                 reserved6276;	//0xC4506764
	UINT32                                                 reserved6277;	//0xC4506768
	UINT32                                                 reserved6278;	//0xC450676C
	UINT32                                                 reserved6279;	//0xC4506770
	UINT32                                                 reserved6280;	//0xC4506774
	UINT32                                                 reserved6281;	//0xC4506778
	UINT32                                                 reserved6282;	//0xC450677C
	UINT32                                                 reserved6283;	//0xC4506780
	UINT32                                                 reserved6284;	//0xC4506784
	UINT32                                                 reserved6285;	//0xC4506788
	UINT32                                                 reserved6286;	//0xC450678C
	UINT32                                                 reserved6287;	//0xC4506790
	UINT32                                                 reserved6288;	//0xC4506794
	UINT32                                                 reserved6289;	//0xC4506798
	UINT32                                                 reserved6290;	//0xC450679C
	UINT32                                                 reserved6291;	//0xC45067A0
	UINT32                                                 reserved6292;	//0xC45067A4
	UINT32                                                 reserved6293;	//0xC45067A8
	UINT32                                                 reserved6294;	//0xC45067AC
	UINT32                                                 reserved6295;	//0xC45067B0
	UINT32                                                 reserved6296;	//0xC45067B4
	UINT32                                                 reserved6297;	//0xC45067B8
	UINT32                                                 reserved6298;	//0xC45067BC
	UINT32                                                 reserved6299;	//0xC45067C0
	UINT32                                                 reserved6300;	//0xC45067C4
	UINT32                                                 reserved6301;	//0xC45067C8
	UINT32                                                 reserved6302;	//0xC45067CC
	UINT32                                                 reserved6303;	//0xC45067D0
	UINT32                                                 reserved6304;	//0xC45067D4
	UINT32                                                 reserved6305;	//0xC45067D8
	UINT32                                                 reserved6306;	//0xC45067DC
	UINT32                                                 reserved6307;	//0xC45067E0
	UINT32                                                 reserved6308;	//0xC45067E4
	UINT32                                                 reserved6309;	//0xC45067E8
	UINT32                                                 reserved6310;	//0xC45067EC
	UINT32                                                 reserved6311;	//0xC45067F0
	UINT32                                                 reserved6312;	//0xC45067F4
	UINT32                                                 reserved6313;	//0xC45067F8
	UINT32                                                 reserved6314;	//0xC45067FC
	REG_DDRC_M2_DRAM_BIST_CTRL_0_T                     dram_bist_ctrl_0;	//0xC4506800
	REG_DDRC_M2_DRAM_BIST_CTRL_1_T                     dram_bist_ctrl_1;	//0xC4506804
	REG_DDRC_M2_DRAM_BIST_CTRL_2_T                     dram_bist_ctrl_2;	//0xC4506808
	REG_DDRC_M2_DRAM_BIST_DATA_0_T                     dram_bist_data_0;	//0xC450680C
	REG_DDRC_M2_DRAM_BIST_DATA_1_T                     dram_bist_data_1;	//0xC4506810
	REG_DDRC_M2_DRAM_BIST_DATA_2_T                     dram_bist_data_2;	//0xC4506814
	REG_DDRC_M2_DRAM_BIST_ADDR_0_T                     dram_bist_addr_0;	//0xC4506818
	REG_DDRC_M2_DRAM_BIST_ADDR_1_T                     dram_bist_addr_1;	//0xC450681C
	REG_DDRC_M2_DRAM_BIST_ADDR_2_T                     dram_bist_addr_2;	//0xC4506820
	REG_DDRC_M2_DRAM_BIST_OPCMD_0_T                   dram_bist_opcmd_0;	//0xC4506824
	REG_DDRC_M2_DRAM_BIST_OPCMD_1_T                   dram_bist_opcmd_1;	//0xC4506828
	REG_DDRC_M2_DRAM_BIST_OPCMD_2_T                   dram_bist_opcmd_2;	//0xC450682C
	REG_DDRC_M2_DRAM_BIST_OPCMD_3_T                   dram_bist_opcmd_3;	//0xC4506830
	REG_DDRC_M2_DRAM_BIST_ERR_ADDR_INFO_T       dram_bist_err_addr_info;	//0xC4506834
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_00_T dram_bist_err_data_info_00;	//0xC4506838
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_01_T dram_bist_err_data_info_01;	//0xC450683C
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_02_T dram_bist_err_data_info_02;	//0xC4506840
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_03_T dram_bist_err_data_info_03;	//0xC4506844
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_04_T dram_bist_err_data_info_04;	//0xC4506848
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_05_T dram_bist_err_data_info_05;	//0xC450684C
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_06_T dram_bist_err_data_info_06;	//0xC4506850
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_07_T dram_bist_err_data_info_07;	//0xC4506854
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_08_T dram_bist_err_data_info_08;	//0xC4506858
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_09_T dram_bist_err_data_info_09;	//0xC450685C
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_10_T dram_bist_err_data_info_10;	//0xC4506860
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_11_T dram_bist_err_data_info_11;	//0xC4506864
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_12_T dram_bist_err_data_info_12;	//0xC4506868
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_13_T dram_bist_err_data_info_13;	//0xC450686C
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_14_T dram_bist_err_data_info_14;	//0xC4506870
	REG_DDRC_M2_DRAM_BIST_ERR_DATA_INFO_15_T dram_bist_err_data_info_15;	//0xC4506874
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_00_T dram_bist_exp_data_info_00;	//0xC4506878
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_01_T dram_bist_exp_data_info_01;	//0xC450687C
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_02_T dram_bist_exp_data_info_02;	//0xC4506880
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_03_T dram_bist_exp_data_info_03;	//0xC4506884
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_04_T dram_bist_exp_data_info_04;	//0xC4506888
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_05_T dram_bist_exp_data_info_05;	//0xC450688C
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_06_T dram_bist_exp_data_info_06;	//0xC4506890
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_07_T dram_bist_exp_data_info_07;	//0xC4506894
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_08_T dram_bist_exp_data_info_08;	//0xC4506898
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_09_T dram_bist_exp_data_info_09;	//0xC450689C
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_10_T dram_bist_exp_data_info_10;	//0xC45068A0
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_11_T dram_bist_exp_data_info_11;	//0xC45068A4
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_12_T dram_bist_exp_data_info_12;	//0xC45068A8
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_13_T dram_bist_exp_data_info_13;	//0xC45068AC
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_14_T dram_bist_exp_data_info_14;	//0xC45068B0
	REG_DDRC_M2_DRAM_BIST_EXP_DATA_INFO_15_T dram_bist_exp_data_info_15;	//0xC45068B4
	UINT32                                                 reserved6315;	//0xC45068B8
	UINT32                                                 reserved6316;	//0xC45068BC
	UINT32                                                 reserved6317;	//0xC45068C0
	UINT32                                                 reserved6318;	//0xC45068C4
	UINT32                                                 reserved6319;	//0xC45068C8
	UINT32                                                 reserved6320;	//0xC45068CC
	UINT32                                                 reserved6321;	//0xC45068D0
	UINT32                                                 reserved6322;	//0xC45068D4
	UINT32                                                 reserved6323;	//0xC45068D8
	UINT32                                                 reserved6324;	//0xC45068DC
	UINT32                                                 reserved6325;	//0xC45068E0
	UINT32                                                 reserved6326;	//0xC45068E4
	UINT32                                                 reserved6327;	//0xC45068E8
	UINT32                                                 reserved6328;	//0xC45068EC
	UINT32                                                 reserved6329;	//0xC45068F0
	UINT32                                                 reserved6330;	//0xC45068F4
	UINT32                                                 reserved6331;	//0xC45068F8
	UINT32                                                 reserved6332;	//0xC45068FC
	UINT32                                                 reserved6333;	//0xC4506900
	UINT32                                                 reserved6334;	//0xC4506904
	UINT32                                                 reserved6335;	//0xC4506908
	UINT32                                                 reserved6336;	//0xC450690C
	UINT32                                                 reserved6337;	//0xC4506910
	UINT32                                                 reserved6338;	//0xC4506914
	UINT32                                                 reserved6339;	//0xC4506918
	UINT32                                                 reserved6340;	//0xC450691C
	UINT32                                                 reserved6341;	//0xC4506920
	UINT32                                                 reserved6342;	//0xC4506924
	UINT32                                                 reserved6343;	//0xC4506928
	UINT32                                                 reserved6344;	//0xC450692C
	UINT32                                                 reserved6345;	//0xC4506930
	UINT32                                                 reserved6346;	//0xC4506934
	UINT32                                                 reserved6347;	//0xC4506938
	UINT32                                                 reserved6348;	//0xC450693C
	UINT32                                                 reserved6349;	//0xC4506940
	UINT32                                                 reserved6350;	//0xC4506944
	UINT32                                                 reserved6351;	//0xC4506948
	UINT32                                                 reserved6352;	//0xC450694C
	UINT32                                                 reserved6353;	//0xC4506950
	UINT32                                                 reserved6354;	//0xC4506954
	UINT32                                                 reserved6355;	//0xC4506958
	UINT32                                                 reserved6356;	//0xC450695C
	UINT32                                                 reserved6357;	//0xC4506960
	UINT32                                                 reserved6358;	//0xC4506964
	UINT32                                                 reserved6359;	//0xC4506968
	UINT32                                                 reserved6360;	//0xC450696C
	UINT32                                                 reserved6361;	//0xC4506970
	UINT32                                                 reserved6362;	//0xC4506974
	UINT32                                                 reserved6363;	//0xC4506978
	UINT32                                                 reserved6364;	//0xC450697C
	UINT32                                                 reserved6365;	//0xC4506980
	UINT32                                                 reserved6366;	//0xC4506984
	UINT32                                                 reserved6367;	//0xC4506988
	UINT32                                                 reserved6368;	//0xC450698C
	UINT32                                                 reserved6369;	//0xC4506990
	UINT32                                                 reserved6370;	//0xC4506994
	UINT32                                                 reserved6371;	//0xC4506998
	UINT32                                                 reserved6372;	//0xC450699C
	UINT32                                                 reserved6373;	//0xC45069A0
	UINT32                                                 reserved6374;	//0xC45069A4
	UINT32                                                 reserved6375;	//0xC45069A8
	UINT32                                                 reserved6376;	//0xC45069AC
	UINT32                                                 reserved6377;	//0xC45069B0
	UINT32                                                 reserved6378;	//0xC45069B4
	UINT32                                                 reserved6379;	//0xC45069B8
	UINT32                                                 reserved6380;	//0xC45069BC
	UINT32                                                 reserved6381;	//0xC45069C0
	UINT32                                                 reserved6382;	//0xC45069C4
	UINT32                                                 reserved6383;	//0xC45069C8
	UINT32                                                 reserved6384;	//0xC45069CC
	UINT32                                                 reserved6385;	//0xC45069D0
	UINT32                                                 reserved6386;	//0xC45069D4
	UINT32                                                 reserved6387;	//0xC45069D8
	UINT32                                                 reserved6388;	//0xC45069DC
	UINT32                                                 reserved6389;	//0xC45069E0
	UINT32                                                 reserved6390;	//0xC45069E4
	UINT32                                                 reserved6391;	//0xC45069E8
	UINT32                                                 reserved6392;	//0xC45069EC
	UINT32                                                 reserved6393;	//0xC45069F0
	UINT32                                                 reserved6394;	//0xC45069F4
	UINT32                                                 reserved6395;	//0xC45069F8
	UINT32                                                 reserved6396;	//0xC45069FC
	UINT32                                                 reserved6397;	//0xC4506A00
	UINT32                                                 reserved6398;	//0xC4506A04
	UINT32                                                 reserved6399;	//0xC4506A08
	UINT32                                                 reserved6400;	//0xC4506A0C
	UINT32                                                 reserved6401;	//0xC4506A10
	UINT32                                                 reserved6402;	//0xC4506A14
	UINT32                                                 reserved6403;	//0xC4506A18
	UINT32                                                 reserved6404;	//0xC4506A1C
	UINT32                                                 reserved6405;	//0xC4506A20
	UINT32                                                 reserved6406;	//0xC4506A24
	UINT32                                                 reserved6407;	//0xC4506A28
	UINT32                                                 reserved6408;	//0xC4506A2C
	UINT32                                                 reserved6409;	//0xC4506A30
	UINT32                                                 reserved6410;	//0xC4506A34
	UINT32                                                 reserved6411;	//0xC4506A38
	UINT32                                                 reserved6412;	//0xC4506A3C
	UINT32                                                 reserved6413;	//0xC4506A40
	UINT32                                                 reserved6414;	//0xC4506A44
	UINT32                                                 reserved6415;	//0xC4506A48
	UINT32                                                 reserved6416;	//0xC4506A4C
	UINT32                                                 reserved6417;	//0xC4506A50
	UINT32                                                 reserved6418;	//0xC4506A54
	UINT32                                                 reserved6419;	//0xC4506A58
	UINT32                                                 reserved6420;	//0xC4506A5C
	UINT32                                                 reserved6421;	//0xC4506A60
	UINT32                                                 reserved6422;	//0xC4506A64
	UINT32                                                 reserved6423;	//0xC4506A68
	UINT32                                                 reserved6424;	//0xC4506A6C
	UINT32                                                 reserved6425;	//0xC4506A70
	UINT32                                                 reserved6426;	//0xC4506A74
	UINT32                                                 reserved6427;	//0xC4506A78
	UINT32                                                 reserved6428;	//0xC4506A7C
	UINT32                                                 reserved6429;	//0xC4506A80
	UINT32                                                 reserved6430;	//0xC4506A84
	UINT32                                                 reserved6431;	//0xC4506A88
	UINT32                                                 reserved6432;	//0xC4506A8C
	UINT32                                                 reserved6433;	//0xC4506A90
	UINT32                                                 reserved6434;	//0xC4506A94
	UINT32                                                 reserved6435;	//0xC4506A98
	UINT32                                                 reserved6436;	//0xC4506A9C
	UINT32                                                 reserved6437;	//0xC4506AA0
	UINT32                                                 reserved6438;	//0xC4506AA4
	UINT32                                                 reserved6439;	//0xC4506AA8
	UINT32                                                 reserved6440;	//0xC4506AAC
	UINT32                                                 reserved6441;	//0xC4506AB0
	UINT32                                                 reserved6442;	//0xC4506AB4
	UINT32                                                 reserved6443;	//0xC4506AB8
	UINT32                                                 reserved6444;	//0xC4506ABC
	UINT32                                                 reserved6445;	//0xC4506AC0
	UINT32                                                 reserved6446;	//0xC4506AC4
	UINT32                                                 reserved6447;	//0xC4506AC8
	UINT32                                                 reserved6448;	//0xC4506ACC
	UINT32                                                 reserved6449;	//0xC4506AD0
	UINT32                                                 reserved6450;	//0xC4506AD4
	UINT32                                                 reserved6451;	//0xC4506AD8
	UINT32                                                 reserved6452;	//0xC4506ADC
	UINT32                                                 reserved6453;	//0xC4506AE0
	UINT32                                                 reserved6454;	//0xC4506AE4
	UINT32                                                 reserved6455;	//0xC4506AE8
	UINT32                                                 reserved6456;	//0xC4506AEC
	UINT32                                                 reserved6457;	//0xC4506AF0
	UINT32                                                 reserved6458;	//0xC4506AF4
	UINT32                                                 reserved6459;	//0xC4506AF8
	UINT32                                                 reserved6460;	//0xC4506AFC
	UINT32                                                 reserved6461;	//0xC4506B00
	UINT32                                                 reserved6462;	//0xC4506B04
	UINT32                                                 reserved6463;	//0xC4506B08
	UINT32                                                 reserved6464;	//0xC4506B0C
	UINT32                                                 reserved6465;	//0xC4506B10
	UINT32                                                 reserved6466;	//0xC4506B14
	UINT32                                                 reserved6467;	//0xC4506B18
	UINT32                                                 reserved6468;	//0xC4506B1C
	UINT32                                                 reserved6469;	//0xC4506B20
	UINT32                                                 reserved6470;	//0xC4506B24
	UINT32                                                 reserved6471;	//0xC4506B28
	UINT32                                                 reserved6472;	//0xC4506B2C
	UINT32                                                 reserved6473;	//0xC4506B30
	UINT32                                                 reserved6474;	//0xC4506B34
	UINT32                                                 reserved6475;	//0xC4506B38
	UINT32                                                 reserved6476;	//0xC4506B3C
	UINT32                                                 reserved6477;	//0xC4506B40
	UINT32                                                 reserved6478;	//0xC4506B44
	UINT32                                                 reserved6479;	//0xC4506B48
	UINT32                                                 reserved6480;	//0xC4506B4C
	UINT32                                                 reserved6481;	//0xC4506B50
	UINT32                                                 reserved6482;	//0xC4506B54
	UINT32                                                 reserved6483;	//0xC4506B58
	UINT32                                                 reserved6484;	//0xC4506B5C
	UINT32                                                 reserved6485;	//0xC4506B60
	UINT32                                                 reserved6486;	//0xC4506B64
	UINT32                                                 reserved6487;	//0xC4506B68
	UINT32                                                 reserved6488;	//0xC4506B6C
	UINT32                                                 reserved6489;	//0xC4506B70
	UINT32                                                 reserved6490;	//0xC4506B74
	UINT32                                                 reserved6491;	//0xC4506B78
	UINT32                                                 reserved6492;	//0xC4506B7C
	UINT32                                                 reserved6493;	//0xC4506B80
	UINT32                                                 reserved6494;	//0xC4506B84
	UINT32                                                 reserved6495;	//0xC4506B88
	UINT32                                                 reserved6496;	//0xC4506B8C
	UINT32                                                 reserved6497;	//0xC4506B90
	UINT32                                                 reserved6498;	//0xC4506B94
	UINT32                                                 reserved6499;	//0xC4506B98
	UINT32                                                 reserved6500;	//0xC4506B9C
	UINT32                                                 reserved6501;	//0xC4506BA0
	UINT32                                                 reserved6502;	//0xC4506BA4
	UINT32                                                 reserved6503;	//0xC4506BA8
	UINT32                                                 reserved6504;	//0xC4506BAC
	UINT32                                                 reserved6505;	//0xC4506BB0
	UINT32                                                 reserved6506;	//0xC4506BB4
	UINT32                                                 reserved6507;	//0xC4506BB8
	UINT32                                                 reserved6508;	//0xC4506BBC
	UINT32                                                 reserved6509;	//0xC4506BC0
	UINT32                                                 reserved6510;	//0xC4506BC4
	UINT32                                                 reserved6511;	//0xC4506BC8
	UINT32                                                 reserved6512;	//0xC4506BCC
	UINT32                                                 reserved6513;	//0xC4506BD0
	UINT32                                                 reserved6514;	//0xC4506BD4
	UINT32                                                 reserved6515;	//0xC4506BD8
	UINT32                                                 reserved6516;	//0xC4506BDC
	UINT32                                                 reserved6517;	//0xC4506BE0
	UINT32                                                 reserved6518;	//0xC4506BE4
	UINT32                                                 reserved6519;	//0xC4506BE8
	UINT32                                                 reserved6520;	//0xC4506BEC
	UINT32                                                 reserved6521;	//0xC4506BF0
	UINT32                                                 reserved6522;	//0xC4506BF4
	UINT32                                                 reserved6523;	//0xC4506BF8
	UINT32                                                 reserved6524;	//0xC4506BFC
	UINT32                                                 reserved6525;	//0xC4506C00
	UINT32                                                 reserved6526;	//0xC4506C04
	UINT32                                                 reserved6527;	//0xC4506C08
	UINT32                                                 reserved6528;	//0xC4506C0C
	UINT32                                                 reserved6529;	//0xC4506C10
	UINT32                                                 reserved6530;	//0xC4506C14
	UINT32                                                 reserved6531;	//0xC4506C18
	UINT32                                                 reserved6532;	//0xC4506C1C
	UINT32                                                 reserved6533;	//0xC4506C20
	UINT32                                                 reserved6534;	//0xC4506C24
	UINT32                                                 reserved6535;	//0xC4506C28
	UINT32                                                 reserved6536;	//0xC4506C2C
	UINT32                                                 reserved6537;	//0xC4506C30
	UINT32                                                 reserved6538;	//0xC4506C34
	UINT32                                                 reserved6539;	//0xC4506C38
	UINT32                                                 reserved6540;	//0xC4506C3C
	UINT32                                                 reserved6541;	//0xC4506C40
	UINT32                                                 reserved6542;	//0xC4506C44
	UINT32                                                 reserved6543;	//0xC4506C48
	UINT32                                                 reserved6544;	//0xC4506C4C
	UINT32                                                 reserved6545;	//0xC4506C50
	UINT32                                                 reserved6546;	//0xC4506C54
	UINT32                                                 reserved6547;	//0xC4506C58
	UINT32                                                 reserved6548;	//0xC4506C5C
	UINT32                                                 reserved6549;	//0xC4506C60
	UINT32                                                 reserved6550;	//0xC4506C64
	UINT32                                                 reserved6551;	//0xC4506C68
	UINT32                                                 reserved6552;	//0xC4506C6C
	UINT32                                                 reserved6553;	//0xC4506C70
	UINT32                                                 reserved6554;	//0xC4506C74
	UINT32                                                 reserved6555;	//0xC4506C78
	UINT32                                                 reserved6556;	//0xC4506C7C
	UINT32                                                 reserved6557;	//0xC4506C80
	UINT32                                                 reserved6558;	//0xC4506C84
	UINT32                                                 reserved6559;	//0xC4506C88
	UINT32                                                 reserved6560;	//0xC4506C8C
	UINT32                                                 reserved6561;	//0xC4506C90
	UINT32                                                 reserved6562;	//0xC4506C94
	UINT32                                                 reserved6563;	//0xC4506C98
	UINT32                                                 reserved6564;	//0xC4506C9C
	UINT32                                                 reserved6565;	//0xC4506CA0
	UINT32                                                 reserved6566;	//0xC4506CA4
	UINT32                                                 reserved6567;	//0xC4506CA8
	UINT32                                                 reserved6568;	//0xC4506CAC
	UINT32                                                 reserved6569;	//0xC4506CB0
	UINT32                                                 reserved6570;	//0xC4506CB4
	UINT32                                                 reserved6571;	//0xC4506CB8
	UINT32                                                 reserved6572;	//0xC4506CBC
	UINT32                                                 reserved6573;	//0xC4506CC0
	UINT32                                                 reserved6574;	//0xC4506CC4
	UINT32                                                 reserved6575;	//0xC4506CC8
	UINT32                                                 reserved6576;	//0xC4506CCC
	UINT32                                                 reserved6577;	//0xC4506CD0
	UINT32                                                 reserved6578;	//0xC4506CD4
	UINT32                                                 reserved6579;	//0xC4506CD8
	UINT32                                                 reserved6580;	//0xC4506CDC
	UINT32                                                 reserved6581;	//0xC4506CE0
	UINT32                                                 reserved6582;	//0xC4506CE4
	UINT32                                                 reserved6583;	//0xC4506CE8
	UINT32                                                 reserved6584;	//0xC4506CEC
	UINT32                                                 reserved6585;	//0xC4506CF0
	UINT32                                                 reserved6586;	//0xC4506CF4
	UINT32                                                 reserved6587;	//0xC4506CF8
	UINT32                                                 reserved6588;	//0xC4506CFC
	UINT32                                                 reserved6589;	//0xC4506D00
	UINT32                                                 reserved6590;	//0xC4506D04
	UINT32                                                 reserved6591;	//0xC4506D08
	UINT32                                                 reserved6592;	//0xC4506D0C
	UINT32                                                 reserved6593;	//0xC4506D10
	UINT32                                                 reserved6594;	//0xC4506D14
	UINT32                                                 reserved6595;	//0xC4506D18
	UINT32                                                 reserved6596;	//0xC4506D1C
	UINT32                                                 reserved6597;	//0xC4506D20
	UINT32                                                 reserved6598;	//0xC4506D24
	UINT32                                                 reserved6599;	//0xC4506D28
	UINT32                                                 reserved6600;	//0xC4506D2C
	UINT32                                                 reserved6601;	//0xC4506D30
	UINT32                                                 reserved6602;	//0xC4506D34
	UINT32                                                 reserved6603;	//0xC4506D38
	UINT32                                                 reserved6604;	//0xC4506D3C
	UINT32                                                 reserved6605;	//0xC4506D40
	UINT32                                                 reserved6606;	//0xC4506D44
	UINT32                                                 reserved6607;	//0xC4506D48
	UINT32                                                 reserved6608;	//0xC4506D4C
	UINT32                                                 reserved6609;	//0xC4506D50
	UINT32                                                 reserved6610;	//0xC4506D54
	UINT32                                                 reserved6611;	//0xC4506D58
	UINT32                                                 reserved6612;	//0xC4506D5C
	UINT32                                                 reserved6613;	//0xC4506D60
	UINT32                                                 reserved6614;	//0xC4506D64
	UINT32                                                 reserved6615;	//0xC4506D68
	UINT32                                                 reserved6616;	//0xC4506D6C
	UINT32                                                 reserved6617;	//0xC4506D70
	UINT32                                                 reserved6618;	//0xC4506D74
	UINT32                                                 reserved6619;	//0xC4506D78
	UINT32                                                 reserved6620;	//0xC4506D7C
	UINT32                                                 reserved6621;	//0xC4506D80
	UINT32                                                 reserved6622;	//0xC4506D84
	UINT32                                                 reserved6623;	//0xC4506D88
	UINT32                                                 reserved6624;	//0xC4506D8C
	UINT32                                                 reserved6625;	//0xC4506D90
	UINT32                                                 reserved6626;	//0xC4506D94
	UINT32                                                 reserved6627;	//0xC4506D98
	UINT32                                                 reserved6628;	//0xC4506D9C
	UINT32                                                 reserved6629;	//0xC4506DA0
	UINT32                                                 reserved6630;	//0xC4506DA4
	UINT32                                                 reserved6631;	//0xC4506DA8
	UINT32                                                 reserved6632;	//0xC4506DAC
	UINT32                                                 reserved6633;	//0xC4506DB0
	UINT32                                                 reserved6634;	//0xC4506DB4
	UINT32                                                 reserved6635;	//0xC4506DB8
	UINT32                                                 reserved6636;	//0xC4506DBC
	UINT32                                                 reserved6637;	//0xC4506DC0
	UINT32                                                 reserved6638;	//0xC4506DC4
	UINT32                                                 reserved6639;	//0xC4506DC8
	UINT32                                                 reserved6640;	//0xC4506DCC
	UINT32                                                 reserved6641;	//0xC4506DD0
	UINT32                                                 reserved6642;	//0xC4506DD4
	UINT32                                                 reserved6643;	//0xC4506DD8
	UINT32                                                 reserved6644;	//0xC4506DDC
	UINT32                                                 reserved6645;	//0xC4506DE0
	UINT32                                                 reserved6646;	//0xC4506DE4
	UINT32                                                 reserved6647;	//0xC4506DE8
	UINT32                                                 reserved6648;	//0xC4506DEC
	UINT32                                                 reserved6649;	//0xC4506DF0
	UINT32                                                 reserved6650;	//0xC4506DF4
	UINT32                                                 reserved6651;	//0xC4506DF8
	UINT32                                                 reserved6652;	//0xC4506DFC
	UINT32                                                 reserved6653;	//0xC4506E00
	UINT32                                                 reserved6654;	//0xC4506E04
	UINT32                                                 reserved6655;	//0xC4506E08
	UINT32                                                 reserved6656;	//0xC4506E0C
	UINT32                                                 reserved6657;	//0xC4506E10
	UINT32                                                 reserved6658;	//0xC4506E14
	UINT32                                                 reserved6659;	//0xC4506E18
	UINT32                                                 reserved6660;	//0xC4506E1C
	UINT32                                                 reserved6661;	//0xC4506E20
	UINT32                                                 reserved6662;	//0xC4506E24
	UINT32                                                 reserved6663;	//0xC4506E28
	UINT32                                                 reserved6664;	//0xC4506E2C
	UINT32                                                 reserved6665;	//0xC4506E30
	UINT32                                                 reserved6666;	//0xC4506E34
	UINT32                                                 reserved6667;	//0xC4506E38
	UINT32                                                 reserved6668;	//0xC4506E3C
	UINT32                                                 reserved6669;	//0xC4506E40
	UINT32                                                 reserved6670;	//0xC4506E44
	UINT32                                                 reserved6671;	//0xC4506E48
	UINT32                                                 reserved6672;	//0xC4506E4C
	UINT32                                                 reserved6673;	//0xC4506E50
	UINT32                                                 reserved6674;	//0xC4506E54
	UINT32                                                 reserved6675;	//0xC4506E58
	UINT32                                                 reserved6676;	//0xC4506E5C
	UINT32                                                 reserved6677;	//0xC4506E60
	UINT32                                                 reserved6678;	//0xC4506E64
	UINT32                                                 reserved6679;	//0xC4506E68
	UINT32                                                 reserved6680;	//0xC4506E6C
	UINT32                                                 reserved6681;	//0xC4506E70
	UINT32                                                 reserved6682;	//0xC4506E74
	UINT32                                                 reserved6683;	//0xC4506E78
	UINT32                                                 reserved6684;	//0xC4506E7C
	UINT32                                                 reserved6685;	//0xC4506E80
	UINT32                                                 reserved6686;	//0xC4506E84
	UINT32                                                 reserved6687;	//0xC4506E88
	UINT32                                                 reserved6688;	//0xC4506E8C
	UINT32                                                 reserved6689;	//0xC4506E90
	UINT32                                                 reserved6690;	//0xC4506E94
	UINT32                                                 reserved6691;	//0xC4506E98
	UINT32                                                 reserved6692;	//0xC4506E9C
	UINT32                                                 reserved6693;	//0xC4506EA0
	UINT32                                                 reserved6694;	//0xC4506EA4
	UINT32                                                 reserved6695;	//0xC4506EA8
	UINT32                                                 reserved6696;	//0xC4506EAC
	UINT32                                                 reserved6697;	//0xC4506EB0
	UINT32                                                 reserved6698;	//0xC4506EB4
	UINT32                                                 reserved6699;	//0xC4506EB8
	UINT32                                                 reserved6700;	//0xC4506EBC
	UINT32                                                 reserved6701;	//0xC4506EC0
	UINT32                                                 reserved6702;	//0xC4506EC4
	UINT32                                                 reserved6703;	//0xC4506EC8
	UINT32                                                 reserved6704;	//0xC4506ECC
	UINT32                                                 reserved6705;	//0xC4506ED0
	UINT32                                                 reserved6706;	//0xC4506ED4
	UINT32                                                 reserved6707;	//0xC4506ED8
	UINT32                                                 reserved6708;	//0xC4506EDC
	UINT32                                                 reserved6709;	//0xC4506EE0
	UINT32                                                 reserved6710;	//0xC4506EE4
	UINT32                                                 reserved6711;	//0xC4506EE8
	UINT32                                                 reserved6712;	//0xC4506EEC
	UINT32                                                 reserved6713;	//0xC4506EF0
	UINT32                                                 reserved6714;	//0xC4506EF4
	UINT32                                                 reserved6715;	//0xC4506EF8
	UINT32                                                 reserved6716;	//0xC4506EFC
	UINT32                                                 reserved6717;	//0xC4506F00
	UINT32                                                 reserved6718;	//0xC4506F04
	UINT32                                                 reserved6719;	//0xC4506F08
	UINT32                                                 reserved6720;	//0xC4506F0C
	UINT32                                                 reserved6721;	//0xC4506F10
	UINT32                                                 reserved6722;	//0xC4506F14
	UINT32                                                 reserved6723;	//0xC4506F18
	UINT32                                                 reserved6724;	//0xC4506F1C
	UINT32                                                 reserved6725;	//0xC4506F20
	UINT32                                                 reserved6726;	//0xC4506F24
	UINT32                                                 reserved6727;	//0xC4506F28
	UINT32                                                 reserved6728;	//0xC4506F2C
	UINT32                                                 reserved6729;	//0xC4506F30
	UINT32                                                 reserved6730;	//0xC4506F34
	UINT32                                                 reserved6731;	//0xC4506F38
	UINT32                                                 reserved6732;	//0xC4506F3C
	UINT32                                                 reserved6733;	//0xC4506F40
	UINT32                                                 reserved6734;	//0xC4506F44
	UINT32                                                 reserved6735;	//0xC4506F48
	UINT32                                                 reserved6736;	//0xC4506F4C
	UINT32                                                 reserved6737;	//0xC4506F50
	UINT32                                                 reserved6738;	//0xC4506F54
	UINT32                                                 reserved6739;	//0xC4506F58
	UINT32                                                 reserved6740;	//0xC4506F5C
	UINT32                                                 reserved6741;	//0xC4506F60
	UINT32                                                 reserved6742;	//0xC4506F64
	UINT32                                                 reserved6743;	//0xC4506F68
	UINT32                                                 reserved6744;	//0xC4506F6C
	UINT32                                                 reserved6745;	//0xC4506F70
	UINT32                                                 reserved6746;	//0xC4506F74
	UINT32                                                 reserved6747;	//0xC4506F78
	UINT32                                                 reserved6748;	//0xC4506F7C
	UINT32                                                 reserved6749;	//0xC4506F80
	UINT32                                                 reserved6750;	//0xC4506F84
	UINT32                                                 reserved6751;	//0xC4506F88
	UINT32                                                 reserved6752;	//0xC4506F8C
	UINT32                                                 reserved6753;	//0xC4506F90
	UINT32                                                 reserved6754;	//0xC4506F94
	UINT32                                                 reserved6755;	//0xC4506F98
	UINT32                                                 reserved6756;	//0xC4506F9C
	UINT32                                                 reserved6757;	//0xC4506FA0
	UINT32                                                 reserved6758;	//0xC4506FA4
	UINT32                                                 reserved6759;	//0xC4506FA8
	UINT32                                                 reserved6760;	//0xC4506FAC
	UINT32                                                 reserved6761;	//0xC4506FB0
	UINT32                                                 reserved6762;	//0xC4506FB4
	UINT32                                                 reserved6763;	//0xC4506FB8
	UINT32                                                 reserved6764;	//0xC4506FBC
	UINT32                                                 reserved6765;	//0xC4506FC0
	UINT32                                                 reserved6766;	//0xC4506FC4
	UINT32                                                 reserved6767;	//0xC4506FC8
	UINT32                                                 reserved6768;	//0xC4506FCC
	UINT32                                                 reserved6769;	//0xC4506FD0
	UINT32                                                 reserved6770;	//0xC4506FD4
	UINT32                                                 reserved6771;	//0xC4506FD8
	UINT32                                                 reserved6772;	//0xC4506FDC
	REG_DDRC_M2_REY_SPARE_T                                   rey_spare;	//0xC4506FE0
}REG_DDRC_M2_T;

extern volatile REG_DDRC_M2_T*                     gpREG_DDRC_M2;
  
#endif
