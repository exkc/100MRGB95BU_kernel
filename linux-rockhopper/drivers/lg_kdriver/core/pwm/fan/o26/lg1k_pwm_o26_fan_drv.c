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
#include <linux/delay.h>

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
static void o26_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en);
static void o26_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty);
static void o26_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en);
static int  o26_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev);
static void o26_fan_hw_dump_regs(struct seq_file* m);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
// hw context is used at lg1k_pwm_fan_drv.c
struct lg1k_pwm_hw_driver o26_fan_hw_driver =
{
    .hw_config = o26_fan_hw_config,
    .hw_enable = o26_fan_hw_enable,
    .hw_get_rpm = o26_fan_hw_get_rpm,
    .hw_dump_regs = o26_fan_hw_dump_regs,
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

static void o26_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en)
{
#if 0
    int mux_val = (en) ? 0x2 : 0x0;

    lg1k_pwm_debug("pwm(%s) en=0x%x, mux_val=0x%x\n", my_dev->name, en, mux_val);

    if (!en)
    {
        lg1k_pwm_warn("pwm(%s) DO NOT disable mux\n", my_dev->name);
        return;
    }

    CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud64);
    CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud65);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio10_mux_sel, mux_val);   // fsc0.out_ch0 (pwm0)
            break;

        case PWM_ID_FAN(1):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio11_mux_sel, mux_val);   // fsc0.out_ch0 (pwm1)
            break;

        case PWM_ID_FAN(2):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio12_mux_sel, mux_val);   // fsc0.out_ch0 (pwm2)
            break;

        case PWM_ID_RPM(0):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio00_mux_sel, mux_val);   // fsc0_tacho.in_ch0 (rpm0)
            break;

        case PWM_ID_RPM(1):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio01_mux_sel, mux_val);   // fsc0_tacho.in_ch0 (rpm1)
            break;

        case PWM_ID_RPM(2):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio02_mux_sel, mux_val);   // fsc0_tacho.in_ch2 (rpm2)
            break;

        case PWM_ID_RPM(3):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio05_mux_sel, mux_val);   // fsc0_tacho.in_ch3 (rpm3)
            break;

        case PWM_ID_RPM(4):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio06_mux_sel, mux_val);   // fsc0_tacho.in_ch4 (rpm4)
            break;

        case PWM_ID_RPM(5):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio07_mux_sel, mux_val);   // fsc0_tacho.in_ch5 (rpm5)
            break;

        case PWM_ID_RPM(6):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio08_mux_sel, mux_val);   // fsc0_tacho.in_ch6 (rpm6)
            break;

        case PWM_ID_RPM(7):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio09_mux_sel, mux_val);   // fsc0_tacho.in_ch7 (rpm7)
            break;

        case PWM_ID_RPM(8):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio13_mux_sel, mux_val);   // fsc0_tacho.in_ch8 (rpm8)
            break;

        case PWM_ID_RPM(9):
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio14_mux_sel, mux_val);   // fsc0_tacho.in_ch9 (rpm9)
            break;

        default:
            lg1k_pwm_error("invalid pwmid=0x%08x\n",  my_dev->pwm_id);
            break;
    }

    lg1k_pwm_debug("fsc0.iomux.pad_64: 0x%08x\n", CTOP_CTRL_O26Ax_Rd(IOMUX_CTRL_AUD, pad_aud64));
    lg1k_pwm_debug("fsc0.iomux.pad_65: 0x%08x\n", CTOP_CTRL_O26Ax_Rd(IOMUX_CTRL_AUD, pad_aud65));

    CTOP_CTRL_O26Ax_WrFL(IOMUX_CTRL_AUD, pad_aud64);
    CTOP_CTRL_O26Ax_WrFL(IOMUX_CTRL_AUD, pad_aud65);
#endif

#if 0
    lg1k_pwm_noti("o26 pwm(%s) %s. hw_cfg_mask=0x%08x\n",
                  my_dev->name,
                  (en) ? "configured" : "unconfigured",
                  hw_cfg_mask);
#endif

}

