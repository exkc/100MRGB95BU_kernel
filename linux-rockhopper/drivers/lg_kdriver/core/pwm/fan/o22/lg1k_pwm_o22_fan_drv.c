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
static void o22_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en);
static void o22_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty);
static void o22_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en);
static int  o22_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev);
static void o22_fan_hw_dump_regs(struct seq_file* m);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
// hw context is used at lg1k_pwm_fan_drv.c
struct lg1k_pwm_hw_driver o22_fan_hw_driver =
{
    .hw_config = o22_fan_hw_config,
    .hw_enable = o22_fan_hw_enable,
    .hw_get_rpm = o22_fan_hw_get_rpm,
    .hw_dump_regs = o22_fan_hw_dump_regs,
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

static void o22_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en)
{
    int ctop_val = (en) ? 0x2 : 0x0;

    lg1k_pwm_debug("pwm(%s) en=0x%x, ctop_val=0x%x\n", my_dev->name, en, ctop_val);

    if (!en)
    {
        lg1k_pwm_warn("pwm(%s) DO NOT disable mux\n", my_dev->name);
        return;
    }

    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_LGSR, pad_lgsr67);  // fsc0.iomux
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_LGSR, pad_lgsr68);  // fsc0.iomux
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd067);    // fsc1.iomux
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd068);    // fsc1.iomux
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd069);    // fsc1.iomux

#if 0
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio10_mux_sel, 0x0); // fsc0.out_ch0 (pwm0)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio11_mux_sel, 0x0); // fsc0.out_ch1 (pwm1)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio12_mux_sel, 0x0); // fsc0.out_ch2 (pwm2)

    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio0_mux_sel, 0x0);  // fsc0.in_ch0 (rpm0)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio1_mux_sel, 0x0);  // fsc0.in_ch1 (rpm1)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio2_mux_sel, 0x0);  // fsc0.in_ch2 (rpm2)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio3_mux_sel, 0x0);  // fsc0.in_ch3 (rpm3)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio4_mux_sel, 0x0);  // fsc0.in_ch4 (rpm4)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio5_mux_sel, 0x0);  // fsc0.in_ch5 (rpm5)

    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio6_mux_sel, 0x0);  // fsc0.in_ch6 (rpm6)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio7_mux_sel, 0x0);  // fsc0.in_ch7 (rpm7)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio8_mux_sel, 0x0);  // fsc0.in_ch8 (rpm8)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio9_mux_sel, 0x0);  // fsc0.in_ch9 (rpm9)

    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data0_ext2_mux_sel, 0x0); // fsc1.out_ch0 (pwm3)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data1_ext2_mux_sel, 0x0); // fsc1.out_ch1 (pwm4)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data2_ext2_mux_sel, 0x0); // fsc1.out_ch2 (pwm5)

    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data0_ext1_mux_sel, 0x0);  // fsc1.in_ch0 (rpm10
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data1_ext1_mux_sel, 0x0);  // fsc1.in_ch1 (rpm11)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data2_ext1_mux_sel, 0x0);  // fsc1.in_ch2 (rpm12)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data3_ext1_mux_sel, 0x0);  // fsc1.in_ch3 (rpm13)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data4_ext1_mux_sel, 0x0);  // fsc1.in_ch4 (rpm14)

    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069, reg_pad_tpi_data5_ext1_mux_sel, 0x0);  // fsc1.in_ch5 (rpm15)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069, reg_pad_tpi_data6_ext1_mux_sel, 0x0);  // fsc1.in_ch6 (rpm16)

    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data4_ext2_mux_sel, 0x0);  // fsc1.in_ch7 (rpm17)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data5_ext2_mux_sel, 0x0);  // fsc1.in_ch8 (rpm18)
    CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data6_ext2_mux_sel, 0x0);  // fsc1.in_ch8 (rpm19)

    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_LGSR, pad_lgsr67);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_LGSR, pad_lgsr68);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd067);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd068);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd069);

    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_LGSR, pad_lgsr67);
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_LGSR, pad_lgsr68);
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd067);
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd068);
    CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd069);
