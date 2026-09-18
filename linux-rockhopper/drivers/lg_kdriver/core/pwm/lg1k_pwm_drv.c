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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "lg1k_pwm_impl.h"
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
void lg1k_pwm_preinit(void);
void lg1k_pwm_cleanup(void);
int lg1k_pwm_init(void);

extern int lg1k_pwm_fan_configure(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
int g_lg1k_pwm_debug_fd;

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct lg1k_pwm* g_lg1k_pwm = NULL;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void lg1k_pwm_init_proc(void);

static int lg1k_pwm_pm_function(struct device* dev, char* command)
{
    int i;
    bool restore_hw = false;
    struct lg1k_pwm_dev* my_dev;
    struct lg1k_pwm_callback* my_cb;
    struct lg1k_pwm* lg1k_pwm = dev_get_drvdata(dev);

    if (!strncmp(command, "resume", 6) || !strncmp(command, "restore", 7))
    {
        restore_hw = true;
    }

    lg1k_pwm_noti("pm_func=%s, restore_hw=%d\n", command, restore_hw);

    //my_cb->do_pm(NULL, command);

    for (i = 0; i < lg1k_pwm->chip_desc.npwm; i++)
    {
        my_dev = get_pwm_dev(lg1k_pwm, i);

        if (my_dev)
        {
            my_cb = my_dev->cb;

            my_cb->do_pm(my_dev, command);

            if (restore_hw)
            {
                struct pwm_device p;
                p.hwpwm = my_dev->hwpwm;

                lg1k_pwm_noti("name=%s configured=%d, enabled=%d\n",
                              my_dev->name,
                              my_dev->status.configured,
                              my_dev->status.enabled);

                if (my_dev->status.configured)
                {
                    my_cb->do_config(my_dev, my_dev->status.period, my_dev->status.duty);

                    if (my_dev->status.enabled)
                    {
                        my_cb->do_enable(my_dev, true);
                    }
                }
            }
        }

        // 추후 필요시 pm prepare, pm complete 체제로 바꾸도록 한다.
    }

    return 0;
}

static int lg1k_pwm_freeze(struct device* dev)
{
    return lg1k_pwm_pm_function(dev, "freeze");
}

static int lg1k_pwm_thaw(struct device* dev)
{
    return lg1k_pwm_pm_function(dev, "thaw");
}

static int lg1k_pwm_restore(struct device* dev)
{
    return lg1k_pwm_pm_function(dev, "restore");
}

static int lg1k_pwm_suspend(struct device* dev)
{
    return lg1k_pwm_pm_function(dev, "suspend");
}

static int lg1k_pwm_resume(struct device* dev)
{
    return lg1k_pwm_pm_function(dev, "resume");
}

static int lg1k_pwm_runtime_resume(struct device* dev)
{
    /* do nothing */ return 0;
}

static int lg1k_pwm_runtime_suspend(struct device* dev)
{
    /* do nothing */ return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
// see include/linux/pwm.h
#else
static inline struct lg1k_pwm* pwmchip_get_drvdata(struct pwm_chip* pc)
{
    return container_of(pc, struct lg1k_pwm, chip);
}
#endif

static int __attribute__((used)) lg1k_pwm_enable(struct pwm_chip* pc, struct pwm_device* p)
{
    struct lg1k_pwm* lg1k_pwm = (struct lg1k_pwm*)pwmchip_get_drvdata(pc);
    struct lg1k_pwm_dev* my_dev = get_pwm_dev(lg1k_pwm, p->hwpwm);
    struct lg1k_pwm_callback* my_cb = my_dev->cb;

    lg1k_pwm_check_error(!my_dev, return -1, "invalid pwm_id(%d)\n", p->hwpwm);
    lg1k_pwm_noti("pwm(%s) enable hwid=%d\n", my_dev->name, p->hwpwm);

    if (my_cb && my_cb->do_enable)
    {
        my_cb->do_enable(my_dev, true);
    }

    my_dev->status.enabled = true;

    //my_cb->do_config(my_dev, my_dev->status.period, my_dev->status.duty);

    return 0;
}

static void __attribute__((used)) lg1k_pwm_disable(struct pwm_chip* pc, struct pwm_device* p)
{
    struct lg1k_pwm* lg1k_pwm = (struct lg1k_pwm*)pwmchip_get_drvdata(pc);
    struct lg1k_pwm_dev* my_dev = get_pwm_dev(lg1k_pwm, p->hwpwm);
    //struct lg1k_pwm_callback* my_cb = lg1k_pwm->chip_desc.cb;
    struct lg1k_pwm_callback* my_cb = my_dev->cb;

    lg1k_pwm_check_error(!my_dev, return, "invalid pwm_id(%d)\n", p->hwpwm);
    lg1k_pwm_noti("pwm(%s) disable hwid=%d\n", my_dev->name, p->hwpwm);

    if (my_cb && my_cb->do_enable)
    {
        my_cb->do_enable(my_dev, false);
    }

    my_dev->status.enabled = false;
}

static int __attribute__((used)) lg1k_pwm_config(struct pwm_chip* pc, struct pwm_device* p, int duty_ns, int period_ns)
{
    struct lg1k_pwm* lg1k_pwm = (struct lg1k_pwm*)pwmchip_get_drvdata(pc);
    struct lg1k_pwm_dev* my_dev = get_pwm_dev(lg1k_pwm, p->hwpwm);
    //struct lg1k_pwm_callback* my_cb = lg1k_pwm->chip_desc.cb;
    struct lg1k_pwm_callback* my_cb = my_dev->cb;

    uint32_t hw_period;
    uint32_t hw_duty;

    if (p->hwpwm >= lg1k_pwm->chip_desc.npwm)
    {
        lg1k_pwm_error("not supported pwm dev=%d >= npwm=%d\n",
                       p->hwpwm, lg1k_pwm->chip_desc.npwm);
    }

    lg1k_pwm_check_error(!my_dev, return -1, "invalid pwm_id(%d)\n", p->hwpwm);

    lg1k_pwm_noti("pwm(%s) duty_ns = %d, period_ns = %d ",
                  my_dev->name, duty_ns, period_ns);

#if 0

    // 허용가능한 최대 period 주기값을 넘을 수 없다.
    if (period_ns > my_dev->max_period_ns)
    {
        lg1k_pwm_error("not supported period_ns=%d > max=%d\n",
                       period_ns, my_dev->max_period_ns);
        return -EINVAL;
    }

#endif

    /* perioid 가 바뀔때, 필요한 동작을 할것 */
    if (pwm_get_period(p) != period_ns)
    {
        /* do nothing */
    }

    // base_clk 정보를 바탕으로 HW 에 설정할 period 값을 계산한다.
    // 이값은 duty 값의 최대치로 사용된다.
    hw_period = (uint32_t)((long)period_ns * my_dev->base_clk / NSEC_PER_SEC);
    hw_duty = (uint32_t)((long)hw_period * duty_ns / period_ns);

    if (hw_period > my_dev->max_hw_period)
    {
        lg1k_pwm_error("invalid hw period(0x%04x) > max(0x%04x)\n", hw_period, my_dev->max_hw_period);
        return -EINVAL;
    }

    if (hw_duty > hw_period)
    {
        lg1k_pwm_error("invalid hw duty(0x%4x) > hw period(0x%04x). cut duty value\n", hw_duty, hw_period);
        hw_duty = hw_period;
    }

    lg1k_pwm_noti("pwm(%s) hw_period=0x%04x, hw_duty=0x%04x\n",
                  my_dev->name, hw_period, hw_duty);

    if (my_cb && my_cb->do_config)
    {
        my_cb->do_config(my_dev, hw_period, hw_duty);
    }

    my_dev->status.period = hw_period;
    my_dev->status.duty = hw_duty;
    my_dev->status.configured = true;

    return 0;
}

static int __attribute__((used)) lg1k_pwm_apply(struct pwm_chip* pc, struct pwm_device* pwm,
        const struct pwm_state* state)
{
    int s;

    if (pc == NULL || pwm == NULL || state == NULL)
    {
        pr_err("Invalid parameters\n");
        return -1; // 오류 코드 반환
    }

    // PWM 상태 적용
    pwm->state.duty_cycle = state->duty_cycle;
    pwm->state.period = state->period;
    pwm->state.enabled = state->enabled;

    if (state->enabled)
    {
        s = lg1k_pwm_config(pc, pwm, state->duty_cycle, state->period);

        if (unlikely(s))
        {
            return -EINVAL;
        }

        s = lg1k_pwm_enable(pc, pwm);

        if (unlikely(s))
        {
            return -EINVAL;
        }

        lg1k_pwm_noti("PWM enabled: duty=%d, period=%d\n",
                      (int)pwm->state.duty_cycle, (int)pwm->state.period);
    }
    else
    {
        lg1k_pwm_disable(pc, pwm);

        lg1k_pwm_noti("PWM disabled\n");
    }

    return 0;
}

static const struct pwm_ops lg1k_pwm_ops =
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
    .apply = lg1k_pwm_apply,
#else
    .config = lg1k_pwm_config,
    .enable = lg1k_pwm_enable,
    .disable = lg1k_pwm_disable,
#endif
};

static int lg1k_pwm_probe(struct platform_device* pdev)
{
    int rc;
    struct lg1k_pwm* lg1k_pwm;
    struct pwm_chip* chip;
    struct lg1k_pwm_chip_desc chip_desc;

    chip_desc = lg1k_pwm_chip_config();

    // lg1k_pwm 을  alloc 하고 필요한 변수를 초기화한다.
    lg1k_pwm = devm_kzalloc(&pdev->dev, sizeof(struct lg1k_pwm), GFP_KERNEL);

    if (IS_ERR(lg1k_pwm))
    {
        return -ENOMEM;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
    // devm_pwmchip_alloc 을 통해 pwm_chip 을 초기화해야 한다.
    // lg1k_pwm* 은 chip 의 pwmchip_get_drvdata() 로 얻어오는 구조가 되어야 한다.

    chip = devm_pwmchip_alloc(&pdev->dev, chip_desc.npwm, sizeof(struct lg1k_pwm));

    if (IS_ERR(chip))
    {
        return -ENOMEM;
    }

    lg1k_pwm = (struct lg1k_pwm*)pwmchip_get_drvdata(chip);
    lg1k_pwm->chip = chip;
#else
    chip = &lg1k_pwm->chip;

    chip->dev = &pdev->dev;
    chip->base = 0;
    chip->npwm = chip_desc.npwm;
#endif
    chip->ops = &lg1k_pwm_ops;
    lg1k_pwm->chip_desc = chip_desc;

    // struct lg1k_pwm 설정을 통해 pwm 관련 모든 값을 접근할 수 있도록 한다.
    platform_set_drvdata(pdev, lg1k_pwm);

    // proc 정보 획득 목적으로 lg1k_pwm 을 저장한다. 다른 방법으로 재구현 할것
    g_lg1k_pwm = lg1k_pwm;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
    rc = pwmchip_add(lg1k_pwm->chip);
#else
    rc = pwmchip_add(&lg1k_pwm->chip);
#endif

    lg1k_pwm_noti("pwmchip_add rc=%d\n", rc);

    return rc;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void lg1k_pwm_remove(struct platform_device* pdev)
#else
static int lg1k_pwm_remove(struct platform_device* pdev)
#endif
{
    struct lg1k_pwm* lg1k_pwm = platform_get_drvdata(pdev);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
    pwmchip_remove(lg1k_pwm->chip);
#else
    pwmchip_remove(&lg1k_pwm->chip);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
    // void
#else
    return 0;
#endif
}

static void  lg1k_pwm_release(struct device* dev)
{
    // do nothing
}

/*========================================================================================
    Implementation Group
========================================================================================*/
static struct dev_pm_ops lg1k_pwm_pm_ops =
{
    .freeze     = lg1k_pwm_freeze,      // SNAPSHOT suspend
    .thaw       = lg1k_pwm_thaw,        // SNAPSHOT resume right after making
    .restore_early = lg1k_pwm_restore,  // SNAPSHOT boot

    .suspend    = lg1k_pwm_suspend,     // IBOOT suspend
    .resume     = lg1k_pwm_resume,      // IBOOT boot(resume)

    .runtime_suspend = lg1k_pwm_runtime_suspend,
    .runtime_resume = lg1k_pwm_runtime_resume,
};

static struct platform_driver lg1k_pwm_driver =
{
    .probe = lg1k_pwm_probe,
    .remove = lg1k_pwm_remove,
    .driver = {
        .name = "lg1k-pwm",
        .pm = &lg1k_pwm_pm_ops,
    },
};

static struct platform_device lg1k_pwm_device =
{
    .name = "lg1k-pwm",
    .id = -1,
    .dev = {
        .release = lg1k_pwm_release,
    },
};


void lg1k_pwm_preinit(void)
{
    // do nothing
}

void lg1k_pwm_cleanup(void)
{
    // do nothing
}

int lg1k_pwm_init(void)
{
    g_lg1k_pwm_debug_fd = DBG_OPEN("lg1k-pwm");

    if (g_lg1k_pwm_debug_fd >= 0)
    {
        OS_DEBUG_EnableModuleByIndex(g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED);
        OS_DEBUG_EnableModuleByIndex(g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW);
        OS_DEBUG_EnableModuleByIndex(g_lg1k_pwm_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_YELLOW);
    }

    if (platform_driver_register(&lg1k_pwm_driver) < 0)
    {
        pr_err("pwm platform driver failed\n");
    }

    if (platform_device_register(&lg1k_pwm_device) != 0)
    {
        pr_err("pmw platform device failed\n");
    }

    /* enable PM runtime */
    pm_runtime_set_active(&lg1k_pwm_device.dev);
    pm_runtime_enable(&lg1k_pwm_device.dev);
    /* set control mode to "on" not "auto" */
    pm_runtime_forbid(&lg1k_pwm_device.dev);

    lg1k_pwm_init_proc();

    /* configure FAN pwm driver */
    if (lg1k_pwm_fan_configure() != RET_OK)
    {
        pr_err("pmw fan configure error\n");
    }

    /* TODO: initialize another pwm driver */

    lg1k_pwm_noti("lg1k_pwm driver initialized\n");

    return 0;
}

/*========================================================================================
    Implementation Group
========================================================================================*/
enum
{
    PROC_ID_PM_TEST = 0,
    PROC_ID_MAX
};

#ifdef OS_API_VERSION
static int lg1k_pwm_proc_report_status(struct seq_file* m, void* data);
#else
static void lg1k_pwm_proc_report_status(struct seq_file* m, void* data);
#endif

#ifdef OS_API_VERSION
// see proc_util.h
#else
// legacy proc usage

/** sequential reader helper with dynamic data args
 *
 * ex)
        static void lg1k_pwm_proc_report_status(struct seq_file *m, void* data);
        __os_proc_seq_reader_define(lg1k_pwm_proc_status_fops, lg1k_pwm_proc_report_status)

        dir_entry = proc_mkdir(my_dev->name, lg1k_pwm_proc_dir);
        proc_create_data("status", 0440, dir_entry, &my_proc_status_fops, my_dev);
 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
#define get_pde_data(a) pde_data(a)
#else
#define get_pde_data(a) PDE_DATA(a)
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))

#define __os_proc_seq_reader_define(fops,readfn) \
 static int print_##fops(struct seq_file* m, void* v) \
 { \
     void* data = m->private; \
     readfn(m, data); return 0;\
 }\
 static int open_##fops(struct inode *n, struct file *fl)\
 {\
     void* data = get_pde_data(n);\
     return single_open(fl, print_##fops, data); \
 }\
 \
 const static struct proc_ops fops = { \
     .proc_open       = open_##fops, \
     .proc_read       = seq_read, \
     .proc_lseek      = seq_lseek, \
     .proc_release    = single_release, \
 };

#else

#define __os_proc_seq_reader_define(fops,readfn) \
 static int print_##fops(struct seq_file* m, void* v) \
 { \
     void* data = m->private; \
     readfn(m, data); return 0;\
 }\
 static int open_##fops(struct inode *n, struct file *fl)\
 {\
     void* data = get_pde_data(n);\
     return single_open(fl, print_##fops, data); \
 }\
 \
 const static struct file_operations fops = { \
     .open       = open_##fops, \
     .read       = seq_read, \
     .llseek     = seq_lseek, \
     .release    = single_release, \
 };

#endif

__os_proc_seq_reader_define(lg1k_pwm_proc_status_fops, lg1k_pwm_proc_report_status)

const static OS_PROC_DESC_TABLE_T _g_pwm_device_proc_table[] =
{
    { "pmtest", PROC_ID_PM_TEST, OS_PROC_FLAG_WRITE},
    { NULL, PROC_ID_MAX, 0 }
};

static struct proc_dir_entry* lg1k_pwm_proc_dir;

#endif

#ifdef OS_API_VERSION
static int sys_pwm_proc_reader_func(UINT32 procId, char* buffer, int size, void* data)
#else
static int sys_pwm_proc_reader_func(UINT32 procId, char* buffer)
#endif
{
    return 0;
}

#ifdef OS_API_VERSION
static int sys_pwm_proc_writer_func(UINT32 procId, char* command, int size, void* data)
#else
static int sys_pwm_proc_writer_func(UINT32 procId, char* command)
#endif
{
    switch (procId)
    {
        case PROC_ID_PM_TEST:
        {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0))
            lg1k_pwm_pm_function(&g_lg1k_pwm->chip->dev, command);
#else
            lg1k_pwm_pm_function(g_lg1k_pwm->chip.dev, command);
#endif
        }
        break;
    }

    return strlen(command);
}


static void lg1k_pwm_init_proc(void)
{
    int i;
    struct lg1k_pwm_dev* my_dev;

#ifdef OS_API_VERSION

    struct os_proc* base_proc = os_proc_create_dir(NULL, "pwm", sys_pwm_proc_reader_func, sys_pwm_proc_writer_func);

    os_proc_create_seq_file(base_proc, "status", lg1k_pwm_proc_report_status, NULL, NULL);

    for (i = 0; i < g_lg1k_pwm->chip_desc.npwm; i++)
    {
        struct os_proc* cur_proc;

        my_dev = get_pwm_dev(g_lg1k_pwm, i);
        lg1k_pwm_check_error(!my_dev, return, "invalid pwm_id(%d)\n", i);

        cur_proc = os_proc_create_dir(base_proc, my_dev->name, NULL, NULL);
        os_proc_create_seq_file(cur_proc, "status", lg1k_pwm_proc_report_status, NULL, my_dev);
    }

#else
    // legacy proc usage
    struct proc_dir_entry* dir_entry;

    lg1k_pwm_proc_dir = OS_PROC_CreateEntry("pwm", OS_PROC_GetBaseEntry(),
                                            (OS_PROC_DESC_TABLE_T*)_g_pwm_device_proc_table,
                                            sys_pwm_proc_reader_func,
                                            sys_pwm_proc_writer_func);

    proc_create_data("status", 0440, lg1k_pwm_proc_dir, &lg1k_pwm_proc_status_fops, NULL);

    for (i = 0; i < g_lg1k_pwm->chip_desc.npwm; i++)
    {
        my_dev = get_pwm_dev(g_lg1k_pwm, i);
        lg1k_pwm_check_error(!my_dev, return, "invalid pwm_id(%d)\n", i);

        dir_entry = proc_mkdir(my_dev->name, lg1k_pwm_proc_dir);
        proc_create_data("status", 0440, dir_entry, &lg1k_pwm_proc_status_fops, my_dev);

        lg1k_pwm_noti("create proc pwm/%s\n", my_dev->name);
    }

#endif
}

#ifdef OS_API_VERSION
static int lg1k_pwm_proc_report_status(struct seq_file* m, void* data)
#else
static void lg1k_pwm_proc_report_status(struct seq_file* m, void* data)
#endif
{
    struct lg1k_pwm_dev* my_dev = (struct lg1k_pwm_dev*)data;
    //struct lg1k_pwm_callback* my_cb = g_lg1k_pwm->chip_desc.cb;

    if (my_dev)
    {
        struct lg1k_pwm_callback* my_cb = my_dev->cb;

        seq_printf(m, "name: %s\n", my_dev->name);
        seq_printf(m, "pwm_id: 0x%08x\n", my_dev->pwm_id);
        seq_printf(m, "base_clk: %d\n",  my_dev->base_clk);
        seq_printf(m, "max_hw_period: %d\n", my_dev->max_hw_period);
        seq_printf(m, "status.enabled: %d\n", my_dev->status.enabled);
        seq_printf(m, "status.period: %d (0x%x)\n", my_dev->status.period, my_dev->status.period);
        seq_printf(m, "status.duty: %d (0x%x)\n", my_dev->status.duty, my_dev->status.duty);

        if (my_cb && my_cb->do_proc)
        {
            my_cb->do_proc(my_dev, m, "status");
        }
    }
    else
    {
        seq_printf(m, "npwm: %d\n", g_lg1k_pwm->chip_desc.npwm);

        if (g_lg1k_pwm->chip_desc.do_proc)
        {
            g_lg1k_pwm->chip_desc.do_proc(NULL, m, "chip_status");
            g_lg1k_pwm->chip_desc.do_proc(NULL, m, "dump_regs");
        }
    }

#ifdef OS_API_VERSION
    return 0;
#endif
}