static void o26_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty)
{
    uint32_t val;

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0): // fsc0.ch0

            if (period >= 0)
            {
                CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_gen_clk_0);
                CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, val);

                if (val != period)
                {
                    CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period);
                    CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_gen_clk_0);
                }
            }

            if (duty >= 0)
            {
                CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_duty_0);
                CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_duty_0, reg_pwm_duty_ch0, duty);
                CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_duty_0);
            }

            break;

        case PWM_ID_FAN(1): // fsc0.ch1

            if (period >= 0)
            {
                CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_gen_clk_1);
                CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, val);

                if (val != period)
                {
                    CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period);
                    CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_gen_clk_1);
                }
            }

            if (duty >= 0)
            {
                CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_duty_1);
                CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_duty_1, reg_pwm_duty_ch1, duty);
                CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_duty_1);
            }

            break;

        case PWM_ID_FAN(2): // fsc0.ch2

            if (period >= 0)
            {
                CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_gen_clk_2);
                CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, val);

                if (val != period)
                {
                    CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period);
                    CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_gen_clk_2);
                }
            }

            if (duty >= 0)
            {
                CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_duty_2);
                CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_duty_2, reg_pwm_duty_ch2, duty);
                CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_duty_2);
            }

            break;

        default:
            // do nothing
            break;
    }
}

static void o26_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en)
{
    int mux_val = (en) ? 0x2 : 0x0;

    lg1k_pwm_noti("pwm(%s) en=0x%x\n", my_dev->name, en);

    o26_fan_hw_set_mux(my_dev, en);

    CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud64);
    CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud65);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0): // fsc0.out_ch0

            if (!en)
            {
                lg1k_pwm_noti("make zero period/duty before pwm(%s) shutdown\n", my_dev->name);
                o26_fan_hw_config(my_dev, 0, 0);
                //usleep_range(10000,20000);
            }

            // fsc.out 에 대한 iomux 를 off 할 수 없다. fan 이 full speed 로 동작함
            // 따라서 iomux 설정은 fan on/off 와 무관하게 항상 fan 용도로 조치되도록 한다.
			// see http://jira.lge.com/issue/browse/SICDTV-15895
            {
                mux_val = 0x2;
                CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio10_mux_sel, mux_val);   // fsc0.out_ch0 (pwm0)
            }

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_op_mode_0);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_op_mode_0, reg_pwm_en_ch0, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_op_mode_0);
            break;

        case PWM_ID_FAN(1): // fsc0.out_ch1

            if (!en)
            {
                lg1k_pwm_noti("make zero period/duty before pwm(%s) shutdown\n", my_dev->name);
                o26_fan_hw_config(my_dev, 0, 0);
                //usleep_range(10000,20000);
            }

            // fsc.out 에 대한 iomux 를 off 할 수 없다. fan 이 full speed 로 동작함
            // 따라서 iomux 설정은 fan on/off 와 무관하게 항상 fan 용도로 조치되도록 한다.
            {
                mux_val = 0x2;
                CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio11_mux_sel, mux_val);   // fsc0.out_ch0 (pwm1)
            }

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_op_mode_1);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_op_mode_1, reg_pwm_en_ch1, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_op_mode_1);
            break;

        case PWM_ID_FAN(2): // fsc0.out_ch2

            if (!en)
            {
                lg1k_pwm_noti("make zero period/duty before pwm(%s) shutdown\n", my_dev->name);
                o26_fan_hw_config(my_dev, 0, 0);
                //usleep_range(10000,20000);
            }

            // fsc.out 에 대한 iomux 를 off 할 수 없다. fan 이 full speed 로 동작함
            // 따라서 iomux 설정은 fan on/off 와 무관하게 항상 fan 용도로 조치되도록 한다.
            {
                mux_val = 0x2;
                CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio12_mux_sel, mux_val);   // fsc0.out_ch0 (pwm2)
            }

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_op_mode_2);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, pwm_op_mode_2, reg_pwm_en_ch2, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, pwm_op_mode_2);
            break;

        case PWM_ID_RPM(0): // fsc0.in_ch0
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio00_mux_sel, mux_val);   // fsc0_tacho.in_ch0 (rpm0)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch0, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(1): // fsc0.in_ch1
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio01_mux_sel, mux_val);   // fsc0_tacho.in_ch0 (rpm1)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch1, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(2): // fsc0.in_ch2
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio02_mux_sel, mux_val);   // fsc0_tacho.in_ch2 (rpm2)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch2, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(3): // fsc0.in_ch3
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio05_mux_sel, mux_val);   // fsc0_tacho.in_ch3 (rpm3)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch3, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(4): // fsc0.in_ch4
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio06_mux_sel, mux_val);   // fsc0_tacho.in_ch4 (rpm4)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch4, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(5): // fsc0.in_ch5
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio07_mux_sel, mux_val);   // fsc0_tacho.in_ch5 (rpm5)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch5, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(6): // fsc0.in_ch6
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio08_mux_sel, mux_val);   // fsc0_tacho.in_ch6 (rpm6)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch6, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(7): // fsc0.in_ch7
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio09_mux_sel, mux_val);   // fsc0_tacho.in_ch7 (rpm7)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch7, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(8): // fsc0.in_ch8
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio13_mux_sel, mux_val);   // fsc0_tacho.in_ch8 (rpm8)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch8, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(9): // fsc0.in_ch9
            CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio14_mux_sel, mux_val);   // fsc0_tacho.in_ch9 (rpm9)

            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);
            CTOP_CTRL_O26Ax_Wr01(FSC_CTRL_AUD, reg_pwm_det_en, reg_pwm_det_en_ch9, en);
            CTOP_CTRL_O26Ax_WrFL(FSC_CTRL_AUD, reg_pwm_det_en);
            break;

        default:
            // do nothing
            break;
    }

    CTOP_CTRL_O26Ax_WrFL(IOMUX_CTRL_AUD, pad_aud64); // update iomux
    CTOP_CTRL_O26Ax_WrFL(IOMUX_CTRL_AUD, pad_aud65); // update iomux
}