#endif

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio10_mux_sel, ctop_val); // fsc0.out_ch0 (pwm0)
            break;

        case PWM_ID_FAN(1):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio11_mux_sel, ctop_val); // fsc0.out_ch1 (pwm1)
            break;

        case PWM_ID_FAN(2):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio12_mux_sel, ctop_val); // fsc0.out_ch2 (pwm2)
            break;


        case PWM_ID_RPM(0):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio0_mux_sel, ctop_val);  // fsc0.in_ch0 (rpm0)
            break;

        case PWM_ID_RPM(1):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio1_mux_sel, ctop_val);  // fsc0.in_ch1 (rpm1)
            break;

        case PWM_ID_RPM(2):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio2_mux_sel, ctop_val);  // fsc0.in_ch2 (rpm2)
            break;

        case PWM_ID_RPM(3):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio3_mux_sel, ctop_val);  // fsc0.in_ch3 (rpm3)
            break;

        case PWM_ID_RPM(4):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio4_mux_sel, ctop_val);  // fsc0.in_ch4 (rpm4)
            break;

        case PWM_ID_RPM(5):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr67, reg_pad_gpio5_mux_sel, ctop_val);  // fsc0.in_ch5 (rpm5)
            break;

        case PWM_ID_RPM(6):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio6_mux_sel, ctop_val);  // fsc0.in_ch6 (rpm6)
            break;

        case PWM_ID_RPM(7):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio7_mux_sel, ctop_val);  // fsc0.in_ch7 (rpm7)
            break;

        case PWM_ID_RPM(8):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio8_mux_sel, ctop_val);  // fsc0.in_ch8 (rpm8)
            break;

        case PWM_ID_RPM(9):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_LGSR, pad_lgsr68, reg_pad_gpio9_mux_sel, ctop_val);  // fsc0.in_ch9 (rpm9)
            break;

        case PWM_ID_FAN(3):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data0_ext2_mux_sel, ctop_val); // fsc1.out_ch0 (pwm3)
            break;

        case PWM_ID_FAN(4):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data1_ext2_mux_sel, ctop_val); // fsc1.out_ch1 (pwm4)
            break;

        case PWM_ID_FAN(5):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data2_ext2_mux_sel, ctop_val); // fsc1.out_ch2 (pwm5)
            break;

        case PWM_ID_RPM(10):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data0_ext1_mux_sel, ctop_val);  // fsc1.in_ch0 (rpm10)
            break;

        case PWM_ID_RPM(11):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data1_ext1_mux_sel, ctop_val);  // fsc1.in_ch1 (rpm11)
            break;

        case PWM_ID_RPM(12):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data2_ext1_mux_sel, ctop_val);  // fsc1.in_ch2 (rpm12)
            break;

        case PWM_ID_RPM(13):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data3_ext1_mux_sel, ctop_val);  // fsc1.in_ch3 (rpm13)
            break;

        case PWM_ID_RPM(14):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068, reg_pad_tpi_data4_ext1_mux_sel, ctop_val);  // fsc1.in_ch4 (rpm14)
            break;

        case PWM_ID_RPM(15):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069, reg_pad_tpi_data5_ext1_mux_sel, ctop_val);  // fsc1.in_ch5 (rpm15)
            break;

        case PWM_ID_RPM(16):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069, reg_pad_tpi_data6_ext1_mux_sel, ctop_val);  // fsc1.in_ch6 (rpm16)
            break;

        case PWM_ID_RPM(17):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data4_ext2_mux_sel, ctop_val);  // fsc1.in_ch7 (rpm17)
            break;

        case PWM_ID_RPM(18):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data5_ext2_mux_sel, ctop_val);  // fsc1.in_ch7 (rpm18)
            break;

        case PWM_ID_RPM(19):
            CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067, reg_pad_tpi_data6_ext2_mux_sel, ctop_val);  // fsc1.in_ch8 (rpm19)
            break;

        default:
            lg1k_pwm_error("invalid pwmid=0x%08x\n",  my_dev->pwm_id);
            break;
    }

    lg1k_pwm_debug("fsc0.iomux.pad_67: 0x%08x\n", CTOP_CTRL_O22Ax_Rd(FUNC_IOMUX_LGSR, pad_lgsr67));
    lg1k_pwm_debug("fsc0.iomux.pad_68: 0x%08x\n", CTOP_CTRL_O22Ax_Rd(FUNC_IOMUX_LGSR, pad_lgsr68));
    lg1k_pwm_debug("fsc1.iomux.pad_67: 0x%08x\n", CTOP_CTRL_O22Ax_Rd(FUNC_IOMUX_VD0, pad_vd067));
    lg1k_pwm_debug("fsc1.iomux.pad_68: 0x%08x\n", CTOP_CTRL_O22Ax_Rd(FUNC_IOMUX_VD0, pad_vd068));
    lg1k_pwm_debug("fsc1.iomux.pad_69: 0x%08x\n", CTOP_CTRL_O22Ax_Rd(FUNC_IOMUX_VD0, pad_vd069));

    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_LGSR, pad_lgsr67);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_LGSR, pad_lgsr68);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd067);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd068);
    CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd069);
}

