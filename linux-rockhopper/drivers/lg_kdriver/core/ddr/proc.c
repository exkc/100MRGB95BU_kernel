#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/printk.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include "proc_util.h" // lgtv-driver
#include "register.h"
#include "proc.h"

unsigned int strtoui(char *str)
{
	unsigned long res = 0;
	int ret;

	ret = kstrtoul(str, 0, &res);
	if (ret) {
		pr_err("strtoui error %d\n", ret);
	}

	return (uint32_t)(res);
}

static struct proc_dir_entry *ddr_dir = NULL;
static struct proc_dir_entry *debug_dir = NULL;

struct reg_info {
	uint32_t addr;
	uint32_t data;
	uint32_t *base;
	uint32_t count;
	uint32_t page;
};

static ssize_t command_write(struct file *file,
		const char __user *buffer, size_t count, loff_t *pos)
{
	char *buf, *buf1;
	int ret = 0;

	buf = kmalloc(count*sizeof(char), GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;
	buf[count-1] = 0;

	buf1 = buf;
	ret = ddr_cmd(buf1);
	if (ret)
		goto out;

	kfree(buf);
	return count;
out:
	kfree(buf);
	return -EINVAL;
}

static int command_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int command_release(struct inode *inode, struct file *file)
{
	return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
struct proc_ops command_fops =
{
	.proc_write		= command_write,
	.proc_open		= command_open,
	.proc_release	= command_release,
};
#else
struct file_operations command_fops =
{
	.write		= command_write,
	.open		= command_open,
	.release	= command_release,
};
#endif

static int register_show(struct seq_file *s, void *v)
{
	struct reg_info *reg;
	uint32_t *base;

	reg = s->private;
	if (reg->addr == 0) {
		seq_printf(s, "Input address\n");
		return 0;
	}

	base = ioremap(reg->addr, sizeof(uint32_t));
	if (!base)
		return -ENOMEM;
	seq_printf(s, "0x%08x\n", base[0]);
	iounmap(base);

	return 0;
}

static ssize_t register_write(struct file *file,
		const char __user *buffer, size_t count, loff_t *pos)
{
	struct reg_info *reg;
	char *buf, *buf1, *token;
	char *bw, *bp;
	uint32_t *base, argc = 0;
	uint32_t m[3], n = 0;
	uint32_t mask, width, data;

	reg = ((struct seq_file *)file->private_data)->private;

	buf = kmalloc(count*sizeof(char), GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;
	buf[count-1] = 0;

	buf1 = buf;
	while ((token = strsep(&buf1, " ")) != NULL) {
		argc++;
		if (argc == 1) {
			reg->addr = strtoui(token);
			if (reg->addr < 0xc0000000) {
				kfree(buf);
				pr_err("out of memory map\n");
				return -EINVAL;
			}
		} else if (argc == 2) {
			reg->data = strtoui(token);
		} else if (argc == 3) {
			bw = token;
			while((bp = strsep(&bw, "[:]")) != NULL) {
				if (n > 1)
					break;
				if (strlen(bp)) {
					m[n] = strtoui(bp);
					m[n+1] = m[n];
					n++;
				}
			}

			if (m[1] > m[0]) {
				pr_err("Bit order error\n");
				return -EINVAL;
			}
		} else {
			pr_err("too many argc\n");
			kfree(buf);
			return -EINVAL;
		}
	}

	if (argc == 2) {
		base = ioremap(reg->addr, sizeof(uint32_t));
		REG_WR(base, reg->data);
		iounmap(base);
	} else if (argc == 3) {
		m[3] = m[0] - m[1] + 1;
		if (m[3] > 31) {
			mask = 0x0;
			width = 0xFFFFFFFF;
		} else {
			mask = ~(~(0xFFFFFFFF << m[3]) << m[1]);
			width = ~(0xFFFFFFFF << m[3]);
			reg->data &= (~(0xFFFFFFFF << m[3]));
		}

		base = ioremap(reg->addr, sizeof(uint32_t));
		data = REG_RD(base);
		reg->data = (data & mask) | (reg->data << m[1]);
		REG_WR(base, reg->data);
		iounmap(base);
	}

	kfree(buf);
	return count;
}

static int register_open(struct inode *inode, struct file *file)
{
	struct reg_info *reg;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	reg = pde_data(inode);
#else
	reg = PDE_DATA(inode);
#endif

	return single_open(file, register_show, reg);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
struct proc_ops register_fops =
{
	.proc_open		= register_open,
	.proc_read		= seq_read,
	.proc_lseek		= seq_lseek,
	.proc_release	= single_release,
	.proc_write		= register_write,
};
#else
struct file_operations register_fops =
{
	.open		= register_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
	.write		= register_write,
};
#endif

static void *dump_seq_start(struct seq_file *s, loff_t *pos)
{
	struct reg_info *reg;

	reg = s->private;

	if (reg->addr == 0) {
		pr_err("Input address\n");
		return NULL;
	}
	reg->base = ioremap(reg->addr, PAGE_SIZE * reg->page);
	if (!reg->base)
		return NULL;

	reg->data = reg->base[*pos];

	return reg;
}

static void *dump_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	struct reg_info *reg;

	reg = (struct reg_info *)v;

	(*pos)++;
	reg->data = reg->base[*pos];
	reg->count++;

	return reg;
}

static void dump_seq_stop(struct seq_file *s, void *v)
{
	struct reg_info *reg;

	if (v) {
		reg = (struct reg_info *)v;
		reg->page++;
		iounmap(reg->base);
	}
}

static int dump_seq_show(struct seq_file *s, void *v)
{
	struct reg_info *reg;

	reg = (struct reg_info *)v;

	if ((reg->count % 8) == 0)
		seq_printf(s, "%08x: ", (reg->addr) + (reg->count*4));
	seq_printf(s, "%08x ", reg->data);
	if ((reg->count % 8) == 7)
		seq_printf(s, "\n");

	return 0;
}

static struct seq_operations dump_seq_ops = {
	.start	= dump_seq_start,
	.next	= dump_seq_next,
	.stop	= dump_seq_stop,
	.show	= dump_seq_show,
};

static int dump_open(struct inode *inode, struct file *file)
{
	struct reg_info *reg;

	seq_open(file, &dump_seq_ops);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	reg = pde_data(inode);
#else
	reg = PDE_DATA(inode);
#endif
	((struct seq_file *)file->private_data)->private = reg;

	return 0;
};

static ssize_t dump_write(struct file *file,
		const char __user *buffer, size_t count, loff_t *pos)
{
	struct reg_info *reg;
	char *buf, *buf1, *token;
	uint32_t argc = 0;

	reg = ((struct seq_file *)file->private_data)->private;
	reg->count = 0;
	reg->page = 1;

	buf = kmalloc(count*sizeof(char), GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;
	buf[count-1] = 0;

	buf1 = buf;
	while ((token = strsep(&buf1, " ")) != NULL) {
		argc++;
		if (argc == 1) {
			reg->addr = strtoui(token);
		} else {
			pr_err("too many argc\n");
			kfree(buf);
			return -EINVAL;
		}
	}

	kfree(buf);
	return count;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
struct proc_ops dump_fops =
{
	.proc_open		= dump_open,
	.proc_read		= seq_read,
	.proc_lseek		= seq_lseek,
	.proc_release	= seq_release,
	.proc_write		= dump_write,
};
#else
struct file_operations dump_fops =
{
	.open		= dump_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release,
	.write		= dump_write,
};
#endif

// lgtv-driver/ddr/ddr_info
static int info_show(struct seq_file *s, void *v)
{
	struct ddr_info dev;
	int ret;

	ret = get_ddr_info(&dev);
	if (ret)
		return -EINVAL;

	seq_printf(s, "DDR_Size = %s\n", dev.size);
	seq_printf(s, "CLOCK = %s\n", dev.clock);

	return 0;
}

static int info_open(struct inode *inode, struct file *file)
{
	return single_open(file, info_show, NULL);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
struct proc_ops info_fops =
{
	.proc_open		= info_open,
	.proc_read		= seq_read,
	.proc_lseek		= seq_lseek,
	.proc_release	= single_release,
};
#else
struct file_operations info_fops =
{
	.open		= info_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
#endif

int init_ddr_proc(void)
{
	static struct reg_info *reg;

	struct proc_dir_entry *lgtv_drv;
	struct proc_dir_entry *lgtv_ddr;

	ddr_dir = proc_mkdir("ddr", NULL);
	if (!ddr_dir)
		return 0;
	debug_dir = proc_mkdir("debug", ddr_dir);
	if (!debug_dir)
		return 0;

	reg = kcalloc(1, sizeof(struct reg_info), GFP_KERNEL);
	if (reg == NULL)
		return -ENOMEM;

	proc_create_data("cmd", 0644, debug_dir, &command_fops, reg);
	proc_create_data("reg", 0644, debug_dir, &register_fops, reg);
	proc_create_data("dump", 0644, debug_dir, &dump_fops, reg);

	// lgtv-driver/ddr/ddr_info
	lgtv_drv = OS_PROC_GetLinuxTvEntry();

	lgtv_ddr = proc_mkdir("ddr", lgtv_drv);
	if (!lgtv_ddr)
		return 0;

	proc_create_data("ddr_info", 0644, lgtv_ddr, &info_fops, NULL);

	return 0;
}

void cleanup_ddr_proc(void)
{
	remove_proc_entry("cmd", debug_dir);
	remove_proc_entry("reg", debug_dir);
	remove_proc_entry("dump", debug_dir);
	remove_proc_entry("debug", ddr_dir);
	remove_proc_entry("ddr", NULL);
}

