
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/seq_file.h>
#include <linux/version.h>
#include <asm/uaccess.h>

#include "module/adec_module_list.h"
#include "imc/cmd/module_cmd_debug.h"
#include "kaimc.h"
#include "hal/hal.h"

#include "ipc_regs.h"
#include "reg_peri_ctrl.h"
#include "reg_dsp_ctrl.h"
#include "proc.h"
#include "logmsg.h"
#include "dsp_control.h"

#include "logm.h"

logm_define (aproc, log_level_noti);

#define trace(fmt,args...)	logm_trace(aproc,fmt,##args)
#define debug(fmt,args...)	logm_debug(aproc,fmt,##args)
#define info(fmt,args...)	logm_info(aproc,fmt,##args)
#define noti(fmt,args...)	logm_noti(aproc,fmt,##args)
#define error(fmt,args...)	logm_error(aproc,fmt,##args)

static int got_a_line (char *line, int (*send_cmd) (int, char **))
{
    char *argv[10];
    int argc;

    debug ("user command, %p, %s\n", line, line);

    argc = 0;
    while (line != NULL && argc < (ARRAY_SIZE (argv) - 1))
    {
        argv[argc++] = strsep (&line, " \t");
    }
    argv[argc] = NULL;

    return send_cmd (argc, argv);
}

static ssize_t debug_write (struct file *file, const char __user * buf, size_t size, loff_t * off)
{
    char *tmp, *p;
    int ret;
    int a;

    if (*off != 0)
        return -EINVAL;

    tmp = kmalloc (size + 1, GFP_KERNEL);
    if (!tmp)
        return -ENOMEM;

    ret = copy_from_user (tmp, buf, size);
    if (ret)
    {
        ret = -EFAULT;
        goto done;
    }
    tmp[size] = 0;

    p = tmp;
    debug ("buffer %p\n", p);
    for (a = 0; a < size; a++)
    {
        if (tmp[a] != '\n' && tmp[a] != 0)
            continue;

        debug ("got line break at %p\n", tmp + a);
        tmp[a] = 0;
        if (*p)
        {
            ret = got_a_line (p, file->private_data);
            if (ret < 0)
                goto done;
        }

        p = tmp + a + 1;
    }
    ret = size;

  done:
    kfree (tmp);

    return ret;
}

static int debug_open (struct inode *inode, struct file *file)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    file->private_data = pde_data (inode);
#else
    file->private_data = PDE_DATA (inode);
#endif
    if (!file->private_data)
    {
        error ("no function\n");
        return -EINVAL;
    }

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
const struct proc_ops aaudio_args_fops = {
    .proc_open = debug_open,
    .proc_write = debug_write,
};
#else
struct file_operations aaudio_args_fops = {
    .open = debug_open,
    .write = debug_write,
};
#endif

static int got_a_line_arg (char *line, struct aaudio_args_arg *arg)
{
    char **argv, *p;
    int argc;
    int i;
    int ret;

    for (argc = 0, p = line; p && *p; p = strpbrk (p + 1, " \t"), argc++);
    debug ("user command, argc %d, %p, \"%s\"\n", argc, line, line);

    argv = kmalloc (sizeof (char *) * (argc + 1), GFP_KERNEL);
    if (!argv)
        return -ENOMEM;

    for (i = 0, p = line; i < argc && p != NULL; i++)
    {
        argv[i] = strsep (&p, " \t");
        debug ("arg%d. \"%s\"\n", i, argv[i]);
    }
    argv[i] = NULL;

    ret = arg->callback (arg->arg, argc, argv);
    kfree (argv);
    return ret;
}

