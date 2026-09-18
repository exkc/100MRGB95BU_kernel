/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "lg1k_pwm_impl.h"
#include "sys_regs.h"
#include "proc_util.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
static void m19_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en);
static void m19_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty);
static void m19_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en);
static int  m19_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev);
static void m19_fan_hw_dump_regs(struct seq_file* m);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
// hw context is used at lg1k_pwm_fan_drv.c
struct lg1k_pwm_hw_driver m19_fan_hw_driver =
{
    .hw_config = m19_fan_hw_config,
    .hw_enable = m19_fan_hw_enable,
    .hw_get_rpm = m19_fan_hw_get_rpm,
    .hw_dump_regs = m19_fan_hw_dump_regs,
};

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
    Implementation Group
========================================================================================*/

static void m19_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en)
{
    unsigned int my_hwpwm_mask = (1 << my_dev->hwpwm);
    int mux_val = (en) ? 0x0 : 0x1;

    lg1k_pwm_debug("pwm(%s) en=%d, mux_val=%d\n", my_dev->name, en, mux_val);

    if (!en)
    {
        lg1k_pwm_warn("pwm(%s) DO NOT disable mux\n", my_dev->name);
        return;
    }

#if 0
    // 세부적인 설정을 하기 위하여 초기 설정값으로 돌려야 한다.
    {
        /* mux selection */
        CTOP_CTRL_M19Ax_RdFL(CTOP_ND0, ctop_nd0_r04);
        CTOP_CTRL_M19Ax_RdFL(CTOP_ND0, ctop_nd0_r05);

        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_fsc_en, en);

        //CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_dvb_out_ctrl0, 0x0);
        //CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_dvb_out_ctrl1, 0x0);
        //CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_stpi0_out_ctrl0, 0x0);
        //CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_stpi0_out_ctrl1, 0x0);

        // pwm_out(0) is not connected to gpio(46)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r04, reg_use_cpu_gpio_5_6, 0x1);

        // pwm_out(1) is not connected to gpio(45)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r04, reg_use_cpu_gpio_5_5, 0x1);

        // pwm_out(2) is not connected to gpio(96)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r04, reg_use_cpu_gpio_12_0, 0x1);

        // pwm_in(0) is not connected to gpio(65)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_1, 0x1);

        // pwm_in(1) is not connected to gpio(66)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_2, 0x1);

        // pwm_in(2) is not connected to gpio(67)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_3, 0x1);

        // pwm_in(3) is not connected to gpio(68)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_4, 0x1);

        // pwm_in(4) is not connected to gpio(69)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_5, 0x1);

        // pwm_in(5) is not connected to gpio(70)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_6, 0x1);

        // pwm_in(6) is not connected to gpio(7l)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_7, 0x1);

        // pwm_in(7) is not connected to gpio(104)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_13_0, 0x1);

        // pwm_in(8) is not connected to gpio(111)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_13_7, 0x1);

        // pwm_in(9) is not connected to gpio(128)
        CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_16_0, 0x1);

        CTOP_CTRL_M19Ax_WrFL(CTOP_ND0, ctop_nd0_r04);
        CTOP_CTRL_M19Ax_WrFL(CTOP_ND0, ctop_nd0_r05);
    }
#endif

    // FSC 와 GPIO 가 연결/종료되도록 조치한다.
    CTOP_CTRL_M19Ax_RdFL(CTOP_ND0, ctop_nd0_r04);
    CTOP_CTRL_M19Ax_RdFL(CTOP_ND0, ctop_nd0_r05);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r04, reg_use_cpu_gpio_5_6, mux_val);
            break;

        case PWM_ID_FAN(1):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r04, reg_use_cpu_gpio_5_5, mux_val);
            break;

        case PWM_ID_FAN(2):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r04, reg_use_cpu_gpio_12_0, mux_val);
            break;

        case PWM_ID_RPM(0):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_1, mux_val);
            break;

        case PWM_ID_RPM(1):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_2, mux_val);
            break;

        case PWM_ID_RPM(2):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_3, mux_val);
            break;

        case PWM_ID_RPM(3):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_4, mux_val);
            break;

        case PWM_ID_RPM(4):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_5, mux_val);
            break;

        case PWM_ID_RPM(5):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_6, mux_val);
            break;

        case PWM_ID_RPM(6):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_8_7, mux_val);
            break;

        case PWM_ID_RPM(7):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_13_0, mux_val);
            break;

        case PWM_ID_RPM(8):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_13_7, mux_val);
            break;

        case PWM_ID_RPM(9):
            CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05, reg_use_cpu_gpio_16_0, mux_val);
            break;
    }

    CTOP_CTRL_M19Ax_WrFL(CTOP_ND0, ctop_nd0_r04);
    CTOP_CTRL_M19Ax_WrFL(CTOP_ND0, ctop_nd0_r05);
}

