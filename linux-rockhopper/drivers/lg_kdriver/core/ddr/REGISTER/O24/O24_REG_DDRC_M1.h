#ifndef _REG_DDRC_M1_h
#define _REG_DDRC_M1_h
//Header File for DDRC_M1 in \O24\O24_DRAM_M1_Register_Manual.xls

#define REG_DDRC_M1_DRAM_CONF                                               (APB_DDRC_M1_BASE+0x0000)
#define REG_DDRC_M1_MODE_SEL                                                (APB_DDRC_M1_BASE+0x0004)
#define REG_DDRC_M1_BASE_PERIOD                                             (APB_DDRC_M1_BASE+0x0008)
#define REG_DDRC_M1_ALP                                                     (APB_DDRC_M1_BASE+0x0100)
#define REG_DDRC_M1_CGL                                                     (APB_DDRC_M1_BASE+0x0104)
#define REG_DDRC_M1_CGL_MON                                                 (APB_DDRC_M1_BASE+0x0108)
#define REG_DDRC_M1_PERFMON                                                 (APB_DDRC_M1_BASE+0x0200)
#define REG_DDRC_M1_PERFMON_EMG_MAX                                         (APB_DDRC_M1_BASE+0x0204)
#define REG_DDRC_M1_PERFMON_W0                                              (APB_DDRC_M1_BASE+0x0210)
#define REG_DDRC_M1_PERFMON_W1                                              (APB_DDRC_M1_BASE+0x0214)
#define REG_DDRC_M1_PERFMON_W2                                              (APB_DDRC_M1_BASE+0x0218)
#define REG_DDRC_M1_PERFMON_W3                                              (APB_DDRC_M1_BASE+0x021C)
#define REG_DDRC_M1_PERFMON_R0                                              (APB_DDRC_M1_BASE+0x0220)
#define REG_DDRC_M1_PERFMON_R1                                              (APB_DDRC_M1_BASE+0x0224)
#define REG_DDRC_M1_PERFMON_R2                                              (APB_DDRC_M1_BASE+0x0228)
#define REG_DDRC_M1_PERFMON_R3                                              (APB_DDRC_M1_BASE+0x022C)
#define REG_DDRC_M1_LATMON                                                  (APB_DDRC_M1_BASE+0x0230)
#define REG_DDRC_M1_DFS                                                     (APB_DDRC_M1_BASE+0x0300)
#define REG_DDRC_M1_DFS_RESULT                                              (APB_DDRC_M1_BASE+0x0304)
#define REG_DDRC_M1_ADDR_MAP                                                (APB_DDRC_M1_BASE+0x0400)
#define REG_DDRC_M1_COMMON                                                  (APB_DDRC_M1_BASE+0x0404)
#define REG_DDRC_M1_DATA_ENC0                                               (APB_DDRC_M1_BASE+0x0408)
#define REG_DDRC_M1_DATA_ENC1                                               (APB_DDRC_M1_BASE+0x040C)
#define REG_DDRC_M1_RD_URG                                                  (APB_DDRC_M1_BASE+0x0500)
#define REG_DDRC_M1_WR_URG                                                  (APB_DDRC_M1_BASE+0x0504)
#define REG_DDRC_M1_FIFO_RDY                                                (APB_DDRC_M1_BASE+0x1000)
#define REG_DDRC_M1_FIFO_STATUS                                             (APB_DDRC_M1_BASE+0x1004)
#define REG_DDRC_M1_FIFO_CONF                                               (APB_DDRC_M1_BASE+0x1008)
#define REG_DDRC_M1_LIMITER_EN                                              (APB_DDRC_M1_BASE+0x1010)
#define REG_DDRC_M1_LIMITER_AW_THR                                          (APB_DDRC_M1_BASE+0x1014)
#define REG_DDRC_M1_LIMITER_W_THR                                           (APB_DDRC_M1_BASE+0x1018)
#define REG_DDRC_M1_LIMITER_AR_THR                                          (APB_DDRC_M1_BASE+0x1024)
#define REG_DDRC_M1_LIMITER_R_THR                                           (APB_DDRC_M1_BASE+0x1028)
#define REG_DDRC_M1_FIFO_MUX                                                (APB_DDRC_M1_BASE+0x1100)
#define REG_DDRC_M1_FIFO_MUX_MAX                                            (APB_DDRC_M1_BASE+0x1104)
#define REG_DDRC_M1_FIFO_MUX_WR_PRT                                         (APB_DDRC_M1_BASE+0x1108)
#define REG_DDRC_M1_FIFO_MUX_RD_PRT                                         (APB_DDRC_M1_BASE+0x110C)
#define REG_DDRC_M1_FIFO_MUX_PRT_MAX                                        (APB_DDRC_M1_BASE+0x1110)
#define REG_DDRC_M1_PQ                                                      (APB_DDRC_M1_BASE+0x2000)
#define REG_DDRC_M1_BQ                                                      (APB_DDRC_M1_BASE+0x2004)
#define REG_DDRC_M1_BQ_RW_THR                                               (APB_DDRC_M1_BASE+0x2008)
#define REG_DDRC_M1_BQ_HYB_STV                                              (APB_DDRC_M1_BASE+0x200C)
#define REG_DDRC_M1_LPD4_MAIN_FSM_INIT_0                                    (APB_DDRC_M1_BASE+0x3000)
#define REG_DDRC_M1_LPD4_MAIN_FSM_INIT_1                                    (APB_DDRC_M1_BASE+0x3004)
#define REG_DDRC_M1_LPD4_MAIN_FSM_INIT_2                                    (APB_DDRC_M1_BASE+0x3008)
#define REG_DDRC_M1_LPD4_MAIN_FSM_CTRL                                      (APB_DDRC_M1_BASE+0x300C)
#define REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_0                                (APB_DDRC_M1_BASE+0x3010)
#define REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_1                                (APB_DDRC_M1_BASE+0x3014)
#define REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_2                                (APB_DDRC_M1_BASE+0x3018)
#define REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_3                                (APB_DDRC_M1_BASE+0x301C)
#define REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_4                                (APB_DDRC_M1_BASE+0x3020)
#define REG_DDRC_M1_LPD4_MAIN_FSM_DFS_MRW                                   (APB_DDRC_M1_BASE+0x3024)
#define REG_DDRC_M1_LPD4_MAIN_FSM_CTRLUPD                                   (APB_DDRC_M1_BASE+0x3028)
#define REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_0                                (APB_DDRC_M1_BASE+0x302C)
#define REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_1                                (APB_DDRC_M1_BASE+0x3030)
#define REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_2                                (APB_DDRC_M1_BASE+0x3034)
#define REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_3                                (APB_DDRC_M1_BASE+0x3038)
#define REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_4                                (APB_DDRC_M1_BASE+0x303C)
#define REG_DDRC_M1_LPD4_MR_CTRL_0                                          (APB_DDRC_M1_BASE+0x3050)
#define REG_DDRC_M1_LPD4_MR_CTRL_1                                          (APB_DDRC_M1_BASE+0x3054)
#define REG_DDRC_M1_LPD4_MR_CTRL_2                                          (APB_DDRC_M1_BASE+0x3058)
#define REG_DDRC_M1_LPD4_REF_REQ_CTRL                                       (APB_DDRC_M1_BASE+0x3060)
#define REG_DDRC_M1_LPD4_REF_CTRL                                           (APB_DDRC_M1_BASE+0x3070)
#define REG_DDRC_M1_LPD4_BANK_FSM                                           (APB_DDRC_M1_BASE+0x3080)
#define REG_DDRC_M1_LPD4_BANK_STATUS                                        (APB_DDRC_M1_BASE+0x30A0)
#define REG_DDRC_M1_LPD4_PHY_IF                                             (APB_DDRC_M1_BASE+0x30C0)
#define REG_DDRC_M1_LPD4_DFS0_MR_0_CH0                                      (APB_DDRC_M1_BASE+0x3100)
#define REG_DDRC_M1_LPD4_DFS0_MR_1_CH0                                      (APB_DDRC_M1_BASE+0x3104)
#define REG_DDRC_M1_LPD4_DFS0_MR_2_CH0                                      (APB_DDRC_M1_BASE+0x3108)
#define REG_DDRC_M1_LPD4_DFS0_MR_3_CH0                                      (APB_DDRC_M1_BASE+0x310C)
#define REG_DDRC_M1_LPD4_DFS0_MR_4_CH0                                      (APB_DDRC_M1_BASE+0x3110)
#define REG_DDRC_M1_LPD4_DFS0_MR_5_CH0                                      (APB_DDRC_M1_BASE+0x3114)
#define REG_DDRC_M1_LPD4_DFS0_MR_6_CH0                                      (APB_DDRC_M1_BASE+0x3118)
#define REG_DDRC_M1_LPD4_DFS0_MR_0_CH1                                      (APB_DDRC_M1_BASE+0x3120)
#define REG_DDRC_M1_LPD4_DFS0_MR_1_CH1                                      (APB_DDRC_M1_BASE+0x3124)
#define REG_DDRC_M1_LPD4_DFS0_MR_2_CH1                                      (APB_DDRC_M1_BASE+0x3128)
#define REG_DDRC_M1_LPD4_DFS0_MR_3_CH1                                      (APB_DDRC_M1_BASE+0x312C)
#define REG_DDRC_M1_LPD4_DFS0_MR_4_CH1                                      (APB_DDRC_M1_BASE+0x3130)
#define REG_DDRC_M1_LPD4_DFS0_MR_5_CH1                                      (APB_DDRC_M1_BASE+0x3134)
#define REG_DDRC_M1_LPD4_DFS0_MR_6_CH1                                      (APB_DDRC_M1_BASE+0x3138)
#define REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_0                                    (APB_DDRC_M1_BASE+0x3140)
#define REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_1                                    (APB_DDRC_M1_BASE+0x3144)
#define REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_2                                    (APB_DDRC_M1_BASE+0x3148)
#define REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_3                                    (APB_DDRC_M1_BASE+0x314C)
#define REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_4                                    (APB_DDRC_M1_BASE+0x3150)
#define REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_5                                    (APB_DDRC_M1_BASE+0x3154)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_0                                (APB_DDRC_M1_BASE+0x3160)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_1                                (APB_DDRC_M1_BASE+0x3164)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_2                                (APB_DDRC_M1_BASE+0x3168)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_3                                (APB_DDRC_M1_BASE+0x316C)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_4                                (APB_DDRC_M1_BASE+0x3170)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_5                                (APB_DDRC_M1_BASE+0x3174)
#define REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_6                                (APB_DDRC_M1_BASE+0x3178)
#define REG_DDRC_M1_LPD4_DFS0_REF_CTRL                                      (APB_DDRC_M1_BASE+0x3190)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_0                                 (APB_DDRC_M1_BASE+0x31A0)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_1                                 (APB_DDRC_M1_BASE+0x31A4)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_2                                 (APB_DDRC_M1_BASE+0x31A8)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_3                                 (APB_DDRC_M1_BASE+0x31AC)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_4                                 (APB_DDRC_M1_BASE+0x31B0)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_5                                 (APB_DDRC_M1_BASE+0x31B4)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_6                                 (APB_DDRC_M1_BASE+0x31B8)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_7                                 (APB_DDRC_M1_BASE+0x31BC)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_8                                 (APB_DDRC_M1_BASE+0x31C0)
#define REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_9                                 (APB_DDRC_M1_BASE+0x31C4)
#define REG_DDRC_M1_LPD4_DFS0_PHY_IF                                        (APB_DDRC_M1_BASE+0x31E0)
#define REG_DDRC_M1_LPD4_DFS1_MR_0_CH0                                      (APB_DDRC_M1_BASE+0x3200)
#define REG_DDRC_M1_LPD4_DFS1_MR_1_CH0                                      (APB_DDRC_M1_BASE+0x3204)
#define REG_DDRC_M1_LPD4_DFS1_MR_2_CH0                                      (APB_DDRC_M1_BASE+0x3208)
#define REG_DDRC_M1_LPD4_DFS1_MR_3_CH0                                      (APB_DDRC_M1_BASE+0x320C)
#define REG_DDRC_M1_LPD4_DFS1_MR_4_CH0                                      (APB_DDRC_M1_BASE+0x3210)
#define REG_DDRC_M1_LPD4_DFS1_MR_5_CH0                                      (APB_DDRC_M1_BASE+0x3214)
#define REG_DDRC_M1_LPD4_DFS1_MR_6_CH0                                      (APB_DDRC_M1_BASE+0x3218)
#define REG_DDRC_M1_LPD4_DFS1_MR_0_CH1                                      (APB_DDRC_M1_BASE+0x3220)
#define REG_DDRC_M1_LPD4_DFS1_MR_1_CH1                                      (APB_DDRC_M1_BASE+0x3224)
#define REG_DDRC_M1_LPD4_DFS1_MR_2_CH1                                      (APB_DDRC_M1_BASE+0x3228)
#define REG_DDRC_M1_LPD4_DFS1_MR_3_CH1                                      (APB_DDRC_M1_BASE+0x322C)
#define REG_DDRC_M1_LPD4_DFS1_MR_4_CH1                                      (APB_DDRC_M1_BASE+0x3230)
#define REG_DDRC_M1_LPD4_DFS1_MR_5_CH1                                      (APB_DDRC_M1_BASE+0x3234)
#define REG_DDRC_M1_LPD4_DFS1_MR_6_CH1                                      (APB_DDRC_M1_BASE+0x3238)
#define REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_0                                    (APB_DDRC_M1_BASE+0x3240)
#define REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_1                                    (APB_DDRC_M1_BASE+0x3244)
#define REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_2                                    (APB_DDRC_M1_BASE+0x3248)
#define REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_3                                    (APB_DDRC_M1_BASE+0x324C)
#define REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_4                                    (APB_DDRC_M1_BASE+0x3250)
#define REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_5                                    (APB_DDRC_M1_BASE+0x3254)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_0                                (APB_DDRC_M1_BASE+0x3260)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_1                                (APB_DDRC_M1_BASE+0x3264)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_2                                (APB_DDRC_M1_BASE+0x3268)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_3                                (APB_DDRC_M1_BASE+0x326C)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_4                                (APB_DDRC_M1_BASE+0x3270)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_5                                (APB_DDRC_M1_BASE+0x3274)
#define REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_6                                (APB_DDRC_M1_BASE+0x3278)
#define REG_DDRC_M1_LPD4_DFS1_REF_CTRL                                      (APB_DDRC_M1_BASE+0x3290)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_0                                 (APB_DDRC_M1_BASE+0x32A0)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_1                                 (APB_DDRC_M1_BASE+0x32A4)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_2                                 (APB_DDRC_M1_BASE+0x32A8)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_3                                 (APB_DDRC_M1_BASE+0x32AC)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_4                                 (APB_DDRC_M1_BASE+0x32B0)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_5                                 (APB_DDRC_M1_BASE+0x32B4)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_6                                 (APB_DDRC_M1_BASE+0x32B8)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_7                                 (APB_DDRC_M1_BASE+0x32BC)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_8                                 (APB_DDRC_M1_BASE+0x32C0)
#define REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_9                                 (APB_DDRC_M1_BASE+0x32C4)
#define REG_DDRC_M1_LPD4_DFS1_PHY_IF                                        (APB_DDRC_M1_BASE+0x32E0)
#define REG_DDRC_M1_LPD4_DFS2_MR_0_CH0                                      (APB_DDRC_M1_BASE+0x3300)
#define REG_DDRC_M1_LPD4_DFS2_MR_1_CH0                                      (APB_DDRC_M1_BASE+0x3304)
#define REG_DDRC_M1_LPD4_DFS2_MR_2_CH0                                      (APB_DDRC_M1_BASE+0x3308)
#define REG_DDRC_M1_LPD4_DFS2_MR_3_CH0                                      (APB_DDRC_M1_BASE+0x330C)
#define REG_DDRC_M1_LPD4_DFS2_MR_4_CH0                                      (APB_DDRC_M1_BASE+0x3310)
#define REG_DDRC_M1_LPD4_DFS2_MR_5_CH0                                      (APB_DDRC_M1_BASE+0x3314)
#define REG_DDRC_M1_LPD4_DFS2_MR_6_CH0                                      (APB_DDRC_M1_BASE+0x3318)
#define REG_DDRC_M1_LPD4_DFS2_MR_0_CH1                                      (APB_DDRC_M1_BASE+0x3320)
#define REG_DDRC_M1_LPD4_DFS2_MR_1_CH1                                      (APB_DDRC_M1_BASE+0x3324)
#define REG_DDRC_M1_LPD4_DFS2_MR_2_CH1                                      (APB_DDRC_M1_BASE+0x3328)
#define REG_DDRC_M1_LPD4_DFS2_MR_3_CH1                                      (APB_DDRC_M1_BASE+0x332C)
#define REG_DDRC_M1_LPD4_DFS2_MR_4_CH1                                      (APB_DDRC_M1_BASE+0x3330)
#define REG_DDRC_M1_LPD4_DFS2_MR_5_CH1                                      (APB_DDRC_M1_BASE+0x3334)
#define REG_DDRC_M1_LPD4_DFS2_MR_6_CH1                                      (APB_DDRC_M1_BASE+0x3338)
#define REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_0                                    (APB_DDRC_M1_BASE+0x3340)
#define REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_1                                    (APB_DDRC_M1_BASE+0x3344)
#define REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_2                                    (APB_DDRC_M1_BASE+0x3348)
#define REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_3                                    (APB_DDRC_M1_BASE+0x334C)
#define REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_4                                    (APB_DDRC_M1_BASE+0x3350)
#define REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_5                                    (APB_DDRC_M1_BASE+0x3354)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_0                                (APB_DDRC_M1_BASE+0x3360)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_1                                (APB_DDRC_M1_BASE+0x3364)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_2                                (APB_DDRC_M1_BASE+0x3368)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_3                                (APB_DDRC_M1_BASE+0x336C)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_4                                (APB_DDRC_M1_BASE+0x3370)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_5                                (APB_DDRC_M1_BASE+0x3374)
#define REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_6                                (APB_DDRC_M1_BASE+0x3378)
#define REG_DDRC_M1_LPD4_DFS2_REF_CTRL                                      (APB_DDRC_M1_BASE+0x3390)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_0                                 (APB_DDRC_M1_BASE+0x33A0)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_1                                 (APB_DDRC_M1_BASE+0x33A4)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_2                                 (APB_DDRC_M1_BASE+0x33A8)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_3                                 (APB_DDRC_M1_BASE+0x33AC)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_4                                 (APB_DDRC_M1_BASE+0x33B0)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_5                                 (APB_DDRC_M1_BASE+0x33B4)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_6                                 (APB_DDRC_M1_BASE+0x33B8)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_7                                 (APB_DDRC_M1_BASE+0x33BC)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_8                                 (APB_DDRC_M1_BASE+0x33C0)
#define REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_9                                 (APB_DDRC_M1_BASE+0x33C4)
#define REG_DDRC_M1_LPD4_DFS2_PHY_IF                                        (APB_DDRC_M1_BASE+0x33E0)
#define REG_DDRC_M1_DEBUG_COMMON                                            (APB_DDRC_M1_BASE+0x5000)
#define REG_DDRC_M1_DEBUG_PERIOD                                            (APB_DDRC_M1_BASE+0x5004)
#define REG_DDRC_M1_IRQ_MASK                                                (APB_DDRC_M1_BASE+0x5010)
#define REG_DDRC_M1_IRQ_STATUS                                              (APB_DDRC_M1_BASE+0x5014)
#define REG_DDRC_M1_DEBUG_BUS_IF                                            (APB_DDRC_M1_BASE+0x5100)
#define REG_DDRC_M1_DEBUG_PORT_IF_0                                         (APB_DDRC_M1_BASE+0x5200)
#define REG_DDRC_M1_DEBUG_PORT_IF_1                                         (APB_DDRC_M1_BASE+0x5204)
#define REG_DDRC_M1_DEBUG_PORT_IF_2                                         (APB_DDRC_M1_BASE+0x5208)
#define REG_DDRC_M1_DEBUG_PORT_IF_3                                         (APB_DDRC_M1_BASE+0x520C)
#define REG_DDRC_M1_DEBUG_PORT_IF_4                                         (APB_DDRC_M1_BASE+0x5210)
#define REG_DDRC_M1_DEBUG_PORT_IF_5                                         (APB_DDRC_M1_BASE+0x5214)
#define REG_DDRC_M1_DEBUG_PORT_IF_6                                         (APB_DDRC_M1_BASE+0x5218)
#define REG_DDRC_M1_DEBUG_PORT_IF_7                                         (APB_DDRC_M1_BASE+0x521C)
#define REG_DDRC_M1_DEBUG_UQ_1                                              (APB_DDRC_M1_BASE+0x5300)
#define REG_DDRC_M1_DEBUG_UQ_2                                              (APB_DDRC_M1_BASE+0x5304)
#define REG_DDRC_M1_DEBUG_SCH0                                              (APB_DDRC_M1_BASE+0x5400)
#define REG_DDRC_M1_DEBUG_SCH1                                              (APB_DDRC_M1_BASE+0x5404)
#define REG_DDRC_M1_DEBUG_ALP                                               (APB_DDRC_M1_BASE+0x5500)
#define REG_DDRC_M1_DEBUG_ALP_ENTRY_NUM                                     (APB_DDRC_M1_BASE+0x5504)
#define REG_DDRC_M1_DEBUG_ALP_TIME                                          (APB_DDRC_M1_BASE+0x5508)
#define REG_DDRC_M1_DEBUG_ALP_WAIT_CNT                                      (APB_DDRC_M1_BASE+0x550C)
#define REG_DDRC_M1_DEBUG_DFS                                               (APB_DDRC_M1_BASE+0x5600)
#define REG_DDRC_M1_DEBUG_IDLE_CNT                                          (APB_DDRC_M1_BASE+0x5700)
#define REG_DDRC_M1_DEBUG_RD_CNT                                            (APB_DDRC_M1_BASE+0x5704)
#define REG_DDRC_M1_DEBUG_RDL_CNT                                           (APB_DDRC_M1_BASE+0x5708)
#define REG_DDRC_M1_DEBUG_RWR_CNT                                           (APB_DDRC_M1_BASE+0x5710)
#define REG_DDRC_M1_DEBUG_MWR_CNT                                           (APB_DDRC_M1_BASE+0x5714)
#define REG_DDRC_M1_DEBUG_WRL_CNT                                           (APB_DDRC_M1_BASE+0x5718)
#define REG_DDRC_M1_DEBUG_PRG_CNT                                           (APB_DDRC_M1_BASE+0x5720)
#define REG_DDRC_M1_DEBUG_REF_CNT                                           (APB_DDRC_M1_BASE+0x5724)
#define REG_DDRC_M1_DEBUG_ACT_CNT                                           (APB_DDRC_M1_BASE+0x5728)
#define REG_DDRC_M1_DEBUG_RW_SWC_CNT                                        (APB_DDRC_M1_BASE+0x572C)
#define REG_DDRC_M1_DEBUG_R_URG_SWC_CNT                                     (APB_DDRC_M1_BASE+0x5730)
#define REG_DDRC_M1_DEBUG_R_REQ_ROW_HIT_CNT                                 (APB_DDRC_M1_BASE+0x5734)
#define REG_DDRC_M1_DEBUG_R_REQ_HIT_CNT                                     (APB_DDRC_M1_BASE+0x5738)
#define REG_DDRC_M1_DEBUG_R_URG_ROW_HIT_CNT                                 (APB_DDRC_M1_BASE+0x573C)
#define REG_DDRC_M1_DEBUG_R_URG_HIT_CNT                                     (APB_DDRC_M1_BASE+0x5740)
#define REG_DDRC_M1_DEBUG_R_ROW_HIT_CNT                                     (APB_DDRC_M1_BASE+0x5744)
#define REG_DDRC_M1_DEBUG_R_LUCKY_HIT_CNT                                   (APB_DDRC_M1_BASE+0x5748)
#define REG_DDRC_M1_DEBUG_W_URG_SWC_CNT                                     (APB_DDRC_M1_BASE+0x5750)
#define REG_DDRC_M1_DEBUG_W_REQ_ROW_HIT_CNT                                 (APB_DDRC_M1_BASE+0x5754)
#define REG_DDRC_M1_DEBUG_W_REQ_HIT_CNT                                     (APB_DDRC_M1_BASE+0x5758)
#define REG_DDRC_M1_DEBUG_W_URG_ROW_HIT_CNT                                 (APB_DDRC_M1_BASE+0x575C)
#define REG_DDRC_M1_DEBUG_W_URG_HIT_CNT                                     (APB_DDRC_M1_BASE+0x5760)
#define REG_DDRC_M1_DEBUG_W_ROW_HIT_CNT                                     (APB_DDRC_M1_BASE+0x5764)
#define REG_DDRC_M1_DEBUG_W_LUCKY_HIT_CNT                                   (APB_DDRC_M1_BASE+0x5768)
#define REG_DDRC_M1_DEBUG_MAX_LAT_QOS                                       (APB_DDRC_M1_BASE+0x5770)
#define REG_DDRC_M1_DEBUG_R_HYB_SWC_CNT                                     (APB_DDRC_M1_BASE+0x5800)
#define REG_DDRC_M1_DEBUG_W_HYB_SWC_CNT                                     (APB_DDRC_M1_BASE+0x5804)
#define REG_DDRC_M1_DEBUG_R_FIFO_0_PRT_CNT                                  (APB_DDRC_M1_BASE+0x5900)
#define REG_DDRC_M1_DEBUG_R_FIFO_1_PRT_CNT                                  (APB_DDRC_M1_BASE+0x5904)
#define REG_DDRC_M1_DEBUG_R_FIFO_2_PRT_CNT                                  (APB_DDRC_M1_BASE+0x5908)
#define REG_DDRC_M1_DEBUG_R_FIFO_3_PRT_CNT                                  (APB_DDRC_M1_BASE+0x590C)
#define REG_DDRC_M1_DEBUG_W_FIFO_0_PRT_CNT                                  (APB_DDRC_M1_BASE+0x5910)
#define REG_DDRC_M1_DEBUG_W_FIFO_1_PRT_CNT                                  (APB_DDRC_M1_BASE+0x5914)
#define REG_DDRC_M1_DEBUG_W_FIFO_2_PRT_CNT                                  (APB_DDRC_M1_BASE+0x5918)
#define REG_DDRC_M1_DEBUG_W_FIFO_3_PRT_CNT                                  (APB_DDRC_M1_BASE+0x591C)
#define REG_DDRC_M1_DEBUG_LPD4_0                                            (APB_DDRC_M1_BASE+0x6000)
#define REG_DDRC_M1_DEBUG_LPD4_1                                            (APB_DDRC_M1_BASE+0x6004)
#define REG_DDRC_M1_DEBUG_LPD4_2                                            (APB_DDRC_M1_BASE+0x6008)
#define REG_DDRC_M1_DEBUG_LPD4_3                                            (APB_DDRC_M1_BASE+0x600C)
#define REG_DDRC_M1_DEBUG_LPD4_4                                            (APB_DDRC_M1_BASE+0x6010)
#define REG_DDRC_M1_DEBUG_LPD4_5                                            (APB_DDRC_M1_BASE+0x6014)
#define REG_DDRC_M1_DEBUG_LPD4_6                                            (APB_DDRC_M1_BASE+0x6018)
#define REG_DDRC_M1_DEBUG_LPD4_7                                            (APB_DDRC_M1_BASE+0x601C)
#define REG_DDRC_M1_DEBUG_LPD4_8                                            (APB_DDRC_M1_BASE+0x6020)
#define REG_DDRC_M1_DEBUG_LPD4_9                                            (APB_DDRC_M1_BASE+0x6024)
#define REG_DDRC_M1_DEBUG_LPD4_10                                           (APB_DDRC_M1_BASE+0x6028)
#define REG_DDRC_M1_DEBUG_LPD4_11                                           (APB_DDRC_M1_BASE+0x602C)
#define REG_DDRC_M1_DEBUG_LPD4_12                                           (APB_DDRC_M1_BASE+0x6030)
#define REG_DDRC_M1_DEBUG_LPD4_13                                           (APB_DDRC_M1_BASE+0x6034)
#define REG_DDRC_M1_DEBUG_LPD4_14                                           (APB_DDRC_M1_BASE+0x6038)
#define REG_DDRC_M1_DEBUG_LPD4_15                                           (APB_DDRC_M1_BASE+0x603C)
#define REG_DDRC_M1_DEBUG_LPD4_16                                           (APB_DDRC_M1_BASE+0x6040)
#define REG_DDRC_M1_DEBUG_LPD4_MR_0                                         (APB_DDRC_M1_BASE+0x6100)
#define REG_DDRC_M1_DEBUG_LPD4_MR_1                                         (APB_DDRC_M1_BASE+0x6104)
#define REG_DDRC_M1_DEBUG_LPD4_MR_2                                         (APB_DDRC_M1_BASE+0x6108)
#define REG_DDRC_M1_DEBUG_LPD4_MR_3                                         (APB_DDRC_M1_BASE+0x610C)
#define REG_DDRC_M1_DEBUG_LPD4_MR_4                                         (APB_DDRC_M1_BASE+0x6110)
#define REG_DDRC_M1_DEBUG_LPD4_MR_5                                         (APB_DDRC_M1_BASE+0x6114)
#define REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_0                                   (APB_DDRC_M1_BASE+0x6118)
#define REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_1                                   (APB_DDRC_M1_BASE+0x611C)
#define REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_2                                   (APB_DDRC_M1_BASE+0x6120)
#define REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_3                                   (APB_DDRC_M1_BASE+0x6124)
#define REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_4                                   (APB_DDRC_M1_BASE+0x6128)
#define REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_5                                   (APB_DDRC_M1_BASE+0x612C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MRW1                                     (APB_DDRC_M1_BASE+0x6200)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MRW0                                     (APB_DDRC_M1_BASE+0x6204)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_LP_EXIT                                  (APB_DDRC_M1_BASE+0x6208)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_LP_ENTRY                                 (APB_DDRC_M1_BASE+0x620C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_SR_PD_EXIT                               (APB_DDRC_M1_BASE+0x6210)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_SR_PD_ENTRY                              (APB_DDRC_M1_BASE+0x6214)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_SR_EXIT                                  (APB_DDRC_M1_BASE+0x6218)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_SR_ENTRY                                 (APB_DDRC_M1_BASE+0x621C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PD_EXIT                                  (APB_DDRC_M1_BASE+0x6220)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PD_ENTRY                                 (APB_DDRC_M1_BASE+0x6224)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ZQLAT                                    (APB_DDRC_M1_BASE+0x6228)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ZQCAL                                    (APB_DDRC_M1_BASE+0x622C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_CKE1                                     (APB_DDRC_M1_BASE+0x6230)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_CKE0                                     (APB_DDRC_M1_BASE+0x6234)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RSTN1                                    (APB_DDRC_M1_BASE+0x6238)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RSTN0                                    (APB_DDRC_M1_BASE+0x623C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD0                                      (APB_DDRC_M1_BASE+0x6240)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD1                                      (APB_DDRC_M1_BASE+0x6244)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD2                                      (APB_DDRC_M1_BASE+0x6248)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD3                                      (APB_DDRC_M1_BASE+0x624C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD4                                      (APB_DDRC_M1_BASE+0x6250)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD5                                      (APB_DDRC_M1_BASE+0x6254)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD6                                      (APB_DDRC_M1_BASE+0x6258)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_RD7                                      (APB_DDRC_M1_BASE+0x625C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR0                                     (APB_DDRC_M1_BASE+0x6260)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR1                                     (APB_DDRC_M1_BASE+0x6264)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR2                                     (APB_DDRC_M1_BASE+0x6268)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR3                                     (APB_DDRC_M1_BASE+0x626C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR4                                     (APB_DDRC_M1_BASE+0x6270)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR5                                     (APB_DDRC_M1_BASE+0x6274)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR6                                     (APB_DDRC_M1_BASE+0x6278)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MWR7                                     (APB_DDRC_M1_BASE+0x627C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR0                                      (APB_DDRC_M1_BASE+0x6280)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR1                                      (APB_DDRC_M1_BASE+0x6284)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR2                                      (APB_DDRC_M1_BASE+0x6288)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR3                                      (APB_DDRC_M1_BASE+0x628C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR4                                      (APB_DDRC_M1_BASE+0x6290)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR5                                      (APB_DDRC_M1_BASE+0x6294)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR6                                      (APB_DDRC_M1_BASE+0x6298)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_WR7                                      (APB_DDRC_M1_BASE+0x629C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT0                                     (APB_DDRC_M1_BASE+0x62A0)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT1                                     (APB_DDRC_M1_BASE+0x62A4)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT2                                     (APB_DDRC_M1_BASE+0x62A8)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT3                                     (APB_DDRC_M1_BASE+0x62AC)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT4                                     (APB_DDRC_M1_BASE+0x62B0)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT5                                     (APB_DDRC_M1_BASE+0x62B4)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT6                                     (APB_DDRC_M1_BASE+0x62B8)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_ACT7                                     (APB_DDRC_M1_BASE+0x62BC)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB0                                  (APB_DDRC_M1_BASE+0x6300)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB1                                  (APB_DDRC_M1_BASE+0x6304)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB2                                  (APB_DDRC_M1_BASE+0x6308)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB3                                  (APB_DDRC_M1_BASE+0x630C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB4                                  (APB_DDRC_M1_BASE+0x6310)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB5                                  (APB_DDRC_M1_BASE+0x6314)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB6                                  (APB_DDRC_M1_BASE+0x6318)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB7                                  (APB_DDRC_M1_BASE+0x631C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB0                                  (APB_DDRC_M1_BASE+0x6320)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB1                                  (APB_DDRC_M1_BASE+0x6324)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB2                                  (APB_DDRC_M1_BASE+0x6328)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB3                                  (APB_DDRC_M1_BASE+0x632C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB4                                  (APB_DDRC_M1_BASE+0x6330)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB5                                  (APB_DDRC_M1_BASE+0x6334)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB6                                  (APB_DDRC_M1_BASE+0x6338)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB7                                  (APB_DDRC_M1_BASE+0x633C)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_CG_REF_AB                                (APB_DDRC_M1_BASE+0x6340)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MF_REF_AB                                (APB_DDRC_M1_BASE+0x6344)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_CG_PRG_AB                                (APB_DDRC_M1_BASE+0x6350)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_MF_PRG_AB                                (APB_DDRC_M1_BASE+0x6354)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_CG_BL                                    (APB_DDRC_M1_BASE+0x6360)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_CG_AP                                    (APB_DDRC_M1_BASE+0x6364)
#define REG_DDRC_M1_DEBUG_CTRL_CMD_REF_CYCLE                                (APB_DDRC_M1_BASE+0x6368)
#define REG_DDRC_M1_DEBUG_DFI                                               (APB_DDRC_M1_BASE+0x6700)
#define REG_DDRC_M1_DRAM_BIST_CTRL_0                                        (APB_DDRC_M1_BASE+0x6800)
#define REG_DDRC_M1_DRAM_BIST_CTRL_1                                        (APB_DDRC_M1_BASE+0x6804)
#define REG_DDRC_M1_DRAM_BIST_CTRL_2                                        (APB_DDRC_M1_BASE+0x6808)
#define REG_DDRC_M1_DRAM_BIST_DATA_0                                        (APB_DDRC_M1_BASE+0x680C)
#define REG_DDRC_M1_DRAM_BIST_DATA_1                                        (APB_DDRC_M1_BASE+0x6810)
#define REG_DDRC_M1_DRAM_BIST_DATA_2                                        (APB_DDRC_M1_BASE+0x6814)
#define REG_DDRC_M1_DRAM_BIST_ADDR_0                                        (APB_DDRC_M1_BASE+0x6818)
#define REG_DDRC_M1_DRAM_BIST_ADDR_1                                        (APB_DDRC_M1_BASE+0x681C)
#define REG_DDRC_M1_DRAM_BIST_ADDR_2                                        (APB_DDRC_M1_BASE+0x6820)
#define REG_DDRC_M1_DRAM_BIST_OPCMD_0                                       (APB_DDRC_M1_BASE+0x6824)
#define REG_DDRC_M1_DRAM_BIST_OPCMD_1                                       (APB_DDRC_M1_BASE+0x6828)
#define REG_DDRC_M1_DRAM_BIST_OPCMD_2                                       (APB_DDRC_M1_BASE+0x682C)
#define REG_DDRC_M1_DRAM_BIST_OPCMD_3                                       (APB_DDRC_M1_BASE+0x6830)
#define REG_DDRC_M1_DRAM_BIST_ERR_ADDR_INFO                                 (APB_DDRC_M1_BASE+0x6834)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_00                              (APB_DDRC_M1_BASE+0x6838)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_01                              (APB_DDRC_M1_BASE+0x683C)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_02                              (APB_DDRC_M1_BASE+0x6840)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_03                              (APB_DDRC_M1_BASE+0x6844)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_04                              (APB_DDRC_M1_BASE+0x6848)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_05                              (APB_DDRC_M1_BASE+0x684C)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_06                              (APB_DDRC_M1_BASE+0x6850)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_07                              (APB_DDRC_M1_BASE+0x6854)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_08                              (APB_DDRC_M1_BASE+0x6858)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_09                              (APB_DDRC_M1_BASE+0x685C)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_10                              (APB_DDRC_M1_BASE+0x6860)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_11                              (APB_DDRC_M1_BASE+0x6864)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_12                              (APB_DDRC_M1_BASE+0x6868)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_13                              (APB_DDRC_M1_BASE+0x686C)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_14                              (APB_DDRC_M1_BASE+0x6870)
#define REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_15                              (APB_DDRC_M1_BASE+0x6874)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_00                              (APB_DDRC_M1_BASE+0x6878)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_01                              (APB_DDRC_M1_BASE+0x687C)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_02                              (APB_DDRC_M1_BASE+0x6880)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_03                              (APB_DDRC_M1_BASE+0x6884)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_04                              (APB_DDRC_M1_BASE+0x6888)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_05                              (APB_DDRC_M1_BASE+0x688C)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_06                              (APB_DDRC_M1_BASE+0x6890)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_07                              (APB_DDRC_M1_BASE+0x6894)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_08                              (APB_DDRC_M1_BASE+0x6898)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_09                              (APB_DDRC_M1_BASE+0x689C)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_10                              (APB_DDRC_M1_BASE+0x68A0)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_11                              (APB_DDRC_M1_BASE+0x68A4)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_12                              (APB_DDRC_M1_BASE+0x68A8)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_13                              (APB_DDRC_M1_BASE+0x68AC)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_14                              (APB_DDRC_M1_BASE+0x68B0)
#define REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_15                              (APB_DDRC_M1_BASE+0x68B4)
#define REG_DDRC_M1_REY_SPARE                                               (APB_DDRC_M1_BASE+0x6FE0)

typedef union {
	UINT32 udata32;
	struct {						//0xC4900000 RW
	UINT32 reg_dram_ch                      :1;	//0 //Dram channel width (0: x16, 1: x32)
	UINT32 resvd0                           :3;  
	UINT32 reg_byte_mode                    :1;	//4 //Byte mode enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M1_DRAM_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900004 RW
	UINT32 reg_op_mode                      :1;	//0 //operation mode selection (0: normal, 1: debug)
	UINT32 reg_bist_en                      :1;	//1 //bist mode enable
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M1_MODE_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900008 RW
	UINT32 reg_base_period                  :10;	//9:0	//base period for counter (counter resolution) - ex: 1us
	UINT32 resvd                            :22; 
	};
}REG_DDRC_M1_BASE_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900100 RW
	UINT32 reg_alp_en                       :2;	//1:0	//low power mode enable 	 ([0]: power down, [1]: self refresh)
	UINT32 resvd0                           :2;  
	UINT32 reg_pd_thr                       :4;	//7:4	//power down threshold - waiting for 4*(x+1) cycles
	UINT32 reg_sr_thr                       :4;	//11:8	//self refresh threshold - waiting for tREFI*(x+1) cycles
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M1_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900104 RW
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
}REG_DDRC_M1_CGL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900108 RO
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
}REG_DDRC_M1_CGL_MON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900200 RW
	UINT32 reg_pm_en                        :1;	//0 //performance monitor enable
	UINT32 resvd0                           :3;  
	UINT32 reg_emg_period                   :10;	//13:4	//emergency dfs monitoring period (ex: 100us) - (reg_base_period+1 (ex:1us)) * (reg_emg_period+1) : (final default value 0x63 --> 100ms)
	UINT32 resvd1                           :18; 
	};
}REG_DDRC_M1_PERFMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900204 RO
	UINT32 reg_emg_max                      :12;	//11:0	//max value among dfs_emg_totals during debug monitoring period : emg_total >> cut_width	(max of served bytes during emg period in debug monitoring period can be calculated by reg_emg_max * 16 << cut_width)	- cut_width : reg_emg_period[9]? 10 : 	                  reg_emg_period[8]?  9 :	                   reg_emg_period[7]?  8 :   	                   reg_emg_period[6]?  7 :	                   reg_emg_period[5]?  6 :	                   reg_emg_period[4]?  5 :   	                   reg_emg_period[3]?  4 :	                   reg_emg_period[2]?  3 :	                   reg_emg_period[1]?  2 :   	                      reg_emg_period[0]?  1 : 0
	UINT32 resvd                            :20; 
	};
}REG_DDRC_M1_PERFMON_EMG_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900210 RO
	UINT32 reg_pm_w0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_W0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900214 RO
	UINT32 reg_pm_w1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_W1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900218 RO
	UINT32 reg_pm_w2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_W2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490021C RO
	UINT32 reg_pm_w3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_W3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900220 RO
	UINT32 reg_pm_r0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_R0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900224 RO
	UINT32 reg_pm_r1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_R1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900228 RO
	UINT32 reg_pm_r2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_R2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490022C RO
	UINT32 reg_pm_r3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M1_PERFMON_R3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900230 
	UINT32 reg_max_lat_en                   :1;	//0 //max latency monitor enable
	UINT32 resvd0                           :7;  
	UINT32 reg_max_lat                      :8;	//15:8	//max latency for read request in unified Q (it is reset at every period)
	UINT32 resvd1                           :16; 
	};
}REG_DDRC_M1_LATMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900300 RW
	UINT32 reg_dfs_en                       :1;	//0 //normal dfs enable
	UINT32 reg_dfs_emg_en                   :1;	//1 //emergency dfs enable
	UINT32 reg_dfs_mask_en                  :1;	//2 //dfs mask enable by external blocking	- dfs is masked when asserting external blocking signal
	UINT32 reg_dfs_do                       :1;	//3 //user driven dfs start
	UINT32 resvd0                           :4;  
	UINT32 reg_dfs_block_period             :8;	//15:8	//dfs blocking period after completing dfs done : (reg_dfs_block_period+1)*0x100
	UINT32 reg_dfs_emg_thr                  :12;	//27:16	//emergency dfs threshold : it can be determined like as ((reg_base_period+1)*(reg_emg_period+1))*12.8G/(1s*16*2^cut_width))*80%)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900304 RO
	UINT32 reg_dfs_done                     :1;	//0 //dfs done
	UINT32 resvd0                           :3;  
	UINT32 reg_dfs_type                     :2;	//5:4	//dfs type: DFS0, DFS1, DFS2 (emergency DFS exit)
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M1_DFS_RESULT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900400 RW
	UINT32 reg_dram_density                 :3;	//2:0	//dram density configuration per channel 	(enum {2Gb, 3Gb, 4Gb, 6Gb, 8Gb, 12Gb, 16Gb})
	UINT32 reg_addr_scrb_en                 :1;	//3 //address map: bank scramble enable
	UINT32 reg_addr_sel_bq                  :4;	//7:4	//address map: bank position	(enum {BG4, BG5, BG6, BG7, BP4, BP5, BP6, BP7, BP8, BP9, BP11, BP12})
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_ADDR_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900404 RW
	UINT32 reg_fast_en                      :1;	//0 //fast b valid enable
	UINT32 reg_ooo_en                       :1;	//1 //out of order enable
	UINT32 reg_lpd4_32bl_en                 :1;	//2 //lpddr4 long burst support
	UINT32 reg_exmon_en                     :1;	//3 //exclusive monitor enable
	UINT32 reg_errchk_en                    :1;	//4 //errore checker enable	 - 0: error checker disable	   - for out of range address, row address bits are truncated according to dram_density	     - 6Gb, 8Gb : row[16] = 1'b0	     - 3Gb, 4Gb : row[16:15] = 2'h0	     - 2Gb : row[16:14] = 3'h0	 - 1: error checker enable
	UINT32 reg_illegal_strb_mask_dis        :1;	//5 //illegal strb mask disable	      - '0 : mask illegal strb bits	      - '1 : disable illegal strb checker
	UINT32 resvd                            :26; 
	};
}REG_DDRC_M1_COMMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900408 
	UINT32 reg_rc4_enb                      :1;	//0 //data encryption enable
	UINT32 resvd0                           :7;  
	UINT32 reg_rc4_key_in_4                 :8;	//15:8	//key seed for data encryption (39:32 bits)
	UINT32 reg_rc4_state                    :2;	//17:16	//rc4 key generation status
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M1_DATA_ENC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490040C RW
	UINT32 reg_rc4_key_in_3_0               :32;	//31:0	//key seed for data encryption (31:0 bits)
	};
}REG_DDRC_M1_DATA_ENC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900500 RW
	UINT32 reg_sameid_urg_en                :1;	//0 //urgent arbitration enable for predecssor wth same id	 - if it is enabled, whenever sameid request served at cbuf, prt_tag of previous request with same id is incremented
	UINT32 reg_sameid_urg_wt                :3;	//3:1	//weight value to increase prt_tag when same id urgent occurs
	UINT32 reg_prt_en                       :3;	//6:4	//per-request timeout enable ([0]: cbuf, [1]: pq, [2]: bq)
	UINT32 resvd0                           :1;  
	UINT32 reg_prt_bq_thr                   :4;	//11:8	//threshold value of per-request timeout for bank Q
	UINT32 reg_prt_pq_thr                   :4;	//15:12	//threshold value of per-request timeout for port Q
	UINT32 reg_ep_period                    :10;	//25:16	//a period of epoch counter for per-request timeout
	UINT32 resvd1                           :6;  
	};
}REG_DDRC_M1_RD_URG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4900504 RW
	UINT32 reg_urg_en                       :1;	//0 //urgent enable for port Q and bank Q in write port	 - if a request is blocking others due to RAW or WAW, it becomes urgent one.
	UINT32 resvd0                           :3;  
	UINT32 reg_wr_prt_en                    :1;	//4 //per-request timeout enable for port Q and bank Q in write port	 - if a request is timed-out, it becomes urgent one
	UINT32 resvd1                           :3;  
	UINT32 reg_wr_prt_thr                   :4;	//11:8	//threshold value of per-request timeout for write port
	UINT32 resvd2                           :4;  
	UINT32 reg_wr_ep_period                 :10;	//25:16	//a period of epoch counter for per-request timeout
	UINT32 resvd3                           :6;  
	};
}REG_DDRC_M1_WR_URG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901000 RW
	UINT32 reg_awready_en                   :4;	//3:0	//enable awready for each port
	UINT32 reg_pre_wready_en                :1;	//4 //enable pre-wready
	UINT32 resvd0                           :3;  
	UINT32 reg_arready_en                   :4;	//11:8	//enable arready for each port
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M1_FIFO_RDY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901004 RO
	UINT32 reg_aw_all_empty                 :4;	//3:0	//monitor whether all aw valid entries is empty for each port
	UINT32 reg_ar_all_empty                 :4;	//7:4	//monitor whether all aw valid entries is empty for each port
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_FIFO_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901008 RW
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
}REG_DDRC_M1_FIFO_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901010 RW
	UINT32 reg_w_c_lim_en                   :4;	//3:0	//enable cmd cnt limiter
	UINT32 reg_w_d_lim_en                   :4;	//7:4	//enable data len limiter
	UINT32 reg_r_c_lim_en                   :4;	//11:8	//enable cmd cnt limiter
	UINT32 reg_r_d_lim_en                   :4;	//15:12	//enable data len limiter
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LIMITER_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901014 RW
	UINT32 reg_w_c_lim_thr0                 :5;	//4:0	//threshold value for cmd cnt limiter for write port 0
	UINT32 resvd0                           :3;  
	UINT32 reg_w_c_lim_thr1                 :5;	//12:8	//threshold value for cmd cnt limiter for write port 1
	UINT32 resvd1                           :3;  
	UINT32 reg_w_c_lim_thr2                 :5;	//20:16	//threshold value for cmd cnt limiter for write port 2
	UINT32 resvd2                           :3;  
	UINT32 reg_w_c_lim_thr3                 :5;	//28:24	//threshold value for cmd cnt limiter for write port 3
	UINT32 resvd3                           :3;  
	};
}REG_DDRC_M1_LIMITER_AW_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901018 RW
	UINT32 reg_w_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_w_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_w_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_w_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M1_LIMITER_W_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901024 RW
	UINT32 reg_r_c_lim_thr0                 :5;	//4:0	//threshold value for cmd cnt limiter for write port 0
	UINT32 resvd0                           :3;  
	UINT32 reg_r_c_lim_thr1                 :5;	//12:8	//threshold value for cmd cnt limiter for write port 1
	UINT32 resvd1                           :3;  
	UINT32 reg_r_c_lim_thr2                 :5;	//20:16	//threshold value for cmd cnt limiter for write port 2
	UINT32 resvd2                           :3;  
	UINT32 reg_r_c_lim_thr3                 :5;	//28:24	//threshold value for cmd cnt limiter for write port 3
	UINT32 resvd3                           :3;  
	};
}REG_DDRC_M1_LIMITER_AR_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901028 RW
	UINT32 reg_r_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_r_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_r_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_r_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M1_LIMITER_R_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901100 RW
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
}REG_DDRC_M1_FIFO_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901104 RW
	UINT32 reg_wfo_sol_max0                 :4;	//3:0	//The number of additionally continuous max serving requests for a write fifo 0
	UINT32 reg_wfo_sol_max1                 :4;	//7:4	//The number of additionally continuous max serving requests for a write fifo 1
	UINT32 reg_wfo_sol_max2                 :4;	//11:8	//The number of additionally continuous max serving requests for a write fifo 2
	UINT32 reg_wfo_sol_max3                 :4;	//15:12	//The number of additionally continuous max serving requests for a write fifo 3
	UINT32 reg_rfo_sol_max0                 :4;	//19:16	//The number of additionally continuous max serving requests for a read fifo 1
	UINT32 reg_rfo_sol_max1                 :4;	//23:20	//The number of additionally continuous max serving requests for a read fifo 1
	UINT32 reg_rfo_sol_max2                 :4;	//27:24	//The number of additionally continuous max serving requests for a read fifo 2
	UINT32 reg_rfo_sol_max3                 :4;	//31:28	//The number of additionally continuous max serving requests for a read fifo 3
	};
}REG_DDRC_M1_FIFO_MUX_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901108 RW
	UINT32 reg_wfo_prt_sol_max_en           :1;	//0 //write fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_wfo_prt_sol_max_thr          :4;	//7:4	//write fifo prt sol max threshold
	UINT32 reg_wfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for wfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M1_FIFO_MUX_WR_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490110C RW
	UINT32 reg_rfo_prt_sol_max_en           :1;	//0 //read fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_rfo_prt_sol_max_thr          :4;	//7:4	//read fifo prt sol max threshold
	UINT32 reg_rfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for rfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M1_FIFO_MUX_RD_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4901110 RW
	UINT32 reg_wfo_prt_sol_max0             :4;	//3:0	//The number of additionally continuous max serving requests for a write fifo 0 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max1             :4;	//7:4	//The number of additionally continuous max serving requests for a write fifo 1 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max2             :4;	//11:8	//The number of additionally continuous max serving requests for a write fifo 2 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max3             :4;	//15:12	//The number of additionally continuous max serving requests for a write fifo 3 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max0             :4;	//19:16	//The number of additionally continuous max serving requests for a read fifo 1 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max1             :4;	//23:20	//The number of additionally continuous max serving requests for a read fifo 1 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max2             :4;	//27:24	//The number of additionally continuous max serving requests for a read fifo 2 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max3             :4;	//31:28	//The number of additionally continuous max serving requests for a read fifo 3 in the case prt occurred
	};
}REG_DDRC_M1_FIFO_MUX_PRT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4902000 RW
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
}REG_DDRC_M1_PQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4902004 RW
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
}REG_DDRC_M1_BQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4902008 RW
	UINT32 reg_bq_rd_urg_stv_thr            :6;	//5:0	//ead starvation threshold when per request timeout hit is asserted  : 32*(x+1)
	UINT32 resvd0                           :2;  
	UINT32 reg_bq_wr_urg_stv_thr            :6;	//13:8	//write starvation threshold when urg hit is asserted : 32*(x+1)
	UINT32 resvd1                           :2;  
	UINT32 reg_bq_wr_stv_thr                :8;	//23:16	//write starvation threshold : 32*(x+1)
	UINT32 reg_bq_rd_stv_thr                :8;	//31:24	//read starvation threshold : 32*(x+1)
	};
}REG_DDRC_M1_BQ_RW_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490200C RW
	UINT32 reg_bq_hyb_stv_en                :1;	//0 //hybrid starvation enable
	UINT32 resvd0                           :3;  
	UINT32 reg_bq_hyb_stv_thr               :8;	//11:4	//hybrid starvation threshold : 32*(x+1)
	UINT32 resvd1                           :4;  
	UINT32 reg_bq_hyb_stv_cbuf_thr          :5;	//20:16	//cbuf threshold for hybrid starvation operation
	UINT32 resvd2                           :3;  
	UINT32 reg_bq_hyb_stv_dbuf_thr          :8;	//31:24	//dbuf threshold for hybrid starvation operation
	};
}REG_DDRC_M1_BQ_HYB_STV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903000 RW
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
}REG_DDRC_M1_LPD4_MAIN_FSM_INIT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903004 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp0        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP0 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_INIT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903008 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp1        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP1 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_INIT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490300C RW
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
}REG_DDRC_M1_LPD4_MAIN_FSM_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903010 
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
}REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903014 RW
	UINT32 lpd4_reg_dir_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903018 RW
	UINT32 lpd4_reg_dir_mrr_ma              :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490301C RW
	UINT32 lpd4_reg_dir_sr_mrw_ma           :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903020 RW
	UINT32 lpd4_reg_dir_sr_mrr_ma           :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903024 RW
	UINT32 lpd4_reg_dfs_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for DFS	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_DFS_MRW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903028 
	UINT32 lpd4_reg_dfi_ctrlupd_req         :1;	//0 //DFI control update request (This will be cleared when lpd4_mf_reg_dfi_ctrlupd_ack is asserted high)
	UINT32 lpd4_mf_reg_dfi_ctrlupd_ack      :1;	//1 //Completion of DFI control update request
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_CTRLUPD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490302C RW
	UINT32 lpd4_reg_mpc_fifo_en             :1;	//0 //Periodic MPC WR/RD FIFO command enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_mpc_fifo_cmd_cnt        :3;	//6:4	//Number of MPC FIFO commands issued at one time
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903030 RW
	UINT32 lpd4_reg_mpc_fifo_period         :32;	//31:0	//Period of MPC WR/RD FIFO command
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903034 RW
	UINT32 lpd4_reg_mpc_fifo_data0          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903038 RW
	UINT32 lpd4_reg_mpc_fifo_data1          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490303C RW
	UINT32 lpd4_reg_mpc_fifo_dmi0           :4;	//3:0	//DMI data pattern of MPC WR FIFO Command
	UINT32 lpd4_reg_mpc_fifo_dmi1           :4;	//7:4	//DMI data pattern of MPC WR FIFO Command
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903050 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_sel         :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-channel (x32)	- 2'b00 : CH0 or CH1	- 2'b01 : CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_sel        :2;	//5:4	//Refresh rate in MR4 selection between two-channel (x32)	- 2'b00 : Bigger value between CH0 and CH1	- 2'b01 : Smaller value between CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M1_LPD4_MR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903054 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_byte_sel    :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Byte0 or Byte1	- 2'b01 : Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_byte_sel   :2;	//5:4	//Refresh rate in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Bigger value between Byte0 and Byte1	- 2'b01 : Smaller value between Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M1_LPD4_MR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903058 RW
	UINT32 lpd4_reg_mrr_byte_sel            :1;	//0 //MR selection between two-byte (x16) in byte-mode	- 1'b0 : Byte0	- 1'b1 : Byte1
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_LPD4_MR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903060 RW
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
}REG_DDRC_M1_LPD4_REF_REQ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903070 RW
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
}REG_DDRC_M1_LPD4_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903080 RW
	UINT32 lpd4_reg_bank_lock_wait          :8;	//7:0	//Configurable locking time for BANK FSM operation
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_LPD4_BANK_FSM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49030A0 RW
	UINT32 lpd4_reg_tBL                     :8;	//7:0	//Additional offset of AC timing parameters when applying BL32
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_LPD4_BANK_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49030C0 RW
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
}REG_DDRC_M1_LPD4_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903100 RW
	UINT32 lpd4_reg_mr1_ch0_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS0_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903104 RW
	UINT32 lpd4_reg_mr9_ch0_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903108 RW
	UINT32 lpd4_reg_mr12_ch0_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS0_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490310C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903110 RW
	UINT32 lpd4_reg_mr15_ch0_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS0_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903114 RW
	UINT32 lpd4_reg_mr21_ch0_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS0_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903118 RW
	UINT32 lpd4_reg_mr31_ch0_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS0_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903120 RW
	UINT32 lpd4_reg_mr1_ch1_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS0_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903124 RW
	UINT32 lpd4_reg_mr9_ch1_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903128 RW
	UINT32 lpd4_reg_mr12_ch1_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS0_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490312C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903130 RW
	UINT32 lpd4_reg_mr15_ch1_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS0_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903134 RW
	UINT32 lpd4_reg_mr21_ch1_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS0_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903138 RW
	UINT32 lpd4_reg_mr31_ch1_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS0_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903140 RW
	UINT32 lpd4_reg_period_zq_req_dfs0      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903144 RW
	UINT32 lpd4_reg_tINIT1_dfs0             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs0             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903148 RW
	UINT32 lpd4_reg_tINIT5_dfs0             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs0             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs0             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490314C RW
	UINT32 lpd4_reg_tXP_dfs0                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs0             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs0            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs0            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903150 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs0           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903154 RW
	UINT32 lpd4_reg_tXSR_dfs0               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs0         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903160 RW
	UINT32 lpd4_reg_tREFI_dfs0              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs0           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903164 RW
	UINT32 lpd4_reg_tMRR4I_dfs0             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903168 RW
	UINT32 lpd4_reg_tRRD_dfs0               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs0           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs0           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs0               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490316C RW
	UINT32 lpd4_reg_tRAS_dfs0               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs0              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs0              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs0               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903170 RW
	UINT32 lpd4_reg_tRAP_dfs0               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs0        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs0    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs0    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903174 RW
	UINT32 lpd4_reg_tRCD_derate_dfs0        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs0        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs0       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs0       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903178 RW
	UINT32 lpd4_reg_tWAP_derate_dfs0        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs0        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903190 RW
	UINT32 lpd4_reg_ref_ab_en_dfs0          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs0          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M1_LPD4_DFS0_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031A0 RW
	UINT32 lpd4_reg_odt_on_dfs0             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031A4 RW
	UINT32 lpd4_reg_tCCD_dfs0               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs0             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs0               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs0               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031A8 RW
	UINT32 lpd4_reg_tW2PD_dfs0              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs0             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs0           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs0         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs0        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs0               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs0              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs0             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs0           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs0               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031B4 RW
	UINT32 lpd4_reg_tRFCab_dfs0             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs0             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031B8 RW
	UINT32 lpd4_reg_tMRW_dfs0               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs0           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs0       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs0      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031BC RW
	UINT32 lpd4_reg_tFC_dfs0                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs0           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs0               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs0              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs0            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs0             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs0             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs0           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49031E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs0             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs0            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs0             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS0_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903200 RW
	UINT32 lpd4_reg_mr1_ch0_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS1_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903204 RW
	UINT32 lpd4_reg_mr9_ch0_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903208 RW
	UINT32 lpd4_reg_mr12_ch0_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS1_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490320C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903210 RW
	UINT32 lpd4_reg_mr15_ch0_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS1_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903214 RW
	UINT32 lpd4_reg_mr21_ch0_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS1_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903218 RW
	UINT32 lpd4_reg_mr31_ch0_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS1_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903220 RW
	UINT32 lpd4_reg_mr1_ch1_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS1_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903224 RW
	UINT32 lpd4_reg_mr9_ch1_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903228 RW
	UINT32 lpd4_reg_mr12_ch1_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS1_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490322C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903230 RW
	UINT32 lpd4_reg_mr15_ch1_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS1_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903234 RW
	UINT32 lpd4_reg_mr21_ch1_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS1_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903238 RW
	UINT32 lpd4_reg_mr31_ch1_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS1_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903240 RW
	UINT32 lpd4_reg_period_zq_req_dfs1      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903244 RW
	UINT32 lpd4_reg_tINIT1_dfs1             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs1             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903248 RW
	UINT32 lpd4_reg_tINIT5_dfs1             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs1             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs1             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490324C RW
	UINT32 lpd4_reg_tXP_dfs1                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs1             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs1            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs1            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903250 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs1           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903254 RW
	UINT32 lpd4_reg_tXSR_dfs1               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs1         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903260 RW
	UINT32 lpd4_reg_tREFI_dfs1              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs1           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903264 RW
	UINT32 lpd4_reg_tMRR4I_dfs1             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903268 RW
	UINT32 lpd4_reg_tRRD_dfs1               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs1           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs1           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs1               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490326C RW
	UINT32 lpd4_reg_tRAS_dfs1               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs1              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs1              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs1               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903270 RW
	UINT32 lpd4_reg_tRAP_dfs1               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs1        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs1    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs1    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903274 RW
	UINT32 lpd4_reg_tRCD_derate_dfs1        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs1        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs1       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs1       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903278 RW
	UINT32 lpd4_reg_tWAP_derate_dfs1        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs1        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903290 RW
	UINT32 lpd4_reg_ref_ab_en_dfs1          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs1          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M1_LPD4_DFS1_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032A0 RW
	UINT32 lpd4_reg_odt_on_dfs1             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032A4 RW
	UINT32 lpd4_reg_tCCD_dfs1               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs1             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs1               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs1               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032A8 RW
	UINT32 lpd4_reg_tW2PD_dfs1              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs1             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs1           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs1         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs1        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs1               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs1              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs1             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs1           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs1               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032B4 RW
	UINT32 lpd4_reg_tRFCab_dfs1             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs1             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032B8 RW
	UINT32 lpd4_reg_tMRW_dfs1               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs1           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs1       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs1      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032BC RW
	UINT32 lpd4_reg_tFC_dfs1                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs1           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs1               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs1              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs1            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs1             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs1             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs1           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49032E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs1             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs1            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs1             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS1_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903300 RW
	UINT32 lpd4_reg_mr1_ch0_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS2_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903304 RW
	UINT32 lpd4_reg_mr9_ch0_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903308 RW
	UINT32 lpd4_reg_mr12_ch0_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS2_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490330C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903310 RW
	UINT32 lpd4_reg_mr15_ch0_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS2_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903314 RW
	UINT32 lpd4_reg_mr21_ch0_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS2_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903318 RW
	UINT32 lpd4_reg_mr31_ch0_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M1_LPD4_DFS2_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903320 RW
	UINT32 lpd4_reg_mr1_ch1_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS2_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903324 RW
	UINT32 lpd4_reg_mr9_ch1_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903328 RW
	UINT32 lpd4_reg_mr12_ch1_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS2_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490332C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903330 RW
	UINT32 lpd4_reg_mr15_ch1_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS2_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903334 RW
	UINT32 lpd4_reg_mr21_ch1_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS2_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903338 RW
	UINT32 lpd4_reg_mr31_ch1_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M1_LPD4_DFS2_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903340 RW
	UINT32 lpd4_reg_period_zq_req_dfs2      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903344 RW
	UINT32 lpd4_reg_tINIT1_dfs2             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs2             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903348 RW
	UINT32 lpd4_reg_tINIT5_dfs2             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs2             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs2             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490334C RW
	UINT32 lpd4_reg_tXP_dfs2                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs2             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs2            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs2            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903350 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs2           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903354 RW
	UINT32 lpd4_reg_tXSR_dfs2               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs2         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903360 RW
	UINT32 lpd4_reg_tREFI_dfs2              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs2           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903364 RW
	UINT32 lpd4_reg_tMRR4I_dfs2             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903368 RW
	UINT32 lpd4_reg_tRRD_dfs2               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs2           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs2           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs2               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490336C RW
	UINT32 lpd4_reg_tRAS_dfs2               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs2              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs2              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs2               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903370 RW
	UINT32 lpd4_reg_tRAP_dfs2               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs2        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs2    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs2    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903374 RW
	UINT32 lpd4_reg_tRCD_derate_dfs2        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs2        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs2       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs2       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903378 RW
	UINT32 lpd4_reg_tWAP_derate_dfs2        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs2        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4903390 RW
	UINT32 lpd4_reg_ref_ab_en_dfs2          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs2          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M1_LPD4_DFS2_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033A0 RW
	UINT32 lpd4_reg_odt_on_dfs2             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033A4 RW
	UINT32 lpd4_reg_tCCD_dfs2               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs2             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs2               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs2               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033A8 RW
	UINT32 lpd4_reg_tW2PD_dfs2              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs2             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs2           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs2         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs2        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs2               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs2              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs2             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs2           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs2               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033B4 RW
	UINT32 lpd4_reg_tRFCab_dfs2             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs2             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033B8 RW
	UINT32 lpd4_reg_tMRW_dfs2               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs2           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs2       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs2      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033BC RW
	UINT32 lpd4_reg_tFC_dfs2                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs2           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs2               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs2              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs2            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs2             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs2             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs2           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49033E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs2             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs2            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs2             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M1_LPD4_DFS2_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905000 RO
	UINT32 reg_dram_init_done               :1;	//0 //DRAM initialization done
	UINT32 reg_rey_idle                     :1;	//1 //Rey idle
	UINT32 resvd0                           :2;  
	UINT32 reg_init_set                     :1;	//4 //debug mode or before dram initialization
	UINT32 reg_set                          :1;	//5 //debug mode or rey idle
	UINT32 reg_alp_ready                    :1;	//6 //ALP READY state
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M1_DEBUG_COMMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905004 RW
	UINT32 reg_debug_mon_period             :20;	//19:0	//debug monitoring period (ex: 100ms) - (reg_base_period+1) * (reg_debug_mon_period+1)
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905010 RW
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
}REG_DDRC_M1_IRQ_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905014 RO
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
}REG_DDRC_M1_IRQ_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905100 RO
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
}REG_DDRC_M1_DEBUG_BUS_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905200 RO
	UINT32 reg_aw_err_0                     :4;	//3:0	//AXI AW Request ERR flag in port0
	UINT32 reg_aw_err_1                     :4;	//7:4	//AXI AW Request ERR flag in port1
	UINT32 reg_aw_err_2                     :4;	//11:8	//AXI AW Request ERR flag in port2
	UINT32 reg_aw_err_3                     :4;	//15:12	//AXI AW Request ERR flag in port3
	UINT32 reg_ar_err_0                     :4;	//19:16	//AXI AR Request ERR flag in port0
	UINT32 reg_ar_err_1                     :4;	//23:20	//AXI AR Request ERR flag in port1
	UINT32 reg_ar_err_2                     :4;	//27:24	//AXI AR Request ERR flag in port2
	UINT32 reg_ar_err_3                     :4;	//31:28	//AXI AR Request ERR flag in port3
	};
}REG_DDRC_M1_DEBUG_PORT_IF_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905204 RW
	UINT32 reg_port_cmd_mon_en              :1;	//0 //AXI  Request capture en in wfo/rfo
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_DEBUG_PORT_IF_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905208 RO
	UINT32 reg_ar_err_id                    :18;	//17:0	//AXI AR Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M1_DEBUG_PORT_IF_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490520C RO
	UINT32 reg_ar_err_addr                  :32;	//31:0	//AXI AR Request ERR or Last Request's addr
	};
}REG_DDRC_M1_DEBUG_PORT_IF_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905210 RO
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
}REG_DDRC_M1_DEBUG_PORT_IF_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905214 RO
	UINT32 reg_aw_err_id                    :18;	//17:0	//AXI AW Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M1_DEBUG_PORT_IF_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905218 RO
	UINT32 reg_aw_err_addr                  :32;	//31:0	//AXI AW Request ERR or Last Request's addr
	};
}REG_DDRC_M1_DEBUG_PORT_IF_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490521C RO
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
}REG_DDRC_M1_DEBUG_PORT_IF_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905300 RO
	UINT32 reg_debug_wuq_valid              :1;	//0 //wuq to sch valid signal probe
	UINT32 reg_debug_wuq_ready              :1;	//1 //wuq to sch ready signal probe
	UINT32 reg_debug_ruq_valid              :1;	//2 //ruq to sch valid signal probe
	UINT32 reg_debug_ruq_ready              :1;	//3 //ruq to sch ready signal probe
	UINT32 resvd                            :28; 
	};
}REG_DDRC_M1_DEBUG_UQ_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905304 RO
	UINT32 reg_debug_wuq_c_cnt              :6;	//5:0	//wuq data queue pending cnt
	UINT32 resvd0                           :10; 
	UINT32 reg_debug_wuq_d_cnt              :9;	//24:16	//wuq command queue pending cnt
	UINT32 resvd1                           :7;  
	};
}REG_DDRC_M1_DEBUG_UQ_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905400 RO
	UINT32 reg_debug_prg_rdy                :8;	//7:0	//precharge ready signal probe per each bank
	UINT32 reg_debug_act_rdy                :8;	//15:8	//activate ready signal probe per each bank
	UINT32 reg_debug_wr_rdy                 :8;	//23:16	//write ready signal probe per each bank
	UINT32 reg_debug_mwr_rdy                :8;	//31:24	//masked write ready signal probe per each bank
	};
}REG_DDRC_M1_DEBUG_SCH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905404 RO
	UINT32 reg_debug_rd_rdy                 :8;	//7:0	//read ready signal probe per each bank
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_DEBUG_SCH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905500 RO
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
}REG_DDRC_M1_DEBUG_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905504 RO
	UINT32 reg_debug_pd_cnt                 :16;	//15:0	//the number of power down entry during monitor period
	UINT32 reg_debug_sr_cnt                 :16;	//31:16	//the number of self refresh entry during monitor period
	};
}REG_DDRC_M1_DEBUG_ALP_ENTRY_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905508 RO
	UINT32 reg_debug_pd_time                :16;	//15:0	//total time of power down stay during monitor period
	UINT32 reg_debug_sr_time                :16;	//31:16	//total time of self refresh stay during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M1_DEBUG_ALP_TIME_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490550C RO
	UINT32 reg_debug_pd_std_cnt             :8;	//7:0	//max value of power down entry waiting counter during monitor period
	UINT32 reg_debug_sr_std_cnt             :8;	//15:8	//max value of self refresh entry waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	UINT32 reg_debug_pd_ex_std_cnt          :8;	//23:16	//max value of power down exit waiting counter during monitor period
	UINT32 reg_debug_sr_ex_std_cnt          :8;	//31:24	//max value of self refresh exit waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M1_DEBUG_ALP_WAIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905600 RO
	UINT32 reg_debug_dfs_state              :3;	//2:0	//dfs status
	UINT32 resvd                            :29; 
	};
}REG_DDRC_M1_DEBUG_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905700 RO
	UINT32 reg_debug_nidle                  :32;	//31:0	//number of idle cycle
	};
}REG_DDRC_M1_DEBUG_IDLE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905704 RO
	UINT32 reg_debug_nrd                    :32;	//31:0	//number of short read commands
	};
}REG_DDRC_M1_DEBUG_RD_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905708 RO
	UINT32 reg_debug_nrdl                   :32;	//31:0	//number of long read commands
	};
}REG_DDRC_M1_DEBUG_RDL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905710 RO
	UINT32 reg_debug_nwr                    :32;	//31:0	//number of short write commands
	};
}REG_DDRC_M1_DEBUG_RWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905714 RO
	UINT32 reg_debug_nmwr                   :32;	//31:0	//number of short masked write commands
	};
}REG_DDRC_M1_DEBUG_MWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905718 RO
	UINT32 reg_debug_nwrl                   :32;	//31:0	//number of long write commands
	};
}REG_DDRC_M1_DEBUG_WRL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905720 RO
	UINT32 reg_debug_nap                    :20;	//19:0	//number of AP commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_PRG_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905724 RO
	UINT32 reg_debug_nref                   :20;	//19:0	//number of all bank refresh commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_REF_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905728 RO
	UINT32 reg_debug_nact                   :32;	//31:0	//number of act commands
	};
}REG_DDRC_M1_DEBUG_ACT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490572C RO
	UINT32 reg_debug_nrw_swc                :32;	//31:0	//number of read/write command swich
	};
}REG_DDRC_M1_DEBUG_RW_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905730 RO
	UINT32 reg_debug_nr_urg_swc             :32;	//31:0	//number of urgent read command swich
	};
}REG_DDRC_M1_DEBUG_R_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905734 RO
	UINT32 reg_debug_nr_req_row_hit         :32;	//31:0	//number of req_row hit in read port
	};
}REG_DDRC_M1_DEBUG_R_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905738 RO
	UINT32 reg_debug_nr_req_hit             :32;	//31:0	//number of req hit in read port
	};
}REG_DDRC_M1_DEBUG_R_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490573C RO
	UINT32 reg_debug_nr_urg_row_hit         :32;	//31:0	//number of urgent row hit in read port
	};
}REG_DDRC_M1_DEBUG_R_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905740 RO
	UINT32 reg_debug_nr_urg_hit             :32;	//31:0	//number of urgent hit in read port
	};
}REG_DDRC_M1_DEBUG_R_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905744 RO
	UINT32 reg_debug_nr_row_hit             :32;	//31:0	//number of row hit in read port
	};
}REG_DDRC_M1_DEBUG_R_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905748 RO
	UINT32 reg_debug_nr_lucky_hit           :32;	//31:0	//number of lucky in read port
	};
}REG_DDRC_M1_DEBUG_R_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905750 RO
	UINT32 reg_debug_nw_urg_swc             :32;	//31:0	//number of urgent write command swich
	};
}REG_DDRC_M1_DEBUG_W_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905754 RO
	UINT32 reg_debug_nw_req_row_hit         :32;	//31:0	//number of req_row hit in write port
	};
}REG_DDRC_M1_DEBUG_W_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905758 RO
	UINT32 reg_debug_nw_req_hit             :32;	//31:0	//number of req hit in write port
	};
}REG_DDRC_M1_DEBUG_W_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490575C RO
	UINT32 reg_debug_nw_urg_row_hit         :32;	//31:0	//number of urgent row hit in write port
	};
}REG_DDRC_M1_DEBUG_W_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905760 RO
	UINT32 reg_debug_nw_urg_hit             :32;	//31:0	//number of urgent hit in write port
	};
}REG_DDRC_M1_DEBUG_W_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905764 RO
	UINT32 reg_debug_nw_row_hit             :32;	//31:0	//number of row hit in write port
	};
}REG_DDRC_M1_DEBUG_W_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905768 RO
	UINT32 reg_debug_nw_lucky_hit           :32;	//31:0	//number of lucky in write port
	};
}REG_DDRC_M1_DEBUG_W_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905770 RO
	UINT32 reg_debug_max_lat_3              :8;	//7:0	//max latency for qos 1~3
	UINT32 reg_debug_max_lat_5              :8;	//15:8	//max latency for qos 4~5
	UINT32 reg_debug_max_lat_7              :8;	//23:16	//max latency for qos 6~7
	UINT32 reg_debug_max_lat_8              :8;	//31:24	//max latency for qos 8~
	};
}REG_DDRC_M1_DEBUG_MAX_LAT_QOS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905800 RO
	UINT32 reg_debug_nr_hyb_swc             :32;	//31:0	//number of hybrid read command swich
	};
}REG_DDRC_M1_DEBUG_R_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905804 RO
	UINT32 reg_debug_nw_hyb_swc             :32;	//31:0	//number of hybrid write command swich
	};
}REG_DDRC_M1_DEBUG_W_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905900 RO
	UINT32 reg_debug_nr_fifo_0_prt          :32;	//31:0	//number of read fifo 0 prt
	};
}REG_DDRC_M1_DEBUG_R_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905904 RO
	UINT32 reg_debug_nr_fifo_1_prt          :32;	//31:0	//number of read fifo 1 prt
	};
}REG_DDRC_M1_DEBUG_R_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905908 RO
	UINT32 reg_debug_nr_fifo_2_prt          :32;	//31:0	//number of read fifo 2 prt
	};
}REG_DDRC_M1_DEBUG_R_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490590C RO
	UINT32 reg_debug_nr_fifo_3_prt          :32;	//31:0	//number of read fifo 3 prt
	};
}REG_DDRC_M1_DEBUG_R_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905910 RO
	UINT32 reg_debug_nw_fifo_0_prt          :32;	//31:0	//number of write fifo 0 prt
	};
}REG_DDRC_M1_DEBUG_W_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905914 RO
	UINT32 reg_debug_nw_fifo_1_prt          :32;	//31:0	//number of write fifo 1 prt
	};
}REG_DDRC_M1_DEBUG_W_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4905918 RO
	UINT32 reg_debug_nw_fifo_2_prt          :32;	//31:0	//number of write fifo 2 prt
	};
}REG_DDRC_M1_DEBUG_W_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490591C RO
	UINT32 reg_debug_nw_fifo_3_prt          :32;	//31:0	//number of write fifo 3 prt
	};
}REG_DDRC_M1_DEBUG_W_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906000 RO
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
}REG_DDRC_M1_DEBUG_LPD4_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906004 RO
	UINT32 lpd4_mf_reg_fsm_status_0         :32;	//31:0	//Main FSM information (1ST)
	};
}REG_DDRC_M1_DEBUG_LPD4_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906008 RO
	UINT32 lpd4_mf_reg_fsm_status_1         :32;	//31:0	//Main FSM information (2ND)
	};
}REG_DDRC_M1_DEBUG_LPD4_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490600C RO
	UINT32 lpd4_mf_reg_fsm_status_2         :1;	//0 //Main FSM information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_DEBUG_LPD4_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906010 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_0    :32;	//31:0	//Direct control done information (1ST)
	};
}REG_DDRC_M1_DEBUG_LPD4_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906014 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_1    :32;	//31:0	//Direct control done information (2ND)
	};
}REG_DDRC_M1_DEBUG_LPD4_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906018 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_2    :1;	//0 //Direct control done information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M1_DEBUG_LPD4_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490601C RO
	UINT32 lpd4_rr_reg_ref_req_ctrl_status  :32;	//31:0	//[31:16] : Derated tREFI	[15:12] : Derated threshold value of urgent refresh	[11:4] : Derated tRRD	[1] : Forced all-bank refresh mode	[0] : Distributed all-bank refresh mode
	};
}REG_DDRC_M1_DEBUG_LPD4_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906020 RO
	UINT32 lpd4_rc_reg_fsm_status           :11;	//10:0	//Refresh controller FSM information
	UINT32 resvd                            :5;  
	UINT32 lpd4_rc_reg_ref_pb_sel_flag      :8;	//23:16	//Bank selection information for per-bank refresh
	UINT32 lpd4_rc_reg_ref_pb_done_flag     :8;	//31:24	//Bank completion information for per-bank refresh
	};
}REG_DDRC_M1_DEBUG_LPD4_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906024 RO
	UINT32 lpd4_bf_reg_fsm_status_b0        :14;	//13:0	//Bank FSM information (bank0)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b1        :14;	//29:16	//Bank FSM information (bank1)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M1_DEBUG_LPD4_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906028 RO
	UINT32 lpd4_bf_reg_fsm_status_b2        :14;	//13:0	//Bank FSM information (bank2)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b3        :14;	//29:16	//Bank FSM information (bank3)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M1_DEBUG_LPD4_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490602C RO
	UINT32 lpd4_bf_reg_fsm_status_b4        :14;	//13:0	//Bank FSM information (bank4)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b5        :14;	//29:16	//Bank FSM information (bank5)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M1_DEBUG_LPD4_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906030 RO
	UINT32 lpd4_bf_reg_fsm_status_b6        :14;	//13:0	//Bank FSM information (bank6)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b7        :14;	//29:16	//Bank FSM information (bank7)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M1_DEBUG_LPD4_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906034 RO
	UINT32 lpd4_bs_reg_bank_open            :8;	//7:0	//Bank open information
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M1_DEBUG_LPD4_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906038 RO
	UINT32 lpd4_bs_reg_rdy_status_0         :32;	//31:0	//Bank ready information	[31:24] : Read	[23:16] : Masked write	[15:8] : Write	[7:0] : Activate
	};
}REG_DDRC_M1_DEBUG_LPD4_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490603C RO
	UINT32 lpd4_bs_reg_rdy_status_1         :32;	//31:0	//Bank ready information	[28] : MRR	[27] : MRW	[26] : Power-down	[25] : All-bank refresh	[23:16] : Per-bank refresh	[15:8] : Auto-precharge	[7:0] : Per-bank precharge
	};
}REG_DDRC_M1_DEBUG_LPD4_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906040 RO
	UINT32 lpd4_pi_reg_fifo_status          :32;	//31:0	//Pointer information	[22:20] : Read pipeline pointer	[18:16] : Write pipeline pointer	[15:12] : RFIFO output pointer	[11:8] : RFIFO input pointer	[7:4] : WFIFO output pointer	[3:0] : WFIFO input pointer
	};
}REG_DDRC_M1_DEBUG_LPD4_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906100 RO
	UINT32 lpd4_mr_reg_mr0_ch0              :8;	//7:0	//MR0 read information for CH0
	UINT32 lpd4_mr_reg_mr4_ch0              :8;	//15:8	//MR4 read information for CH0
	UINT32 lpd4_mr_reg_mr5_ch0              :8;	//23:16	//MR5 read information for CH0
	UINT32 lpd4_mr_reg_mr6_ch0              :8;	//31:24	//MR6 read information for CH0
	};
}REG_DDRC_M1_DEBUG_LPD4_MR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906104 RO
	UINT32 lpd4_mr_reg_mr7_ch0              :8;	//7:0	//MR7 read information for CH0
	UINT32 lpd4_mr_reg_mr8_ch0              :8;	//15:8	//MR8 read information for CH0
	UINT32 lpd4_mr_reg_mr12_ch0             :8;	//23:16	//MR12 read information for CH0
	UINT32 lpd4_mr_reg_mr14_ch0             :8;	//31:24	//MR14 read information for CH0
	};
}REG_DDRC_M1_DEBUG_LPD4_MR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906108 RO
	UINT32 lpd4_mr_reg_mr18_ch0             :8;	//7:0	//MR18 read information for CH0
	UINT32 lpd4_mr_reg_mr19_ch0             :8;	//15:8	//MR19 read information for CH0
	UINT32 lpd4_mr_reg_mr24_ch0             :8;	//23:16	//MR24 read information for CH0
	UINT32 lpd4_mr_reg_mr25_ch0             :8;	//31:24	//MR25 read information for CH0
	};
}REG_DDRC_M1_DEBUG_LPD4_MR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490610C RO
	UINT32 lpd4_mr_reg_mr0_ch1              :8;	//7:0	//MR0 read information for CH1
	UINT32 lpd4_mr_reg_mr4_ch1              :8;	//15:8	//MR4 read information for CH1
	UINT32 lpd4_mr_reg_mr5_ch1              :8;	//23:16	//MR5 read information for CH1
	UINT32 lpd4_mr_reg_mr6_ch1              :8;	//31:24	//MR6 read information for CH1
	};
}REG_DDRC_M1_DEBUG_LPD4_MR_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906110 RO
	UINT32 lpd4_mr_reg_mr7_ch1              :8;	//7:0	//MR7 read information for CH1
	UINT32 lpd4_mr_reg_mr8_ch1              :8;	//15:8	//MR8 read information for CH1
	UINT32 lpd4_mr_reg_mr12_ch1             :8;	//23:16	//MR12 read information for CH1
	UINT32 lpd4_mr_reg_mr14_ch1             :8;	//31:24	//MR14 read information for CH1
	};
}REG_DDRC_M1_DEBUG_LPD4_MR_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906114 RO
	UINT32 lpd4_mr_reg_mr18_ch1             :8;	//7:0	//MR18 read information for CH1
	UINT32 lpd4_mr_reg_mr19_ch1             :8;	//15:8	//MR19 read information for CH1
	UINT32 lpd4_mr_reg_mr24_ch1             :8;	//23:16	//MR24 read information for CH1
	UINT32 lpd4_mr_reg_mr25_ch1             :8;	//31:24	//MR25 read information for CH1
	};
}REG_DDRC_M1_DEBUG_LPD4_MR_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906118 RO
	UINT32 lpd4_reg_mpc_fifo_fail_cnt       :32;	//31:0	//Periodic MPC FIFO fail count
	};
}REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490611C RO
	UINT32 lpd4_reg_mpc_fifo_fail_data0     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906120 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data1     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906124 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data2     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906128 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data3     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490612C RO
	UINT32 lpd4_reg_mpc_fifo_fail_dmi0      :4;	//3:0	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi1      :4;	//7:4	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi2      :4;	//11:8	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi3      :4;	//15:12	//Periodic MPC FIFO fail dmi data
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906200 RO
	UINT32 reg_mf_mrw1_cnt                  :20;	//19:0	//number of channel 1 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MRW1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906204 RO
	UINT32 reg_mf_mrw0_cnt                  :20;	//19:0	//number of channel 0 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MRW0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906208 RO
	UINT32 reg_mf_lp_exit_cnt               :20;	//19:0	//number of lp exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_LP_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490620C RO
	UINT32 reg_mf_lp_entry_cnt              :20;	//19:0	//number of lp entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_LP_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906210 RO
	UINT32 reg_mf_sr_pd_exit_cnt            :20;	//19:0	//number of self-rerfresh power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_SR_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906214 RO
	UINT32 reg_mf_sr_pd_entry_cnt           :20;	//19:0	//number of self-refresh power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_SR_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906218 RO
	UINT32 reg_mf_sr_exit_cnt               :20;	//19:0	//number of self-refresh exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_SR_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490621C RO
	UINT32 reg_mf_sr_entry_cnt              :20;	//19:0	//number of self_refresh entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_SR_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906220 RO
	UINT32 reg_mf_pd_exit_cnt               :20;	//19:0	//number of power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906224 RO
	UINT32 reg_mf_pd_entry_cnt              :20;	//19:0	//number of power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906228 RO
	UINT32 reg_mf_zqlat_cnt                 :20;	//19:0	//number of zqcal latch command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ZQLAT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490622C RO
	UINT32 reg_mf_zqcal_cnt                 :20;	//19:0	//number of zqcal command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ZQCAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906230 RO
	UINT32 reg_mf_cke_1_cnt                 :20;	//19:0	//number of cke rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_CKE1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906234 RO
	UINT32 reg_mf_cke_0_cnt                 :20;	//19:0	//number of cke falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_CKE0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906238 RO
	UINT32 reg_mf_rstn_1_cnt                :20;	//19:0	//number of reset rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RSTN1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490623C RO
	UINT32 reg_mf_rstn_0_cnt                :20;	//19:0	//number of reset falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RSTN0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906240 RO
	UINT32 reg_cg_rd0_cnt                   :32;	//31:0	//number of bank 0 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906244 RO
	UINT32 reg_cg_rd1_cnt                   :32;	//31:0	//number of bank 1 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906248 RO
	UINT32 reg_cg_rd2_cnt                   :32;	//31:0	//number of bank 2 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490624C RO
	UINT32 reg_cg_rd3_cnt                   :32;	//31:0	//number of bank 3 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906250 RO
	UINT32 reg_cg_rd4_cnt                   :32;	//31:0	//number of bank 4 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906254 RO
	UINT32 reg_cg_rd5_cnt                   :32;	//31:0	//number of bank 5 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906258 RO
	UINT32 reg_cg_rd6_cnt                   :32;	//31:0	//number of bank 6 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490625C RO
	UINT32 reg_cg_rd7_cnt                   :32;	//31:0	//number of bank 7 read command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_RD7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906260 RO
	UINT32 reg_cg_mwr0_cnt                  :32;	//31:0	//number of bank 0 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906264 RO
	UINT32 reg_cg_mwr1_cnt                  :32;	//31:0	//number of bank 1 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906268 RO
	UINT32 reg_cg_mwr2_cnt                  :32;	//31:0	//number of bank 2 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490626C RO
	UINT32 reg_cg_mwr3_cnt                  :32;	//31:0	//number of bank 3 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906270 RO
	UINT32 reg_cg_mwr4_cnt                  :32;	//31:0	//number of bank 4 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906274 RO
	UINT32 reg_cg_mwr5_cnt                  :32;	//31:0	//number of bank 5 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906278 RO
	UINT32 reg_cg_mwr6_cnt                  :32;	//31:0	//number of bank 6 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490627C RO
	UINT32 reg_cg_mwr7_cnt                  :32;	//31:0	//number of bank 7 masked write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MWR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906280 RO
	UINT32 reg_cg_wr0_cnt                   :32;	//31:0	//number of bank 0 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906284 RO
	UINT32 reg_cg_wr1_cnt                   :32;	//31:0	//number of bank 1 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906288 RO
	UINT32 reg_cg_wr2_cnt                   :32;	//31:0	//number of bank 2 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490628C RO
	UINT32 reg_cg_wr3_cnt                   :32;	//31:0	//number of bank 3 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906290 RO
	UINT32 reg_cg_wr4_cnt                   :32;	//31:0	//number of bank 4 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906294 RO
	UINT32 reg_cg_wr5_cnt                   :32;	//31:0	//number of bank 5 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906298 RO
	UINT32 reg_cg_wr6_cnt                   :32;	//31:0	//number of bank 6 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490629C RO
	UINT32 reg_cg_wr7_cnt                   :32;	//31:0	//number of bank 7 write command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_WR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062A0 RO
	UINT32 reg_cg_act0_cnt                  :32;	//31:0	//number of bank 0 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062A4 RO
	UINT32 reg_cg_act1_cnt                  :32;	//31:0	//number of bank 1 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062A8 RO
	UINT32 reg_cg_act2_cnt                  :32;	//31:0	//number of bank 2 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062AC RO
	UINT32 reg_cg_act3_cnt                  :32;	//31:0	//number of bank 3 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062B0 RO
	UINT32 reg_cg_act4_cnt                  :32;	//31:0	//number of bank 4 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062B4 RO
	UINT32 reg_cg_act5_cnt                  :32;	//31:0	//number of bank 5 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062B8 RO
	UINT32 reg_cg_act6_cnt                  :32;	//31:0	//number of bank 6 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49062BC RO
	UINT32 reg_cg_act7_cnt                  :32;	//31:0	//number of bank 7 activate command issued by command generator
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_ACT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906300 RO
	UINT32 reg_ref_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906304 RO
	UINT32 reg_ref_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906308 RO
	UINT32 reg_ref_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490630C RO
	UINT32 reg_ref_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906310 RO
	UINT32 reg_ref_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906314 RO
	UINT32 reg_ref_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906318 RO
	UINT32 reg_ref_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490631C RO
	UINT32 reg_ref_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906320 RO
	UINT32 reg_prg_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906324 RO
	UINT32 reg_prg_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906328 RO
	UINT32 reg_prg_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490632C RO
	UINT32 reg_prg_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906330 RO
	UINT32 reg_prg_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906334 RO
	UINT32 reg_prg_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906338 RO
	UINT32 reg_prg_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490633C RO
	UINT32 reg_prg_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906340 RO
	UINT32 reg_cg_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_CG_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906344 RO
	UINT32 reg_mf_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MF_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906350 RO
	UINT32 reg_cg_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_CG_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906354 RO
	UINT32 reg_mf_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_MF_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906360 RO
	UINT32 reg_cg_bl_cnt                    :22;	//21:0	//number of long burst command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_CG_BL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906364 RO
	UINT32 reg_cg_ap_cnt                    :22;	//21:0	//number of auto precharge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_CG_AP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906368 RO
	UINT32 reg_ref_cycling_done_cnt         :20;	//19:0	//number of refresh cycling done command
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M1_DEBUG_CTRL_CMD_REF_CYCLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906700 RO
	UINT32 pi_reg_dfi_status                :32;	//31:0	//DFI information	[30] : dfi_lp_ack	[29:26] : dfi_lp_wakeup	[25] : dfi_lp_req	[24] : dfi_dram_clk_disable	[23:21] : pll_freq_type[2:0]	[20] : pll_lock_done	[19:18] : pll_freq_type[4:3]	[17] : dfi_ctrlupd_ack	[16] : dfi_ctrlupd_req	[14] : dfi_phyupd_ack	[13] : dfi_phyupd_type	[12] : dfi_phyupd_req	[10] : dfi_phymstr_ack	[9] : dfi_phymstr_type	[8] : dfi_phymstr_req	[6] : dfi_init_complete	[5:1] : dfi_frequency	[0] : dfi_init_start
	};
}REG_DDRC_M1_DEBUG_DFI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906800 
	UINT32 reg_bist_start                   :1;	//0 //dram bist start, 0: stop, 1: start
	UINT32 resvd0                           :3;  
	UINT32 reg_bist_done                    :1;	//4 //dram bist done check, 0: running or idle, 1: done
	UINT32 resvd1                           :3;  
	UINT32 reg_bist_result                  :1;	//8 //dram bist result check , 0: PASS, 1: FAIL
	UINT32 resvd2                           :3;  
	UINT32 reg_bist_opcmd_ptr               :4;	//15:12	//dram bist opcmd pointer monitor
	UINT32 reg_bist_err_cnt                 :16;	//31:16	//dram bist err count monitor
	};
}REG_DDRC_M1_DRAM_BIST_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906804 
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
}REG_DDRC_M1_DRAM_BIST_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906808 
	UINT32 reg_bist_cmdq_vld                :16;	//15:0	//bist cmdq valid state monitor
	UINT32 reg_bist_cmdq_req                :16;	//31:16	//bist cmdq request state monitor
	};
}REG_DDRC_M1_DRAM_BIST_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490680C 
	UINT32 reg_user_pat                     :32;	//31:0	//set bist user data pattern
	};
}REG_DDRC_M1_DRAM_BIST_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906810 
	UINT32 reg_mask_pat_0                   :16;	//15:0	//data mask for 1st 16byte data
	UINT32 reg_mask_pat_1                   :16;	//31:16	//data mask for 2nd 16byte data
	};
}REG_DDRC_M1_DRAM_BIST_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906814 
	UINT32 reg_mask_pat_2                   :16;	//15:0	//data mask for 3rd 16byte data
	UINT32 reg_mask_pat_3                   :16;	//31:16	//data mask for 4th 16byte data
	};
}REG_DDRC_M1_DRAM_BIST_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906818 
	UINT32 reg_bist_addr_cnt_max            :32;	//31:0	//Set how many times to repeat when reg_bist_addr_map is not "SPL".
	};
}REG_DDRC_M1_DRAM_BIST_ADDR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490681C 
	UINT32 reg_s_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col)
	};
}REG_DDRC_M1_DRAM_BIST_ADDR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906820 
	UINT32 reg_e_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col), default 2Gbyte setting
	};
}REG_DDRC_M1_DRAM_BIST_ADDR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906824 
	UINT32 reg_bist_opcmd_00                :8;	//7:0	//
	UINT32 reg_bist_opcmd_01                :8;	//15:8	//
	UINT32 reg_bist_opcmd_02                :8;	//23:16	//
	UINT32 reg_bist_opcmd_03                :8;	//31:24	//set bist operation cmd  , default MARCH C-,
	};
}REG_DDRC_M1_DRAM_BIST_OPCMD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906828 
	UINT32 reg_bist_opcmd_04                :8;	//7:0	//
	UINT32 reg_bist_opcmd_05                :8;	//15:8	//
	UINT32 reg_bist_opcmd_06                :8;	//23:16	//
	UINT32 reg_bist_opcmd_07                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M1_DRAM_BIST_OPCMD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490682C 
	UINT32 reg_bist_opcmd_08                :8;	//7:0	//
	UINT32 reg_bist_opcmd_09                :8;	//15:8	//
	UINT32 reg_bist_opcmd_10                :8;	//23:16	//
	UINT32 reg_bist_opcmd_11                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M1_DRAM_BIST_OPCMD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906830 
	UINT32 reg_bist_opcmd_12                :8;	//7:0	//
	UINT32 reg_bist_opcmd_13                :8;	//15:8	//
	UINT32 reg_bist_opcmd_14                :8;	//23:16	//
	UINT32 reg_bist_opcmd_15                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M1_DRAM_BIST_OPCMD_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906834 RO
	UINT32 reg_err_addr                     :32;	//31:0	//address where error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_ADDR_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906838 RO
	UINT32 reg_err_data_00                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490683C RO
	UINT32 reg_err_data_01                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906840 RO
	UINT32 reg_err_data_02                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906844 RO
	UINT32 reg_err_data_03                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906848 RO
	UINT32 reg_err_data_04                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490684C RO
	UINT32 reg_err_data_05                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906850 RO
	UINT32 reg_err_data_06                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906854 RO
	UINT32 reg_err_data_07                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906858 RO
	UINT32 reg_err_data_08                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490685C RO
	UINT32 reg_err_data_09                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906860 RO
	UINT32 reg_err_data_10                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906864 RO
	UINT32 reg_err_data_11                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906868 RO
	UINT32 reg_err_data_12                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490686C RO
	UINT32 reg_err_data_13                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906870 RO
	UINT32 reg_err_data_14                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906874 RO
	UINT32 reg_err_data_15                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906878 RO
	UINT32 reg_exp_data_00                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490687C RO
	UINT32 reg_exp_data_01                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906880 RO
	UINT32 reg_exp_data_02                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906884 RO
	UINT32 reg_exp_data_03                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906888 RO
	UINT32 reg_exp_data_04                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490688C RO
	UINT32 reg_exp_data_05                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906890 RO
	UINT32 reg_exp_data_06                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906894 RO
	UINT32 reg_exp_data_07                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906898 RO
	UINT32 reg_exp_data_08                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC490689C RO
	UINT32 reg_exp_data_09                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49068A0 RO
	UINT32 reg_exp_data_10                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49068A4 RO
	UINT32 reg_exp_data_11                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49068A8 RO
	UINT32 reg_exp_data_12                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49068AC RO
	UINT32 reg_exp_data_13                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49068B0 RO
	UINT32 reg_exp_data_14                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC49068B4 RO
	UINT32 reg_exp_data_15                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4906FE0 RW
	UINT32 reg_rey_spare                    :32;	//31:0	//spare register for ECO (should not be removed)
	};
}REG_DDRC_M1_REY_SPARE_T;

typedef struct {
	REG_DDRC_M1_DRAM_CONF_T                                   dram_conf;	//0xC4900000
	REG_DDRC_M1_MODE_SEL_T                                     mode_sel;	//0xC4900004
	REG_DDRC_M1_BASE_PERIOD_T                               base_period;	//0xC4900008
	UINT32                                                    reserved0;	//0xC490000C
	UINT32                                                    reserved1;	//0xC4900010
	UINT32                                                    reserved2;	//0xC4900014
	UINT32                                                    reserved3;	//0xC4900018
	UINT32                                                    reserved4;	//0xC490001C
	UINT32                                                    reserved5;	//0xC4900020
	UINT32                                                    reserved6;	//0xC4900024
	UINT32                                                    reserved7;	//0xC4900028
	UINT32                                                    reserved8;	//0xC490002C
	UINT32                                                    reserved9;	//0xC4900030
	UINT32                                                   reserved10;	//0xC4900034
	UINT32                                                   reserved11;	//0xC4900038
	UINT32                                                   reserved12;	//0xC490003C
	UINT32                                                   reserved13;	//0xC4900040
	UINT32                                                   reserved14;	//0xC4900044
	UINT32                                                   reserved15;	//0xC4900048
	UINT32                                                   reserved16;	//0xC490004C
	UINT32                                                   reserved17;	//0xC4900050
	UINT32                                                   reserved18;	//0xC4900054
	UINT32                                                   reserved19;	//0xC4900058
	UINT32                                                   reserved20;	//0xC490005C
	UINT32                                                   reserved21;	//0xC4900060
	UINT32                                                   reserved22;	//0xC4900064
	UINT32                                                   reserved23;	//0xC4900068
	UINT32                                                   reserved24;	//0xC490006C
	UINT32                                                   reserved25;	//0xC4900070
	UINT32                                                   reserved26;	//0xC4900074
	UINT32                                                   reserved27;	//0xC4900078
	UINT32                                                   reserved28;	//0xC490007C
	UINT32                                                   reserved29;	//0xC4900080
	UINT32                                                   reserved30;	//0xC4900084
	UINT32                                                   reserved31;	//0xC4900088
	UINT32                                                   reserved32;	//0xC490008C
	UINT32                                                   reserved33;	//0xC4900090
	UINT32                                                   reserved34;	//0xC4900094
	UINT32                                                   reserved35;	//0xC4900098
	UINT32                                                   reserved36;	//0xC490009C
	UINT32                                                   reserved37;	//0xC49000A0
	UINT32                                                   reserved38;	//0xC49000A4
	UINT32                                                   reserved39;	//0xC49000A8
	UINT32                                                   reserved40;	//0xC49000AC
	UINT32                                                   reserved41;	//0xC49000B0
	UINT32                                                   reserved42;	//0xC49000B4
	UINT32                                                   reserved43;	//0xC49000B8
	UINT32                                                   reserved44;	//0xC49000BC
	UINT32                                                   reserved45;	//0xC49000C0
	UINT32                                                   reserved46;	//0xC49000C4
	UINT32                                                   reserved47;	//0xC49000C8
	UINT32                                                   reserved48;	//0xC49000CC
	UINT32                                                   reserved49;	//0xC49000D0
	UINT32                                                   reserved50;	//0xC49000D4
	UINT32                                                   reserved51;	//0xC49000D8
	UINT32                                                   reserved52;	//0xC49000DC
	UINT32                                                   reserved53;	//0xC49000E0
	UINT32                                                   reserved54;	//0xC49000E4
	UINT32                                                   reserved55;	//0xC49000E8
	UINT32                                                   reserved56;	//0xC49000EC
	UINT32                                                   reserved57;	//0xC49000F0
	UINT32                                                   reserved58;	//0xC49000F4
	UINT32                                                   reserved59;	//0xC49000F8
	UINT32                                                   reserved60;	//0xC49000FC
	REG_DDRC_M1_ALP_T                                               alp;	//0xC4900100
	REG_DDRC_M1_CGL_T                                               cgl;	//0xC4900104
	REG_DDRC_M1_CGL_MON_T                                       cgl_mon;	//0xC4900108
	UINT32                                                   reserved61;	//0xC490010C
	UINT32                                                   reserved62;	//0xC4900110
	UINT32                                                   reserved63;	//0xC4900114
	UINT32                                                   reserved64;	//0xC4900118
	UINT32                                                   reserved65;	//0xC490011C
	UINT32                                                   reserved66;	//0xC4900120
	UINT32                                                   reserved67;	//0xC4900124
	UINT32                                                   reserved68;	//0xC4900128
	UINT32                                                   reserved69;	//0xC490012C
	UINT32                                                   reserved70;	//0xC4900130
	UINT32                                                   reserved71;	//0xC4900134
	UINT32                                                   reserved72;	//0xC4900138
	UINT32                                                   reserved73;	//0xC490013C
	UINT32                                                   reserved74;	//0xC4900140
	UINT32                                                   reserved75;	//0xC4900144
	UINT32                                                   reserved76;	//0xC4900148
	UINT32                                                   reserved77;	//0xC490014C
	UINT32                                                   reserved78;	//0xC4900150
	UINT32                                                   reserved79;	//0xC4900154
	UINT32                                                   reserved80;	//0xC4900158
	UINT32                                                   reserved81;	//0xC490015C
	UINT32                                                   reserved82;	//0xC4900160
	UINT32                                                   reserved83;	//0xC4900164
	UINT32                                                   reserved84;	//0xC4900168
	UINT32                                                   reserved85;	//0xC490016C
	UINT32                                                   reserved86;	//0xC4900170
	UINT32                                                   reserved87;	//0xC4900174
	UINT32                                                   reserved88;	//0xC4900178
	UINT32                                                   reserved89;	//0xC490017C
	UINT32                                                   reserved90;	//0xC4900180
	UINT32                                                   reserved91;	//0xC4900184
	UINT32                                                   reserved92;	//0xC4900188
	UINT32                                                   reserved93;	//0xC490018C
	UINT32                                                   reserved94;	//0xC4900190
	UINT32                                                   reserved95;	//0xC4900194
	UINT32                                                   reserved96;	//0xC4900198
	UINT32                                                   reserved97;	//0xC490019C
	UINT32                                                   reserved98;	//0xC49001A0
	UINT32                                                   reserved99;	//0xC49001A4
	UINT32                                                  reserved100;	//0xC49001A8
	UINT32                                                  reserved101;	//0xC49001AC
	UINT32                                                  reserved102;	//0xC49001B0
	UINT32                                                  reserved103;	//0xC49001B4
	UINT32                                                  reserved104;	//0xC49001B8
	UINT32                                                  reserved105;	//0xC49001BC
	UINT32                                                  reserved106;	//0xC49001C0
	UINT32                                                  reserved107;	//0xC49001C4
	UINT32                                                  reserved108;	//0xC49001C8
	UINT32                                                  reserved109;	//0xC49001CC
	UINT32                                                  reserved110;	//0xC49001D0
	UINT32                                                  reserved111;	//0xC49001D4
	UINT32                                                  reserved112;	//0xC49001D8
	UINT32                                                  reserved113;	//0xC49001DC
	UINT32                                                  reserved114;	//0xC49001E0
	UINT32                                                  reserved115;	//0xC49001E4
	UINT32                                                  reserved116;	//0xC49001E8
	UINT32                                                  reserved117;	//0xC49001EC
	UINT32                                                  reserved118;	//0xC49001F0
	UINT32                                                  reserved119;	//0xC49001F4
	UINT32                                                  reserved120;	//0xC49001F8
	UINT32                                                  reserved121;	//0xC49001FC
	REG_DDRC_M1_PERFMON_T                                       perfmon;	//0xC4900200
	REG_DDRC_M1_PERFMON_EMG_MAX_T                       perfmon_emg_max;	//0xC4900204
	UINT32                                                  reserved122;	//0xC4900208
	UINT32                                                  reserved123;	//0xC490020C
	REG_DDRC_M1_PERFMON_W0_T                                 perfmon_w0;	//0xC4900210
	REG_DDRC_M1_PERFMON_W1_T                                 perfmon_w1;	//0xC4900214
	REG_DDRC_M1_PERFMON_W2_T                                 perfmon_w2;	//0xC4900218
	REG_DDRC_M1_PERFMON_W3_T                                 perfmon_w3;	//0xC490021C
	REG_DDRC_M1_PERFMON_R0_T                                 perfmon_r0;	//0xC4900220
	REG_DDRC_M1_PERFMON_R1_T                                 perfmon_r1;	//0xC4900224
	REG_DDRC_M1_PERFMON_R2_T                                 perfmon_r2;	//0xC4900228
	REG_DDRC_M1_PERFMON_R3_T                                 perfmon_r3;	//0xC490022C
	REG_DDRC_M1_LATMON_T                                         latmon;	//0xC4900230
	UINT32                                                  reserved124;	//0xC4900234
	UINT32                                                  reserved125;	//0xC4900238
	UINT32                                                  reserved126;	//0xC490023C
	UINT32                                                  reserved127;	//0xC4900240
	UINT32                                                  reserved128;	//0xC4900244
	UINT32                                                  reserved129;	//0xC4900248
	UINT32                                                  reserved130;	//0xC490024C
	UINT32                                                  reserved131;	//0xC4900250
	UINT32                                                  reserved132;	//0xC4900254
	UINT32                                                  reserved133;	//0xC4900258
	UINT32                                                  reserved134;	//0xC490025C
	UINT32                                                  reserved135;	//0xC4900260
	UINT32                                                  reserved136;	//0xC4900264
	UINT32                                                  reserved137;	//0xC4900268
	UINT32                                                  reserved138;	//0xC490026C
	UINT32                                                  reserved139;	//0xC4900270
	UINT32                                                  reserved140;	//0xC4900274
	UINT32                                                  reserved141;	//0xC4900278
	UINT32                                                  reserved142;	//0xC490027C
	UINT32                                                  reserved143;	//0xC4900280
	UINT32                                                  reserved144;	//0xC4900284
	UINT32                                                  reserved145;	//0xC4900288
	UINT32                                                  reserved146;	//0xC490028C
	UINT32                                                  reserved147;	//0xC4900290
	UINT32                                                  reserved148;	//0xC4900294
	UINT32                                                  reserved149;	//0xC4900298
	UINT32                                                  reserved150;	//0xC490029C
	UINT32                                                  reserved151;	//0xC49002A0
	UINT32                                                  reserved152;	//0xC49002A4
	UINT32                                                  reserved153;	//0xC49002A8
	UINT32                                                  reserved154;	//0xC49002AC
	UINT32                                                  reserved155;	//0xC49002B0
	UINT32                                                  reserved156;	//0xC49002B4
	UINT32                                                  reserved157;	//0xC49002B8
	UINT32                                                  reserved158;	//0xC49002BC
	UINT32                                                  reserved159;	//0xC49002C0
	UINT32                                                  reserved160;	//0xC49002C4
	UINT32                                                  reserved161;	//0xC49002C8
	UINT32                                                  reserved162;	//0xC49002CC
	UINT32                                                  reserved163;	//0xC49002D0
	UINT32                                                  reserved164;	//0xC49002D4
	UINT32                                                  reserved165;	//0xC49002D8
	UINT32                                                  reserved166;	//0xC49002DC
	UINT32                                                  reserved167;	//0xC49002E0
	UINT32                                                  reserved168;	//0xC49002E4
	UINT32                                                  reserved169;	//0xC49002E8
	UINT32                                                  reserved170;	//0xC49002EC
	UINT32                                                  reserved171;	//0xC49002F0
	UINT32                                                  reserved172;	//0xC49002F4
	UINT32                                                  reserved173;	//0xC49002F8
	UINT32                                                  reserved174;	//0xC49002FC
	REG_DDRC_M1_DFS_T                                               dfs;	//0xC4900300
	REG_DDRC_M1_DFS_RESULT_T                                 dfs_result;	//0xC4900304
	UINT32                                                  reserved175;	//0xC4900308
	UINT32                                                  reserved176;	//0xC490030C
	UINT32                                                  reserved177;	//0xC4900310
	UINT32                                                  reserved178;	//0xC4900314
	UINT32                                                  reserved179;	//0xC4900318
	UINT32                                                  reserved180;	//0xC490031C
	UINT32                                                  reserved181;	//0xC4900320
	UINT32                                                  reserved182;	//0xC4900324
	UINT32                                                  reserved183;	//0xC4900328
	UINT32                                                  reserved184;	//0xC490032C
	UINT32                                                  reserved185;	//0xC4900330
	UINT32                                                  reserved186;	//0xC4900334
	UINT32                                                  reserved187;	//0xC4900338
	UINT32                                                  reserved188;	//0xC490033C
	UINT32                                                  reserved189;	//0xC4900340
	UINT32                                                  reserved190;	//0xC4900344
	UINT32                                                  reserved191;	//0xC4900348
	UINT32                                                  reserved192;	//0xC490034C
	UINT32                                                  reserved193;	//0xC4900350
	UINT32                                                  reserved194;	//0xC4900354
	UINT32                                                  reserved195;	//0xC4900358
	UINT32                                                  reserved196;	//0xC490035C
	UINT32                                                  reserved197;	//0xC4900360
	UINT32                                                  reserved198;	//0xC4900364
	UINT32                                                  reserved199;	//0xC4900368
	UINT32                                                  reserved200;	//0xC490036C
	UINT32                                                  reserved201;	//0xC4900370
	UINT32                                                  reserved202;	//0xC4900374
	UINT32                                                  reserved203;	//0xC4900378
	UINT32                                                  reserved204;	//0xC490037C
	UINT32                                                  reserved205;	//0xC4900380
	UINT32                                                  reserved206;	//0xC4900384
	UINT32                                                  reserved207;	//0xC4900388
	UINT32                                                  reserved208;	//0xC490038C
	UINT32                                                  reserved209;	//0xC4900390
	UINT32                                                  reserved210;	//0xC4900394
	UINT32                                                  reserved211;	//0xC4900398
	UINT32                                                  reserved212;	//0xC490039C
	UINT32                                                  reserved213;	//0xC49003A0
	UINT32                                                  reserved214;	//0xC49003A4
	UINT32                                                  reserved215;	//0xC49003A8
	UINT32                                                  reserved216;	//0xC49003AC
	UINT32                                                  reserved217;	//0xC49003B0
	UINT32                                                  reserved218;	//0xC49003B4
	UINT32                                                  reserved219;	//0xC49003B8
	UINT32                                                  reserved220;	//0xC49003BC
	UINT32                                                  reserved221;	//0xC49003C0
	UINT32                                                  reserved222;	//0xC49003C4
	UINT32                                                  reserved223;	//0xC49003C8
	UINT32                                                  reserved224;	//0xC49003CC
	UINT32                                                  reserved225;	//0xC49003D0
	UINT32                                                  reserved226;	//0xC49003D4
	UINT32                                                  reserved227;	//0xC49003D8
	UINT32                                                  reserved228;	//0xC49003DC
	UINT32                                                  reserved229;	//0xC49003E0
	UINT32                                                  reserved230;	//0xC49003E4
	UINT32                                                  reserved231;	//0xC49003E8
	UINT32                                                  reserved232;	//0xC49003EC
	UINT32                                                  reserved233;	//0xC49003F0
	UINT32                                                  reserved234;	//0xC49003F4
	UINT32                                                  reserved235;	//0xC49003F8
	UINT32                                                  reserved236;	//0xC49003FC
	REG_DDRC_M1_ADDR_MAP_T                                     addr_map;	//0xC4900400
	REG_DDRC_M1_COMMON_T                                         common;	//0xC4900404
	REG_DDRC_M1_DATA_ENC0_T                                   data_enc0;	//0xC4900408
	REG_DDRC_M1_DATA_ENC1_T                                   data_enc1;	//0xC490040C
	UINT32                                                  reserved237;	//0xC4900410
	UINT32                                                  reserved238;	//0xC4900414
	UINT32                                                  reserved239;	//0xC4900418
	UINT32                                                  reserved240;	//0xC490041C
	UINT32                                                  reserved241;	//0xC4900420
	UINT32                                                  reserved242;	//0xC4900424
	UINT32                                                  reserved243;	//0xC4900428
	UINT32                                                  reserved244;	//0xC490042C
	UINT32                                                  reserved245;	//0xC4900430
	UINT32                                                  reserved246;	//0xC4900434
	UINT32                                                  reserved247;	//0xC4900438
	UINT32                                                  reserved248;	//0xC490043C
	UINT32                                                  reserved249;	//0xC4900440
	UINT32                                                  reserved250;	//0xC4900444
	UINT32                                                  reserved251;	//0xC4900448
	UINT32                                                  reserved252;	//0xC490044C
	UINT32                                                  reserved253;	//0xC4900450
	UINT32                                                  reserved254;	//0xC4900454
	UINT32                                                  reserved255;	//0xC4900458
	UINT32                                                  reserved256;	//0xC490045C
	UINT32                                                  reserved257;	//0xC4900460
	UINT32                                                  reserved258;	//0xC4900464
	UINT32                                                  reserved259;	//0xC4900468
	UINT32                                                  reserved260;	//0xC490046C
	UINT32                                                  reserved261;	//0xC4900470
	UINT32                                                  reserved262;	//0xC4900474
	UINT32                                                  reserved263;	//0xC4900478
	UINT32                                                  reserved264;	//0xC490047C
	UINT32                                                  reserved265;	//0xC4900480
	UINT32                                                  reserved266;	//0xC4900484
	UINT32                                                  reserved267;	//0xC4900488
	UINT32                                                  reserved268;	//0xC490048C
	UINT32                                                  reserved269;	//0xC4900490
	UINT32                                                  reserved270;	//0xC4900494
	UINT32                                                  reserved271;	//0xC4900498
	UINT32                                                  reserved272;	//0xC490049C
	UINT32                                                  reserved273;	//0xC49004A0
	UINT32                                                  reserved274;	//0xC49004A4
	UINT32                                                  reserved275;	//0xC49004A8
	UINT32                                                  reserved276;	//0xC49004AC
	UINT32                                                  reserved277;	//0xC49004B0
	UINT32                                                  reserved278;	//0xC49004B4
	UINT32                                                  reserved279;	//0xC49004B8
	UINT32                                                  reserved280;	//0xC49004BC
	UINT32                                                  reserved281;	//0xC49004C0
	UINT32                                                  reserved282;	//0xC49004C4
	UINT32                                                  reserved283;	//0xC49004C8
	UINT32                                                  reserved284;	//0xC49004CC
	UINT32                                                  reserved285;	//0xC49004D0
	UINT32                                                  reserved286;	//0xC49004D4
	UINT32                                                  reserved287;	//0xC49004D8
	UINT32                                                  reserved288;	//0xC49004DC
	UINT32                                                  reserved289;	//0xC49004E0
	UINT32                                                  reserved290;	//0xC49004E4
	UINT32                                                  reserved291;	//0xC49004E8
	UINT32                                                  reserved292;	//0xC49004EC
	UINT32                                                  reserved293;	//0xC49004F0
	UINT32                                                  reserved294;	//0xC49004F4
	UINT32                                                  reserved295;	//0xC49004F8
	UINT32                                                  reserved296;	//0xC49004FC
	REG_DDRC_M1_RD_URG_T                                         rd_urg;	//0xC4900500
	REG_DDRC_M1_WR_URG_T                                         wr_urg;	//0xC4900504
	UINT32                                                  reserved297;	//0xC4900508
	UINT32                                                  reserved298;	//0xC490050C
	UINT32                                                  reserved299;	//0xC4900510
	UINT32                                                  reserved300;	//0xC4900514
	UINT32                                                  reserved301;	//0xC4900518
	UINT32                                                  reserved302;	//0xC490051C
	UINT32                                                  reserved303;	//0xC4900520
	UINT32                                                  reserved304;	//0xC4900524
	UINT32                                                  reserved305;	//0xC4900528
	UINT32                                                  reserved306;	//0xC490052C
	UINT32                                                  reserved307;	//0xC4900530
	UINT32                                                  reserved308;	//0xC4900534
	UINT32                                                  reserved309;	//0xC4900538
	UINT32                                                  reserved310;	//0xC490053C
	UINT32                                                  reserved311;	//0xC4900540
	UINT32                                                  reserved312;	//0xC4900544
	UINT32                                                  reserved313;	//0xC4900548
	UINT32                                                  reserved314;	//0xC490054C
	UINT32                                                  reserved315;	//0xC4900550
	UINT32                                                  reserved316;	//0xC4900554
	UINT32                                                  reserved317;	//0xC4900558
	UINT32                                                  reserved318;	//0xC490055C
	UINT32                                                  reserved319;	//0xC4900560
	UINT32                                                  reserved320;	//0xC4900564
	UINT32                                                  reserved321;	//0xC4900568
	UINT32                                                  reserved322;	//0xC490056C
	UINT32                                                  reserved323;	//0xC4900570
	UINT32                                                  reserved324;	//0xC4900574
	UINT32                                                  reserved325;	//0xC4900578
	UINT32                                                  reserved326;	//0xC490057C
	UINT32                                                  reserved327;	//0xC4900580
	UINT32                                                  reserved328;	//0xC4900584
	UINT32                                                  reserved329;	//0xC4900588
	UINT32                                                  reserved330;	//0xC490058C
	UINT32                                                  reserved331;	//0xC4900590
	UINT32                                                  reserved332;	//0xC4900594
	UINT32                                                  reserved333;	//0xC4900598
	UINT32                                                  reserved334;	//0xC490059C
	UINT32                                                  reserved335;	//0xC49005A0
	UINT32                                                  reserved336;	//0xC49005A4
	UINT32                                                  reserved337;	//0xC49005A8
	UINT32                                                  reserved338;	//0xC49005AC
	UINT32                                                  reserved339;	//0xC49005B0
	UINT32                                                  reserved340;	//0xC49005B4
	UINT32                                                  reserved341;	//0xC49005B8
	UINT32                                                  reserved342;	//0xC49005BC
	UINT32                                                  reserved343;	//0xC49005C0
	UINT32                                                  reserved344;	//0xC49005C4
	UINT32                                                  reserved345;	//0xC49005C8
	UINT32                                                  reserved346;	//0xC49005CC
	UINT32                                                  reserved347;	//0xC49005D0
	UINT32                                                  reserved348;	//0xC49005D4
	UINT32                                                  reserved349;	//0xC49005D8
	UINT32                                                  reserved350;	//0xC49005DC
	UINT32                                                  reserved351;	//0xC49005E0
	UINT32                                                  reserved352;	//0xC49005E4
	UINT32                                                  reserved353;	//0xC49005E8
	UINT32                                                  reserved354;	//0xC49005EC
	UINT32                                                  reserved355;	//0xC49005F0
	UINT32                                                  reserved356;	//0xC49005F4
	UINT32                                                  reserved357;	//0xC49005F8
	UINT32                                                  reserved358;	//0xC49005FC
	UINT32                                                  reserved359;	//0xC4900600
	UINT32                                                  reserved360;	//0xC4900604
	UINT32                                                  reserved361;	//0xC4900608
	UINT32                                                  reserved362;	//0xC490060C
	UINT32                                                  reserved363;	//0xC4900610
	UINT32                                                  reserved364;	//0xC4900614
	UINT32                                                  reserved365;	//0xC4900618
	UINT32                                                  reserved366;	//0xC490061C
	UINT32                                                  reserved367;	//0xC4900620
	UINT32                                                  reserved368;	//0xC4900624
	UINT32                                                  reserved369;	//0xC4900628
	UINT32                                                  reserved370;	//0xC490062C
	UINT32                                                  reserved371;	//0xC4900630
	UINT32                                                  reserved372;	//0xC4900634
	UINT32                                                  reserved373;	//0xC4900638
	UINT32                                                  reserved374;	//0xC490063C
	UINT32                                                  reserved375;	//0xC4900640
	UINT32                                                  reserved376;	//0xC4900644
	UINT32                                                  reserved377;	//0xC4900648
	UINT32                                                  reserved378;	//0xC490064C
	UINT32                                                  reserved379;	//0xC4900650
	UINT32                                                  reserved380;	//0xC4900654
	UINT32                                                  reserved381;	//0xC4900658
	UINT32                                                  reserved382;	//0xC490065C
	UINT32                                                  reserved383;	//0xC4900660
	UINT32                                                  reserved384;	//0xC4900664
	UINT32                                                  reserved385;	//0xC4900668
	UINT32                                                  reserved386;	//0xC490066C
	UINT32                                                  reserved387;	//0xC4900670
	UINT32                                                  reserved388;	//0xC4900674
	UINT32                                                  reserved389;	//0xC4900678
	UINT32                                                  reserved390;	//0xC490067C
	UINT32                                                  reserved391;	//0xC4900680
	UINT32                                                  reserved392;	//0xC4900684
	UINT32                                                  reserved393;	//0xC4900688
	UINT32                                                  reserved394;	//0xC490068C
	UINT32                                                  reserved395;	//0xC4900690
	UINT32                                                  reserved396;	//0xC4900694
	UINT32                                                  reserved397;	//0xC4900698
	UINT32                                                  reserved398;	//0xC490069C
	UINT32                                                  reserved399;	//0xC49006A0
	UINT32                                                  reserved400;	//0xC49006A4
	UINT32                                                  reserved401;	//0xC49006A8
	UINT32                                                  reserved402;	//0xC49006AC
	UINT32                                                  reserved403;	//0xC49006B0
	UINT32                                                  reserved404;	//0xC49006B4
	UINT32                                                  reserved405;	//0xC49006B8
	UINT32                                                  reserved406;	//0xC49006BC
	UINT32                                                  reserved407;	//0xC49006C0
	UINT32                                                  reserved408;	//0xC49006C4
	UINT32                                                  reserved409;	//0xC49006C8
	UINT32                                                  reserved410;	//0xC49006CC
	UINT32                                                  reserved411;	//0xC49006D0
	UINT32                                                  reserved412;	//0xC49006D4
	UINT32                                                  reserved413;	//0xC49006D8
	UINT32                                                  reserved414;	//0xC49006DC
	UINT32                                                  reserved415;	//0xC49006E0
	UINT32                                                  reserved416;	//0xC49006E4
	UINT32                                                  reserved417;	//0xC49006E8
	UINT32                                                  reserved418;	//0xC49006EC
	UINT32                                                  reserved419;	//0xC49006F0
	UINT32                                                  reserved420;	//0xC49006F4
	UINT32                                                  reserved421;	//0xC49006F8
	UINT32                                                  reserved422;	//0xC49006FC
	UINT32                                                  reserved423;	//0xC4900700
	UINT32                                                  reserved424;	//0xC4900704
	UINT32                                                  reserved425;	//0xC4900708
	UINT32                                                  reserved426;	//0xC490070C
	UINT32                                                  reserved427;	//0xC4900710
	UINT32                                                  reserved428;	//0xC4900714
	UINT32                                                  reserved429;	//0xC4900718
	UINT32                                                  reserved430;	//0xC490071C
	UINT32                                                  reserved431;	//0xC4900720
	UINT32                                                  reserved432;	//0xC4900724
	UINT32                                                  reserved433;	//0xC4900728
	UINT32                                                  reserved434;	//0xC490072C
	UINT32                                                  reserved435;	//0xC4900730
	UINT32                                                  reserved436;	//0xC4900734
	UINT32                                                  reserved437;	//0xC4900738
	UINT32                                                  reserved438;	//0xC490073C
	UINT32                                                  reserved439;	//0xC4900740
	UINT32                                                  reserved440;	//0xC4900744
	UINT32                                                  reserved441;	//0xC4900748
	UINT32                                                  reserved442;	//0xC490074C
	UINT32                                                  reserved443;	//0xC4900750
	UINT32                                                  reserved444;	//0xC4900754
	UINT32                                                  reserved445;	//0xC4900758
	UINT32                                                  reserved446;	//0xC490075C
	UINT32                                                  reserved447;	//0xC4900760
	UINT32                                                  reserved448;	//0xC4900764
	UINT32                                                  reserved449;	//0xC4900768
	UINT32                                                  reserved450;	//0xC490076C
	UINT32                                                  reserved451;	//0xC4900770
	UINT32                                                  reserved452;	//0xC4900774
	UINT32                                                  reserved453;	//0xC4900778
	UINT32                                                  reserved454;	//0xC490077C
	UINT32                                                  reserved455;	//0xC4900780
	UINT32                                                  reserved456;	//0xC4900784
	UINT32                                                  reserved457;	//0xC4900788
	UINT32                                                  reserved458;	//0xC490078C
	UINT32                                                  reserved459;	//0xC4900790
	UINT32                                                  reserved460;	//0xC4900794
	UINT32                                                  reserved461;	//0xC4900798
	UINT32                                                  reserved462;	//0xC490079C
	UINT32                                                  reserved463;	//0xC49007A0
	UINT32                                                  reserved464;	//0xC49007A4
	UINT32                                                  reserved465;	//0xC49007A8
	UINT32                                                  reserved466;	//0xC49007AC
	UINT32                                                  reserved467;	//0xC49007B0
	UINT32                                                  reserved468;	//0xC49007B4
	UINT32                                                  reserved469;	//0xC49007B8
	UINT32                                                  reserved470;	//0xC49007BC
	UINT32                                                  reserved471;	//0xC49007C0
	UINT32                                                  reserved472;	//0xC49007C4
	UINT32                                                  reserved473;	//0xC49007C8
	UINT32                                                  reserved474;	//0xC49007CC
	UINT32                                                  reserved475;	//0xC49007D0
	UINT32                                                  reserved476;	//0xC49007D4
	UINT32                                                  reserved477;	//0xC49007D8
	UINT32                                                  reserved478;	//0xC49007DC
	UINT32                                                  reserved479;	//0xC49007E0
	UINT32                                                  reserved480;	//0xC49007E4
	UINT32                                                  reserved481;	//0xC49007E8
	UINT32                                                  reserved482;	//0xC49007EC
	UINT32                                                  reserved483;	//0xC49007F0
	UINT32                                                  reserved484;	//0xC49007F4
	UINT32                                                  reserved485;	//0xC49007F8
	UINT32                                                  reserved486;	//0xC49007FC
	UINT32                                                  reserved487;	//0xC4900800
	UINT32                                                  reserved488;	//0xC4900804
	UINT32                                                  reserved489;	//0xC4900808
	UINT32                                                  reserved490;	//0xC490080C
	UINT32                                                  reserved491;	//0xC4900810
	UINT32                                                  reserved492;	//0xC4900814
	UINT32                                                  reserved493;	//0xC4900818
	UINT32                                                  reserved494;	//0xC490081C
	UINT32                                                  reserved495;	//0xC4900820
	UINT32                                                  reserved496;	//0xC4900824
	UINT32                                                  reserved497;	//0xC4900828
	UINT32                                                  reserved498;	//0xC490082C
	UINT32                                                  reserved499;	//0xC4900830
	UINT32                                                  reserved500;	//0xC4900834
	UINT32                                                  reserved501;	//0xC4900838
	UINT32                                                  reserved502;	//0xC490083C
	UINT32                                                  reserved503;	//0xC4900840
	UINT32                                                  reserved504;	//0xC4900844
	UINT32                                                  reserved505;	//0xC4900848
	UINT32                                                  reserved506;	//0xC490084C
	UINT32                                                  reserved507;	//0xC4900850
	UINT32                                                  reserved508;	//0xC4900854
	UINT32                                                  reserved509;	//0xC4900858
	UINT32                                                  reserved510;	//0xC490085C
	UINT32                                                  reserved511;	//0xC4900860
	UINT32                                                  reserved512;	//0xC4900864
	UINT32                                                  reserved513;	//0xC4900868
	UINT32                                                  reserved514;	//0xC490086C
	UINT32                                                  reserved515;	//0xC4900870
	UINT32                                                  reserved516;	//0xC4900874
	UINT32                                                  reserved517;	//0xC4900878
	UINT32                                                  reserved518;	//0xC490087C
	UINT32                                                  reserved519;	//0xC4900880
	UINT32                                                  reserved520;	//0xC4900884
	UINT32                                                  reserved521;	//0xC4900888
	UINT32                                                  reserved522;	//0xC490088C
	UINT32                                                  reserved523;	//0xC4900890
	UINT32                                                  reserved524;	//0xC4900894
	UINT32                                                  reserved525;	//0xC4900898
	UINT32                                                  reserved526;	//0xC490089C
	UINT32                                                  reserved527;	//0xC49008A0
	UINT32                                                  reserved528;	//0xC49008A4
	UINT32                                                  reserved529;	//0xC49008A8
	UINT32                                                  reserved530;	//0xC49008AC
	UINT32                                                  reserved531;	//0xC49008B0
	UINT32                                                  reserved532;	//0xC49008B4
	UINT32                                                  reserved533;	//0xC49008B8
	UINT32                                                  reserved534;	//0xC49008BC
	UINT32                                                  reserved535;	//0xC49008C0
	UINT32                                                  reserved536;	//0xC49008C4
	UINT32                                                  reserved537;	//0xC49008C8
	UINT32                                                  reserved538;	//0xC49008CC
	UINT32                                                  reserved539;	//0xC49008D0
	UINT32                                                  reserved540;	//0xC49008D4
	UINT32                                                  reserved541;	//0xC49008D8
	UINT32                                                  reserved542;	//0xC49008DC
	UINT32                                                  reserved543;	//0xC49008E0
	UINT32                                                  reserved544;	//0xC49008E4
	UINT32                                                  reserved545;	//0xC49008E8
	UINT32                                                  reserved546;	//0xC49008EC
	UINT32                                                  reserved547;	//0xC49008F0
	UINT32                                                  reserved548;	//0xC49008F4
	UINT32                                                  reserved549;	//0xC49008F8
	UINT32                                                  reserved550;	//0xC49008FC
	UINT32                                                  reserved551;	//0xC4900900
	UINT32                                                  reserved552;	//0xC4900904
	UINT32                                                  reserved553;	//0xC4900908
	UINT32                                                  reserved554;	//0xC490090C
	UINT32                                                  reserved555;	//0xC4900910
	UINT32                                                  reserved556;	//0xC4900914
	UINT32                                                  reserved557;	//0xC4900918
	UINT32                                                  reserved558;	//0xC490091C
	UINT32                                                  reserved559;	//0xC4900920
	UINT32                                                  reserved560;	//0xC4900924
	UINT32                                                  reserved561;	//0xC4900928
	UINT32                                                  reserved562;	//0xC490092C
	UINT32                                                  reserved563;	//0xC4900930
	UINT32                                                  reserved564;	//0xC4900934
	UINT32                                                  reserved565;	//0xC4900938
	UINT32                                                  reserved566;	//0xC490093C
	UINT32                                                  reserved567;	//0xC4900940
	UINT32                                                  reserved568;	//0xC4900944
	UINT32                                                  reserved569;	//0xC4900948
	UINT32                                                  reserved570;	//0xC490094C
	UINT32                                                  reserved571;	//0xC4900950
	UINT32                                                  reserved572;	//0xC4900954
	UINT32                                                  reserved573;	//0xC4900958
	UINT32                                                  reserved574;	//0xC490095C
	UINT32                                                  reserved575;	//0xC4900960
	UINT32                                                  reserved576;	//0xC4900964
	UINT32                                                  reserved577;	//0xC4900968
	UINT32                                                  reserved578;	//0xC490096C
	UINT32                                                  reserved579;	//0xC4900970
	UINT32                                                  reserved580;	//0xC4900974
	UINT32                                                  reserved581;	//0xC4900978
	UINT32                                                  reserved582;	//0xC490097C
	UINT32                                                  reserved583;	//0xC4900980
	UINT32                                                  reserved584;	//0xC4900984
	UINT32                                                  reserved585;	//0xC4900988
	UINT32                                                  reserved586;	//0xC490098C
	UINT32                                                  reserved587;	//0xC4900990
	UINT32                                                  reserved588;	//0xC4900994
	UINT32                                                  reserved589;	//0xC4900998
	UINT32                                                  reserved590;	//0xC490099C
	UINT32                                                  reserved591;	//0xC49009A0
	UINT32                                                  reserved592;	//0xC49009A4
	UINT32                                                  reserved593;	//0xC49009A8
	UINT32                                                  reserved594;	//0xC49009AC
	UINT32                                                  reserved595;	//0xC49009B0
	UINT32                                                  reserved596;	//0xC49009B4
	UINT32                                                  reserved597;	//0xC49009B8
	UINT32                                                  reserved598;	//0xC49009BC
	UINT32                                                  reserved599;	//0xC49009C0
	UINT32                                                  reserved600;	//0xC49009C4
	UINT32                                                  reserved601;	//0xC49009C8
	UINT32                                                  reserved602;	//0xC49009CC
	UINT32                                                  reserved603;	//0xC49009D0
	UINT32                                                  reserved604;	//0xC49009D4
	UINT32                                                  reserved605;	//0xC49009D8
	UINT32                                                  reserved606;	//0xC49009DC
	UINT32                                                  reserved607;	//0xC49009E0
	UINT32                                                  reserved608;	//0xC49009E4
	UINT32                                                  reserved609;	//0xC49009E8
	UINT32                                                  reserved610;	//0xC49009EC
	UINT32                                                  reserved611;	//0xC49009F0
	UINT32                                                  reserved612;	//0xC49009F4
	UINT32                                                  reserved613;	//0xC49009F8
	UINT32                                                  reserved614;	//0xC49009FC
	UINT32                                                  reserved615;	//0xC4900A00
	UINT32                                                  reserved616;	//0xC4900A04
	UINT32                                                  reserved617;	//0xC4900A08
	UINT32                                                  reserved618;	//0xC4900A0C
	UINT32                                                  reserved619;	//0xC4900A10
	UINT32                                                  reserved620;	//0xC4900A14
	UINT32                                                  reserved621;	//0xC4900A18
	UINT32                                                  reserved622;	//0xC4900A1C
	UINT32                                                  reserved623;	//0xC4900A20
	UINT32                                                  reserved624;	//0xC4900A24
	UINT32                                                  reserved625;	//0xC4900A28
	UINT32                                                  reserved626;	//0xC4900A2C
	UINT32                                                  reserved627;	//0xC4900A30
	UINT32                                                  reserved628;	//0xC4900A34
	UINT32                                                  reserved629;	//0xC4900A38
	UINT32                                                  reserved630;	//0xC4900A3C
	UINT32                                                  reserved631;	//0xC4900A40
	UINT32                                                  reserved632;	//0xC4900A44
	UINT32                                                  reserved633;	//0xC4900A48
	UINT32                                                  reserved634;	//0xC4900A4C
	UINT32                                                  reserved635;	//0xC4900A50
	UINT32                                                  reserved636;	//0xC4900A54
	UINT32                                                  reserved637;	//0xC4900A58
	UINT32                                                  reserved638;	//0xC4900A5C
	UINT32                                                  reserved639;	//0xC4900A60
	UINT32                                                  reserved640;	//0xC4900A64
	UINT32                                                  reserved641;	//0xC4900A68
	UINT32                                                  reserved642;	//0xC4900A6C
	UINT32                                                  reserved643;	//0xC4900A70
	UINT32                                                  reserved644;	//0xC4900A74
	UINT32                                                  reserved645;	//0xC4900A78
	UINT32                                                  reserved646;	//0xC4900A7C
	UINT32                                                  reserved647;	//0xC4900A80
	UINT32                                                  reserved648;	//0xC4900A84
	UINT32                                                  reserved649;	//0xC4900A88
	UINT32                                                  reserved650;	//0xC4900A8C
	UINT32                                                  reserved651;	//0xC4900A90
	UINT32                                                  reserved652;	//0xC4900A94
	UINT32                                                  reserved653;	//0xC4900A98
	UINT32                                                  reserved654;	//0xC4900A9C
	UINT32                                                  reserved655;	//0xC4900AA0
	UINT32                                                  reserved656;	//0xC4900AA4
	UINT32                                                  reserved657;	//0xC4900AA8
	UINT32                                                  reserved658;	//0xC4900AAC
	UINT32                                                  reserved659;	//0xC4900AB0
	UINT32                                                  reserved660;	//0xC4900AB4
	UINT32                                                  reserved661;	//0xC4900AB8
	UINT32                                                  reserved662;	//0xC4900ABC
	UINT32                                                  reserved663;	//0xC4900AC0
	UINT32                                                  reserved664;	//0xC4900AC4
	UINT32                                                  reserved665;	//0xC4900AC8
	UINT32                                                  reserved666;	//0xC4900ACC
	UINT32                                                  reserved667;	//0xC4900AD0
	UINT32                                                  reserved668;	//0xC4900AD4
	UINT32                                                  reserved669;	//0xC4900AD8
	UINT32                                                  reserved670;	//0xC4900ADC
	UINT32                                                  reserved671;	//0xC4900AE0
	UINT32                                                  reserved672;	//0xC4900AE4
	UINT32                                                  reserved673;	//0xC4900AE8
	UINT32                                                  reserved674;	//0xC4900AEC
	UINT32                                                  reserved675;	//0xC4900AF0
	UINT32                                                  reserved676;	//0xC4900AF4
	UINT32                                                  reserved677;	//0xC4900AF8
	UINT32                                                  reserved678;	//0xC4900AFC
	UINT32                                                  reserved679;	//0xC4900B00
	UINT32                                                  reserved680;	//0xC4900B04
	UINT32                                                  reserved681;	//0xC4900B08
	UINT32                                                  reserved682;	//0xC4900B0C
	UINT32                                                  reserved683;	//0xC4900B10
	UINT32                                                  reserved684;	//0xC4900B14
	UINT32                                                  reserved685;	//0xC4900B18
	UINT32                                                  reserved686;	//0xC4900B1C
	UINT32                                                  reserved687;	//0xC4900B20
	UINT32                                                  reserved688;	//0xC4900B24
	UINT32                                                  reserved689;	//0xC4900B28
	UINT32                                                  reserved690;	//0xC4900B2C
	UINT32                                                  reserved691;	//0xC4900B30
	UINT32                                                  reserved692;	//0xC4900B34
	UINT32                                                  reserved693;	//0xC4900B38
	UINT32                                                  reserved694;	//0xC4900B3C
	UINT32                                                  reserved695;	//0xC4900B40
	UINT32                                                  reserved696;	//0xC4900B44
	UINT32                                                  reserved697;	//0xC4900B48
	UINT32                                                  reserved698;	//0xC4900B4C
	UINT32                                                  reserved699;	//0xC4900B50
	UINT32                                                  reserved700;	//0xC4900B54
	UINT32                                                  reserved701;	//0xC4900B58
	UINT32                                                  reserved702;	//0xC4900B5C
	UINT32                                                  reserved703;	//0xC4900B60
	UINT32                                                  reserved704;	//0xC4900B64
	UINT32                                                  reserved705;	//0xC4900B68
	UINT32                                                  reserved706;	//0xC4900B6C
	UINT32                                                  reserved707;	//0xC4900B70
	UINT32                                                  reserved708;	//0xC4900B74
	UINT32                                                  reserved709;	//0xC4900B78
	UINT32                                                  reserved710;	//0xC4900B7C
	UINT32                                                  reserved711;	//0xC4900B80
	UINT32                                                  reserved712;	//0xC4900B84
	UINT32                                                  reserved713;	//0xC4900B88
	UINT32                                                  reserved714;	//0xC4900B8C
	UINT32                                                  reserved715;	//0xC4900B90
	UINT32                                                  reserved716;	//0xC4900B94
	UINT32                                                  reserved717;	//0xC4900B98
	UINT32                                                  reserved718;	//0xC4900B9C
	UINT32                                                  reserved719;	//0xC4900BA0
	UINT32                                                  reserved720;	//0xC4900BA4
	UINT32                                                  reserved721;	//0xC4900BA8
	UINT32                                                  reserved722;	//0xC4900BAC
	UINT32                                                  reserved723;	//0xC4900BB0
	UINT32                                                  reserved724;	//0xC4900BB4
	UINT32                                                  reserved725;	//0xC4900BB8
	UINT32                                                  reserved726;	//0xC4900BBC
	UINT32                                                  reserved727;	//0xC4900BC0
	UINT32                                                  reserved728;	//0xC4900BC4
	UINT32                                                  reserved729;	//0xC4900BC8
	UINT32                                                  reserved730;	//0xC4900BCC
	UINT32                                                  reserved731;	//0xC4900BD0
	UINT32                                                  reserved732;	//0xC4900BD4
	UINT32                                                  reserved733;	//0xC4900BD8
	UINT32                                                  reserved734;	//0xC4900BDC
	UINT32                                                  reserved735;	//0xC4900BE0
	UINT32                                                  reserved736;	//0xC4900BE4
	UINT32                                                  reserved737;	//0xC4900BE8
	UINT32                                                  reserved738;	//0xC4900BEC
	UINT32                                                  reserved739;	//0xC4900BF0
	UINT32                                                  reserved740;	//0xC4900BF4
	UINT32                                                  reserved741;	//0xC4900BF8
	UINT32                                                  reserved742;	//0xC4900BFC
	UINT32                                                  reserved743;	//0xC4900C00
	UINT32                                                  reserved744;	//0xC4900C04
	UINT32                                                  reserved745;	//0xC4900C08
	UINT32                                                  reserved746;	//0xC4900C0C
	UINT32                                                  reserved747;	//0xC4900C10
	UINT32                                                  reserved748;	//0xC4900C14
	UINT32                                                  reserved749;	//0xC4900C18
	UINT32                                                  reserved750;	//0xC4900C1C
	UINT32                                                  reserved751;	//0xC4900C20
	UINT32                                                  reserved752;	//0xC4900C24
	UINT32                                                  reserved753;	//0xC4900C28
	UINT32                                                  reserved754;	//0xC4900C2C
	UINT32                                                  reserved755;	//0xC4900C30
	UINT32                                                  reserved756;	//0xC4900C34
	UINT32                                                  reserved757;	//0xC4900C38
	UINT32                                                  reserved758;	//0xC4900C3C
	UINT32                                                  reserved759;	//0xC4900C40
	UINT32                                                  reserved760;	//0xC4900C44
	UINT32                                                  reserved761;	//0xC4900C48
	UINT32                                                  reserved762;	//0xC4900C4C
	UINT32                                                  reserved763;	//0xC4900C50
	UINT32                                                  reserved764;	//0xC4900C54
	UINT32                                                  reserved765;	//0xC4900C58
	UINT32                                                  reserved766;	//0xC4900C5C
	UINT32                                                  reserved767;	//0xC4900C60
	UINT32                                                  reserved768;	//0xC4900C64
	UINT32                                                  reserved769;	//0xC4900C68
	UINT32                                                  reserved770;	//0xC4900C6C
	UINT32                                                  reserved771;	//0xC4900C70
	UINT32                                                  reserved772;	//0xC4900C74
	UINT32                                                  reserved773;	//0xC4900C78
	UINT32                                                  reserved774;	//0xC4900C7C
	UINT32                                                  reserved775;	//0xC4900C80
	UINT32                                                  reserved776;	//0xC4900C84
	UINT32                                                  reserved777;	//0xC4900C88
	UINT32                                                  reserved778;	//0xC4900C8C
	UINT32                                                  reserved779;	//0xC4900C90
	UINT32                                                  reserved780;	//0xC4900C94
	UINT32                                                  reserved781;	//0xC4900C98
	UINT32                                                  reserved782;	//0xC4900C9C
	UINT32                                                  reserved783;	//0xC4900CA0
	UINT32                                                  reserved784;	//0xC4900CA4
	UINT32                                                  reserved785;	//0xC4900CA8
	UINT32                                                  reserved786;	//0xC4900CAC
	UINT32                                                  reserved787;	//0xC4900CB0
	UINT32                                                  reserved788;	//0xC4900CB4
	UINT32                                                  reserved789;	//0xC4900CB8
	UINT32                                                  reserved790;	//0xC4900CBC
	UINT32                                                  reserved791;	//0xC4900CC0
	UINT32                                                  reserved792;	//0xC4900CC4
	UINT32                                                  reserved793;	//0xC4900CC8
	UINT32                                                  reserved794;	//0xC4900CCC
	UINT32                                                  reserved795;	//0xC4900CD0
	UINT32                                                  reserved796;	//0xC4900CD4
	UINT32                                                  reserved797;	//0xC4900CD8
	UINT32                                                  reserved798;	//0xC4900CDC
	UINT32                                                  reserved799;	//0xC4900CE0
	UINT32                                                  reserved800;	//0xC4900CE4
	UINT32                                                  reserved801;	//0xC4900CE8
	UINT32                                                  reserved802;	//0xC4900CEC
	UINT32                                                  reserved803;	//0xC4900CF0
	UINT32                                                  reserved804;	//0xC4900CF4
	UINT32                                                  reserved805;	//0xC4900CF8
	UINT32                                                  reserved806;	//0xC4900CFC
	UINT32                                                  reserved807;	//0xC4900D00
	UINT32                                                  reserved808;	//0xC4900D04
	UINT32                                                  reserved809;	//0xC4900D08
	UINT32                                                  reserved810;	//0xC4900D0C
	UINT32                                                  reserved811;	//0xC4900D10
	UINT32                                                  reserved812;	//0xC4900D14
	UINT32                                                  reserved813;	//0xC4900D18
	UINT32                                                  reserved814;	//0xC4900D1C
	UINT32                                                  reserved815;	//0xC4900D20
	UINT32                                                  reserved816;	//0xC4900D24
	UINT32                                                  reserved817;	//0xC4900D28
	UINT32                                                  reserved818;	//0xC4900D2C
	UINT32                                                  reserved819;	//0xC4900D30
	UINT32                                                  reserved820;	//0xC4900D34
	UINT32                                                  reserved821;	//0xC4900D38
	UINT32                                                  reserved822;	//0xC4900D3C
	UINT32                                                  reserved823;	//0xC4900D40
	UINT32                                                  reserved824;	//0xC4900D44
	UINT32                                                  reserved825;	//0xC4900D48
	UINT32                                                  reserved826;	//0xC4900D4C
	UINT32                                                  reserved827;	//0xC4900D50
	UINT32                                                  reserved828;	//0xC4900D54
	UINT32                                                  reserved829;	//0xC4900D58
	UINT32                                                  reserved830;	//0xC4900D5C
	UINT32                                                  reserved831;	//0xC4900D60
	UINT32                                                  reserved832;	//0xC4900D64
	UINT32                                                  reserved833;	//0xC4900D68
	UINT32                                                  reserved834;	//0xC4900D6C
	UINT32                                                  reserved835;	//0xC4900D70
	UINT32                                                  reserved836;	//0xC4900D74
	UINT32                                                  reserved837;	//0xC4900D78
	UINT32                                                  reserved838;	//0xC4900D7C
	UINT32                                                  reserved839;	//0xC4900D80
	UINT32                                                  reserved840;	//0xC4900D84
	UINT32                                                  reserved841;	//0xC4900D88
	UINT32                                                  reserved842;	//0xC4900D8C
	UINT32                                                  reserved843;	//0xC4900D90
	UINT32                                                  reserved844;	//0xC4900D94
	UINT32                                                  reserved845;	//0xC4900D98
	UINT32                                                  reserved846;	//0xC4900D9C
	UINT32                                                  reserved847;	//0xC4900DA0
	UINT32                                                  reserved848;	//0xC4900DA4
	UINT32                                                  reserved849;	//0xC4900DA8
	UINT32                                                  reserved850;	//0xC4900DAC
	UINT32                                                  reserved851;	//0xC4900DB0
	UINT32                                                  reserved852;	//0xC4900DB4
	UINT32                                                  reserved853;	//0xC4900DB8
	UINT32                                                  reserved854;	//0xC4900DBC
	UINT32                                                  reserved855;	//0xC4900DC0
	UINT32                                                  reserved856;	//0xC4900DC4
	UINT32                                                  reserved857;	//0xC4900DC8
	UINT32                                                  reserved858;	//0xC4900DCC
	UINT32                                                  reserved859;	//0xC4900DD0
	UINT32                                                  reserved860;	//0xC4900DD4
	UINT32                                                  reserved861;	//0xC4900DD8
	UINT32                                                  reserved862;	//0xC4900DDC
	UINT32                                                  reserved863;	//0xC4900DE0
	UINT32                                                  reserved864;	//0xC4900DE4
	UINT32                                                  reserved865;	//0xC4900DE8
	UINT32                                                  reserved866;	//0xC4900DEC
	UINT32                                                  reserved867;	//0xC4900DF0
	UINT32                                                  reserved868;	//0xC4900DF4
	UINT32                                                  reserved869;	//0xC4900DF8
	UINT32                                                  reserved870;	//0xC4900DFC
	UINT32                                                  reserved871;	//0xC4900E00
	UINT32                                                  reserved872;	//0xC4900E04
	UINT32                                                  reserved873;	//0xC4900E08
	UINT32                                                  reserved874;	//0xC4900E0C
	UINT32                                                  reserved875;	//0xC4900E10
	UINT32                                                  reserved876;	//0xC4900E14
	UINT32                                                  reserved877;	//0xC4900E18
	UINT32                                                  reserved878;	//0xC4900E1C
	UINT32                                                  reserved879;	//0xC4900E20
	UINT32                                                  reserved880;	//0xC4900E24
	UINT32                                                  reserved881;	//0xC4900E28
	UINT32                                                  reserved882;	//0xC4900E2C
	UINT32                                                  reserved883;	//0xC4900E30
	UINT32                                                  reserved884;	//0xC4900E34
	UINT32                                                  reserved885;	//0xC4900E38
	UINT32                                                  reserved886;	//0xC4900E3C
	UINT32                                                  reserved887;	//0xC4900E40
	UINT32                                                  reserved888;	//0xC4900E44
	UINT32                                                  reserved889;	//0xC4900E48
	UINT32                                                  reserved890;	//0xC4900E4C
	UINT32                                                  reserved891;	//0xC4900E50
	UINT32                                                  reserved892;	//0xC4900E54
	UINT32                                                  reserved893;	//0xC4900E58
	UINT32                                                  reserved894;	//0xC4900E5C
	UINT32                                                  reserved895;	//0xC4900E60
	UINT32                                                  reserved896;	//0xC4900E64
	UINT32                                                  reserved897;	//0xC4900E68
	UINT32                                                  reserved898;	//0xC4900E6C
	UINT32                                                  reserved899;	//0xC4900E70
	UINT32                                                  reserved900;	//0xC4900E74
	UINT32                                                  reserved901;	//0xC4900E78
	UINT32                                                  reserved902;	//0xC4900E7C
	UINT32                                                  reserved903;	//0xC4900E80
	UINT32                                                  reserved904;	//0xC4900E84
	UINT32                                                  reserved905;	//0xC4900E88
	UINT32                                                  reserved906;	//0xC4900E8C
	UINT32                                                  reserved907;	//0xC4900E90
	UINT32                                                  reserved908;	//0xC4900E94
	UINT32                                                  reserved909;	//0xC4900E98
	UINT32                                                  reserved910;	//0xC4900E9C
	UINT32                                                  reserved911;	//0xC4900EA0
	UINT32                                                  reserved912;	//0xC4900EA4
	UINT32                                                  reserved913;	//0xC4900EA8
	UINT32                                                  reserved914;	//0xC4900EAC
	UINT32                                                  reserved915;	//0xC4900EB0
	UINT32                                                  reserved916;	//0xC4900EB4
	UINT32                                                  reserved917;	//0xC4900EB8
	UINT32                                                  reserved918;	//0xC4900EBC
	UINT32                                                  reserved919;	//0xC4900EC0
	UINT32                                                  reserved920;	//0xC4900EC4
	UINT32                                                  reserved921;	//0xC4900EC8
	UINT32                                                  reserved922;	//0xC4900ECC
	UINT32                                                  reserved923;	//0xC4900ED0
	UINT32                                                  reserved924;	//0xC4900ED4
	UINT32                                                  reserved925;	//0xC4900ED8
	UINT32                                                  reserved926;	//0xC4900EDC
	UINT32                                                  reserved927;	//0xC4900EE0
	UINT32                                                  reserved928;	//0xC4900EE4
	UINT32                                                  reserved929;	//0xC4900EE8
	UINT32                                                  reserved930;	//0xC4900EEC
	UINT32                                                  reserved931;	//0xC4900EF0
	UINT32                                                  reserved932;	//0xC4900EF4
	UINT32                                                  reserved933;	//0xC4900EF8
	UINT32                                                  reserved934;	//0xC4900EFC
	UINT32                                                  reserved935;	//0xC4900F00
	UINT32                                                  reserved936;	//0xC4900F04
	UINT32                                                  reserved937;	//0xC4900F08
	UINT32                                                  reserved938;	//0xC4900F0C
	UINT32                                                  reserved939;	//0xC4900F10
	UINT32                                                  reserved940;	//0xC4900F14
	UINT32                                                  reserved941;	//0xC4900F18
	UINT32                                                  reserved942;	//0xC4900F1C
	UINT32                                                  reserved943;	//0xC4900F20
	UINT32                                                  reserved944;	//0xC4900F24
	UINT32                                                  reserved945;	//0xC4900F28
	UINT32                                                  reserved946;	//0xC4900F2C
	UINT32                                                  reserved947;	//0xC4900F30
	UINT32                                                  reserved948;	//0xC4900F34
	UINT32                                                  reserved949;	//0xC4900F38
	UINT32                                                  reserved950;	//0xC4900F3C
	UINT32                                                  reserved951;	//0xC4900F40
	UINT32                                                  reserved952;	//0xC4900F44
	UINT32                                                  reserved953;	//0xC4900F48
	UINT32                                                  reserved954;	//0xC4900F4C
	UINT32                                                  reserved955;	//0xC4900F50
	UINT32                                                  reserved956;	//0xC4900F54
	UINT32                                                  reserved957;	//0xC4900F58
	UINT32                                                  reserved958;	//0xC4900F5C
	UINT32                                                  reserved959;	//0xC4900F60
	UINT32                                                  reserved960;	//0xC4900F64
	UINT32                                                  reserved961;	//0xC4900F68
	UINT32                                                  reserved962;	//0xC4900F6C
	UINT32                                                  reserved963;	//0xC4900F70
	UINT32                                                  reserved964;	//0xC4900F74
	UINT32                                                  reserved965;	//0xC4900F78
	UINT32                                                  reserved966;	//0xC4900F7C
	UINT32                                                  reserved967;	//0xC4900F80
	UINT32                                                  reserved968;	//0xC4900F84
	UINT32                                                  reserved969;	//0xC4900F88
	UINT32                                                  reserved970;	//0xC4900F8C
	UINT32                                                  reserved971;	//0xC4900F90
	UINT32                                                  reserved972;	//0xC4900F94
	UINT32                                                  reserved973;	//0xC4900F98
	UINT32                                                  reserved974;	//0xC4900F9C
	UINT32                                                  reserved975;	//0xC4900FA0
	UINT32                                                  reserved976;	//0xC4900FA4
	UINT32                                                  reserved977;	//0xC4900FA8
	UINT32                                                  reserved978;	//0xC4900FAC
	UINT32                                                  reserved979;	//0xC4900FB0
	UINT32                                                  reserved980;	//0xC4900FB4
	UINT32                                                  reserved981;	//0xC4900FB8
	UINT32                                                  reserved982;	//0xC4900FBC
	UINT32                                                  reserved983;	//0xC4900FC0
	UINT32                                                  reserved984;	//0xC4900FC4
	UINT32                                                  reserved985;	//0xC4900FC8
	UINT32                                                  reserved986;	//0xC4900FCC
	UINT32                                                  reserved987;	//0xC4900FD0
	UINT32                                                  reserved988;	//0xC4900FD4
	UINT32                                                  reserved989;	//0xC4900FD8
	UINT32                                                  reserved990;	//0xC4900FDC
	UINT32                                                  reserved991;	//0xC4900FE0
	UINT32                                                  reserved992;	//0xC4900FE4
	UINT32                                                  reserved993;	//0xC4900FE8
	UINT32                                                  reserved994;	//0xC4900FEC
	UINT32                                                  reserved995;	//0xC4900FF0
	UINT32                                                  reserved996;	//0xC4900FF4
	UINT32                                                  reserved997;	//0xC4900FF8
	UINT32                                                  reserved998;	//0xC4900FFC
	REG_DDRC_M1_FIFO_RDY_T                                     fifo_rdy;	//0xC4901000
	REG_DDRC_M1_FIFO_STATUS_T                               fifo_status;	//0xC4901004
	REG_DDRC_M1_FIFO_CONF_T                                   fifo_conf;	//0xC4901008
	UINT32                                                  reserved999;	//0xC490100C
	REG_DDRC_M1_LIMITER_EN_T                                 limiter_en;	//0xC4901010
	REG_DDRC_M1_LIMITER_AW_THR_T                         limiter_aw_thr;	//0xC4901014
	REG_DDRC_M1_LIMITER_W_THR_T                           limiter_w_thr;	//0xC4901018
	UINT32                                                 reserved1000;	//0xC490101C
	UINT32                                                 reserved1001;	//0xC4901020
	REG_DDRC_M1_LIMITER_AR_THR_T                         limiter_ar_thr;	//0xC4901024
	REG_DDRC_M1_LIMITER_R_THR_T                           limiter_r_thr;	//0xC4901028
	UINT32                                                 reserved1002;	//0xC490102C
	UINT32                                                 reserved1003;	//0xC4901030
	UINT32                                                 reserved1004;	//0xC4901034
	UINT32                                                 reserved1005;	//0xC4901038
	UINT32                                                 reserved1006;	//0xC490103C
	UINT32                                                 reserved1007;	//0xC4901040
	UINT32                                                 reserved1008;	//0xC4901044
	UINT32                                                 reserved1009;	//0xC4901048
	UINT32                                                 reserved1010;	//0xC490104C
	UINT32                                                 reserved1011;	//0xC4901050
	UINT32                                                 reserved1012;	//0xC4901054
	UINT32                                                 reserved1013;	//0xC4901058
	UINT32                                                 reserved1014;	//0xC490105C
	UINT32                                                 reserved1015;	//0xC4901060
	UINT32                                                 reserved1016;	//0xC4901064
	UINT32                                                 reserved1017;	//0xC4901068
	UINT32                                                 reserved1018;	//0xC490106C
	UINT32                                                 reserved1019;	//0xC4901070
	UINT32                                                 reserved1020;	//0xC4901074
	UINT32                                                 reserved1021;	//0xC4901078
	UINT32                                                 reserved1022;	//0xC490107C
	UINT32                                                 reserved1023;	//0xC4901080
	UINT32                                                 reserved1024;	//0xC4901084
	UINT32                                                 reserved1025;	//0xC4901088
	UINT32                                                 reserved1026;	//0xC490108C
	UINT32                                                 reserved1027;	//0xC4901090
	UINT32                                                 reserved1028;	//0xC4901094
	UINT32                                                 reserved1029;	//0xC4901098
	UINT32                                                 reserved1030;	//0xC490109C
	UINT32                                                 reserved1031;	//0xC49010A0
	UINT32                                                 reserved1032;	//0xC49010A4
	UINT32                                                 reserved1033;	//0xC49010A8
	UINT32                                                 reserved1034;	//0xC49010AC
	UINT32                                                 reserved1035;	//0xC49010B0
	UINT32                                                 reserved1036;	//0xC49010B4
	UINT32                                                 reserved1037;	//0xC49010B8
	UINT32                                                 reserved1038;	//0xC49010BC
	UINT32                                                 reserved1039;	//0xC49010C0
	UINT32                                                 reserved1040;	//0xC49010C4
	UINT32                                                 reserved1041;	//0xC49010C8
	UINT32                                                 reserved1042;	//0xC49010CC
	UINT32                                                 reserved1043;	//0xC49010D0
	UINT32                                                 reserved1044;	//0xC49010D4
	UINT32                                                 reserved1045;	//0xC49010D8
	UINT32                                                 reserved1046;	//0xC49010DC
	UINT32                                                 reserved1047;	//0xC49010E0
	UINT32                                                 reserved1048;	//0xC49010E4
	UINT32                                                 reserved1049;	//0xC49010E8
	UINT32                                                 reserved1050;	//0xC49010EC
	UINT32                                                 reserved1051;	//0xC49010F0
	UINT32                                                 reserved1052;	//0xC49010F4
	UINT32                                                 reserved1053;	//0xC49010F8
	UINT32                                                 reserved1054;	//0xC49010FC
	REG_DDRC_M1_FIFO_MUX_T                                     fifo_mux;	//0xC4901100
	REG_DDRC_M1_FIFO_MUX_MAX_T                             fifo_mux_max;	//0xC4901104
	REG_DDRC_M1_FIFO_MUX_WR_PRT_T                       fifo_mux_wr_prt;	//0xC4901108
	REG_DDRC_M1_FIFO_MUX_RD_PRT_T                       fifo_mux_rd_prt;	//0xC490110C
	REG_DDRC_M1_FIFO_MUX_PRT_MAX_T                     fifo_mux_prt_max;	//0xC4901110
	UINT32                                                 reserved1055;	//0xC4901114
	UINT32                                                 reserved1056;	//0xC4901118
	UINT32                                                 reserved1057;	//0xC490111C
	UINT32                                                 reserved1058;	//0xC4901120
	UINT32                                                 reserved1059;	//0xC4901124
	UINT32                                                 reserved1060;	//0xC4901128
	UINT32                                                 reserved1061;	//0xC490112C
	UINT32                                                 reserved1062;	//0xC4901130
	UINT32                                                 reserved1063;	//0xC4901134
	UINT32                                                 reserved1064;	//0xC4901138
	UINT32                                                 reserved1065;	//0xC490113C
	UINT32                                                 reserved1066;	//0xC4901140
	UINT32                                                 reserved1067;	//0xC4901144
	UINT32                                                 reserved1068;	//0xC4901148
	UINT32                                                 reserved1069;	//0xC490114C
	UINT32                                                 reserved1070;	//0xC4901150
	UINT32                                                 reserved1071;	//0xC4901154
	UINT32                                                 reserved1072;	//0xC4901158
	UINT32                                                 reserved1073;	//0xC490115C
	UINT32                                                 reserved1074;	//0xC4901160
	UINT32                                                 reserved1075;	//0xC4901164
	UINT32                                                 reserved1076;	//0xC4901168
	UINT32                                                 reserved1077;	//0xC490116C
	UINT32                                                 reserved1078;	//0xC4901170
	UINT32                                                 reserved1079;	//0xC4901174
	UINT32                                                 reserved1080;	//0xC4901178
	UINT32                                                 reserved1081;	//0xC490117C
	UINT32                                                 reserved1082;	//0xC4901180
	UINT32                                                 reserved1083;	//0xC4901184
	UINT32                                                 reserved1084;	//0xC4901188
	UINT32                                                 reserved1085;	//0xC490118C
	UINT32                                                 reserved1086;	//0xC4901190
	UINT32                                                 reserved1087;	//0xC4901194
	UINT32                                                 reserved1088;	//0xC4901198
	UINT32                                                 reserved1089;	//0xC490119C
	UINT32                                                 reserved1090;	//0xC49011A0
	UINT32                                                 reserved1091;	//0xC49011A4
	UINT32                                                 reserved1092;	//0xC49011A8
	UINT32                                                 reserved1093;	//0xC49011AC
	UINT32                                                 reserved1094;	//0xC49011B0
	UINT32                                                 reserved1095;	//0xC49011B4
	UINT32                                                 reserved1096;	//0xC49011B8
	UINT32                                                 reserved1097;	//0xC49011BC
	UINT32                                                 reserved1098;	//0xC49011C0
	UINT32                                                 reserved1099;	//0xC49011C4
	UINT32                                                 reserved1100;	//0xC49011C8
	UINT32                                                 reserved1101;	//0xC49011CC
	UINT32                                                 reserved1102;	//0xC49011D0
	UINT32                                                 reserved1103;	//0xC49011D4
	UINT32                                                 reserved1104;	//0xC49011D8
	UINT32                                                 reserved1105;	//0xC49011DC
	UINT32                                                 reserved1106;	//0xC49011E0
	UINT32                                                 reserved1107;	//0xC49011E4
	UINT32                                                 reserved1108;	//0xC49011E8
	UINT32                                                 reserved1109;	//0xC49011EC
	UINT32                                                 reserved1110;	//0xC49011F0
	UINT32                                                 reserved1111;	//0xC49011F4
	UINT32                                                 reserved1112;	//0xC49011F8
	UINT32                                                 reserved1113;	//0xC49011FC
	UINT32                                                 reserved1114;	//0xC4901200
	UINT32                                                 reserved1115;	//0xC4901204
	UINT32                                                 reserved1116;	//0xC4901208
	UINT32                                                 reserved1117;	//0xC490120C
	UINT32                                                 reserved1118;	//0xC4901210
	UINT32                                                 reserved1119;	//0xC4901214
	UINT32                                                 reserved1120;	//0xC4901218
	UINT32                                                 reserved1121;	//0xC490121C
	UINT32                                                 reserved1122;	//0xC4901220
	UINT32                                                 reserved1123;	//0xC4901224
	UINT32                                                 reserved1124;	//0xC4901228
	UINT32                                                 reserved1125;	//0xC490122C
	UINT32                                                 reserved1126;	//0xC4901230
	UINT32                                                 reserved1127;	//0xC4901234
	UINT32                                                 reserved1128;	//0xC4901238
	UINT32                                                 reserved1129;	//0xC490123C
	UINT32                                                 reserved1130;	//0xC4901240
	UINT32                                                 reserved1131;	//0xC4901244
	UINT32                                                 reserved1132;	//0xC4901248
	UINT32                                                 reserved1133;	//0xC490124C
	UINT32                                                 reserved1134;	//0xC4901250
	UINT32                                                 reserved1135;	//0xC4901254
	UINT32                                                 reserved1136;	//0xC4901258
	UINT32                                                 reserved1137;	//0xC490125C
	UINT32                                                 reserved1138;	//0xC4901260
	UINT32                                                 reserved1139;	//0xC4901264
	UINT32                                                 reserved1140;	//0xC4901268
	UINT32                                                 reserved1141;	//0xC490126C
	UINT32                                                 reserved1142;	//0xC4901270
	UINT32                                                 reserved1143;	//0xC4901274
	UINT32                                                 reserved1144;	//0xC4901278
	UINT32                                                 reserved1145;	//0xC490127C
	UINT32                                                 reserved1146;	//0xC4901280
	UINT32                                                 reserved1147;	//0xC4901284
	UINT32                                                 reserved1148;	//0xC4901288
	UINT32                                                 reserved1149;	//0xC490128C
	UINT32                                                 reserved1150;	//0xC4901290
	UINT32                                                 reserved1151;	//0xC4901294
	UINT32                                                 reserved1152;	//0xC4901298
	UINT32                                                 reserved1153;	//0xC490129C
	UINT32                                                 reserved1154;	//0xC49012A0
	UINT32                                                 reserved1155;	//0xC49012A4
	UINT32                                                 reserved1156;	//0xC49012A8
	UINT32                                                 reserved1157;	//0xC49012AC
	UINT32                                                 reserved1158;	//0xC49012B0
	UINT32                                                 reserved1159;	//0xC49012B4
	UINT32                                                 reserved1160;	//0xC49012B8
	UINT32                                                 reserved1161;	//0xC49012BC
	UINT32                                                 reserved1162;	//0xC49012C0
	UINT32                                                 reserved1163;	//0xC49012C4
	UINT32                                                 reserved1164;	//0xC49012C8
	UINT32                                                 reserved1165;	//0xC49012CC
	UINT32                                                 reserved1166;	//0xC49012D0
	UINT32                                                 reserved1167;	//0xC49012D4
	UINT32                                                 reserved1168;	//0xC49012D8
	UINT32                                                 reserved1169;	//0xC49012DC
	UINT32                                                 reserved1170;	//0xC49012E0
	UINT32                                                 reserved1171;	//0xC49012E4
	UINT32                                                 reserved1172;	//0xC49012E8
	UINT32                                                 reserved1173;	//0xC49012EC
	UINT32                                                 reserved1174;	//0xC49012F0
	UINT32                                                 reserved1175;	//0xC49012F4
	UINT32                                                 reserved1176;	//0xC49012F8
	UINT32                                                 reserved1177;	//0xC49012FC
	UINT32                                                 reserved1178;	//0xC4901300
	UINT32                                                 reserved1179;	//0xC4901304
	UINT32                                                 reserved1180;	//0xC4901308
	UINT32                                                 reserved1181;	//0xC490130C
	UINT32                                                 reserved1182;	//0xC4901310
	UINT32                                                 reserved1183;	//0xC4901314
	UINT32                                                 reserved1184;	//0xC4901318
	UINT32                                                 reserved1185;	//0xC490131C
	UINT32                                                 reserved1186;	//0xC4901320
	UINT32                                                 reserved1187;	//0xC4901324
	UINT32                                                 reserved1188;	//0xC4901328
	UINT32                                                 reserved1189;	//0xC490132C
	UINT32                                                 reserved1190;	//0xC4901330
	UINT32                                                 reserved1191;	//0xC4901334
	UINT32                                                 reserved1192;	//0xC4901338
	UINT32                                                 reserved1193;	//0xC490133C
	UINT32                                                 reserved1194;	//0xC4901340
	UINT32                                                 reserved1195;	//0xC4901344
	UINT32                                                 reserved1196;	//0xC4901348
	UINT32                                                 reserved1197;	//0xC490134C
	UINT32                                                 reserved1198;	//0xC4901350
	UINT32                                                 reserved1199;	//0xC4901354
	UINT32                                                 reserved1200;	//0xC4901358
	UINT32                                                 reserved1201;	//0xC490135C
	UINT32                                                 reserved1202;	//0xC4901360
	UINT32                                                 reserved1203;	//0xC4901364
	UINT32                                                 reserved1204;	//0xC4901368
	UINT32                                                 reserved1205;	//0xC490136C
	UINT32                                                 reserved1206;	//0xC4901370
	UINT32                                                 reserved1207;	//0xC4901374
	UINT32                                                 reserved1208;	//0xC4901378
	UINT32                                                 reserved1209;	//0xC490137C
	UINT32                                                 reserved1210;	//0xC4901380
	UINT32                                                 reserved1211;	//0xC4901384
	UINT32                                                 reserved1212;	//0xC4901388
	UINT32                                                 reserved1213;	//0xC490138C
	UINT32                                                 reserved1214;	//0xC4901390
	UINT32                                                 reserved1215;	//0xC4901394
	UINT32                                                 reserved1216;	//0xC4901398
	UINT32                                                 reserved1217;	//0xC490139C
	UINT32                                                 reserved1218;	//0xC49013A0
	UINT32                                                 reserved1219;	//0xC49013A4
	UINT32                                                 reserved1220;	//0xC49013A8
	UINT32                                                 reserved1221;	//0xC49013AC
	UINT32                                                 reserved1222;	//0xC49013B0
	UINT32                                                 reserved1223;	//0xC49013B4
	UINT32                                                 reserved1224;	//0xC49013B8
	UINT32                                                 reserved1225;	//0xC49013BC
	UINT32                                                 reserved1226;	//0xC49013C0
	UINT32                                                 reserved1227;	//0xC49013C4
	UINT32                                                 reserved1228;	//0xC49013C8
	UINT32                                                 reserved1229;	//0xC49013CC
	UINT32                                                 reserved1230;	//0xC49013D0
	UINT32                                                 reserved1231;	//0xC49013D4
	UINT32                                                 reserved1232;	//0xC49013D8
	UINT32                                                 reserved1233;	//0xC49013DC
	UINT32                                                 reserved1234;	//0xC49013E0
	UINT32                                                 reserved1235;	//0xC49013E4
	UINT32                                                 reserved1236;	//0xC49013E8
	UINT32                                                 reserved1237;	//0xC49013EC
	UINT32                                                 reserved1238;	//0xC49013F0
	UINT32                                                 reserved1239;	//0xC49013F4
	UINT32                                                 reserved1240;	//0xC49013F8
	UINT32                                                 reserved1241;	//0xC49013FC
	UINT32                                                 reserved1242;	//0xC4901400
	UINT32                                                 reserved1243;	//0xC4901404
	UINT32                                                 reserved1244;	//0xC4901408
	UINT32                                                 reserved1245;	//0xC490140C
	UINT32                                                 reserved1246;	//0xC4901410
	UINT32                                                 reserved1247;	//0xC4901414
	UINT32                                                 reserved1248;	//0xC4901418
	UINT32                                                 reserved1249;	//0xC490141C
	UINT32                                                 reserved1250;	//0xC4901420
	UINT32                                                 reserved1251;	//0xC4901424
	UINT32                                                 reserved1252;	//0xC4901428
	UINT32                                                 reserved1253;	//0xC490142C
	UINT32                                                 reserved1254;	//0xC4901430
	UINT32                                                 reserved1255;	//0xC4901434
	UINT32                                                 reserved1256;	//0xC4901438
	UINT32                                                 reserved1257;	//0xC490143C
	UINT32                                                 reserved1258;	//0xC4901440
	UINT32                                                 reserved1259;	//0xC4901444
	UINT32                                                 reserved1260;	//0xC4901448
	UINT32                                                 reserved1261;	//0xC490144C
	UINT32                                                 reserved1262;	//0xC4901450
	UINT32                                                 reserved1263;	//0xC4901454
	UINT32                                                 reserved1264;	//0xC4901458
	UINT32                                                 reserved1265;	//0xC490145C
	UINT32                                                 reserved1266;	//0xC4901460
	UINT32                                                 reserved1267;	//0xC4901464
	UINT32                                                 reserved1268;	//0xC4901468
	UINT32                                                 reserved1269;	//0xC490146C
	UINT32                                                 reserved1270;	//0xC4901470
	UINT32                                                 reserved1271;	//0xC4901474
	UINT32                                                 reserved1272;	//0xC4901478
	UINT32                                                 reserved1273;	//0xC490147C
	UINT32                                                 reserved1274;	//0xC4901480
	UINT32                                                 reserved1275;	//0xC4901484
	UINT32                                                 reserved1276;	//0xC4901488
	UINT32                                                 reserved1277;	//0xC490148C
	UINT32                                                 reserved1278;	//0xC4901490
	UINT32                                                 reserved1279;	//0xC4901494
	UINT32                                                 reserved1280;	//0xC4901498
	UINT32                                                 reserved1281;	//0xC490149C
	UINT32                                                 reserved1282;	//0xC49014A0
	UINT32                                                 reserved1283;	//0xC49014A4
	UINT32                                                 reserved1284;	//0xC49014A8
	UINT32                                                 reserved1285;	//0xC49014AC
	UINT32                                                 reserved1286;	//0xC49014B0
	UINT32                                                 reserved1287;	//0xC49014B4
	UINT32                                                 reserved1288;	//0xC49014B8
	UINT32                                                 reserved1289;	//0xC49014BC
	UINT32                                                 reserved1290;	//0xC49014C0
	UINT32                                                 reserved1291;	//0xC49014C4
	UINT32                                                 reserved1292;	//0xC49014C8
	UINT32                                                 reserved1293;	//0xC49014CC
	UINT32                                                 reserved1294;	//0xC49014D0
	UINT32                                                 reserved1295;	//0xC49014D4
	UINT32                                                 reserved1296;	//0xC49014D8
	UINT32                                                 reserved1297;	//0xC49014DC
	UINT32                                                 reserved1298;	//0xC49014E0
	UINT32                                                 reserved1299;	//0xC49014E4
	UINT32                                                 reserved1300;	//0xC49014E8
	UINT32                                                 reserved1301;	//0xC49014EC
	UINT32                                                 reserved1302;	//0xC49014F0
	UINT32                                                 reserved1303;	//0xC49014F4
	UINT32                                                 reserved1304;	//0xC49014F8
	UINT32                                                 reserved1305;	//0xC49014FC
	UINT32                                                 reserved1306;	//0xC4901500
	UINT32                                                 reserved1307;	//0xC4901504
	UINT32                                                 reserved1308;	//0xC4901508
	UINT32                                                 reserved1309;	//0xC490150C
	UINT32                                                 reserved1310;	//0xC4901510
	UINT32                                                 reserved1311;	//0xC4901514
	UINT32                                                 reserved1312;	//0xC4901518
	UINT32                                                 reserved1313;	//0xC490151C
	UINT32                                                 reserved1314;	//0xC4901520
	UINT32                                                 reserved1315;	//0xC4901524
	UINT32                                                 reserved1316;	//0xC4901528
	UINT32                                                 reserved1317;	//0xC490152C
	UINT32                                                 reserved1318;	//0xC4901530
	UINT32                                                 reserved1319;	//0xC4901534
	UINT32                                                 reserved1320;	//0xC4901538
	UINT32                                                 reserved1321;	//0xC490153C
	UINT32                                                 reserved1322;	//0xC4901540
	UINT32                                                 reserved1323;	//0xC4901544
	UINT32                                                 reserved1324;	//0xC4901548
	UINT32                                                 reserved1325;	//0xC490154C
	UINT32                                                 reserved1326;	//0xC4901550
	UINT32                                                 reserved1327;	//0xC4901554
	UINT32                                                 reserved1328;	//0xC4901558
	UINT32                                                 reserved1329;	//0xC490155C
	UINT32                                                 reserved1330;	//0xC4901560
	UINT32                                                 reserved1331;	//0xC4901564
	UINT32                                                 reserved1332;	//0xC4901568
	UINT32                                                 reserved1333;	//0xC490156C
	UINT32                                                 reserved1334;	//0xC4901570
	UINT32                                                 reserved1335;	//0xC4901574
	UINT32                                                 reserved1336;	//0xC4901578
	UINT32                                                 reserved1337;	//0xC490157C
	UINT32                                                 reserved1338;	//0xC4901580
	UINT32                                                 reserved1339;	//0xC4901584
	UINT32                                                 reserved1340;	//0xC4901588
	UINT32                                                 reserved1341;	//0xC490158C
	UINT32                                                 reserved1342;	//0xC4901590
	UINT32                                                 reserved1343;	//0xC4901594
	UINT32                                                 reserved1344;	//0xC4901598
	UINT32                                                 reserved1345;	//0xC490159C
	UINT32                                                 reserved1346;	//0xC49015A0
	UINT32                                                 reserved1347;	//0xC49015A4
	UINT32                                                 reserved1348;	//0xC49015A8
	UINT32                                                 reserved1349;	//0xC49015AC
	UINT32                                                 reserved1350;	//0xC49015B0
	UINT32                                                 reserved1351;	//0xC49015B4
	UINT32                                                 reserved1352;	//0xC49015B8
	UINT32                                                 reserved1353;	//0xC49015BC
	UINT32                                                 reserved1354;	//0xC49015C0
	UINT32                                                 reserved1355;	//0xC49015C4
	UINT32                                                 reserved1356;	//0xC49015C8
	UINT32                                                 reserved1357;	//0xC49015CC
	UINT32                                                 reserved1358;	//0xC49015D0
	UINT32                                                 reserved1359;	//0xC49015D4
	UINT32                                                 reserved1360;	//0xC49015D8
	UINT32                                                 reserved1361;	//0xC49015DC
	UINT32                                                 reserved1362;	//0xC49015E0
	UINT32                                                 reserved1363;	//0xC49015E4
	UINT32                                                 reserved1364;	//0xC49015E8
	UINT32                                                 reserved1365;	//0xC49015EC
	UINT32                                                 reserved1366;	//0xC49015F0
	UINT32                                                 reserved1367;	//0xC49015F4
	UINT32                                                 reserved1368;	//0xC49015F8
	UINT32                                                 reserved1369;	//0xC49015FC
	UINT32                                                 reserved1370;	//0xC4901600
	UINT32                                                 reserved1371;	//0xC4901604
	UINT32                                                 reserved1372;	//0xC4901608
	UINT32                                                 reserved1373;	//0xC490160C
	UINT32                                                 reserved1374;	//0xC4901610
	UINT32                                                 reserved1375;	//0xC4901614
	UINT32                                                 reserved1376;	//0xC4901618
	UINT32                                                 reserved1377;	//0xC490161C
	UINT32                                                 reserved1378;	//0xC4901620
	UINT32                                                 reserved1379;	//0xC4901624
	UINT32                                                 reserved1380;	//0xC4901628
	UINT32                                                 reserved1381;	//0xC490162C
	UINT32                                                 reserved1382;	//0xC4901630
	UINT32                                                 reserved1383;	//0xC4901634
	UINT32                                                 reserved1384;	//0xC4901638
	UINT32                                                 reserved1385;	//0xC490163C
	UINT32                                                 reserved1386;	//0xC4901640
	UINT32                                                 reserved1387;	//0xC4901644
	UINT32                                                 reserved1388;	//0xC4901648
	UINT32                                                 reserved1389;	//0xC490164C
	UINT32                                                 reserved1390;	//0xC4901650
	UINT32                                                 reserved1391;	//0xC4901654
	UINT32                                                 reserved1392;	//0xC4901658
	UINT32                                                 reserved1393;	//0xC490165C
	UINT32                                                 reserved1394;	//0xC4901660
	UINT32                                                 reserved1395;	//0xC4901664
	UINT32                                                 reserved1396;	//0xC4901668
	UINT32                                                 reserved1397;	//0xC490166C
	UINT32                                                 reserved1398;	//0xC4901670
	UINT32                                                 reserved1399;	//0xC4901674
	UINT32                                                 reserved1400;	//0xC4901678
	UINT32                                                 reserved1401;	//0xC490167C
	UINT32                                                 reserved1402;	//0xC4901680
	UINT32                                                 reserved1403;	//0xC4901684
	UINT32                                                 reserved1404;	//0xC4901688
	UINT32                                                 reserved1405;	//0xC490168C
	UINT32                                                 reserved1406;	//0xC4901690
	UINT32                                                 reserved1407;	//0xC4901694
	UINT32                                                 reserved1408;	//0xC4901698
	UINT32                                                 reserved1409;	//0xC490169C
	UINT32                                                 reserved1410;	//0xC49016A0
	UINT32                                                 reserved1411;	//0xC49016A4
	UINT32                                                 reserved1412;	//0xC49016A8
	UINT32                                                 reserved1413;	//0xC49016AC
	UINT32                                                 reserved1414;	//0xC49016B0
	UINT32                                                 reserved1415;	//0xC49016B4
	UINT32                                                 reserved1416;	//0xC49016B8
	UINT32                                                 reserved1417;	//0xC49016BC
	UINT32                                                 reserved1418;	//0xC49016C0
	UINT32                                                 reserved1419;	//0xC49016C4
	UINT32                                                 reserved1420;	//0xC49016C8
	UINT32                                                 reserved1421;	//0xC49016CC
	UINT32                                                 reserved1422;	//0xC49016D0
	UINT32                                                 reserved1423;	//0xC49016D4
	UINT32                                                 reserved1424;	//0xC49016D8
	UINT32                                                 reserved1425;	//0xC49016DC
	UINT32                                                 reserved1426;	//0xC49016E0
	UINT32                                                 reserved1427;	//0xC49016E4
	UINT32                                                 reserved1428;	//0xC49016E8
	UINT32                                                 reserved1429;	//0xC49016EC
	UINT32                                                 reserved1430;	//0xC49016F0
	UINT32                                                 reserved1431;	//0xC49016F4
	UINT32                                                 reserved1432;	//0xC49016F8
	UINT32                                                 reserved1433;	//0xC49016FC
	UINT32                                                 reserved1434;	//0xC4901700
	UINT32                                                 reserved1435;	//0xC4901704
	UINT32                                                 reserved1436;	//0xC4901708
	UINT32                                                 reserved1437;	//0xC490170C
	UINT32                                                 reserved1438;	//0xC4901710
	UINT32                                                 reserved1439;	//0xC4901714
	UINT32                                                 reserved1440;	//0xC4901718
	UINT32                                                 reserved1441;	//0xC490171C
	UINT32                                                 reserved1442;	//0xC4901720
	UINT32                                                 reserved1443;	//0xC4901724
	UINT32                                                 reserved1444;	//0xC4901728
	UINT32                                                 reserved1445;	//0xC490172C
	UINT32                                                 reserved1446;	//0xC4901730
	UINT32                                                 reserved1447;	//0xC4901734
	UINT32                                                 reserved1448;	//0xC4901738
	UINT32                                                 reserved1449;	//0xC490173C
	UINT32                                                 reserved1450;	//0xC4901740
	UINT32                                                 reserved1451;	//0xC4901744
	UINT32                                                 reserved1452;	//0xC4901748
	UINT32                                                 reserved1453;	//0xC490174C
	UINT32                                                 reserved1454;	//0xC4901750
	UINT32                                                 reserved1455;	//0xC4901754
	UINT32                                                 reserved1456;	//0xC4901758
	UINT32                                                 reserved1457;	//0xC490175C
	UINT32                                                 reserved1458;	//0xC4901760
	UINT32                                                 reserved1459;	//0xC4901764
	UINT32                                                 reserved1460;	//0xC4901768
	UINT32                                                 reserved1461;	//0xC490176C
	UINT32                                                 reserved1462;	//0xC4901770
	UINT32                                                 reserved1463;	//0xC4901774
	UINT32                                                 reserved1464;	//0xC4901778
	UINT32                                                 reserved1465;	//0xC490177C
	UINT32                                                 reserved1466;	//0xC4901780
	UINT32                                                 reserved1467;	//0xC4901784
	UINT32                                                 reserved1468;	//0xC4901788
	UINT32                                                 reserved1469;	//0xC490178C
	UINT32                                                 reserved1470;	//0xC4901790
	UINT32                                                 reserved1471;	//0xC4901794
	UINT32                                                 reserved1472;	//0xC4901798
	UINT32                                                 reserved1473;	//0xC490179C
	UINT32                                                 reserved1474;	//0xC49017A0
	UINT32                                                 reserved1475;	//0xC49017A4
	UINT32                                                 reserved1476;	//0xC49017A8
	UINT32                                                 reserved1477;	//0xC49017AC
	UINT32                                                 reserved1478;	//0xC49017B0
	UINT32                                                 reserved1479;	//0xC49017B4
	UINT32                                                 reserved1480;	//0xC49017B8
	UINT32                                                 reserved1481;	//0xC49017BC
	UINT32                                                 reserved1482;	//0xC49017C0
	UINT32                                                 reserved1483;	//0xC49017C4
	UINT32                                                 reserved1484;	//0xC49017C8
	UINT32                                                 reserved1485;	//0xC49017CC
	UINT32                                                 reserved1486;	//0xC49017D0
	UINT32                                                 reserved1487;	//0xC49017D4
	UINT32                                                 reserved1488;	//0xC49017D8
	UINT32                                                 reserved1489;	//0xC49017DC
	UINT32                                                 reserved1490;	//0xC49017E0
	UINT32                                                 reserved1491;	//0xC49017E4
	UINT32                                                 reserved1492;	//0xC49017E8
	UINT32                                                 reserved1493;	//0xC49017EC
	UINT32                                                 reserved1494;	//0xC49017F0
	UINT32                                                 reserved1495;	//0xC49017F4
	UINT32                                                 reserved1496;	//0xC49017F8
	UINT32                                                 reserved1497;	//0xC49017FC
	UINT32                                                 reserved1498;	//0xC4901800
	UINT32                                                 reserved1499;	//0xC4901804
	UINT32                                                 reserved1500;	//0xC4901808
	UINT32                                                 reserved1501;	//0xC490180C
	UINT32                                                 reserved1502;	//0xC4901810
	UINT32                                                 reserved1503;	//0xC4901814
	UINT32                                                 reserved1504;	//0xC4901818
	UINT32                                                 reserved1505;	//0xC490181C
	UINT32                                                 reserved1506;	//0xC4901820
	UINT32                                                 reserved1507;	//0xC4901824
	UINT32                                                 reserved1508;	//0xC4901828
	UINT32                                                 reserved1509;	//0xC490182C
	UINT32                                                 reserved1510;	//0xC4901830
	UINT32                                                 reserved1511;	//0xC4901834
	UINT32                                                 reserved1512;	//0xC4901838
	UINT32                                                 reserved1513;	//0xC490183C
	UINT32                                                 reserved1514;	//0xC4901840
	UINT32                                                 reserved1515;	//0xC4901844
	UINT32                                                 reserved1516;	//0xC4901848
	UINT32                                                 reserved1517;	//0xC490184C
	UINT32                                                 reserved1518;	//0xC4901850
	UINT32                                                 reserved1519;	//0xC4901854
	UINT32                                                 reserved1520;	//0xC4901858
	UINT32                                                 reserved1521;	//0xC490185C
	UINT32                                                 reserved1522;	//0xC4901860
	UINT32                                                 reserved1523;	//0xC4901864
	UINT32                                                 reserved1524;	//0xC4901868
	UINT32                                                 reserved1525;	//0xC490186C
	UINT32                                                 reserved1526;	//0xC4901870
	UINT32                                                 reserved1527;	//0xC4901874
	UINT32                                                 reserved1528;	//0xC4901878
	UINT32                                                 reserved1529;	//0xC490187C
	UINT32                                                 reserved1530;	//0xC4901880
	UINT32                                                 reserved1531;	//0xC4901884
	UINT32                                                 reserved1532;	//0xC4901888
	UINT32                                                 reserved1533;	//0xC490188C
	UINT32                                                 reserved1534;	//0xC4901890
	UINT32                                                 reserved1535;	//0xC4901894
	UINT32                                                 reserved1536;	//0xC4901898
	UINT32                                                 reserved1537;	//0xC490189C
	UINT32                                                 reserved1538;	//0xC49018A0
	UINT32                                                 reserved1539;	//0xC49018A4
	UINT32                                                 reserved1540;	//0xC49018A8
	UINT32                                                 reserved1541;	//0xC49018AC
	UINT32                                                 reserved1542;	//0xC49018B0
	UINT32                                                 reserved1543;	//0xC49018B4
	UINT32                                                 reserved1544;	//0xC49018B8
	UINT32                                                 reserved1545;	//0xC49018BC
	UINT32                                                 reserved1546;	//0xC49018C0
	UINT32                                                 reserved1547;	//0xC49018C4
	UINT32                                                 reserved1548;	//0xC49018C8
	UINT32                                                 reserved1549;	//0xC49018CC
	UINT32                                                 reserved1550;	//0xC49018D0
	UINT32                                                 reserved1551;	//0xC49018D4
	UINT32                                                 reserved1552;	//0xC49018D8
	UINT32                                                 reserved1553;	//0xC49018DC
	UINT32                                                 reserved1554;	//0xC49018E0
	UINT32                                                 reserved1555;	//0xC49018E4
	UINT32                                                 reserved1556;	//0xC49018E8
	UINT32                                                 reserved1557;	//0xC49018EC
	UINT32                                                 reserved1558;	//0xC49018F0
	UINT32                                                 reserved1559;	//0xC49018F4
	UINT32                                                 reserved1560;	//0xC49018F8
	UINT32                                                 reserved1561;	//0xC49018FC
	UINT32                                                 reserved1562;	//0xC4901900
	UINT32                                                 reserved1563;	//0xC4901904
	UINT32                                                 reserved1564;	//0xC4901908
	UINT32                                                 reserved1565;	//0xC490190C
	UINT32                                                 reserved1566;	//0xC4901910
	UINT32                                                 reserved1567;	//0xC4901914
	UINT32                                                 reserved1568;	//0xC4901918
	UINT32                                                 reserved1569;	//0xC490191C
	UINT32                                                 reserved1570;	//0xC4901920
	UINT32                                                 reserved1571;	//0xC4901924
	UINT32                                                 reserved1572;	//0xC4901928
	UINT32                                                 reserved1573;	//0xC490192C
	UINT32                                                 reserved1574;	//0xC4901930
	UINT32                                                 reserved1575;	//0xC4901934
	UINT32                                                 reserved1576;	//0xC4901938
	UINT32                                                 reserved1577;	//0xC490193C
	UINT32                                                 reserved1578;	//0xC4901940
	UINT32                                                 reserved1579;	//0xC4901944
	UINT32                                                 reserved1580;	//0xC4901948
	UINT32                                                 reserved1581;	//0xC490194C
	UINT32                                                 reserved1582;	//0xC4901950
	UINT32                                                 reserved1583;	//0xC4901954
	UINT32                                                 reserved1584;	//0xC4901958
	UINT32                                                 reserved1585;	//0xC490195C
	UINT32                                                 reserved1586;	//0xC4901960
	UINT32                                                 reserved1587;	//0xC4901964
	UINT32                                                 reserved1588;	//0xC4901968
	UINT32                                                 reserved1589;	//0xC490196C
	UINT32                                                 reserved1590;	//0xC4901970
	UINT32                                                 reserved1591;	//0xC4901974
	UINT32                                                 reserved1592;	//0xC4901978
	UINT32                                                 reserved1593;	//0xC490197C
	UINT32                                                 reserved1594;	//0xC4901980
	UINT32                                                 reserved1595;	//0xC4901984
	UINT32                                                 reserved1596;	//0xC4901988
	UINT32                                                 reserved1597;	//0xC490198C
	UINT32                                                 reserved1598;	//0xC4901990
	UINT32                                                 reserved1599;	//0xC4901994
	UINT32                                                 reserved1600;	//0xC4901998
	UINT32                                                 reserved1601;	//0xC490199C
	UINT32                                                 reserved1602;	//0xC49019A0
	UINT32                                                 reserved1603;	//0xC49019A4
	UINT32                                                 reserved1604;	//0xC49019A8
	UINT32                                                 reserved1605;	//0xC49019AC
	UINT32                                                 reserved1606;	//0xC49019B0
	UINT32                                                 reserved1607;	//0xC49019B4
	UINT32                                                 reserved1608;	//0xC49019B8
	UINT32                                                 reserved1609;	//0xC49019BC
	UINT32                                                 reserved1610;	//0xC49019C0
	UINT32                                                 reserved1611;	//0xC49019C4
	UINT32                                                 reserved1612;	//0xC49019C8
	UINT32                                                 reserved1613;	//0xC49019CC
	UINT32                                                 reserved1614;	//0xC49019D0
	UINT32                                                 reserved1615;	//0xC49019D4
	UINT32                                                 reserved1616;	//0xC49019D8
	UINT32                                                 reserved1617;	//0xC49019DC
	UINT32                                                 reserved1618;	//0xC49019E0
	UINT32                                                 reserved1619;	//0xC49019E4
	UINT32                                                 reserved1620;	//0xC49019E8
	UINT32                                                 reserved1621;	//0xC49019EC
	UINT32                                                 reserved1622;	//0xC49019F0
	UINT32                                                 reserved1623;	//0xC49019F4
	UINT32                                                 reserved1624;	//0xC49019F8
	UINT32                                                 reserved1625;	//0xC49019FC
	UINT32                                                 reserved1626;	//0xC4901A00
	UINT32                                                 reserved1627;	//0xC4901A04
	UINT32                                                 reserved1628;	//0xC4901A08
	UINT32                                                 reserved1629;	//0xC4901A0C
	UINT32                                                 reserved1630;	//0xC4901A10
	UINT32                                                 reserved1631;	//0xC4901A14
	UINT32                                                 reserved1632;	//0xC4901A18
	UINT32                                                 reserved1633;	//0xC4901A1C
	UINT32                                                 reserved1634;	//0xC4901A20
	UINT32                                                 reserved1635;	//0xC4901A24
	UINT32                                                 reserved1636;	//0xC4901A28
	UINT32                                                 reserved1637;	//0xC4901A2C
	UINT32                                                 reserved1638;	//0xC4901A30
	UINT32                                                 reserved1639;	//0xC4901A34
	UINT32                                                 reserved1640;	//0xC4901A38
	UINT32                                                 reserved1641;	//0xC4901A3C
	UINT32                                                 reserved1642;	//0xC4901A40
	UINT32                                                 reserved1643;	//0xC4901A44
	UINT32                                                 reserved1644;	//0xC4901A48
	UINT32                                                 reserved1645;	//0xC4901A4C
	UINT32                                                 reserved1646;	//0xC4901A50
	UINT32                                                 reserved1647;	//0xC4901A54
	UINT32                                                 reserved1648;	//0xC4901A58
	UINT32                                                 reserved1649;	//0xC4901A5C
	UINT32                                                 reserved1650;	//0xC4901A60
	UINT32                                                 reserved1651;	//0xC4901A64
	UINT32                                                 reserved1652;	//0xC4901A68
	UINT32                                                 reserved1653;	//0xC4901A6C
	UINT32                                                 reserved1654;	//0xC4901A70
	UINT32                                                 reserved1655;	//0xC4901A74
	UINT32                                                 reserved1656;	//0xC4901A78
	UINT32                                                 reserved1657;	//0xC4901A7C
	UINT32                                                 reserved1658;	//0xC4901A80
	UINT32                                                 reserved1659;	//0xC4901A84
	UINT32                                                 reserved1660;	//0xC4901A88
	UINT32                                                 reserved1661;	//0xC4901A8C
	UINT32                                                 reserved1662;	//0xC4901A90
	UINT32                                                 reserved1663;	//0xC4901A94
	UINT32                                                 reserved1664;	//0xC4901A98
	UINT32                                                 reserved1665;	//0xC4901A9C
	UINT32                                                 reserved1666;	//0xC4901AA0
	UINT32                                                 reserved1667;	//0xC4901AA4
	UINT32                                                 reserved1668;	//0xC4901AA8
	UINT32                                                 reserved1669;	//0xC4901AAC
	UINT32                                                 reserved1670;	//0xC4901AB0
	UINT32                                                 reserved1671;	//0xC4901AB4
	UINT32                                                 reserved1672;	//0xC4901AB8
	UINT32                                                 reserved1673;	//0xC4901ABC
	UINT32                                                 reserved1674;	//0xC4901AC0
	UINT32                                                 reserved1675;	//0xC4901AC4
	UINT32                                                 reserved1676;	//0xC4901AC8
	UINT32                                                 reserved1677;	//0xC4901ACC
	UINT32                                                 reserved1678;	//0xC4901AD0
	UINT32                                                 reserved1679;	//0xC4901AD4
	UINT32                                                 reserved1680;	//0xC4901AD8
	UINT32                                                 reserved1681;	//0xC4901ADC
	UINT32                                                 reserved1682;	//0xC4901AE0
	UINT32                                                 reserved1683;	//0xC4901AE4
	UINT32                                                 reserved1684;	//0xC4901AE8
	UINT32                                                 reserved1685;	//0xC4901AEC
	UINT32                                                 reserved1686;	//0xC4901AF0
	UINT32                                                 reserved1687;	//0xC4901AF4
	UINT32                                                 reserved1688;	//0xC4901AF8
	UINT32                                                 reserved1689;	//0xC4901AFC
	UINT32                                                 reserved1690;	//0xC4901B00
	UINT32                                                 reserved1691;	//0xC4901B04
	UINT32                                                 reserved1692;	//0xC4901B08
	UINT32                                                 reserved1693;	//0xC4901B0C
	UINT32                                                 reserved1694;	//0xC4901B10
	UINT32                                                 reserved1695;	//0xC4901B14
	UINT32                                                 reserved1696;	//0xC4901B18
	UINT32                                                 reserved1697;	//0xC4901B1C
	UINT32                                                 reserved1698;	//0xC4901B20
	UINT32                                                 reserved1699;	//0xC4901B24
	UINT32                                                 reserved1700;	//0xC4901B28
	UINT32                                                 reserved1701;	//0xC4901B2C
	UINT32                                                 reserved1702;	//0xC4901B30
	UINT32                                                 reserved1703;	//0xC4901B34
	UINT32                                                 reserved1704;	//0xC4901B38
	UINT32                                                 reserved1705;	//0xC4901B3C
	UINT32                                                 reserved1706;	//0xC4901B40
	UINT32                                                 reserved1707;	//0xC4901B44
	UINT32                                                 reserved1708;	//0xC4901B48
	UINT32                                                 reserved1709;	//0xC4901B4C
	UINT32                                                 reserved1710;	//0xC4901B50
	UINT32                                                 reserved1711;	//0xC4901B54
	UINT32                                                 reserved1712;	//0xC4901B58
	UINT32                                                 reserved1713;	//0xC4901B5C
	UINT32                                                 reserved1714;	//0xC4901B60
	UINT32                                                 reserved1715;	//0xC4901B64
	UINT32                                                 reserved1716;	//0xC4901B68
	UINT32                                                 reserved1717;	//0xC4901B6C
	UINT32                                                 reserved1718;	//0xC4901B70
	UINT32                                                 reserved1719;	//0xC4901B74
	UINT32                                                 reserved1720;	//0xC4901B78
	UINT32                                                 reserved1721;	//0xC4901B7C
	UINT32                                                 reserved1722;	//0xC4901B80
	UINT32                                                 reserved1723;	//0xC4901B84
	UINT32                                                 reserved1724;	//0xC4901B88
	UINT32                                                 reserved1725;	//0xC4901B8C
	UINT32                                                 reserved1726;	//0xC4901B90
	UINT32                                                 reserved1727;	//0xC4901B94
	UINT32                                                 reserved1728;	//0xC4901B98
	UINT32                                                 reserved1729;	//0xC4901B9C
	UINT32                                                 reserved1730;	//0xC4901BA0
	UINT32                                                 reserved1731;	//0xC4901BA4
	UINT32                                                 reserved1732;	//0xC4901BA8
	UINT32                                                 reserved1733;	//0xC4901BAC
	UINT32                                                 reserved1734;	//0xC4901BB0
	UINT32                                                 reserved1735;	//0xC4901BB4
	UINT32                                                 reserved1736;	//0xC4901BB8
	UINT32                                                 reserved1737;	//0xC4901BBC
	UINT32                                                 reserved1738;	//0xC4901BC0
	UINT32                                                 reserved1739;	//0xC4901BC4
	UINT32                                                 reserved1740;	//0xC4901BC8
	UINT32                                                 reserved1741;	//0xC4901BCC
	UINT32                                                 reserved1742;	//0xC4901BD0
	UINT32                                                 reserved1743;	//0xC4901BD4
	UINT32                                                 reserved1744;	//0xC4901BD8
	UINT32                                                 reserved1745;	//0xC4901BDC
	UINT32                                                 reserved1746;	//0xC4901BE0
	UINT32                                                 reserved1747;	//0xC4901BE4
	UINT32                                                 reserved1748;	//0xC4901BE8
	UINT32                                                 reserved1749;	//0xC4901BEC
	UINT32                                                 reserved1750;	//0xC4901BF0
	UINT32                                                 reserved1751;	//0xC4901BF4
	UINT32                                                 reserved1752;	//0xC4901BF8
	UINT32                                                 reserved1753;	//0xC4901BFC
	UINT32                                                 reserved1754;	//0xC4901C00
	UINT32                                                 reserved1755;	//0xC4901C04
	UINT32                                                 reserved1756;	//0xC4901C08
	UINT32                                                 reserved1757;	//0xC4901C0C
	UINT32                                                 reserved1758;	//0xC4901C10
	UINT32                                                 reserved1759;	//0xC4901C14
	UINT32                                                 reserved1760;	//0xC4901C18
	UINT32                                                 reserved1761;	//0xC4901C1C
	UINT32                                                 reserved1762;	//0xC4901C20
	UINT32                                                 reserved1763;	//0xC4901C24
	UINT32                                                 reserved1764;	//0xC4901C28
	UINT32                                                 reserved1765;	//0xC4901C2C
	UINT32                                                 reserved1766;	//0xC4901C30
	UINT32                                                 reserved1767;	//0xC4901C34
	UINT32                                                 reserved1768;	//0xC4901C38
	UINT32                                                 reserved1769;	//0xC4901C3C
	UINT32                                                 reserved1770;	//0xC4901C40
	UINT32                                                 reserved1771;	//0xC4901C44
	UINT32                                                 reserved1772;	//0xC4901C48
	UINT32                                                 reserved1773;	//0xC4901C4C
	UINT32                                                 reserved1774;	//0xC4901C50
	UINT32                                                 reserved1775;	//0xC4901C54
	UINT32                                                 reserved1776;	//0xC4901C58
	UINT32                                                 reserved1777;	//0xC4901C5C
	UINT32                                                 reserved1778;	//0xC4901C60
	UINT32                                                 reserved1779;	//0xC4901C64
	UINT32                                                 reserved1780;	//0xC4901C68
	UINT32                                                 reserved1781;	//0xC4901C6C
	UINT32                                                 reserved1782;	//0xC4901C70
	UINT32                                                 reserved1783;	//0xC4901C74
	UINT32                                                 reserved1784;	//0xC4901C78
	UINT32                                                 reserved1785;	//0xC4901C7C
	UINT32                                                 reserved1786;	//0xC4901C80
	UINT32                                                 reserved1787;	//0xC4901C84
	UINT32                                                 reserved1788;	//0xC4901C88
	UINT32                                                 reserved1789;	//0xC4901C8C
	UINT32                                                 reserved1790;	//0xC4901C90
	UINT32                                                 reserved1791;	//0xC4901C94
	UINT32                                                 reserved1792;	//0xC4901C98
	UINT32                                                 reserved1793;	//0xC4901C9C
	UINT32                                                 reserved1794;	//0xC4901CA0
	UINT32                                                 reserved1795;	//0xC4901CA4
	UINT32                                                 reserved1796;	//0xC4901CA8
	UINT32                                                 reserved1797;	//0xC4901CAC
	UINT32                                                 reserved1798;	//0xC4901CB0
	UINT32                                                 reserved1799;	//0xC4901CB4
	UINT32                                                 reserved1800;	//0xC4901CB8
	UINT32                                                 reserved1801;	//0xC4901CBC
	UINT32                                                 reserved1802;	//0xC4901CC0
	UINT32                                                 reserved1803;	//0xC4901CC4
	UINT32                                                 reserved1804;	//0xC4901CC8
	UINT32                                                 reserved1805;	//0xC4901CCC
	UINT32                                                 reserved1806;	//0xC4901CD0
	UINT32                                                 reserved1807;	//0xC4901CD4
	UINT32                                                 reserved1808;	//0xC4901CD8
	UINT32                                                 reserved1809;	//0xC4901CDC
	UINT32                                                 reserved1810;	//0xC4901CE0
	UINT32                                                 reserved1811;	//0xC4901CE4
	UINT32                                                 reserved1812;	//0xC4901CE8
	UINT32                                                 reserved1813;	//0xC4901CEC
	UINT32                                                 reserved1814;	//0xC4901CF0
	UINT32                                                 reserved1815;	//0xC4901CF4
	UINT32                                                 reserved1816;	//0xC4901CF8
	UINT32                                                 reserved1817;	//0xC4901CFC
	UINT32                                                 reserved1818;	//0xC4901D00
	UINT32                                                 reserved1819;	//0xC4901D04
	UINT32                                                 reserved1820;	//0xC4901D08
	UINT32                                                 reserved1821;	//0xC4901D0C
	UINT32                                                 reserved1822;	//0xC4901D10
	UINT32                                                 reserved1823;	//0xC4901D14
	UINT32                                                 reserved1824;	//0xC4901D18
	UINT32                                                 reserved1825;	//0xC4901D1C
	UINT32                                                 reserved1826;	//0xC4901D20
	UINT32                                                 reserved1827;	//0xC4901D24
	UINT32                                                 reserved1828;	//0xC4901D28
	UINT32                                                 reserved1829;	//0xC4901D2C
	UINT32                                                 reserved1830;	//0xC4901D30
	UINT32                                                 reserved1831;	//0xC4901D34
	UINT32                                                 reserved1832;	//0xC4901D38
	UINT32                                                 reserved1833;	//0xC4901D3C
	UINT32                                                 reserved1834;	//0xC4901D40
	UINT32                                                 reserved1835;	//0xC4901D44
	UINT32                                                 reserved1836;	//0xC4901D48
	UINT32                                                 reserved1837;	//0xC4901D4C
	UINT32                                                 reserved1838;	//0xC4901D50
	UINT32                                                 reserved1839;	//0xC4901D54
	UINT32                                                 reserved1840;	//0xC4901D58
	UINT32                                                 reserved1841;	//0xC4901D5C
	UINT32                                                 reserved1842;	//0xC4901D60
	UINT32                                                 reserved1843;	//0xC4901D64
	UINT32                                                 reserved1844;	//0xC4901D68
	UINT32                                                 reserved1845;	//0xC4901D6C
	UINT32                                                 reserved1846;	//0xC4901D70
	UINT32                                                 reserved1847;	//0xC4901D74
	UINT32                                                 reserved1848;	//0xC4901D78
	UINT32                                                 reserved1849;	//0xC4901D7C
	UINT32                                                 reserved1850;	//0xC4901D80
	UINT32                                                 reserved1851;	//0xC4901D84
	UINT32                                                 reserved1852;	//0xC4901D88
	UINT32                                                 reserved1853;	//0xC4901D8C
	UINT32                                                 reserved1854;	//0xC4901D90
	UINT32                                                 reserved1855;	//0xC4901D94
	UINT32                                                 reserved1856;	//0xC4901D98
	UINT32                                                 reserved1857;	//0xC4901D9C
	UINT32                                                 reserved1858;	//0xC4901DA0
	UINT32                                                 reserved1859;	//0xC4901DA4
	UINT32                                                 reserved1860;	//0xC4901DA8
	UINT32                                                 reserved1861;	//0xC4901DAC
	UINT32                                                 reserved1862;	//0xC4901DB0
	UINT32                                                 reserved1863;	//0xC4901DB4
	UINT32                                                 reserved1864;	//0xC4901DB8
	UINT32                                                 reserved1865;	//0xC4901DBC
	UINT32                                                 reserved1866;	//0xC4901DC0
	UINT32                                                 reserved1867;	//0xC4901DC4
	UINT32                                                 reserved1868;	//0xC4901DC8
	UINT32                                                 reserved1869;	//0xC4901DCC
	UINT32                                                 reserved1870;	//0xC4901DD0
	UINT32                                                 reserved1871;	//0xC4901DD4
	UINT32                                                 reserved1872;	//0xC4901DD8
	UINT32                                                 reserved1873;	//0xC4901DDC
	UINT32                                                 reserved1874;	//0xC4901DE0
	UINT32                                                 reserved1875;	//0xC4901DE4
	UINT32                                                 reserved1876;	//0xC4901DE8
	UINT32                                                 reserved1877;	//0xC4901DEC
	UINT32                                                 reserved1878;	//0xC4901DF0
	UINT32                                                 reserved1879;	//0xC4901DF4
	UINT32                                                 reserved1880;	//0xC4901DF8
	UINT32                                                 reserved1881;	//0xC4901DFC
	UINT32                                                 reserved1882;	//0xC4901E00
	UINT32                                                 reserved1883;	//0xC4901E04
	UINT32                                                 reserved1884;	//0xC4901E08
	UINT32                                                 reserved1885;	//0xC4901E0C
	UINT32                                                 reserved1886;	//0xC4901E10
	UINT32                                                 reserved1887;	//0xC4901E14
	UINT32                                                 reserved1888;	//0xC4901E18
	UINT32                                                 reserved1889;	//0xC4901E1C
	UINT32                                                 reserved1890;	//0xC4901E20
	UINT32                                                 reserved1891;	//0xC4901E24
	UINT32                                                 reserved1892;	//0xC4901E28
	UINT32                                                 reserved1893;	//0xC4901E2C
	UINT32                                                 reserved1894;	//0xC4901E30
	UINT32                                                 reserved1895;	//0xC4901E34
	UINT32                                                 reserved1896;	//0xC4901E38
	UINT32                                                 reserved1897;	//0xC4901E3C
	UINT32                                                 reserved1898;	//0xC4901E40
	UINT32                                                 reserved1899;	//0xC4901E44
	UINT32                                                 reserved1900;	//0xC4901E48
	UINT32                                                 reserved1901;	//0xC4901E4C
	UINT32                                                 reserved1902;	//0xC4901E50
	UINT32                                                 reserved1903;	//0xC4901E54
	UINT32                                                 reserved1904;	//0xC4901E58
	UINT32                                                 reserved1905;	//0xC4901E5C
	UINT32                                                 reserved1906;	//0xC4901E60
	UINT32                                                 reserved1907;	//0xC4901E64
	UINT32                                                 reserved1908;	//0xC4901E68
	UINT32                                                 reserved1909;	//0xC4901E6C
	UINT32                                                 reserved1910;	//0xC4901E70
	UINT32                                                 reserved1911;	//0xC4901E74
	UINT32                                                 reserved1912;	//0xC4901E78
	UINT32                                                 reserved1913;	//0xC4901E7C
	UINT32                                                 reserved1914;	//0xC4901E80
	UINT32                                                 reserved1915;	//0xC4901E84
	UINT32                                                 reserved1916;	//0xC4901E88
	UINT32                                                 reserved1917;	//0xC4901E8C
	UINT32                                                 reserved1918;	//0xC4901E90
	UINT32                                                 reserved1919;	//0xC4901E94
	UINT32                                                 reserved1920;	//0xC4901E98
	UINT32                                                 reserved1921;	//0xC4901E9C
	UINT32                                                 reserved1922;	//0xC4901EA0
	UINT32                                                 reserved1923;	//0xC4901EA4
	UINT32                                                 reserved1924;	//0xC4901EA8
	UINT32                                                 reserved1925;	//0xC4901EAC
	UINT32                                                 reserved1926;	//0xC4901EB0
	UINT32                                                 reserved1927;	//0xC4901EB4
	UINT32                                                 reserved1928;	//0xC4901EB8
	UINT32                                                 reserved1929;	//0xC4901EBC
	UINT32                                                 reserved1930;	//0xC4901EC0
	UINT32                                                 reserved1931;	//0xC4901EC4
	UINT32                                                 reserved1932;	//0xC4901EC8
	UINT32                                                 reserved1933;	//0xC4901ECC
	UINT32                                                 reserved1934;	//0xC4901ED0
	UINT32                                                 reserved1935;	//0xC4901ED4
	UINT32                                                 reserved1936;	//0xC4901ED8
	UINT32                                                 reserved1937;	//0xC4901EDC
	UINT32                                                 reserved1938;	//0xC4901EE0
	UINT32                                                 reserved1939;	//0xC4901EE4
	UINT32                                                 reserved1940;	//0xC4901EE8
	UINT32                                                 reserved1941;	//0xC4901EEC
	UINT32                                                 reserved1942;	//0xC4901EF0
	UINT32                                                 reserved1943;	//0xC4901EF4
	UINT32                                                 reserved1944;	//0xC4901EF8
	UINT32                                                 reserved1945;	//0xC4901EFC
	UINT32                                                 reserved1946;	//0xC4901F00
	UINT32                                                 reserved1947;	//0xC4901F04
	UINT32                                                 reserved1948;	//0xC4901F08
	UINT32                                                 reserved1949;	//0xC4901F0C
	UINT32                                                 reserved1950;	//0xC4901F10
	UINT32                                                 reserved1951;	//0xC4901F14
	UINT32                                                 reserved1952;	//0xC4901F18
	UINT32                                                 reserved1953;	//0xC4901F1C
	UINT32                                                 reserved1954;	//0xC4901F20
	UINT32                                                 reserved1955;	//0xC4901F24
	UINT32                                                 reserved1956;	//0xC4901F28
	UINT32                                                 reserved1957;	//0xC4901F2C
	UINT32                                                 reserved1958;	//0xC4901F30
	UINT32                                                 reserved1959;	//0xC4901F34
	UINT32                                                 reserved1960;	//0xC4901F38
	UINT32                                                 reserved1961;	//0xC4901F3C
	UINT32                                                 reserved1962;	//0xC4901F40
	UINT32                                                 reserved1963;	//0xC4901F44
	UINT32                                                 reserved1964;	//0xC4901F48
	UINT32                                                 reserved1965;	//0xC4901F4C
	UINT32                                                 reserved1966;	//0xC4901F50
	UINT32                                                 reserved1967;	//0xC4901F54
	UINT32                                                 reserved1968;	//0xC4901F58
	UINT32                                                 reserved1969;	//0xC4901F5C
	UINT32                                                 reserved1970;	//0xC4901F60
	UINT32                                                 reserved1971;	//0xC4901F64
	UINT32                                                 reserved1972;	//0xC4901F68
	UINT32                                                 reserved1973;	//0xC4901F6C
	UINT32                                                 reserved1974;	//0xC4901F70
	UINT32                                                 reserved1975;	//0xC4901F74
	UINT32                                                 reserved1976;	//0xC4901F78
	UINT32                                                 reserved1977;	//0xC4901F7C
	UINT32                                                 reserved1978;	//0xC4901F80
	UINT32                                                 reserved1979;	//0xC4901F84
	UINT32                                                 reserved1980;	//0xC4901F88
	UINT32                                                 reserved1981;	//0xC4901F8C
	UINT32                                                 reserved1982;	//0xC4901F90
	UINT32                                                 reserved1983;	//0xC4901F94
	UINT32                                                 reserved1984;	//0xC4901F98
	UINT32                                                 reserved1985;	//0xC4901F9C
	UINT32                                                 reserved1986;	//0xC4901FA0
	UINT32                                                 reserved1987;	//0xC4901FA4
	UINT32                                                 reserved1988;	//0xC4901FA8
	UINT32                                                 reserved1989;	//0xC4901FAC
	UINT32                                                 reserved1990;	//0xC4901FB0
	UINT32                                                 reserved1991;	//0xC4901FB4
	UINT32                                                 reserved1992;	//0xC4901FB8
	UINT32                                                 reserved1993;	//0xC4901FBC
	UINT32                                                 reserved1994;	//0xC4901FC0
	UINT32                                                 reserved1995;	//0xC4901FC4
	UINT32                                                 reserved1996;	//0xC4901FC8
	UINT32                                                 reserved1997;	//0xC4901FCC
	UINT32                                                 reserved1998;	//0xC4901FD0
	UINT32                                                 reserved1999;	//0xC4901FD4
	UINT32                                                 reserved2000;	//0xC4901FD8
	UINT32                                                 reserved2001;	//0xC4901FDC
	UINT32                                                 reserved2002;	//0xC4901FE0
	UINT32                                                 reserved2003;	//0xC4901FE4
	UINT32                                                 reserved2004;	//0xC4901FE8
	UINT32                                                 reserved2005;	//0xC4901FEC
	UINT32                                                 reserved2006;	//0xC4901FF0
	UINT32                                                 reserved2007;	//0xC4901FF4
	UINT32                                                 reserved2008;	//0xC4901FF8
	UINT32                                                 reserved2009;	//0xC4901FFC
	REG_DDRC_M1_PQ_T                                                 pq;	//0xC4902000
	REG_DDRC_M1_BQ_T                                                 bq;	//0xC4902004
	REG_DDRC_M1_BQ_RW_THR_T                                   bq_rw_thr;	//0xC4902008
	REG_DDRC_M1_BQ_HYB_STV_T                                 bq_hyb_stv;	//0xC490200C
	UINT32                                                 reserved2010;	//0xC4902010
	UINT32                                                 reserved2011;	//0xC4902014
	UINT32                                                 reserved2012;	//0xC4902018
	UINT32                                                 reserved2013;	//0xC490201C
	UINT32                                                 reserved2014;	//0xC4902020
	UINT32                                                 reserved2015;	//0xC4902024
	UINT32                                                 reserved2016;	//0xC4902028
	UINT32                                                 reserved2017;	//0xC490202C
	UINT32                                                 reserved2018;	//0xC4902030
	UINT32                                                 reserved2019;	//0xC4902034
	UINT32                                                 reserved2020;	//0xC4902038
	UINT32                                                 reserved2021;	//0xC490203C
	UINT32                                                 reserved2022;	//0xC4902040
	UINT32                                                 reserved2023;	//0xC4902044
	UINT32                                                 reserved2024;	//0xC4902048
	UINT32                                                 reserved2025;	//0xC490204C
	UINT32                                                 reserved2026;	//0xC4902050
	UINT32                                                 reserved2027;	//0xC4902054
	UINT32                                                 reserved2028;	//0xC4902058
	UINT32                                                 reserved2029;	//0xC490205C
	UINT32                                                 reserved2030;	//0xC4902060
	UINT32                                                 reserved2031;	//0xC4902064
	UINT32                                                 reserved2032;	//0xC4902068
	UINT32                                                 reserved2033;	//0xC490206C
	UINT32                                                 reserved2034;	//0xC4902070
	UINT32                                                 reserved2035;	//0xC4902074
	UINT32                                                 reserved2036;	//0xC4902078
	UINT32                                                 reserved2037;	//0xC490207C
	UINT32                                                 reserved2038;	//0xC4902080
	UINT32                                                 reserved2039;	//0xC4902084
	UINT32                                                 reserved2040;	//0xC4902088
	UINT32                                                 reserved2041;	//0xC490208C
	UINT32                                                 reserved2042;	//0xC4902090
	UINT32                                                 reserved2043;	//0xC4902094
	UINT32                                                 reserved2044;	//0xC4902098
	UINT32                                                 reserved2045;	//0xC490209C
	UINT32                                                 reserved2046;	//0xC49020A0
	UINT32                                                 reserved2047;	//0xC49020A4
	UINT32                                                 reserved2048;	//0xC49020A8
	UINT32                                                 reserved2049;	//0xC49020AC
	UINT32                                                 reserved2050;	//0xC49020B0
	UINT32                                                 reserved2051;	//0xC49020B4
	UINT32                                                 reserved2052;	//0xC49020B8
	UINT32                                                 reserved2053;	//0xC49020BC
	UINT32                                                 reserved2054;	//0xC49020C0
	UINT32                                                 reserved2055;	//0xC49020C4
	UINT32                                                 reserved2056;	//0xC49020C8
	UINT32                                                 reserved2057;	//0xC49020CC
	UINT32                                                 reserved2058;	//0xC49020D0
	UINT32                                                 reserved2059;	//0xC49020D4
	UINT32                                                 reserved2060;	//0xC49020D8
	UINT32                                                 reserved2061;	//0xC49020DC
	UINT32                                                 reserved2062;	//0xC49020E0
	UINT32                                                 reserved2063;	//0xC49020E4
	UINT32                                                 reserved2064;	//0xC49020E8
	UINT32                                                 reserved2065;	//0xC49020EC
	UINT32                                                 reserved2066;	//0xC49020F0
	UINT32                                                 reserved2067;	//0xC49020F4
	UINT32                                                 reserved2068;	//0xC49020F8
	UINT32                                                 reserved2069;	//0xC49020FC
	UINT32                                                 reserved2070;	//0xC4902100
	UINT32                                                 reserved2071;	//0xC4902104
	UINT32                                                 reserved2072;	//0xC4902108
	UINT32                                                 reserved2073;	//0xC490210C
	UINT32                                                 reserved2074;	//0xC4902110
	UINT32                                                 reserved2075;	//0xC4902114
	UINT32                                                 reserved2076;	//0xC4902118
	UINT32                                                 reserved2077;	//0xC490211C
	UINT32                                                 reserved2078;	//0xC4902120
	UINT32                                                 reserved2079;	//0xC4902124
	UINT32                                                 reserved2080;	//0xC4902128
	UINT32                                                 reserved2081;	//0xC490212C
	UINT32                                                 reserved2082;	//0xC4902130
	UINT32                                                 reserved2083;	//0xC4902134
	UINT32                                                 reserved2084;	//0xC4902138
	UINT32                                                 reserved2085;	//0xC490213C
	UINT32                                                 reserved2086;	//0xC4902140
	UINT32                                                 reserved2087;	//0xC4902144
	UINT32                                                 reserved2088;	//0xC4902148
	UINT32                                                 reserved2089;	//0xC490214C
	UINT32                                                 reserved2090;	//0xC4902150
	UINT32                                                 reserved2091;	//0xC4902154
	UINT32                                                 reserved2092;	//0xC4902158
	UINT32                                                 reserved2093;	//0xC490215C
	UINT32                                                 reserved2094;	//0xC4902160
	UINT32                                                 reserved2095;	//0xC4902164
	UINT32                                                 reserved2096;	//0xC4902168
	UINT32                                                 reserved2097;	//0xC490216C
	UINT32                                                 reserved2098;	//0xC4902170
	UINT32                                                 reserved2099;	//0xC4902174
	UINT32                                                 reserved2100;	//0xC4902178
	UINT32                                                 reserved2101;	//0xC490217C
	UINT32                                                 reserved2102;	//0xC4902180
	UINT32                                                 reserved2103;	//0xC4902184
	UINT32                                                 reserved2104;	//0xC4902188
	UINT32                                                 reserved2105;	//0xC490218C
	UINT32                                                 reserved2106;	//0xC4902190
	UINT32                                                 reserved2107;	//0xC4902194
	UINT32                                                 reserved2108;	//0xC4902198
	UINT32                                                 reserved2109;	//0xC490219C
	UINT32                                                 reserved2110;	//0xC49021A0
	UINT32                                                 reserved2111;	//0xC49021A4
	UINT32                                                 reserved2112;	//0xC49021A8
	UINT32                                                 reserved2113;	//0xC49021AC
	UINT32                                                 reserved2114;	//0xC49021B0
	UINT32                                                 reserved2115;	//0xC49021B4
	UINT32                                                 reserved2116;	//0xC49021B8
	UINT32                                                 reserved2117;	//0xC49021BC
	UINT32                                                 reserved2118;	//0xC49021C0
	UINT32                                                 reserved2119;	//0xC49021C4
	UINT32                                                 reserved2120;	//0xC49021C8
	UINT32                                                 reserved2121;	//0xC49021CC
	UINT32                                                 reserved2122;	//0xC49021D0
	UINT32                                                 reserved2123;	//0xC49021D4
	UINT32                                                 reserved2124;	//0xC49021D8
	UINT32                                                 reserved2125;	//0xC49021DC
	UINT32                                                 reserved2126;	//0xC49021E0
	UINT32                                                 reserved2127;	//0xC49021E4
	UINT32                                                 reserved2128;	//0xC49021E8
	UINT32                                                 reserved2129;	//0xC49021EC
	UINT32                                                 reserved2130;	//0xC49021F0
	UINT32                                                 reserved2131;	//0xC49021F4
	UINT32                                                 reserved2132;	//0xC49021F8
	UINT32                                                 reserved2133;	//0xC49021FC
	UINT32                                                 reserved2134;	//0xC4902200
	UINT32                                                 reserved2135;	//0xC4902204
	UINT32                                                 reserved2136;	//0xC4902208
	UINT32                                                 reserved2137;	//0xC490220C
	UINT32                                                 reserved2138;	//0xC4902210
	UINT32                                                 reserved2139;	//0xC4902214
	UINT32                                                 reserved2140;	//0xC4902218
	UINT32                                                 reserved2141;	//0xC490221C
	UINT32                                                 reserved2142;	//0xC4902220
	UINT32                                                 reserved2143;	//0xC4902224
	UINT32                                                 reserved2144;	//0xC4902228
	UINT32                                                 reserved2145;	//0xC490222C
	UINT32                                                 reserved2146;	//0xC4902230
	UINT32                                                 reserved2147;	//0xC4902234
	UINT32                                                 reserved2148;	//0xC4902238
	UINT32                                                 reserved2149;	//0xC490223C
	UINT32                                                 reserved2150;	//0xC4902240
	UINT32                                                 reserved2151;	//0xC4902244
	UINT32                                                 reserved2152;	//0xC4902248
	UINT32                                                 reserved2153;	//0xC490224C
	UINT32                                                 reserved2154;	//0xC4902250
	UINT32                                                 reserved2155;	//0xC4902254
	UINT32                                                 reserved2156;	//0xC4902258
	UINT32                                                 reserved2157;	//0xC490225C
	UINT32                                                 reserved2158;	//0xC4902260
	UINT32                                                 reserved2159;	//0xC4902264
	UINT32                                                 reserved2160;	//0xC4902268
	UINT32                                                 reserved2161;	//0xC490226C
	UINT32                                                 reserved2162;	//0xC4902270
	UINT32                                                 reserved2163;	//0xC4902274
	UINT32                                                 reserved2164;	//0xC4902278
	UINT32                                                 reserved2165;	//0xC490227C
	UINT32                                                 reserved2166;	//0xC4902280
	UINT32                                                 reserved2167;	//0xC4902284
	UINT32                                                 reserved2168;	//0xC4902288
	UINT32                                                 reserved2169;	//0xC490228C
	UINT32                                                 reserved2170;	//0xC4902290
	UINT32                                                 reserved2171;	//0xC4902294
	UINT32                                                 reserved2172;	//0xC4902298
	UINT32                                                 reserved2173;	//0xC490229C
	UINT32                                                 reserved2174;	//0xC49022A0
	UINT32                                                 reserved2175;	//0xC49022A4
	UINT32                                                 reserved2176;	//0xC49022A8
	UINT32                                                 reserved2177;	//0xC49022AC
	UINT32                                                 reserved2178;	//0xC49022B0
	UINT32                                                 reserved2179;	//0xC49022B4
	UINT32                                                 reserved2180;	//0xC49022B8
	UINT32                                                 reserved2181;	//0xC49022BC
	UINT32                                                 reserved2182;	//0xC49022C0
	UINT32                                                 reserved2183;	//0xC49022C4
	UINT32                                                 reserved2184;	//0xC49022C8
	UINT32                                                 reserved2185;	//0xC49022CC
	UINT32                                                 reserved2186;	//0xC49022D0
	UINT32                                                 reserved2187;	//0xC49022D4
	UINT32                                                 reserved2188;	//0xC49022D8
	UINT32                                                 reserved2189;	//0xC49022DC
	UINT32                                                 reserved2190;	//0xC49022E0
	UINT32                                                 reserved2191;	//0xC49022E4
	UINT32                                                 reserved2192;	//0xC49022E8
	UINT32                                                 reserved2193;	//0xC49022EC
	UINT32                                                 reserved2194;	//0xC49022F0
	UINT32                                                 reserved2195;	//0xC49022F4
	UINT32                                                 reserved2196;	//0xC49022F8
	UINT32                                                 reserved2197;	//0xC49022FC
	UINT32                                                 reserved2198;	//0xC4902300
	UINT32                                                 reserved2199;	//0xC4902304
	UINT32                                                 reserved2200;	//0xC4902308
	UINT32                                                 reserved2201;	//0xC490230C
	UINT32                                                 reserved2202;	//0xC4902310
	UINT32                                                 reserved2203;	//0xC4902314
	UINT32                                                 reserved2204;	//0xC4902318
	UINT32                                                 reserved2205;	//0xC490231C
	UINT32                                                 reserved2206;	//0xC4902320
	UINT32                                                 reserved2207;	//0xC4902324
	UINT32                                                 reserved2208;	//0xC4902328
	UINT32                                                 reserved2209;	//0xC490232C
	UINT32                                                 reserved2210;	//0xC4902330
	UINT32                                                 reserved2211;	//0xC4902334
	UINT32                                                 reserved2212;	//0xC4902338
	UINT32                                                 reserved2213;	//0xC490233C
	UINT32                                                 reserved2214;	//0xC4902340
	UINT32                                                 reserved2215;	//0xC4902344
	UINT32                                                 reserved2216;	//0xC4902348
	UINT32                                                 reserved2217;	//0xC490234C
	UINT32                                                 reserved2218;	//0xC4902350
	UINT32                                                 reserved2219;	//0xC4902354
	UINT32                                                 reserved2220;	//0xC4902358
	UINT32                                                 reserved2221;	//0xC490235C
	UINT32                                                 reserved2222;	//0xC4902360
	UINT32                                                 reserved2223;	//0xC4902364
	UINT32                                                 reserved2224;	//0xC4902368
	UINT32                                                 reserved2225;	//0xC490236C
	UINT32                                                 reserved2226;	//0xC4902370
	UINT32                                                 reserved2227;	//0xC4902374
	UINT32                                                 reserved2228;	//0xC4902378
	UINT32                                                 reserved2229;	//0xC490237C
	UINT32                                                 reserved2230;	//0xC4902380
	UINT32                                                 reserved2231;	//0xC4902384
	UINT32                                                 reserved2232;	//0xC4902388
	UINT32                                                 reserved2233;	//0xC490238C
	UINT32                                                 reserved2234;	//0xC4902390
	UINT32                                                 reserved2235;	//0xC4902394
	UINT32                                                 reserved2236;	//0xC4902398
	UINT32                                                 reserved2237;	//0xC490239C
	UINT32                                                 reserved2238;	//0xC49023A0
	UINT32                                                 reserved2239;	//0xC49023A4
	UINT32                                                 reserved2240;	//0xC49023A8
	UINT32                                                 reserved2241;	//0xC49023AC
	UINT32                                                 reserved2242;	//0xC49023B0
	UINT32                                                 reserved2243;	//0xC49023B4
	UINT32                                                 reserved2244;	//0xC49023B8
	UINT32                                                 reserved2245;	//0xC49023BC
	UINT32                                                 reserved2246;	//0xC49023C0
	UINT32                                                 reserved2247;	//0xC49023C4
	UINT32                                                 reserved2248;	//0xC49023C8
	UINT32                                                 reserved2249;	//0xC49023CC
	UINT32                                                 reserved2250;	//0xC49023D0
	UINT32                                                 reserved2251;	//0xC49023D4
	UINT32                                                 reserved2252;	//0xC49023D8
	UINT32                                                 reserved2253;	//0xC49023DC
	UINT32                                                 reserved2254;	//0xC49023E0
	UINT32                                                 reserved2255;	//0xC49023E4
	UINT32                                                 reserved2256;	//0xC49023E8
	UINT32                                                 reserved2257;	//0xC49023EC
	UINT32                                                 reserved2258;	//0xC49023F0
	UINT32                                                 reserved2259;	//0xC49023F4
	UINT32                                                 reserved2260;	//0xC49023F8
	UINT32                                                 reserved2261;	//0xC49023FC
	UINT32                                                 reserved2262;	//0xC4902400
	UINT32                                                 reserved2263;	//0xC4902404
	UINT32                                                 reserved2264;	//0xC4902408
	UINT32                                                 reserved2265;	//0xC490240C
	UINT32                                                 reserved2266;	//0xC4902410
	UINT32                                                 reserved2267;	//0xC4902414
	UINT32                                                 reserved2268;	//0xC4902418
	UINT32                                                 reserved2269;	//0xC490241C
	UINT32                                                 reserved2270;	//0xC4902420
	UINT32                                                 reserved2271;	//0xC4902424
	UINT32                                                 reserved2272;	//0xC4902428
	UINT32                                                 reserved2273;	//0xC490242C
	UINT32                                                 reserved2274;	//0xC4902430
	UINT32                                                 reserved2275;	//0xC4902434
	UINT32                                                 reserved2276;	//0xC4902438
	UINT32                                                 reserved2277;	//0xC490243C
	UINT32                                                 reserved2278;	//0xC4902440
	UINT32                                                 reserved2279;	//0xC4902444
	UINT32                                                 reserved2280;	//0xC4902448
	UINT32                                                 reserved2281;	//0xC490244C
	UINT32                                                 reserved2282;	//0xC4902450
	UINT32                                                 reserved2283;	//0xC4902454
	UINT32                                                 reserved2284;	//0xC4902458
	UINT32                                                 reserved2285;	//0xC490245C
	UINT32                                                 reserved2286;	//0xC4902460
	UINT32                                                 reserved2287;	//0xC4902464
	UINT32                                                 reserved2288;	//0xC4902468
	UINT32                                                 reserved2289;	//0xC490246C
	UINT32                                                 reserved2290;	//0xC4902470
	UINT32                                                 reserved2291;	//0xC4902474
	UINT32                                                 reserved2292;	//0xC4902478
	UINT32                                                 reserved2293;	//0xC490247C
	UINT32                                                 reserved2294;	//0xC4902480
	UINT32                                                 reserved2295;	//0xC4902484
	UINT32                                                 reserved2296;	//0xC4902488
	UINT32                                                 reserved2297;	//0xC490248C
	UINT32                                                 reserved2298;	//0xC4902490
	UINT32                                                 reserved2299;	//0xC4902494
	UINT32                                                 reserved2300;	//0xC4902498
	UINT32                                                 reserved2301;	//0xC490249C
	UINT32                                                 reserved2302;	//0xC49024A0
	UINT32                                                 reserved2303;	//0xC49024A4
	UINT32                                                 reserved2304;	//0xC49024A8
	UINT32                                                 reserved2305;	//0xC49024AC
	UINT32                                                 reserved2306;	//0xC49024B0
	UINT32                                                 reserved2307;	//0xC49024B4
	UINT32                                                 reserved2308;	//0xC49024B8
	UINT32                                                 reserved2309;	//0xC49024BC
	UINT32                                                 reserved2310;	//0xC49024C0
	UINT32                                                 reserved2311;	//0xC49024C4
	UINT32                                                 reserved2312;	//0xC49024C8
	UINT32                                                 reserved2313;	//0xC49024CC
	UINT32                                                 reserved2314;	//0xC49024D0
	UINT32                                                 reserved2315;	//0xC49024D4
	UINT32                                                 reserved2316;	//0xC49024D8
	UINT32                                                 reserved2317;	//0xC49024DC
	UINT32                                                 reserved2318;	//0xC49024E0
	UINT32                                                 reserved2319;	//0xC49024E4
	UINT32                                                 reserved2320;	//0xC49024E8
	UINT32                                                 reserved2321;	//0xC49024EC
	UINT32                                                 reserved2322;	//0xC49024F0
	UINT32                                                 reserved2323;	//0xC49024F4
	UINT32                                                 reserved2324;	//0xC49024F8
	UINT32                                                 reserved2325;	//0xC49024FC
	UINT32                                                 reserved2326;	//0xC4902500
	UINT32                                                 reserved2327;	//0xC4902504
	UINT32                                                 reserved2328;	//0xC4902508
	UINT32                                                 reserved2329;	//0xC490250C
	UINT32                                                 reserved2330;	//0xC4902510
	UINT32                                                 reserved2331;	//0xC4902514
	UINT32                                                 reserved2332;	//0xC4902518
	UINT32                                                 reserved2333;	//0xC490251C
	UINT32                                                 reserved2334;	//0xC4902520
	UINT32                                                 reserved2335;	//0xC4902524
	UINT32                                                 reserved2336;	//0xC4902528
	UINT32                                                 reserved2337;	//0xC490252C
	UINT32                                                 reserved2338;	//0xC4902530
	UINT32                                                 reserved2339;	//0xC4902534
	UINT32                                                 reserved2340;	//0xC4902538
	UINT32                                                 reserved2341;	//0xC490253C
	UINT32                                                 reserved2342;	//0xC4902540
	UINT32                                                 reserved2343;	//0xC4902544
	UINT32                                                 reserved2344;	//0xC4902548
	UINT32                                                 reserved2345;	//0xC490254C
	UINT32                                                 reserved2346;	//0xC4902550
	UINT32                                                 reserved2347;	//0xC4902554
	UINT32                                                 reserved2348;	//0xC4902558
	UINT32                                                 reserved2349;	//0xC490255C
	UINT32                                                 reserved2350;	//0xC4902560
	UINT32                                                 reserved2351;	//0xC4902564
	UINT32                                                 reserved2352;	//0xC4902568
	UINT32                                                 reserved2353;	//0xC490256C
	UINT32                                                 reserved2354;	//0xC4902570
	UINT32                                                 reserved2355;	//0xC4902574
	UINT32                                                 reserved2356;	//0xC4902578
	UINT32                                                 reserved2357;	//0xC490257C
	UINT32                                                 reserved2358;	//0xC4902580
	UINT32                                                 reserved2359;	//0xC4902584
	UINT32                                                 reserved2360;	//0xC4902588
	UINT32                                                 reserved2361;	//0xC490258C
	UINT32                                                 reserved2362;	//0xC4902590
	UINT32                                                 reserved2363;	//0xC4902594
	UINT32                                                 reserved2364;	//0xC4902598
	UINT32                                                 reserved2365;	//0xC490259C
	UINT32                                                 reserved2366;	//0xC49025A0
	UINT32                                                 reserved2367;	//0xC49025A4
	UINT32                                                 reserved2368;	//0xC49025A8
	UINT32                                                 reserved2369;	//0xC49025AC
	UINT32                                                 reserved2370;	//0xC49025B0
	UINT32                                                 reserved2371;	//0xC49025B4
	UINT32                                                 reserved2372;	//0xC49025B8
	UINT32                                                 reserved2373;	//0xC49025BC
	UINT32                                                 reserved2374;	//0xC49025C0
	UINT32                                                 reserved2375;	//0xC49025C4
	UINT32                                                 reserved2376;	//0xC49025C8
	UINT32                                                 reserved2377;	//0xC49025CC
	UINT32                                                 reserved2378;	//0xC49025D0
	UINT32                                                 reserved2379;	//0xC49025D4
	UINT32                                                 reserved2380;	//0xC49025D8
	UINT32                                                 reserved2381;	//0xC49025DC
	UINT32                                                 reserved2382;	//0xC49025E0
	UINT32                                                 reserved2383;	//0xC49025E4
	UINT32                                                 reserved2384;	//0xC49025E8
	UINT32                                                 reserved2385;	//0xC49025EC
	UINT32                                                 reserved2386;	//0xC49025F0
	UINT32                                                 reserved2387;	//0xC49025F4
	UINT32                                                 reserved2388;	//0xC49025F8
	UINT32                                                 reserved2389;	//0xC49025FC
	UINT32                                                 reserved2390;	//0xC4902600
	UINT32                                                 reserved2391;	//0xC4902604
	UINT32                                                 reserved2392;	//0xC4902608
	UINT32                                                 reserved2393;	//0xC490260C
	UINT32                                                 reserved2394;	//0xC4902610
	UINT32                                                 reserved2395;	//0xC4902614
	UINT32                                                 reserved2396;	//0xC4902618
	UINT32                                                 reserved2397;	//0xC490261C
	UINT32                                                 reserved2398;	//0xC4902620
	UINT32                                                 reserved2399;	//0xC4902624
	UINT32                                                 reserved2400;	//0xC4902628
	UINT32                                                 reserved2401;	//0xC490262C
	UINT32                                                 reserved2402;	//0xC4902630
	UINT32                                                 reserved2403;	//0xC4902634
	UINT32                                                 reserved2404;	//0xC4902638
	UINT32                                                 reserved2405;	//0xC490263C
	UINT32                                                 reserved2406;	//0xC4902640
	UINT32                                                 reserved2407;	//0xC4902644
	UINT32                                                 reserved2408;	//0xC4902648
	UINT32                                                 reserved2409;	//0xC490264C
	UINT32                                                 reserved2410;	//0xC4902650
	UINT32                                                 reserved2411;	//0xC4902654
	UINT32                                                 reserved2412;	//0xC4902658
	UINT32                                                 reserved2413;	//0xC490265C
	UINT32                                                 reserved2414;	//0xC4902660
	UINT32                                                 reserved2415;	//0xC4902664
	UINT32                                                 reserved2416;	//0xC4902668
	UINT32                                                 reserved2417;	//0xC490266C
	UINT32                                                 reserved2418;	//0xC4902670
	UINT32                                                 reserved2419;	//0xC4902674
	UINT32                                                 reserved2420;	//0xC4902678
	UINT32                                                 reserved2421;	//0xC490267C
	UINT32                                                 reserved2422;	//0xC4902680
	UINT32                                                 reserved2423;	//0xC4902684
	UINT32                                                 reserved2424;	//0xC4902688
	UINT32                                                 reserved2425;	//0xC490268C
	UINT32                                                 reserved2426;	//0xC4902690
	UINT32                                                 reserved2427;	//0xC4902694
	UINT32                                                 reserved2428;	//0xC4902698
	UINT32                                                 reserved2429;	//0xC490269C
	UINT32                                                 reserved2430;	//0xC49026A0
	UINT32                                                 reserved2431;	//0xC49026A4
	UINT32                                                 reserved2432;	//0xC49026A8
	UINT32                                                 reserved2433;	//0xC49026AC
	UINT32                                                 reserved2434;	//0xC49026B0
	UINT32                                                 reserved2435;	//0xC49026B4
	UINT32                                                 reserved2436;	//0xC49026B8
	UINT32                                                 reserved2437;	//0xC49026BC
	UINT32                                                 reserved2438;	//0xC49026C0
	UINT32                                                 reserved2439;	//0xC49026C4
	UINT32                                                 reserved2440;	//0xC49026C8
	UINT32                                                 reserved2441;	//0xC49026CC
	UINT32                                                 reserved2442;	//0xC49026D0
	UINT32                                                 reserved2443;	//0xC49026D4
	UINT32                                                 reserved2444;	//0xC49026D8
	UINT32                                                 reserved2445;	//0xC49026DC
	UINT32                                                 reserved2446;	//0xC49026E0
	UINT32                                                 reserved2447;	//0xC49026E4
	UINT32                                                 reserved2448;	//0xC49026E8
	UINT32                                                 reserved2449;	//0xC49026EC
	UINT32                                                 reserved2450;	//0xC49026F0
	UINT32                                                 reserved2451;	//0xC49026F4
	UINT32                                                 reserved2452;	//0xC49026F8
	UINT32                                                 reserved2453;	//0xC49026FC
	UINT32                                                 reserved2454;	//0xC4902700
	UINT32                                                 reserved2455;	//0xC4902704
	UINT32                                                 reserved2456;	//0xC4902708
	UINT32                                                 reserved2457;	//0xC490270C
	UINT32                                                 reserved2458;	//0xC4902710
	UINT32                                                 reserved2459;	//0xC4902714
	UINT32                                                 reserved2460;	//0xC4902718
	UINT32                                                 reserved2461;	//0xC490271C
	UINT32                                                 reserved2462;	//0xC4902720
	UINT32                                                 reserved2463;	//0xC4902724
	UINT32                                                 reserved2464;	//0xC4902728
	UINT32                                                 reserved2465;	//0xC490272C
	UINT32                                                 reserved2466;	//0xC4902730
	UINT32                                                 reserved2467;	//0xC4902734
	UINT32                                                 reserved2468;	//0xC4902738
	UINT32                                                 reserved2469;	//0xC490273C
	UINT32                                                 reserved2470;	//0xC4902740
	UINT32                                                 reserved2471;	//0xC4902744
	UINT32                                                 reserved2472;	//0xC4902748
	UINT32                                                 reserved2473;	//0xC490274C
	UINT32                                                 reserved2474;	//0xC4902750
	UINT32                                                 reserved2475;	//0xC4902754
	UINT32                                                 reserved2476;	//0xC4902758
	UINT32                                                 reserved2477;	//0xC490275C
	UINT32                                                 reserved2478;	//0xC4902760
	UINT32                                                 reserved2479;	//0xC4902764
	UINT32                                                 reserved2480;	//0xC4902768
	UINT32                                                 reserved2481;	//0xC490276C
	UINT32                                                 reserved2482;	//0xC4902770
	UINT32                                                 reserved2483;	//0xC4902774
	UINT32                                                 reserved2484;	//0xC4902778
	UINT32                                                 reserved2485;	//0xC490277C
	UINT32                                                 reserved2486;	//0xC4902780
	UINT32                                                 reserved2487;	//0xC4902784
	UINT32                                                 reserved2488;	//0xC4902788
	UINT32                                                 reserved2489;	//0xC490278C
	UINT32                                                 reserved2490;	//0xC4902790
	UINT32                                                 reserved2491;	//0xC4902794
	UINT32                                                 reserved2492;	//0xC4902798
	UINT32                                                 reserved2493;	//0xC490279C
	UINT32                                                 reserved2494;	//0xC49027A0
	UINT32                                                 reserved2495;	//0xC49027A4
	UINT32                                                 reserved2496;	//0xC49027A8
	UINT32                                                 reserved2497;	//0xC49027AC
	UINT32                                                 reserved2498;	//0xC49027B0
	UINT32                                                 reserved2499;	//0xC49027B4
	UINT32                                                 reserved2500;	//0xC49027B8
	UINT32                                                 reserved2501;	//0xC49027BC
	UINT32                                                 reserved2502;	//0xC49027C0
	UINT32                                                 reserved2503;	//0xC49027C4
	UINT32                                                 reserved2504;	//0xC49027C8
	UINT32                                                 reserved2505;	//0xC49027CC
	UINT32                                                 reserved2506;	//0xC49027D0
	UINT32                                                 reserved2507;	//0xC49027D4
	UINT32                                                 reserved2508;	//0xC49027D8
	UINT32                                                 reserved2509;	//0xC49027DC
	UINT32                                                 reserved2510;	//0xC49027E0
	UINT32                                                 reserved2511;	//0xC49027E4
	UINT32                                                 reserved2512;	//0xC49027E8
	UINT32                                                 reserved2513;	//0xC49027EC
	UINT32                                                 reserved2514;	//0xC49027F0
	UINT32                                                 reserved2515;	//0xC49027F4
	UINT32                                                 reserved2516;	//0xC49027F8
	UINT32                                                 reserved2517;	//0xC49027FC
	UINT32                                                 reserved2518;	//0xC4902800
	UINT32                                                 reserved2519;	//0xC4902804
	UINT32                                                 reserved2520;	//0xC4902808
	UINT32                                                 reserved2521;	//0xC490280C
	UINT32                                                 reserved2522;	//0xC4902810
	UINT32                                                 reserved2523;	//0xC4902814
	UINT32                                                 reserved2524;	//0xC4902818
	UINT32                                                 reserved2525;	//0xC490281C
	UINT32                                                 reserved2526;	//0xC4902820
	UINT32                                                 reserved2527;	//0xC4902824
	UINT32                                                 reserved2528;	//0xC4902828
	UINT32                                                 reserved2529;	//0xC490282C
	UINT32                                                 reserved2530;	//0xC4902830
	UINT32                                                 reserved2531;	//0xC4902834
	UINT32                                                 reserved2532;	//0xC4902838
	UINT32                                                 reserved2533;	//0xC490283C
	UINT32                                                 reserved2534;	//0xC4902840
	UINT32                                                 reserved2535;	//0xC4902844
	UINT32                                                 reserved2536;	//0xC4902848
	UINT32                                                 reserved2537;	//0xC490284C
	UINT32                                                 reserved2538;	//0xC4902850
	UINT32                                                 reserved2539;	//0xC4902854
	UINT32                                                 reserved2540;	//0xC4902858
	UINT32                                                 reserved2541;	//0xC490285C
	UINT32                                                 reserved2542;	//0xC4902860
	UINT32                                                 reserved2543;	//0xC4902864
	UINT32                                                 reserved2544;	//0xC4902868
	UINT32                                                 reserved2545;	//0xC490286C
	UINT32                                                 reserved2546;	//0xC4902870
	UINT32                                                 reserved2547;	//0xC4902874
	UINT32                                                 reserved2548;	//0xC4902878
	UINT32                                                 reserved2549;	//0xC490287C
	UINT32                                                 reserved2550;	//0xC4902880
	UINT32                                                 reserved2551;	//0xC4902884
	UINT32                                                 reserved2552;	//0xC4902888
	UINT32                                                 reserved2553;	//0xC490288C
	UINT32                                                 reserved2554;	//0xC4902890
	UINT32                                                 reserved2555;	//0xC4902894
	UINT32                                                 reserved2556;	//0xC4902898
	UINT32                                                 reserved2557;	//0xC490289C
	UINT32                                                 reserved2558;	//0xC49028A0
	UINT32                                                 reserved2559;	//0xC49028A4
	UINT32                                                 reserved2560;	//0xC49028A8
	UINT32                                                 reserved2561;	//0xC49028AC
	UINT32                                                 reserved2562;	//0xC49028B0
	UINT32                                                 reserved2563;	//0xC49028B4
	UINT32                                                 reserved2564;	//0xC49028B8
	UINT32                                                 reserved2565;	//0xC49028BC
	UINT32                                                 reserved2566;	//0xC49028C0
	UINT32                                                 reserved2567;	//0xC49028C4
	UINT32                                                 reserved2568;	//0xC49028C8
	UINT32                                                 reserved2569;	//0xC49028CC
	UINT32                                                 reserved2570;	//0xC49028D0
	UINT32                                                 reserved2571;	//0xC49028D4
	UINT32                                                 reserved2572;	//0xC49028D8
	UINT32                                                 reserved2573;	//0xC49028DC
	UINT32                                                 reserved2574;	//0xC49028E0
	UINT32                                                 reserved2575;	//0xC49028E4
	UINT32                                                 reserved2576;	//0xC49028E8
	UINT32                                                 reserved2577;	//0xC49028EC
	UINT32                                                 reserved2578;	//0xC49028F0
	UINT32                                                 reserved2579;	//0xC49028F4
	UINT32                                                 reserved2580;	//0xC49028F8
	UINT32                                                 reserved2581;	//0xC49028FC
	UINT32                                                 reserved2582;	//0xC4902900
	UINT32                                                 reserved2583;	//0xC4902904
	UINT32                                                 reserved2584;	//0xC4902908
	UINT32                                                 reserved2585;	//0xC490290C
	UINT32                                                 reserved2586;	//0xC4902910
	UINT32                                                 reserved2587;	//0xC4902914
	UINT32                                                 reserved2588;	//0xC4902918
	UINT32                                                 reserved2589;	//0xC490291C
	UINT32                                                 reserved2590;	//0xC4902920
	UINT32                                                 reserved2591;	//0xC4902924
	UINT32                                                 reserved2592;	//0xC4902928
	UINT32                                                 reserved2593;	//0xC490292C
	UINT32                                                 reserved2594;	//0xC4902930
	UINT32                                                 reserved2595;	//0xC4902934
	UINT32                                                 reserved2596;	//0xC4902938
	UINT32                                                 reserved2597;	//0xC490293C
	UINT32                                                 reserved2598;	//0xC4902940
	UINT32                                                 reserved2599;	//0xC4902944
	UINT32                                                 reserved2600;	//0xC4902948
	UINT32                                                 reserved2601;	//0xC490294C
	UINT32                                                 reserved2602;	//0xC4902950
	UINT32                                                 reserved2603;	//0xC4902954
	UINT32                                                 reserved2604;	//0xC4902958
	UINT32                                                 reserved2605;	//0xC490295C
	UINT32                                                 reserved2606;	//0xC4902960
	UINT32                                                 reserved2607;	//0xC4902964
	UINT32                                                 reserved2608;	//0xC4902968
	UINT32                                                 reserved2609;	//0xC490296C
	UINT32                                                 reserved2610;	//0xC4902970
	UINT32                                                 reserved2611;	//0xC4902974
	UINT32                                                 reserved2612;	//0xC4902978
	UINT32                                                 reserved2613;	//0xC490297C
	UINT32                                                 reserved2614;	//0xC4902980
	UINT32                                                 reserved2615;	//0xC4902984
	UINT32                                                 reserved2616;	//0xC4902988
	UINT32                                                 reserved2617;	//0xC490298C
	UINT32                                                 reserved2618;	//0xC4902990
	UINT32                                                 reserved2619;	//0xC4902994
	UINT32                                                 reserved2620;	//0xC4902998
	UINT32                                                 reserved2621;	//0xC490299C
	UINT32                                                 reserved2622;	//0xC49029A0
	UINT32                                                 reserved2623;	//0xC49029A4
	UINT32                                                 reserved2624;	//0xC49029A8
	UINT32                                                 reserved2625;	//0xC49029AC
	UINT32                                                 reserved2626;	//0xC49029B0
	UINT32                                                 reserved2627;	//0xC49029B4
	UINT32                                                 reserved2628;	//0xC49029B8
	UINT32                                                 reserved2629;	//0xC49029BC
	UINT32                                                 reserved2630;	//0xC49029C0
	UINT32                                                 reserved2631;	//0xC49029C4
	UINT32                                                 reserved2632;	//0xC49029C8
	UINT32                                                 reserved2633;	//0xC49029CC
	UINT32                                                 reserved2634;	//0xC49029D0
	UINT32                                                 reserved2635;	//0xC49029D4
	UINT32                                                 reserved2636;	//0xC49029D8
	UINT32                                                 reserved2637;	//0xC49029DC
	UINT32                                                 reserved2638;	//0xC49029E0
	UINT32                                                 reserved2639;	//0xC49029E4
	UINT32                                                 reserved2640;	//0xC49029E8
	UINT32                                                 reserved2641;	//0xC49029EC
	UINT32                                                 reserved2642;	//0xC49029F0
	UINT32                                                 reserved2643;	//0xC49029F4
	UINT32                                                 reserved2644;	//0xC49029F8
	UINT32                                                 reserved2645;	//0xC49029FC
	UINT32                                                 reserved2646;	//0xC4902A00
	UINT32                                                 reserved2647;	//0xC4902A04
	UINT32                                                 reserved2648;	//0xC4902A08
	UINT32                                                 reserved2649;	//0xC4902A0C
	UINT32                                                 reserved2650;	//0xC4902A10
	UINT32                                                 reserved2651;	//0xC4902A14
	UINT32                                                 reserved2652;	//0xC4902A18
	UINT32                                                 reserved2653;	//0xC4902A1C
	UINT32                                                 reserved2654;	//0xC4902A20
	UINT32                                                 reserved2655;	//0xC4902A24
	UINT32                                                 reserved2656;	//0xC4902A28
	UINT32                                                 reserved2657;	//0xC4902A2C
	UINT32                                                 reserved2658;	//0xC4902A30
	UINT32                                                 reserved2659;	//0xC4902A34
	UINT32                                                 reserved2660;	//0xC4902A38
	UINT32                                                 reserved2661;	//0xC4902A3C
	UINT32                                                 reserved2662;	//0xC4902A40
	UINT32                                                 reserved2663;	//0xC4902A44
	UINT32                                                 reserved2664;	//0xC4902A48
	UINT32                                                 reserved2665;	//0xC4902A4C
	UINT32                                                 reserved2666;	//0xC4902A50
	UINT32                                                 reserved2667;	//0xC4902A54
	UINT32                                                 reserved2668;	//0xC4902A58
	UINT32                                                 reserved2669;	//0xC4902A5C
	UINT32                                                 reserved2670;	//0xC4902A60
	UINT32                                                 reserved2671;	//0xC4902A64
	UINT32                                                 reserved2672;	//0xC4902A68
	UINT32                                                 reserved2673;	//0xC4902A6C
	UINT32                                                 reserved2674;	//0xC4902A70
	UINT32                                                 reserved2675;	//0xC4902A74
	UINT32                                                 reserved2676;	//0xC4902A78
	UINT32                                                 reserved2677;	//0xC4902A7C
	UINT32                                                 reserved2678;	//0xC4902A80
	UINT32                                                 reserved2679;	//0xC4902A84
	UINT32                                                 reserved2680;	//0xC4902A88
	UINT32                                                 reserved2681;	//0xC4902A8C
	UINT32                                                 reserved2682;	//0xC4902A90
	UINT32                                                 reserved2683;	//0xC4902A94
	UINT32                                                 reserved2684;	//0xC4902A98
	UINT32                                                 reserved2685;	//0xC4902A9C
	UINT32                                                 reserved2686;	//0xC4902AA0
	UINT32                                                 reserved2687;	//0xC4902AA4
	UINT32                                                 reserved2688;	//0xC4902AA8
	UINT32                                                 reserved2689;	//0xC4902AAC
	UINT32                                                 reserved2690;	//0xC4902AB0
	UINT32                                                 reserved2691;	//0xC4902AB4
	UINT32                                                 reserved2692;	//0xC4902AB8
	UINT32                                                 reserved2693;	//0xC4902ABC
	UINT32                                                 reserved2694;	//0xC4902AC0
	UINT32                                                 reserved2695;	//0xC4902AC4
	UINT32                                                 reserved2696;	//0xC4902AC8
	UINT32                                                 reserved2697;	//0xC4902ACC
	UINT32                                                 reserved2698;	//0xC4902AD0
	UINT32                                                 reserved2699;	//0xC4902AD4
	UINT32                                                 reserved2700;	//0xC4902AD8
	UINT32                                                 reserved2701;	//0xC4902ADC
	UINT32                                                 reserved2702;	//0xC4902AE0
	UINT32                                                 reserved2703;	//0xC4902AE4
	UINT32                                                 reserved2704;	//0xC4902AE8
	UINT32                                                 reserved2705;	//0xC4902AEC
	UINT32                                                 reserved2706;	//0xC4902AF0
	UINT32                                                 reserved2707;	//0xC4902AF4
	UINT32                                                 reserved2708;	//0xC4902AF8
	UINT32                                                 reserved2709;	//0xC4902AFC
	UINT32                                                 reserved2710;	//0xC4902B00
	UINT32                                                 reserved2711;	//0xC4902B04
	UINT32                                                 reserved2712;	//0xC4902B08
	UINT32                                                 reserved2713;	//0xC4902B0C
	UINT32                                                 reserved2714;	//0xC4902B10
	UINT32                                                 reserved2715;	//0xC4902B14
	UINT32                                                 reserved2716;	//0xC4902B18
	UINT32                                                 reserved2717;	//0xC4902B1C
	UINT32                                                 reserved2718;	//0xC4902B20
	UINT32                                                 reserved2719;	//0xC4902B24
	UINT32                                                 reserved2720;	//0xC4902B28
	UINT32                                                 reserved2721;	//0xC4902B2C
	UINT32                                                 reserved2722;	//0xC4902B30
	UINT32                                                 reserved2723;	//0xC4902B34
	UINT32                                                 reserved2724;	//0xC4902B38
	UINT32                                                 reserved2725;	//0xC4902B3C
	UINT32                                                 reserved2726;	//0xC4902B40
	UINT32                                                 reserved2727;	//0xC4902B44
	UINT32                                                 reserved2728;	//0xC4902B48
	UINT32                                                 reserved2729;	//0xC4902B4C
	UINT32                                                 reserved2730;	//0xC4902B50
	UINT32                                                 reserved2731;	//0xC4902B54
	UINT32                                                 reserved2732;	//0xC4902B58
	UINT32                                                 reserved2733;	//0xC4902B5C
	UINT32                                                 reserved2734;	//0xC4902B60
	UINT32                                                 reserved2735;	//0xC4902B64
	UINT32                                                 reserved2736;	//0xC4902B68
	UINT32                                                 reserved2737;	//0xC4902B6C
	UINT32                                                 reserved2738;	//0xC4902B70
	UINT32                                                 reserved2739;	//0xC4902B74
	UINT32                                                 reserved2740;	//0xC4902B78
	UINT32                                                 reserved2741;	//0xC4902B7C
	UINT32                                                 reserved2742;	//0xC4902B80
	UINT32                                                 reserved2743;	//0xC4902B84
	UINT32                                                 reserved2744;	//0xC4902B88
	UINT32                                                 reserved2745;	//0xC4902B8C
	UINT32                                                 reserved2746;	//0xC4902B90
	UINT32                                                 reserved2747;	//0xC4902B94
	UINT32                                                 reserved2748;	//0xC4902B98
	UINT32                                                 reserved2749;	//0xC4902B9C
	UINT32                                                 reserved2750;	//0xC4902BA0
	UINT32                                                 reserved2751;	//0xC4902BA4
	UINT32                                                 reserved2752;	//0xC4902BA8
	UINT32                                                 reserved2753;	//0xC4902BAC
	UINT32                                                 reserved2754;	//0xC4902BB0
	UINT32                                                 reserved2755;	//0xC4902BB4
	UINT32                                                 reserved2756;	//0xC4902BB8
	UINT32                                                 reserved2757;	//0xC4902BBC
	UINT32                                                 reserved2758;	//0xC4902BC0
	UINT32                                                 reserved2759;	//0xC4902BC4
	UINT32                                                 reserved2760;	//0xC4902BC8
	UINT32                                                 reserved2761;	//0xC4902BCC
	UINT32                                                 reserved2762;	//0xC4902BD0
	UINT32                                                 reserved2763;	//0xC4902BD4
	UINT32                                                 reserved2764;	//0xC4902BD8
	UINT32                                                 reserved2765;	//0xC4902BDC
	UINT32                                                 reserved2766;	//0xC4902BE0
	UINT32                                                 reserved2767;	//0xC4902BE4
	UINT32                                                 reserved2768;	//0xC4902BE8
	UINT32                                                 reserved2769;	//0xC4902BEC
	UINT32                                                 reserved2770;	//0xC4902BF0
	UINT32                                                 reserved2771;	//0xC4902BF4
	UINT32                                                 reserved2772;	//0xC4902BF8
	UINT32                                                 reserved2773;	//0xC4902BFC
	UINT32                                                 reserved2774;	//0xC4902C00
	UINT32                                                 reserved2775;	//0xC4902C04
	UINT32                                                 reserved2776;	//0xC4902C08
	UINT32                                                 reserved2777;	//0xC4902C0C
	UINT32                                                 reserved2778;	//0xC4902C10
	UINT32                                                 reserved2779;	//0xC4902C14
	UINT32                                                 reserved2780;	//0xC4902C18
	UINT32                                                 reserved2781;	//0xC4902C1C
	UINT32                                                 reserved2782;	//0xC4902C20
	UINT32                                                 reserved2783;	//0xC4902C24
	UINT32                                                 reserved2784;	//0xC4902C28
	UINT32                                                 reserved2785;	//0xC4902C2C
	UINT32                                                 reserved2786;	//0xC4902C30
	UINT32                                                 reserved2787;	//0xC4902C34
	UINT32                                                 reserved2788;	//0xC4902C38
	UINT32                                                 reserved2789;	//0xC4902C3C
	UINT32                                                 reserved2790;	//0xC4902C40
	UINT32                                                 reserved2791;	//0xC4902C44
	UINT32                                                 reserved2792;	//0xC4902C48
	UINT32                                                 reserved2793;	//0xC4902C4C
	UINT32                                                 reserved2794;	//0xC4902C50
	UINT32                                                 reserved2795;	//0xC4902C54
	UINT32                                                 reserved2796;	//0xC4902C58
	UINT32                                                 reserved2797;	//0xC4902C5C
	UINT32                                                 reserved2798;	//0xC4902C60
	UINT32                                                 reserved2799;	//0xC4902C64
	UINT32                                                 reserved2800;	//0xC4902C68
	UINT32                                                 reserved2801;	//0xC4902C6C
	UINT32                                                 reserved2802;	//0xC4902C70
	UINT32                                                 reserved2803;	//0xC4902C74
	UINT32                                                 reserved2804;	//0xC4902C78
	UINT32                                                 reserved2805;	//0xC4902C7C
	UINT32                                                 reserved2806;	//0xC4902C80
	UINT32                                                 reserved2807;	//0xC4902C84
	UINT32                                                 reserved2808;	//0xC4902C88
	UINT32                                                 reserved2809;	//0xC4902C8C
	UINT32                                                 reserved2810;	//0xC4902C90
	UINT32                                                 reserved2811;	//0xC4902C94
	UINT32                                                 reserved2812;	//0xC4902C98
	UINT32                                                 reserved2813;	//0xC4902C9C
	UINT32                                                 reserved2814;	//0xC4902CA0
	UINT32                                                 reserved2815;	//0xC4902CA4
	UINT32                                                 reserved2816;	//0xC4902CA8
	UINT32                                                 reserved2817;	//0xC4902CAC
	UINT32                                                 reserved2818;	//0xC4902CB0
	UINT32                                                 reserved2819;	//0xC4902CB4
	UINT32                                                 reserved2820;	//0xC4902CB8
	UINT32                                                 reserved2821;	//0xC4902CBC
	UINT32                                                 reserved2822;	//0xC4902CC0
	UINT32                                                 reserved2823;	//0xC4902CC4
	UINT32                                                 reserved2824;	//0xC4902CC8
	UINT32                                                 reserved2825;	//0xC4902CCC
	UINT32                                                 reserved2826;	//0xC4902CD0
	UINT32                                                 reserved2827;	//0xC4902CD4
	UINT32                                                 reserved2828;	//0xC4902CD8
	UINT32                                                 reserved2829;	//0xC4902CDC
	UINT32                                                 reserved2830;	//0xC4902CE0
	UINT32                                                 reserved2831;	//0xC4902CE4
	UINT32                                                 reserved2832;	//0xC4902CE8
	UINT32                                                 reserved2833;	//0xC4902CEC
	UINT32                                                 reserved2834;	//0xC4902CF0
	UINT32                                                 reserved2835;	//0xC4902CF4
	UINT32                                                 reserved2836;	//0xC4902CF8
	UINT32                                                 reserved2837;	//0xC4902CFC
	UINT32                                                 reserved2838;	//0xC4902D00
	UINT32                                                 reserved2839;	//0xC4902D04
	UINT32                                                 reserved2840;	//0xC4902D08
	UINT32                                                 reserved2841;	//0xC4902D0C
	UINT32                                                 reserved2842;	//0xC4902D10
	UINT32                                                 reserved2843;	//0xC4902D14
	UINT32                                                 reserved2844;	//0xC4902D18
	UINT32                                                 reserved2845;	//0xC4902D1C
	UINT32                                                 reserved2846;	//0xC4902D20
	UINT32                                                 reserved2847;	//0xC4902D24
	UINT32                                                 reserved2848;	//0xC4902D28
	UINT32                                                 reserved2849;	//0xC4902D2C
	UINT32                                                 reserved2850;	//0xC4902D30
	UINT32                                                 reserved2851;	//0xC4902D34
	UINT32                                                 reserved2852;	//0xC4902D38
	UINT32                                                 reserved2853;	//0xC4902D3C
	UINT32                                                 reserved2854;	//0xC4902D40
	UINT32                                                 reserved2855;	//0xC4902D44
	UINT32                                                 reserved2856;	//0xC4902D48
	UINT32                                                 reserved2857;	//0xC4902D4C
	UINT32                                                 reserved2858;	//0xC4902D50
	UINT32                                                 reserved2859;	//0xC4902D54
	UINT32                                                 reserved2860;	//0xC4902D58
	UINT32                                                 reserved2861;	//0xC4902D5C
	UINT32                                                 reserved2862;	//0xC4902D60
	UINT32                                                 reserved2863;	//0xC4902D64
	UINT32                                                 reserved2864;	//0xC4902D68
	UINT32                                                 reserved2865;	//0xC4902D6C
	UINT32                                                 reserved2866;	//0xC4902D70
	UINT32                                                 reserved2867;	//0xC4902D74
	UINT32                                                 reserved2868;	//0xC4902D78
	UINT32                                                 reserved2869;	//0xC4902D7C
	UINT32                                                 reserved2870;	//0xC4902D80
	UINT32                                                 reserved2871;	//0xC4902D84
	UINT32                                                 reserved2872;	//0xC4902D88
	UINT32                                                 reserved2873;	//0xC4902D8C
	UINT32                                                 reserved2874;	//0xC4902D90
	UINT32                                                 reserved2875;	//0xC4902D94
	UINT32                                                 reserved2876;	//0xC4902D98
	UINT32                                                 reserved2877;	//0xC4902D9C
	UINT32                                                 reserved2878;	//0xC4902DA0
	UINT32                                                 reserved2879;	//0xC4902DA4
	UINT32                                                 reserved2880;	//0xC4902DA8
	UINT32                                                 reserved2881;	//0xC4902DAC
	UINT32                                                 reserved2882;	//0xC4902DB0
	UINT32                                                 reserved2883;	//0xC4902DB4
	UINT32                                                 reserved2884;	//0xC4902DB8
	UINT32                                                 reserved2885;	//0xC4902DBC
	UINT32                                                 reserved2886;	//0xC4902DC0
	UINT32                                                 reserved2887;	//0xC4902DC4
	UINT32                                                 reserved2888;	//0xC4902DC8
	UINT32                                                 reserved2889;	//0xC4902DCC
	UINT32                                                 reserved2890;	//0xC4902DD0
	UINT32                                                 reserved2891;	//0xC4902DD4
	UINT32                                                 reserved2892;	//0xC4902DD8
	UINT32                                                 reserved2893;	//0xC4902DDC
	UINT32                                                 reserved2894;	//0xC4902DE0
	UINT32                                                 reserved2895;	//0xC4902DE4
	UINT32                                                 reserved2896;	//0xC4902DE8
	UINT32                                                 reserved2897;	//0xC4902DEC
	UINT32                                                 reserved2898;	//0xC4902DF0
	UINT32                                                 reserved2899;	//0xC4902DF4
	UINT32                                                 reserved2900;	//0xC4902DF8
	UINT32                                                 reserved2901;	//0xC4902DFC
	UINT32                                                 reserved2902;	//0xC4902E00
	UINT32                                                 reserved2903;	//0xC4902E04
	UINT32                                                 reserved2904;	//0xC4902E08
	UINT32                                                 reserved2905;	//0xC4902E0C
	UINT32                                                 reserved2906;	//0xC4902E10
	UINT32                                                 reserved2907;	//0xC4902E14
	UINT32                                                 reserved2908;	//0xC4902E18
	UINT32                                                 reserved2909;	//0xC4902E1C
	UINT32                                                 reserved2910;	//0xC4902E20
	UINT32                                                 reserved2911;	//0xC4902E24
	UINT32                                                 reserved2912;	//0xC4902E28
	UINT32                                                 reserved2913;	//0xC4902E2C
	UINT32                                                 reserved2914;	//0xC4902E30
	UINT32                                                 reserved2915;	//0xC4902E34
	UINT32                                                 reserved2916;	//0xC4902E38
	UINT32                                                 reserved2917;	//0xC4902E3C
	UINT32                                                 reserved2918;	//0xC4902E40
	UINT32                                                 reserved2919;	//0xC4902E44
	UINT32                                                 reserved2920;	//0xC4902E48
	UINT32                                                 reserved2921;	//0xC4902E4C
	UINT32                                                 reserved2922;	//0xC4902E50
	UINT32                                                 reserved2923;	//0xC4902E54
	UINT32                                                 reserved2924;	//0xC4902E58
	UINT32                                                 reserved2925;	//0xC4902E5C
	UINT32                                                 reserved2926;	//0xC4902E60
	UINT32                                                 reserved2927;	//0xC4902E64
	UINT32                                                 reserved2928;	//0xC4902E68
	UINT32                                                 reserved2929;	//0xC4902E6C
	UINT32                                                 reserved2930;	//0xC4902E70
	UINT32                                                 reserved2931;	//0xC4902E74
	UINT32                                                 reserved2932;	//0xC4902E78
	UINT32                                                 reserved2933;	//0xC4902E7C
	UINT32                                                 reserved2934;	//0xC4902E80
	UINT32                                                 reserved2935;	//0xC4902E84
	UINT32                                                 reserved2936;	//0xC4902E88
	UINT32                                                 reserved2937;	//0xC4902E8C
	UINT32                                                 reserved2938;	//0xC4902E90
	UINT32                                                 reserved2939;	//0xC4902E94
	UINT32                                                 reserved2940;	//0xC4902E98
	UINT32                                                 reserved2941;	//0xC4902E9C
	UINT32                                                 reserved2942;	//0xC4902EA0
	UINT32                                                 reserved2943;	//0xC4902EA4
	UINT32                                                 reserved2944;	//0xC4902EA8
	UINT32                                                 reserved2945;	//0xC4902EAC
	UINT32                                                 reserved2946;	//0xC4902EB0
	UINT32                                                 reserved2947;	//0xC4902EB4
	UINT32                                                 reserved2948;	//0xC4902EB8
	UINT32                                                 reserved2949;	//0xC4902EBC
	UINT32                                                 reserved2950;	//0xC4902EC0
	UINT32                                                 reserved2951;	//0xC4902EC4
	UINT32                                                 reserved2952;	//0xC4902EC8
	UINT32                                                 reserved2953;	//0xC4902ECC
	UINT32                                                 reserved2954;	//0xC4902ED0
	UINT32                                                 reserved2955;	//0xC4902ED4
	UINT32                                                 reserved2956;	//0xC4902ED8
	UINT32                                                 reserved2957;	//0xC4902EDC
	UINT32                                                 reserved2958;	//0xC4902EE0
	UINT32                                                 reserved2959;	//0xC4902EE4
	UINT32                                                 reserved2960;	//0xC4902EE8
	UINT32                                                 reserved2961;	//0xC4902EEC
	UINT32                                                 reserved2962;	//0xC4902EF0
	UINT32                                                 reserved2963;	//0xC4902EF4
	UINT32                                                 reserved2964;	//0xC4902EF8
	UINT32                                                 reserved2965;	//0xC4902EFC
	UINT32                                                 reserved2966;	//0xC4902F00
	UINT32                                                 reserved2967;	//0xC4902F04
	UINT32                                                 reserved2968;	//0xC4902F08
	UINT32                                                 reserved2969;	//0xC4902F0C
	UINT32                                                 reserved2970;	//0xC4902F10
	UINT32                                                 reserved2971;	//0xC4902F14
	UINT32                                                 reserved2972;	//0xC4902F18
	UINT32                                                 reserved2973;	//0xC4902F1C
	UINT32                                                 reserved2974;	//0xC4902F20
	UINT32                                                 reserved2975;	//0xC4902F24
	UINT32                                                 reserved2976;	//0xC4902F28
	UINT32                                                 reserved2977;	//0xC4902F2C
	UINT32                                                 reserved2978;	//0xC4902F30
	UINT32                                                 reserved2979;	//0xC4902F34
	UINT32                                                 reserved2980;	//0xC4902F38
	UINT32                                                 reserved2981;	//0xC4902F3C
	UINT32                                                 reserved2982;	//0xC4902F40
	UINT32                                                 reserved2983;	//0xC4902F44
	UINT32                                                 reserved2984;	//0xC4902F48
	UINT32                                                 reserved2985;	//0xC4902F4C
	UINT32                                                 reserved2986;	//0xC4902F50
	UINT32                                                 reserved2987;	//0xC4902F54
	UINT32                                                 reserved2988;	//0xC4902F58
	UINT32                                                 reserved2989;	//0xC4902F5C
	UINT32                                                 reserved2990;	//0xC4902F60
	UINT32                                                 reserved2991;	//0xC4902F64
	UINT32                                                 reserved2992;	//0xC4902F68
	UINT32                                                 reserved2993;	//0xC4902F6C
	UINT32                                                 reserved2994;	//0xC4902F70
	UINT32                                                 reserved2995;	//0xC4902F74
	UINT32                                                 reserved2996;	//0xC4902F78
	UINT32                                                 reserved2997;	//0xC4902F7C
	UINT32                                                 reserved2998;	//0xC4902F80
	UINT32                                                 reserved2999;	//0xC4902F84
	UINT32                                                 reserved3000;	//0xC4902F88
	UINT32                                                 reserved3001;	//0xC4902F8C
	UINT32                                                 reserved3002;	//0xC4902F90
	UINT32                                                 reserved3003;	//0xC4902F94
	UINT32                                                 reserved3004;	//0xC4902F98
	UINT32                                                 reserved3005;	//0xC4902F9C
	UINT32                                                 reserved3006;	//0xC4902FA0
	UINT32                                                 reserved3007;	//0xC4902FA4
	UINT32                                                 reserved3008;	//0xC4902FA8
	UINT32                                                 reserved3009;	//0xC4902FAC
	UINT32                                                 reserved3010;	//0xC4902FB0
	UINT32                                                 reserved3011;	//0xC4902FB4
	UINT32                                                 reserved3012;	//0xC4902FB8
	UINT32                                                 reserved3013;	//0xC4902FBC
	UINT32                                                 reserved3014;	//0xC4902FC0
	UINT32                                                 reserved3015;	//0xC4902FC4
	UINT32                                                 reserved3016;	//0xC4902FC8
	UINT32                                                 reserved3017;	//0xC4902FCC
	UINT32                                                 reserved3018;	//0xC4902FD0
	UINT32                                                 reserved3019;	//0xC4902FD4
	UINT32                                                 reserved3020;	//0xC4902FD8
	UINT32                                                 reserved3021;	//0xC4902FDC
	UINT32                                                 reserved3022;	//0xC4902FE0
	UINT32                                                 reserved3023;	//0xC4902FE4
	UINT32                                                 reserved3024;	//0xC4902FE8
	UINT32                                                 reserved3025;	//0xC4902FEC
	UINT32                                                 reserved3026;	//0xC4902FF0
	UINT32                                                 reserved3027;	//0xC4902FF4
	UINT32                                                 reserved3028;	//0xC4902FF8
	UINT32                                                 reserved3029;	//0xC4902FFC
	REG_DDRC_M1_LPD4_MAIN_FSM_INIT_0_T             lpd4_main_fsm_init_0;	//0xC4903000
	REG_DDRC_M1_LPD4_MAIN_FSM_INIT_1_T             lpd4_main_fsm_init_1;	//0xC4903004
	REG_DDRC_M1_LPD4_MAIN_FSM_INIT_2_T             lpd4_main_fsm_init_2;	//0xC4903008
	REG_DDRC_M1_LPD4_MAIN_FSM_CTRL_T                 lpd4_main_fsm_ctrl;	//0xC490300C
	REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_0_T     lpd4_main_fsm_dir_ctrl_0;	//0xC4903010
	REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_1_T     lpd4_main_fsm_dir_ctrl_1;	//0xC4903014
	REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_2_T     lpd4_main_fsm_dir_ctrl_2;	//0xC4903018
	REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_3_T     lpd4_main_fsm_dir_ctrl_3;	//0xC490301C
	REG_DDRC_M1_LPD4_MAIN_FSM_DIR_CTRL_4_T     lpd4_main_fsm_dir_ctrl_4;	//0xC4903020
	REG_DDRC_M1_LPD4_MAIN_FSM_DFS_MRW_T           lpd4_main_fsm_dfs_mrw;	//0xC4903024
	REG_DDRC_M1_LPD4_MAIN_FSM_CTRLUPD_T           lpd4_main_fsm_ctrlupd;	//0xC4903028
	REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_0_T     lpd4_main_fsm_mpc_fifo_0;	//0xC490302C
	REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_1_T     lpd4_main_fsm_mpc_fifo_1;	//0xC4903030
	REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_2_T     lpd4_main_fsm_mpc_fifo_2;	//0xC4903034
	REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_3_T     lpd4_main_fsm_mpc_fifo_3;	//0xC4903038
	REG_DDRC_M1_LPD4_MAIN_FSM_MPC_FIFO_4_T     lpd4_main_fsm_mpc_fifo_4;	//0xC490303C
	UINT32                                                 reserved3030;	//0xC4903040
	UINT32                                                 reserved3031;	//0xC4903044
	UINT32                                                 reserved3032;	//0xC4903048
	UINT32                                                 reserved3033;	//0xC490304C
	REG_DDRC_M1_LPD4_MR_CTRL_0_T                         lpd4_mr_ctrl_0;	//0xC4903050
	REG_DDRC_M1_LPD4_MR_CTRL_1_T                         lpd4_mr_ctrl_1;	//0xC4903054
	REG_DDRC_M1_LPD4_MR_CTRL_2_T                         lpd4_mr_ctrl_2;	//0xC4903058
	UINT32                                                 reserved3034;	//0xC490305C
	REG_DDRC_M1_LPD4_REF_REQ_CTRL_T                   lpd4_ref_req_ctrl;	//0xC4903060
	UINT32                                                 reserved3035;	//0xC4903064
	UINT32                                                 reserved3036;	//0xC4903068
	UINT32                                                 reserved3037;	//0xC490306C
	REG_DDRC_M1_LPD4_REF_CTRL_T                           lpd4_ref_ctrl;	//0xC4903070
	UINT32                                                 reserved3038;	//0xC4903074
	UINT32                                                 reserved3039;	//0xC4903078
	UINT32                                                 reserved3040;	//0xC490307C
	REG_DDRC_M1_LPD4_BANK_FSM_T                           lpd4_bank_fsm;	//0xC4903080
	UINT32                                                 reserved3041;	//0xC4903084
	UINT32                                                 reserved3042;	//0xC4903088
	UINT32                                                 reserved3043;	//0xC490308C
	UINT32                                                 reserved3044;	//0xC4903090
	UINT32                                                 reserved3045;	//0xC4903094
	UINT32                                                 reserved3046;	//0xC4903098
	UINT32                                                 reserved3047;	//0xC490309C
	REG_DDRC_M1_LPD4_BANK_STATUS_T                     lpd4_bank_status;	//0xC49030A0
	UINT32                                                 reserved3048;	//0xC49030A4
	UINT32                                                 reserved3049;	//0xC49030A8
	UINT32                                                 reserved3050;	//0xC49030AC
	UINT32                                                 reserved3051;	//0xC49030B0
	UINT32                                                 reserved3052;	//0xC49030B4
	UINT32                                                 reserved3053;	//0xC49030B8
	UINT32                                                 reserved3054;	//0xC49030BC
	REG_DDRC_M1_LPD4_PHY_IF_T                               lpd4_phy_if;	//0xC49030C0
	UINT32                                                 reserved3055;	//0xC49030C4
	UINT32                                                 reserved3056;	//0xC49030C8
	UINT32                                                 reserved3057;	//0xC49030CC
	UINT32                                                 reserved3058;	//0xC49030D0
	UINT32                                                 reserved3059;	//0xC49030D4
	UINT32                                                 reserved3060;	//0xC49030D8
	UINT32                                                 reserved3061;	//0xC49030DC
	UINT32                                                 reserved3062;	//0xC49030E0
	UINT32                                                 reserved3063;	//0xC49030E4
	UINT32                                                 reserved3064;	//0xC49030E8
	UINT32                                                 reserved3065;	//0xC49030EC
	UINT32                                                 reserved3066;	//0xC49030F0
	UINT32                                                 reserved3067;	//0xC49030F4
	UINT32                                                 reserved3068;	//0xC49030F8
	UINT32                                                 reserved3069;	//0xC49030FC
	REG_DDRC_M1_LPD4_DFS0_MR_0_CH0_T                 lpd4_dfs0_mr_0_ch0;	//0xC4903100
	REG_DDRC_M1_LPD4_DFS0_MR_1_CH0_T                 lpd4_dfs0_mr_1_ch0;	//0xC4903104
	REG_DDRC_M1_LPD4_DFS0_MR_2_CH0_T                 lpd4_dfs0_mr_2_ch0;	//0xC4903108
	REG_DDRC_M1_LPD4_DFS0_MR_3_CH0_T                 lpd4_dfs0_mr_3_ch0;	//0xC490310C
	REG_DDRC_M1_LPD4_DFS0_MR_4_CH0_T                 lpd4_dfs0_mr_4_ch0;	//0xC4903110
	REG_DDRC_M1_LPD4_DFS0_MR_5_CH0_T                 lpd4_dfs0_mr_5_ch0;	//0xC4903114
	REG_DDRC_M1_LPD4_DFS0_MR_6_CH0_T                 lpd4_dfs0_mr_6_ch0;	//0xC4903118
	UINT32                                                 reserved3070;	//0xC490311C
	REG_DDRC_M1_LPD4_DFS0_MR_0_CH1_T                 lpd4_dfs0_mr_0_ch1;	//0xC4903120
	REG_DDRC_M1_LPD4_DFS0_MR_1_CH1_T                 lpd4_dfs0_mr_1_ch1;	//0xC4903124
	REG_DDRC_M1_LPD4_DFS0_MR_2_CH1_T                 lpd4_dfs0_mr_2_ch1;	//0xC4903128
	REG_DDRC_M1_LPD4_DFS0_MR_3_CH1_T                 lpd4_dfs0_mr_3_ch1;	//0xC490312C
	REG_DDRC_M1_LPD4_DFS0_MR_4_CH1_T                 lpd4_dfs0_mr_4_ch1;	//0xC4903130
	REG_DDRC_M1_LPD4_DFS0_MR_5_CH1_T                 lpd4_dfs0_mr_5_ch1;	//0xC4903134
	REG_DDRC_M1_LPD4_DFS0_MR_6_CH1_T                 lpd4_dfs0_mr_6_ch1;	//0xC4903138
	UINT32                                                 reserved3071;	//0xC490313C
	REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_0_T             lpd4_dfs0_main_fsm_0;	//0xC4903140
	REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_1_T             lpd4_dfs0_main_fsm_1;	//0xC4903144
	REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_2_T             lpd4_dfs0_main_fsm_2;	//0xC4903148
	REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_3_T             lpd4_dfs0_main_fsm_3;	//0xC490314C
	REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_4_T             lpd4_dfs0_main_fsm_4;	//0xC4903150
	REG_DDRC_M1_LPD4_DFS0_MAIN_FSM_5_T             lpd4_dfs0_main_fsm_5;	//0xC4903154
	UINT32                                                 reserved3072;	//0xC4903158
	UINT32                                                 reserved3073;	//0xC490315C
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_0_T     lpd4_dfs0_ref_req_ctrl_0;	//0xC4903160
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_1_T     lpd4_dfs0_ref_req_ctrl_1;	//0xC4903164
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_2_T     lpd4_dfs0_ref_req_ctrl_2;	//0xC4903168
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_3_T     lpd4_dfs0_ref_req_ctrl_3;	//0xC490316C
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_4_T     lpd4_dfs0_ref_req_ctrl_4;	//0xC4903170
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_5_T     lpd4_dfs0_ref_req_ctrl_5;	//0xC4903174
	REG_DDRC_M1_LPD4_DFS0_REF_REQ_CTRL_6_T     lpd4_dfs0_ref_req_ctrl_6;	//0xC4903178
	UINT32                                                 reserved3074;	//0xC490317C
	UINT32                                                 reserved3075;	//0xC4903180
	UINT32                                                 reserved3076;	//0xC4903184
	UINT32                                                 reserved3077;	//0xC4903188
	UINT32                                                 reserved3078;	//0xC490318C
	REG_DDRC_M1_LPD4_DFS0_REF_CTRL_T                 lpd4_dfs0_ref_ctrl;	//0xC4903190
	UINT32                                                 reserved3079;	//0xC4903194
	UINT32                                                 reserved3080;	//0xC4903198
	UINT32                                                 reserved3081;	//0xC490319C
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_0_T       lpd4_dfs0_bank_status_0;	//0xC49031A0
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_1_T       lpd4_dfs0_bank_status_1;	//0xC49031A4
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_2_T       lpd4_dfs0_bank_status_2;	//0xC49031A8
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_3_T       lpd4_dfs0_bank_status_3;	//0xC49031AC
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_4_T       lpd4_dfs0_bank_status_4;	//0xC49031B0
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_5_T       lpd4_dfs0_bank_status_5;	//0xC49031B4
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_6_T       lpd4_dfs0_bank_status_6;	//0xC49031B8
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_7_T       lpd4_dfs0_bank_status_7;	//0xC49031BC
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_8_T       lpd4_dfs0_bank_status_8;	//0xC49031C0
	REG_DDRC_M1_LPD4_DFS0_BANK_STATUS_9_T       lpd4_dfs0_bank_status_9;	//0xC49031C4
	UINT32                                                 reserved3082;	//0xC49031C8
	UINT32                                                 reserved3083;	//0xC49031CC
	UINT32                                                 reserved3084;	//0xC49031D0
	UINT32                                                 reserved3085;	//0xC49031D4
	UINT32                                                 reserved3086;	//0xC49031D8
	UINT32                                                 reserved3087;	//0xC49031DC
	REG_DDRC_M1_LPD4_DFS0_PHY_IF_T                     lpd4_dfs0_phy_if;	//0xC49031E0
	UINT32                                                 reserved3088;	//0xC49031E4
	UINT32                                                 reserved3089;	//0xC49031E8
	UINT32                                                 reserved3090;	//0xC49031EC
	UINT32                                                 reserved3091;	//0xC49031F0
	UINT32                                                 reserved3092;	//0xC49031F4
	UINT32                                                 reserved3093;	//0xC49031F8
	UINT32                                                 reserved3094;	//0xC49031FC
	REG_DDRC_M1_LPD4_DFS1_MR_0_CH0_T                 lpd4_dfs1_mr_0_ch0;	//0xC4903200
	REG_DDRC_M1_LPD4_DFS1_MR_1_CH0_T                 lpd4_dfs1_mr_1_ch0;	//0xC4903204
	REG_DDRC_M1_LPD4_DFS1_MR_2_CH0_T                 lpd4_dfs1_mr_2_ch0;	//0xC4903208
	REG_DDRC_M1_LPD4_DFS1_MR_3_CH0_T                 lpd4_dfs1_mr_3_ch0;	//0xC490320C
	REG_DDRC_M1_LPD4_DFS1_MR_4_CH0_T                 lpd4_dfs1_mr_4_ch0;	//0xC4903210
	REG_DDRC_M1_LPD4_DFS1_MR_5_CH0_T                 lpd4_dfs1_mr_5_ch0;	//0xC4903214
	REG_DDRC_M1_LPD4_DFS1_MR_6_CH0_T                 lpd4_dfs1_mr_6_ch0;	//0xC4903218
	UINT32                                                 reserved3095;	//0xC490321C
	REG_DDRC_M1_LPD4_DFS1_MR_0_CH1_T                 lpd4_dfs1_mr_0_ch1;	//0xC4903220
	REG_DDRC_M1_LPD4_DFS1_MR_1_CH1_T                 lpd4_dfs1_mr_1_ch1;	//0xC4903224
	REG_DDRC_M1_LPD4_DFS1_MR_2_CH1_T                 lpd4_dfs1_mr_2_ch1;	//0xC4903228
	REG_DDRC_M1_LPD4_DFS1_MR_3_CH1_T                 lpd4_dfs1_mr_3_ch1;	//0xC490322C
	REG_DDRC_M1_LPD4_DFS1_MR_4_CH1_T                 lpd4_dfs1_mr_4_ch1;	//0xC4903230
	REG_DDRC_M1_LPD4_DFS1_MR_5_CH1_T                 lpd4_dfs1_mr_5_ch1;	//0xC4903234
	REG_DDRC_M1_LPD4_DFS1_MR_6_CH1_T                 lpd4_dfs1_mr_6_ch1;	//0xC4903238
	UINT32                                                 reserved3096;	//0xC490323C
	REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_0_T             lpd4_dfs1_main_fsm_0;	//0xC4903240
	REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_1_T             lpd4_dfs1_main_fsm_1;	//0xC4903244
	REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_2_T             lpd4_dfs1_main_fsm_2;	//0xC4903248
	REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_3_T             lpd4_dfs1_main_fsm_3;	//0xC490324C
	REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_4_T             lpd4_dfs1_main_fsm_4;	//0xC4903250
	REG_DDRC_M1_LPD4_DFS1_MAIN_FSM_5_T             lpd4_dfs1_main_fsm_5;	//0xC4903254
	UINT32                                                 reserved3097;	//0xC4903258
	UINT32                                                 reserved3098;	//0xC490325C
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_0_T     lpd4_dfs1_ref_req_ctrl_0;	//0xC4903260
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_1_T     lpd4_dfs1_ref_req_ctrl_1;	//0xC4903264
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_2_T     lpd4_dfs1_ref_req_ctrl_2;	//0xC4903268
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_3_T     lpd4_dfs1_ref_req_ctrl_3;	//0xC490326C
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_4_T     lpd4_dfs1_ref_req_ctrl_4;	//0xC4903270
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_5_T     lpd4_dfs1_ref_req_ctrl_5;	//0xC4903274
	REG_DDRC_M1_LPD4_DFS1_REF_REQ_CTRL_6_T     lpd4_dfs1_ref_req_ctrl_6;	//0xC4903278
	UINT32                                                 reserved3099;	//0xC490327C
	UINT32                                                 reserved3100;	//0xC4903280
	UINT32                                                 reserved3101;	//0xC4903284
	UINT32                                                 reserved3102;	//0xC4903288
	UINT32                                                 reserved3103;	//0xC490328C
	REG_DDRC_M1_LPD4_DFS1_REF_CTRL_T                 lpd4_dfs1_ref_ctrl;	//0xC4903290
	UINT32                                                 reserved3104;	//0xC4903294
	UINT32                                                 reserved3105;	//0xC4903298
	UINT32                                                 reserved3106;	//0xC490329C
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_0_T       lpd4_dfs1_bank_status_0;	//0xC49032A0
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_1_T       lpd4_dfs1_bank_status_1;	//0xC49032A4
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_2_T       lpd4_dfs1_bank_status_2;	//0xC49032A8
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_3_T       lpd4_dfs1_bank_status_3;	//0xC49032AC
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_4_T       lpd4_dfs1_bank_status_4;	//0xC49032B0
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_5_T       lpd4_dfs1_bank_status_5;	//0xC49032B4
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_6_T       lpd4_dfs1_bank_status_6;	//0xC49032B8
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_7_T       lpd4_dfs1_bank_status_7;	//0xC49032BC
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_8_T       lpd4_dfs1_bank_status_8;	//0xC49032C0
	REG_DDRC_M1_LPD4_DFS1_BANK_STATUS_9_T       lpd4_dfs1_bank_status_9;	//0xC49032C4
	UINT32                                                 reserved3107;	//0xC49032C8
	UINT32                                                 reserved3108;	//0xC49032CC
	UINT32                                                 reserved3109;	//0xC49032D0
	UINT32                                                 reserved3110;	//0xC49032D4
	UINT32                                                 reserved3111;	//0xC49032D8
	UINT32                                                 reserved3112;	//0xC49032DC
	REG_DDRC_M1_LPD4_DFS1_PHY_IF_T                     lpd4_dfs1_phy_if;	//0xC49032E0
	UINT32                                                 reserved3113;	//0xC49032E4
	UINT32                                                 reserved3114;	//0xC49032E8
	UINT32                                                 reserved3115;	//0xC49032EC
	UINT32                                                 reserved3116;	//0xC49032F0
	UINT32                                                 reserved3117;	//0xC49032F4
	UINT32                                                 reserved3118;	//0xC49032F8
	UINT32                                                 reserved3119;	//0xC49032FC
	REG_DDRC_M1_LPD4_DFS2_MR_0_CH0_T                 lpd4_dfs2_mr_0_ch0;	//0xC4903300
	REG_DDRC_M1_LPD4_DFS2_MR_1_CH0_T                 lpd4_dfs2_mr_1_ch0;	//0xC4903304
	REG_DDRC_M1_LPD4_DFS2_MR_2_CH0_T                 lpd4_dfs2_mr_2_ch0;	//0xC4903308
	REG_DDRC_M1_LPD4_DFS2_MR_3_CH0_T                 lpd4_dfs2_mr_3_ch0;	//0xC490330C
	REG_DDRC_M1_LPD4_DFS2_MR_4_CH0_T                 lpd4_dfs2_mr_4_ch0;	//0xC4903310
	REG_DDRC_M1_LPD4_DFS2_MR_5_CH0_T                 lpd4_dfs2_mr_5_ch0;	//0xC4903314
	REG_DDRC_M1_LPD4_DFS2_MR_6_CH0_T                 lpd4_dfs2_mr_6_ch0;	//0xC4903318
	UINT32                                                 reserved3120;	//0xC490331C
	REG_DDRC_M1_LPD4_DFS2_MR_0_CH1_T                 lpd4_dfs2_mr_0_ch1;	//0xC4903320
	REG_DDRC_M1_LPD4_DFS2_MR_1_CH1_T                 lpd4_dfs2_mr_1_ch1;	//0xC4903324
	REG_DDRC_M1_LPD4_DFS2_MR_2_CH1_T                 lpd4_dfs2_mr_2_ch1;	//0xC4903328
	REG_DDRC_M1_LPD4_DFS2_MR_3_CH1_T                 lpd4_dfs2_mr_3_ch1;	//0xC490332C
	REG_DDRC_M1_LPD4_DFS2_MR_4_CH1_T                 lpd4_dfs2_mr_4_ch1;	//0xC4903330
	REG_DDRC_M1_LPD4_DFS2_MR_5_CH1_T                 lpd4_dfs2_mr_5_ch1;	//0xC4903334
	REG_DDRC_M1_LPD4_DFS2_MR_6_CH1_T                 lpd4_dfs2_mr_6_ch1;	//0xC4903338
	UINT32                                                 reserved3121;	//0xC490333C
	REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_0_T             lpd4_dfs2_main_fsm_0;	//0xC4903340
	REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_1_T             lpd4_dfs2_main_fsm_1;	//0xC4903344
	REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_2_T             lpd4_dfs2_main_fsm_2;	//0xC4903348
	REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_3_T             lpd4_dfs2_main_fsm_3;	//0xC490334C
	REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_4_T             lpd4_dfs2_main_fsm_4;	//0xC4903350
	REG_DDRC_M1_LPD4_DFS2_MAIN_FSM_5_T             lpd4_dfs2_main_fsm_5;	//0xC4903354
	UINT32                                                 reserved3122;	//0xC4903358
	UINT32                                                 reserved3123;	//0xC490335C
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_0_T     lpd4_dfs2_ref_req_ctrl_0;	//0xC4903360
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_1_T     lpd4_dfs2_ref_req_ctrl_1;	//0xC4903364
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_2_T     lpd4_dfs2_ref_req_ctrl_2;	//0xC4903368
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_3_T     lpd4_dfs2_ref_req_ctrl_3;	//0xC490336C
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_4_T     lpd4_dfs2_ref_req_ctrl_4;	//0xC4903370
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_5_T     lpd4_dfs2_ref_req_ctrl_5;	//0xC4903374
	REG_DDRC_M1_LPD4_DFS2_REF_REQ_CTRL_6_T     lpd4_dfs2_ref_req_ctrl_6;	//0xC4903378
	UINT32                                                 reserved3124;	//0xC490337C
	UINT32                                                 reserved3125;	//0xC4903380
	UINT32                                                 reserved3126;	//0xC4903384
	UINT32                                                 reserved3127;	//0xC4903388
	UINT32                                                 reserved3128;	//0xC490338C
	REG_DDRC_M1_LPD4_DFS2_REF_CTRL_T                 lpd4_dfs2_ref_ctrl;	//0xC4903390
	UINT32                                                 reserved3129;	//0xC4903394
	UINT32                                                 reserved3130;	//0xC4903398
	UINT32                                                 reserved3131;	//0xC490339C
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_0_T       lpd4_dfs2_bank_status_0;	//0xC49033A0
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_1_T       lpd4_dfs2_bank_status_1;	//0xC49033A4
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_2_T       lpd4_dfs2_bank_status_2;	//0xC49033A8
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_3_T       lpd4_dfs2_bank_status_3;	//0xC49033AC
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_4_T       lpd4_dfs2_bank_status_4;	//0xC49033B0
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_5_T       lpd4_dfs2_bank_status_5;	//0xC49033B4
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_6_T       lpd4_dfs2_bank_status_6;	//0xC49033B8
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_7_T       lpd4_dfs2_bank_status_7;	//0xC49033BC
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_8_T       lpd4_dfs2_bank_status_8;	//0xC49033C0
	REG_DDRC_M1_LPD4_DFS2_BANK_STATUS_9_T       lpd4_dfs2_bank_status_9;	//0xC49033C4
	UINT32                                                 reserved3132;	//0xC49033C8
	UINT32                                                 reserved3133;	//0xC49033CC
	UINT32                                                 reserved3134;	//0xC49033D0
	UINT32                                                 reserved3135;	//0xC49033D4
	UINT32                                                 reserved3136;	//0xC49033D8
	UINT32                                                 reserved3137;	//0xC49033DC
	REG_DDRC_M1_LPD4_DFS2_PHY_IF_T                     lpd4_dfs2_phy_if;	//0xC49033E0
	UINT32                                                 reserved3138;	//0xC49033E4
	UINT32                                                 reserved3139;	//0xC49033E8
	UINT32                                                 reserved3140;	//0xC49033EC
	UINT32                                                 reserved3141;	//0xC49033F0
	UINT32                                                 reserved3142;	//0xC49033F4
	UINT32                                                 reserved3143;	//0xC49033F8
	UINT32                                                 reserved3144;	//0xC49033FC
	UINT32                                                 reserved3145;	//0xC4903400
	UINT32                                                 reserved3146;	//0xC4903404
	UINT32                                                 reserved3147;	//0xC4903408
	UINT32                                                 reserved3148;	//0xC490340C
	UINT32                                                 reserved3149;	//0xC4903410
	UINT32                                                 reserved3150;	//0xC4903414
	UINT32                                                 reserved3151;	//0xC4903418
	UINT32                                                 reserved3152;	//0xC490341C
	UINT32                                                 reserved3153;	//0xC4903420
	UINT32                                                 reserved3154;	//0xC4903424
	UINT32                                                 reserved3155;	//0xC4903428
	UINT32                                                 reserved3156;	//0xC490342C
	UINT32                                                 reserved3157;	//0xC4903430
	UINT32                                                 reserved3158;	//0xC4903434
	UINT32                                                 reserved3159;	//0xC4903438
	UINT32                                                 reserved3160;	//0xC490343C
	UINT32                                                 reserved3161;	//0xC4903440
	UINT32                                                 reserved3162;	//0xC4903444
	UINT32                                                 reserved3163;	//0xC4903448
	UINT32                                                 reserved3164;	//0xC490344C
	UINT32                                                 reserved3165;	//0xC4903450
	UINT32                                                 reserved3166;	//0xC4903454
	UINT32                                                 reserved3167;	//0xC4903458
	UINT32                                                 reserved3168;	//0xC490345C
	UINT32                                                 reserved3169;	//0xC4903460
	UINT32                                                 reserved3170;	//0xC4903464
	UINT32                                                 reserved3171;	//0xC4903468
	UINT32                                                 reserved3172;	//0xC490346C
	UINT32                                                 reserved3173;	//0xC4903470
	UINT32                                                 reserved3174;	//0xC4903474
	UINT32                                                 reserved3175;	//0xC4903478
	UINT32                                                 reserved3176;	//0xC490347C
	UINT32                                                 reserved3177;	//0xC4903480
	UINT32                                                 reserved3178;	//0xC4903484
	UINT32                                                 reserved3179;	//0xC4903488
	UINT32                                                 reserved3180;	//0xC490348C
	UINT32                                                 reserved3181;	//0xC4903490
	UINT32                                                 reserved3182;	//0xC4903494
	UINT32                                                 reserved3183;	//0xC4903498
	UINT32                                                 reserved3184;	//0xC490349C
	UINT32                                                 reserved3185;	//0xC49034A0
	UINT32                                                 reserved3186;	//0xC49034A4
	UINT32                                                 reserved3187;	//0xC49034A8
	UINT32                                                 reserved3188;	//0xC49034AC
	UINT32                                                 reserved3189;	//0xC49034B0
	UINT32                                                 reserved3190;	//0xC49034B4
	UINT32                                                 reserved3191;	//0xC49034B8
	UINT32                                                 reserved3192;	//0xC49034BC
	UINT32                                                 reserved3193;	//0xC49034C0
	UINT32                                                 reserved3194;	//0xC49034C4
	UINT32                                                 reserved3195;	//0xC49034C8
	UINT32                                                 reserved3196;	//0xC49034CC
	UINT32                                                 reserved3197;	//0xC49034D0
	UINT32                                                 reserved3198;	//0xC49034D4
	UINT32                                                 reserved3199;	//0xC49034D8
	UINT32                                                 reserved3200;	//0xC49034DC
	UINT32                                                 reserved3201;	//0xC49034E0
	UINT32                                                 reserved3202;	//0xC49034E4
	UINT32                                                 reserved3203;	//0xC49034E8
	UINT32                                                 reserved3204;	//0xC49034EC
	UINT32                                                 reserved3205;	//0xC49034F0
	UINT32                                                 reserved3206;	//0xC49034F4
	UINT32                                                 reserved3207;	//0xC49034F8
	UINT32                                                 reserved3208;	//0xC49034FC
	UINT32                                                 reserved3209;	//0xC4903500
	UINT32                                                 reserved3210;	//0xC4903504
	UINT32                                                 reserved3211;	//0xC4903508
	UINT32                                                 reserved3212;	//0xC490350C
	UINT32                                                 reserved3213;	//0xC4903510
	UINT32                                                 reserved3214;	//0xC4903514
	UINT32                                                 reserved3215;	//0xC4903518
	UINT32                                                 reserved3216;	//0xC490351C
	UINT32                                                 reserved3217;	//0xC4903520
	UINT32                                                 reserved3218;	//0xC4903524
	UINT32                                                 reserved3219;	//0xC4903528
	UINT32                                                 reserved3220;	//0xC490352C
	UINT32                                                 reserved3221;	//0xC4903530
	UINT32                                                 reserved3222;	//0xC4903534
	UINT32                                                 reserved3223;	//0xC4903538
	UINT32                                                 reserved3224;	//0xC490353C
	UINT32                                                 reserved3225;	//0xC4903540
	UINT32                                                 reserved3226;	//0xC4903544
	UINT32                                                 reserved3227;	//0xC4903548
	UINT32                                                 reserved3228;	//0xC490354C
	UINT32                                                 reserved3229;	//0xC4903550
	UINT32                                                 reserved3230;	//0xC4903554
	UINT32                                                 reserved3231;	//0xC4903558
	UINT32                                                 reserved3232;	//0xC490355C
	UINT32                                                 reserved3233;	//0xC4903560
	UINT32                                                 reserved3234;	//0xC4903564
	UINT32                                                 reserved3235;	//0xC4903568
	UINT32                                                 reserved3236;	//0xC490356C
	UINT32                                                 reserved3237;	//0xC4903570
	UINT32                                                 reserved3238;	//0xC4903574
	UINT32                                                 reserved3239;	//0xC4903578
	UINT32                                                 reserved3240;	//0xC490357C
	UINT32                                                 reserved3241;	//0xC4903580
	UINT32                                                 reserved3242;	//0xC4903584
	UINT32                                                 reserved3243;	//0xC4903588
	UINT32                                                 reserved3244;	//0xC490358C
	UINT32                                                 reserved3245;	//0xC4903590
	UINT32                                                 reserved3246;	//0xC4903594
	UINT32                                                 reserved3247;	//0xC4903598
	UINT32                                                 reserved3248;	//0xC490359C
	UINT32                                                 reserved3249;	//0xC49035A0
	UINT32                                                 reserved3250;	//0xC49035A4
	UINT32                                                 reserved3251;	//0xC49035A8
	UINT32                                                 reserved3252;	//0xC49035AC
	UINT32                                                 reserved3253;	//0xC49035B0
	UINT32                                                 reserved3254;	//0xC49035B4
	UINT32                                                 reserved3255;	//0xC49035B8
	UINT32                                                 reserved3256;	//0xC49035BC
	UINT32                                                 reserved3257;	//0xC49035C0
	UINT32                                                 reserved3258;	//0xC49035C4
	UINT32                                                 reserved3259;	//0xC49035C8
	UINT32                                                 reserved3260;	//0xC49035CC
	UINT32                                                 reserved3261;	//0xC49035D0
	UINT32                                                 reserved3262;	//0xC49035D4
	UINT32                                                 reserved3263;	//0xC49035D8
	UINT32                                                 reserved3264;	//0xC49035DC
	UINT32                                                 reserved3265;	//0xC49035E0
	UINT32                                                 reserved3266;	//0xC49035E4
	UINT32                                                 reserved3267;	//0xC49035E8
	UINT32                                                 reserved3268;	//0xC49035EC
	UINT32                                                 reserved3269;	//0xC49035F0
	UINT32                                                 reserved3270;	//0xC49035F4
	UINT32                                                 reserved3271;	//0xC49035F8
	UINT32                                                 reserved3272;	//0xC49035FC
	UINT32                                                 reserved3273;	//0xC4903600
	UINT32                                                 reserved3274;	//0xC4903604
	UINT32                                                 reserved3275;	//0xC4903608
	UINT32                                                 reserved3276;	//0xC490360C
	UINT32                                                 reserved3277;	//0xC4903610
	UINT32                                                 reserved3278;	//0xC4903614
	UINT32                                                 reserved3279;	//0xC4903618
	UINT32                                                 reserved3280;	//0xC490361C
	UINT32                                                 reserved3281;	//0xC4903620
	UINT32                                                 reserved3282;	//0xC4903624
	UINT32                                                 reserved3283;	//0xC4903628
	UINT32                                                 reserved3284;	//0xC490362C
	UINT32                                                 reserved3285;	//0xC4903630
	UINT32                                                 reserved3286;	//0xC4903634
	UINT32                                                 reserved3287;	//0xC4903638
	UINT32                                                 reserved3288;	//0xC490363C
	UINT32                                                 reserved3289;	//0xC4903640
	UINT32                                                 reserved3290;	//0xC4903644
	UINT32                                                 reserved3291;	//0xC4903648
	UINT32                                                 reserved3292;	//0xC490364C
	UINT32                                                 reserved3293;	//0xC4903650
	UINT32                                                 reserved3294;	//0xC4903654
	UINT32                                                 reserved3295;	//0xC4903658
	UINT32                                                 reserved3296;	//0xC490365C
	UINT32                                                 reserved3297;	//0xC4903660
	UINT32                                                 reserved3298;	//0xC4903664
	UINT32                                                 reserved3299;	//0xC4903668
	UINT32                                                 reserved3300;	//0xC490366C
	UINT32                                                 reserved3301;	//0xC4903670
	UINT32                                                 reserved3302;	//0xC4903674
	UINT32                                                 reserved3303;	//0xC4903678
	UINT32                                                 reserved3304;	//0xC490367C
	UINT32                                                 reserved3305;	//0xC4903680
	UINT32                                                 reserved3306;	//0xC4903684
	UINT32                                                 reserved3307;	//0xC4903688
	UINT32                                                 reserved3308;	//0xC490368C
	UINT32                                                 reserved3309;	//0xC4903690
	UINT32                                                 reserved3310;	//0xC4903694
	UINT32                                                 reserved3311;	//0xC4903698
	UINT32                                                 reserved3312;	//0xC490369C
	UINT32                                                 reserved3313;	//0xC49036A0
	UINT32                                                 reserved3314;	//0xC49036A4
	UINT32                                                 reserved3315;	//0xC49036A8
	UINT32                                                 reserved3316;	//0xC49036AC
	UINT32                                                 reserved3317;	//0xC49036B0
	UINT32                                                 reserved3318;	//0xC49036B4
	UINT32                                                 reserved3319;	//0xC49036B8
	UINT32                                                 reserved3320;	//0xC49036BC
	UINT32                                                 reserved3321;	//0xC49036C0
	UINT32                                                 reserved3322;	//0xC49036C4
	UINT32                                                 reserved3323;	//0xC49036C8
	UINT32                                                 reserved3324;	//0xC49036CC
	UINT32                                                 reserved3325;	//0xC49036D0
	UINT32                                                 reserved3326;	//0xC49036D4
	UINT32                                                 reserved3327;	//0xC49036D8
	UINT32                                                 reserved3328;	//0xC49036DC
	UINT32                                                 reserved3329;	//0xC49036E0
	UINT32                                                 reserved3330;	//0xC49036E4
	UINT32                                                 reserved3331;	//0xC49036E8
	UINT32                                                 reserved3332;	//0xC49036EC
	UINT32                                                 reserved3333;	//0xC49036F0
	UINT32                                                 reserved3334;	//0xC49036F4
	UINT32                                                 reserved3335;	//0xC49036F8
	UINT32                                                 reserved3336;	//0xC49036FC
	UINT32                                                 reserved3337;	//0xC4903700
	UINT32                                                 reserved3338;	//0xC4903704
	UINT32                                                 reserved3339;	//0xC4903708
	UINT32                                                 reserved3340;	//0xC490370C
	UINT32                                                 reserved3341;	//0xC4903710
	UINT32                                                 reserved3342;	//0xC4903714
	UINT32                                                 reserved3343;	//0xC4903718
	UINT32                                                 reserved3344;	//0xC490371C
	UINT32                                                 reserved3345;	//0xC4903720
	UINT32                                                 reserved3346;	//0xC4903724
	UINT32                                                 reserved3347;	//0xC4903728
	UINT32                                                 reserved3348;	//0xC490372C
	UINT32                                                 reserved3349;	//0xC4903730
	UINT32                                                 reserved3350;	//0xC4903734
	UINT32                                                 reserved3351;	//0xC4903738
	UINT32                                                 reserved3352;	//0xC490373C
	UINT32                                                 reserved3353;	//0xC4903740
	UINT32                                                 reserved3354;	//0xC4903744
	UINT32                                                 reserved3355;	//0xC4903748
	UINT32                                                 reserved3356;	//0xC490374C
	UINT32                                                 reserved3357;	//0xC4903750
	UINT32                                                 reserved3358;	//0xC4903754
	UINT32                                                 reserved3359;	//0xC4903758
	UINT32                                                 reserved3360;	//0xC490375C
	UINT32                                                 reserved3361;	//0xC4903760
	UINT32                                                 reserved3362;	//0xC4903764
	UINT32                                                 reserved3363;	//0xC4903768
	UINT32                                                 reserved3364;	//0xC490376C
	UINT32                                                 reserved3365;	//0xC4903770
	UINT32                                                 reserved3366;	//0xC4903774
	UINT32                                                 reserved3367;	//0xC4903778
	UINT32                                                 reserved3368;	//0xC490377C
	UINT32                                                 reserved3369;	//0xC4903780
	UINT32                                                 reserved3370;	//0xC4903784
	UINT32                                                 reserved3371;	//0xC4903788
	UINT32                                                 reserved3372;	//0xC490378C
	UINT32                                                 reserved3373;	//0xC4903790
	UINT32                                                 reserved3374;	//0xC4903794
	UINT32                                                 reserved3375;	//0xC4903798
	UINT32                                                 reserved3376;	//0xC490379C
	UINT32                                                 reserved3377;	//0xC49037A0
	UINT32                                                 reserved3378;	//0xC49037A4
	UINT32                                                 reserved3379;	//0xC49037A8
	UINT32                                                 reserved3380;	//0xC49037AC
	UINT32                                                 reserved3381;	//0xC49037B0
	UINT32                                                 reserved3382;	//0xC49037B4
	UINT32                                                 reserved3383;	//0xC49037B8
	UINT32                                                 reserved3384;	//0xC49037BC
	UINT32                                                 reserved3385;	//0xC49037C0
	UINT32                                                 reserved3386;	//0xC49037C4
	UINT32                                                 reserved3387;	//0xC49037C8
	UINT32                                                 reserved3388;	//0xC49037CC
	UINT32                                                 reserved3389;	//0xC49037D0
	UINT32                                                 reserved3390;	//0xC49037D4
	UINT32                                                 reserved3391;	//0xC49037D8
	UINT32                                                 reserved3392;	//0xC49037DC
	UINT32                                                 reserved3393;	//0xC49037E0
	UINT32                                                 reserved3394;	//0xC49037E4
	UINT32                                                 reserved3395;	//0xC49037E8
	UINT32                                                 reserved3396;	//0xC49037EC
	UINT32                                                 reserved3397;	//0xC49037F0
	UINT32                                                 reserved3398;	//0xC49037F4
	UINT32                                                 reserved3399;	//0xC49037F8
	UINT32                                                 reserved3400;	//0xC49037FC
	UINT32                                                 reserved3401;	//0xC4903800
	UINT32                                                 reserved3402;	//0xC4903804
	UINT32                                                 reserved3403;	//0xC4903808
	UINT32                                                 reserved3404;	//0xC490380C
	UINT32                                                 reserved3405;	//0xC4903810
	UINT32                                                 reserved3406;	//0xC4903814
	UINT32                                                 reserved3407;	//0xC4903818
	UINT32                                                 reserved3408;	//0xC490381C
	UINT32                                                 reserved3409;	//0xC4903820
	UINT32                                                 reserved3410;	//0xC4903824
	UINT32                                                 reserved3411;	//0xC4903828
	UINT32                                                 reserved3412;	//0xC490382C
	UINT32                                                 reserved3413;	//0xC4903830
	UINT32                                                 reserved3414;	//0xC4903834
	UINT32                                                 reserved3415;	//0xC4903838
	UINT32                                                 reserved3416;	//0xC490383C
	UINT32                                                 reserved3417;	//0xC4903840
	UINT32                                                 reserved3418;	//0xC4903844
	UINT32                                                 reserved3419;	//0xC4903848
	UINT32                                                 reserved3420;	//0xC490384C
	UINT32                                                 reserved3421;	//0xC4903850
	UINT32                                                 reserved3422;	//0xC4903854
	UINT32                                                 reserved3423;	//0xC4903858
	UINT32                                                 reserved3424;	//0xC490385C
	UINT32                                                 reserved3425;	//0xC4903860
	UINT32                                                 reserved3426;	//0xC4903864
	UINT32                                                 reserved3427;	//0xC4903868
	UINT32                                                 reserved3428;	//0xC490386C
	UINT32                                                 reserved3429;	//0xC4903870
	UINT32                                                 reserved3430;	//0xC4903874
	UINT32                                                 reserved3431;	//0xC4903878
	UINT32                                                 reserved3432;	//0xC490387C
	UINT32                                                 reserved3433;	//0xC4903880
	UINT32                                                 reserved3434;	//0xC4903884
	UINT32                                                 reserved3435;	//0xC4903888
	UINT32                                                 reserved3436;	//0xC490388C
	UINT32                                                 reserved3437;	//0xC4903890
	UINT32                                                 reserved3438;	//0xC4903894
	UINT32                                                 reserved3439;	//0xC4903898
	UINT32                                                 reserved3440;	//0xC490389C
	UINT32                                                 reserved3441;	//0xC49038A0
	UINT32                                                 reserved3442;	//0xC49038A4
	UINT32                                                 reserved3443;	//0xC49038A8
	UINT32                                                 reserved3444;	//0xC49038AC
	UINT32                                                 reserved3445;	//0xC49038B0
	UINT32                                                 reserved3446;	//0xC49038B4
	UINT32                                                 reserved3447;	//0xC49038B8
	UINT32                                                 reserved3448;	//0xC49038BC
	UINT32                                                 reserved3449;	//0xC49038C0
	UINT32                                                 reserved3450;	//0xC49038C4
	UINT32                                                 reserved3451;	//0xC49038C8
	UINT32                                                 reserved3452;	//0xC49038CC
	UINT32                                                 reserved3453;	//0xC49038D0
	UINT32                                                 reserved3454;	//0xC49038D4
	UINT32                                                 reserved3455;	//0xC49038D8
	UINT32                                                 reserved3456;	//0xC49038DC
	UINT32                                                 reserved3457;	//0xC49038E0
	UINT32                                                 reserved3458;	//0xC49038E4
	UINT32                                                 reserved3459;	//0xC49038E8
	UINT32                                                 reserved3460;	//0xC49038EC
	UINT32                                                 reserved3461;	//0xC49038F0
	UINT32                                                 reserved3462;	//0xC49038F4
	UINT32                                                 reserved3463;	//0xC49038F8
	UINT32                                                 reserved3464;	//0xC49038FC
	UINT32                                                 reserved3465;	//0xC4903900
	UINT32                                                 reserved3466;	//0xC4903904
	UINT32                                                 reserved3467;	//0xC4903908
	UINT32                                                 reserved3468;	//0xC490390C
	UINT32                                                 reserved3469;	//0xC4903910
	UINT32                                                 reserved3470;	//0xC4903914
	UINT32                                                 reserved3471;	//0xC4903918
	UINT32                                                 reserved3472;	//0xC490391C
	UINT32                                                 reserved3473;	//0xC4903920
	UINT32                                                 reserved3474;	//0xC4903924
	UINT32                                                 reserved3475;	//0xC4903928
	UINT32                                                 reserved3476;	//0xC490392C
	UINT32                                                 reserved3477;	//0xC4903930
	UINT32                                                 reserved3478;	//0xC4903934
	UINT32                                                 reserved3479;	//0xC4903938
	UINT32                                                 reserved3480;	//0xC490393C
	UINT32                                                 reserved3481;	//0xC4903940
	UINT32                                                 reserved3482;	//0xC4903944
	UINT32                                                 reserved3483;	//0xC4903948
	UINT32                                                 reserved3484;	//0xC490394C
	UINT32                                                 reserved3485;	//0xC4903950
	UINT32                                                 reserved3486;	//0xC4903954
	UINT32                                                 reserved3487;	//0xC4903958
	UINT32                                                 reserved3488;	//0xC490395C
	UINT32                                                 reserved3489;	//0xC4903960
	UINT32                                                 reserved3490;	//0xC4903964
	UINT32                                                 reserved3491;	//0xC4903968
	UINT32                                                 reserved3492;	//0xC490396C
	UINT32                                                 reserved3493;	//0xC4903970
	UINT32                                                 reserved3494;	//0xC4903974
	UINT32                                                 reserved3495;	//0xC4903978
	UINT32                                                 reserved3496;	//0xC490397C
	UINT32                                                 reserved3497;	//0xC4903980
	UINT32                                                 reserved3498;	//0xC4903984
	UINT32                                                 reserved3499;	//0xC4903988
	UINT32                                                 reserved3500;	//0xC490398C
	UINT32                                                 reserved3501;	//0xC4903990
	UINT32                                                 reserved3502;	//0xC4903994
	UINT32                                                 reserved3503;	//0xC4903998
	UINT32                                                 reserved3504;	//0xC490399C
	UINT32                                                 reserved3505;	//0xC49039A0
	UINT32                                                 reserved3506;	//0xC49039A4
	UINT32                                                 reserved3507;	//0xC49039A8
	UINT32                                                 reserved3508;	//0xC49039AC
	UINT32                                                 reserved3509;	//0xC49039B0
	UINT32                                                 reserved3510;	//0xC49039B4
	UINT32                                                 reserved3511;	//0xC49039B8
	UINT32                                                 reserved3512;	//0xC49039BC
	UINT32                                                 reserved3513;	//0xC49039C0
	UINT32                                                 reserved3514;	//0xC49039C4
	UINT32                                                 reserved3515;	//0xC49039C8
	UINT32                                                 reserved3516;	//0xC49039CC
	UINT32                                                 reserved3517;	//0xC49039D0
	UINT32                                                 reserved3518;	//0xC49039D4
	UINT32                                                 reserved3519;	//0xC49039D8
	UINT32                                                 reserved3520;	//0xC49039DC
	UINT32                                                 reserved3521;	//0xC49039E0
	UINT32                                                 reserved3522;	//0xC49039E4
	UINT32                                                 reserved3523;	//0xC49039E8
	UINT32                                                 reserved3524;	//0xC49039EC
	UINT32                                                 reserved3525;	//0xC49039F0
	UINT32                                                 reserved3526;	//0xC49039F4
	UINT32                                                 reserved3527;	//0xC49039F8
	UINT32                                                 reserved3528;	//0xC49039FC
	UINT32                                                 reserved3529;	//0xC4903A00
	UINT32                                                 reserved3530;	//0xC4903A04
	UINT32                                                 reserved3531;	//0xC4903A08
	UINT32                                                 reserved3532;	//0xC4903A0C
	UINT32                                                 reserved3533;	//0xC4903A10
	UINT32                                                 reserved3534;	//0xC4903A14
	UINT32                                                 reserved3535;	//0xC4903A18
	UINT32                                                 reserved3536;	//0xC4903A1C
	UINT32                                                 reserved3537;	//0xC4903A20
	UINT32                                                 reserved3538;	//0xC4903A24
	UINT32                                                 reserved3539;	//0xC4903A28
	UINT32                                                 reserved3540;	//0xC4903A2C
	UINT32                                                 reserved3541;	//0xC4903A30
	UINT32                                                 reserved3542;	//0xC4903A34
	UINT32                                                 reserved3543;	//0xC4903A38
	UINT32                                                 reserved3544;	//0xC4903A3C
	UINT32                                                 reserved3545;	//0xC4903A40
	UINT32                                                 reserved3546;	//0xC4903A44
	UINT32                                                 reserved3547;	//0xC4903A48
	UINT32                                                 reserved3548;	//0xC4903A4C
	UINT32                                                 reserved3549;	//0xC4903A50
	UINT32                                                 reserved3550;	//0xC4903A54
	UINT32                                                 reserved3551;	//0xC4903A58
	UINT32                                                 reserved3552;	//0xC4903A5C
	UINT32                                                 reserved3553;	//0xC4903A60
	UINT32                                                 reserved3554;	//0xC4903A64
	UINT32                                                 reserved3555;	//0xC4903A68
	UINT32                                                 reserved3556;	//0xC4903A6C
	UINT32                                                 reserved3557;	//0xC4903A70
	UINT32                                                 reserved3558;	//0xC4903A74
	UINT32                                                 reserved3559;	//0xC4903A78
	UINT32                                                 reserved3560;	//0xC4903A7C
	UINT32                                                 reserved3561;	//0xC4903A80
	UINT32                                                 reserved3562;	//0xC4903A84
	UINT32                                                 reserved3563;	//0xC4903A88
	UINT32                                                 reserved3564;	//0xC4903A8C
	UINT32                                                 reserved3565;	//0xC4903A90
	UINT32                                                 reserved3566;	//0xC4903A94
	UINT32                                                 reserved3567;	//0xC4903A98
	UINT32                                                 reserved3568;	//0xC4903A9C
	UINT32                                                 reserved3569;	//0xC4903AA0
	UINT32                                                 reserved3570;	//0xC4903AA4
	UINT32                                                 reserved3571;	//0xC4903AA8
	UINT32                                                 reserved3572;	//0xC4903AAC
	UINT32                                                 reserved3573;	//0xC4903AB0
	UINT32                                                 reserved3574;	//0xC4903AB4
	UINT32                                                 reserved3575;	//0xC4903AB8
	UINT32                                                 reserved3576;	//0xC4903ABC
	UINT32                                                 reserved3577;	//0xC4903AC0
	UINT32                                                 reserved3578;	//0xC4903AC4
	UINT32                                                 reserved3579;	//0xC4903AC8
	UINT32                                                 reserved3580;	//0xC4903ACC
	UINT32                                                 reserved3581;	//0xC4903AD0
	UINT32                                                 reserved3582;	//0xC4903AD4
	UINT32                                                 reserved3583;	//0xC4903AD8
	UINT32                                                 reserved3584;	//0xC4903ADC
	UINT32                                                 reserved3585;	//0xC4903AE0
	UINT32                                                 reserved3586;	//0xC4903AE4
	UINT32                                                 reserved3587;	//0xC4903AE8
	UINT32                                                 reserved3588;	//0xC4903AEC
	UINT32                                                 reserved3589;	//0xC4903AF0
	UINT32                                                 reserved3590;	//0xC4903AF4
	UINT32                                                 reserved3591;	//0xC4903AF8
	UINT32                                                 reserved3592;	//0xC4903AFC
	UINT32                                                 reserved3593;	//0xC4903B00
	UINT32                                                 reserved3594;	//0xC4903B04
	UINT32                                                 reserved3595;	//0xC4903B08
	UINT32                                                 reserved3596;	//0xC4903B0C
	UINT32                                                 reserved3597;	//0xC4903B10
	UINT32                                                 reserved3598;	//0xC4903B14
	UINT32                                                 reserved3599;	//0xC4903B18
	UINT32                                                 reserved3600;	//0xC4903B1C
	UINT32                                                 reserved3601;	//0xC4903B20
	UINT32                                                 reserved3602;	//0xC4903B24
	UINT32                                                 reserved3603;	//0xC4903B28
	UINT32                                                 reserved3604;	//0xC4903B2C
	UINT32                                                 reserved3605;	//0xC4903B30
	UINT32                                                 reserved3606;	//0xC4903B34
	UINT32                                                 reserved3607;	//0xC4903B38
	UINT32                                                 reserved3608;	//0xC4903B3C
	UINT32                                                 reserved3609;	//0xC4903B40
	UINT32                                                 reserved3610;	//0xC4903B44
	UINT32                                                 reserved3611;	//0xC4903B48
	UINT32                                                 reserved3612;	//0xC4903B4C
	UINT32                                                 reserved3613;	//0xC4903B50
	UINT32                                                 reserved3614;	//0xC4903B54
	UINT32                                                 reserved3615;	//0xC4903B58
	UINT32                                                 reserved3616;	//0xC4903B5C
	UINT32                                                 reserved3617;	//0xC4903B60
	UINT32                                                 reserved3618;	//0xC4903B64
	UINT32                                                 reserved3619;	//0xC4903B68
	UINT32                                                 reserved3620;	//0xC4903B6C
	UINT32                                                 reserved3621;	//0xC4903B70
	UINT32                                                 reserved3622;	//0xC4903B74
	UINT32                                                 reserved3623;	//0xC4903B78
	UINT32                                                 reserved3624;	//0xC4903B7C
	UINT32                                                 reserved3625;	//0xC4903B80
	UINT32                                                 reserved3626;	//0xC4903B84
	UINT32                                                 reserved3627;	//0xC4903B88
	UINT32                                                 reserved3628;	//0xC4903B8C
	UINT32                                                 reserved3629;	//0xC4903B90
	UINT32                                                 reserved3630;	//0xC4903B94
	UINT32                                                 reserved3631;	//0xC4903B98
	UINT32                                                 reserved3632;	//0xC4903B9C
	UINT32                                                 reserved3633;	//0xC4903BA0
	UINT32                                                 reserved3634;	//0xC4903BA4
	UINT32                                                 reserved3635;	//0xC4903BA8
	UINT32                                                 reserved3636;	//0xC4903BAC
	UINT32                                                 reserved3637;	//0xC4903BB0
	UINT32                                                 reserved3638;	//0xC4903BB4
	UINT32                                                 reserved3639;	//0xC4903BB8
	UINT32                                                 reserved3640;	//0xC4903BBC
	UINT32                                                 reserved3641;	//0xC4903BC0
	UINT32                                                 reserved3642;	//0xC4903BC4
	UINT32                                                 reserved3643;	//0xC4903BC8
	UINT32                                                 reserved3644;	//0xC4903BCC
	UINT32                                                 reserved3645;	//0xC4903BD0
	UINT32                                                 reserved3646;	//0xC4903BD4
	UINT32                                                 reserved3647;	//0xC4903BD8
	UINT32                                                 reserved3648;	//0xC4903BDC
	UINT32                                                 reserved3649;	//0xC4903BE0
	UINT32                                                 reserved3650;	//0xC4903BE4
	UINT32                                                 reserved3651;	//0xC4903BE8
	UINT32                                                 reserved3652;	//0xC4903BEC
	UINT32                                                 reserved3653;	//0xC4903BF0
	UINT32                                                 reserved3654;	//0xC4903BF4
	UINT32                                                 reserved3655;	//0xC4903BF8
	UINT32                                                 reserved3656;	//0xC4903BFC
	UINT32                                                 reserved3657;	//0xC4903C00
	UINT32                                                 reserved3658;	//0xC4903C04
	UINT32                                                 reserved3659;	//0xC4903C08
	UINT32                                                 reserved3660;	//0xC4903C0C
	UINT32                                                 reserved3661;	//0xC4903C10
	UINT32                                                 reserved3662;	//0xC4903C14
	UINT32                                                 reserved3663;	//0xC4903C18
	UINT32                                                 reserved3664;	//0xC4903C1C
	UINT32                                                 reserved3665;	//0xC4903C20
	UINT32                                                 reserved3666;	//0xC4903C24
	UINT32                                                 reserved3667;	//0xC4903C28
	UINT32                                                 reserved3668;	//0xC4903C2C
	UINT32                                                 reserved3669;	//0xC4903C30
	UINT32                                                 reserved3670;	//0xC4903C34
	UINT32                                                 reserved3671;	//0xC4903C38
	UINT32                                                 reserved3672;	//0xC4903C3C
	UINT32                                                 reserved3673;	//0xC4903C40
	UINT32                                                 reserved3674;	//0xC4903C44
	UINT32                                                 reserved3675;	//0xC4903C48
	UINT32                                                 reserved3676;	//0xC4903C4C
	UINT32                                                 reserved3677;	//0xC4903C50
	UINT32                                                 reserved3678;	//0xC4903C54
	UINT32                                                 reserved3679;	//0xC4903C58
	UINT32                                                 reserved3680;	//0xC4903C5C
	UINT32                                                 reserved3681;	//0xC4903C60
	UINT32                                                 reserved3682;	//0xC4903C64
	UINT32                                                 reserved3683;	//0xC4903C68
	UINT32                                                 reserved3684;	//0xC4903C6C
	UINT32                                                 reserved3685;	//0xC4903C70
	UINT32                                                 reserved3686;	//0xC4903C74
	UINT32                                                 reserved3687;	//0xC4903C78
	UINT32                                                 reserved3688;	//0xC4903C7C
	UINT32                                                 reserved3689;	//0xC4903C80
	UINT32                                                 reserved3690;	//0xC4903C84
	UINT32                                                 reserved3691;	//0xC4903C88
	UINT32                                                 reserved3692;	//0xC4903C8C
	UINT32                                                 reserved3693;	//0xC4903C90
	UINT32                                                 reserved3694;	//0xC4903C94
	UINT32                                                 reserved3695;	//0xC4903C98
	UINT32                                                 reserved3696;	//0xC4903C9C
	UINT32                                                 reserved3697;	//0xC4903CA0
	UINT32                                                 reserved3698;	//0xC4903CA4
	UINT32                                                 reserved3699;	//0xC4903CA8
	UINT32                                                 reserved3700;	//0xC4903CAC
	UINT32                                                 reserved3701;	//0xC4903CB0
	UINT32                                                 reserved3702;	//0xC4903CB4
	UINT32                                                 reserved3703;	//0xC4903CB8
	UINT32                                                 reserved3704;	//0xC4903CBC
	UINT32                                                 reserved3705;	//0xC4903CC0
	UINT32                                                 reserved3706;	//0xC4903CC4
	UINT32                                                 reserved3707;	//0xC4903CC8
	UINT32                                                 reserved3708;	//0xC4903CCC
	UINT32                                                 reserved3709;	//0xC4903CD0
	UINT32                                                 reserved3710;	//0xC4903CD4
	UINT32                                                 reserved3711;	//0xC4903CD8
	UINT32                                                 reserved3712;	//0xC4903CDC
	UINT32                                                 reserved3713;	//0xC4903CE0
	UINT32                                                 reserved3714;	//0xC4903CE4
	UINT32                                                 reserved3715;	//0xC4903CE8
	UINT32                                                 reserved3716;	//0xC4903CEC
	UINT32                                                 reserved3717;	//0xC4903CF0
	UINT32                                                 reserved3718;	//0xC4903CF4
	UINT32                                                 reserved3719;	//0xC4903CF8
	UINT32                                                 reserved3720;	//0xC4903CFC
	UINT32                                                 reserved3721;	//0xC4903D00
	UINT32                                                 reserved3722;	//0xC4903D04
	UINT32                                                 reserved3723;	//0xC4903D08
	UINT32                                                 reserved3724;	//0xC4903D0C
	UINT32                                                 reserved3725;	//0xC4903D10
	UINT32                                                 reserved3726;	//0xC4903D14
	UINT32                                                 reserved3727;	//0xC4903D18
	UINT32                                                 reserved3728;	//0xC4903D1C
	UINT32                                                 reserved3729;	//0xC4903D20
	UINT32                                                 reserved3730;	//0xC4903D24
	UINT32                                                 reserved3731;	//0xC4903D28
	UINT32                                                 reserved3732;	//0xC4903D2C
	UINT32                                                 reserved3733;	//0xC4903D30
	UINT32                                                 reserved3734;	//0xC4903D34
	UINT32                                                 reserved3735;	//0xC4903D38
	UINT32                                                 reserved3736;	//0xC4903D3C
	UINT32                                                 reserved3737;	//0xC4903D40
	UINT32                                                 reserved3738;	//0xC4903D44
	UINT32                                                 reserved3739;	//0xC4903D48
	UINT32                                                 reserved3740;	//0xC4903D4C
	UINT32                                                 reserved3741;	//0xC4903D50
	UINT32                                                 reserved3742;	//0xC4903D54
	UINT32                                                 reserved3743;	//0xC4903D58
	UINT32                                                 reserved3744;	//0xC4903D5C
	UINT32                                                 reserved3745;	//0xC4903D60
	UINT32                                                 reserved3746;	//0xC4903D64
	UINT32                                                 reserved3747;	//0xC4903D68
	UINT32                                                 reserved3748;	//0xC4903D6C
	UINT32                                                 reserved3749;	//0xC4903D70
	UINT32                                                 reserved3750;	//0xC4903D74
	UINT32                                                 reserved3751;	//0xC4903D78
	UINT32                                                 reserved3752;	//0xC4903D7C
	UINT32                                                 reserved3753;	//0xC4903D80
	UINT32                                                 reserved3754;	//0xC4903D84
	UINT32                                                 reserved3755;	//0xC4903D88
	UINT32                                                 reserved3756;	//0xC4903D8C
	UINT32                                                 reserved3757;	//0xC4903D90
	UINT32                                                 reserved3758;	//0xC4903D94
	UINT32                                                 reserved3759;	//0xC4903D98
	UINT32                                                 reserved3760;	//0xC4903D9C
	UINT32                                                 reserved3761;	//0xC4903DA0
	UINT32                                                 reserved3762;	//0xC4903DA4
	UINT32                                                 reserved3763;	//0xC4903DA8
	UINT32                                                 reserved3764;	//0xC4903DAC
	UINT32                                                 reserved3765;	//0xC4903DB0
	UINT32                                                 reserved3766;	//0xC4903DB4
	UINT32                                                 reserved3767;	//0xC4903DB8
	UINT32                                                 reserved3768;	//0xC4903DBC
	UINT32                                                 reserved3769;	//0xC4903DC0
	UINT32                                                 reserved3770;	//0xC4903DC4
	UINT32                                                 reserved3771;	//0xC4903DC8
	UINT32                                                 reserved3772;	//0xC4903DCC
	UINT32                                                 reserved3773;	//0xC4903DD0
	UINT32                                                 reserved3774;	//0xC4903DD4
	UINT32                                                 reserved3775;	//0xC4903DD8
	UINT32                                                 reserved3776;	//0xC4903DDC
	UINT32                                                 reserved3777;	//0xC4903DE0
	UINT32                                                 reserved3778;	//0xC4903DE4
	UINT32                                                 reserved3779;	//0xC4903DE8
	UINT32                                                 reserved3780;	//0xC4903DEC
	UINT32                                                 reserved3781;	//0xC4903DF0
	UINT32                                                 reserved3782;	//0xC4903DF4
	UINT32                                                 reserved3783;	//0xC4903DF8
	UINT32                                                 reserved3784;	//0xC4903DFC
	UINT32                                                 reserved3785;	//0xC4903E00
	UINT32                                                 reserved3786;	//0xC4903E04
	UINT32                                                 reserved3787;	//0xC4903E08
	UINT32                                                 reserved3788;	//0xC4903E0C
	UINT32                                                 reserved3789;	//0xC4903E10
	UINT32                                                 reserved3790;	//0xC4903E14
	UINT32                                                 reserved3791;	//0xC4903E18
	UINT32                                                 reserved3792;	//0xC4903E1C
	UINT32                                                 reserved3793;	//0xC4903E20
	UINT32                                                 reserved3794;	//0xC4903E24
	UINT32                                                 reserved3795;	//0xC4903E28
	UINT32                                                 reserved3796;	//0xC4903E2C
	UINT32                                                 reserved3797;	//0xC4903E30
	UINT32                                                 reserved3798;	//0xC4903E34
	UINT32                                                 reserved3799;	//0xC4903E38
	UINT32                                                 reserved3800;	//0xC4903E3C
	UINT32                                                 reserved3801;	//0xC4903E40
	UINT32                                                 reserved3802;	//0xC4903E44
	UINT32                                                 reserved3803;	//0xC4903E48
	UINT32                                                 reserved3804;	//0xC4903E4C
	UINT32                                                 reserved3805;	//0xC4903E50
	UINT32                                                 reserved3806;	//0xC4903E54
	UINT32                                                 reserved3807;	//0xC4903E58
	UINT32                                                 reserved3808;	//0xC4903E5C
	UINT32                                                 reserved3809;	//0xC4903E60
	UINT32                                                 reserved3810;	//0xC4903E64
	UINT32                                                 reserved3811;	//0xC4903E68
	UINT32                                                 reserved3812;	//0xC4903E6C
	UINT32                                                 reserved3813;	//0xC4903E70
	UINT32                                                 reserved3814;	//0xC4903E74
	UINT32                                                 reserved3815;	//0xC4903E78
	UINT32                                                 reserved3816;	//0xC4903E7C
	UINT32                                                 reserved3817;	//0xC4903E80
	UINT32                                                 reserved3818;	//0xC4903E84
	UINT32                                                 reserved3819;	//0xC4903E88
	UINT32                                                 reserved3820;	//0xC4903E8C
	UINT32                                                 reserved3821;	//0xC4903E90
	UINT32                                                 reserved3822;	//0xC4903E94
	UINT32                                                 reserved3823;	//0xC4903E98
	UINT32                                                 reserved3824;	//0xC4903E9C
	UINT32                                                 reserved3825;	//0xC4903EA0
	UINT32                                                 reserved3826;	//0xC4903EA4
	UINT32                                                 reserved3827;	//0xC4903EA8
	UINT32                                                 reserved3828;	//0xC4903EAC
	UINT32                                                 reserved3829;	//0xC4903EB0
	UINT32                                                 reserved3830;	//0xC4903EB4
	UINT32                                                 reserved3831;	//0xC4903EB8
	UINT32                                                 reserved3832;	//0xC4903EBC
	UINT32                                                 reserved3833;	//0xC4903EC0
	UINT32                                                 reserved3834;	//0xC4903EC4
	UINT32                                                 reserved3835;	//0xC4903EC8
	UINT32                                                 reserved3836;	//0xC4903ECC
	UINT32                                                 reserved3837;	//0xC4903ED0
	UINT32                                                 reserved3838;	//0xC4903ED4
	UINT32                                                 reserved3839;	//0xC4903ED8
	UINT32                                                 reserved3840;	//0xC4903EDC
	UINT32                                                 reserved3841;	//0xC4903EE0
	UINT32                                                 reserved3842;	//0xC4903EE4
	UINT32                                                 reserved3843;	//0xC4903EE8
	UINT32                                                 reserved3844;	//0xC4903EEC
	UINT32                                                 reserved3845;	//0xC4903EF0
	UINT32                                                 reserved3846;	//0xC4903EF4
	UINT32                                                 reserved3847;	//0xC4903EF8
	UINT32                                                 reserved3848;	//0xC4903EFC
	UINT32                                                 reserved3849;	//0xC4903F00
	UINT32                                                 reserved3850;	//0xC4903F04
	UINT32                                                 reserved3851;	//0xC4903F08
	UINT32                                                 reserved3852;	//0xC4903F0C
	UINT32                                                 reserved3853;	//0xC4903F10
	UINT32                                                 reserved3854;	//0xC4903F14
	UINT32                                                 reserved3855;	//0xC4903F18
	UINT32                                                 reserved3856;	//0xC4903F1C
	UINT32                                                 reserved3857;	//0xC4903F20
	UINT32                                                 reserved3858;	//0xC4903F24
	UINT32                                                 reserved3859;	//0xC4903F28
	UINT32                                                 reserved3860;	//0xC4903F2C
	UINT32                                                 reserved3861;	//0xC4903F30
	UINT32                                                 reserved3862;	//0xC4903F34
	UINT32                                                 reserved3863;	//0xC4903F38
	UINT32                                                 reserved3864;	//0xC4903F3C
	UINT32                                                 reserved3865;	//0xC4903F40
	UINT32                                                 reserved3866;	//0xC4903F44
	UINT32                                                 reserved3867;	//0xC4903F48
	UINT32                                                 reserved3868;	//0xC4903F4C
	UINT32                                                 reserved3869;	//0xC4903F50
	UINT32                                                 reserved3870;	//0xC4903F54
	UINT32                                                 reserved3871;	//0xC4903F58
	UINT32                                                 reserved3872;	//0xC4903F5C
	UINT32                                                 reserved3873;	//0xC4903F60
	UINT32                                                 reserved3874;	//0xC4903F64
	UINT32                                                 reserved3875;	//0xC4903F68
	UINT32                                                 reserved3876;	//0xC4903F6C
	UINT32                                                 reserved3877;	//0xC4903F70
	UINT32                                                 reserved3878;	//0xC4903F74
	UINT32                                                 reserved3879;	//0xC4903F78
	UINT32                                                 reserved3880;	//0xC4903F7C
	UINT32                                                 reserved3881;	//0xC4903F80
	UINT32                                                 reserved3882;	//0xC4903F84
	UINT32                                                 reserved3883;	//0xC4903F88
	UINT32                                                 reserved3884;	//0xC4903F8C
	UINT32                                                 reserved3885;	//0xC4903F90
	UINT32                                                 reserved3886;	//0xC4903F94
	UINT32                                                 reserved3887;	//0xC4903F98
	UINT32                                                 reserved3888;	//0xC4903F9C
	UINT32                                                 reserved3889;	//0xC4903FA0
	UINT32                                                 reserved3890;	//0xC4903FA4
	UINT32                                                 reserved3891;	//0xC4903FA8
	UINT32                                                 reserved3892;	//0xC4903FAC
	UINT32                                                 reserved3893;	//0xC4903FB0
	UINT32                                                 reserved3894;	//0xC4903FB4
	UINT32                                                 reserved3895;	//0xC4903FB8
	UINT32                                                 reserved3896;	//0xC4903FBC
	UINT32                                                 reserved3897;	//0xC4903FC0
	UINT32                                                 reserved3898;	//0xC4903FC4
	UINT32                                                 reserved3899;	//0xC4903FC8
	UINT32                                                 reserved3900;	//0xC4903FCC
	UINT32                                                 reserved3901;	//0xC4903FD0
	UINT32                                                 reserved3902;	//0xC4903FD4
	UINT32                                                 reserved3903;	//0xC4903FD8
	UINT32                                                 reserved3904;	//0xC4903FDC
	UINT32                                                 reserved3905;	//0xC4903FE0
	UINT32                                                 reserved3906;	//0xC4903FE4
	UINT32                                                 reserved3907;	//0xC4903FE8
	UINT32                                                 reserved3908;	//0xC4903FEC
	UINT32                                                 reserved3909;	//0xC4903FF0
	UINT32                                                 reserved3910;	//0xC4903FF4
	UINT32                                                 reserved3911;	//0xC4903FF8
	UINT32                                                 reserved3912;	//0xC4903FFC
	UINT32                                                 reserved3913;	//0xC4904000
	UINT32                                                 reserved3914;	//0xC4904004
	UINT32                                                 reserved3915;	//0xC4904008
	UINT32                                                 reserved3916;	//0xC490400C
	UINT32                                                 reserved3917;	//0xC4904010
	UINT32                                                 reserved3918;	//0xC4904014
	UINT32                                                 reserved3919;	//0xC4904018
	UINT32                                                 reserved3920;	//0xC490401C
	UINT32                                                 reserved3921;	//0xC4904020
	UINT32                                                 reserved3922;	//0xC4904024
	UINT32                                                 reserved3923;	//0xC4904028
	UINT32                                                 reserved3924;	//0xC490402C
	UINT32                                                 reserved3925;	//0xC4904030
	UINT32                                                 reserved3926;	//0xC4904034
	UINT32                                                 reserved3927;	//0xC4904038
	UINT32                                                 reserved3928;	//0xC490403C
	UINT32                                                 reserved3929;	//0xC4904040
	UINT32                                                 reserved3930;	//0xC4904044
	UINT32                                                 reserved3931;	//0xC4904048
	UINT32                                                 reserved3932;	//0xC490404C
	UINT32                                                 reserved3933;	//0xC4904050
	UINT32                                                 reserved3934;	//0xC4904054
	UINT32                                                 reserved3935;	//0xC4904058
	UINT32                                                 reserved3936;	//0xC490405C
	UINT32                                                 reserved3937;	//0xC4904060
	UINT32                                                 reserved3938;	//0xC4904064
	UINT32                                                 reserved3939;	//0xC4904068
	UINT32                                                 reserved3940;	//0xC490406C
	UINT32                                                 reserved3941;	//0xC4904070
	UINT32                                                 reserved3942;	//0xC4904074
	UINT32                                                 reserved3943;	//0xC4904078
	UINT32                                                 reserved3944;	//0xC490407C
	UINT32                                                 reserved3945;	//0xC4904080
	UINT32                                                 reserved3946;	//0xC4904084
	UINT32                                                 reserved3947;	//0xC4904088
	UINT32                                                 reserved3948;	//0xC490408C
	UINT32                                                 reserved3949;	//0xC4904090
	UINT32                                                 reserved3950;	//0xC4904094
	UINT32                                                 reserved3951;	//0xC4904098
	UINT32                                                 reserved3952;	//0xC490409C
	UINT32                                                 reserved3953;	//0xC49040A0
	UINT32                                                 reserved3954;	//0xC49040A4
	UINT32                                                 reserved3955;	//0xC49040A8
	UINT32                                                 reserved3956;	//0xC49040AC
	UINT32                                                 reserved3957;	//0xC49040B0
	UINT32                                                 reserved3958;	//0xC49040B4
	UINT32                                                 reserved3959;	//0xC49040B8
	UINT32                                                 reserved3960;	//0xC49040BC
	UINT32                                                 reserved3961;	//0xC49040C0
	UINT32                                                 reserved3962;	//0xC49040C4
	UINT32                                                 reserved3963;	//0xC49040C8
	UINT32                                                 reserved3964;	//0xC49040CC
	UINT32                                                 reserved3965;	//0xC49040D0
	UINT32                                                 reserved3966;	//0xC49040D4
	UINT32                                                 reserved3967;	//0xC49040D8
	UINT32                                                 reserved3968;	//0xC49040DC
	UINT32                                                 reserved3969;	//0xC49040E0
	UINT32                                                 reserved3970;	//0xC49040E4
	UINT32                                                 reserved3971;	//0xC49040E8
	UINT32                                                 reserved3972;	//0xC49040EC
	UINT32                                                 reserved3973;	//0xC49040F0
	UINT32                                                 reserved3974;	//0xC49040F4
	UINT32                                                 reserved3975;	//0xC49040F8
	UINT32                                                 reserved3976;	//0xC49040FC
	UINT32                                                 reserved3977;	//0xC4904100
	UINT32                                                 reserved3978;	//0xC4904104
	UINT32                                                 reserved3979;	//0xC4904108
	UINT32                                                 reserved3980;	//0xC490410C
	UINT32                                                 reserved3981;	//0xC4904110
	UINT32                                                 reserved3982;	//0xC4904114
	UINT32                                                 reserved3983;	//0xC4904118
	UINT32                                                 reserved3984;	//0xC490411C
	UINT32                                                 reserved3985;	//0xC4904120
	UINT32                                                 reserved3986;	//0xC4904124
	UINT32                                                 reserved3987;	//0xC4904128
	UINT32                                                 reserved3988;	//0xC490412C
	UINT32                                                 reserved3989;	//0xC4904130
	UINT32                                                 reserved3990;	//0xC4904134
	UINT32                                                 reserved3991;	//0xC4904138
	UINT32                                                 reserved3992;	//0xC490413C
	UINT32                                                 reserved3993;	//0xC4904140
	UINT32                                                 reserved3994;	//0xC4904144
	UINT32                                                 reserved3995;	//0xC4904148
	UINT32                                                 reserved3996;	//0xC490414C
	UINT32                                                 reserved3997;	//0xC4904150
	UINT32                                                 reserved3998;	//0xC4904154
	UINT32                                                 reserved3999;	//0xC4904158
	UINT32                                                 reserved4000;	//0xC490415C
	UINT32                                                 reserved4001;	//0xC4904160
	UINT32                                                 reserved4002;	//0xC4904164
	UINT32                                                 reserved4003;	//0xC4904168
	UINT32                                                 reserved4004;	//0xC490416C
	UINT32                                                 reserved4005;	//0xC4904170
	UINT32                                                 reserved4006;	//0xC4904174
	UINT32                                                 reserved4007;	//0xC4904178
	UINT32                                                 reserved4008;	//0xC490417C
	UINT32                                                 reserved4009;	//0xC4904180
	UINT32                                                 reserved4010;	//0xC4904184
	UINT32                                                 reserved4011;	//0xC4904188
	UINT32                                                 reserved4012;	//0xC490418C
	UINT32                                                 reserved4013;	//0xC4904190
	UINT32                                                 reserved4014;	//0xC4904194
	UINT32                                                 reserved4015;	//0xC4904198
	UINT32                                                 reserved4016;	//0xC490419C
	UINT32                                                 reserved4017;	//0xC49041A0
	UINT32                                                 reserved4018;	//0xC49041A4
	UINT32                                                 reserved4019;	//0xC49041A8
	UINT32                                                 reserved4020;	//0xC49041AC
	UINT32                                                 reserved4021;	//0xC49041B0
	UINT32                                                 reserved4022;	//0xC49041B4
	UINT32                                                 reserved4023;	//0xC49041B8
	UINT32                                                 reserved4024;	//0xC49041BC
	UINT32                                                 reserved4025;	//0xC49041C0
	UINT32                                                 reserved4026;	//0xC49041C4
	UINT32                                                 reserved4027;	//0xC49041C8
	UINT32                                                 reserved4028;	//0xC49041CC
	UINT32                                                 reserved4029;	//0xC49041D0
	UINT32                                                 reserved4030;	//0xC49041D4
	UINT32                                                 reserved4031;	//0xC49041D8
	UINT32                                                 reserved4032;	//0xC49041DC
	UINT32                                                 reserved4033;	//0xC49041E0
	UINT32                                                 reserved4034;	//0xC49041E4
	UINT32                                                 reserved4035;	//0xC49041E8
	UINT32                                                 reserved4036;	//0xC49041EC
	UINT32                                                 reserved4037;	//0xC49041F0
	UINT32                                                 reserved4038;	//0xC49041F4
	UINT32                                                 reserved4039;	//0xC49041F8
	UINT32                                                 reserved4040;	//0xC49041FC
	UINT32                                                 reserved4041;	//0xC4904200
	UINT32                                                 reserved4042;	//0xC4904204
	UINT32                                                 reserved4043;	//0xC4904208
	UINT32                                                 reserved4044;	//0xC490420C
	UINT32                                                 reserved4045;	//0xC4904210
	UINT32                                                 reserved4046;	//0xC4904214
	UINT32                                                 reserved4047;	//0xC4904218
	UINT32                                                 reserved4048;	//0xC490421C
	UINT32                                                 reserved4049;	//0xC4904220
	UINT32                                                 reserved4050;	//0xC4904224
	UINT32                                                 reserved4051;	//0xC4904228
	UINT32                                                 reserved4052;	//0xC490422C
	UINT32                                                 reserved4053;	//0xC4904230
	UINT32                                                 reserved4054;	//0xC4904234
	UINT32                                                 reserved4055;	//0xC4904238
	UINT32                                                 reserved4056;	//0xC490423C
	UINT32                                                 reserved4057;	//0xC4904240
	UINT32                                                 reserved4058;	//0xC4904244
	UINT32                                                 reserved4059;	//0xC4904248
	UINT32                                                 reserved4060;	//0xC490424C
	UINT32                                                 reserved4061;	//0xC4904250
	UINT32                                                 reserved4062;	//0xC4904254
	UINT32                                                 reserved4063;	//0xC4904258
	UINT32                                                 reserved4064;	//0xC490425C
	UINT32                                                 reserved4065;	//0xC4904260
	UINT32                                                 reserved4066;	//0xC4904264
	UINT32                                                 reserved4067;	//0xC4904268
	UINT32                                                 reserved4068;	//0xC490426C
	UINT32                                                 reserved4069;	//0xC4904270
	UINT32                                                 reserved4070;	//0xC4904274
	UINT32                                                 reserved4071;	//0xC4904278
	UINT32                                                 reserved4072;	//0xC490427C
	UINT32                                                 reserved4073;	//0xC4904280
	UINT32                                                 reserved4074;	//0xC4904284
	UINT32                                                 reserved4075;	//0xC4904288
	UINT32                                                 reserved4076;	//0xC490428C
	UINT32                                                 reserved4077;	//0xC4904290
	UINT32                                                 reserved4078;	//0xC4904294
	UINT32                                                 reserved4079;	//0xC4904298
	UINT32                                                 reserved4080;	//0xC490429C
	UINT32                                                 reserved4081;	//0xC49042A0
	UINT32                                                 reserved4082;	//0xC49042A4
	UINT32                                                 reserved4083;	//0xC49042A8
	UINT32                                                 reserved4084;	//0xC49042AC
	UINT32                                                 reserved4085;	//0xC49042B0
	UINT32                                                 reserved4086;	//0xC49042B4
	UINT32                                                 reserved4087;	//0xC49042B8
	UINT32                                                 reserved4088;	//0xC49042BC
	UINT32                                                 reserved4089;	//0xC49042C0
	UINT32                                                 reserved4090;	//0xC49042C4
	UINT32                                                 reserved4091;	//0xC49042C8
	UINT32                                                 reserved4092;	//0xC49042CC
	UINT32                                                 reserved4093;	//0xC49042D0
	UINT32                                                 reserved4094;	//0xC49042D4
	UINT32                                                 reserved4095;	//0xC49042D8
	UINT32                                                 reserved4096;	//0xC49042DC
	UINT32                                                 reserved4097;	//0xC49042E0
	UINT32                                                 reserved4098;	//0xC49042E4
	UINT32                                                 reserved4099;	//0xC49042E8
	UINT32                                                 reserved4100;	//0xC49042EC
	UINT32                                                 reserved4101;	//0xC49042F0
	UINT32                                                 reserved4102;	//0xC49042F4
	UINT32                                                 reserved4103;	//0xC49042F8
	UINT32                                                 reserved4104;	//0xC49042FC
	UINT32                                                 reserved4105;	//0xC4904300
	UINT32                                                 reserved4106;	//0xC4904304
	UINT32                                                 reserved4107;	//0xC4904308
	UINT32                                                 reserved4108;	//0xC490430C
	UINT32                                                 reserved4109;	//0xC4904310
	UINT32                                                 reserved4110;	//0xC4904314
	UINT32                                                 reserved4111;	//0xC4904318
	UINT32                                                 reserved4112;	//0xC490431C
	UINT32                                                 reserved4113;	//0xC4904320
	UINT32                                                 reserved4114;	//0xC4904324
	UINT32                                                 reserved4115;	//0xC4904328
	UINT32                                                 reserved4116;	//0xC490432C
	UINT32                                                 reserved4117;	//0xC4904330
	UINT32                                                 reserved4118;	//0xC4904334
	UINT32                                                 reserved4119;	//0xC4904338
	UINT32                                                 reserved4120;	//0xC490433C
	UINT32                                                 reserved4121;	//0xC4904340
	UINT32                                                 reserved4122;	//0xC4904344
	UINT32                                                 reserved4123;	//0xC4904348
	UINT32                                                 reserved4124;	//0xC490434C
	UINT32                                                 reserved4125;	//0xC4904350
	UINT32                                                 reserved4126;	//0xC4904354
	UINT32                                                 reserved4127;	//0xC4904358
	UINT32                                                 reserved4128;	//0xC490435C
	UINT32                                                 reserved4129;	//0xC4904360
	UINT32                                                 reserved4130;	//0xC4904364
	UINT32                                                 reserved4131;	//0xC4904368
	UINT32                                                 reserved4132;	//0xC490436C
	UINT32                                                 reserved4133;	//0xC4904370
	UINT32                                                 reserved4134;	//0xC4904374
	UINT32                                                 reserved4135;	//0xC4904378
	UINT32                                                 reserved4136;	//0xC490437C
	UINT32                                                 reserved4137;	//0xC4904380
	UINT32                                                 reserved4138;	//0xC4904384
	UINT32                                                 reserved4139;	//0xC4904388
	UINT32                                                 reserved4140;	//0xC490438C
	UINT32                                                 reserved4141;	//0xC4904390
	UINT32                                                 reserved4142;	//0xC4904394
	UINT32                                                 reserved4143;	//0xC4904398
	UINT32                                                 reserved4144;	//0xC490439C
	UINT32                                                 reserved4145;	//0xC49043A0
	UINT32                                                 reserved4146;	//0xC49043A4
	UINT32                                                 reserved4147;	//0xC49043A8
	UINT32                                                 reserved4148;	//0xC49043AC
	UINT32                                                 reserved4149;	//0xC49043B0
	UINT32                                                 reserved4150;	//0xC49043B4
	UINT32                                                 reserved4151;	//0xC49043B8
	UINT32                                                 reserved4152;	//0xC49043BC
	UINT32                                                 reserved4153;	//0xC49043C0
	UINT32                                                 reserved4154;	//0xC49043C4
	UINT32                                                 reserved4155;	//0xC49043C8
	UINT32                                                 reserved4156;	//0xC49043CC
	UINT32                                                 reserved4157;	//0xC49043D0
	UINT32                                                 reserved4158;	//0xC49043D4
	UINT32                                                 reserved4159;	//0xC49043D8
	UINT32                                                 reserved4160;	//0xC49043DC
	UINT32                                                 reserved4161;	//0xC49043E0
	UINT32                                                 reserved4162;	//0xC49043E4
	UINT32                                                 reserved4163;	//0xC49043E8
	UINT32                                                 reserved4164;	//0xC49043EC
	UINT32                                                 reserved4165;	//0xC49043F0
	UINT32                                                 reserved4166;	//0xC49043F4
	UINT32                                                 reserved4167;	//0xC49043F8
	UINT32                                                 reserved4168;	//0xC49043FC
	UINT32                                                 reserved4169;	//0xC4904400
	UINT32                                                 reserved4170;	//0xC4904404
	UINT32                                                 reserved4171;	//0xC4904408
	UINT32                                                 reserved4172;	//0xC490440C
	UINT32                                                 reserved4173;	//0xC4904410
	UINT32                                                 reserved4174;	//0xC4904414
	UINT32                                                 reserved4175;	//0xC4904418
	UINT32                                                 reserved4176;	//0xC490441C
	UINT32                                                 reserved4177;	//0xC4904420
	UINT32                                                 reserved4178;	//0xC4904424
	UINT32                                                 reserved4179;	//0xC4904428
	UINT32                                                 reserved4180;	//0xC490442C
	UINT32                                                 reserved4181;	//0xC4904430
	UINT32                                                 reserved4182;	//0xC4904434
	UINT32                                                 reserved4183;	//0xC4904438
	UINT32                                                 reserved4184;	//0xC490443C
	UINT32                                                 reserved4185;	//0xC4904440
	UINT32                                                 reserved4186;	//0xC4904444
	UINT32                                                 reserved4187;	//0xC4904448
	UINT32                                                 reserved4188;	//0xC490444C
	UINT32                                                 reserved4189;	//0xC4904450
	UINT32                                                 reserved4190;	//0xC4904454
	UINT32                                                 reserved4191;	//0xC4904458
	UINT32                                                 reserved4192;	//0xC490445C
	UINT32                                                 reserved4193;	//0xC4904460
	UINT32                                                 reserved4194;	//0xC4904464
	UINT32                                                 reserved4195;	//0xC4904468
	UINT32                                                 reserved4196;	//0xC490446C
	UINT32                                                 reserved4197;	//0xC4904470
	UINT32                                                 reserved4198;	//0xC4904474
	UINT32                                                 reserved4199;	//0xC4904478
	UINT32                                                 reserved4200;	//0xC490447C
	UINT32                                                 reserved4201;	//0xC4904480
	UINT32                                                 reserved4202;	//0xC4904484
	UINT32                                                 reserved4203;	//0xC4904488
	UINT32                                                 reserved4204;	//0xC490448C
	UINT32                                                 reserved4205;	//0xC4904490
	UINT32                                                 reserved4206;	//0xC4904494
	UINT32                                                 reserved4207;	//0xC4904498
	UINT32                                                 reserved4208;	//0xC490449C
	UINT32                                                 reserved4209;	//0xC49044A0
	UINT32                                                 reserved4210;	//0xC49044A4
	UINT32                                                 reserved4211;	//0xC49044A8
	UINT32                                                 reserved4212;	//0xC49044AC
	UINT32                                                 reserved4213;	//0xC49044B0
	UINT32                                                 reserved4214;	//0xC49044B4
	UINT32                                                 reserved4215;	//0xC49044B8
	UINT32                                                 reserved4216;	//0xC49044BC
	UINT32                                                 reserved4217;	//0xC49044C0
	UINT32                                                 reserved4218;	//0xC49044C4
	UINT32                                                 reserved4219;	//0xC49044C8
	UINT32                                                 reserved4220;	//0xC49044CC
	UINT32                                                 reserved4221;	//0xC49044D0
	UINT32                                                 reserved4222;	//0xC49044D4
	UINT32                                                 reserved4223;	//0xC49044D8
	UINT32                                                 reserved4224;	//0xC49044DC
	UINT32                                                 reserved4225;	//0xC49044E0
	UINT32                                                 reserved4226;	//0xC49044E4
	UINT32                                                 reserved4227;	//0xC49044E8
	UINT32                                                 reserved4228;	//0xC49044EC
	UINT32                                                 reserved4229;	//0xC49044F0
	UINT32                                                 reserved4230;	//0xC49044F4
	UINT32                                                 reserved4231;	//0xC49044F8
	UINT32                                                 reserved4232;	//0xC49044FC
	UINT32                                                 reserved4233;	//0xC4904500
	UINT32                                                 reserved4234;	//0xC4904504
	UINT32                                                 reserved4235;	//0xC4904508
	UINT32                                                 reserved4236;	//0xC490450C
	UINT32                                                 reserved4237;	//0xC4904510
	UINT32                                                 reserved4238;	//0xC4904514
	UINT32                                                 reserved4239;	//0xC4904518
	UINT32                                                 reserved4240;	//0xC490451C
	UINT32                                                 reserved4241;	//0xC4904520
	UINT32                                                 reserved4242;	//0xC4904524
	UINT32                                                 reserved4243;	//0xC4904528
	UINT32                                                 reserved4244;	//0xC490452C
	UINT32                                                 reserved4245;	//0xC4904530
	UINT32                                                 reserved4246;	//0xC4904534
	UINT32                                                 reserved4247;	//0xC4904538
	UINT32                                                 reserved4248;	//0xC490453C
	UINT32                                                 reserved4249;	//0xC4904540
	UINT32                                                 reserved4250;	//0xC4904544
	UINT32                                                 reserved4251;	//0xC4904548
	UINT32                                                 reserved4252;	//0xC490454C
	UINT32                                                 reserved4253;	//0xC4904550
	UINT32                                                 reserved4254;	//0xC4904554
	UINT32                                                 reserved4255;	//0xC4904558
	UINT32                                                 reserved4256;	//0xC490455C
	UINT32                                                 reserved4257;	//0xC4904560
	UINT32                                                 reserved4258;	//0xC4904564
	UINT32                                                 reserved4259;	//0xC4904568
	UINT32                                                 reserved4260;	//0xC490456C
	UINT32                                                 reserved4261;	//0xC4904570
	UINT32                                                 reserved4262;	//0xC4904574
	UINT32                                                 reserved4263;	//0xC4904578
	UINT32                                                 reserved4264;	//0xC490457C
	UINT32                                                 reserved4265;	//0xC4904580
	UINT32                                                 reserved4266;	//0xC4904584
	UINT32                                                 reserved4267;	//0xC4904588
	UINT32                                                 reserved4268;	//0xC490458C
	UINT32                                                 reserved4269;	//0xC4904590
	UINT32                                                 reserved4270;	//0xC4904594
	UINT32                                                 reserved4271;	//0xC4904598
	UINT32                                                 reserved4272;	//0xC490459C
	UINT32                                                 reserved4273;	//0xC49045A0
	UINT32                                                 reserved4274;	//0xC49045A4
	UINT32                                                 reserved4275;	//0xC49045A8
	UINT32                                                 reserved4276;	//0xC49045AC
	UINT32                                                 reserved4277;	//0xC49045B0
	UINT32                                                 reserved4278;	//0xC49045B4
	UINT32                                                 reserved4279;	//0xC49045B8
	UINT32                                                 reserved4280;	//0xC49045BC
	UINT32                                                 reserved4281;	//0xC49045C0
	UINT32                                                 reserved4282;	//0xC49045C4
	UINT32                                                 reserved4283;	//0xC49045C8
	UINT32                                                 reserved4284;	//0xC49045CC
	UINT32                                                 reserved4285;	//0xC49045D0
	UINT32                                                 reserved4286;	//0xC49045D4
	UINT32                                                 reserved4287;	//0xC49045D8
	UINT32                                                 reserved4288;	//0xC49045DC
	UINT32                                                 reserved4289;	//0xC49045E0
	UINT32                                                 reserved4290;	//0xC49045E4
	UINT32                                                 reserved4291;	//0xC49045E8
	UINT32                                                 reserved4292;	//0xC49045EC
	UINT32                                                 reserved4293;	//0xC49045F0
	UINT32                                                 reserved4294;	//0xC49045F4
	UINT32                                                 reserved4295;	//0xC49045F8
	UINT32                                                 reserved4296;	//0xC49045FC
	UINT32                                                 reserved4297;	//0xC4904600
	UINT32                                                 reserved4298;	//0xC4904604
	UINT32                                                 reserved4299;	//0xC4904608
	UINT32                                                 reserved4300;	//0xC490460C
	UINT32                                                 reserved4301;	//0xC4904610
	UINT32                                                 reserved4302;	//0xC4904614
	UINT32                                                 reserved4303;	//0xC4904618
	UINT32                                                 reserved4304;	//0xC490461C
	UINT32                                                 reserved4305;	//0xC4904620
	UINT32                                                 reserved4306;	//0xC4904624
	UINT32                                                 reserved4307;	//0xC4904628
	UINT32                                                 reserved4308;	//0xC490462C
	UINT32                                                 reserved4309;	//0xC4904630
	UINT32                                                 reserved4310;	//0xC4904634
	UINT32                                                 reserved4311;	//0xC4904638
	UINT32                                                 reserved4312;	//0xC490463C
	UINT32                                                 reserved4313;	//0xC4904640
	UINT32                                                 reserved4314;	//0xC4904644
	UINT32                                                 reserved4315;	//0xC4904648
	UINT32                                                 reserved4316;	//0xC490464C
	UINT32                                                 reserved4317;	//0xC4904650
	UINT32                                                 reserved4318;	//0xC4904654
	UINT32                                                 reserved4319;	//0xC4904658
	UINT32                                                 reserved4320;	//0xC490465C
	UINT32                                                 reserved4321;	//0xC4904660
	UINT32                                                 reserved4322;	//0xC4904664
	UINT32                                                 reserved4323;	//0xC4904668
	UINT32                                                 reserved4324;	//0xC490466C
	UINT32                                                 reserved4325;	//0xC4904670
	UINT32                                                 reserved4326;	//0xC4904674
	UINT32                                                 reserved4327;	//0xC4904678
	UINT32                                                 reserved4328;	//0xC490467C
	UINT32                                                 reserved4329;	//0xC4904680
	UINT32                                                 reserved4330;	//0xC4904684
	UINT32                                                 reserved4331;	//0xC4904688
	UINT32                                                 reserved4332;	//0xC490468C
	UINT32                                                 reserved4333;	//0xC4904690
	UINT32                                                 reserved4334;	//0xC4904694
	UINT32                                                 reserved4335;	//0xC4904698
	UINT32                                                 reserved4336;	//0xC490469C
	UINT32                                                 reserved4337;	//0xC49046A0
	UINT32                                                 reserved4338;	//0xC49046A4
	UINT32                                                 reserved4339;	//0xC49046A8
	UINT32                                                 reserved4340;	//0xC49046AC
	UINT32                                                 reserved4341;	//0xC49046B0
	UINT32                                                 reserved4342;	//0xC49046B4
	UINT32                                                 reserved4343;	//0xC49046B8
	UINT32                                                 reserved4344;	//0xC49046BC
	UINT32                                                 reserved4345;	//0xC49046C0
	UINT32                                                 reserved4346;	//0xC49046C4
	UINT32                                                 reserved4347;	//0xC49046C8
	UINT32                                                 reserved4348;	//0xC49046CC
	UINT32                                                 reserved4349;	//0xC49046D0
	UINT32                                                 reserved4350;	//0xC49046D4
	UINT32                                                 reserved4351;	//0xC49046D8
	UINT32                                                 reserved4352;	//0xC49046DC
	UINT32                                                 reserved4353;	//0xC49046E0
	UINT32                                                 reserved4354;	//0xC49046E4
	UINT32                                                 reserved4355;	//0xC49046E8
	UINT32                                                 reserved4356;	//0xC49046EC
	UINT32                                                 reserved4357;	//0xC49046F0
	UINT32                                                 reserved4358;	//0xC49046F4
	UINT32                                                 reserved4359;	//0xC49046F8
	UINT32                                                 reserved4360;	//0xC49046FC
	UINT32                                                 reserved4361;	//0xC4904700
	UINT32                                                 reserved4362;	//0xC4904704
	UINT32                                                 reserved4363;	//0xC4904708
	UINT32                                                 reserved4364;	//0xC490470C
	UINT32                                                 reserved4365;	//0xC4904710
	UINT32                                                 reserved4366;	//0xC4904714
	UINT32                                                 reserved4367;	//0xC4904718
	UINT32                                                 reserved4368;	//0xC490471C
	UINT32                                                 reserved4369;	//0xC4904720
	UINT32                                                 reserved4370;	//0xC4904724
	UINT32                                                 reserved4371;	//0xC4904728
	UINT32                                                 reserved4372;	//0xC490472C
	UINT32                                                 reserved4373;	//0xC4904730
	UINT32                                                 reserved4374;	//0xC4904734
	UINT32                                                 reserved4375;	//0xC4904738
	UINT32                                                 reserved4376;	//0xC490473C
	UINT32                                                 reserved4377;	//0xC4904740
	UINT32                                                 reserved4378;	//0xC4904744
	UINT32                                                 reserved4379;	//0xC4904748
	UINT32                                                 reserved4380;	//0xC490474C
	UINT32                                                 reserved4381;	//0xC4904750
	UINT32                                                 reserved4382;	//0xC4904754
	UINT32                                                 reserved4383;	//0xC4904758
	UINT32                                                 reserved4384;	//0xC490475C
	UINT32                                                 reserved4385;	//0xC4904760
	UINT32                                                 reserved4386;	//0xC4904764
	UINT32                                                 reserved4387;	//0xC4904768
	UINT32                                                 reserved4388;	//0xC490476C
	UINT32                                                 reserved4389;	//0xC4904770
	UINT32                                                 reserved4390;	//0xC4904774
	UINT32                                                 reserved4391;	//0xC4904778
	UINT32                                                 reserved4392;	//0xC490477C
	UINT32                                                 reserved4393;	//0xC4904780
	UINT32                                                 reserved4394;	//0xC4904784
	UINT32                                                 reserved4395;	//0xC4904788
	UINT32                                                 reserved4396;	//0xC490478C
	UINT32                                                 reserved4397;	//0xC4904790
	UINT32                                                 reserved4398;	//0xC4904794
	UINT32                                                 reserved4399;	//0xC4904798
	UINT32                                                 reserved4400;	//0xC490479C
	UINT32                                                 reserved4401;	//0xC49047A0
	UINT32                                                 reserved4402;	//0xC49047A4
	UINT32                                                 reserved4403;	//0xC49047A8
	UINT32                                                 reserved4404;	//0xC49047AC
	UINT32                                                 reserved4405;	//0xC49047B0
	UINT32                                                 reserved4406;	//0xC49047B4
	UINT32                                                 reserved4407;	//0xC49047B8
	UINT32                                                 reserved4408;	//0xC49047BC
	UINT32                                                 reserved4409;	//0xC49047C0
	UINT32                                                 reserved4410;	//0xC49047C4
	UINT32                                                 reserved4411;	//0xC49047C8
	UINT32                                                 reserved4412;	//0xC49047CC
	UINT32                                                 reserved4413;	//0xC49047D0
	UINT32                                                 reserved4414;	//0xC49047D4
	UINT32                                                 reserved4415;	//0xC49047D8
	UINT32                                                 reserved4416;	//0xC49047DC
	UINT32                                                 reserved4417;	//0xC49047E0
	UINT32                                                 reserved4418;	//0xC49047E4
	UINT32                                                 reserved4419;	//0xC49047E8
	UINT32                                                 reserved4420;	//0xC49047EC
	UINT32                                                 reserved4421;	//0xC49047F0
	UINT32                                                 reserved4422;	//0xC49047F4
	UINT32                                                 reserved4423;	//0xC49047F8
	UINT32                                                 reserved4424;	//0xC49047FC
	UINT32                                                 reserved4425;	//0xC4904800
	UINT32                                                 reserved4426;	//0xC4904804
	UINT32                                                 reserved4427;	//0xC4904808
	UINT32                                                 reserved4428;	//0xC490480C
	UINT32                                                 reserved4429;	//0xC4904810
	UINT32                                                 reserved4430;	//0xC4904814
	UINT32                                                 reserved4431;	//0xC4904818
	UINT32                                                 reserved4432;	//0xC490481C
	UINT32                                                 reserved4433;	//0xC4904820
	UINT32                                                 reserved4434;	//0xC4904824
	UINT32                                                 reserved4435;	//0xC4904828
	UINT32                                                 reserved4436;	//0xC490482C
	UINT32                                                 reserved4437;	//0xC4904830
	UINT32                                                 reserved4438;	//0xC4904834
	UINT32                                                 reserved4439;	//0xC4904838
	UINT32                                                 reserved4440;	//0xC490483C
	UINT32                                                 reserved4441;	//0xC4904840
	UINT32                                                 reserved4442;	//0xC4904844
	UINT32                                                 reserved4443;	//0xC4904848
	UINT32                                                 reserved4444;	//0xC490484C
	UINT32                                                 reserved4445;	//0xC4904850
	UINT32                                                 reserved4446;	//0xC4904854
	UINT32                                                 reserved4447;	//0xC4904858
	UINT32                                                 reserved4448;	//0xC490485C
	UINT32                                                 reserved4449;	//0xC4904860
	UINT32                                                 reserved4450;	//0xC4904864
	UINT32                                                 reserved4451;	//0xC4904868
	UINT32                                                 reserved4452;	//0xC490486C
	UINT32                                                 reserved4453;	//0xC4904870
	UINT32                                                 reserved4454;	//0xC4904874
	UINT32                                                 reserved4455;	//0xC4904878
	UINT32                                                 reserved4456;	//0xC490487C
	UINT32                                                 reserved4457;	//0xC4904880
	UINT32                                                 reserved4458;	//0xC4904884
	UINT32                                                 reserved4459;	//0xC4904888
	UINT32                                                 reserved4460;	//0xC490488C
	UINT32                                                 reserved4461;	//0xC4904890
	UINT32                                                 reserved4462;	//0xC4904894
	UINT32                                                 reserved4463;	//0xC4904898
	UINT32                                                 reserved4464;	//0xC490489C
	UINT32                                                 reserved4465;	//0xC49048A0
	UINT32                                                 reserved4466;	//0xC49048A4
	UINT32                                                 reserved4467;	//0xC49048A8
	UINT32                                                 reserved4468;	//0xC49048AC
	UINT32                                                 reserved4469;	//0xC49048B0
	UINT32                                                 reserved4470;	//0xC49048B4
	UINT32                                                 reserved4471;	//0xC49048B8
	UINT32                                                 reserved4472;	//0xC49048BC
	UINT32                                                 reserved4473;	//0xC49048C0
	UINT32                                                 reserved4474;	//0xC49048C4
	UINT32                                                 reserved4475;	//0xC49048C8
	UINT32                                                 reserved4476;	//0xC49048CC
	UINT32                                                 reserved4477;	//0xC49048D0
	UINT32                                                 reserved4478;	//0xC49048D4
	UINT32                                                 reserved4479;	//0xC49048D8
	UINT32                                                 reserved4480;	//0xC49048DC
	UINT32                                                 reserved4481;	//0xC49048E0
	UINT32                                                 reserved4482;	//0xC49048E4
	UINT32                                                 reserved4483;	//0xC49048E8
	UINT32                                                 reserved4484;	//0xC49048EC
	UINT32                                                 reserved4485;	//0xC49048F0
	UINT32                                                 reserved4486;	//0xC49048F4
	UINT32                                                 reserved4487;	//0xC49048F8
	UINT32                                                 reserved4488;	//0xC49048FC
	UINT32                                                 reserved4489;	//0xC4904900
	UINT32                                                 reserved4490;	//0xC4904904
	UINT32                                                 reserved4491;	//0xC4904908
	UINT32                                                 reserved4492;	//0xC490490C
	UINT32                                                 reserved4493;	//0xC4904910
	UINT32                                                 reserved4494;	//0xC4904914
	UINT32                                                 reserved4495;	//0xC4904918
	UINT32                                                 reserved4496;	//0xC490491C
	UINT32                                                 reserved4497;	//0xC4904920
	UINT32                                                 reserved4498;	//0xC4904924
	UINT32                                                 reserved4499;	//0xC4904928
	UINT32                                                 reserved4500;	//0xC490492C
	UINT32                                                 reserved4501;	//0xC4904930
	UINT32                                                 reserved4502;	//0xC4904934
	UINT32                                                 reserved4503;	//0xC4904938
	UINT32                                                 reserved4504;	//0xC490493C
	UINT32                                                 reserved4505;	//0xC4904940
	UINT32                                                 reserved4506;	//0xC4904944
	UINT32                                                 reserved4507;	//0xC4904948
	UINT32                                                 reserved4508;	//0xC490494C
	UINT32                                                 reserved4509;	//0xC4904950
	UINT32                                                 reserved4510;	//0xC4904954
	UINT32                                                 reserved4511;	//0xC4904958
	UINT32                                                 reserved4512;	//0xC490495C
	UINT32                                                 reserved4513;	//0xC4904960
	UINT32                                                 reserved4514;	//0xC4904964
	UINT32                                                 reserved4515;	//0xC4904968
	UINT32                                                 reserved4516;	//0xC490496C
	UINT32                                                 reserved4517;	//0xC4904970
	UINT32                                                 reserved4518;	//0xC4904974
	UINT32                                                 reserved4519;	//0xC4904978
	UINT32                                                 reserved4520;	//0xC490497C
	UINT32                                                 reserved4521;	//0xC4904980
	UINT32                                                 reserved4522;	//0xC4904984
	UINT32                                                 reserved4523;	//0xC4904988
	UINT32                                                 reserved4524;	//0xC490498C
	UINT32                                                 reserved4525;	//0xC4904990
	UINT32                                                 reserved4526;	//0xC4904994
	UINT32                                                 reserved4527;	//0xC4904998
	UINT32                                                 reserved4528;	//0xC490499C
	UINT32                                                 reserved4529;	//0xC49049A0
	UINT32                                                 reserved4530;	//0xC49049A4
	UINT32                                                 reserved4531;	//0xC49049A8
	UINT32                                                 reserved4532;	//0xC49049AC
	UINT32                                                 reserved4533;	//0xC49049B0
	UINT32                                                 reserved4534;	//0xC49049B4
	UINT32                                                 reserved4535;	//0xC49049B8
	UINT32                                                 reserved4536;	//0xC49049BC
	UINT32                                                 reserved4537;	//0xC49049C0
	UINT32                                                 reserved4538;	//0xC49049C4
	UINT32                                                 reserved4539;	//0xC49049C8
	UINT32                                                 reserved4540;	//0xC49049CC
	UINT32                                                 reserved4541;	//0xC49049D0
	UINT32                                                 reserved4542;	//0xC49049D4
	UINT32                                                 reserved4543;	//0xC49049D8
	UINT32                                                 reserved4544;	//0xC49049DC
	UINT32                                                 reserved4545;	//0xC49049E0
	UINT32                                                 reserved4546;	//0xC49049E4
	UINT32                                                 reserved4547;	//0xC49049E8
	UINT32                                                 reserved4548;	//0xC49049EC
	UINT32                                                 reserved4549;	//0xC49049F0
	UINT32                                                 reserved4550;	//0xC49049F4
	UINT32                                                 reserved4551;	//0xC49049F8
	UINT32                                                 reserved4552;	//0xC49049FC
	UINT32                                                 reserved4553;	//0xC4904A00
	UINT32                                                 reserved4554;	//0xC4904A04
	UINT32                                                 reserved4555;	//0xC4904A08
	UINT32                                                 reserved4556;	//0xC4904A0C
	UINT32                                                 reserved4557;	//0xC4904A10
	UINT32                                                 reserved4558;	//0xC4904A14
	UINT32                                                 reserved4559;	//0xC4904A18
	UINT32                                                 reserved4560;	//0xC4904A1C
	UINT32                                                 reserved4561;	//0xC4904A20
	UINT32                                                 reserved4562;	//0xC4904A24
	UINT32                                                 reserved4563;	//0xC4904A28
	UINT32                                                 reserved4564;	//0xC4904A2C
	UINT32                                                 reserved4565;	//0xC4904A30
	UINT32                                                 reserved4566;	//0xC4904A34
	UINT32                                                 reserved4567;	//0xC4904A38
	UINT32                                                 reserved4568;	//0xC4904A3C
	UINT32                                                 reserved4569;	//0xC4904A40
	UINT32                                                 reserved4570;	//0xC4904A44
	UINT32                                                 reserved4571;	//0xC4904A48
	UINT32                                                 reserved4572;	//0xC4904A4C
	UINT32                                                 reserved4573;	//0xC4904A50
	UINT32                                                 reserved4574;	//0xC4904A54
	UINT32                                                 reserved4575;	//0xC4904A58
	UINT32                                                 reserved4576;	//0xC4904A5C
	UINT32                                                 reserved4577;	//0xC4904A60
	UINT32                                                 reserved4578;	//0xC4904A64
	UINT32                                                 reserved4579;	//0xC4904A68
	UINT32                                                 reserved4580;	//0xC4904A6C
	UINT32                                                 reserved4581;	//0xC4904A70
	UINT32                                                 reserved4582;	//0xC4904A74
	UINT32                                                 reserved4583;	//0xC4904A78
	UINT32                                                 reserved4584;	//0xC4904A7C
	UINT32                                                 reserved4585;	//0xC4904A80
	UINT32                                                 reserved4586;	//0xC4904A84
	UINT32                                                 reserved4587;	//0xC4904A88
	UINT32                                                 reserved4588;	//0xC4904A8C
	UINT32                                                 reserved4589;	//0xC4904A90
	UINT32                                                 reserved4590;	//0xC4904A94
	UINT32                                                 reserved4591;	//0xC4904A98
	UINT32                                                 reserved4592;	//0xC4904A9C
	UINT32                                                 reserved4593;	//0xC4904AA0
	UINT32                                                 reserved4594;	//0xC4904AA4
	UINT32                                                 reserved4595;	//0xC4904AA8
	UINT32                                                 reserved4596;	//0xC4904AAC
	UINT32                                                 reserved4597;	//0xC4904AB0
	UINT32                                                 reserved4598;	//0xC4904AB4
	UINT32                                                 reserved4599;	//0xC4904AB8
	UINT32                                                 reserved4600;	//0xC4904ABC
	UINT32                                                 reserved4601;	//0xC4904AC0
	UINT32                                                 reserved4602;	//0xC4904AC4
	UINT32                                                 reserved4603;	//0xC4904AC8
	UINT32                                                 reserved4604;	//0xC4904ACC
	UINT32                                                 reserved4605;	//0xC4904AD0
	UINT32                                                 reserved4606;	//0xC4904AD4
	UINT32                                                 reserved4607;	//0xC4904AD8
	UINT32                                                 reserved4608;	//0xC4904ADC
	UINT32                                                 reserved4609;	//0xC4904AE0
	UINT32                                                 reserved4610;	//0xC4904AE4
	UINT32                                                 reserved4611;	//0xC4904AE8
	UINT32                                                 reserved4612;	//0xC4904AEC
	UINT32                                                 reserved4613;	//0xC4904AF0
	UINT32                                                 reserved4614;	//0xC4904AF4
	UINT32                                                 reserved4615;	//0xC4904AF8
	UINT32                                                 reserved4616;	//0xC4904AFC
	UINT32                                                 reserved4617;	//0xC4904B00
	UINT32                                                 reserved4618;	//0xC4904B04
	UINT32                                                 reserved4619;	//0xC4904B08
	UINT32                                                 reserved4620;	//0xC4904B0C
	UINT32                                                 reserved4621;	//0xC4904B10
	UINT32                                                 reserved4622;	//0xC4904B14
	UINT32                                                 reserved4623;	//0xC4904B18
	UINT32                                                 reserved4624;	//0xC4904B1C
	UINT32                                                 reserved4625;	//0xC4904B20
	UINT32                                                 reserved4626;	//0xC4904B24
	UINT32                                                 reserved4627;	//0xC4904B28
	UINT32                                                 reserved4628;	//0xC4904B2C
	UINT32                                                 reserved4629;	//0xC4904B30
	UINT32                                                 reserved4630;	//0xC4904B34
	UINT32                                                 reserved4631;	//0xC4904B38
	UINT32                                                 reserved4632;	//0xC4904B3C
	UINT32                                                 reserved4633;	//0xC4904B40
	UINT32                                                 reserved4634;	//0xC4904B44
	UINT32                                                 reserved4635;	//0xC4904B48
	UINT32                                                 reserved4636;	//0xC4904B4C
	UINT32                                                 reserved4637;	//0xC4904B50
	UINT32                                                 reserved4638;	//0xC4904B54
	UINT32                                                 reserved4639;	//0xC4904B58
	UINT32                                                 reserved4640;	//0xC4904B5C
	UINT32                                                 reserved4641;	//0xC4904B60
	UINT32                                                 reserved4642;	//0xC4904B64
	UINT32                                                 reserved4643;	//0xC4904B68
	UINT32                                                 reserved4644;	//0xC4904B6C
	UINT32                                                 reserved4645;	//0xC4904B70
	UINT32                                                 reserved4646;	//0xC4904B74
	UINT32                                                 reserved4647;	//0xC4904B78
	UINT32                                                 reserved4648;	//0xC4904B7C
	UINT32                                                 reserved4649;	//0xC4904B80
	UINT32                                                 reserved4650;	//0xC4904B84
	UINT32                                                 reserved4651;	//0xC4904B88
	UINT32                                                 reserved4652;	//0xC4904B8C
	UINT32                                                 reserved4653;	//0xC4904B90
	UINT32                                                 reserved4654;	//0xC4904B94
	UINT32                                                 reserved4655;	//0xC4904B98
	UINT32                                                 reserved4656;	//0xC4904B9C
	UINT32                                                 reserved4657;	//0xC4904BA0
	UINT32                                                 reserved4658;	//0xC4904BA4
	UINT32                                                 reserved4659;	//0xC4904BA8
	UINT32                                                 reserved4660;	//0xC4904BAC
	UINT32                                                 reserved4661;	//0xC4904BB0
	UINT32                                                 reserved4662;	//0xC4904BB4
	UINT32                                                 reserved4663;	//0xC4904BB8
	UINT32                                                 reserved4664;	//0xC4904BBC
	UINT32                                                 reserved4665;	//0xC4904BC0
	UINT32                                                 reserved4666;	//0xC4904BC4
	UINT32                                                 reserved4667;	//0xC4904BC8
	UINT32                                                 reserved4668;	//0xC4904BCC
	UINT32                                                 reserved4669;	//0xC4904BD0
	UINT32                                                 reserved4670;	//0xC4904BD4
	UINT32                                                 reserved4671;	//0xC4904BD8
	UINT32                                                 reserved4672;	//0xC4904BDC
	UINT32                                                 reserved4673;	//0xC4904BE0
	UINT32                                                 reserved4674;	//0xC4904BE4
	UINT32                                                 reserved4675;	//0xC4904BE8
	UINT32                                                 reserved4676;	//0xC4904BEC
	UINT32                                                 reserved4677;	//0xC4904BF0
	UINT32                                                 reserved4678;	//0xC4904BF4
	UINT32                                                 reserved4679;	//0xC4904BF8
	UINT32                                                 reserved4680;	//0xC4904BFC
	UINT32                                                 reserved4681;	//0xC4904C00
	UINT32                                                 reserved4682;	//0xC4904C04
	UINT32                                                 reserved4683;	//0xC4904C08
	UINT32                                                 reserved4684;	//0xC4904C0C
	UINT32                                                 reserved4685;	//0xC4904C10
	UINT32                                                 reserved4686;	//0xC4904C14
	UINT32                                                 reserved4687;	//0xC4904C18
	UINT32                                                 reserved4688;	//0xC4904C1C
	UINT32                                                 reserved4689;	//0xC4904C20
	UINT32                                                 reserved4690;	//0xC4904C24
	UINT32                                                 reserved4691;	//0xC4904C28
	UINT32                                                 reserved4692;	//0xC4904C2C
	UINT32                                                 reserved4693;	//0xC4904C30
	UINT32                                                 reserved4694;	//0xC4904C34
	UINT32                                                 reserved4695;	//0xC4904C38
	UINT32                                                 reserved4696;	//0xC4904C3C
	UINT32                                                 reserved4697;	//0xC4904C40
	UINT32                                                 reserved4698;	//0xC4904C44
	UINT32                                                 reserved4699;	//0xC4904C48
	UINT32                                                 reserved4700;	//0xC4904C4C
	UINT32                                                 reserved4701;	//0xC4904C50
	UINT32                                                 reserved4702;	//0xC4904C54
	UINT32                                                 reserved4703;	//0xC4904C58
	UINT32                                                 reserved4704;	//0xC4904C5C
	UINT32                                                 reserved4705;	//0xC4904C60
	UINT32                                                 reserved4706;	//0xC4904C64
	UINT32                                                 reserved4707;	//0xC4904C68
	UINT32                                                 reserved4708;	//0xC4904C6C
	UINT32                                                 reserved4709;	//0xC4904C70
	UINT32                                                 reserved4710;	//0xC4904C74
	UINT32                                                 reserved4711;	//0xC4904C78
	UINT32                                                 reserved4712;	//0xC4904C7C
	UINT32                                                 reserved4713;	//0xC4904C80
	UINT32                                                 reserved4714;	//0xC4904C84
	UINT32                                                 reserved4715;	//0xC4904C88
	UINT32                                                 reserved4716;	//0xC4904C8C
	UINT32                                                 reserved4717;	//0xC4904C90
	UINT32                                                 reserved4718;	//0xC4904C94
	UINT32                                                 reserved4719;	//0xC4904C98
	UINT32                                                 reserved4720;	//0xC4904C9C
	UINT32                                                 reserved4721;	//0xC4904CA0
	UINT32                                                 reserved4722;	//0xC4904CA4
	UINT32                                                 reserved4723;	//0xC4904CA8
	UINT32                                                 reserved4724;	//0xC4904CAC
	UINT32                                                 reserved4725;	//0xC4904CB0
	UINT32                                                 reserved4726;	//0xC4904CB4
	UINT32                                                 reserved4727;	//0xC4904CB8
	UINT32                                                 reserved4728;	//0xC4904CBC
	UINT32                                                 reserved4729;	//0xC4904CC0
	UINT32                                                 reserved4730;	//0xC4904CC4
	UINT32                                                 reserved4731;	//0xC4904CC8
	UINT32                                                 reserved4732;	//0xC4904CCC
	UINT32                                                 reserved4733;	//0xC4904CD0
	UINT32                                                 reserved4734;	//0xC4904CD4
	UINT32                                                 reserved4735;	//0xC4904CD8
	UINT32                                                 reserved4736;	//0xC4904CDC
	UINT32                                                 reserved4737;	//0xC4904CE0
	UINT32                                                 reserved4738;	//0xC4904CE4
	UINT32                                                 reserved4739;	//0xC4904CE8
	UINT32                                                 reserved4740;	//0xC4904CEC
	UINT32                                                 reserved4741;	//0xC4904CF0
	UINT32                                                 reserved4742;	//0xC4904CF4
	UINT32                                                 reserved4743;	//0xC4904CF8
	UINT32                                                 reserved4744;	//0xC4904CFC
	UINT32                                                 reserved4745;	//0xC4904D00
	UINT32                                                 reserved4746;	//0xC4904D04
	UINT32                                                 reserved4747;	//0xC4904D08
	UINT32                                                 reserved4748;	//0xC4904D0C
	UINT32                                                 reserved4749;	//0xC4904D10
	UINT32                                                 reserved4750;	//0xC4904D14
	UINT32                                                 reserved4751;	//0xC4904D18
	UINT32                                                 reserved4752;	//0xC4904D1C
	UINT32                                                 reserved4753;	//0xC4904D20
	UINT32                                                 reserved4754;	//0xC4904D24
	UINT32                                                 reserved4755;	//0xC4904D28
	UINT32                                                 reserved4756;	//0xC4904D2C
	UINT32                                                 reserved4757;	//0xC4904D30
	UINT32                                                 reserved4758;	//0xC4904D34
	UINT32                                                 reserved4759;	//0xC4904D38
	UINT32                                                 reserved4760;	//0xC4904D3C
	UINT32                                                 reserved4761;	//0xC4904D40
	UINT32                                                 reserved4762;	//0xC4904D44
	UINT32                                                 reserved4763;	//0xC4904D48
	UINT32                                                 reserved4764;	//0xC4904D4C
	UINT32                                                 reserved4765;	//0xC4904D50
	UINT32                                                 reserved4766;	//0xC4904D54
	UINT32                                                 reserved4767;	//0xC4904D58
	UINT32                                                 reserved4768;	//0xC4904D5C
	UINT32                                                 reserved4769;	//0xC4904D60
	UINT32                                                 reserved4770;	//0xC4904D64
	UINT32                                                 reserved4771;	//0xC4904D68
	UINT32                                                 reserved4772;	//0xC4904D6C
	UINT32                                                 reserved4773;	//0xC4904D70
	UINT32                                                 reserved4774;	//0xC4904D74
	UINT32                                                 reserved4775;	//0xC4904D78
	UINT32                                                 reserved4776;	//0xC4904D7C
	UINT32                                                 reserved4777;	//0xC4904D80
	UINT32                                                 reserved4778;	//0xC4904D84
	UINT32                                                 reserved4779;	//0xC4904D88
	UINT32                                                 reserved4780;	//0xC4904D8C
	UINT32                                                 reserved4781;	//0xC4904D90
	UINT32                                                 reserved4782;	//0xC4904D94
	UINT32                                                 reserved4783;	//0xC4904D98
	UINT32                                                 reserved4784;	//0xC4904D9C
	UINT32                                                 reserved4785;	//0xC4904DA0
	UINT32                                                 reserved4786;	//0xC4904DA4
	UINT32                                                 reserved4787;	//0xC4904DA8
	UINT32                                                 reserved4788;	//0xC4904DAC
	UINT32                                                 reserved4789;	//0xC4904DB0
	UINT32                                                 reserved4790;	//0xC4904DB4
	UINT32                                                 reserved4791;	//0xC4904DB8
	UINT32                                                 reserved4792;	//0xC4904DBC
	UINT32                                                 reserved4793;	//0xC4904DC0
	UINT32                                                 reserved4794;	//0xC4904DC4
	UINT32                                                 reserved4795;	//0xC4904DC8
	UINT32                                                 reserved4796;	//0xC4904DCC
	UINT32                                                 reserved4797;	//0xC4904DD0
	UINT32                                                 reserved4798;	//0xC4904DD4
	UINT32                                                 reserved4799;	//0xC4904DD8
	UINT32                                                 reserved4800;	//0xC4904DDC
	UINT32                                                 reserved4801;	//0xC4904DE0
	UINT32                                                 reserved4802;	//0xC4904DE4
	UINT32                                                 reserved4803;	//0xC4904DE8
	UINT32                                                 reserved4804;	//0xC4904DEC
	UINT32                                                 reserved4805;	//0xC4904DF0
	UINT32                                                 reserved4806;	//0xC4904DF4
	UINT32                                                 reserved4807;	//0xC4904DF8
	UINT32                                                 reserved4808;	//0xC4904DFC
	UINT32                                                 reserved4809;	//0xC4904E00
	UINT32                                                 reserved4810;	//0xC4904E04
	UINT32                                                 reserved4811;	//0xC4904E08
	UINT32                                                 reserved4812;	//0xC4904E0C
	UINT32                                                 reserved4813;	//0xC4904E10
	UINT32                                                 reserved4814;	//0xC4904E14
	UINT32                                                 reserved4815;	//0xC4904E18
	UINT32                                                 reserved4816;	//0xC4904E1C
	UINT32                                                 reserved4817;	//0xC4904E20
	UINT32                                                 reserved4818;	//0xC4904E24
	UINT32                                                 reserved4819;	//0xC4904E28
	UINT32                                                 reserved4820;	//0xC4904E2C
	UINT32                                                 reserved4821;	//0xC4904E30
	UINT32                                                 reserved4822;	//0xC4904E34
	UINT32                                                 reserved4823;	//0xC4904E38
	UINT32                                                 reserved4824;	//0xC4904E3C
	UINT32                                                 reserved4825;	//0xC4904E40
	UINT32                                                 reserved4826;	//0xC4904E44
	UINT32                                                 reserved4827;	//0xC4904E48
	UINT32                                                 reserved4828;	//0xC4904E4C
	UINT32                                                 reserved4829;	//0xC4904E50
	UINT32                                                 reserved4830;	//0xC4904E54
	UINT32                                                 reserved4831;	//0xC4904E58
	UINT32                                                 reserved4832;	//0xC4904E5C
	UINT32                                                 reserved4833;	//0xC4904E60
	UINT32                                                 reserved4834;	//0xC4904E64
	UINT32                                                 reserved4835;	//0xC4904E68
	UINT32                                                 reserved4836;	//0xC4904E6C
	UINT32                                                 reserved4837;	//0xC4904E70
	UINT32                                                 reserved4838;	//0xC4904E74
	UINT32                                                 reserved4839;	//0xC4904E78
	UINT32                                                 reserved4840;	//0xC4904E7C
	UINT32                                                 reserved4841;	//0xC4904E80
	UINT32                                                 reserved4842;	//0xC4904E84
	UINT32                                                 reserved4843;	//0xC4904E88
	UINT32                                                 reserved4844;	//0xC4904E8C
	UINT32                                                 reserved4845;	//0xC4904E90
	UINT32                                                 reserved4846;	//0xC4904E94
	UINT32                                                 reserved4847;	//0xC4904E98
	UINT32                                                 reserved4848;	//0xC4904E9C
	UINT32                                                 reserved4849;	//0xC4904EA0
	UINT32                                                 reserved4850;	//0xC4904EA4
	UINT32                                                 reserved4851;	//0xC4904EA8
	UINT32                                                 reserved4852;	//0xC4904EAC
	UINT32                                                 reserved4853;	//0xC4904EB0
	UINT32                                                 reserved4854;	//0xC4904EB4
	UINT32                                                 reserved4855;	//0xC4904EB8
	UINT32                                                 reserved4856;	//0xC4904EBC
	UINT32                                                 reserved4857;	//0xC4904EC0
	UINT32                                                 reserved4858;	//0xC4904EC4
	UINT32                                                 reserved4859;	//0xC4904EC8
	UINT32                                                 reserved4860;	//0xC4904ECC
	UINT32                                                 reserved4861;	//0xC4904ED0
	UINT32                                                 reserved4862;	//0xC4904ED4
	UINT32                                                 reserved4863;	//0xC4904ED8
	UINT32                                                 reserved4864;	//0xC4904EDC
	UINT32                                                 reserved4865;	//0xC4904EE0
	UINT32                                                 reserved4866;	//0xC4904EE4
	UINT32                                                 reserved4867;	//0xC4904EE8
	UINT32                                                 reserved4868;	//0xC4904EEC
	UINT32                                                 reserved4869;	//0xC4904EF0
	UINT32                                                 reserved4870;	//0xC4904EF4
	UINT32                                                 reserved4871;	//0xC4904EF8
	UINT32                                                 reserved4872;	//0xC4904EFC
	UINT32                                                 reserved4873;	//0xC4904F00
	UINT32                                                 reserved4874;	//0xC4904F04
	UINT32                                                 reserved4875;	//0xC4904F08
	UINT32                                                 reserved4876;	//0xC4904F0C
	UINT32                                                 reserved4877;	//0xC4904F10
	UINT32                                                 reserved4878;	//0xC4904F14
	UINT32                                                 reserved4879;	//0xC4904F18
	UINT32                                                 reserved4880;	//0xC4904F1C
	UINT32                                                 reserved4881;	//0xC4904F20
	UINT32                                                 reserved4882;	//0xC4904F24
	UINT32                                                 reserved4883;	//0xC4904F28
	UINT32                                                 reserved4884;	//0xC4904F2C
	UINT32                                                 reserved4885;	//0xC4904F30
	UINT32                                                 reserved4886;	//0xC4904F34
	UINT32                                                 reserved4887;	//0xC4904F38
	UINT32                                                 reserved4888;	//0xC4904F3C
	UINT32                                                 reserved4889;	//0xC4904F40
	UINT32                                                 reserved4890;	//0xC4904F44
	UINT32                                                 reserved4891;	//0xC4904F48
	UINT32                                                 reserved4892;	//0xC4904F4C
	UINT32                                                 reserved4893;	//0xC4904F50
	UINT32                                                 reserved4894;	//0xC4904F54
	UINT32                                                 reserved4895;	//0xC4904F58
	UINT32                                                 reserved4896;	//0xC4904F5C
	UINT32                                                 reserved4897;	//0xC4904F60
	UINT32                                                 reserved4898;	//0xC4904F64
	UINT32                                                 reserved4899;	//0xC4904F68
	UINT32                                                 reserved4900;	//0xC4904F6C
	UINT32                                                 reserved4901;	//0xC4904F70
	UINT32                                                 reserved4902;	//0xC4904F74
	UINT32                                                 reserved4903;	//0xC4904F78
	UINT32                                                 reserved4904;	//0xC4904F7C
	UINT32                                                 reserved4905;	//0xC4904F80
	UINT32                                                 reserved4906;	//0xC4904F84
	UINT32                                                 reserved4907;	//0xC4904F88
	UINT32                                                 reserved4908;	//0xC4904F8C
	UINT32                                                 reserved4909;	//0xC4904F90
	UINT32                                                 reserved4910;	//0xC4904F94
	UINT32                                                 reserved4911;	//0xC4904F98
	UINT32                                                 reserved4912;	//0xC4904F9C
	UINT32                                                 reserved4913;	//0xC4904FA0
	UINT32                                                 reserved4914;	//0xC4904FA4
	UINT32                                                 reserved4915;	//0xC4904FA8
	UINT32                                                 reserved4916;	//0xC4904FAC
	UINT32                                                 reserved4917;	//0xC4904FB0
	UINT32                                                 reserved4918;	//0xC4904FB4
	UINT32                                                 reserved4919;	//0xC4904FB8
	UINT32                                                 reserved4920;	//0xC4904FBC
	UINT32                                                 reserved4921;	//0xC4904FC0
	UINT32                                                 reserved4922;	//0xC4904FC4
	UINT32                                                 reserved4923;	//0xC4904FC8
	UINT32                                                 reserved4924;	//0xC4904FCC
	UINT32                                                 reserved4925;	//0xC4904FD0
	UINT32                                                 reserved4926;	//0xC4904FD4
	UINT32                                                 reserved4927;	//0xC4904FD8
	UINT32                                                 reserved4928;	//0xC4904FDC
	UINT32                                                 reserved4929;	//0xC4904FE0
	UINT32                                                 reserved4930;	//0xC4904FE4
	UINT32                                                 reserved4931;	//0xC4904FE8
	UINT32                                                 reserved4932;	//0xC4904FEC
	UINT32                                                 reserved4933;	//0xC4904FF0
	UINT32                                                 reserved4934;	//0xC4904FF4
	UINT32                                                 reserved4935;	//0xC4904FF8
	UINT32                                                 reserved4936;	//0xC4904FFC
	REG_DDRC_M1_DEBUG_COMMON_T                             debug_common;	//0xC4905000
	REG_DDRC_M1_DEBUG_PERIOD_T                             debug_period;	//0xC4905004
	UINT32                                                 reserved4937;	//0xC4905008
	UINT32                                                 reserved4938;	//0xC490500C
	REG_DDRC_M1_IRQ_MASK_T                                     irq_mask;	//0xC4905010
	REG_DDRC_M1_IRQ_STATUS_T                                 irq_status;	//0xC4905014
	UINT32                                                 reserved4939;	//0xC4905018
	UINT32                                                 reserved4940;	//0xC490501C
	UINT32                                                 reserved4941;	//0xC4905020
	UINT32                                                 reserved4942;	//0xC4905024
	UINT32                                                 reserved4943;	//0xC4905028
	UINT32                                                 reserved4944;	//0xC490502C
	UINT32                                                 reserved4945;	//0xC4905030
	UINT32                                                 reserved4946;	//0xC4905034
	UINT32                                                 reserved4947;	//0xC4905038
	UINT32                                                 reserved4948;	//0xC490503C
	UINT32                                                 reserved4949;	//0xC4905040
	UINT32                                                 reserved4950;	//0xC4905044
	UINT32                                                 reserved4951;	//0xC4905048
	UINT32                                                 reserved4952;	//0xC490504C
	UINT32                                                 reserved4953;	//0xC4905050
	UINT32                                                 reserved4954;	//0xC4905054
	UINT32                                                 reserved4955;	//0xC4905058
	UINT32                                                 reserved4956;	//0xC490505C
	UINT32                                                 reserved4957;	//0xC4905060
	UINT32                                                 reserved4958;	//0xC4905064
	UINT32                                                 reserved4959;	//0xC4905068
	UINT32                                                 reserved4960;	//0xC490506C
	UINT32                                                 reserved4961;	//0xC4905070
	UINT32                                                 reserved4962;	//0xC4905074
	UINT32                                                 reserved4963;	//0xC4905078
	UINT32                                                 reserved4964;	//0xC490507C
	UINT32                                                 reserved4965;	//0xC4905080
	UINT32                                                 reserved4966;	//0xC4905084
	UINT32                                                 reserved4967;	//0xC4905088
	UINT32                                                 reserved4968;	//0xC490508C
	UINT32                                                 reserved4969;	//0xC4905090
	UINT32                                                 reserved4970;	//0xC4905094
	UINT32                                                 reserved4971;	//0xC4905098
	UINT32                                                 reserved4972;	//0xC490509C
	UINT32                                                 reserved4973;	//0xC49050A0
	UINT32                                                 reserved4974;	//0xC49050A4
	UINT32                                                 reserved4975;	//0xC49050A8
	UINT32                                                 reserved4976;	//0xC49050AC
	UINT32                                                 reserved4977;	//0xC49050B0
	UINT32                                                 reserved4978;	//0xC49050B4
	UINT32                                                 reserved4979;	//0xC49050B8
	UINT32                                                 reserved4980;	//0xC49050BC
	UINT32                                                 reserved4981;	//0xC49050C0
	UINT32                                                 reserved4982;	//0xC49050C4
	UINT32                                                 reserved4983;	//0xC49050C8
	UINT32                                                 reserved4984;	//0xC49050CC
	UINT32                                                 reserved4985;	//0xC49050D0
	UINT32                                                 reserved4986;	//0xC49050D4
	UINT32                                                 reserved4987;	//0xC49050D8
	UINT32                                                 reserved4988;	//0xC49050DC
	UINT32                                                 reserved4989;	//0xC49050E0
	UINT32                                                 reserved4990;	//0xC49050E4
	UINT32                                                 reserved4991;	//0xC49050E8
	UINT32                                                 reserved4992;	//0xC49050EC
	UINT32                                                 reserved4993;	//0xC49050F0
	UINT32                                                 reserved4994;	//0xC49050F4
	UINT32                                                 reserved4995;	//0xC49050F8
	UINT32                                                 reserved4996;	//0xC49050FC
	REG_DDRC_M1_DEBUG_BUS_IF_T                             debug_bus_if;	//0xC4905100
	UINT32                                                 reserved4997;	//0xC4905104
	UINT32                                                 reserved4998;	//0xC4905108
	UINT32                                                 reserved4999;	//0xC490510C
	UINT32                                                 reserved5000;	//0xC4905110
	UINT32                                                 reserved5001;	//0xC4905114
	UINT32                                                 reserved5002;	//0xC4905118
	UINT32                                                 reserved5003;	//0xC490511C
	UINT32                                                 reserved5004;	//0xC4905120
	UINT32                                                 reserved5005;	//0xC4905124
	UINT32                                                 reserved5006;	//0xC4905128
	UINT32                                                 reserved5007;	//0xC490512C
	UINT32                                                 reserved5008;	//0xC4905130
	UINT32                                                 reserved5009;	//0xC4905134
	UINT32                                                 reserved5010;	//0xC4905138
	UINT32                                                 reserved5011;	//0xC490513C
	UINT32                                                 reserved5012;	//0xC4905140
	UINT32                                                 reserved5013;	//0xC4905144
	UINT32                                                 reserved5014;	//0xC4905148
	UINT32                                                 reserved5015;	//0xC490514C
	UINT32                                                 reserved5016;	//0xC4905150
	UINT32                                                 reserved5017;	//0xC4905154
	UINT32                                                 reserved5018;	//0xC4905158
	UINT32                                                 reserved5019;	//0xC490515C
	UINT32                                                 reserved5020;	//0xC4905160
	UINT32                                                 reserved5021;	//0xC4905164
	UINT32                                                 reserved5022;	//0xC4905168
	UINT32                                                 reserved5023;	//0xC490516C
	UINT32                                                 reserved5024;	//0xC4905170
	UINT32                                                 reserved5025;	//0xC4905174
	UINT32                                                 reserved5026;	//0xC4905178
	UINT32                                                 reserved5027;	//0xC490517C
	UINT32                                                 reserved5028;	//0xC4905180
	UINT32                                                 reserved5029;	//0xC4905184
	UINT32                                                 reserved5030;	//0xC4905188
	UINT32                                                 reserved5031;	//0xC490518C
	UINT32                                                 reserved5032;	//0xC4905190
	UINT32                                                 reserved5033;	//0xC4905194
	UINT32                                                 reserved5034;	//0xC4905198
	UINT32                                                 reserved5035;	//0xC490519C
	UINT32                                                 reserved5036;	//0xC49051A0
	UINT32                                                 reserved5037;	//0xC49051A4
	UINT32                                                 reserved5038;	//0xC49051A8
	UINT32                                                 reserved5039;	//0xC49051AC
	UINT32                                                 reserved5040;	//0xC49051B0
	UINT32                                                 reserved5041;	//0xC49051B4
	UINT32                                                 reserved5042;	//0xC49051B8
	UINT32                                                 reserved5043;	//0xC49051BC
	UINT32                                                 reserved5044;	//0xC49051C0
	UINT32                                                 reserved5045;	//0xC49051C4
	UINT32                                                 reserved5046;	//0xC49051C8
	UINT32                                                 reserved5047;	//0xC49051CC
	UINT32                                                 reserved5048;	//0xC49051D0
	UINT32                                                 reserved5049;	//0xC49051D4
	UINT32                                                 reserved5050;	//0xC49051D8
	UINT32                                                 reserved5051;	//0xC49051DC
	UINT32                                                 reserved5052;	//0xC49051E0
	UINT32                                                 reserved5053;	//0xC49051E4
	UINT32                                                 reserved5054;	//0xC49051E8
	UINT32                                                 reserved5055;	//0xC49051EC
	UINT32                                                 reserved5056;	//0xC49051F0
	UINT32                                                 reserved5057;	//0xC49051F4
	UINT32                                                 reserved5058;	//0xC49051F8
	UINT32                                                 reserved5059;	//0xC49051FC
	REG_DDRC_M1_DEBUG_PORT_IF_0_T                       debug_port_if_0;	//0xC4905200
	REG_DDRC_M1_DEBUG_PORT_IF_1_T                       debug_port_if_1;	//0xC4905204
	REG_DDRC_M1_DEBUG_PORT_IF_2_T                       debug_port_if_2;	//0xC4905208
	REG_DDRC_M1_DEBUG_PORT_IF_3_T                       debug_port_if_3;	//0xC490520C
	REG_DDRC_M1_DEBUG_PORT_IF_4_T                       debug_port_if_4;	//0xC4905210
	REG_DDRC_M1_DEBUG_PORT_IF_5_T                       debug_port_if_5;	//0xC4905214
	REG_DDRC_M1_DEBUG_PORT_IF_6_T                       debug_port_if_6;	//0xC4905218
	REG_DDRC_M1_DEBUG_PORT_IF_7_T                       debug_port_if_7;	//0xC490521C
	UINT32                                                 reserved5060;	//0xC4905220
	UINT32                                                 reserved5061;	//0xC4905224
	UINT32                                                 reserved5062;	//0xC4905228
	UINT32                                                 reserved5063;	//0xC490522C
	UINT32                                                 reserved5064;	//0xC4905230
	UINT32                                                 reserved5065;	//0xC4905234
	UINT32                                                 reserved5066;	//0xC4905238
	UINT32                                                 reserved5067;	//0xC490523C
	UINT32                                                 reserved5068;	//0xC4905240
	UINT32                                                 reserved5069;	//0xC4905244
	UINT32                                                 reserved5070;	//0xC4905248
	UINT32                                                 reserved5071;	//0xC490524C
	UINT32                                                 reserved5072;	//0xC4905250
	UINT32                                                 reserved5073;	//0xC4905254
	UINT32                                                 reserved5074;	//0xC4905258
	UINT32                                                 reserved5075;	//0xC490525C
	UINT32                                                 reserved5076;	//0xC4905260
	UINT32                                                 reserved5077;	//0xC4905264
	UINT32                                                 reserved5078;	//0xC4905268
	UINT32                                                 reserved5079;	//0xC490526C
	UINT32                                                 reserved5080;	//0xC4905270
	UINT32                                                 reserved5081;	//0xC4905274
	UINT32                                                 reserved5082;	//0xC4905278
	UINT32                                                 reserved5083;	//0xC490527C
	UINT32                                                 reserved5084;	//0xC4905280
	UINT32                                                 reserved5085;	//0xC4905284
	UINT32                                                 reserved5086;	//0xC4905288
	UINT32                                                 reserved5087;	//0xC490528C
	UINT32                                                 reserved5088;	//0xC4905290
	UINT32                                                 reserved5089;	//0xC4905294
	UINT32                                                 reserved5090;	//0xC4905298
	UINT32                                                 reserved5091;	//0xC490529C
	UINT32                                                 reserved5092;	//0xC49052A0
	UINT32                                                 reserved5093;	//0xC49052A4
	UINT32                                                 reserved5094;	//0xC49052A8
	UINT32                                                 reserved5095;	//0xC49052AC
	UINT32                                                 reserved5096;	//0xC49052B0
	UINT32                                                 reserved5097;	//0xC49052B4
	UINT32                                                 reserved5098;	//0xC49052B8
	UINT32                                                 reserved5099;	//0xC49052BC
	UINT32                                                 reserved5100;	//0xC49052C0
	UINT32                                                 reserved5101;	//0xC49052C4
	UINT32                                                 reserved5102;	//0xC49052C8
	UINT32                                                 reserved5103;	//0xC49052CC
	UINT32                                                 reserved5104;	//0xC49052D0
	UINT32                                                 reserved5105;	//0xC49052D4
	UINT32                                                 reserved5106;	//0xC49052D8
	UINT32                                                 reserved5107;	//0xC49052DC
	UINT32                                                 reserved5108;	//0xC49052E0
	UINT32                                                 reserved5109;	//0xC49052E4
	UINT32                                                 reserved5110;	//0xC49052E8
	UINT32                                                 reserved5111;	//0xC49052EC
	UINT32                                                 reserved5112;	//0xC49052F0
	UINT32                                                 reserved5113;	//0xC49052F4
	UINT32                                                 reserved5114;	//0xC49052F8
	UINT32                                                 reserved5115;	//0xC49052FC
	REG_DDRC_M1_DEBUG_UQ_1_T                                 debug_uq_1;	//0xC4905300
	REG_DDRC_M1_DEBUG_UQ_2_T                                 debug_uq_2;	//0xC4905304
	UINT32                                                 reserved5116;	//0xC4905308
	UINT32                                                 reserved5117;	//0xC490530C
	UINT32                                                 reserved5118;	//0xC4905310
	UINT32                                                 reserved5119;	//0xC4905314
	UINT32                                                 reserved5120;	//0xC4905318
	UINT32                                                 reserved5121;	//0xC490531C
	UINT32                                                 reserved5122;	//0xC4905320
	UINT32                                                 reserved5123;	//0xC4905324
	UINT32                                                 reserved5124;	//0xC4905328
	UINT32                                                 reserved5125;	//0xC490532C
	UINT32                                                 reserved5126;	//0xC4905330
	UINT32                                                 reserved5127;	//0xC4905334
	UINT32                                                 reserved5128;	//0xC4905338
	UINT32                                                 reserved5129;	//0xC490533C
	UINT32                                                 reserved5130;	//0xC4905340
	UINT32                                                 reserved5131;	//0xC4905344
	UINT32                                                 reserved5132;	//0xC4905348
	UINT32                                                 reserved5133;	//0xC490534C
	UINT32                                                 reserved5134;	//0xC4905350
	UINT32                                                 reserved5135;	//0xC4905354
	UINT32                                                 reserved5136;	//0xC4905358
	UINT32                                                 reserved5137;	//0xC490535C
	UINT32                                                 reserved5138;	//0xC4905360
	UINT32                                                 reserved5139;	//0xC4905364
	UINT32                                                 reserved5140;	//0xC4905368
	UINT32                                                 reserved5141;	//0xC490536C
	UINT32                                                 reserved5142;	//0xC4905370
	UINT32                                                 reserved5143;	//0xC4905374
	UINT32                                                 reserved5144;	//0xC4905378
	UINT32                                                 reserved5145;	//0xC490537C
	UINT32                                                 reserved5146;	//0xC4905380
	UINT32                                                 reserved5147;	//0xC4905384
	UINT32                                                 reserved5148;	//0xC4905388
	UINT32                                                 reserved5149;	//0xC490538C
	UINT32                                                 reserved5150;	//0xC4905390
	UINT32                                                 reserved5151;	//0xC4905394
	UINT32                                                 reserved5152;	//0xC4905398
	UINT32                                                 reserved5153;	//0xC490539C
	UINT32                                                 reserved5154;	//0xC49053A0
	UINT32                                                 reserved5155;	//0xC49053A4
	UINT32                                                 reserved5156;	//0xC49053A8
	UINT32                                                 reserved5157;	//0xC49053AC
	UINT32                                                 reserved5158;	//0xC49053B0
	UINT32                                                 reserved5159;	//0xC49053B4
	UINT32                                                 reserved5160;	//0xC49053B8
	UINT32                                                 reserved5161;	//0xC49053BC
	UINT32                                                 reserved5162;	//0xC49053C0
	UINT32                                                 reserved5163;	//0xC49053C4
	UINT32                                                 reserved5164;	//0xC49053C8
	UINT32                                                 reserved5165;	//0xC49053CC
	UINT32                                                 reserved5166;	//0xC49053D0
	UINT32                                                 reserved5167;	//0xC49053D4
	UINT32                                                 reserved5168;	//0xC49053D8
	UINT32                                                 reserved5169;	//0xC49053DC
	UINT32                                                 reserved5170;	//0xC49053E0
	UINT32                                                 reserved5171;	//0xC49053E4
	UINT32                                                 reserved5172;	//0xC49053E8
	UINT32                                                 reserved5173;	//0xC49053EC
	UINT32                                                 reserved5174;	//0xC49053F0
	UINT32                                                 reserved5175;	//0xC49053F4
	UINT32                                                 reserved5176;	//0xC49053F8
	UINT32                                                 reserved5177;	//0xC49053FC
	REG_DDRC_M1_DEBUG_SCH0_T                                 debug_sch0;	//0xC4905400
	REG_DDRC_M1_DEBUG_SCH1_T                                 debug_sch1;	//0xC4905404
	UINT32                                                 reserved5178;	//0xC4905408
	UINT32                                                 reserved5179;	//0xC490540C
	UINT32                                                 reserved5180;	//0xC4905410
	UINT32                                                 reserved5181;	//0xC4905414
	UINT32                                                 reserved5182;	//0xC4905418
	UINT32                                                 reserved5183;	//0xC490541C
	UINT32                                                 reserved5184;	//0xC4905420
	UINT32                                                 reserved5185;	//0xC4905424
	UINT32                                                 reserved5186;	//0xC4905428
	UINT32                                                 reserved5187;	//0xC490542C
	UINT32                                                 reserved5188;	//0xC4905430
	UINT32                                                 reserved5189;	//0xC4905434
	UINT32                                                 reserved5190;	//0xC4905438
	UINT32                                                 reserved5191;	//0xC490543C
	UINT32                                                 reserved5192;	//0xC4905440
	UINT32                                                 reserved5193;	//0xC4905444
	UINT32                                                 reserved5194;	//0xC4905448
	UINT32                                                 reserved5195;	//0xC490544C
	UINT32                                                 reserved5196;	//0xC4905450
	UINT32                                                 reserved5197;	//0xC4905454
	UINT32                                                 reserved5198;	//0xC4905458
	UINT32                                                 reserved5199;	//0xC490545C
	UINT32                                                 reserved5200;	//0xC4905460
	UINT32                                                 reserved5201;	//0xC4905464
	UINT32                                                 reserved5202;	//0xC4905468
	UINT32                                                 reserved5203;	//0xC490546C
	UINT32                                                 reserved5204;	//0xC4905470
	UINT32                                                 reserved5205;	//0xC4905474
	UINT32                                                 reserved5206;	//0xC4905478
	UINT32                                                 reserved5207;	//0xC490547C
	UINT32                                                 reserved5208;	//0xC4905480
	UINT32                                                 reserved5209;	//0xC4905484
	UINT32                                                 reserved5210;	//0xC4905488
	UINT32                                                 reserved5211;	//0xC490548C
	UINT32                                                 reserved5212;	//0xC4905490
	UINT32                                                 reserved5213;	//0xC4905494
	UINT32                                                 reserved5214;	//0xC4905498
	UINT32                                                 reserved5215;	//0xC490549C
	UINT32                                                 reserved5216;	//0xC49054A0
	UINT32                                                 reserved5217;	//0xC49054A4
	UINT32                                                 reserved5218;	//0xC49054A8
	UINT32                                                 reserved5219;	//0xC49054AC
	UINT32                                                 reserved5220;	//0xC49054B0
	UINT32                                                 reserved5221;	//0xC49054B4
	UINT32                                                 reserved5222;	//0xC49054B8
	UINT32                                                 reserved5223;	//0xC49054BC
	UINT32                                                 reserved5224;	//0xC49054C0
	UINT32                                                 reserved5225;	//0xC49054C4
	UINT32                                                 reserved5226;	//0xC49054C8
	UINT32                                                 reserved5227;	//0xC49054CC
	UINT32                                                 reserved5228;	//0xC49054D0
	UINT32                                                 reserved5229;	//0xC49054D4
	UINT32                                                 reserved5230;	//0xC49054D8
	UINT32                                                 reserved5231;	//0xC49054DC
	UINT32                                                 reserved5232;	//0xC49054E0
	UINT32                                                 reserved5233;	//0xC49054E4
	UINT32                                                 reserved5234;	//0xC49054E8
	UINT32                                                 reserved5235;	//0xC49054EC
	UINT32                                                 reserved5236;	//0xC49054F0
	UINT32                                                 reserved5237;	//0xC49054F4
	UINT32                                                 reserved5238;	//0xC49054F8
	UINT32                                                 reserved5239;	//0xC49054FC
	REG_DDRC_M1_DEBUG_ALP_T                                   debug_alp;	//0xC4905500
	REG_DDRC_M1_DEBUG_ALP_ENTRY_NUM_T               debug_alp_entry_num;	//0xC4905504
	REG_DDRC_M1_DEBUG_ALP_TIME_T                         debug_alp_time;	//0xC4905508
	REG_DDRC_M1_DEBUG_ALP_WAIT_CNT_T                 debug_alp_wait_cnt;	//0xC490550C
	UINT32                                                 reserved5240;	//0xC4905510
	UINT32                                                 reserved5241;	//0xC4905514
	UINT32                                                 reserved5242;	//0xC4905518
	UINT32                                                 reserved5243;	//0xC490551C
	UINT32                                                 reserved5244;	//0xC4905520
	UINT32                                                 reserved5245;	//0xC4905524
	UINT32                                                 reserved5246;	//0xC4905528
	UINT32                                                 reserved5247;	//0xC490552C
	UINT32                                                 reserved5248;	//0xC4905530
	UINT32                                                 reserved5249;	//0xC4905534
	UINT32                                                 reserved5250;	//0xC4905538
	UINT32                                                 reserved5251;	//0xC490553C
	UINT32                                                 reserved5252;	//0xC4905540
	UINT32                                                 reserved5253;	//0xC4905544
	UINT32                                                 reserved5254;	//0xC4905548
	UINT32                                                 reserved5255;	//0xC490554C
	UINT32                                                 reserved5256;	//0xC4905550
	UINT32                                                 reserved5257;	//0xC4905554
	UINT32                                                 reserved5258;	//0xC4905558
	UINT32                                                 reserved5259;	//0xC490555C
	UINT32                                                 reserved5260;	//0xC4905560
	UINT32                                                 reserved5261;	//0xC4905564
	UINT32                                                 reserved5262;	//0xC4905568
	UINT32                                                 reserved5263;	//0xC490556C
	UINT32                                                 reserved5264;	//0xC4905570
	UINT32                                                 reserved5265;	//0xC4905574
	UINT32                                                 reserved5266;	//0xC4905578
	UINT32                                                 reserved5267;	//0xC490557C
	UINT32                                                 reserved5268;	//0xC4905580
	UINT32                                                 reserved5269;	//0xC4905584
	UINT32                                                 reserved5270;	//0xC4905588
	UINT32                                                 reserved5271;	//0xC490558C
	UINT32                                                 reserved5272;	//0xC4905590
	UINT32                                                 reserved5273;	//0xC4905594
	UINT32                                                 reserved5274;	//0xC4905598
	UINT32                                                 reserved5275;	//0xC490559C
	UINT32                                                 reserved5276;	//0xC49055A0
	UINT32                                                 reserved5277;	//0xC49055A4
	UINT32                                                 reserved5278;	//0xC49055A8
	UINT32                                                 reserved5279;	//0xC49055AC
	UINT32                                                 reserved5280;	//0xC49055B0
	UINT32                                                 reserved5281;	//0xC49055B4
	UINT32                                                 reserved5282;	//0xC49055B8
	UINT32                                                 reserved5283;	//0xC49055BC
	UINT32                                                 reserved5284;	//0xC49055C0
	UINT32                                                 reserved5285;	//0xC49055C4
	UINT32                                                 reserved5286;	//0xC49055C8
	UINT32                                                 reserved5287;	//0xC49055CC
	UINT32                                                 reserved5288;	//0xC49055D0
	UINT32                                                 reserved5289;	//0xC49055D4
	UINT32                                                 reserved5290;	//0xC49055D8
	UINT32                                                 reserved5291;	//0xC49055DC
	UINT32                                                 reserved5292;	//0xC49055E0
	UINT32                                                 reserved5293;	//0xC49055E4
	UINT32                                                 reserved5294;	//0xC49055E8
	UINT32                                                 reserved5295;	//0xC49055EC
	UINT32                                                 reserved5296;	//0xC49055F0
	UINT32                                                 reserved5297;	//0xC49055F4
	UINT32                                                 reserved5298;	//0xC49055F8
	UINT32                                                 reserved5299;	//0xC49055FC
	REG_DDRC_M1_DEBUG_DFS_T                                   debug_dfs;	//0xC4905600
	UINT32                                                 reserved5300;	//0xC4905604
	UINT32                                                 reserved5301;	//0xC4905608
	UINT32                                                 reserved5302;	//0xC490560C
	UINT32                                                 reserved5303;	//0xC4905610
	UINT32                                                 reserved5304;	//0xC4905614
	UINT32                                                 reserved5305;	//0xC4905618
	UINT32                                                 reserved5306;	//0xC490561C
	UINT32                                                 reserved5307;	//0xC4905620
	UINT32                                                 reserved5308;	//0xC4905624
	UINT32                                                 reserved5309;	//0xC4905628
	UINT32                                                 reserved5310;	//0xC490562C
	UINT32                                                 reserved5311;	//0xC4905630
	UINT32                                                 reserved5312;	//0xC4905634
	UINT32                                                 reserved5313;	//0xC4905638
	UINT32                                                 reserved5314;	//0xC490563C
	UINT32                                                 reserved5315;	//0xC4905640
	UINT32                                                 reserved5316;	//0xC4905644
	UINT32                                                 reserved5317;	//0xC4905648
	UINT32                                                 reserved5318;	//0xC490564C
	UINT32                                                 reserved5319;	//0xC4905650
	UINT32                                                 reserved5320;	//0xC4905654
	UINT32                                                 reserved5321;	//0xC4905658
	UINT32                                                 reserved5322;	//0xC490565C
	UINT32                                                 reserved5323;	//0xC4905660
	UINT32                                                 reserved5324;	//0xC4905664
	UINT32                                                 reserved5325;	//0xC4905668
	UINT32                                                 reserved5326;	//0xC490566C
	UINT32                                                 reserved5327;	//0xC4905670
	UINT32                                                 reserved5328;	//0xC4905674
	UINT32                                                 reserved5329;	//0xC4905678
	UINT32                                                 reserved5330;	//0xC490567C
	UINT32                                                 reserved5331;	//0xC4905680
	UINT32                                                 reserved5332;	//0xC4905684
	UINT32                                                 reserved5333;	//0xC4905688
	UINT32                                                 reserved5334;	//0xC490568C
	UINT32                                                 reserved5335;	//0xC4905690
	UINT32                                                 reserved5336;	//0xC4905694
	UINT32                                                 reserved5337;	//0xC4905698
	UINT32                                                 reserved5338;	//0xC490569C
	UINT32                                                 reserved5339;	//0xC49056A0
	UINT32                                                 reserved5340;	//0xC49056A4
	UINT32                                                 reserved5341;	//0xC49056A8
	UINT32                                                 reserved5342;	//0xC49056AC
	UINT32                                                 reserved5343;	//0xC49056B0
	UINT32                                                 reserved5344;	//0xC49056B4
	UINT32                                                 reserved5345;	//0xC49056B8
	UINT32                                                 reserved5346;	//0xC49056BC
	UINT32                                                 reserved5347;	//0xC49056C0
	UINT32                                                 reserved5348;	//0xC49056C4
	UINT32                                                 reserved5349;	//0xC49056C8
	UINT32                                                 reserved5350;	//0xC49056CC
	UINT32                                                 reserved5351;	//0xC49056D0
	UINT32                                                 reserved5352;	//0xC49056D4
	UINT32                                                 reserved5353;	//0xC49056D8
	UINT32                                                 reserved5354;	//0xC49056DC
	UINT32                                                 reserved5355;	//0xC49056E0
	UINT32                                                 reserved5356;	//0xC49056E4
	UINT32                                                 reserved5357;	//0xC49056E8
	UINT32                                                 reserved5358;	//0xC49056EC
	UINT32                                                 reserved5359;	//0xC49056F0
	UINT32                                                 reserved5360;	//0xC49056F4
	UINT32                                                 reserved5361;	//0xC49056F8
	UINT32                                                 reserved5362;	//0xC49056FC
	REG_DDRC_M1_DEBUG_IDLE_CNT_T                         debug_idle_cnt;	//0xC4905700
	REG_DDRC_M1_DEBUG_RD_CNT_T                             debug_rd_cnt;	//0xC4905704
	REG_DDRC_M1_DEBUG_RDL_CNT_T                           debug_rdl_cnt;	//0xC4905708
	UINT32                                                 reserved5363;	//0xC490570C
	REG_DDRC_M1_DEBUG_RWR_CNT_T                           debug_rwr_cnt;	//0xC4905710
	REG_DDRC_M1_DEBUG_MWR_CNT_T                           debug_mwr_cnt;	//0xC4905714
	REG_DDRC_M1_DEBUG_WRL_CNT_T                           debug_wrl_cnt;	//0xC4905718
	UINT32                                                 reserved5364;	//0xC490571C
	REG_DDRC_M1_DEBUG_PRG_CNT_T                           debug_prg_cnt;	//0xC4905720
	REG_DDRC_M1_DEBUG_REF_CNT_T                           debug_ref_cnt;	//0xC4905724
	REG_DDRC_M1_DEBUG_ACT_CNT_T                           debug_act_cnt;	//0xC4905728
	REG_DDRC_M1_DEBUG_RW_SWC_CNT_T                     debug_rw_swc_cnt;	//0xC490572C
	REG_DDRC_M1_DEBUG_R_URG_SWC_CNT_T               debug_r_urg_swc_cnt;	//0xC4905730
	REG_DDRC_M1_DEBUG_R_REQ_ROW_HIT_CNT_T       debug_r_req_row_hit_cnt;	//0xC4905734
	REG_DDRC_M1_DEBUG_R_REQ_HIT_CNT_T               debug_r_req_hit_cnt;	//0xC4905738
	REG_DDRC_M1_DEBUG_R_URG_ROW_HIT_CNT_T       debug_r_urg_row_hit_cnt;	//0xC490573C
	REG_DDRC_M1_DEBUG_R_URG_HIT_CNT_T               debug_r_urg_hit_cnt;	//0xC4905740
	REG_DDRC_M1_DEBUG_R_ROW_HIT_CNT_T               debug_r_row_hit_cnt;	//0xC4905744
	REG_DDRC_M1_DEBUG_R_LUCKY_HIT_CNT_T           debug_r_lucky_hit_cnt;	//0xC4905748
	UINT32                                                 reserved5365;	//0xC490574C
	REG_DDRC_M1_DEBUG_W_URG_SWC_CNT_T               debug_w_urg_swc_cnt;	//0xC4905750
	REG_DDRC_M1_DEBUG_W_REQ_ROW_HIT_CNT_T       debug_w_req_row_hit_cnt;	//0xC4905754
	REG_DDRC_M1_DEBUG_W_REQ_HIT_CNT_T               debug_w_req_hit_cnt;	//0xC4905758
	REG_DDRC_M1_DEBUG_W_URG_ROW_HIT_CNT_T       debug_w_urg_row_hit_cnt;	//0xC490575C
	REG_DDRC_M1_DEBUG_W_URG_HIT_CNT_T               debug_w_urg_hit_cnt;	//0xC4905760
	REG_DDRC_M1_DEBUG_W_ROW_HIT_CNT_T               debug_w_row_hit_cnt;	//0xC4905764
	REG_DDRC_M1_DEBUG_W_LUCKY_HIT_CNT_T           debug_w_lucky_hit_cnt;	//0xC4905768
	UINT32                                                 reserved5366;	//0xC490576C
	REG_DDRC_M1_DEBUG_MAX_LAT_QOS_T                   debug_max_lat_qos;	//0xC4905770
	UINT32                                                 reserved5367;	//0xC4905774
	UINT32                                                 reserved5368;	//0xC4905778
	UINT32                                                 reserved5369;	//0xC490577C
	UINT32                                                 reserved5370;	//0xC4905780
	UINT32                                                 reserved5371;	//0xC4905784
	UINT32                                                 reserved5372;	//0xC4905788
	UINT32                                                 reserved5373;	//0xC490578C
	UINT32                                                 reserved5374;	//0xC4905790
	UINT32                                                 reserved5375;	//0xC4905794
	UINT32                                                 reserved5376;	//0xC4905798
	UINT32                                                 reserved5377;	//0xC490579C
	UINT32                                                 reserved5378;	//0xC49057A0
	UINT32                                                 reserved5379;	//0xC49057A4
	UINT32                                                 reserved5380;	//0xC49057A8
	UINT32                                                 reserved5381;	//0xC49057AC
	UINT32                                                 reserved5382;	//0xC49057B0
	UINT32                                                 reserved5383;	//0xC49057B4
	UINT32                                                 reserved5384;	//0xC49057B8
	UINT32                                                 reserved5385;	//0xC49057BC
	UINT32                                                 reserved5386;	//0xC49057C0
	UINT32                                                 reserved5387;	//0xC49057C4
	UINT32                                                 reserved5388;	//0xC49057C8
	UINT32                                                 reserved5389;	//0xC49057CC
	UINT32                                                 reserved5390;	//0xC49057D0
	UINT32                                                 reserved5391;	//0xC49057D4
	UINT32                                                 reserved5392;	//0xC49057D8
	UINT32                                                 reserved5393;	//0xC49057DC
	UINT32                                                 reserved5394;	//0xC49057E0
	UINT32                                                 reserved5395;	//0xC49057E4
	UINT32                                                 reserved5396;	//0xC49057E8
	UINT32                                                 reserved5397;	//0xC49057EC
	UINT32                                                 reserved5398;	//0xC49057F0
	UINT32                                                 reserved5399;	//0xC49057F4
	UINT32                                                 reserved5400;	//0xC49057F8
	UINT32                                                 reserved5401;	//0xC49057FC
	REG_DDRC_M1_DEBUG_R_HYB_SWC_CNT_T               debug_r_hyb_swc_cnt;	//0xC4905800
	REG_DDRC_M1_DEBUG_W_HYB_SWC_CNT_T               debug_w_hyb_swc_cnt;	//0xC4905804
	UINT32                                                 reserved5402;	//0xC4905808
	UINT32                                                 reserved5403;	//0xC490580C
	UINT32                                                 reserved5404;	//0xC4905810
	UINT32                                                 reserved5405;	//0xC4905814
	UINT32                                                 reserved5406;	//0xC4905818
	UINT32                                                 reserved5407;	//0xC490581C
	UINT32                                                 reserved5408;	//0xC4905820
	UINT32                                                 reserved5409;	//0xC4905824
	UINT32                                                 reserved5410;	//0xC4905828
	UINT32                                                 reserved5411;	//0xC490582C
	UINT32                                                 reserved5412;	//0xC4905830
	UINT32                                                 reserved5413;	//0xC4905834
	UINT32                                                 reserved5414;	//0xC4905838
	UINT32                                                 reserved5415;	//0xC490583C
	UINT32                                                 reserved5416;	//0xC4905840
	UINT32                                                 reserved5417;	//0xC4905844
	UINT32                                                 reserved5418;	//0xC4905848
	UINT32                                                 reserved5419;	//0xC490584C
	UINT32                                                 reserved5420;	//0xC4905850
	UINT32                                                 reserved5421;	//0xC4905854
	UINT32                                                 reserved5422;	//0xC4905858
	UINT32                                                 reserved5423;	//0xC490585C
	UINT32                                                 reserved5424;	//0xC4905860
	UINT32                                                 reserved5425;	//0xC4905864
	UINT32                                                 reserved5426;	//0xC4905868
	UINT32                                                 reserved5427;	//0xC490586C
	UINT32                                                 reserved5428;	//0xC4905870
	UINT32                                                 reserved5429;	//0xC4905874
	UINT32                                                 reserved5430;	//0xC4905878
	UINT32                                                 reserved5431;	//0xC490587C
	UINT32                                                 reserved5432;	//0xC4905880
	UINT32                                                 reserved5433;	//0xC4905884
	UINT32                                                 reserved5434;	//0xC4905888
	UINT32                                                 reserved5435;	//0xC490588C
	UINT32                                                 reserved5436;	//0xC4905890
	UINT32                                                 reserved5437;	//0xC4905894
	UINT32                                                 reserved5438;	//0xC4905898
	UINT32                                                 reserved5439;	//0xC490589C
	UINT32                                                 reserved5440;	//0xC49058A0
	UINT32                                                 reserved5441;	//0xC49058A4
	UINT32                                                 reserved5442;	//0xC49058A8
	UINT32                                                 reserved5443;	//0xC49058AC
	UINT32                                                 reserved5444;	//0xC49058B0
	UINT32                                                 reserved5445;	//0xC49058B4
	UINT32                                                 reserved5446;	//0xC49058B8
	UINT32                                                 reserved5447;	//0xC49058BC
	UINT32                                                 reserved5448;	//0xC49058C0
	UINT32                                                 reserved5449;	//0xC49058C4
	UINT32                                                 reserved5450;	//0xC49058C8
	UINT32                                                 reserved5451;	//0xC49058CC
	UINT32                                                 reserved5452;	//0xC49058D0
	UINT32                                                 reserved5453;	//0xC49058D4
	UINT32                                                 reserved5454;	//0xC49058D8
	UINT32                                                 reserved5455;	//0xC49058DC
	UINT32                                                 reserved5456;	//0xC49058E0
	UINT32                                                 reserved5457;	//0xC49058E4
	UINT32                                                 reserved5458;	//0xC49058E8
	UINT32                                                 reserved5459;	//0xC49058EC
	UINT32                                                 reserved5460;	//0xC49058F0
	UINT32                                                 reserved5461;	//0xC49058F4
	UINT32                                                 reserved5462;	//0xC49058F8
	UINT32                                                 reserved5463;	//0xC49058FC
	REG_DDRC_M1_DEBUG_R_FIFO_0_PRT_CNT_T         debug_r_fifo_0_prt_cnt;	//0xC4905900
	REG_DDRC_M1_DEBUG_R_FIFO_1_PRT_CNT_T         debug_r_fifo_1_prt_cnt;	//0xC4905904
	REG_DDRC_M1_DEBUG_R_FIFO_2_PRT_CNT_T         debug_r_fifo_2_prt_cnt;	//0xC4905908
	REG_DDRC_M1_DEBUG_R_FIFO_3_PRT_CNT_T         debug_r_fifo_3_prt_cnt;	//0xC490590C
	REG_DDRC_M1_DEBUG_W_FIFO_0_PRT_CNT_T         debug_w_fifo_0_prt_cnt;	//0xC4905910
	REG_DDRC_M1_DEBUG_W_FIFO_1_PRT_CNT_T         debug_w_fifo_1_prt_cnt;	//0xC4905914
	REG_DDRC_M1_DEBUG_W_FIFO_2_PRT_CNT_T         debug_w_fifo_2_prt_cnt;	//0xC4905918
	REG_DDRC_M1_DEBUG_W_FIFO_3_PRT_CNT_T         debug_w_fifo_3_prt_cnt;	//0xC490591C
	UINT32                                                 reserved5464;	//0xC4905920
	UINT32                                                 reserved5465;	//0xC4905924
	UINT32                                                 reserved5466;	//0xC4905928
	UINT32                                                 reserved5467;	//0xC490592C
	UINT32                                                 reserved5468;	//0xC4905930
	UINT32                                                 reserved5469;	//0xC4905934
	UINT32                                                 reserved5470;	//0xC4905938
	UINT32                                                 reserved5471;	//0xC490593C
	UINT32                                                 reserved5472;	//0xC4905940
	UINT32                                                 reserved5473;	//0xC4905944
	UINT32                                                 reserved5474;	//0xC4905948
	UINT32                                                 reserved5475;	//0xC490594C
	UINT32                                                 reserved5476;	//0xC4905950
	UINT32                                                 reserved5477;	//0xC4905954
	UINT32                                                 reserved5478;	//0xC4905958
	UINT32                                                 reserved5479;	//0xC490595C
	UINT32                                                 reserved5480;	//0xC4905960
	UINT32                                                 reserved5481;	//0xC4905964
	UINT32                                                 reserved5482;	//0xC4905968
	UINT32                                                 reserved5483;	//0xC490596C
	UINT32                                                 reserved5484;	//0xC4905970
	UINT32                                                 reserved5485;	//0xC4905974
	UINT32                                                 reserved5486;	//0xC4905978
	UINT32                                                 reserved5487;	//0xC490597C
	UINT32                                                 reserved5488;	//0xC4905980
	UINT32                                                 reserved5489;	//0xC4905984
	UINT32                                                 reserved5490;	//0xC4905988
	UINT32                                                 reserved5491;	//0xC490598C
	UINT32                                                 reserved5492;	//0xC4905990
	UINT32                                                 reserved5493;	//0xC4905994
	UINT32                                                 reserved5494;	//0xC4905998
	UINT32                                                 reserved5495;	//0xC490599C
	UINT32                                                 reserved5496;	//0xC49059A0
	UINT32                                                 reserved5497;	//0xC49059A4
	UINT32                                                 reserved5498;	//0xC49059A8
	UINT32                                                 reserved5499;	//0xC49059AC
	UINT32                                                 reserved5500;	//0xC49059B0
	UINT32                                                 reserved5501;	//0xC49059B4
	UINT32                                                 reserved5502;	//0xC49059B8
	UINT32                                                 reserved5503;	//0xC49059BC
	UINT32                                                 reserved5504;	//0xC49059C0
	UINT32                                                 reserved5505;	//0xC49059C4
	UINT32                                                 reserved5506;	//0xC49059C8
	UINT32                                                 reserved5507;	//0xC49059CC
	UINT32                                                 reserved5508;	//0xC49059D0
	UINT32                                                 reserved5509;	//0xC49059D4
	UINT32                                                 reserved5510;	//0xC49059D8
	UINT32                                                 reserved5511;	//0xC49059DC
	UINT32                                                 reserved5512;	//0xC49059E0
	UINT32                                                 reserved5513;	//0xC49059E4
	UINT32                                                 reserved5514;	//0xC49059E8
	UINT32                                                 reserved5515;	//0xC49059EC
	UINT32                                                 reserved5516;	//0xC49059F0
	UINT32                                                 reserved5517;	//0xC49059F4
	UINT32                                                 reserved5518;	//0xC49059F8
	UINT32                                                 reserved5519;	//0xC49059FC
	UINT32                                                 reserved5520;	//0xC4905A00
	UINT32                                                 reserved5521;	//0xC4905A04
	UINT32                                                 reserved5522;	//0xC4905A08
	UINT32                                                 reserved5523;	//0xC4905A0C
	UINT32                                                 reserved5524;	//0xC4905A10
	UINT32                                                 reserved5525;	//0xC4905A14
	UINT32                                                 reserved5526;	//0xC4905A18
	UINT32                                                 reserved5527;	//0xC4905A1C
	UINT32                                                 reserved5528;	//0xC4905A20
	UINT32                                                 reserved5529;	//0xC4905A24
	UINT32                                                 reserved5530;	//0xC4905A28
	UINT32                                                 reserved5531;	//0xC4905A2C
	UINT32                                                 reserved5532;	//0xC4905A30
	UINT32                                                 reserved5533;	//0xC4905A34
	UINT32                                                 reserved5534;	//0xC4905A38
	UINT32                                                 reserved5535;	//0xC4905A3C
	UINT32                                                 reserved5536;	//0xC4905A40
	UINT32                                                 reserved5537;	//0xC4905A44
	UINT32                                                 reserved5538;	//0xC4905A48
	UINT32                                                 reserved5539;	//0xC4905A4C
	UINT32                                                 reserved5540;	//0xC4905A50
	UINT32                                                 reserved5541;	//0xC4905A54
	UINT32                                                 reserved5542;	//0xC4905A58
	UINT32                                                 reserved5543;	//0xC4905A5C
	UINT32                                                 reserved5544;	//0xC4905A60
	UINT32                                                 reserved5545;	//0xC4905A64
	UINT32                                                 reserved5546;	//0xC4905A68
	UINT32                                                 reserved5547;	//0xC4905A6C
	UINT32                                                 reserved5548;	//0xC4905A70
	UINT32                                                 reserved5549;	//0xC4905A74
	UINT32                                                 reserved5550;	//0xC4905A78
	UINT32                                                 reserved5551;	//0xC4905A7C
	UINT32                                                 reserved5552;	//0xC4905A80
	UINT32                                                 reserved5553;	//0xC4905A84
	UINT32                                                 reserved5554;	//0xC4905A88
	UINT32                                                 reserved5555;	//0xC4905A8C
	UINT32                                                 reserved5556;	//0xC4905A90
	UINT32                                                 reserved5557;	//0xC4905A94
	UINT32                                                 reserved5558;	//0xC4905A98
	UINT32                                                 reserved5559;	//0xC4905A9C
	UINT32                                                 reserved5560;	//0xC4905AA0
	UINT32                                                 reserved5561;	//0xC4905AA4
	UINT32                                                 reserved5562;	//0xC4905AA8
	UINT32                                                 reserved5563;	//0xC4905AAC
	UINT32                                                 reserved5564;	//0xC4905AB0
	UINT32                                                 reserved5565;	//0xC4905AB4
	UINT32                                                 reserved5566;	//0xC4905AB8
	UINT32                                                 reserved5567;	//0xC4905ABC
	UINT32                                                 reserved5568;	//0xC4905AC0
	UINT32                                                 reserved5569;	//0xC4905AC4
	UINT32                                                 reserved5570;	//0xC4905AC8
	UINT32                                                 reserved5571;	//0xC4905ACC
	UINT32                                                 reserved5572;	//0xC4905AD0
	UINT32                                                 reserved5573;	//0xC4905AD4
	UINT32                                                 reserved5574;	//0xC4905AD8
	UINT32                                                 reserved5575;	//0xC4905ADC
	UINT32                                                 reserved5576;	//0xC4905AE0
	UINT32                                                 reserved5577;	//0xC4905AE4
	UINT32                                                 reserved5578;	//0xC4905AE8
	UINT32                                                 reserved5579;	//0xC4905AEC
	UINT32                                                 reserved5580;	//0xC4905AF0
	UINT32                                                 reserved5581;	//0xC4905AF4
	UINT32                                                 reserved5582;	//0xC4905AF8
	UINT32                                                 reserved5583;	//0xC4905AFC
	UINT32                                                 reserved5584;	//0xC4905B00
	UINT32                                                 reserved5585;	//0xC4905B04
	UINT32                                                 reserved5586;	//0xC4905B08
	UINT32                                                 reserved5587;	//0xC4905B0C
	UINT32                                                 reserved5588;	//0xC4905B10
	UINT32                                                 reserved5589;	//0xC4905B14
	UINT32                                                 reserved5590;	//0xC4905B18
	UINT32                                                 reserved5591;	//0xC4905B1C
	UINT32                                                 reserved5592;	//0xC4905B20
	UINT32                                                 reserved5593;	//0xC4905B24
	UINT32                                                 reserved5594;	//0xC4905B28
	UINT32                                                 reserved5595;	//0xC4905B2C
	UINT32                                                 reserved5596;	//0xC4905B30
	UINT32                                                 reserved5597;	//0xC4905B34
	UINT32                                                 reserved5598;	//0xC4905B38
	UINT32                                                 reserved5599;	//0xC4905B3C
	UINT32                                                 reserved5600;	//0xC4905B40
	UINT32                                                 reserved5601;	//0xC4905B44
	UINT32                                                 reserved5602;	//0xC4905B48
	UINT32                                                 reserved5603;	//0xC4905B4C
	UINT32                                                 reserved5604;	//0xC4905B50
	UINT32                                                 reserved5605;	//0xC4905B54
	UINT32                                                 reserved5606;	//0xC4905B58
	UINT32                                                 reserved5607;	//0xC4905B5C
	UINT32                                                 reserved5608;	//0xC4905B60
	UINT32                                                 reserved5609;	//0xC4905B64
	UINT32                                                 reserved5610;	//0xC4905B68
	UINT32                                                 reserved5611;	//0xC4905B6C
	UINT32                                                 reserved5612;	//0xC4905B70
	UINT32                                                 reserved5613;	//0xC4905B74
	UINT32                                                 reserved5614;	//0xC4905B78
	UINT32                                                 reserved5615;	//0xC4905B7C
	UINT32                                                 reserved5616;	//0xC4905B80
	UINT32                                                 reserved5617;	//0xC4905B84
	UINT32                                                 reserved5618;	//0xC4905B88
	UINT32                                                 reserved5619;	//0xC4905B8C
	UINT32                                                 reserved5620;	//0xC4905B90
	UINT32                                                 reserved5621;	//0xC4905B94
	UINT32                                                 reserved5622;	//0xC4905B98
	UINT32                                                 reserved5623;	//0xC4905B9C
	UINT32                                                 reserved5624;	//0xC4905BA0
	UINT32                                                 reserved5625;	//0xC4905BA4
	UINT32                                                 reserved5626;	//0xC4905BA8
	UINT32                                                 reserved5627;	//0xC4905BAC
	UINT32                                                 reserved5628;	//0xC4905BB0
	UINT32                                                 reserved5629;	//0xC4905BB4
	UINT32                                                 reserved5630;	//0xC4905BB8
	UINT32                                                 reserved5631;	//0xC4905BBC
	UINT32                                                 reserved5632;	//0xC4905BC0
	UINT32                                                 reserved5633;	//0xC4905BC4
	UINT32                                                 reserved5634;	//0xC4905BC8
	UINT32                                                 reserved5635;	//0xC4905BCC
	UINT32                                                 reserved5636;	//0xC4905BD0
	UINT32                                                 reserved5637;	//0xC4905BD4
	UINT32                                                 reserved5638;	//0xC4905BD8
	UINT32                                                 reserved5639;	//0xC4905BDC
	UINT32                                                 reserved5640;	//0xC4905BE0
	UINT32                                                 reserved5641;	//0xC4905BE4
	UINT32                                                 reserved5642;	//0xC4905BE8
	UINT32                                                 reserved5643;	//0xC4905BEC
	UINT32                                                 reserved5644;	//0xC4905BF0
	UINT32                                                 reserved5645;	//0xC4905BF4
	UINT32                                                 reserved5646;	//0xC4905BF8
	UINT32                                                 reserved5647;	//0xC4905BFC
	UINT32                                                 reserved5648;	//0xC4905C00
	UINT32                                                 reserved5649;	//0xC4905C04
	UINT32                                                 reserved5650;	//0xC4905C08
	UINT32                                                 reserved5651;	//0xC4905C0C
	UINT32                                                 reserved5652;	//0xC4905C10
	UINT32                                                 reserved5653;	//0xC4905C14
	UINT32                                                 reserved5654;	//0xC4905C18
	UINT32                                                 reserved5655;	//0xC4905C1C
	UINT32                                                 reserved5656;	//0xC4905C20
	UINT32                                                 reserved5657;	//0xC4905C24
	UINT32                                                 reserved5658;	//0xC4905C28
	UINT32                                                 reserved5659;	//0xC4905C2C
	UINT32                                                 reserved5660;	//0xC4905C30
	UINT32                                                 reserved5661;	//0xC4905C34
	UINT32                                                 reserved5662;	//0xC4905C38
	UINT32                                                 reserved5663;	//0xC4905C3C
	UINT32                                                 reserved5664;	//0xC4905C40
	UINT32                                                 reserved5665;	//0xC4905C44
	UINT32                                                 reserved5666;	//0xC4905C48
	UINT32                                                 reserved5667;	//0xC4905C4C
	UINT32                                                 reserved5668;	//0xC4905C50
	UINT32                                                 reserved5669;	//0xC4905C54
	UINT32                                                 reserved5670;	//0xC4905C58
	UINT32                                                 reserved5671;	//0xC4905C5C
	UINT32                                                 reserved5672;	//0xC4905C60
	UINT32                                                 reserved5673;	//0xC4905C64
	UINT32                                                 reserved5674;	//0xC4905C68
	UINT32                                                 reserved5675;	//0xC4905C6C
	UINT32                                                 reserved5676;	//0xC4905C70
	UINT32                                                 reserved5677;	//0xC4905C74
	UINT32                                                 reserved5678;	//0xC4905C78
	UINT32                                                 reserved5679;	//0xC4905C7C
	UINT32                                                 reserved5680;	//0xC4905C80
	UINT32                                                 reserved5681;	//0xC4905C84
	UINT32                                                 reserved5682;	//0xC4905C88
	UINT32                                                 reserved5683;	//0xC4905C8C
	UINT32                                                 reserved5684;	//0xC4905C90
	UINT32                                                 reserved5685;	//0xC4905C94
	UINT32                                                 reserved5686;	//0xC4905C98
	UINT32                                                 reserved5687;	//0xC4905C9C
	UINT32                                                 reserved5688;	//0xC4905CA0
	UINT32                                                 reserved5689;	//0xC4905CA4
	UINT32                                                 reserved5690;	//0xC4905CA8
	UINT32                                                 reserved5691;	//0xC4905CAC
	UINT32                                                 reserved5692;	//0xC4905CB0
	UINT32                                                 reserved5693;	//0xC4905CB4
	UINT32                                                 reserved5694;	//0xC4905CB8
	UINT32                                                 reserved5695;	//0xC4905CBC
	UINT32                                                 reserved5696;	//0xC4905CC0
	UINT32                                                 reserved5697;	//0xC4905CC4
	UINT32                                                 reserved5698;	//0xC4905CC8
	UINT32                                                 reserved5699;	//0xC4905CCC
	UINT32                                                 reserved5700;	//0xC4905CD0
	UINT32                                                 reserved5701;	//0xC4905CD4
	UINT32                                                 reserved5702;	//0xC4905CD8
	UINT32                                                 reserved5703;	//0xC4905CDC
	UINT32                                                 reserved5704;	//0xC4905CE0
	UINT32                                                 reserved5705;	//0xC4905CE4
	UINT32                                                 reserved5706;	//0xC4905CE8
	UINT32                                                 reserved5707;	//0xC4905CEC
	UINT32                                                 reserved5708;	//0xC4905CF0
	UINT32                                                 reserved5709;	//0xC4905CF4
	UINT32                                                 reserved5710;	//0xC4905CF8
	UINT32                                                 reserved5711;	//0xC4905CFC
	UINT32                                                 reserved5712;	//0xC4905D00
	UINT32                                                 reserved5713;	//0xC4905D04
	UINT32                                                 reserved5714;	//0xC4905D08
	UINT32                                                 reserved5715;	//0xC4905D0C
	UINT32                                                 reserved5716;	//0xC4905D10
	UINT32                                                 reserved5717;	//0xC4905D14
	UINT32                                                 reserved5718;	//0xC4905D18
	UINT32                                                 reserved5719;	//0xC4905D1C
	UINT32                                                 reserved5720;	//0xC4905D20
	UINT32                                                 reserved5721;	//0xC4905D24
	UINT32                                                 reserved5722;	//0xC4905D28
	UINT32                                                 reserved5723;	//0xC4905D2C
	UINT32                                                 reserved5724;	//0xC4905D30
	UINT32                                                 reserved5725;	//0xC4905D34
	UINT32                                                 reserved5726;	//0xC4905D38
	UINT32                                                 reserved5727;	//0xC4905D3C
	UINT32                                                 reserved5728;	//0xC4905D40
	UINT32                                                 reserved5729;	//0xC4905D44
	UINT32                                                 reserved5730;	//0xC4905D48
	UINT32                                                 reserved5731;	//0xC4905D4C
	UINT32                                                 reserved5732;	//0xC4905D50
	UINT32                                                 reserved5733;	//0xC4905D54
	UINT32                                                 reserved5734;	//0xC4905D58
	UINT32                                                 reserved5735;	//0xC4905D5C
	UINT32                                                 reserved5736;	//0xC4905D60
	UINT32                                                 reserved5737;	//0xC4905D64
	UINT32                                                 reserved5738;	//0xC4905D68
	UINT32                                                 reserved5739;	//0xC4905D6C
	UINT32                                                 reserved5740;	//0xC4905D70
	UINT32                                                 reserved5741;	//0xC4905D74
	UINT32                                                 reserved5742;	//0xC4905D78
	UINT32                                                 reserved5743;	//0xC4905D7C
	UINT32                                                 reserved5744;	//0xC4905D80
	UINT32                                                 reserved5745;	//0xC4905D84
	UINT32                                                 reserved5746;	//0xC4905D88
	UINT32                                                 reserved5747;	//0xC4905D8C
	UINT32                                                 reserved5748;	//0xC4905D90
	UINT32                                                 reserved5749;	//0xC4905D94
	UINT32                                                 reserved5750;	//0xC4905D98
	UINT32                                                 reserved5751;	//0xC4905D9C
	UINT32                                                 reserved5752;	//0xC4905DA0
	UINT32                                                 reserved5753;	//0xC4905DA4
	UINT32                                                 reserved5754;	//0xC4905DA8
	UINT32                                                 reserved5755;	//0xC4905DAC
	UINT32                                                 reserved5756;	//0xC4905DB0
	UINT32                                                 reserved5757;	//0xC4905DB4
	UINT32                                                 reserved5758;	//0xC4905DB8
	UINT32                                                 reserved5759;	//0xC4905DBC
	UINT32                                                 reserved5760;	//0xC4905DC0
	UINT32                                                 reserved5761;	//0xC4905DC4
	UINT32                                                 reserved5762;	//0xC4905DC8
	UINT32                                                 reserved5763;	//0xC4905DCC
	UINT32                                                 reserved5764;	//0xC4905DD0
	UINT32                                                 reserved5765;	//0xC4905DD4
	UINT32                                                 reserved5766;	//0xC4905DD8
	UINT32                                                 reserved5767;	//0xC4905DDC
	UINT32                                                 reserved5768;	//0xC4905DE0
	UINT32                                                 reserved5769;	//0xC4905DE4
	UINT32                                                 reserved5770;	//0xC4905DE8
	UINT32                                                 reserved5771;	//0xC4905DEC
	UINT32                                                 reserved5772;	//0xC4905DF0
	UINT32                                                 reserved5773;	//0xC4905DF4
	UINT32                                                 reserved5774;	//0xC4905DF8
	UINT32                                                 reserved5775;	//0xC4905DFC
	UINT32                                                 reserved5776;	//0xC4905E00
	UINT32                                                 reserved5777;	//0xC4905E04
	UINT32                                                 reserved5778;	//0xC4905E08
	UINT32                                                 reserved5779;	//0xC4905E0C
	UINT32                                                 reserved5780;	//0xC4905E10
	UINT32                                                 reserved5781;	//0xC4905E14
	UINT32                                                 reserved5782;	//0xC4905E18
	UINT32                                                 reserved5783;	//0xC4905E1C
	UINT32                                                 reserved5784;	//0xC4905E20
	UINT32                                                 reserved5785;	//0xC4905E24
	UINT32                                                 reserved5786;	//0xC4905E28
	UINT32                                                 reserved5787;	//0xC4905E2C
	UINT32                                                 reserved5788;	//0xC4905E30
	UINT32                                                 reserved5789;	//0xC4905E34
	UINT32                                                 reserved5790;	//0xC4905E38
	UINT32                                                 reserved5791;	//0xC4905E3C
	UINT32                                                 reserved5792;	//0xC4905E40
	UINT32                                                 reserved5793;	//0xC4905E44
	UINT32                                                 reserved5794;	//0xC4905E48
	UINT32                                                 reserved5795;	//0xC4905E4C
	UINT32                                                 reserved5796;	//0xC4905E50
	UINT32                                                 reserved5797;	//0xC4905E54
	UINT32                                                 reserved5798;	//0xC4905E58
	UINT32                                                 reserved5799;	//0xC4905E5C
	UINT32                                                 reserved5800;	//0xC4905E60
	UINT32                                                 reserved5801;	//0xC4905E64
	UINT32                                                 reserved5802;	//0xC4905E68
	UINT32                                                 reserved5803;	//0xC4905E6C
	UINT32                                                 reserved5804;	//0xC4905E70
	UINT32                                                 reserved5805;	//0xC4905E74
	UINT32                                                 reserved5806;	//0xC4905E78
	UINT32                                                 reserved5807;	//0xC4905E7C
	UINT32                                                 reserved5808;	//0xC4905E80
	UINT32                                                 reserved5809;	//0xC4905E84
	UINT32                                                 reserved5810;	//0xC4905E88
	UINT32                                                 reserved5811;	//0xC4905E8C
	UINT32                                                 reserved5812;	//0xC4905E90
	UINT32                                                 reserved5813;	//0xC4905E94
	UINT32                                                 reserved5814;	//0xC4905E98
	UINT32                                                 reserved5815;	//0xC4905E9C
	UINT32                                                 reserved5816;	//0xC4905EA0
	UINT32                                                 reserved5817;	//0xC4905EA4
	UINT32                                                 reserved5818;	//0xC4905EA8
	UINT32                                                 reserved5819;	//0xC4905EAC
	UINT32                                                 reserved5820;	//0xC4905EB0
	UINT32                                                 reserved5821;	//0xC4905EB4
	UINT32                                                 reserved5822;	//0xC4905EB8
	UINT32                                                 reserved5823;	//0xC4905EBC
	UINT32                                                 reserved5824;	//0xC4905EC0
	UINT32                                                 reserved5825;	//0xC4905EC4
	UINT32                                                 reserved5826;	//0xC4905EC8
	UINT32                                                 reserved5827;	//0xC4905ECC
	UINT32                                                 reserved5828;	//0xC4905ED0
	UINT32                                                 reserved5829;	//0xC4905ED4
	UINT32                                                 reserved5830;	//0xC4905ED8
	UINT32                                                 reserved5831;	//0xC4905EDC
	UINT32                                                 reserved5832;	//0xC4905EE0
	UINT32                                                 reserved5833;	//0xC4905EE4
	UINT32                                                 reserved5834;	//0xC4905EE8
	UINT32                                                 reserved5835;	//0xC4905EEC
	UINT32                                                 reserved5836;	//0xC4905EF0
	UINT32                                                 reserved5837;	//0xC4905EF4
	UINT32                                                 reserved5838;	//0xC4905EF8
	UINT32                                                 reserved5839;	//0xC4905EFC
	UINT32                                                 reserved5840;	//0xC4905F00
	UINT32                                                 reserved5841;	//0xC4905F04
	UINT32                                                 reserved5842;	//0xC4905F08
	UINT32                                                 reserved5843;	//0xC4905F0C
	UINT32                                                 reserved5844;	//0xC4905F10
	UINT32                                                 reserved5845;	//0xC4905F14
	UINT32                                                 reserved5846;	//0xC4905F18
	UINT32                                                 reserved5847;	//0xC4905F1C
	UINT32                                                 reserved5848;	//0xC4905F20
	UINT32                                                 reserved5849;	//0xC4905F24
	UINT32                                                 reserved5850;	//0xC4905F28
	UINT32                                                 reserved5851;	//0xC4905F2C
	UINT32                                                 reserved5852;	//0xC4905F30
	UINT32                                                 reserved5853;	//0xC4905F34
	UINT32                                                 reserved5854;	//0xC4905F38
	UINT32                                                 reserved5855;	//0xC4905F3C
	UINT32                                                 reserved5856;	//0xC4905F40
	UINT32                                                 reserved5857;	//0xC4905F44
	UINT32                                                 reserved5858;	//0xC4905F48
	UINT32                                                 reserved5859;	//0xC4905F4C
	UINT32                                                 reserved5860;	//0xC4905F50
	UINT32                                                 reserved5861;	//0xC4905F54
	UINT32                                                 reserved5862;	//0xC4905F58
	UINT32                                                 reserved5863;	//0xC4905F5C
	UINT32                                                 reserved5864;	//0xC4905F60
	UINT32                                                 reserved5865;	//0xC4905F64
	UINT32                                                 reserved5866;	//0xC4905F68
	UINT32                                                 reserved5867;	//0xC4905F6C
	UINT32                                                 reserved5868;	//0xC4905F70
	UINT32                                                 reserved5869;	//0xC4905F74
	UINT32                                                 reserved5870;	//0xC4905F78
	UINT32                                                 reserved5871;	//0xC4905F7C
	UINT32                                                 reserved5872;	//0xC4905F80
	UINT32                                                 reserved5873;	//0xC4905F84
	UINT32                                                 reserved5874;	//0xC4905F88
	UINT32                                                 reserved5875;	//0xC4905F8C
	UINT32                                                 reserved5876;	//0xC4905F90
	UINT32                                                 reserved5877;	//0xC4905F94
	UINT32                                                 reserved5878;	//0xC4905F98
	UINT32                                                 reserved5879;	//0xC4905F9C
	UINT32                                                 reserved5880;	//0xC4905FA0
	UINT32                                                 reserved5881;	//0xC4905FA4
	UINT32                                                 reserved5882;	//0xC4905FA8
	UINT32                                                 reserved5883;	//0xC4905FAC
	UINT32                                                 reserved5884;	//0xC4905FB0
	UINT32                                                 reserved5885;	//0xC4905FB4
	UINT32                                                 reserved5886;	//0xC4905FB8
	UINT32                                                 reserved5887;	//0xC4905FBC
	UINT32                                                 reserved5888;	//0xC4905FC0
	UINT32                                                 reserved5889;	//0xC4905FC4
	UINT32                                                 reserved5890;	//0xC4905FC8
	UINT32                                                 reserved5891;	//0xC4905FCC
	UINT32                                                 reserved5892;	//0xC4905FD0
	UINT32                                                 reserved5893;	//0xC4905FD4
	UINT32                                                 reserved5894;	//0xC4905FD8
	UINT32                                                 reserved5895;	//0xC4905FDC
	UINT32                                                 reserved5896;	//0xC4905FE0
	UINT32                                                 reserved5897;	//0xC4905FE4
	UINT32                                                 reserved5898;	//0xC4905FE8
	UINT32                                                 reserved5899;	//0xC4905FEC
	UINT32                                                 reserved5900;	//0xC4905FF0
	UINT32                                                 reserved5901;	//0xC4905FF4
	UINT32                                                 reserved5902;	//0xC4905FF8
	UINT32                                                 reserved5903;	//0xC4905FFC
	REG_DDRC_M1_DEBUG_LPD4_0_T                             debug_lpd4_0;	//0xC4906000
	REG_DDRC_M1_DEBUG_LPD4_1_T                             debug_lpd4_1;	//0xC4906004
	REG_DDRC_M1_DEBUG_LPD4_2_T                             debug_lpd4_2;	//0xC4906008
	REG_DDRC_M1_DEBUG_LPD4_3_T                             debug_lpd4_3;	//0xC490600C
	REG_DDRC_M1_DEBUG_LPD4_4_T                             debug_lpd4_4;	//0xC4906010
	REG_DDRC_M1_DEBUG_LPD4_5_T                             debug_lpd4_5;	//0xC4906014
	REG_DDRC_M1_DEBUG_LPD4_6_T                             debug_lpd4_6;	//0xC4906018
	REG_DDRC_M1_DEBUG_LPD4_7_T                             debug_lpd4_7;	//0xC490601C
	REG_DDRC_M1_DEBUG_LPD4_8_T                             debug_lpd4_8;	//0xC4906020
	REG_DDRC_M1_DEBUG_LPD4_9_T                             debug_lpd4_9;	//0xC4906024
	REG_DDRC_M1_DEBUG_LPD4_10_T                           debug_lpd4_10;	//0xC4906028
	REG_DDRC_M1_DEBUG_LPD4_11_T                           debug_lpd4_11;	//0xC490602C
	REG_DDRC_M1_DEBUG_LPD4_12_T                           debug_lpd4_12;	//0xC4906030
	REG_DDRC_M1_DEBUG_LPD4_13_T                           debug_lpd4_13;	//0xC4906034
	REG_DDRC_M1_DEBUG_LPD4_14_T                           debug_lpd4_14;	//0xC4906038
	REG_DDRC_M1_DEBUG_LPD4_15_T                           debug_lpd4_15;	//0xC490603C
	REG_DDRC_M1_DEBUG_LPD4_16_T                           debug_lpd4_16;	//0xC4906040
	UINT32                                                 reserved5904;	//0xC4906044
	UINT32                                                 reserved5905;	//0xC4906048
	UINT32                                                 reserved5906;	//0xC490604C
	UINT32                                                 reserved5907;	//0xC4906050
	UINT32                                                 reserved5908;	//0xC4906054
	UINT32                                                 reserved5909;	//0xC4906058
	UINT32                                                 reserved5910;	//0xC490605C
	UINT32                                                 reserved5911;	//0xC4906060
	UINT32                                                 reserved5912;	//0xC4906064
	UINT32                                                 reserved5913;	//0xC4906068
	UINT32                                                 reserved5914;	//0xC490606C
	UINT32                                                 reserved5915;	//0xC4906070
	UINT32                                                 reserved5916;	//0xC4906074
	UINT32                                                 reserved5917;	//0xC4906078
	UINT32                                                 reserved5918;	//0xC490607C
	UINT32                                                 reserved5919;	//0xC4906080
	UINT32                                                 reserved5920;	//0xC4906084
	UINT32                                                 reserved5921;	//0xC4906088
	UINT32                                                 reserved5922;	//0xC490608C
	UINT32                                                 reserved5923;	//0xC4906090
	UINT32                                                 reserved5924;	//0xC4906094
	UINT32                                                 reserved5925;	//0xC4906098
	UINT32                                                 reserved5926;	//0xC490609C
	UINT32                                                 reserved5927;	//0xC49060A0
	UINT32                                                 reserved5928;	//0xC49060A4
	UINT32                                                 reserved5929;	//0xC49060A8
	UINT32                                                 reserved5930;	//0xC49060AC
	UINT32                                                 reserved5931;	//0xC49060B0
	UINT32                                                 reserved5932;	//0xC49060B4
	UINT32                                                 reserved5933;	//0xC49060B8
	UINT32                                                 reserved5934;	//0xC49060BC
	UINT32                                                 reserved5935;	//0xC49060C0
	UINT32                                                 reserved5936;	//0xC49060C4
	UINT32                                                 reserved5937;	//0xC49060C8
	UINT32                                                 reserved5938;	//0xC49060CC
	UINT32                                                 reserved5939;	//0xC49060D0
	UINT32                                                 reserved5940;	//0xC49060D4
	UINT32                                                 reserved5941;	//0xC49060D8
	UINT32                                                 reserved5942;	//0xC49060DC
	UINT32                                                 reserved5943;	//0xC49060E0
	UINT32                                                 reserved5944;	//0xC49060E4
	UINT32                                                 reserved5945;	//0xC49060E8
	UINT32                                                 reserved5946;	//0xC49060EC
	UINT32                                                 reserved5947;	//0xC49060F0
	UINT32                                                 reserved5948;	//0xC49060F4
	UINT32                                                 reserved5949;	//0xC49060F8
	UINT32                                                 reserved5950;	//0xC49060FC
	REG_DDRC_M1_DEBUG_LPD4_MR_0_T                       debug_lpd4_mr_0;	//0xC4906100
	REG_DDRC_M1_DEBUG_LPD4_MR_1_T                       debug_lpd4_mr_1;	//0xC4906104
	REG_DDRC_M1_DEBUG_LPD4_MR_2_T                       debug_lpd4_mr_2;	//0xC4906108
	REG_DDRC_M1_DEBUG_LPD4_MR_3_T                       debug_lpd4_mr_3;	//0xC490610C
	REG_DDRC_M1_DEBUG_LPD4_MR_4_T                       debug_lpd4_mr_4;	//0xC4906110
	REG_DDRC_M1_DEBUG_LPD4_MR_5_T                       debug_lpd4_mr_5;	//0xC4906114
	REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_0_T           debug_lpd4_mpc_fifo_0;	//0xC4906118
	REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_1_T           debug_lpd4_mpc_fifo_1;	//0xC490611C
	REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_2_T           debug_lpd4_mpc_fifo_2;	//0xC4906120
	REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_3_T           debug_lpd4_mpc_fifo_3;	//0xC4906124
	REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_4_T           debug_lpd4_mpc_fifo_4;	//0xC4906128
	REG_DDRC_M1_DEBUG_LPD4_MPC_FIFO_5_T           debug_lpd4_mpc_fifo_5;	//0xC490612C
	UINT32                                                 reserved5951;	//0xC4906130
	UINT32                                                 reserved5952;	//0xC4906134
	UINT32                                                 reserved5953;	//0xC4906138
	UINT32                                                 reserved5954;	//0xC490613C
	UINT32                                                 reserved5955;	//0xC4906140
	UINT32                                                 reserved5956;	//0xC4906144
	UINT32                                                 reserved5957;	//0xC4906148
	UINT32                                                 reserved5958;	//0xC490614C
	UINT32                                                 reserved5959;	//0xC4906150
	UINT32                                                 reserved5960;	//0xC4906154
	UINT32                                                 reserved5961;	//0xC4906158
	UINT32                                                 reserved5962;	//0xC490615C
	UINT32                                                 reserved5963;	//0xC4906160
	UINT32                                                 reserved5964;	//0xC4906164
	UINT32                                                 reserved5965;	//0xC4906168
	UINT32                                                 reserved5966;	//0xC490616C
	UINT32                                                 reserved5967;	//0xC4906170
	UINT32                                                 reserved5968;	//0xC4906174
	UINT32                                                 reserved5969;	//0xC4906178
	UINT32                                                 reserved5970;	//0xC490617C
	UINT32                                                 reserved5971;	//0xC4906180
	UINT32                                                 reserved5972;	//0xC4906184
	UINT32                                                 reserved5973;	//0xC4906188
	UINT32                                                 reserved5974;	//0xC490618C
	UINT32                                                 reserved5975;	//0xC4906190
	UINT32                                                 reserved5976;	//0xC4906194
	UINT32                                                 reserved5977;	//0xC4906198
	UINT32                                                 reserved5978;	//0xC490619C
	UINT32                                                 reserved5979;	//0xC49061A0
	UINT32                                                 reserved5980;	//0xC49061A4
	UINT32                                                 reserved5981;	//0xC49061A8
	UINT32                                                 reserved5982;	//0xC49061AC
	UINT32                                                 reserved5983;	//0xC49061B0
	UINT32                                                 reserved5984;	//0xC49061B4
	UINT32                                                 reserved5985;	//0xC49061B8
	UINT32                                                 reserved5986;	//0xC49061BC
	UINT32                                                 reserved5987;	//0xC49061C0
	UINT32                                                 reserved5988;	//0xC49061C4
	UINT32                                                 reserved5989;	//0xC49061C8
	UINT32                                                 reserved5990;	//0xC49061CC
	UINT32                                                 reserved5991;	//0xC49061D0
	UINT32                                                 reserved5992;	//0xC49061D4
	UINT32                                                 reserved5993;	//0xC49061D8
	UINT32                                                 reserved5994;	//0xC49061DC
	UINT32                                                 reserved5995;	//0xC49061E0
	UINT32                                                 reserved5996;	//0xC49061E4
	UINT32                                                 reserved5997;	//0xC49061E8
	UINT32                                                 reserved5998;	//0xC49061EC
	UINT32                                                 reserved5999;	//0xC49061F0
	UINT32                                                 reserved6000;	//0xC49061F4
	UINT32                                                 reserved6001;	//0xC49061F8
	UINT32                                                 reserved6002;	//0xC49061FC
	REG_DDRC_M1_DEBUG_CTRL_CMD_MRW1_T               debug_ctrl_cmd_mrw1;	//0xC4906200
	REG_DDRC_M1_DEBUG_CTRL_CMD_MRW0_T               debug_ctrl_cmd_mrw0;	//0xC4906204
	REG_DDRC_M1_DEBUG_CTRL_CMD_LP_EXIT_T         debug_ctrl_cmd_lp_exit;	//0xC4906208
	REG_DDRC_M1_DEBUG_CTRL_CMD_LP_ENTRY_T       debug_ctrl_cmd_lp_entry;	//0xC490620C
	REG_DDRC_M1_DEBUG_CTRL_CMD_SR_PD_EXIT_T   debug_ctrl_cmd_sr_pd_exit;	//0xC4906210
	REG_DDRC_M1_DEBUG_CTRL_CMD_SR_PD_ENTRY_T debug_ctrl_cmd_sr_pd_entry;	//0xC4906214
	REG_DDRC_M1_DEBUG_CTRL_CMD_SR_EXIT_T         debug_ctrl_cmd_sr_exit;	//0xC4906218
	REG_DDRC_M1_DEBUG_CTRL_CMD_SR_ENTRY_T       debug_ctrl_cmd_sr_entry;	//0xC490621C
	REG_DDRC_M1_DEBUG_CTRL_CMD_PD_EXIT_T         debug_ctrl_cmd_pd_exit;	//0xC4906220
	REG_DDRC_M1_DEBUG_CTRL_CMD_PD_ENTRY_T       debug_ctrl_cmd_pd_entry;	//0xC4906224
	REG_DDRC_M1_DEBUG_CTRL_CMD_ZQLAT_T             debug_ctrl_cmd_zqlat;	//0xC4906228
	REG_DDRC_M1_DEBUG_CTRL_CMD_ZQCAL_T             debug_ctrl_cmd_zqcal;	//0xC490622C
	REG_DDRC_M1_DEBUG_CTRL_CMD_CKE1_T               debug_ctrl_cmd_cke1;	//0xC4906230
	REG_DDRC_M1_DEBUG_CTRL_CMD_CKE0_T               debug_ctrl_cmd_cke0;	//0xC4906234
	REG_DDRC_M1_DEBUG_CTRL_CMD_RSTN1_T             debug_ctrl_cmd_rstn1;	//0xC4906238
	REG_DDRC_M1_DEBUG_CTRL_CMD_RSTN0_T             debug_ctrl_cmd_rstn0;	//0xC490623C
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD0_T                 debug_ctrl_cmd_rd0;	//0xC4906240
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD1_T                 debug_ctrl_cmd_rd1;	//0xC4906244
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD2_T                 debug_ctrl_cmd_rd2;	//0xC4906248
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD3_T                 debug_ctrl_cmd_rd3;	//0xC490624C
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD4_T                 debug_ctrl_cmd_rd4;	//0xC4906250
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD5_T                 debug_ctrl_cmd_rd5;	//0xC4906254
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD6_T                 debug_ctrl_cmd_rd6;	//0xC4906258
	REG_DDRC_M1_DEBUG_CTRL_CMD_RD7_T                 debug_ctrl_cmd_rd7;	//0xC490625C
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR0_T               debug_ctrl_cmd_mwr0;	//0xC4906260
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR1_T               debug_ctrl_cmd_mwr1;	//0xC4906264
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR2_T               debug_ctrl_cmd_mwr2;	//0xC4906268
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR3_T               debug_ctrl_cmd_mwr3;	//0xC490626C
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR4_T               debug_ctrl_cmd_mwr4;	//0xC4906270
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR5_T               debug_ctrl_cmd_mwr5;	//0xC4906274
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR6_T               debug_ctrl_cmd_mwr6;	//0xC4906278
	REG_DDRC_M1_DEBUG_CTRL_CMD_MWR7_T               debug_ctrl_cmd_mwr7;	//0xC490627C
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR0_T                 debug_ctrl_cmd_wr0;	//0xC4906280
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR1_T                 debug_ctrl_cmd_wr1;	//0xC4906284
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR2_T                 debug_ctrl_cmd_wr2;	//0xC4906288
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR3_T                 debug_ctrl_cmd_wr3;	//0xC490628C
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR4_T                 debug_ctrl_cmd_wr4;	//0xC4906290
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR5_T                 debug_ctrl_cmd_wr5;	//0xC4906294
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR6_T                 debug_ctrl_cmd_wr6;	//0xC4906298
	REG_DDRC_M1_DEBUG_CTRL_CMD_WR7_T                 debug_ctrl_cmd_wr7;	//0xC490629C
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT0_T               debug_ctrl_cmd_act0;	//0xC49062A0
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT1_T               debug_ctrl_cmd_act1;	//0xC49062A4
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT2_T               debug_ctrl_cmd_act2;	//0xC49062A8
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT3_T               debug_ctrl_cmd_act3;	//0xC49062AC
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT4_T               debug_ctrl_cmd_act4;	//0xC49062B0
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT5_T               debug_ctrl_cmd_act5;	//0xC49062B4
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT6_T               debug_ctrl_cmd_act6;	//0xC49062B8
	REG_DDRC_M1_DEBUG_CTRL_CMD_ACT7_T               debug_ctrl_cmd_act7;	//0xC49062BC
	UINT32                                                 reserved6003;	//0xC49062C0
	UINT32                                                 reserved6004;	//0xC49062C4
	UINT32                                                 reserved6005;	//0xC49062C8
	UINT32                                                 reserved6006;	//0xC49062CC
	UINT32                                                 reserved6007;	//0xC49062D0
	UINT32                                                 reserved6008;	//0xC49062D4
	UINT32                                                 reserved6009;	//0xC49062D8
	UINT32                                                 reserved6010;	//0xC49062DC
	UINT32                                                 reserved6011;	//0xC49062E0
	UINT32                                                 reserved6012;	//0xC49062E4
	UINT32                                                 reserved6013;	//0xC49062E8
	UINT32                                                 reserved6014;	//0xC49062EC
	UINT32                                                 reserved6015;	//0xC49062F0
	UINT32                                                 reserved6016;	//0xC49062F4
	UINT32                                                 reserved6017;	//0xC49062F8
	UINT32                                                 reserved6018;	//0xC49062FC
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB0_T         debug_ctrl_cmd_ref_pb0;	//0xC4906300
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB1_T         debug_ctrl_cmd_ref_pb1;	//0xC4906304
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB2_T         debug_ctrl_cmd_ref_pb2;	//0xC4906308
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB3_T         debug_ctrl_cmd_ref_pb3;	//0xC490630C
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB4_T         debug_ctrl_cmd_ref_pb4;	//0xC4906310
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB5_T         debug_ctrl_cmd_ref_pb5;	//0xC4906314
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB6_T         debug_ctrl_cmd_ref_pb6;	//0xC4906318
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_PB7_T         debug_ctrl_cmd_ref_pb7;	//0xC490631C
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB0_T         debug_ctrl_cmd_prg_pb0;	//0xC4906320
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB1_T         debug_ctrl_cmd_prg_pb1;	//0xC4906324
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB2_T         debug_ctrl_cmd_prg_pb2;	//0xC4906328
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB3_T         debug_ctrl_cmd_prg_pb3;	//0xC490632C
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB4_T         debug_ctrl_cmd_prg_pb4;	//0xC4906330
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB5_T         debug_ctrl_cmd_prg_pb5;	//0xC4906334
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB6_T         debug_ctrl_cmd_prg_pb6;	//0xC4906338
	REG_DDRC_M1_DEBUG_CTRL_CMD_PRG_PB7_T         debug_ctrl_cmd_prg_pb7;	//0xC490633C
	REG_DDRC_M1_DEBUG_CTRL_CMD_CG_REF_AB_T     debug_ctrl_cmd_cg_ref_ab;	//0xC4906340
	REG_DDRC_M1_DEBUG_CTRL_CMD_MF_REF_AB_T     debug_ctrl_cmd_mf_ref_ab;	//0xC4906344
	UINT32                                                 reserved6019;	//0xC4906348
	UINT32                                                 reserved6020;	//0xC490634C
	REG_DDRC_M1_DEBUG_CTRL_CMD_CG_PRG_AB_T     debug_ctrl_cmd_cg_prg_ab;	//0xC4906350
	REG_DDRC_M1_DEBUG_CTRL_CMD_MF_PRG_AB_T     debug_ctrl_cmd_mf_prg_ab;	//0xC4906354
	UINT32                                                 reserved6021;	//0xC4906358
	UINT32                                                 reserved6022;	//0xC490635C
	REG_DDRC_M1_DEBUG_CTRL_CMD_CG_BL_T             debug_ctrl_cmd_cg_bl;	//0xC4906360
	REG_DDRC_M1_DEBUG_CTRL_CMD_CG_AP_T             debug_ctrl_cmd_cg_ap;	//0xC4906364
	REG_DDRC_M1_DEBUG_CTRL_CMD_REF_CYCLE_T     debug_ctrl_cmd_ref_cycle;	//0xC4906368
	UINT32                                                 reserved6023;	//0xC490636C
	UINT32                                                 reserved6024;	//0xC4906370
	UINT32                                                 reserved6025;	//0xC4906374
	UINT32                                                 reserved6026;	//0xC4906378
	UINT32                                                 reserved6027;	//0xC490637C
	UINT32                                                 reserved6028;	//0xC4906380
	UINT32                                                 reserved6029;	//0xC4906384
	UINT32                                                 reserved6030;	//0xC4906388
	UINT32                                                 reserved6031;	//0xC490638C
	UINT32                                                 reserved6032;	//0xC4906390
	UINT32                                                 reserved6033;	//0xC4906394
	UINT32                                                 reserved6034;	//0xC4906398
	UINT32                                                 reserved6035;	//0xC490639C
	UINT32                                                 reserved6036;	//0xC49063A0
	UINT32                                                 reserved6037;	//0xC49063A4
	UINT32                                                 reserved6038;	//0xC49063A8
	UINT32                                                 reserved6039;	//0xC49063AC
	UINT32                                                 reserved6040;	//0xC49063B0
	UINT32                                                 reserved6041;	//0xC49063B4
	UINT32                                                 reserved6042;	//0xC49063B8
	UINT32                                                 reserved6043;	//0xC49063BC
	UINT32                                                 reserved6044;	//0xC49063C0
	UINT32                                                 reserved6045;	//0xC49063C4
	UINT32                                                 reserved6046;	//0xC49063C8
	UINT32                                                 reserved6047;	//0xC49063CC
	UINT32                                                 reserved6048;	//0xC49063D0
	UINT32                                                 reserved6049;	//0xC49063D4
	UINT32                                                 reserved6050;	//0xC49063D8
	UINT32                                                 reserved6051;	//0xC49063DC
	UINT32                                                 reserved6052;	//0xC49063E0
	UINT32                                                 reserved6053;	//0xC49063E4
	UINT32                                                 reserved6054;	//0xC49063E8
	UINT32                                                 reserved6055;	//0xC49063EC
	UINT32                                                 reserved6056;	//0xC49063F0
	UINT32                                                 reserved6057;	//0xC49063F4
	UINT32                                                 reserved6058;	//0xC49063F8
	UINT32                                                 reserved6059;	//0xC49063FC
	UINT32                                                 reserved6060;	//0xC4906400
	UINT32                                                 reserved6061;	//0xC4906404
	UINT32                                                 reserved6062;	//0xC4906408
	UINT32                                                 reserved6063;	//0xC490640C
	UINT32                                                 reserved6064;	//0xC4906410
	UINT32                                                 reserved6065;	//0xC4906414
	UINT32                                                 reserved6066;	//0xC4906418
	UINT32                                                 reserved6067;	//0xC490641C
	UINT32                                                 reserved6068;	//0xC4906420
	UINT32                                                 reserved6069;	//0xC4906424
	UINT32                                                 reserved6070;	//0xC4906428
	UINT32                                                 reserved6071;	//0xC490642C
	UINT32                                                 reserved6072;	//0xC4906430
	UINT32                                                 reserved6073;	//0xC4906434
	UINT32                                                 reserved6074;	//0xC4906438
	UINT32                                                 reserved6075;	//0xC490643C
	UINT32                                                 reserved6076;	//0xC4906440
	UINT32                                                 reserved6077;	//0xC4906444
	UINT32                                                 reserved6078;	//0xC4906448
	UINT32                                                 reserved6079;	//0xC490644C
	UINT32                                                 reserved6080;	//0xC4906450
	UINT32                                                 reserved6081;	//0xC4906454
	UINT32                                                 reserved6082;	//0xC4906458
	UINT32                                                 reserved6083;	//0xC490645C
	UINT32                                                 reserved6084;	//0xC4906460
	UINT32                                                 reserved6085;	//0xC4906464
	UINT32                                                 reserved6086;	//0xC4906468
	UINT32                                                 reserved6087;	//0xC490646C
	UINT32                                                 reserved6088;	//0xC4906470
	UINT32                                                 reserved6089;	//0xC4906474
	UINT32                                                 reserved6090;	//0xC4906478
	UINT32                                                 reserved6091;	//0xC490647C
	UINT32                                                 reserved6092;	//0xC4906480
	UINT32                                                 reserved6093;	//0xC4906484
	UINT32                                                 reserved6094;	//0xC4906488
	UINT32                                                 reserved6095;	//0xC490648C
	UINT32                                                 reserved6096;	//0xC4906490
	UINT32                                                 reserved6097;	//0xC4906494
	UINT32                                                 reserved6098;	//0xC4906498
	UINT32                                                 reserved6099;	//0xC490649C
	UINT32                                                 reserved6100;	//0xC49064A0
	UINT32                                                 reserved6101;	//0xC49064A4
	UINT32                                                 reserved6102;	//0xC49064A8
	UINT32                                                 reserved6103;	//0xC49064AC
	UINT32                                                 reserved6104;	//0xC49064B0
	UINT32                                                 reserved6105;	//0xC49064B4
	UINT32                                                 reserved6106;	//0xC49064B8
	UINT32                                                 reserved6107;	//0xC49064BC
	UINT32                                                 reserved6108;	//0xC49064C0
	UINT32                                                 reserved6109;	//0xC49064C4
	UINT32                                                 reserved6110;	//0xC49064C8
	UINT32                                                 reserved6111;	//0xC49064CC
	UINT32                                                 reserved6112;	//0xC49064D0
	UINT32                                                 reserved6113;	//0xC49064D4
	UINT32                                                 reserved6114;	//0xC49064D8
	UINT32                                                 reserved6115;	//0xC49064DC
	UINT32                                                 reserved6116;	//0xC49064E0
	UINT32                                                 reserved6117;	//0xC49064E4
	UINT32                                                 reserved6118;	//0xC49064E8
	UINT32                                                 reserved6119;	//0xC49064EC
	UINT32                                                 reserved6120;	//0xC49064F0
	UINT32                                                 reserved6121;	//0xC49064F4
	UINT32                                                 reserved6122;	//0xC49064F8
	UINT32                                                 reserved6123;	//0xC49064FC
	UINT32                                                 reserved6124;	//0xC4906500
	UINT32                                                 reserved6125;	//0xC4906504
	UINT32                                                 reserved6126;	//0xC4906508
	UINT32                                                 reserved6127;	//0xC490650C
	UINT32                                                 reserved6128;	//0xC4906510
	UINT32                                                 reserved6129;	//0xC4906514
	UINT32                                                 reserved6130;	//0xC4906518
	UINT32                                                 reserved6131;	//0xC490651C
	UINT32                                                 reserved6132;	//0xC4906520
	UINT32                                                 reserved6133;	//0xC4906524
	UINT32                                                 reserved6134;	//0xC4906528
	UINT32                                                 reserved6135;	//0xC490652C
	UINT32                                                 reserved6136;	//0xC4906530
	UINT32                                                 reserved6137;	//0xC4906534
	UINT32                                                 reserved6138;	//0xC4906538
	UINT32                                                 reserved6139;	//0xC490653C
	UINT32                                                 reserved6140;	//0xC4906540
	UINT32                                                 reserved6141;	//0xC4906544
	UINT32                                                 reserved6142;	//0xC4906548
	UINT32                                                 reserved6143;	//0xC490654C
	UINT32                                                 reserved6144;	//0xC4906550
	UINT32                                                 reserved6145;	//0xC4906554
	UINT32                                                 reserved6146;	//0xC4906558
	UINT32                                                 reserved6147;	//0xC490655C
	UINT32                                                 reserved6148;	//0xC4906560
	UINT32                                                 reserved6149;	//0xC4906564
	UINT32                                                 reserved6150;	//0xC4906568
	UINT32                                                 reserved6151;	//0xC490656C
	UINT32                                                 reserved6152;	//0xC4906570
	UINT32                                                 reserved6153;	//0xC4906574
	UINT32                                                 reserved6154;	//0xC4906578
	UINT32                                                 reserved6155;	//0xC490657C
	UINT32                                                 reserved6156;	//0xC4906580
	UINT32                                                 reserved6157;	//0xC4906584
	UINT32                                                 reserved6158;	//0xC4906588
	UINT32                                                 reserved6159;	//0xC490658C
	UINT32                                                 reserved6160;	//0xC4906590
	UINT32                                                 reserved6161;	//0xC4906594
	UINT32                                                 reserved6162;	//0xC4906598
	UINT32                                                 reserved6163;	//0xC490659C
	UINT32                                                 reserved6164;	//0xC49065A0
	UINT32                                                 reserved6165;	//0xC49065A4
	UINT32                                                 reserved6166;	//0xC49065A8
	UINT32                                                 reserved6167;	//0xC49065AC
	UINT32                                                 reserved6168;	//0xC49065B0
	UINT32                                                 reserved6169;	//0xC49065B4
	UINT32                                                 reserved6170;	//0xC49065B8
	UINT32                                                 reserved6171;	//0xC49065BC
	UINT32                                                 reserved6172;	//0xC49065C0
	UINT32                                                 reserved6173;	//0xC49065C4
	UINT32                                                 reserved6174;	//0xC49065C8
	UINT32                                                 reserved6175;	//0xC49065CC
	UINT32                                                 reserved6176;	//0xC49065D0
	UINT32                                                 reserved6177;	//0xC49065D4
	UINT32                                                 reserved6178;	//0xC49065D8
	UINT32                                                 reserved6179;	//0xC49065DC
	UINT32                                                 reserved6180;	//0xC49065E0
	UINT32                                                 reserved6181;	//0xC49065E4
	UINT32                                                 reserved6182;	//0xC49065E8
	UINT32                                                 reserved6183;	//0xC49065EC
	UINT32                                                 reserved6184;	//0xC49065F0
	UINT32                                                 reserved6185;	//0xC49065F4
	UINT32                                                 reserved6186;	//0xC49065F8
	UINT32                                                 reserved6187;	//0xC49065FC
	UINT32                                                 reserved6188;	//0xC4906600
	UINT32                                                 reserved6189;	//0xC4906604
	UINT32                                                 reserved6190;	//0xC4906608
	UINT32                                                 reserved6191;	//0xC490660C
	UINT32                                                 reserved6192;	//0xC4906610
	UINT32                                                 reserved6193;	//0xC4906614
	UINT32                                                 reserved6194;	//0xC4906618
	UINT32                                                 reserved6195;	//0xC490661C
	UINT32                                                 reserved6196;	//0xC4906620
	UINT32                                                 reserved6197;	//0xC4906624
	UINT32                                                 reserved6198;	//0xC4906628
	UINT32                                                 reserved6199;	//0xC490662C
	UINT32                                                 reserved6200;	//0xC4906630
	UINT32                                                 reserved6201;	//0xC4906634
	UINT32                                                 reserved6202;	//0xC4906638
	UINT32                                                 reserved6203;	//0xC490663C
	UINT32                                                 reserved6204;	//0xC4906640
	UINT32                                                 reserved6205;	//0xC4906644
	UINT32                                                 reserved6206;	//0xC4906648
	UINT32                                                 reserved6207;	//0xC490664C
	UINT32                                                 reserved6208;	//0xC4906650
	UINT32                                                 reserved6209;	//0xC4906654
	UINT32                                                 reserved6210;	//0xC4906658
	UINT32                                                 reserved6211;	//0xC490665C
	UINT32                                                 reserved6212;	//0xC4906660
	UINT32                                                 reserved6213;	//0xC4906664
	UINT32                                                 reserved6214;	//0xC4906668
	UINT32                                                 reserved6215;	//0xC490666C
	UINT32                                                 reserved6216;	//0xC4906670
	UINT32                                                 reserved6217;	//0xC4906674
	UINT32                                                 reserved6218;	//0xC4906678
	UINT32                                                 reserved6219;	//0xC490667C
	UINT32                                                 reserved6220;	//0xC4906680
	UINT32                                                 reserved6221;	//0xC4906684
	UINT32                                                 reserved6222;	//0xC4906688
	UINT32                                                 reserved6223;	//0xC490668C
	UINT32                                                 reserved6224;	//0xC4906690
	UINT32                                                 reserved6225;	//0xC4906694
	UINT32                                                 reserved6226;	//0xC4906698
	UINT32                                                 reserved6227;	//0xC490669C
	UINT32                                                 reserved6228;	//0xC49066A0
	UINT32                                                 reserved6229;	//0xC49066A4
	UINT32                                                 reserved6230;	//0xC49066A8
	UINT32                                                 reserved6231;	//0xC49066AC
	UINT32                                                 reserved6232;	//0xC49066B0
	UINT32                                                 reserved6233;	//0xC49066B4
	UINT32                                                 reserved6234;	//0xC49066B8
	UINT32                                                 reserved6235;	//0xC49066BC
	UINT32                                                 reserved6236;	//0xC49066C0
	UINT32                                                 reserved6237;	//0xC49066C4
	UINT32                                                 reserved6238;	//0xC49066C8
	UINT32                                                 reserved6239;	//0xC49066CC
	UINT32                                                 reserved6240;	//0xC49066D0
	UINT32                                                 reserved6241;	//0xC49066D4
	UINT32                                                 reserved6242;	//0xC49066D8
	UINT32                                                 reserved6243;	//0xC49066DC
	UINT32                                                 reserved6244;	//0xC49066E0
	UINT32                                                 reserved6245;	//0xC49066E4
	UINT32                                                 reserved6246;	//0xC49066E8
	UINT32                                                 reserved6247;	//0xC49066EC
	UINT32                                                 reserved6248;	//0xC49066F0
	UINT32                                                 reserved6249;	//0xC49066F4
	UINT32                                                 reserved6250;	//0xC49066F8
	UINT32                                                 reserved6251;	//0xC49066FC
	REG_DDRC_M1_DEBUG_DFI_T                                   debug_dfi;	//0xC4906700
	UINT32                                                 reserved6252;	//0xC4906704
	UINT32                                                 reserved6253;	//0xC4906708
	UINT32                                                 reserved6254;	//0xC490670C
	UINT32                                                 reserved6255;	//0xC4906710
	UINT32                                                 reserved6256;	//0xC4906714
	UINT32                                                 reserved6257;	//0xC4906718
	UINT32                                                 reserved6258;	//0xC490671C
	UINT32                                                 reserved6259;	//0xC4906720
	UINT32                                                 reserved6260;	//0xC4906724
	UINT32                                                 reserved6261;	//0xC4906728
	UINT32                                                 reserved6262;	//0xC490672C
	UINT32                                                 reserved6263;	//0xC4906730
	UINT32                                                 reserved6264;	//0xC4906734
	UINT32                                                 reserved6265;	//0xC4906738
	UINT32                                                 reserved6266;	//0xC490673C
	UINT32                                                 reserved6267;	//0xC4906740
	UINT32                                                 reserved6268;	//0xC4906744
	UINT32                                                 reserved6269;	//0xC4906748
	UINT32                                                 reserved6270;	//0xC490674C
	UINT32                                                 reserved6271;	//0xC4906750
	UINT32                                                 reserved6272;	//0xC4906754
	UINT32                                                 reserved6273;	//0xC4906758
	UINT32                                                 reserved6274;	//0xC490675C
	UINT32                                                 reserved6275;	//0xC4906760
	UINT32                                                 reserved6276;	//0xC4906764
	UINT32                                                 reserved6277;	//0xC4906768
	UINT32                                                 reserved6278;	//0xC490676C
	UINT32                                                 reserved6279;	//0xC4906770
	UINT32                                                 reserved6280;	//0xC4906774
	UINT32                                                 reserved6281;	//0xC4906778
	UINT32                                                 reserved6282;	//0xC490677C
	UINT32                                                 reserved6283;	//0xC4906780
	UINT32                                                 reserved6284;	//0xC4906784
	UINT32                                                 reserved6285;	//0xC4906788
	UINT32                                                 reserved6286;	//0xC490678C
	UINT32                                                 reserved6287;	//0xC4906790
	UINT32                                                 reserved6288;	//0xC4906794
	UINT32                                                 reserved6289;	//0xC4906798
	UINT32                                                 reserved6290;	//0xC490679C
	UINT32                                                 reserved6291;	//0xC49067A0
	UINT32                                                 reserved6292;	//0xC49067A4
	UINT32                                                 reserved6293;	//0xC49067A8
	UINT32                                                 reserved6294;	//0xC49067AC
	UINT32                                                 reserved6295;	//0xC49067B0
	UINT32                                                 reserved6296;	//0xC49067B4
	UINT32                                                 reserved6297;	//0xC49067B8
	UINT32                                                 reserved6298;	//0xC49067BC
	UINT32                                                 reserved6299;	//0xC49067C0
	UINT32                                                 reserved6300;	//0xC49067C4
	UINT32                                                 reserved6301;	//0xC49067C8
	UINT32                                                 reserved6302;	//0xC49067CC
	UINT32                                                 reserved6303;	//0xC49067D0
	UINT32                                                 reserved6304;	//0xC49067D4
	UINT32                                                 reserved6305;	//0xC49067D8
	UINT32                                                 reserved6306;	//0xC49067DC
	UINT32                                                 reserved6307;	//0xC49067E0
	UINT32                                                 reserved6308;	//0xC49067E4
	UINT32                                                 reserved6309;	//0xC49067E8
	UINT32                                                 reserved6310;	//0xC49067EC
	UINT32                                                 reserved6311;	//0xC49067F0
	UINT32                                                 reserved6312;	//0xC49067F4
	UINT32                                                 reserved6313;	//0xC49067F8
	UINT32                                                 reserved6314;	//0xC49067FC
	REG_DDRC_M1_DRAM_BIST_CTRL_0_T                     dram_bist_ctrl_0;	//0xC4906800
	REG_DDRC_M1_DRAM_BIST_CTRL_1_T                     dram_bist_ctrl_1;	//0xC4906804
	REG_DDRC_M1_DRAM_BIST_CTRL_2_T                     dram_bist_ctrl_2;	//0xC4906808
	REG_DDRC_M1_DRAM_BIST_DATA_0_T                     dram_bist_data_0;	//0xC490680C
	REG_DDRC_M1_DRAM_BIST_DATA_1_T                     dram_bist_data_1;	//0xC4906810
	REG_DDRC_M1_DRAM_BIST_DATA_2_T                     dram_bist_data_2;	//0xC4906814
	REG_DDRC_M1_DRAM_BIST_ADDR_0_T                     dram_bist_addr_0;	//0xC4906818
	REG_DDRC_M1_DRAM_BIST_ADDR_1_T                     dram_bist_addr_1;	//0xC490681C
	REG_DDRC_M1_DRAM_BIST_ADDR_2_T                     dram_bist_addr_2;	//0xC4906820
	REG_DDRC_M1_DRAM_BIST_OPCMD_0_T                   dram_bist_opcmd_0;	//0xC4906824
	REG_DDRC_M1_DRAM_BIST_OPCMD_1_T                   dram_bist_opcmd_1;	//0xC4906828
	REG_DDRC_M1_DRAM_BIST_OPCMD_2_T                   dram_bist_opcmd_2;	//0xC490682C
	REG_DDRC_M1_DRAM_BIST_OPCMD_3_T                   dram_bist_opcmd_3;	//0xC4906830
	REG_DDRC_M1_DRAM_BIST_ERR_ADDR_INFO_T       dram_bist_err_addr_info;	//0xC4906834
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_00_T dram_bist_err_data_info_00;	//0xC4906838
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_01_T dram_bist_err_data_info_01;	//0xC490683C
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_02_T dram_bist_err_data_info_02;	//0xC4906840
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_03_T dram_bist_err_data_info_03;	//0xC4906844
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_04_T dram_bist_err_data_info_04;	//0xC4906848
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_05_T dram_bist_err_data_info_05;	//0xC490684C
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_06_T dram_bist_err_data_info_06;	//0xC4906850
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_07_T dram_bist_err_data_info_07;	//0xC4906854
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_08_T dram_bist_err_data_info_08;	//0xC4906858
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_09_T dram_bist_err_data_info_09;	//0xC490685C
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_10_T dram_bist_err_data_info_10;	//0xC4906860
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_11_T dram_bist_err_data_info_11;	//0xC4906864
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_12_T dram_bist_err_data_info_12;	//0xC4906868
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_13_T dram_bist_err_data_info_13;	//0xC490686C
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_14_T dram_bist_err_data_info_14;	//0xC4906870
	REG_DDRC_M1_DRAM_BIST_ERR_DATA_INFO_15_T dram_bist_err_data_info_15;	//0xC4906874
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_00_T dram_bist_exp_data_info_00;	//0xC4906878
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_01_T dram_bist_exp_data_info_01;	//0xC490687C
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_02_T dram_bist_exp_data_info_02;	//0xC4906880
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_03_T dram_bist_exp_data_info_03;	//0xC4906884
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_04_T dram_bist_exp_data_info_04;	//0xC4906888
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_05_T dram_bist_exp_data_info_05;	//0xC490688C
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_06_T dram_bist_exp_data_info_06;	//0xC4906890
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_07_T dram_bist_exp_data_info_07;	//0xC4906894
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_08_T dram_bist_exp_data_info_08;	//0xC4906898
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_09_T dram_bist_exp_data_info_09;	//0xC490689C
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_10_T dram_bist_exp_data_info_10;	//0xC49068A0
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_11_T dram_bist_exp_data_info_11;	//0xC49068A4
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_12_T dram_bist_exp_data_info_12;	//0xC49068A8
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_13_T dram_bist_exp_data_info_13;	//0xC49068AC
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_14_T dram_bist_exp_data_info_14;	//0xC49068B0
	REG_DDRC_M1_DRAM_BIST_EXP_DATA_INFO_15_T dram_bist_exp_data_info_15;	//0xC49068B4
	UINT32                                                 reserved6315;	//0xC49068B8
	UINT32                                                 reserved6316;	//0xC49068BC
	UINT32                                                 reserved6317;	//0xC49068C0
	UINT32                                                 reserved6318;	//0xC49068C4
	UINT32                                                 reserved6319;	//0xC49068C8
	UINT32                                                 reserved6320;	//0xC49068CC
	UINT32                                                 reserved6321;	//0xC49068D0
	UINT32                                                 reserved6322;	//0xC49068D4
	UINT32                                                 reserved6323;	//0xC49068D8
	UINT32                                                 reserved6324;	//0xC49068DC
	UINT32                                                 reserved6325;	//0xC49068E0
	UINT32                                                 reserved6326;	//0xC49068E4
	UINT32                                                 reserved6327;	//0xC49068E8
	UINT32                                                 reserved6328;	//0xC49068EC
	UINT32                                                 reserved6329;	//0xC49068F0
	UINT32                                                 reserved6330;	//0xC49068F4
	UINT32                                                 reserved6331;	//0xC49068F8
	UINT32                                                 reserved6332;	//0xC49068FC
	UINT32                                                 reserved6333;	//0xC4906900
	UINT32                                                 reserved6334;	//0xC4906904
	UINT32                                                 reserved6335;	//0xC4906908
	UINT32                                                 reserved6336;	//0xC490690C
	UINT32                                                 reserved6337;	//0xC4906910
	UINT32                                                 reserved6338;	//0xC4906914
	UINT32                                                 reserved6339;	//0xC4906918
	UINT32                                                 reserved6340;	//0xC490691C
	UINT32                                                 reserved6341;	//0xC4906920
	UINT32                                                 reserved6342;	//0xC4906924
	UINT32                                                 reserved6343;	//0xC4906928
	UINT32                                                 reserved6344;	//0xC490692C
	UINT32                                                 reserved6345;	//0xC4906930
	UINT32                                                 reserved6346;	//0xC4906934
	UINT32                                                 reserved6347;	//0xC4906938
	UINT32                                                 reserved6348;	//0xC490693C
	UINT32                                                 reserved6349;	//0xC4906940
	UINT32                                                 reserved6350;	//0xC4906944
	UINT32                                                 reserved6351;	//0xC4906948
	UINT32                                                 reserved6352;	//0xC490694C
	UINT32                                                 reserved6353;	//0xC4906950
	UINT32                                                 reserved6354;	//0xC4906954
	UINT32                                                 reserved6355;	//0xC4906958
	UINT32                                                 reserved6356;	//0xC490695C
	UINT32                                                 reserved6357;	//0xC4906960
	UINT32                                                 reserved6358;	//0xC4906964
	UINT32                                                 reserved6359;	//0xC4906968
	UINT32                                                 reserved6360;	//0xC490696C
	UINT32                                                 reserved6361;	//0xC4906970
	UINT32                                                 reserved6362;	//0xC4906974
	UINT32                                                 reserved6363;	//0xC4906978
	UINT32                                                 reserved6364;	//0xC490697C
	UINT32                                                 reserved6365;	//0xC4906980
	UINT32                                                 reserved6366;	//0xC4906984
	UINT32                                                 reserved6367;	//0xC4906988
	UINT32                                                 reserved6368;	//0xC490698C
	UINT32                                                 reserved6369;	//0xC4906990
	UINT32                                                 reserved6370;	//0xC4906994
	UINT32                                                 reserved6371;	//0xC4906998
	UINT32                                                 reserved6372;	//0xC490699C
	UINT32                                                 reserved6373;	//0xC49069A0
	UINT32                                                 reserved6374;	//0xC49069A4
	UINT32                                                 reserved6375;	//0xC49069A8
	UINT32                                                 reserved6376;	//0xC49069AC
	UINT32                                                 reserved6377;	//0xC49069B0
	UINT32                                                 reserved6378;	//0xC49069B4
	UINT32                                                 reserved6379;	//0xC49069B8
	UINT32                                                 reserved6380;	//0xC49069BC
	UINT32                                                 reserved6381;	//0xC49069C0
	UINT32                                                 reserved6382;	//0xC49069C4
	UINT32                                                 reserved6383;	//0xC49069C8
	UINT32                                                 reserved6384;	//0xC49069CC
	UINT32                                                 reserved6385;	//0xC49069D0
	UINT32                                                 reserved6386;	//0xC49069D4
	UINT32                                                 reserved6387;	//0xC49069D8
	UINT32                                                 reserved6388;	//0xC49069DC
	UINT32                                                 reserved6389;	//0xC49069E0
	UINT32                                                 reserved6390;	//0xC49069E4
	UINT32                                                 reserved6391;	//0xC49069E8
	UINT32                                                 reserved6392;	//0xC49069EC
	UINT32                                                 reserved6393;	//0xC49069F0
	UINT32                                                 reserved6394;	//0xC49069F4
	UINT32                                                 reserved6395;	//0xC49069F8
	UINT32                                                 reserved6396;	//0xC49069FC
	UINT32                                                 reserved6397;	//0xC4906A00
	UINT32                                                 reserved6398;	//0xC4906A04
	UINT32                                                 reserved6399;	//0xC4906A08
	UINT32                                                 reserved6400;	//0xC4906A0C
	UINT32                                                 reserved6401;	//0xC4906A10
	UINT32                                                 reserved6402;	//0xC4906A14
	UINT32                                                 reserved6403;	//0xC4906A18
	UINT32                                                 reserved6404;	//0xC4906A1C
	UINT32                                                 reserved6405;	//0xC4906A20
	UINT32                                                 reserved6406;	//0xC4906A24
	UINT32                                                 reserved6407;	//0xC4906A28
	UINT32                                                 reserved6408;	//0xC4906A2C
	UINT32                                                 reserved6409;	//0xC4906A30
	UINT32                                                 reserved6410;	//0xC4906A34
	UINT32                                                 reserved6411;	//0xC4906A38
	UINT32                                                 reserved6412;	//0xC4906A3C
	UINT32                                                 reserved6413;	//0xC4906A40
	UINT32                                                 reserved6414;	//0xC4906A44
	UINT32                                                 reserved6415;	//0xC4906A48
	UINT32                                                 reserved6416;	//0xC4906A4C
	UINT32                                                 reserved6417;	//0xC4906A50
	UINT32                                                 reserved6418;	//0xC4906A54
	UINT32                                                 reserved6419;	//0xC4906A58
	UINT32                                                 reserved6420;	//0xC4906A5C
	UINT32                                                 reserved6421;	//0xC4906A60
	UINT32                                                 reserved6422;	//0xC4906A64
	UINT32                                                 reserved6423;	//0xC4906A68
	UINT32                                                 reserved6424;	//0xC4906A6C
	UINT32                                                 reserved6425;	//0xC4906A70
	UINT32                                                 reserved6426;	//0xC4906A74
	UINT32                                                 reserved6427;	//0xC4906A78
	UINT32                                                 reserved6428;	//0xC4906A7C
	UINT32                                                 reserved6429;	//0xC4906A80
	UINT32                                                 reserved6430;	//0xC4906A84
	UINT32                                                 reserved6431;	//0xC4906A88
	UINT32                                                 reserved6432;	//0xC4906A8C
	UINT32                                                 reserved6433;	//0xC4906A90
	UINT32                                                 reserved6434;	//0xC4906A94
	UINT32                                                 reserved6435;	//0xC4906A98
	UINT32                                                 reserved6436;	//0xC4906A9C
	UINT32                                                 reserved6437;	//0xC4906AA0
	UINT32                                                 reserved6438;	//0xC4906AA4
	UINT32                                                 reserved6439;	//0xC4906AA8
	UINT32                                                 reserved6440;	//0xC4906AAC
	UINT32                                                 reserved6441;	//0xC4906AB0
	UINT32                                                 reserved6442;	//0xC4906AB4
	UINT32                                                 reserved6443;	//0xC4906AB8
	UINT32                                                 reserved6444;	//0xC4906ABC
	UINT32                                                 reserved6445;	//0xC4906AC0
	UINT32                                                 reserved6446;	//0xC4906AC4
	UINT32                                                 reserved6447;	//0xC4906AC8
	UINT32                                                 reserved6448;	//0xC4906ACC
	UINT32                                                 reserved6449;	//0xC4906AD0
	UINT32                                                 reserved6450;	//0xC4906AD4
	UINT32                                                 reserved6451;	//0xC4906AD8
	UINT32                                                 reserved6452;	//0xC4906ADC
	UINT32                                                 reserved6453;	//0xC4906AE0
	UINT32                                                 reserved6454;	//0xC4906AE4
	UINT32                                                 reserved6455;	//0xC4906AE8
	UINT32                                                 reserved6456;	//0xC4906AEC
	UINT32                                                 reserved6457;	//0xC4906AF0
	UINT32                                                 reserved6458;	//0xC4906AF4
	UINT32                                                 reserved6459;	//0xC4906AF8
	UINT32                                                 reserved6460;	//0xC4906AFC
	UINT32                                                 reserved6461;	//0xC4906B00
	UINT32                                                 reserved6462;	//0xC4906B04
	UINT32                                                 reserved6463;	//0xC4906B08
	UINT32                                                 reserved6464;	//0xC4906B0C
	UINT32                                                 reserved6465;	//0xC4906B10
	UINT32                                                 reserved6466;	//0xC4906B14
	UINT32                                                 reserved6467;	//0xC4906B18
	UINT32                                                 reserved6468;	//0xC4906B1C
	UINT32                                                 reserved6469;	//0xC4906B20
	UINT32                                                 reserved6470;	//0xC4906B24
	UINT32                                                 reserved6471;	//0xC4906B28
	UINT32                                                 reserved6472;	//0xC4906B2C
	UINT32                                                 reserved6473;	//0xC4906B30
	UINT32                                                 reserved6474;	//0xC4906B34
	UINT32                                                 reserved6475;	//0xC4906B38
	UINT32                                                 reserved6476;	//0xC4906B3C
	UINT32                                                 reserved6477;	//0xC4906B40
	UINT32                                                 reserved6478;	//0xC4906B44
	UINT32                                                 reserved6479;	//0xC4906B48
	UINT32                                                 reserved6480;	//0xC4906B4C
	UINT32                                                 reserved6481;	//0xC4906B50
	UINT32                                                 reserved6482;	//0xC4906B54
	UINT32                                                 reserved6483;	//0xC4906B58
	UINT32                                                 reserved6484;	//0xC4906B5C
	UINT32                                                 reserved6485;	//0xC4906B60
	UINT32                                                 reserved6486;	//0xC4906B64
	UINT32                                                 reserved6487;	//0xC4906B68
	UINT32                                                 reserved6488;	//0xC4906B6C
	UINT32                                                 reserved6489;	//0xC4906B70
	UINT32                                                 reserved6490;	//0xC4906B74
	UINT32                                                 reserved6491;	//0xC4906B78
	UINT32                                                 reserved6492;	//0xC4906B7C
	UINT32                                                 reserved6493;	//0xC4906B80
	UINT32                                                 reserved6494;	//0xC4906B84
	UINT32                                                 reserved6495;	//0xC4906B88
	UINT32                                                 reserved6496;	//0xC4906B8C
	UINT32                                                 reserved6497;	//0xC4906B90
	UINT32                                                 reserved6498;	//0xC4906B94
	UINT32                                                 reserved6499;	//0xC4906B98
	UINT32                                                 reserved6500;	//0xC4906B9C
	UINT32                                                 reserved6501;	//0xC4906BA0
	UINT32                                                 reserved6502;	//0xC4906BA4
	UINT32                                                 reserved6503;	//0xC4906BA8
	UINT32                                                 reserved6504;	//0xC4906BAC
	UINT32                                                 reserved6505;	//0xC4906BB0
	UINT32                                                 reserved6506;	//0xC4906BB4
	UINT32                                                 reserved6507;	//0xC4906BB8
	UINT32                                                 reserved6508;	//0xC4906BBC
	UINT32                                                 reserved6509;	//0xC4906BC0
	UINT32                                                 reserved6510;	//0xC4906BC4
	UINT32                                                 reserved6511;	//0xC4906BC8
	UINT32                                                 reserved6512;	//0xC4906BCC
	UINT32                                                 reserved6513;	//0xC4906BD0
	UINT32                                                 reserved6514;	//0xC4906BD4
	UINT32                                                 reserved6515;	//0xC4906BD8
	UINT32                                                 reserved6516;	//0xC4906BDC
	UINT32                                                 reserved6517;	//0xC4906BE0
	UINT32                                                 reserved6518;	//0xC4906BE4
	UINT32                                                 reserved6519;	//0xC4906BE8
	UINT32                                                 reserved6520;	//0xC4906BEC
	UINT32                                                 reserved6521;	//0xC4906BF0
	UINT32                                                 reserved6522;	//0xC4906BF4
	UINT32                                                 reserved6523;	//0xC4906BF8
	UINT32                                                 reserved6524;	//0xC4906BFC
	UINT32                                                 reserved6525;	//0xC4906C00
	UINT32                                                 reserved6526;	//0xC4906C04
	UINT32                                                 reserved6527;	//0xC4906C08
	UINT32                                                 reserved6528;	//0xC4906C0C
	UINT32                                                 reserved6529;	//0xC4906C10
	UINT32                                                 reserved6530;	//0xC4906C14
	UINT32                                                 reserved6531;	//0xC4906C18
	UINT32                                                 reserved6532;	//0xC4906C1C
	UINT32                                                 reserved6533;	//0xC4906C20
	UINT32                                                 reserved6534;	//0xC4906C24
	UINT32                                                 reserved6535;	//0xC4906C28
	UINT32                                                 reserved6536;	//0xC4906C2C
	UINT32                                                 reserved6537;	//0xC4906C30
	UINT32                                                 reserved6538;	//0xC4906C34
	UINT32                                                 reserved6539;	//0xC4906C38
	UINT32                                                 reserved6540;	//0xC4906C3C
	UINT32                                                 reserved6541;	//0xC4906C40
	UINT32                                                 reserved6542;	//0xC4906C44
	UINT32                                                 reserved6543;	//0xC4906C48
	UINT32                                                 reserved6544;	//0xC4906C4C
	UINT32                                                 reserved6545;	//0xC4906C50
	UINT32                                                 reserved6546;	//0xC4906C54
	UINT32                                                 reserved6547;	//0xC4906C58
	UINT32                                                 reserved6548;	//0xC4906C5C
	UINT32                                                 reserved6549;	//0xC4906C60
	UINT32                                                 reserved6550;	//0xC4906C64
	UINT32                                                 reserved6551;	//0xC4906C68
	UINT32                                                 reserved6552;	//0xC4906C6C
	UINT32                                                 reserved6553;	//0xC4906C70
	UINT32                                                 reserved6554;	//0xC4906C74
	UINT32                                                 reserved6555;	//0xC4906C78
	UINT32                                                 reserved6556;	//0xC4906C7C
	UINT32                                                 reserved6557;	//0xC4906C80
	UINT32                                                 reserved6558;	//0xC4906C84
	UINT32                                                 reserved6559;	//0xC4906C88
	UINT32                                                 reserved6560;	//0xC4906C8C
	UINT32                                                 reserved6561;	//0xC4906C90
	UINT32                                                 reserved6562;	//0xC4906C94
	UINT32                                                 reserved6563;	//0xC4906C98
	UINT32                                                 reserved6564;	//0xC4906C9C
	UINT32                                                 reserved6565;	//0xC4906CA0
	UINT32                                                 reserved6566;	//0xC4906CA4
	UINT32                                                 reserved6567;	//0xC4906CA8
	UINT32                                                 reserved6568;	//0xC4906CAC
	UINT32                                                 reserved6569;	//0xC4906CB0
	UINT32                                                 reserved6570;	//0xC4906CB4
	UINT32                                                 reserved6571;	//0xC4906CB8
	UINT32                                                 reserved6572;	//0xC4906CBC
	UINT32                                                 reserved6573;	//0xC4906CC0
	UINT32                                                 reserved6574;	//0xC4906CC4
	UINT32                                                 reserved6575;	//0xC4906CC8
	UINT32                                                 reserved6576;	//0xC4906CCC
	UINT32                                                 reserved6577;	//0xC4906CD0
	UINT32                                                 reserved6578;	//0xC4906CD4
	UINT32                                                 reserved6579;	//0xC4906CD8
	UINT32                                                 reserved6580;	//0xC4906CDC
	UINT32                                                 reserved6581;	//0xC4906CE0
	UINT32                                                 reserved6582;	//0xC4906CE4
	UINT32                                                 reserved6583;	//0xC4906CE8
	UINT32                                                 reserved6584;	//0xC4906CEC
	UINT32                                                 reserved6585;	//0xC4906CF0
	UINT32                                                 reserved6586;	//0xC4906CF4
	UINT32                                                 reserved6587;	//0xC4906CF8
	UINT32                                                 reserved6588;	//0xC4906CFC
	UINT32                                                 reserved6589;	//0xC4906D00
	UINT32                                                 reserved6590;	//0xC4906D04
	UINT32                                                 reserved6591;	//0xC4906D08
	UINT32                                                 reserved6592;	//0xC4906D0C
	UINT32                                                 reserved6593;	//0xC4906D10
	UINT32                                                 reserved6594;	//0xC4906D14
	UINT32                                                 reserved6595;	//0xC4906D18
	UINT32                                                 reserved6596;	//0xC4906D1C
	UINT32                                                 reserved6597;	//0xC4906D20
	UINT32                                                 reserved6598;	//0xC4906D24
	UINT32                                                 reserved6599;	//0xC4906D28
	UINT32                                                 reserved6600;	//0xC4906D2C
	UINT32                                                 reserved6601;	//0xC4906D30
	UINT32                                                 reserved6602;	//0xC4906D34
	UINT32                                                 reserved6603;	//0xC4906D38
	UINT32                                                 reserved6604;	//0xC4906D3C
	UINT32                                                 reserved6605;	//0xC4906D40
	UINT32                                                 reserved6606;	//0xC4906D44
	UINT32                                                 reserved6607;	//0xC4906D48
	UINT32                                                 reserved6608;	//0xC4906D4C
	UINT32                                                 reserved6609;	//0xC4906D50
	UINT32                                                 reserved6610;	//0xC4906D54
	UINT32                                                 reserved6611;	//0xC4906D58
	UINT32                                                 reserved6612;	//0xC4906D5C
	UINT32                                                 reserved6613;	//0xC4906D60
	UINT32                                                 reserved6614;	//0xC4906D64
	UINT32                                                 reserved6615;	//0xC4906D68
	UINT32                                                 reserved6616;	//0xC4906D6C
	UINT32                                                 reserved6617;	//0xC4906D70
	UINT32                                                 reserved6618;	//0xC4906D74
	UINT32                                                 reserved6619;	//0xC4906D78
	UINT32                                                 reserved6620;	//0xC4906D7C
	UINT32                                                 reserved6621;	//0xC4906D80
	UINT32                                                 reserved6622;	//0xC4906D84
	UINT32                                                 reserved6623;	//0xC4906D88
	UINT32                                                 reserved6624;	//0xC4906D8C
	UINT32                                                 reserved6625;	//0xC4906D90
	UINT32                                                 reserved6626;	//0xC4906D94
	UINT32                                                 reserved6627;	//0xC4906D98
	UINT32                                                 reserved6628;	//0xC4906D9C
	UINT32                                                 reserved6629;	//0xC4906DA0
	UINT32                                                 reserved6630;	//0xC4906DA4
	UINT32                                                 reserved6631;	//0xC4906DA8
	UINT32                                                 reserved6632;	//0xC4906DAC
	UINT32                                                 reserved6633;	//0xC4906DB0
	UINT32                                                 reserved6634;	//0xC4906DB4
	UINT32                                                 reserved6635;	//0xC4906DB8
	UINT32                                                 reserved6636;	//0xC4906DBC
	UINT32                                                 reserved6637;	//0xC4906DC0
	UINT32                                                 reserved6638;	//0xC4906DC4
	UINT32                                                 reserved6639;	//0xC4906DC8
	UINT32                                                 reserved6640;	//0xC4906DCC
	UINT32                                                 reserved6641;	//0xC4906DD0
	UINT32                                                 reserved6642;	//0xC4906DD4
	UINT32                                                 reserved6643;	//0xC4906DD8
	UINT32                                                 reserved6644;	//0xC4906DDC
	UINT32                                                 reserved6645;	//0xC4906DE0
	UINT32                                                 reserved6646;	//0xC4906DE4
	UINT32                                                 reserved6647;	//0xC4906DE8
	UINT32                                                 reserved6648;	//0xC4906DEC
	UINT32                                                 reserved6649;	//0xC4906DF0
	UINT32                                                 reserved6650;	//0xC4906DF4
	UINT32                                                 reserved6651;	//0xC4906DF8
	UINT32                                                 reserved6652;	//0xC4906DFC
	UINT32                                                 reserved6653;	//0xC4906E00
	UINT32                                                 reserved6654;	//0xC4906E04
	UINT32                                                 reserved6655;	//0xC4906E08
	UINT32                                                 reserved6656;	//0xC4906E0C
	UINT32                                                 reserved6657;	//0xC4906E10
	UINT32                                                 reserved6658;	//0xC4906E14
	UINT32                                                 reserved6659;	//0xC4906E18
	UINT32                                                 reserved6660;	//0xC4906E1C
	UINT32                                                 reserved6661;	//0xC4906E20
	UINT32                                                 reserved6662;	//0xC4906E24
	UINT32                                                 reserved6663;	//0xC4906E28
	UINT32                                                 reserved6664;	//0xC4906E2C
	UINT32                                                 reserved6665;	//0xC4906E30
	UINT32                                                 reserved6666;	//0xC4906E34
	UINT32                                                 reserved6667;	//0xC4906E38
	UINT32                                                 reserved6668;	//0xC4906E3C
	UINT32                                                 reserved6669;	//0xC4906E40
	UINT32                                                 reserved6670;	//0xC4906E44
	UINT32                                                 reserved6671;	//0xC4906E48
	UINT32                                                 reserved6672;	//0xC4906E4C
	UINT32                                                 reserved6673;	//0xC4906E50
	UINT32                                                 reserved6674;	//0xC4906E54
	UINT32                                                 reserved6675;	//0xC4906E58
	UINT32                                                 reserved6676;	//0xC4906E5C
	UINT32                                                 reserved6677;	//0xC4906E60
	UINT32                                                 reserved6678;	//0xC4906E64
	UINT32                                                 reserved6679;	//0xC4906E68
	UINT32                                                 reserved6680;	//0xC4906E6C
	UINT32                                                 reserved6681;	//0xC4906E70
	UINT32                                                 reserved6682;	//0xC4906E74
	UINT32                                                 reserved6683;	//0xC4906E78
	UINT32                                                 reserved6684;	//0xC4906E7C
	UINT32                                                 reserved6685;	//0xC4906E80
	UINT32                                                 reserved6686;	//0xC4906E84
	UINT32                                                 reserved6687;	//0xC4906E88
	UINT32                                                 reserved6688;	//0xC4906E8C
	UINT32                                                 reserved6689;	//0xC4906E90
	UINT32                                                 reserved6690;	//0xC4906E94
	UINT32                                                 reserved6691;	//0xC4906E98
	UINT32                                                 reserved6692;	//0xC4906E9C
	UINT32                                                 reserved6693;	//0xC4906EA0
	UINT32                                                 reserved6694;	//0xC4906EA4
	UINT32                                                 reserved6695;	//0xC4906EA8
	UINT32                                                 reserved6696;	//0xC4906EAC
	UINT32                                                 reserved6697;	//0xC4906EB0
	UINT32                                                 reserved6698;	//0xC4906EB4
	UINT32                                                 reserved6699;	//0xC4906EB8
	UINT32                                                 reserved6700;	//0xC4906EBC
	UINT32                                                 reserved6701;	//0xC4906EC0
	UINT32                                                 reserved6702;	//0xC4906EC4
	UINT32                                                 reserved6703;	//0xC4906EC8
	UINT32                                                 reserved6704;	//0xC4906ECC
	UINT32                                                 reserved6705;	//0xC4906ED0
	UINT32                                                 reserved6706;	//0xC4906ED4
	UINT32                                                 reserved6707;	//0xC4906ED8
	UINT32                                                 reserved6708;	//0xC4906EDC
	UINT32                                                 reserved6709;	//0xC4906EE0
	UINT32                                                 reserved6710;	//0xC4906EE4
	UINT32                                                 reserved6711;	//0xC4906EE8
	UINT32                                                 reserved6712;	//0xC4906EEC
	UINT32                                                 reserved6713;	//0xC4906EF0
	UINT32                                                 reserved6714;	//0xC4906EF4
	UINT32                                                 reserved6715;	//0xC4906EF8
	UINT32                                                 reserved6716;	//0xC4906EFC
	UINT32                                                 reserved6717;	//0xC4906F00
	UINT32                                                 reserved6718;	//0xC4906F04
	UINT32                                                 reserved6719;	//0xC4906F08
	UINT32                                                 reserved6720;	//0xC4906F0C
	UINT32                                                 reserved6721;	//0xC4906F10
	UINT32                                                 reserved6722;	//0xC4906F14
	UINT32                                                 reserved6723;	//0xC4906F18
	UINT32                                                 reserved6724;	//0xC4906F1C
	UINT32                                                 reserved6725;	//0xC4906F20
	UINT32                                                 reserved6726;	//0xC4906F24
	UINT32                                                 reserved6727;	//0xC4906F28
	UINT32                                                 reserved6728;	//0xC4906F2C
	UINT32                                                 reserved6729;	//0xC4906F30
	UINT32                                                 reserved6730;	//0xC4906F34
	UINT32                                                 reserved6731;	//0xC4906F38
	UINT32                                                 reserved6732;	//0xC4906F3C
	UINT32                                                 reserved6733;	//0xC4906F40
	UINT32                                                 reserved6734;	//0xC4906F44
	UINT32                                                 reserved6735;	//0xC4906F48
	UINT32                                                 reserved6736;	//0xC4906F4C
	UINT32                                                 reserved6737;	//0xC4906F50
	UINT32                                                 reserved6738;	//0xC4906F54
	UINT32                                                 reserved6739;	//0xC4906F58
	UINT32                                                 reserved6740;	//0xC4906F5C
	UINT32                                                 reserved6741;	//0xC4906F60
	UINT32                                                 reserved6742;	//0xC4906F64
	UINT32                                                 reserved6743;	//0xC4906F68
	UINT32                                                 reserved6744;	//0xC4906F6C
	UINT32                                                 reserved6745;	//0xC4906F70
	UINT32                                                 reserved6746;	//0xC4906F74
	UINT32                                                 reserved6747;	//0xC4906F78
	UINT32                                                 reserved6748;	//0xC4906F7C
	UINT32                                                 reserved6749;	//0xC4906F80
	UINT32                                                 reserved6750;	//0xC4906F84
	UINT32                                                 reserved6751;	//0xC4906F88
	UINT32                                                 reserved6752;	//0xC4906F8C
	UINT32                                                 reserved6753;	//0xC4906F90
	UINT32                                                 reserved6754;	//0xC4906F94
	UINT32                                                 reserved6755;	//0xC4906F98
	UINT32                                                 reserved6756;	//0xC4906F9C
	UINT32                                                 reserved6757;	//0xC4906FA0
	UINT32                                                 reserved6758;	//0xC4906FA4
	UINT32                                                 reserved6759;	//0xC4906FA8
	UINT32                                                 reserved6760;	//0xC4906FAC
	UINT32                                                 reserved6761;	//0xC4906FB0
	UINT32                                                 reserved6762;	//0xC4906FB4
	UINT32                                                 reserved6763;	//0xC4906FB8
	UINT32                                                 reserved6764;	//0xC4906FBC
	UINT32                                                 reserved6765;	//0xC4906FC0
	UINT32                                                 reserved6766;	//0xC4906FC4
	UINT32                                                 reserved6767;	//0xC4906FC8
	UINT32                                                 reserved6768;	//0xC4906FCC
	UINT32                                                 reserved6769;	//0xC4906FD0
	UINT32                                                 reserved6770;	//0xC4906FD4
	UINT32                                                 reserved6771;	//0xC4906FD8
	UINT32                                                 reserved6772;	//0xC4906FDC
	REG_DDRC_M1_REY_SPARE_T                                   rey_spare;	//0xC4906FE0
}REG_DDRC_M1_T;

extern volatile REG_DDRC_M1_T*                     gpREG_DDRC_M1;
  
#endif
