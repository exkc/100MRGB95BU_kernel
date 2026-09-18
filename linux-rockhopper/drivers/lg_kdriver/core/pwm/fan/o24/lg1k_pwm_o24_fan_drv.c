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
static void o24_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en);
static void o24_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty);
static void o24_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en);
static int  o24_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev);
static void o24_fan_hw_dump_regs(struct seq_file* m);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
// hw context is used at lg1k_pwm_fan_drv.c
struct lg1k_pwm_hw_driver o24_fan_hw_driver =
{
    .hw_config = o24_fan_hw_config,
    .hw_enable = o24_fan_hw_enable,
    .hw_get_rpm = o24_fan_hw_get_rpm,
    .hw_dump_regs = o24_fan_hw_dump_regs,
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

static void o24_fan_hw_set_mux(struct lg1k_pwm_dev* my_dev, bool en)
{
    int mux_val = (en) ? 0x2 : 0x0;

    lg1k_pwm_debug("pwm(%s) en=0x%x, mux_val=0x%x\n", my_dev->name, en, mux_val);

    if (!en)
    {
        lg1k_pwm_warn("pwm(%s) DO NOT disable mux\n", my_dev->name);
        return;
    }

#if 0
    // gpio pinmux 설정은 FSC가 사용할 수 있도록 무조건 0x2 설정을 해줘야 한다.
    // 만약 disable 상태가 되면, 해당 pinmux 의 속성에 따라 예상치 못한 동작을 할 수도 있다.
    // O24 의 경우 0 설정하면  gpio in 으로 설정이 되는데, 이때 FAN 으로 이상 신호가 유입되면서 FAN 이
    // full speed 로 동작한다.
    //
    // 따라서 기존의 동작 처럼 enable/disable 은 지원하지 않도록 하며, 항상 pinmux 설정이 FSC 모드가 되도록
    // 한다.
    // see http://clm.lge.com/issue/browse/SCDCR-6462
    //
    // 추후 kdirver 에서 설정이 필요한 경우가 있다면, 어느 레벨까지 조치해야 하는지 확인이 필요함.
    {
        CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_65);  // fsc0.iomux
        CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_66);  // fsc0.iomux
        CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_67);  // fsc0.iomux

        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio00_mux_sel, 0x2); // fsc0.in_ch0 (rpm0)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio01_mux_sel, 0x2); // fsc0.in_ch1 (rpm1)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio02_mux_sel, 0x2); // fsc0.in_ch2 (rpm2)

        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio03_mux_sel, 0x2); // fsc0.in_ch3 (rpm3)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio04_mux_sel, 0x2); // fsc0.in_ch4 (rpm4)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio05_mux_sel, 0x2); // fsc0.in_ch5 (rpm5)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio06_mux_sel, 0x2); // fsc0.in_ch6 (rpm6)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio07_mux_sel, 0x2); // fsc0.in_ch7 (rpm7)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio08_mux_sel, 0x2); // fsc0.in_ch8 (rpm8)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio09_mux_sel, 0x2); // fsc0.in_ch9 (rpm9)

        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio10_mux_sel, 0x2); // fsc0.out_ch0 (pwm0)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio11_mux_sel, 0x2); // fsc0.out_ch1 (pwm1)
        CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio12_mux_sel, 0x2); // fsc0.out_ch2 (pwm2)

        CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_65);  // fsc0.iomux
        CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_66);  // fsc0.iomux
        CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_67);  // fsc0.iomux

        lg1k_pwm_noti("O22 FAN pwm default config completed\n");
        hw_inited = true;
    }
