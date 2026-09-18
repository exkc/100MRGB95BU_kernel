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


/** @file
 *
 *  emulator driver for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-03-29
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/delay.h>

#include "te_emul.h"
#include "te_emul_regs.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DEFAULT_INPUT_SPEED		(1*1024*1024)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
enum
{
	ATSC3_PROC_ID_FILENAME = 0,
	ATSC3_PROC_ID_RUN,
	ATSC3_PROC_ID_SPEED,
	ATSC3_PROC_ID_DEBUG,
	ATSC3_PROC_ID_LOOPCOUNT,
	ATSC3_PROC_ID_MAX,
};

enum
{
	STREAM_PLAYER_STOP = 0,
	STREAM_PLAYER_START,
	STREAM_PLAYER_WAIT,
};

typedef struct
{
	volatile int	status;

	char			*filename;
	UINT32			speed;
	UINT32			loop_count;
	UINT32			delayed_start;

	struct task_struct *thread;
} ATSC3_PROC_T;

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static int atsc3_open(struct inode *inode, struct file *file);
static ssize_t atsc3_write (struct file *file,
		const char __user *buf, size_t size, loff_t *off);
static int atsc3_release (struct inode *inode, struct file *file);

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static struct proc_dir_entry *root_entry;
static struct proc_dir_entry *atsc3_proc_entry;

static struct file_operations atsc3_fops =
{
	.open	= atsc3_open,
	.read	= seq_read,
	.write	= atsc3_write,
	.llseek	= seq_lseek,
	.release= atsc3_release,
};

static ATSC3_PROC_T *atsc_proc;


static int input_speed = DEFAULT_INPUT_SPEED;
module_param(input_speed, int, 0644);

static int loop_count;
module_param(loop_count, int, 0644);

static int auto_start;
module_param(auto_start, int, 0644);

/*========================================================================================
	Implementation Group
========================================================================================*/

static char *get_input_str(char *in)
{
	char *s = in;

	// TODO: remove white space

	/* remove \n */
	while(*s)
	{
		 if(*s == '\n')
		{
			*s = '\0';
			break;
		}
		s++;
	}

	return in;
}

static UINT32 parse_size(const char *ptr)
{
	char *endptr;
	UINT32 ret = simple_strtoul(ptr, &endptr, 0);

	switch(*endptr)
	{
		case 'M':
		case 'm':
			ret <<= 10;
		case 'K':
		case 'k':
			ret <<= 10;
			break;
	}

	return ret;
}

static UINT32 get_ms_ticks( void )
{
	ktime_t	t = ktime_get();
	struct timespec64 ts = ktime_to_timespec64(t);

	return (UINT32)ts.tv_sec * 1000 + (UINT32)(ts.tv_nsec/1000000);
}

static int file_read(struct file *f, void *data, size_t size)
{
	int ret;
	mm_segment_t fs;

	fs = get_fs();
	set_fs(get_ds());
	ret = vfs_read(f, data, size, &f->f_pos);
	set_fs(fs);

	return ret;
}

static int file_seek(struct file *f, off_t offset, int whence)
{
	int ret;

	mm_segment_t fs;

	fs = get_fs();
	set_fs(get_ds());
	ret = vfs_llseek(f, offset, whence);
	set_fs(fs);

	return ret;
}

static int stream_player(void *arg)
{
	int rc;
	int read;
	UINT8 *buf;
	struct file *f = NULL;
	UINT32 buf_size;
	UINT32 stime;
	int loop = 0;
	ATSC3_PROC_T *p = arg;

	buf_size = 64*1024;		/* 64KB */

	buf = kmalloc(buf_size, GFP_KERNEL);
	if(!buf)
	{
		rc = -ENOMEM;
		goto exit;
	}

	f = filp_open(p->filename, O_RDONLY, 0644);
	if(IS_ERR(f))
	{
		printk("can't open file '%s'\n", p->filename);
		rc = -EIO;
		f = NULL;
		goto exit;
	}

	if(p->delayed_start)
	{
		msleep(p->delayed_start);
	}

	while(1)
	{
		if(p->status == STREAM_PLAYER_STOP)
			break;

		if(p->status == STREAM_PLAYER_WAIT)
		{
			msleep(1);
			continue;
		}

		stime = get_ms_ticks();

		read = file_read(f, buf, buf_size);
		if(read < 0)
		{
			printk("can't read file\n");
			break;
		}
		else if(read == 0)
		{
			printk("End of file... loop(%d)\n", ++loop);

			if(p->loop_count &&	loop >= p->loop_count)
			{
				p->status = STREAM_PLAYER_WAIT;
				break;
			}

			file_seek(f, 0, SEEK_SET);
		}

		TE_EMUL_ATSC3_PutStream(buf, read);

		if(p->speed)
		{
			UINT32 interval, diff_time;

			interval = (read*1000) / p->speed;
			diff_time = (UINT32)(get_ms_ticks() - stime);
			if(diff_time < interval)
			{
				UINT32 delay = (interval-diff_time)*1000;

				if(delay >= 1000) msleep(delay/1000);
				udelay(delay%1000);
			}
		}
	}
	rc = 0;

exit:
	if(f) filp_close(f, NULL);
	if(buf) kfree(buf);

	/* Wait until we are told to stop */
	while(1)
	{
		set_current_state(TASK_INTERRUPTIBLE);
		if(kthread_should_stop())
			break;
		schedule();
	}
	set_current_state(TASK_RUNNING);

	return rc;
}

