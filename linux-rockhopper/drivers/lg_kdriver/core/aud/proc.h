#ifndef _AUDIO_PROC_H_
#define _AUDIO_PROC_H_

#include <linux/fs.h>
#include <linux/version.h>

int aproc_init (void);

extern struct proc_dir_entry *aproc_root;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
extern const struct proc_ops aaudio_args_fops;
#else
extern struct file_operations aaudio_args_fops;
#endif
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
extern const struct proc_ops aaudio_seq_show_fops;
#else
extern struct file_operations aaudio_seq_show_fops;
#endif

struct aaudio_args_arg
{
    void *arg;

    /* write to proc file */
    int (*callback) (void *arg, int, char **);

    /* read from proc file */
    int (*show) (void *arg, struct seq_file *m);
    const struct file_operations *read_fops;
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
extern const struct proc_ops aaudio_args_arg_fops;
#else
extern struct file_operations aaudio_args_arg_fops;
#endif

int aproc_lc_trigger (int proc_num, const char *func_name, ...);
ssize_t aproc_lc_read (struct file *file, char __user * data, size_t size, loff_t * pos);
int aproc_lc_release (struct inode *inode, struct file *file);

int aud_call_funcsv (int dspnum, const char *fmt, va_list vargs);
int aud_call_funcs (int dspnum, const char *fmt, ...);

int aud_send_irq_cmd (int dsp, int cmd);

#endif