#endif

    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_65);  // fsc0.iomux
    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_66);  // fsc0.iomux
    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_67);  // fsc0.iomux

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio10_mux_sel, mux_val); // fsc0.out_ch0 (pwm0)
            break;

        case PWM_ID_FAN(1):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio11_mux_sel, mux_val); // fsc0.out_ch1 (pwm1)
            break;

        case PWM_ID_FAN(2):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio12_mux_sel, mux_val); // fsc0.out_ch2 (pwm2)
            break;

        case PWM_ID_RPM(0):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio00_mux_sel, mux_val); // fsc0.in_ch0 (rpm0)
            break;

        case PWM_ID_RPM(1):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio01_mux_sel, mux_val); // fsc0.in_ch1 (rpm1)
            break;

        case PWM_ID_RPM(2):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio02_mux_sel, mux_val); // fsc0.in_ch2 (rpm2)
            break;

        case PWM_ID_RPM(3):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio03_mux_sel, mux_val); // fsc0.in_ch3 (rpm3)
            break;

        case PWM_ID_RPM(4):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio04_mux_sel, mux_val); // fsc0.in_ch4 (rpm4)
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio09_mux_sel, mux_val); // fsc0.in_ch9 (rpm9)
            break;

        case PWM_ID_RPM(5):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio05_mux_sel, mux_val); // fsc0.in_ch5 (rpm5)
            break;

        case PWM_ID_RPM(6):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio06_mux_sel, mux_val); // fsc0.in_ch6 (rpm6)
            break;

        case PWM_ID_RPM(7):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio07_mux_sel, mux_val); // fsc0.in_ch7 (rpm7)
            break;

        case PWM_ID_RPM(8):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio08_mux_sel, mux_val); // fsc0.in_ch8 (rpm8)
            break;

        case PWM_ID_RPM(9):
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio09_mux_sel, mux_val); // fsc0.in_ch9 (rpm9)
            break;

        default:
            lg1k_pwm_error("invalid pwmid=0x%08x\n",  my_dev->pwm_id);
            break;
    }

#if 0

    // save the last cfg
    if (en)
    {
        hw_cfg_mask |= my_hwpwm_mask;
    }
    else
    {
        hw_cfg_mask &= ~my_hwpwm_mask;
    }

#endif

    lg1k_pwm_debug("fsc0.iomux.pad_65: 0x%08x\n", CTOP_CTRL_O24Ax_Rd(IOMUX_CTRL_VD0, pad_vd0_65));
    lg1k_pwm_debug("fsc0.iomux.pad_66: 0x%08x\n", CTOP_CTRL_O24Ax_Rd(IOMUX_CTRL_VD0, pad_vd0_66));
    lg1k_pwm_debug("fsc1.iomux.pad_67: 0x%08x\n", CTOP_CTRL_O24Ax_Rd(IOMUX_CTRL_VD0, pad_vd0_67));

    CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_65);  // fsc0.iomux
    CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_66);  // fsc0.iomux
    CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_67);  // fsc0.iomux

#if 0
    lg1k_pwm_noti("o24 pwm(%s) %s. hw_cfg_mask=0x%08x\n",
                  my_dev->name,
                  (en) ? "configured" : "unconfigured",
                  hw_cfg_mask);
#endif

}

static void o24_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty)
{
    uint32_t val;

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0): // fsc0.ch0
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_gen_clk_0);
            CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, val);

            if (val != period)
            {
                CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period);
                CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_gen_clk_0);
            }

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_duty_0);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_duty_0, reg_pwm_duty_ch0, duty);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_duty_0);
            break;

        case PWM_ID_FAN(1): // fsc0.ch1
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_gen_clk_1);
            CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, val);

            if (val != period)
            {
                CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period);
                CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_gen_clk_1);
            }

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_duty_1);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_duty_1, reg_pwm_duty_ch1, duty);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_duty_1);
            break;

        case PWM_ID_FAN(2): // fsc0.ch2
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_gen_clk_2);
            CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, val);

            if (val != period)
            {
                CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period);
                CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_gen_clk_2);
            }

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_duty_2);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_duty_2, reg_pwm_duty_ch2, duty);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_duty_2);
            break;

        default:
            // do nothing
            break;
    }
}

static void o24_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en)
{
    int mux_val = (en) ? 0x2 : 0x0;

    lg1k_pwm_noti("pwm(%s) en=0x%x\n", my_dev->name, en);

    o24_fan_hw_set_mux(my_dev, en);

    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_65);  // iomux
    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_66);  // iomux
    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_67);  // iomux

    switch (my_dev->pwm_id)
    {
        case PWM_ID_FAN(0): // fsc0.out_ch0
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio10_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_op_mode_0);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_op_mode_0, reg_pwm_en_ch0, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_op_mode_0);
            break;

        case PWM_ID_FAN(1): // fsc0.out_ch1
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio11_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_op_mode_1);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_op_mode_1, reg_pwm_en_ch1, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_op_mode_1);
            break;

        case PWM_ID_FAN(2): // fsc0.out_ch2
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio12_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_op_mode_2);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, pwm_op_mode_2, reg_pwm_en_ch2, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, pwm_op_mode_2);
            break;

        case PWM_ID_RPM(0): // fsc0.in_ch0
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio00_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch0, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(1): // fsc0.in_ch1
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio01_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch1, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(2): // fsc0.in_ch2
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio02_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch2, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(3): // fsc0.in_ch3
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio03_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch3, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(4): // fsc0.in_ch4
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio04_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch4, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(5): // fsc0.in_ch5
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio05_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch5, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(6): // fsc0.in_ch6
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio06_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch6, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(7): // fsc0.in_ch7
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio07_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch7, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(8): // fsc0.in_ch8
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio08_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch8, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        case PWM_ID_RPM(9): // fsc0.in_ch9
            CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio09_mux_sel, mux_val);

            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);
            CTOP_CTRL_O24Ax_Wr01(FSC_CTRL, reg_pwm_det_en, reg_pwm_det_en_ch9, en);
            CTOP_CTRL_O24Ax_WrFL(FSC_CTRL, reg_pwm_det_en);
            break;

        default:
            // do nothing
            break;
    }

    CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_65);  // iomux
    CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_66);  // iomux
    CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_67);  // iomux
}