static void o22_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty)
{
    uint32_t val;

    //lg1k_pwm_fan_hw_init(my_dev, true);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0): // fsc0.ch0
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_gen_clk_0);
            CTOP_CTRL_O22Ax_Rd01(FSC_LGSR, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, val);

            if (val != period)
            {
                CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period);
                CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_gen_clk_0);
            }

            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_duty_0);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_duty_0, reg_pwm_duty_ch0, duty);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_duty_0);
            break;

        case PWM_ID_FAN(1): // fsc0.ch1
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_gen_clk_1);
            CTOP_CTRL_O22Ax_Rd01(FSC_LGSR, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, val);

            if (val != period)
            {
                CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period);
                CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_gen_clk_1);
            }

            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_duty_1);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_duty_1, reg_pwm_duty_ch1, duty);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_duty_1);
            break;

        case PWM_ID_FAN(2): // fsc0.ch2
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_gen_clk_2);
            CTOP_CTRL_O22Ax_Rd01(FSC_LGSR, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, val);

            if (val != period)
            {
                CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period);
                CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_gen_clk_2);
            }

            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_duty_2);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_duty_2, reg_pwm_duty_ch2, duty);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_duty_2);
            break;

        case PWM_ID_FAN(3): // fsc1.ch0
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_gen_clk_0);
            CTOP_CTRL_O22Ax_Rd01(BND_CTRL_VD0, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, val);

            if (val != period)
            {
                CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period);
                CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_gen_clk_0);
            }

            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_duty_0);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_duty_0, reg_pwm_duty_ch0, duty);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_duty_0);
            break;

        case PWM_ID_FAN(4): // fsc1.ch1
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_gen_clk_1);
            CTOP_CTRL_O22Ax_Rd01(BND_CTRL_VD0, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, val);

            if (val != period)
            {
                CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period);
                CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_gen_clk_1);
            }

            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_duty_1);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_duty_1, reg_pwm_duty_ch1, duty);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_duty_1);
            break;

        case PWM_ID_FAN(5): // fsc1.ch2
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_gen_clk_2);
            CTOP_CTRL_O22Ax_Rd01(BND_CTRL_VD0, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, val);

            if (val != period)
            {
                CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period);
                CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_gen_clk_2);
            }

            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_duty_2);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_duty_2, reg_pwm_duty_ch2, duty);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_duty_2);
            break;

        default:
            // do nothing
            break;
    }
}

static void o22_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en)
{
    lg1k_pwm_noti("pwm(%s) en=0x%x\n", my_dev->name, en);

    o22_fan_hw_set_mux(my_dev, en);

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0): // fsc0.out_ch0
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_op_mode_0);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_op_mode_0, reg_pwm_en_ch0, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_op_mode_0);
            break;

        case PWM_ID_FAN(1): // fsc0.out_ch1
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_op_mode_1);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_op_mode_1, reg_pwm_en_ch1, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_op_mode_1);
            break;

        case PWM_ID_FAN(2): // fsc0.out_ch2
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, pwm_op_mode_2);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, pwm_op_mode_2, reg_pwm_en_ch2, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, pwm_op_mode_2);
            break;

        case PWM_ID_RPM(0): // fsc0.in_ch0
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch0, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(1): // fsc0.in_ch1
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch1, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(2): // fsc0.in_ch2
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch2, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(3): // fsc0.in_ch3
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch3, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(4): // fsc0.in_ch4
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch4, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(5): // fsc0.in_ch5
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch5, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(6): // fsc0.in_ch6
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch6, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(7): // fsc0.in_ch7
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch7, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(8): // fsc0.in_ch8
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch8, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(9): // fsc0.in_ch9
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(FSC_LGSR, reg_pwm_det_en, reg_pwm_det_en_ch9, en);
            CTOP_CTRL_O22Ax_WrFL(FSC_LGSR, reg_pwm_det_en);
            break;


        case PWM_ID_FAN(3): // fsc1.out_ch0
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_op_mode_0);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_op_mode_0, reg_pwm_en_ch0, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_op_mode_0);
            break;

        case PWM_ID_FAN(4): // fsc1.out_ch1
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_op_mode_1);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_op_mode_1, reg_pwm_en_ch1, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_op_mode_1);
            break;

        case PWM_ID_FAN(5): // fsc1.out_ch2
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, pwm_op_mode_2);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, pwm_op_mode_2, reg_pwm_en_ch2, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, pwm_op_mode_2);
            break;

        case PWM_ID_RPM(10): // fsc1.in_ch0
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch0, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(11): // fsc1.in_ch1
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch1, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(12): // fsc1.in_ch2
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch2, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(13): // fsc1.in_ch3
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch3, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(14): // fsc1.in_ch4
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch4, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(15): // fsc1.in_ch5
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch5, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(16): // fsc1.in_ch6
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch6, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(17): // fsc1.in_ch7
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch7, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(18): // fsc1.in_ch8
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch8, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(19): // fsc1.in_ch9
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, reg_pwm_det_en);
            CTOP_CTRL_O22Ax_Wr01(BND_CTRL_VD0, reg_pwm_det_en, reg_pwm_det_en_ch9, en);
            CTOP_CTRL_O22Ax_WrFL(BND_CTRL_VD0, reg_pwm_det_en);
            break;

        default:
            // do nothing
            break;
    }

}