static ssize_t debug_write_arg (struct file *file, const char __user * buf, size_t size,
    loff_t * off)
{
    char *tmp, *p;
    int ret;
    int a;

    if (*off != 0)
        return -EINVAL;

    tmp = kmalloc (size + 1, GFP_KERNEL);
    if (!tmp)
        return -ENOMEM;

    ret = copy_from_user (tmp, buf, size);
    if (ret)
    {
        ret = -EFAULT;
        goto done;
    }
    tmp[size] = 0;

    p = tmp;
    debug ("buffer %p\n", p);
    for (a = 0; a < size; a++)
    {
        if (tmp[a] != '\n' && tmp[a] != 0)
            continue;

        debug ("got line break at %p\n", tmp + a);
        tmp[a] = 0;
        if (*p)
        {
            ret = got_a_line_arg (p, (struct aaudio_args_arg *) file->private_data);
            if (ret < 0)
                goto done;
        }

        p = tmp + a + 1;
    }
    ret = size;

  done:
    kfree (tmp);

    return ret;
}

static int debug_show_arg (struct seq_file *m, void *data)
{
    struct aaudio_args_arg *arg = m->private;

    return arg->show (arg->arg, m);
}

static struct file_operations arg_show_fops = {
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
};

static int debug_open_arg (struct inode *inode, struct file *file)
{

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    struct aaudio_args_arg *arg = pde_data (inode);
#else
    struct aaudio_args_arg *arg = PDE_DATA (inode);
#endif
    if (file->f_mode & FMODE_READ)
    {
        int ret;

        file->f_mode &= ~FMODE_PWRITE;
        if (arg->show)
        {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
            ret = single_open (file, debug_show_arg, pde_data (inode));
#else
            ret = single_open (file, debug_show_arg, PDE_DATA (inode));
#endif
	    file->f_op = &arg_show_fops;
        }
        else if (arg->read_fops)
        {
            ret = arg->read_fops->open (inode, file);
            if (ret < 0)
                return ret;
            file->f_op = arg->read_fops;
        }
        else
            return -EPERM;

        return ret;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    file->private_data = pde_data (inode);
#else
    file->private_data = PDE_DATA (inode);
#endif
    if (!file->private_data)
    {
        error ("no function\n");
        return -EINVAL;
    }

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
const struct proc_ops aaudio_args_arg_fops = {
    .proc_open = debug_open_arg,
    .proc_write = debug_write_arg,
};
#else
struct file_operations aaudio_args_arg_fops = {
    .open = debug_open_arg,
    .write = debug_write_arg,
};
#endif

struct proc_dir_entry *aproc_root;

static int set_logmask (int argc, char **argv)
{
    int dspnum;
    ADEC_MODULE_ID target;
    DbgCmdMessageLevel param = { 0, };

    if (argc <= 2)
    {
        error ("too few arguments, %d. <dsp_num> <log_module> <level>\n", argc);
        return -EINVAL;
    }

    dspnum = simple_strtol (argv[0], NULL, 0);
    strncpy (param.name, argv[1], sizeof (param.name));
    param.name[sizeof (param.name) - 1] = 0;
    param.level = simple_strtol (argv[2], NULL, 0);
    info ("set message level for dsp%d. \"%s\":%d\n", dspnum, param.name, param.level);

    switch (dspnum)
    {
        default:
        case 0:
            target = ADEC_MODULE_DBG_DSP0;
            break;

        case 1:
            target = ADEC_MODULE_DBG_DSP1;
            break;

        case 2:
            target = ADEC_MODULE_DBG_DSP2;
            break;

        case 3:
            target = ADEC_MODULE_DBG_DSP3;
            break;
    }

    aimc_send_command (NULL, DBG_CMD_MESSAGE_LEVEL, 0, target, &param, sizeof (param));

    return 0;
}

enum call_param_type
{
    param_arg,
    param_funcv,
};

static int send_call_param (int dspnum, const char *str, enum call_param_type type)
{
    DbgCmdCallFunction param = { 0, };
    ADEC_MODULE_ID target;

    strncpy (param.str, str, sizeof (param.str));
    param.str[sizeof (param.str) - 1] = 0;
    switch (type)
    {
        default:
        case param_arg:
            param.type = call_type_arg_int;
            break;

        case param_funcv:
            param.type = call_type_functionv;
            break;
    }

    switch (dspnum)
    {
        default:
        case 0:
            target = ADEC_MODULE_DBG_DSP0;
            break;

        case 1:
            target = ADEC_MODULE_DBG_DSP1;
            break;

        case 2:
            target = ADEC_MODULE_DBG_DSP2;
            break;

        case 3:
            target = ADEC_MODULE_DBG_DSP3;
            break;
    }

    info ("set %s \"%s\" at dsp%d\n", type == param_arg ? "arg" : "func", str, dspnum);
    aimc_send_command (NULL, DBG_CMD_CALL_FUNCTION, 0, target, &param, sizeof (param));

    return 0;
}

static int send_call (int dspnum, char *cmdline)
{
    int argc;
    char *p;

    info ("call \"%s\"\n", cmdline);

    /* skip initial space */
    while (*cmdline && *cmdline == ' ')
        cmdline++;

    /* count argc */
    p = cmdline;
    argc = 0;
    while (*p != 0)
    {
        bool eos;
        char *as;

        argc++;
        as = p;

        /* search end of text */
        while (*p && *p != ' ')
            p++;

        eos = false;
        if (*p == 0)
            eos = true;

        *p = 0;
        if (argc > 1)
            send_call_param (dspnum, as, param_arg);

        if (eos)
            break;
        p++;

        /* skip space */
        while (*p && *p == ' ')
            p++;
    }

    if (*cmdline)
        send_call_param (dspnum, cmdline, param_funcv);

    return 0;
}

int aud_call_funcsv (int dspnum, const char *fmt, va_list vargs)
{
    char *cmd, *p;

    cmd = kvasprintf (GFP_KERNEL, fmt, vargs);
    if (!cmd)
    {
        error ("no mem for %s\n", fmt);
        return -ENOMEM;
    }

    info ("call functions \"%s\"\n", cmd);

    p = cmd;
    while (true)
    {
        char *n;

        n = strchr (p, ';');
        if (n)
            *n = 0;

        send_call (dspnum, p);

        if (!n)
            break;

        p = n + 1;
    }

    kfree (cmd);

    return 0;
}

int aud_call_funcs (int dspnum, const char *fmt, ...)
{
    int ret;
    va_list vargs;

    va_start (vargs, fmt);
    ret = aud_call_funcsv (dspnum, fmt, vargs);
    va_end (vargs);

    return ret;
}

static int call_funcv (int argc, const char **argv)
{
    int dspnum;
    int i;

    if (argc <= 1)
    {
        error ("too few arguments, %d. <dsp_num> <func_name> [<arg> ...]\n", argc);
        return -EINVAL;
    }

    dspnum = simple_strtol (argv[0], NULL, 0);

    for (i = 2; i < argc; i++)
    {
        info ("set argument %d, %s at dsp%d\n", i - 2, argv[i], dspnum);
        send_call_param (dspnum, argv[i], param_arg);
    }

    info ("call functionv %s() at dsp%d\n", argv[1], dspnum);
    return send_call_param (dspnum, argv[1], param_funcv);
}

int aud_send_irq_cmd (int dsp, int cmd)
{
    unsigned int ipc_off = 0;

    switch (dsp)
    {
        case 0:
        case 1:
        case 2:
#if (NUM_OF_DSP >= 4)
        case 3:
#endif
            ipc_off = AUD_IPCOFFS_IRQ_COMMAND_DSP0 + (dsp * 4);
            break;
        default:
            return 0;
    }

    AUD_IPCREG_OFFS (ipc_off) = cmd;

    if (cmd != 0)
        aimc_send_irq (dsp);

    return 0;
}

static int send_irq_cmd (int argc, const char **argv)
{
    int dsp;
    int cmd;

    if (argc <= 1)
    {
        error ("too few arguments, %d. <dsp_num> <command>\n", argc);
        return -EINVAL;
    }

    dsp = simple_strtol (argv[0], NULL, 0);
    if (dsp < 0 || dsp >= aud_hal_get_number_of_dsp ())
    {
        error ("invalid dsp number (%d)\n", dsp);
        return -1;
    }
    cmd = simple_strtol (argv[1], NULL, 0);

    return aud_send_irq_cmd (dsp, cmd);

}

static void reg_dump (struct seq_file *file, unsigned int *addr, unsigned int size)
{
    int i;

    for (i = 0; i < size / 4;)
    {
        if (i % 8 == 0)
            seq_printf (file, "%08x:", i * 4);
        seq_printf (file, " %08x", addr[i]);
        i++;
        if (i % 8 == 0)
            seq_printf (file, "\n");
    }
    if (i % 8 != 0)
        seq_printf (file, "\n");
}

#ifdef _LNX_
static void reg_dump_show_addr (struct seq_file *file, unsigned int base_reg, unsigned int reg, unsigned int *addr, unsigned int size)
{
    int i;

    for (i = 0; i < size / 4;)
    {
        if (i % 8 == 0)
            seq_printf (file, "%08x(%08x): ", reg + i * 4, (reg - base_reg) + (i * 4));
        seq_printf (file, " %08x", addr[i]);
        i++;
        if (i % 8 == 0)
            seq_printf (file, "\n");
    }
    if (i % 8 != 0)
        seq_printf (file, "\n");
}
#endif

static int reg_show (struct seq_file *m, void *data)
{
    reg_dump (m, (void *) peri_ctrl_reg, peri_reg_size);
#ifndef _DOLBY_IPP_
    reg_dump (m, (void *) dsp_ctrl_reg, dsp_reg_size);
#endif

    return 0;
}

#ifdef _LNX_
static int lnx2_reg_show (struct seq_file *m, void *data)
{
    regs_lnx2_disable_WriteOnly (true);
#if defined(CHIP_NAME_o24)
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_addr, (void *) lnx2_hcr, lnx2_hcr_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_dma_addr, (void *) lnx2_dma, lnx2_dma_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_ce0_addr, (void *) lnx2_cecfc_ce0, lnx2_cecfc_ce0_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_ce1_addr, (void *) lnx2_cecfc_ce1, lnx2_cecfc_ce1_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_ce2_addr, (void *) lnx2_cecfc_ce2, lnx2_cecfc_ce2_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_ce3_addr, (void *) lnx2_cecfc_ce3, lnx2_cecfc_ce3_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_cfc_addr, (void *) lnx2_cecfc_cfc, lnx2_cecfc_cfc_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_top_addr, (void *) lnx2_cecfc_top, lnx2_cecfc_top_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_tm_addr, (void *) lnx2_tm, lnx2_tm_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_host01_addr, (void *) lnx2_hcr_host01, lnx2_hcr_host01_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_host02_addr, (void *) lnx2_hcr_host02, lnx2_hcr_host02_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_host03_addr, (void *) lnx2_hcr_host03, lnx2_hcr_host03_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_host04_addr, (void *) lnx2_hcr_host04, lnx2_hcr_host04_size);
#elif defined(CHIP_NAME_o26)
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_addr, (void *) lnx2_hcr, lnx2_hcr_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_dsscr_addr, (void *) lnx2_dsscr, lnx2_dsscr_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_sscg_addr, (void *) lnx2_sscg, lnx2_sscg_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_dscg_addr, (void *) lnx2_dscg, lnx2_dscg_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_gsema_addr, (void *) lnx2_gsema, lnx2_gsema_size);

    regs_lnx2_reg_write (0x5004, 0x1);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_gb_addr, (void *) lnx2_gb, lnx2_gb_size);

    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_rx_gdma_addr, (void *) lnx2_rx_gdma, lnx2_rx_gdma_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_tx_gdma_addr, (void *) lnx2_tx_gdma, lnx2_tx_gdma_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_dma_addr, (void *) lnx2_dma, lnx2_dma_size);

    regs_lnx2_reg_write (0x9004, 0x10);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_con_ce0_addr, (void *) lnx2_cecfc_con_ce0, lnx2_cecfc_con_ce0_size);
    regs_lnx2_reg_write (0x9004, 0x11);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_con_ce1_addr, (void *) lnx2_cecfc_con_ce1, lnx2_cecfc_con_ce1_size);

    regs_lnx2_reg_write (0x9400, 0x10);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_debug_ce0_addr, (void *) lnx2_cecfc_debug_ce0, lnx2_cecfc_debug_ce0_size);
    regs_lnx2_reg_write (0x9400, 0x21);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_cecfc_debug_ce1_addr, (void *) lnx2_cecfc_debug_ce1, lnx2_cecfc_debug_ce1_size);

    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_tm_addr, (void *) lnx2_tm, lnx2_tm_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_pve_addr, (void *) lnx2_pve, lnx2_pve_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_mcu_mon_addr, (void *) lnx2_mcu_mon, lnx2_mcu_mon_size);
    reg_dump_show_addr (m, lnx2_hcr_addr, lnx2_hcr_host_addr, (void *) lnx2_hcr_host, lnx2_hcr_host_size);
