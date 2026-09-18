#include <linux/sysrq.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/module.h>
#include <linux/workqueue.h>

extern void do_sysrq_print_klog(void);

static void sysrq_handle_print_klog(u8 key)
{
	do_sysrq_print_klog();
}
static struct sysrq_key_op sysrq_printklog_op = {
	.handler	= sysrq_handle_print_klog,
	.help_msg	= "print-kernel-log-buffer(y)",
	.action_msg	= "print-kernel-log-buffer",
	.enable_mask	= SYSRQ_ENABLE_LOG,
};

static int __init sysrq_klog_init(void)
{
	return register_sysrq_key('y', &sysrq_printklog_op);
}
device_initcall(sysrq_klog_init);

static void run_sysrq_emergency_shell(struct work_struct *work);

static DECLARE_WORK(sysrq_shell_work, run_sysrq_emergency_shell);

static void run_sysrq_emergency_shell(struct work_struct *work)
{
	static char *argv[] = { "/usr/sbin/sysrq_shell", NULL };
	static char *envp[] = { "HOME=/", "TERM=linux",
		"PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};

	int ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
	pr_info("call_usermodehelper returned: %d\n", ret);
}

static void sysrq_handle_emergency_shell(u8 key)
{
    schedule_work(&sysrq_shell_work);
}

static struct sysrq_key_op sysrq_shell_op = {
	.handler	= sysrq_handle_emergency_shell,
	.help_msg	= "launch-shell-service(x)",
	.action_msg	= "launch-shell-service",
	.enable_mask	= SYSRQ_ENABLE_LOG,
};

static int __init sysrq_shell_init(void)
{
	return register_sysrq_key('x', &sysrq_shell_op);
}

device_initcall(sysrq_shell_init);
