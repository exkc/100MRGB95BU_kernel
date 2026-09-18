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

#ifndef _PWM_IMPL_H_
#define _PWM_IMPL_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/pwm.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define PWM_ID_FAN(x)   (0x46410a00|(x))
#define PWM_ID_RPM(x)   (0x52504d00|(x))

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define lg1k_pwm_error(format,args...)  DBG_PRINT( g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define lg1k_pwm_warn(format, args...)  DBG_PRINT( g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define lg1k_pwm_noti(format, args...)  DBG_PRINT( g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define lg1k_pwm_info(format, args...)  DBG_PRINT( g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define lg1k_pwm_debug(format,args...)  DBG_PRINT( g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)

#define lg1k_pwm_check_error(__checker,__if_action,fmt,args...)   \
                            __CHECK_IF_ERROR(__checker, lg1k_pwm_error, __if_action , fmt, ##args)

#define get_pwm_dev(lg1k_pwm, id)       ((id)<lg1k_pwm->chip_desc.npwm)? \
                                            &lg1k_pwm->chip_desc.dev_list[id]:NULL

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
struct lg1k_pwm;
struct lg1k_pwm_dev;

struct lg1k_pwm_callback
{
    void (*do_config)(struct lg1k_pwm_dev* my_dev, int period, int duty);
    void (*do_enable)(struct lg1k_pwm_dev* my_dev, bool en);

    int (*do_pm)(struct lg1k_pwm_dev* my_dev, char* command);
    void (*do_proc)(struct lg1k_pwm_dev* my_dev, struct seq_file* m, char* command);
};

struct lg1k_pwm_dev
{
    uint32_t hwpwm;         /* id */
    char*   name;           /* device alias */
    uint32_t pwm_id;        /* PWM_ID_xxx */

    uint32_t base_clk;      /* Hz */
    uint32_t max_hw_period; /* max register value for period */

    struct
    {
        bool configured;
        bool enabled;       /* latest "enable" status */
        uint32_t duty;      /* calculated hw duty */
        uint32_t period;    /* calculated hw period */
    }
    status;

    struct lg1k_pwm_callback* cb;
};

struct lg1k_pwm_chip_desc
{
    uint32_t npwm;
    struct lg1k_pwm_dev* dev_list;

    void (*do_proc)(struct lg1k_pwm_dev* my_dev, struct seq_file* m, char* command); // report status
};

struct lg1k_pwm
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
    struct pwm_chip* chip;
#else
    struct pwm_chip chip;
#endif
    struct lg1k_pwm_chip_desc chip_desc;
};

struct lg1k_pwm_hw_driver
{
    //void (*hw_init)(struct lg1k_pwm_dev* my_dev, bool en);
    void (*hw_config)(struct lg1k_pwm_dev* my_dev, int period, int duty);
    void (*hw_enable)(struct lg1k_pwm_dev* my_dev, bool en);
    int (*hw_get_rpm)(struct lg1k_pwm_dev* my_dev);
    void (*hw_dump_regs)(struct seq_file* m);
};

struct lg1k_pwm_hw_scanner
{
    uint32_t chip;
    struct lg1k_pwm_hw_driver* hw_driver;
    char* text;
};

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
struct lg1k_pwm_chip_desc lg1k_pwm_chip_config(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/
extern int g_lg1k_pwm_debug_fd;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