static int start_stream_player(void)
{
	struct task_struct *thread;

	if(atsc_proc->thread)
	{
		printk("already started...\n");
		return -EBUSY;
	}

	thread = kthread_create(stream_player, atsc_proc, "atsc3_stream");
	if(!thread)
	{
		printk("can't create thread\n");
		return -EIO;
	}
	atsc_proc->thread = thread;
	atsc_proc->status = STREAM_PLAYER_START;

	wake_up_process(thread);

	return 0;
}

static int stop_stream_player(void)
{
	if(!atsc_proc->thread)
		return 0;

	atsc_proc->status = STREAM_PLAYER_STOP;

	kthread_stop(atsc_proc->thread);
	atsc_proc->thread = NULL;

	return 0;
}


#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0))

#else
static int atsc3_show(struct seq_file *m, void *data)
{
	unsigned long cmd = (unsigned long)m->private;

	switch(cmd)
	{
		case ATSC3_PROC_ID_FILENAME:
			seq_printf(m, "filename : '%s'\n", atsc_proc->filename ? : "");
			break;

		case ATSC3_PROC_ID_RUN:
			seq_printf(m, "status : '%s'\n", atsc_proc->status == 0 ? "IDLE" : "RUNNING");
			break;

		case ATSC3_PROC_ID_SPEED:
			seq_printf(m, "speed : %dKBps\n", atsc_proc->speed/1024);
			break;

		case ATSC3_PROC_ID_LOOPCOUNT:
			seq_printf(m, "loopcount : %d\n", atsc_proc->loop_count );
			break;

		default:
			break;
	}

	return 0;
}

static int atsc3_open(struct inode *inode, struct file *file)
{
	unsigned long cmd;
	int ret;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	cmd = (unsigned long)pde_data(inode);
#else
	cmd = (unsigned long)PDE_DATA(inode);
#endif
	ret = single_open(file, atsc3_show, (void*)cmd);

	return ret;
}

static int atsc3_release (struct inode *inode, struct file *file)
{
	return single_release (inode, file);
}


static ssize_t atsc3_write (struct file *file,
		const char __user *buf, size_t size, loff_t *off)
{
	unsigned long cmd;
	char *str;
	int rc, ret;
	unsigned int v;

	if(size == 0)
		return 0;

	str = kmalloc(size, GFP_KERNEL);
	if(!str) return -ENOMEM;

	if(copy_from_user(str, buf, size))
	{
		ret = -EFAULT;
		goto exit;
	}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
	cmd = (unsigned long)pde_data(file->f_inode);
#else
	cmd = (unsigned long)PDE_DATA(file->f_inode);
#endif
	switch(cmd)
	{
		case ATSC3_PROC_ID_FILENAME:
		{
			char *name = get_input_str(str);

			if(atsc_proc->filename) kfree(atsc_proc->filename);

			atsc_proc->filename = kmalloc(strlen(name) + 1, GFP_KERNEL);
			if(!atsc_proc->filename)
			{
				ret = -ENOMEM;
				goto exit;
			}
			strcpy(atsc_proc->filename, name);

			break;
		}

		case ATSC3_PROC_ID_RUN:
		{
			v = simple_strtoul(str, NULL, 0);

			if(v) rc = start_stream_player();
			else rc = stop_stream_player();

			if(rc != 0)
			{
				ret = rc;
				goto exit;
			}

			break;
		}

		case ATSC3_PROC_ID_SPEED:
		{
			v = parse_size(str);
			atsc_proc->speed = v;

			break;
		}

		case ATSC3_PROC_ID_LOOPCOUNT:
		{
			v = simple_strtoul(str, NULL, 0);
			atsc_proc->loop_count = v;

			break;
		}

		default:
		{
			ret = -ENOTTY;
			break;
		}

	}
	ret = size;

exit:
	kfree(str);

	return ret;
}
#endif


static void atsc3_proc_init(void)
{
	atsc3_proc_entry = proc_mkdir("atsc3", root_entry);

	proc_create_data("file", 0644, atsc3_proc_entry, &atsc3_fops, (void*)ATSC3_PROC_ID_FILENAME);
	proc_create_data("run", 0644, atsc3_proc_entry, &atsc3_fops, (void*)ATSC3_PROC_ID_RUN);
	proc_create_data("speed", 0644, atsc3_proc_entry, &atsc3_fops, (void*)ATSC3_PROC_ID_SPEED);
	proc_create_data("loopcount", 0644, atsc3_proc_entry, &atsc3_fops, (void*)ATSC3_PROC_ID_LOOPCOUNT);

}









int proc_init(void)
{
	atsc_proc = kcalloc(1, sizeof(*atsc_proc), GFP_KERNEL);
	if(!atsc_proc)
	{
		printk("no memory\n");
		return -ENOMEM;
	}
	atsc_proc->speed = input_speed;
	atsc_proc->loop_count = loop_count;

	root_entry = proc_mkdir("te_emul", NULL);

	atsc3_proc_init();

	if(auto_start)
	{
		atsc_proc->delayed_start = 500;
		start_stream_player();
	}

	return 0;
}


void proc_cleanup(void)
{
	if(root_entry) remove_proc_subtree("te_emul", NULL);

	if(atsc_proc)
	{
		kfree(atsc_proc);
		atsc_proc = NULL;
	}
}