static int o26_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev)
{
    int rpm;

    switch (my_dev->pwm_id)
    {
        case PWM_ID_RPM(0): // fsc0.in_ch0
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_0);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_0, reg_pwm_sampling_data_ch0);
            break;

        case PWM_ID_RPM(1): // fsc0.in_ch1
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_1);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_1, reg_pwm_sampling_data_ch1);
            break;

        case PWM_ID_RPM(2): // fsc0.in_ch2
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_2);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_2, reg_pwm_sampling_data_ch2);
            break;

        case PWM_ID_RPM(3): // fsc0.in_ch3
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_3);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_3, reg_pwm_sampling_data_ch3);
            break;

        case PWM_ID_RPM(4): // fsc0.in_ch4
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_4);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_4, reg_pwm_sampling_data_ch4);
            break;

        case PWM_ID_RPM(5): // fsc0.in_ch5
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_5);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_5, reg_pwm_sampling_data_ch5);
            break;

        case PWM_ID_RPM(6): // fsc0.in_ch6
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_6);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_6, reg_pwm_sampling_data_ch6);
            break;

        case PWM_ID_RPM(7): // fsc0.in_ch7
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_7);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_7, reg_pwm_sampling_data_ch7);
            break;

        case PWM_ID_RPM(8): // fsc0.in_ch8
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_8);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_8, reg_pwm_sampling_data_ch8);
            break;

        case PWM_ID_RPM(9): // fsc0.in_ch9
            CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_9);
            rpm = CTOP_CTRL_O26Ax_RdFd(FSC_CTRL_AUD, det_count_9, reg_pwm_sampling_data_ch9);
            break;

        default:
            rpm = -1;
            break;
    }

    return rpm;
}