static int  o22_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev)
{
    int rpm = -1;

    switch (my_dev->pwm_id)
    {
        case PWM_ID_RPM(0): // fsc0.in_ch0
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_0);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_0, reg_pwm_sampling_data_ch0);
            break;

        case PWM_ID_RPM(1): // fsc0.in_ch1
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_1);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_1, reg_pwm_sampling_data_ch1);
            break;

        case PWM_ID_RPM(2): // fsc0.in_ch2
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_2);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_2, reg_pwm_sampling_data_ch2);
            break;

        case PWM_ID_RPM(3): // fsc0.in_ch3
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_3);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_3, reg_pwm_sampling_data_ch3);
            break;

        case PWM_ID_RPM(4): // fsc0.in_ch4
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_4);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_4, reg_pwm_sampling_data_ch4);
            break;

        case PWM_ID_RPM(5): // fsc0.in_ch5
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_5);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_5, reg_pwm_sampling_data_ch5);
            break;

        case PWM_ID_RPM(6): // fsc0.in_ch6
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_6);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_6, reg_pwm_sampling_data_ch6);
            break;

        case PWM_ID_RPM(7): // fsc0.in_ch7
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_7);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_7, reg_pwm_sampling_data_ch7);
            break;

        case PWM_ID_RPM(8): // fsc0.in_ch8
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_8);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_8, reg_pwm_sampling_data_ch8);
            break;

        case PWM_ID_RPM(9): // fsc0.in_ch9
            CTOP_CTRL_O22Ax_RdFL(FSC_LGSR, det_count_9);
            rpm = CTOP_CTRL_O22Ax_RdFd(FSC_LGSR, det_count_9, reg_pwm_sampling_data_ch9);
            break;

        case PWM_ID_RPM(10): // fsc1.in_ch0
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_0);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_0, reg_pwm_sampling_data_ch0);
            break;

        case PWM_ID_RPM(11): // fsc1.in_ch1
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_1);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_1, reg_pwm_sampling_data_ch1);
            break;

        case PWM_ID_RPM(12): // fsc1.in_ch2
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_2);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_2, reg_pwm_sampling_data_ch2);
            break;

        case PWM_ID_RPM(13): // fsc1.in_ch3
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_3);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_3, reg_pwm_sampling_data_ch3);
            break;

        case PWM_ID_RPM(14): // fsc1.in_ch4
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_4);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_4, reg_pwm_sampling_data_ch4);
            break;

        case PWM_ID_RPM(15): // fsc1.in_ch5
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_5);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_5, reg_pwm_sampling_data_ch5);
            break;

        case PWM_ID_RPM(16): // fsc1.in_ch6
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_6);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_6, reg_pwm_sampling_data_ch6);
            break;

        case PWM_ID_RPM(17): // fsc1.in_ch7
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_7);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_7, reg_pwm_sampling_data_ch7);
            break;

        case PWM_ID_RPM(18):    // fsc1.in_ch8
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_8);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_8, reg_pwm_sampling_data_ch8);
            break;

        case PWM_ID_RPM(19):    // fsc1.in_ch9
            CTOP_CTRL_O22Ax_RdFL(BND_CTRL_VD0, det_count_9);
            rpm = CTOP_CTRL_O22Ax_RdFd(BND_CTRL_VD0, det_count_9, reg_pwm_sampling_data_ch9);
            break;

        default:
            rpm = -1;
            break;
    }

    return rpm;
}

static void o22_fan_hw_dump_regs(struct seq_file* m)
{

}