#endif
    regs_lnx2_disable_WriteOnly (false);
    return 0;
}
#endif

static int seq_show_open (struct inode *inode, struct file *file)
{
    int ret;
    int (*seq_show) (struct seq_file * m, void *data);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    seq_show = pde_data (inode);
#else
    seq_show = PDE_DATA (inode);
#endif
    ret = single_open (file, seq_show, NULL);
    if (ret < 0)
        return ret;

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
const struct proc_ops aaudio_seq_show_fops = {
    .proc_open = seq_show_open,
    .proc_release = single_release,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
};
#else
struct file_operations aaudio_seq_show_fops = {
    .open = seq_show_open,
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
};
#endif

static DEFINE_MUTEX (aud_log_lock);

struct log_capture_line
{
    struct list_head list;

    int processed;
    int size;
    char string[0];
};
static LIST_HEAD (lc_received);
static DEFINE_MUTEX (lc_received_lock);
static DECLARE_WAIT_QUEUE_HEAD (lc_wq);
static int lc_proc_num;
static enum
{
    lc_state_wait,
    lc_state_working,
    lc_state_done,
} lc_state;
static char lc_magic[16];
static int lc_magic_num;

static void log_capture_log (int proc_num, unsigned int ts, const char *string)
{
    bool drop_log = false;
    struct log_capture_line *line = NULL;

    mutex_lock (&lc_received_lock);
    debug ("state %d, proc%d, %s\n", lc_state, proc_num, string);
    if (lc_proc_num == proc_num)
    {
        if (lc_state == lc_state_working)
        {
            char tmp[32];
            snprintf (tmp, sizeof (tmp), "%s: end\n", lc_magic);

            if (!strcmp (tmp, string))
            {
                drop_log = true;
                lc_state = lc_state_done;
                info ("done..\n");
                wake_up (&lc_wq);
            }
        }

        if (lc_state == lc_state_working)
        {
            int size = strlen (string);
            line = kmalloc (sizeof (*line) + size, GFP_KERNEL);
            if (line)
            {
                line->processed = 0;
                line->size = size;
                memcpy (line->string, string, size);

                list_add_tail (&line->list, &lc_received);
                debug ("size %d, wakeup.\n", size);
                wake_up (&lc_wq);
            }
            else
                error ("no mem. size %d\n", size);
        }

        if (lc_state == lc_state_wait)
        {
            char tmp[32];
            snprintf (tmp, sizeof (tmp), "%s: start\n", lc_magic);

            if (!strcmp (tmp, string))
            {
                drop_log = true;
                lc_state = lc_state_working;
                info ("working..\n");
            }
        }
    }

    if (!line && !drop_log)
        aud_log_default (proc_num, ts, string);
    mutex_unlock (&lc_received_lock);
}

ssize_t aproc_lc_read (struct file *file, char __user * data, size_t size, loff_t * pos)
{
    ssize_t processed = 0;

    debug ("data size %zd\n", size);
    while (processed < size)
    {
        int ret;
        struct log_capture_line *line;
        int copy_size;

        ret = wait_event_interruptible (lc_wq,
            (list_empty (&lc_received) && lc_state == lc_state_done) || !list_empty (&lc_received));
        if (ret < 0)
            break;

        if (list_empty (&lc_received) && lc_state == lc_state_done)
            break;

        line = list_first_entry (&lc_received, struct log_capture_line, list);

        copy_size = size - processed;
        if (copy_size > line->size - line->processed)
            copy_size = line->size - line->processed;
        debug ("copy %d, processed %zd\n", copy_size, processed);

        ret = copy_to_user (data + processed, line->string + line->processed, copy_size);
        if (ret)
            return -EFAULT;
        processed += copy_size;
        line->processed += copy_size;

        if (line->processed >= line->size)
        {
            debug ("remove %d\n", line->size);
            mutex_lock (&lc_received_lock);
            list_del (&line->list);
            mutex_unlock (&lc_received_lock);
        }
    }
    debug ("%zd processed\n", processed);

    return processed;
}

int aproc_lc_release (struct inode *inode, struct file *file)
{
    struct log_capture_line *line, *n;

    info ("log capture done.\n");
    aud_log_print = aud_log_default;
    mutex_lock (&lc_received_lock);
    lc_proc_num = 0;
    list_for_each_entry_safe (line, n, &lc_received, list)
    {
        list_del (&line->list);
        kfree (line);
    }
    mutex_unlock (&lc_received_lock);
    mutex_unlock (&aud_log_lock);

    return 0;
}

/* Trigger log capture function.
 *
 * Send following function call with following arguments.
 * func_name(_MAGIC_%d_ [arg1 arg2 ...])
 */
int aproc_lc_trigger (int proc_num, const char *func_name, ...)
{
    int i;
    int dspnum;
    va_list vargs;
    char *str_arg;
    int ret;

    ret = mutex_lock_interruptible (&aud_log_lock);
    if (ret < 0)
        return ret;

    dspnum = proc_num - ADEC_CORE_DSP0;
    lc_proc_num = proc_num;
    lc_state = lc_state_wait;
    lc_magic_num++;
    snprintf (lc_magic, sizeof (lc_magic), "_MAGIC_%d_", lc_magic_num);
    aud_log_print = log_capture_log;

    send_call_param (dspnum, lc_magic, param_arg);

    va_start (vargs, func_name);
    i = 0;
    while ((str_arg = va_arg (vargs, char *)) != NULL)
    {
        info ("set argument %d, %s at dsp%d\n", i, str_arg, dspnum);
        send_call_param (dspnum, str_arg, param_arg);
        i++;
    }
    va_end (vargs);

    info ("call functionv debug_aimc() at dsp%d\n", dspnum);
    return send_call_param (dspnum, func_name, param_funcv);
}

static int mstate_open (struct inode *inode, struct file *file)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    ModuleInfo *mi = (void *) pde_data (inode);
#else
    ModuleInfo *mi = (void *) PDE_DATA (inode);
#endif
    char moduleid[8];

    snprintf (moduleid, sizeof (moduleid), "%d", mi->module);
    info ("send status imc to %s(%d)\n", mi->name, mi->module);
    return aproc_lc_trigger (ModuleList_FindModule (mi->module), "debug_aimc2", "lstatus", moduleid,
        NULL);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
const struct proc_ops mstate_fops = {
    .proc_open = mstate_open,
    .proc_read = aproc_lc_read,
    .proc_release = aproc_lc_release,
};
#else
struct file_operations mstate_fops = {
    .open = mstate_open,
    .read = aproc_lc_read,
    .release = aproc_lc_release,
};
#endif

struct fcall_info
{
    int proc_num;
    const char *func_name;
};

static int fcall_open (struct inode *inode, struct file *file)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    struct fcall_info *fc = (void *) pde_data (inode);
#else
    struct fcall_info *fc = (void *) PDE_DATA (inode);
#endif
    info ("send function call to %s(%d)\n", fc->func_name, fc->proc_num);
    return aproc_lc_trigger (fc->proc_num, "debug_aimc2", "fcall", fc->func_name, NULL);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
const struct proc_ops fcall_fops = {
    .proc_open = fcall_open,
    .proc_read = aproc_lc_read,
    .proc_release = aproc_lc_release,
};
#else
struct file_operations fcall_fops = {
    .open = fcall_open,
    .read = aproc_lc_read,
    .release = aproc_lc_release,
};
#endif

struct proc_dir_entry *aproc_m_root;
struct proc_dir_entry *aproc_seetv;

extern ModuleInfo gModuleInfo[];

int aproc_init (void)
{
    int number_of_dsp = aud_hal_get_number_of_dsp ();
    int i;

    aproc_root = proc_mkdir ("aaudio", NULL);
    if (!aproc_root)
        printk (KERN_ERR "proc_mkdir(\"aaudio\") failed\n");

    proc_create_data ("logmask", 0640, aproc_root, &aaudio_args_fops, set_logmask);
    proc_create_data ("callv", 0640, aproc_root, &aaudio_args_fops, call_funcv);
    proc_create_data ("irq_command", 0440, aproc_root, &aaudio_args_fops, send_irq_cmd);
    proc_create_data ("register", 0440, aproc_root, &aaudio_seq_show_fops, reg_show);
#ifdef _LNX_
    proc_create_data ("lnx2_reg", 0440, aproc_root, &aaudio_seq_show_fops, lnx2_reg_show);
#endif

    aproc_m_root = proc_mkdir ("module", aproc_root);
    if (!aproc_m_root)
        printk (KERN_ERR "cannot mkdir \"module\"\n");
    for (i = 1; i < ADEC_MODULE_MAX; i++)
    {
        const char *name = ModuleList_GetModuleName (i);
        struct proc_dir_entry *de;

        de = proc_mkdir (name, aproc_m_root);

        proc_create_data ("status", 0640, de, &mstate_fops, &gModuleInfo[i]);
    }

    /* create dsp function call print grabber */
    for (i = 0; i < number_of_dsp; i++)
    {
        static const struct fcall
        {
            const char *name;
            unsigned int only_for_dsp;
#define ONLY_FOR_DSP(d)             (1<<(d))
        } fcalls[] =
        {
            /* *INDENT-OFF* */
            { "dump_module_connection",     },
            { "dot_module_connection",      },

            /* legacy scheduler */
            { "sched_dump_run_list",        },
            { "sched_module_result",        },
            { "sched_run_all",              },
            { "sched_info",                 },
            { "psched_info",                },

            { "irq_status",                 },
            { "debug_bm_report",            },
            { "debug_registry_dump",        },
            { "dot_registry",               },
            { "debug_xos_load",             },
            { "debug_xos_thread",           },
            { "debug_xos_timer",            },
            { "debug_xos_sizes",            },
            { "print_version",              },

            /* heap debug */
            { "show_heap_status",           },
            { "print_free_heap",            },
            { "dump_heap_cell",             },
            { "dump_aud_data_cache"         },

            { "debug_bin"                   },
#if defined(CHIP_NAME_o24) || defined(CHIP_NAME_o26)
            { "axi_gk_set_range"            },
            { "axi_gk_get_err_count"        },
#endif

            { "se_test",                    ONLY_FOR_DSP(1), },
            /* *INDENT-ON* */
        };
        struct proc_dir_entry *aproc_dsp;
        char dspname[] = "dsp0";
        int j;

        dspname[3] = '0' + i;
        aproc_dsp = proc_mkdir (dspname, aproc_root);

        for (j = 0; j < ARRAY_SIZE (fcalls); j++)
        {
            struct fcall_info *fc;

            if (fcalls[j].only_for_dsp & ~(ONLY_FOR_DSP (i)))
                continue;

            fc = kzalloc (sizeof (*fc), GFP_KERNEL);
            if (!fc)
            {
                error ("no mem.\n");
                continue;
            }

            fc->proc_num = ADEC_CORE_DSP0 + i;
            fc->func_name = fcalls[j].name;
            proc_create_data (fc->func_name, 0640, aproc_dsp, &fcall_fops, fc);
        }
    }

    // for jcl4tv debug status
    {
        extern struct proc_dir_entry *OS_PROC_GetLinuxTvEntry (void);
        struct proc_dir_entry *aproc_seetv_root;

        aproc_seetv_root = OS_PROC_GetLinuxTvEntry ();
        aproc_seetv = proc_mkdir ("audio", aproc_seetv_root);
    }

    return 0;
}