static void o26_fan_hw_dump_regs(struct seq_file* m)
{
    int i;
    unsigned int fan_mux[3];

    unsigned int rpm_mux[10];
    unsigned int duty[3];
    unsigned int period[3];

    // 디벅이 목적 및 HW 담당자와의 커뮤니케이션을 위하여 FSC_CTRL 레지스터 덤프를 진행한다.
    seq_printf(m, "FSC_CTRL reg_dump\n");
    {
        UINT32 reg_val;
        UINT32 reg_base = O26_A0_FSC_CTRL_AUD_BASE;
        UINT32 reg_num = sizeof(O26_A0_FSC_CTRL_AUD_BASE) >> 2;

        for (i = 0; i < reg_num; i ++)
        {
            OS_RdReg(reg_base + (i << 2), &reg_val);
            seq_printf(m, "0x%08x: 0x%08x\n", reg_base + (i << 2), reg_val);
        }
    }

    CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud64);
    CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud65);

    seq_printf(m, "\n");
    seq_printf(m, "IOMUX_CTRL_AUD reg_dump\n");
    seq_printf(m, "IOMUX_CTRL_AUD.pad_aud64 = 0x%08x\n", CTOP_CTRL_O26Ax_Rd(IOMUX_CTRL_AUD, pad_aud64));
    seq_printf(m, "IOMUX_CTRL_AUD.pad_aud65 = 0x%08x\n", CTOP_CTRL_O26Ax_Rd(IOMUX_CTRL_AUD, pad_aud65));

    seq_printf(m, "\n");
    seq_printf(m, "FSC0:\n");

    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_op_mode_0);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_op_mode_1);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_op_mode_2);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, reg_pwm_det_en);

    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_gen_clk_0);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_duty_0);
    CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period[0]);
    CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_duty_0, reg_pwm_duty_ch0, duty[0]);

    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_gen_clk_1);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_duty_1);
    CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period[1]);
    CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_duty_1, reg_pwm_duty_ch1, duty[1]);

    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_gen_clk_2);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, pwm_duty_2);
    CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period[2]);
    CTOP_CTRL_O26Ax_Rd01(FSC_CTRL_AUD, pwm_duty_2, reg_pwm_duty_ch2, duty[2]);

    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_8);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_9);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_0);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_1);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_2);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_3);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_4);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_5);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_6);
    CTOP_CTRL_O26Ax_RdFL(FSC_CTRL_AUD, det_count_7);

    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio10_mux_sel, fan_mux[0]); // fsc0.out_ch0 (pwm0)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio11_mux_sel, fan_mux[1]); // fsc0.out_ch0 (pwm1)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio12_mux_sel, fan_mux[2]); // fsc0.out_ch0 (pwm2)

    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio00_mux_sel, rpm_mux[0]); // fsc0_tacho.in_ch0 (rpm0)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio01_mux_sel, rpm_mux[1]); // fsc0_tacho.in_ch0 (rpm1)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio02_mux_sel, rpm_mux[2]); // fsc0_tacho.in_ch2 (rpm2)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio05_mux_sel, rpm_mux[3]); // fsc0_tacho.in_ch3 (rpm3)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio06_mux_sel, rpm_mux[4]); // fsc0_tacho.in_ch4 (rpm4)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio07_mux_sel, rpm_mux[5]); // fsc0_tacho.in_ch5 (rpm5)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud64, reg_pad_gpio08_mux_sel, rpm_mux[6]); // fsc0_tacho.in_ch6 (rpm6)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio09_mux_sel, rpm_mux[7]); // fsc0_tacho.in_ch7 (rpm7)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio13_mux_sel, rpm_mux[8]); // fsc0_tacho.in_ch8 (rpm8)
    CTOP_CTRL_O26Ax_Rd01(IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio14_mux_sel, rpm_mux[9]); // fsc0_tacho.in_ch9 (rpm9)

    // fsc0 report mux status
    for (i = 0; i < 3; i++)
    {
        seq_printf(m, "fsc.iomux.pwm(%d): %d\n", i, fan_mux[i]);
    }

    for (i = 0; i < 10; i++)
    {
        seq_printf(m, "fsc.iomux.rpm(%d): %d\n", i, rpm_mux[i]);
    }

    seq_printf(m, "\n");

    // fsc0 report active (enable/disable) status
    seq_printf(m, "fsc.pwm_op_mode0(fan0_out): 0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, pwm_op_mode_0));
    seq_printf(m, "fsc.pwm_op_mode1(fan1_out): 0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, pwm_op_mode_1));
    seq_printf(m, "fsc.pwm_op_mode2(fan2_out): 0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, pwm_op_mode_2));
    seq_printf(m, "fsc.pwm_det_en(tacho_in): 0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, reg_pwm_det_en));
    seq_printf(m, "\n");

    // fsc0 report duty & period of pwm0/1/2
    seq_printf(m, "fsc.pwm0.period:  0x%08x\n", period[0]);
    seq_printf(m, "fsc.pwm0.duty:    0x%08x\n", duty[0]);
    seq_printf(m, "fsc.pwm1.period:  0x%08x\n", period[1]);
    seq_printf(m, "fsc.pwm1.duty:    0x%08x\n", duty[1]);
    seq_printf(m, "fsc.pwm2.period:  0x%08x\n", period[2]);
    seq_printf(m, "fsc.pwm2.duty:    0x%08x\n", duty[2]);
    seq_printf(m, "\n");

    // fsc0 report RPM status
    seq_printf(m, "fsc.rpm0.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_0));
    seq_printf(m, "fsc.rpm1.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_1));
    seq_printf(m, "fsc.rpm2.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_2));
    seq_printf(m, "fsc.rpm3.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_3));
    seq_printf(m, "fsc.rpm4.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_4));
    seq_printf(m, "fsc.rpm5.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_5));
    seq_printf(m, "fsc.rpm6.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_6));
    seq_printf(m, "fsc.rpm7.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_7));
    seq_printf(m, "fsc.rpm8.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_8));
    seq_printf(m, "fsc.rpm9.count:   0x%08x\n", CTOP_CTRL_O26Ax_Rd(FSC_CTRL_AUD, det_count_9));
    seq_printf(m, "\n");
}

