/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/*
see the below JIRA to get the detail info abut PWM HW spec

M16P3:  http://clm.lge.com/issue/browse/SCDCRID-2943 (ID)
O20 :   http://clm.lge.com/issue/browse/SCDCRID-3067 (ID)
O22:    http://clm.lge.com/issue/browse/SCDCR-4364   (TV)
        http://clm.lge.com/issue/browse/SCDCRID-3357 (ID)
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
#if defined CHIP_NAME_o26
#define MAX_PWM_OUT_NUM 3
#define MAX_RPM_IN_NUM  10
#elif defined CHIP_NAME_o24
#define MAX_PWM_OUT_NUM 3
#define MAX_RPM_IN_NUM  10
#elif defined CHIP_NAME_o22
#define MAX_PWM_OUT_NUM 6
#define MAX_RPM_IN_NUM  20
#else
#define MAX_PWM_OUT_NUM 3
#define MAX_RPM_IN_NUM  10
#endif

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int lg1k_pwm_fan_configure(void);
void lg1k_pwm_fan_config(struct lg1k_pwm_dev* my_dev, int duty_val, int period_val);
void lg1k_pwm_fan_enable(struct lg1k_pwm_dev* my_dev, bool en);
int lg1k_pwm_fan_pm(struct lg1k_pwm_dev* my_dev, char* command);
void lg1k_pwm_fan_proc(struct lg1k_pwm_dev* my_dev, struct seq_file* m, char* command);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern struct lg1k_pwm_hw_driver o26_fan_hw_driver;
extern struct lg1k_pwm_hw_driver o24_fan_hw_driver;
extern struct lg1k_pwm_hw_driver o22_fan_hw_driver;
extern struct lg1k_pwm_hw_driver m19_fan_hw_driver;

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void lg1k_pwm_fan_dump_regs(struct seq_file* m);

static void dummy_fan_hw_config(struct lg1k_pwm_dev* my_dev, int period, int duty)
{
    PARAM_UNUSED(my_dev);
    PARAM_UNUSED(period);
    PARAM_UNUSED(duty);

    lg1k_pwm_noti("dummy driver. do nothing\n");
}

static void dummy_fan_hw_enable(struct lg1k_pwm_dev* my_dev, bool en)
{
    PARAM_UNUSED(my_dev);
    PARAM_UNUSED(en);

    lg1k_pwm_noti("dummy driver. do nothing\n");
}
static int  dummy_fan_hw_get_rpm(struct lg1k_pwm_dev* my_dev)
{
    PARAM_UNUSED(my_dev);
    return 0;
}

static void dummy_fan_hw_dump_regs(struct seq_file* m)
{
    PARAM_UNUSED(m);
}

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

static struct lg1k_pwm_hw_driver __attribute__((used)) dummy_fan_hw_driver =
{
    .hw_config = dummy_fan_hw_config,
    .hw_enable = dummy_fan_hw_enable,
    .hw_get_rpm = dummy_fan_hw_get_rpm,
    .hw_dump_regs = dummy_fan_hw_dump_regs,
};

static struct lg1k_pwm_hw_scanner fan_hw_scanner[] =
{
#ifdef INCLUDE_O26_CHIP_KDRV
    { LX_CHIP_O26, &o26_fan_hw_driver, "o26" },
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    { LX_CHIP_O24, &o24_fan_hw_driver, "o24" },
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
    { LX_CHIP_O22, &o22_fan_hw_driver, "o22" },
#endif
};

static struct lg1k_pwm_hw_driver* fan_hw_driver = NULL;

//static bool pwm_hw_inited = false;
//static unsigned int hw_cfg_mask = 0x0;

/*========================================================================================
    Implementation Group
========================================================================================*/
// Setting the initial state of the FAN driver is crucial for ensuring system stability and performance.
// By configuring the initial state, we can prevent the driver from behaving unexpectedly.
// However, in actual operating environments, setting the initial state during the boot process at the CMM level
// is the safest and most reliable method.
//
// for example, O24 chip driver has blank hw_init() handler and boot loader does CMM-level initialization.
//
int lg1k_pwm_fan_configure(void)
{
    if (!fan_hw_driver)
    {
        int i;
        bool found = false;

        for (i = 0; i < NELEMENTS(fan_hw_scanner); i++)
        {
            if (lx_chip() == fan_hw_scanner[i].chip)
            {
                lg1k_pwm_noti("fan hw(%s) driver detected.\n", fan_hw_scanner[i].text);
                fan_hw_driver = fan_hw_scanner[i].hw_driver;
                found = true;
            }
        }

        if (!found)
        {
            lg1k_pwm_error("fan hw driver not detected. use dummy hw driver.\n");
            fan_hw_driver = &dummy_fan_hw_driver;
        }
    }

    return RET_OK;
}

void lg1k_pwm_fan_config(struct lg1k_pwm_dev* my_dev, int duty_val, int period_val)
{
    if (fan_hw_driver && fan_hw_driver->hw_config)
    {
        fan_hw_driver->hw_config(my_dev, duty_val, period_val);
    }
}

void lg1k_pwm_fan_enable(struct lg1k_pwm_dev* my_dev, bool en)
{
    if (fan_hw_driver && fan_hw_driver->hw_enable)
    {
        fan_hw_driver->hw_enable(my_dev, en);
    }
}

int lg1k_pwm_fan_pm(struct lg1k_pwm_dev* my_dev, char* command)
{
#if 0

    // make pwm to re-initialize
    if (!strncmp(command, "restore", 7) || !strncmp(command, "resume", 6))
    {
        pwm_hw_inited = false;
        hw_cfg_mask = 0x0;
    }

#endif

    return 0;
}

static int lg1k_pwm_fan_get_rpm(struct lg1k_pwm_dev* my_dev)
{
    if (fan_hw_driver && fan_hw_driver->hw_get_rpm)
    {
        return fan_hw_driver->hw_get_rpm(my_dev);
    }
    else
    {
        return -1;
    }
}

void lg1k_pwm_fan_proc(struct lg1k_pwm_dev* my_dev, struct seq_file* m, char* command)
{
    if (!strncmp(command, "status", 6))
    {
        int rpm = lg1k_pwm_fan_get_rpm(my_dev);

        if (rpm >= 0)
        {
            seq_printf(m, "status.rpm: %d\n", rpm);
        }
    }
    else if (!strncmp(command, "chip_status", 11))
    {
        seq_printf(m, "chip.num_pwm_out: %d\n", MAX_PWM_OUT_NUM);
        seq_printf(m, "chip.num_rpm_in: %d\n", MAX_RPM_IN_NUM);
        seq_printf(m, "\n");
    }
    else if (!strncmp(command, "dump_regs", 9))
    {
        lg1k_pwm_fan_dump_regs(m);
    }
}

static void lg1k_pwm_fan_dump_regs(struct seq_file* m)
{
    if (fan_hw_driver && fan_hw_driver->hw_dump_regs)
    {
        fan_hw_driver->hw_dump_regs(m);
    }
}

