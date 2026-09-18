#ifndef _CTOP_CTRL_ND0_O20A0_REG_H_
#define _CTOP_CTRL_ND0_O20A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC930_7400    enable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sc_clk_sel            :  1,    //      0
    reg_jtag0_disable         :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_CTRL_ND0_ENABLE01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7404    ioctrl_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_cd1_n__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_cd1_n__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_cd1_n__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_cd1_n__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_cd1_n__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_cd1_n__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_cd1_n__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7408    ioctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_cd2_n__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_cd2_n__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_cd2_n__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_cd2_n__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_cd2_n__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_cd2_n__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_cd2_n__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_740C    ioctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ce1_n__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_ce1_n__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_ce1_n__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_ce1_n__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_ce1_n__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_ce1_n__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_ce1_n__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7410    ioctrl_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ce2_n__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_ce2_n__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_ce2_n__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_ce2_n__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_ce2_n__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_ce2_n__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_ce2_n__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7414    ioctrl_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ireq_n__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_ireq_n__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_ireq_n__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_ireq_n__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_ireq_n__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_ireq_n__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_ireq_n__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7418    ioctrl_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reg_n__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_reg_n__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_reg_n__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_reg_n__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_reg_n__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_reg_n__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_reg_n__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_741C    ioctrl_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reset__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_reset__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_reset__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_reset__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_reset__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_reset__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_reset__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7420    ioctrl_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_wait_n__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_wait_n__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_wait_n__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_wait_n__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_wait_n__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_wait_n__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_wait_n__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7424    ioctrl_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_clk_out__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sc_clk_out__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sc_clk_out__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sc_clk_out__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sc_clk_out__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sc_clk_out__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sc_clk_out__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7428    ioctrl_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_data__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sc_data__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sc_data__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sc_data__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sc_data__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sc_data__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sc_data__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_742C    ioctrl_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_detect__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sc_detect__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sc_detect__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sc_detect__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sc_detect__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sc_detect__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sc_detect__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7430    ioctrl_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_rst__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sc_rst__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sc_rst__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sc_rst__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sc_rst__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sc_rst__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sc_rst__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7434    ioctrl_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_vcc_sel__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sc_vcc_sel__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sc_vcc_sel__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sc_vcc_sel__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sc_vcc_sel__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sc_vcc_sel__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sc_vcc_sel__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7438    ioctrl_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_vccen__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sc_vccen__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sc_vccen__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sc_vccen__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sc_vccen__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sc_vccen__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sc_vccen__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND0_IOCTRL_13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_743C    ioctrl_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_16_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_16_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_16_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_16_4     :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CTRL_ND0_IOCTRL_14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7440    ioctrl_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_bist_fail        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_emmc_bist_pass        :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_ND0_IOCTRL_15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_ND0_ENABLE01_O20A0_T               enable01                 ;         // 0xC930_7400
CTOP_CTRL_ND0_IOCTRL_0_O20A0_T               ioctrl_0                 ;         // 0xC930_7404
CTOP_CTRL_ND0_IOCTRL_1_O20A0_T               ioctrl_1                 ;         // 0xC930_7408
CTOP_CTRL_ND0_IOCTRL_2_O20A0_T               ioctrl_2                 ;         // 0xC930_740C
CTOP_CTRL_ND0_IOCTRL_3_O20A0_T               ioctrl_3                 ;         // 0xC930_7410
CTOP_CTRL_ND0_IOCTRL_4_O20A0_T               ioctrl_4                 ;         // 0xC930_7414
CTOP_CTRL_ND0_IOCTRL_5_O20A0_T               ioctrl_5                 ;         // 0xC930_7418
CTOP_CTRL_ND0_IOCTRL_6_O20A0_T               ioctrl_6                 ;         // 0xC930_741C
CTOP_CTRL_ND0_IOCTRL_7_O20A0_T               ioctrl_7                 ;         // 0xC930_7420
CTOP_CTRL_ND0_IOCTRL_8_O20A0_T               ioctrl_8                 ;         // 0xC930_7424
CTOP_CTRL_ND0_IOCTRL_9_O20A0_T               ioctrl_9                 ;         // 0xC930_7428
CTOP_CTRL_ND0_IOCTRL_10_O20A0_T              ioctrl_10                ;         // 0xC930_742C
CTOP_CTRL_ND0_IOCTRL_11_O20A0_T              ioctrl_11                ;         // 0xC930_7430
CTOP_CTRL_ND0_IOCTRL_12_O20A0_T              ioctrl_12                ;         // 0xC930_7434
CTOP_CTRL_ND0_IOCTRL_13_O20A0_T              ioctrl_13                ;         // 0xC930_7438
CTOP_CTRL_ND0_IOCTRL_14_O20A0_T              ioctrl_14                ;         // 0xC930_743C
CTOP_CTRL_ND0_IOCTRL_15_O20A0_T              ioctrl_15                ;         // 0xC930_7440
} CTOP_CTRL_ND0_REG_O20A0_T;
/* 17 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_ND0_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