static int o24_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev)
{
    int rpm;

    switch (my_dev->pwm_id)
    {
        case PWM_ID_RPM(0): // fsc0.in_ch0
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_0);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_0, reg_pwm_sampling_data_ch0);
            break;

        case PWM_ID_RPM(1): // fsc0.in_ch1
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_1);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_1, reg_pwm_sampling_data_ch1);
            break;

        case PWM_ID_RPM(2): // fsc0.in_ch2
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_2);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_2, reg_pwm_sampling_data_ch2);
            break;

        case PWM_ID_RPM(3): // fsc0.in_ch3
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_3);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_3, reg_pwm_sampling_data_ch3);
            break;

        case PWM_ID_RPM(4): // fsc0.in_ch4
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_4);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_4, reg_pwm_sampling_data_ch4);
            break;

        case PWM_ID_RPM(5): // fsc0.in_ch5
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_5);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_5, reg_pwm_sampling_data_ch5);
            break;

        case PWM_ID_RPM(6): // fsc0.in_ch6
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_6);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_6, reg_pwm_sampling_data_ch6);
            break;

        case PWM_ID_RPM(7): // fsc0.in_ch7
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_7);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_7, reg_pwm_sampling_data_ch7);
            break;

        case PWM_ID_RPM(8): // fsc0.in_ch8
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_8);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_8, reg_pwm_sampling_data_ch8);
            break;

        case PWM_ID_RPM(9): // fsc0.in_ch9
            CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_9);
            rpm = CTOP_CTRL_O24Ax_RdFd(FSC_CTRL, det_count_9, reg_pwm_sampling_data_ch9);
            break;

        default:
            rpm = -1;
            break;
    }

    return rpm;
}

