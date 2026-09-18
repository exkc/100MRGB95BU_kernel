#ifndef _CTOP_CTRL_VD1_O20A0_REG_H_
#define _CTOP_CTRL_VD1_O20A0_REG_H_

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
    0xC9C7_1600    enable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_vs_en             :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_led_i2c_en            :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmi_i2c_en           :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_en_eb_addr            :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_en_aud_daclrch        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_aud_multi_ch_en       :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_VD1_ENABLE01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1604    enable02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_i2c8_en           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_10_2     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_10_1     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_uart2_en              :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pwm_trig_en           :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_CTRL_VD1_ENABLE02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1608    ioctrl_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_audclk_out__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_audclk_out__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_audclk_out__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_audclk_out__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_audclk_out__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_audclk_out__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_audclk_out__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_160C    ioctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_daclrch__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_daclrch__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_daclrch__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_daclrch__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_daclrch__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_daclrch__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_daclrch__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1610    ioctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_daclrck__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_daclrck__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_daclrck__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_daclrck__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_daclrck__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_daclrck__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_daclrck__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1614    ioctrl_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dacsck__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dacsck__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dacsck__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dacsck__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dacsck__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dacsck__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dacsck__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1618    ioctrl_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio16__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio16__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio16__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio16__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio16__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio16__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio16__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_161C    ioctrl_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio17__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio17__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio17__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio17__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio17__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio17__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio17__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1620    ioctrl_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio18__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio18__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio18__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio18__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio18__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio18__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio18__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1624    ioctrl_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio19__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio19__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio19__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio19__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio19__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio19__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio19__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1628    ioctrl_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio20__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio20__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio20__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio20__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio20__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio20__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio20__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_162C    ioctrl_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio21__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio21__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio21__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio21__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio21__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio21__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio21__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1630    ioctrl_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio22__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio22__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio22__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio22__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio22__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio22__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio22__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1634    ioctrl_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio23__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio23__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio23__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio23__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio23__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio23__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio23__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1638    ioctrl_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio24__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio24__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio24__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio24__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio24__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio24__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio24__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_163C    ioctrl_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio25__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio25__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio25__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio25__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio25__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio25__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio25__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1640    ioctrl_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pqe_ip_enb_0__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pqe_ip_enb_0__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pqe_ip_enb_0__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pqe_ip_enb_0__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pqe_ip_enb_0__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pqe_ip_enb_0__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pqe_ip_enb_0__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1644    ioctrl_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pqe_ip_enb_1__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pqe_ip_enb_1__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pqe_ip_enb_1__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pqe_ip_enb_1__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pqe_ip_enb_1__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pqe_ip_enb_1__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pqe_ip_enb_1__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_VD1_IOCTRL_15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_VD1_ENABLE01_O20A0_T               enable01                 ;         // 0xC9C7_1600
CTOP_CTRL_VD1_ENABLE02_O20A0_T               enable02                 ;         // 0xC9C7_1604
CTOP_CTRL_VD1_IOCTRL_0_O20A0_T               ioctrl_0                 ;         // 0xC9C7_1608
CTOP_CTRL_VD1_IOCTRL_1_O20A0_T               ioctrl_1                 ;         // 0xC9C7_160C
CTOP_CTRL_VD1_IOCTRL_2_O20A0_T               ioctrl_2                 ;         // 0xC9C7_1610
CTOP_CTRL_VD1_IOCTRL_3_O20A0_T               ioctrl_3                 ;         // 0xC9C7_1614
CTOP_CTRL_VD1_IOCTRL_4_O20A0_T               ioctrl_4                 ;         // 0xC9C7_1618
CTOP_CTRL_VD1_IOCTRL_5_O20A0_T               ioctrl_5                 ;         // 0xC9C7_161C
CTOP_CTRL_VD1_IOCTRL_6_O20A0_T               ioctrl_6                 ;         // 0xC9C7_1620
CTOP_CTRL_VD1_IOCTRL_7_O20A0_T               ioctrl_7                 ;         // 0xC9C7_1624
CTOP_CTRL_VD1_IOCTRL_8_O20A0_T               ioctrl_8                 ;         // 0xC9C7_1628
CTOP_CTRL_VD1_IOCTRL_9_O20A0_T               ioctrl_9                 ;         // 0xC9C7_162C
CTOP_CTRL_VD1_IOCTRL_10_O20A0_T              ioctrl_10                ;         // 0xC9C7_1630
CTOP_CTRL_VD1_IOCTRL_11_O20A0_T              ioctrl_11                ;         // 0xC9C7_1634
CTOP_CTRL_VD1_IOCTRL_12_O20A0_T              ioctrl_12                ;         // 0xC9C7_1638
CTOP_CTRL_VD1_IOCTRL_13_O20A0_T              ioctrl_13                ;         // 0xC9C7_163C
CTOP_CTRL_VD1_IOCTRL_14_O20A0_T              ioctrl_14                ;         // 0xC9C7_1640
CTOP_CTRL_VD1_IOCTRL_15_O20A0_T              ioctrl_15                ;         // 0xC9C7_1644
} CTOP_CTRL_VD1_REG_O20A0_T;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_VD1_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