static void m19_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty)
{
    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0):
            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_gen_clk_0);
            CTOP_CTRL_M19Ax_Rd01(FSC, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, val);

            if (val != period)
            {
                CTOP_CTRL_M19Ax_Wr01(FSC, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period);
                CTOP_CTRL_M19Ax_WrFL(FSC, pwm_gen_clk_0);
            }

            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_duty_0);
            CTOP_CTRL_M19Ax_Wr01(FSC, pwm_duty_0, reg_pwm_duty_ch0, duty);
            CTOP_CTRL_M19Ax_WrFL(FSC, pwm_duty_0);
            break;

        case PWM_ID_FAN(1):
            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_gen_clk_1);
            CTOP_CTRL_M19Ax_Rd01(FSC, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, val);

            if (val != period)
            {
                CTOP_CTRL_M19Ax_Wr01(FSC, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period);
                CTOP_CTRL_M19Ax_WrFL(FSC, pwm_gen_clk_1);
            }

            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_duty_1);
            CTOP_CTRL_M19Ax_Wr01(FSC, pwm_duty_1, reg_pwm_duty_ch1, duty);
            CTOP_CTRL_M19Ax_WrFL(FSC, pwm_duty_1);
            break;

        case PWM_ID_FAN(2):
            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_gen_clk_2);
            CTOP_CTRL_M19Ax_Rd01(FSC, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, val);

            if (val != period)
            {
                CTOP_CTRL_M19Ax_Wr01(FSC, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period);
                CTOP_CTRL_M19Ax_WrFL(FSC, pwm_gen_clk_2);
            }

            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_duty_2);
            CTOP_CTRL_M19Ax_Wr01(FSC, pwm_duty_2, reg_pwm_duty_ch2, duty);
            CTOP_CTRL_M19Ax_WrFL(FSC, pwm_duty_2);
            break;

        default:
            // RPM 장치에 대해서는 period, duty 설정이 없다.
            break;
    }
}

static void m19_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en)
{
    lg1k_pwm_noti("pwm(%s) en=0x%x\n", my_dev->name, en);

    m19_fan_hw_set_mux(my_dev, en);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0):
            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_op_mode_0);
            CTOP_CTRL_M19Ax_Wr01(FSC, pwm_op_mode_0, reg_pwm_en_ch0, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, pwm_op_mode_0);
            break;

        case PWM_ID_FAN(1):
            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_op_mode_1);
            CTOP_CTRL_M19Ax_Wr01(FSC, pwm_op_mode_1, reg_pwm_en_ch1, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, pwm_op_mode_1);
            break;

        case PWM_ID_FAN(2):
            CTOP_CTRL_M19Ax_RdFL(FSC, pwm_op_mode_2);
            CTOP_CTRL_M19Ax_Wr01(FSC, pwm_op_mode_2, reg_pwm_en_ch2, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, pwm_op_mode_2);
            break;

        case PWM_ID_RPM(0):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch0, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(1):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch1, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(2):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch2, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(3):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch3, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(4):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch4, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(5):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch5, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(6):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch6, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(7):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch7, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(8):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch8, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(9):
            CTOP_CTRL_M19Ax_RdFL(FSC, reg_pwm_det_en);
            CTOP_CTRL_M19Ax_Wr01(FSC, reg_pwm_det_en, reg_pwm_det_en_ch9, en);
            CTOP_CTRL_M19Ax_WrFL(FSC, reg_pwm_det_en);
            break;

        default:
            // do nothing
            break;
    }
}

static int m19_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev)
{
    int rpm = -1;

    // return rpm=-1 if current is not RPM device
    if ((my_dev->pwm_id & PWM_ID_RPM(0)) != PWM_ID_RPM(0))
    {
        return -1;
    }

    //lg1k_pwm_fan_hw_init(my_dev, true);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_RPM(0):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_0);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_0, reg_pwm_sampling_data_ch0);
            break;

        case PWM_ID_RPM(1):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_1);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_1, reg_pwm_sampling_data_ch1);
            break;

        case PWM_ID_RPM(2):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_2);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_2, reg_pwm_sampling_data_ch2);
            break;

        case PWM_ID_RPM(3):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_3);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_3, reg_pwm_sampling_data_ch3);
            break;

        case PWM_ID_RPM(4):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_4);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_4, reg_pwm_sampling_data_ch4);
            break;

        case PWM_ID_RPM(5):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_5);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_5, reg_pwm_sampling_data_ch5);
            break;

        case PWM_ID_RPM(6):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_6);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_6, reg_pwm_sampling_data_ch6);
            break;

        case PWM_ID_RPM(7):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_7);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_7, reg_pwm_sampling_data_ch7);
            break;

        case PWM_ID_RPM(8):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_8);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_8, reg_pwm_sampling_data_ch8);
            break;

        case PWM_ID_RPM(9):
            CTOP_CTRL_M19Ax_RdFL(FSC, det_count_9);
            rpm = CTOP_CTRL_M19Ax_RdFd(FSC, det_count_9, reg_pwm_sampling_data_ch9);
            break;

        default:
            rpm = -1;
            break;
    }

    return rpm;
}

static void m19_fan_hw_dump_regs(struct seq_file* m)
{
    // not implemented
}