static void o24_fan_hw_dump_regs(struct seq_file* m)
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
        UINT32 reg_base = O24_A0_FSC_CTRL_BASE;
        UINT32 reg_num = sizeof(FSC_CTRL_REG_O24A0_T) >> 2;

        for (i = 0; i < reg_num; i ++)
        {
            OS_RdReg(reg_base + (i << 2), &reg_val);
            seq_printf(m, "0x%08x: 0x%08x\n", reg_base + (i << 2), reg_val);
        }
    }

    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_65);  // fsc0.iomux
    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_66);  // fsc0.iomux
    CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_67);  // fsc0.iomux

    seq_printf(m, "\n");
    seq_printf(m, "IOMUX_CTRL_VD0 reg_dump\n");
    seq_printf(m, "IOMUX_CTRL_VD.pad_vd0_65 = 0x%08x\n", CTOP_CTRL_O24Ax_Rd(IOMUX_CTRL_VD0, pad_vd0_65));
    seq_printf(m, "IOMUX_CTRL_VD.pad_vd0_66 = 0x%08x\n", CTOP_CTRL_O24Ax_Rd(IOMUX_CTRL_VD0, pad_vd0_66));
    seq_printf(m, "IOMUX_CTRL_VD.pad_vd0_67 = 0x%08x\n", CTOP_CTRL_O24Ax_Rd(IOMUX_CTRL_VD0, pad_vd0_67));

    seq_printf(m, "\n");
    seq_printf(m, "FSC0:\n");

    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_op_mode_0);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_op_mode_1);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_op_mode_2);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, reg_pwm_det_en);

    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_gen_clk_0);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_duty_0);
    CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_gen_clk_0, reg_pwm_gen_clk_ch0, period[0]);
    CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_duty_0, reg_pwm_duty_ch0, duty[0]);

    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_gen_clk_1);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_duty_1);
    CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_gen_clk_1, reg_pwm_gen_clk_ch1, period[1]);
    CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_duty_1, reg_pwm_duty_ch1, duty[1]);

    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_gen_clk_2);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, pwm_duty_2);
    CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_gen_clk_2, reg_pwm_gen_clk_ch2, period[2]);
    CTOP_CTRL_O24Ax_Rd01(FSC_CTRL, pwm_duty_2, reg_pwm_duty_ch2, duty[2]);

    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_8);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_9);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_0);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_1);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_2);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_3);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_4);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_5);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_6);
    CTOP_CTRL_O24Ax_RdFL(FSC_CTRL, det_count_7);

    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio10_mux_sel, fan_mux[0]); // fsc0.out_ch0 (pwm0)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio11_mux_sel, fan_mux[1]); // fsc0.out_ch1 (pwm1)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_67, reg_pad_gpio12_mux_sel, fan_mux[2]); // fsc0.out_ch2 (pwm2)

    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio00_mux_sel, rpm_mux[0]); // fsc0.in_ch0 (rpm0)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio01_mux_sel, rpm_mux[1]); // fsc0.in_ch1 (rpm1)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_65, reg_pad_gpio02_mux_sel, rpm_mux[2]); // fsc0.in_ch2 (rpm2)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio03_mux_sel, rpm_mux[3]); // fsc0.in_ch3 (rpm3)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio04_mux_sel, rpm_mux[4]); // fsc0.in_ch4 (rpm4)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio05_mux_sel, rpm_mux[5]); // fsc0.in_ch5 (rpm5)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio06_mux_sel, rpm_mux[6]); // fsc0.in_ch6 (rpm6)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio07_mux_sel, rpm_mux[7]); // fsc0.in_ch7 (rpm7)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio08_mux_sel, rpm_mux[8]); // fsc0.in_ch8 (rpm8)
    CTOP_CTRL_O24Ax_Rd01(IOMUX_CTRL_VD0, pad_vd0_66, reg_pad_gpio09_mux_sel, rpm_mux[9]); // fsc0.in_ch9 (rpm9)


    // fsc0 report mux status
    for (i = 0; i < 3; i++)
    {
        seq_printf(m, "fsc0.mux.pwm(%d): %d\n", i, fan_mux[i]);
    }

    for (i = 0; i < 10; i++)
    {
        seq_printf(m, "fsc0.mux.rpm(%d): %d\n", i, rpm_mux[i]);
    }

    seq_printf(m, "\n");

    // fsc0 report active (enable/disable) status
    seq_printf(m, "fsc0.pwm_op_mode0: 0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, pwm_op_mode_0));
    seq_printf(m, "fsc0.pwm_op_mode1: 0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, pwm_op_mode_1));
    seq_printf(m, "fsc0.pwm_op_mode2: 0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, pwm_op_mode_2));
    seq_printf(m, "fsc0.pwm_det_en:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, reg_pwm_det_en));
    seq_printf(m, "\n");

    // fsc0 report duty & period of pwm0/1/2
    seq_printf(m, "fsc0.pwm0.period:  0x%08x\n", period[0]);
    seq_printf(m, "fsc0.pwm0.duty:    0x%08x\n", duty[0]);
    seq_printf(m, "fsc0.pwm1.period:  0x%08x\n", period[1]);
    seq_printf(m, "fsc0.pwm1.duty:    0x%08x\n", duty[1]);
    seq_printf(m, "fsc0.pwm2.period:  0x%08x\n", period[2]);
    seq_printf(m, "fsc0.pwm2.duty:    0x%08x\n", duty[2]);
    seq_printf(m, "\n");

    // fsc0 report RPM status
    seq_printf(m, "fsc0.rpm0.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_0));
    seq_printf(m, "fsc0.rpm1.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_1));
    seq_printf(m, "fsc0.rpm2.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_2));
    seq_printf(m, "fsc0.rpm3.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_3));
    seq_printf(m, "fsc0.rpm4.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_4));
    seq_printf(m, "fsc0.rpm5.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_5));
    seq_printf(m, "fsc0.rpm6.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_6));
    seq_printf(m, "fsc0.rpm7.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_7));
    seq_printf(m, "fsc0.rpm8.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_8));
    seq_printf(m, "fsc0.rpm9.count:   0x%08x\n", CTOP_CTRL_O24Ax_Rd(FSC_CTRL, det_count_9));
    seq_printf(m, "\n");
}

