// SPDX-License-Identifier: GPL-2.0-only
/*
 * linux/kernel/power/user.c
 *
 * This file provides the user space interface for software suspend/resume.
 *
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 */

#include <linux/suspend.h>
#include <linux/reboot.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/swapops.h>
#include <linux/pm.h>
#include <linux/fs.h>
#include <linux/compat.h>
#include <linux/console.h>
#include <linux/cpu.h>
#include <linux/freezer.h>

#include <linux/uaccess.h>

#include "power.h"

static bool need_wait;

static struct snapshot_data {
	struct snapshot_handle handle;
	int swap;
	int mode;
	bool frozen;
	bool ready;
	bool platform_support;
	bool free_bitmaps;
	dev_t dev;
} snapshot_state;

int is_hibernate_resume_dev(dev_t dev)
{
	return hibernation_available() && snapshot_state.dev == dev;
}

static int snapshot_open(struct inode *inode, struct file *filp)
{
	struct snapshot_data *data;
	unsigned int sleep_flags;
	int error;

	if (!hibernation_available())
		return -EPERM;

	sleep_flags = lock_system_sleep();

	if (!hibernate_acquire()) {
		error = -EBUSY;
		goto Unlock;
	}

	if ((filp->f_flags & O_ACCMODE) == O_RDWR) {
		hibernate_release();
		error = -ENOSYS;
		goto Unlock;
	}
	nonseekable_open(inode, filp);
	data = &snapshot_state;
	filp->private_data = data;
	memset(&data->handle, 0, sizeof(struct snapshot_handle));
	if ((filp->f_flags & O_ACCMODE) == O_RDONLY) {
		/* Hibernating.  The image device should be accessible. */
		data->swap = swap_type_of(swsusp_resume_device, 0);
		data->mode = O_RDONLY;
		data->free_bitmaps = false;
		error = pm_notifier_call_chain_robust(PM_HIBERNATION_PREPARE, PM_POST_HIBERNATION);
	} else {
		/*
		 * Resuming.  We may need to wait for the image device to
		 * appear.
		 */
		need_wait = true;

		data->swap = -1;
		data->mode = O_WRONLY;
		error = pm_notifier_call_chain_robust(PM_RESTORE_PREPARE, PM_POST_RESTORE);
		if (!error) {
			error = create_basic_memory_bitmaps();
			data->free_bitmaps = !error;
		}
	}
	if (error)
		hibernate_release();

	data->frozen = false;
	data->ready = false;
	data->platform_support = false;
	data->dev = 0;

 Unlock:
	unlock_system_sleep(sleep_flags);

	return error;
}

static int snapshot_release(struct inode *inode, struct file *filp)
{
	struct snapshot_data *data;
	unsigned int sleep_flags;

	sleep_flags = lock_system_sleep();

	swsusp_free();
	data = filp->private_data;
	data->dev = 0;
	free_all_swap_pages(data->swap);
	if (data->frozen) {
		pm_restore_gfp_mask();
		free_basic_memory_bitmaps();
		thaw_processes();
	} else if (data->free_bitmaps) {
		free_basic_memory_bitmaps();
	}
	pm_notifier_call_chain(data->mode == O_RDONLY ?
			PM_POST_HIBERNATION : PM_POST_RESTORE);
	hibernate_release();

	unlock_system_sleep(sleep_flags);

	return 0;
}

static ssize_t snapshot_read(struct file *filp, char __user *buf,
                             size_t count, loff_t *offp)
{
	loff_t pg_offp = *offp & ~PAGE_MASK;
	struct snapshot_data *data;
	unsigned int sleep_flags;
	ssize_t res;

	sleep_flags = lock_system_sleep();

	data = filp->private_data;
	if (!data->ready) {
		res = -ENODATA;
		goto Unlock;
	}
	if (!pg_offp) { /* on page boundary? */
		res = snapshot_read_next(&data->handle);
		if (res <= 0)
			goto Unlock;
	} else {
		res = PAGE_SIZE - pg_offp;
	}

	res = simple_read_from_buffer(buf, count, &pg_offp,
			data_of(data->handle), res);
	if (res > 0)
		*offp += res;

 Unlock:
	unlock_system_sleep(sleep_flags);

	return res;
}

static ssize_t snapshot_write(struct file *filp, const char __user *buf,
                              size_t count, loff_t *offp)
{
	loff_t pg_offp = *offp & ~PAGE_MASK;
	struct snapshot_data *data;
	unsigned long sleep_flags;
	ssize_t res;

	if (need_wait) {
		wait_for_device_probe();
		need_wait = false;
	}

	sleep_flags = lock_system_sleep();

	data = filp->private_data;

	if (!pg_offp) {
		res = snapshot_write_next(&data->handle);
		if (res <= 0)
			goto unlock;
	} else {
		res = PAGE_SIZE;
	}

	if (!data_of(data->handle)) {
		res = -EINVAL;
		goto unlock;
	}

	res = simple_write_to_buffer(data_of(data->handle), res, &pg_offp,
			buf, count);
	if (res > 0)
		*offp += res;
unlock:
	unlock_system_sleep(sleep_flags);

	return res;
}

struct compat_resume_swap_area {
	compat_loff_t offset;
	u32 dev;
} __packed;

static int snapshot_set_swap_area(struct snapshot_data *data,
		void __user *argp)
{
	sector_t offset;
	dev_t swdev;

	if (swsusp_swap_in_use())
		return -EPERM;

	if (in_compat_syscall()) {
		struct compat_resume_swap_area swap_area;

		if (copy_from_user(&swap_area, argp, sizeof(swap_area)))
			return -EFAULT;
		swdev = new_decode_dev(swap_area.dev);
		offset = swap_area.offset;
	} else {
		struct resume_swap_area swap_area;

		if (copy_from_user(&swap_area, argp, sizeof(swap_area)))
			return -EFAULT;
		swdev = new_decode_dev(swap_area.dev);
		offset = swap_area.offset;
	}

	/*
	 * User space encodes device types as two-byte values,
	 * so we need to recode them
	 */
	data->swap = swap_type_of(swdev, offset);
	if (data->swap < 0)
		return swdev ? -ENODEV : -EINVAL;
	data->dev = swdev;
	return 0;
}

static long snapshot_ioctl(struct file *filp, unsigned int cmd,
							unsigned long arg)
{
	int error = 0;
	struct snapshot_data *data;
	loff_t size;
	sector_t offset;

	if (need_wait) {
		wait_for_device_probe();
		need_wait = false;
	}

	if (_IOC_TYPE(cmd) != SNAPSHOT_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > SNAPSHOT_IOC_MAXNR)
		return -ENOTTY;
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (!mutex_trylock(&system_transition_mutex))
		return -EBUSY;

	lock_device_hotplug();
	data = filp->private_data;

	switch (cmd) {

	case SNAPSHOT_FREEZE:
		if (data->frozen)
			break;

		ksys_sync_helper();

		error = freeze_processes();
		if (error)
			break;

		error = create_basic_memory_bitmaps();
		if (error)
			thaw_processes();
		else
			data->frozen = true;

		break;

	case SNAPSHOT_UNFREEZE:
		if (!data->frozen || data->ready)
			break;
		pm_restore_gfp_mask();
		free_basic_memory_bitmaps();
		data->free_bitmaps = false;
		thaw_processes();
		data->frozen = false;
		break;

	case SNAPSHOT_CREATE_IMAGE:
		if (data->mode != O_RDONLY || !data->frozen  || data->ready) {
			error = -EPERM;
			break;
		}
		pm_restore_gfp_mask();
		error = hibernation_snapshot(data->platform_support);
		if (!error) {
			error = put_user(in_suspend, (int __user *)arg);
			data->ready = !freezer_test_done && !error;
			freezer_test_done = false;
		}
		break;

	case SNAPSHOT_ATOMIC_RESTORE:
		error = snapshot_write_finalize(&data->handle);
		if (error)
			break;
		if (data->mode != O_WRONLY || !data->frozen ||
		    !snapshot_image_loaded(&data->handle)) {
			error = -EPERM;
			break;
		}
		error = hibernation_restore(data->platform_support);
		break;

	case SNAPSHOT_FREE:
		swsusp_free();
		memset(&data->handle, 0, sizeof(struct snapshot_handle));
		data->ready = false;
		/*
		 * It is necessary to thaw kernel threads here, because
		 * SNAPSHOT_CREATE_IMAGE may be invoked directly after
		 * SNAPSHOT_FREE.  In that case, if kernel threads were not
		 * thawed, the preallocation of memory carried out by
		 * hibernation_snapshot() might run into problems (i.e. it
		 * might fail or even deadlock).
		 */
		thaw_kernel_threads();
		break;

	case SNAPSHOT_PREF_IMAGE_SIZE:
		image_size = arg;
		break;

	case SNAPSHOT_GET_IMAGE_SIZE:
		if (!data->ready) {
			error = -ENODATA;
			break;
		}
		size = snapshot_get_image_size();
		size <<= PAGE_SHIFT;
		error = put_user(size, (loff_t __user *)arg);
		break;

	case SNAPSHOT_AVAIL_SWAP_SIZE:
		size = count_swap_pages(data->swap, 1);
		size <<= PAGE_SHIFT;
		error = put_user(size, (loff_t __user *)arg);
		break;

	case SNAPSHOT_ALLOC_SWAP_PAGE:
		if (data->swap < 0 || data->swap >= MAX_SWAPFILES) {
			error = -ENODEV;
			break;
		}
		offset = alloc_swapdev_block(data->swap);
		if (offset) {
			offset <<= PAGE_SHIFT;
			error = put_user(offset, (loff_t __user *)arg);
		} else {
			error = -ENOSPC;
		}
		break;

	case SNAPSHOT_FREE_SWAP_PAGES:
		if (data->swap < 0 || data->swap >= MAX_SWAPFILES) {
			error = -ENODEV;
			break;
		}
		free_all_swap_pages(data->swap);
		break;

	case SNAPSHOT_S2RAM:
		if (!data->frozen) {
			error = -EPERM;
			break;
		}
		/*
		 * Tasks are frozen and the notifiers have been called with
		 * PM_HIBERNATION_PREPARE
		 */
		error = suspend_devices_and_enter(PM_SUSPEND_MEM);
		data->ready = false;
		break;

	case SNAPSHOT_PLATFORM_SUPPORT:
		data->platform_support = !!arg;
		break;

	case SNAPSHOT_POWER_OFF:
		if (data->platform_support)
			error = hibernation_platform_enter();
		break;

	case SNAPSHOT_SET_SWAP_AREA:
		error = snapshot_set_swap_area(data, (void __user *)arg);
		break;

	default:
		error = -ENOTTY;

	}

	unlock_device_hotplug();
	mutex_unlock(&system_transition_mutex);

	return error;
}

#ifdef CONFIG_COMPAT
static long
snapshot_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	BUILD_BUG_ON(sizeof(loff_t) != sizeof(compat_loff_t));

	switch (cmd) {
	case SNAPSHOT_GET_IMAGE_SIZE:
	case SNAPSHOT_AVAIL_SWAP_SIZE:
	case SNAPSHOT_ALLOC_SWAP_PAGE:
	case SNAPSHOT_CREATE_IMAGE:
	case SNAPSHOT_SET_SWAP_AREA:
		return snapshot_ioctl(file, cmd,
				      (unsigned long) compat_ptr(arg));
	default:
		return snapshot_ioctl(file, cmd, arg);
	}
}
#endif /* CONFIG_COMPAT */

static const struct file_operations snapshot_fops = {
	.open = snapshot_open,
	.release = snapshot_release,
	.read = snapshot_read,
	.write = snapshot_write,
	.unlocked_ioctl = snapshot_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = snapshot_compat_ioctl,
#endif
};

static struct miscdevice snapshot_device = {
	.minor = SNAPSHOT_MINOR,
	.name = "snapshot",
	.fops = &snapshot_fops,
};

static int __init snapshot_device_init(void)
{
	return misc_register(&snapshot_device);
};

device_initcall(snapshot_device_init);


#ifdef CONFIG_LG_SNAPSHOT_BOOT

#define LGSNAP_IOC_MAGIC		's'
#define LGSNAP_GET_IMAGE_SIZE		_IOR(LGSNAP_IOC_MAGIC, 1, u32)
#define LGSNAP_CREATE_IMAGE		_IO(LGSNAP_IOC_MAGIC, 2)
#define LGSNAP_WRITE_MAGIC		_IO(LGSNAP_IOC_MAGIC, 3)
#define LGSNAP_HIBERNATION		_IOW(LGSNAP_IOC_MAGIC, 4, u32)
#define LGSNAP_IOC_MAXNR		5

static atomic_t allow_once_lgsnap = ATOMIC_INIT(-1);
static int lgsnap_open(struct inode *inode, struct file *filp)
{
#ifndef CONFIG_LG_HIBERNATION_HACK
	/* Only allow once a power on */
	if(!atomic_inc_and_test(&allow_once_lgsnap))
		return -EPERM;
#endif

	return 0;
}

static int lgsnap_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static int lgsnap_create_image(void)
{
	int ret;

	ret = pm_autosleep_lock();
	if (ret)
		return ret;

	if (pm_autosleep_state() > PM_SUSPEND_ON) {
		ret = -EBUSY;
		goto out;
	}
	
	ret = hibernate();
	
out:
	pm_autosleep_unlock();

	return ret;
}

extern int lgsnap_image_size;
extern int lgsnap_write_magic(void);
extern int hibernation_enable;
static long lgsnap_ioctl(struct file *filp, unsigned int cmd,
						unsigned long arg)
{
	int ret = -1;

	if (_IOC_TYPE(cmd) != LGSNAP_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > LGSNAP_IOC_MAXNR)
		return -ENOTTY;
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	
	switch (cmd) {
	case LGSNAP_GET_IMAGE_SIZE:
		ret = put_user(lgsnap_image_size, (long __user *)arg);
		break;
		
	case LGSNAP_CREATE_IMAGE:
		ret = lgsnap_create_image();
		break;

	case LGSNAP_WRITE_MAGIC:
		ret = lgsnap_write_magic();
		break;

	case LGSNAP_HIBERNATION:
		ret = get_user(hibernation_enable, (long __user *)arg);
		break;

	default:
		break;
	}
	
	return ret;
}

#ifdef CONFIG_COMPAT
static long lgsnap_compat_ioctl(struct file *filp, unsigned int cmd,
						unsigned long arg)
{
	return lgsnap_ioctl(filp, cmd, arg);
}
#endif

static const struct file_operations lgsnap_fops = {
	.open = lgsnap_open,
	.release = lgsnap_release,
	.unlocked_ioctl = lgsnap_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = lgsnap_compat_ioctl,
#endif
};

static struct miscdevice lgsnap_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "lgsnap",
	.fops = &lgsnap_fops,
};

static int __init lgsnap_device_init(void)
{
	return misc_register(&lgsnap_device);
};

device_initcall(lgsnap_device_init);

#endif

#ifdef CONFIG_LG_INSTANT_BOOT

static atomic_t lgib_device_available = ATOMIC_INIT(1);

static int lgib_open(struct inode *inode, struct file *filp)
{
	if (!atomic_add_unless(&lgib_device_available, -1, 0))
		return -EBUSY;

	return 0;
}

static int lgib_release(struct inode *inode, struct file *filp)
{
	atomic_inc(&lgib_device_available);

	return 0;
}

static int lgib_suspend_to_ram(void)
{
	int ret;
	suspend_state_t state = PM_SUSPEND_MEM;

	ret = pm_autosleep_lock();
	if (ret)
		return ret;

	if (pm_autosleep_state() > PM_SUSPEND_ON) {
		ret = -EBUSY;
		goto out;
	}

	ret = pm_suspend(state);

out:
	pm_autosleep_unlock();
	return ret;
}

static long lgib_ioctl(struct file *filp, unsigned int cmd,
						unsigned long arg)
{
	int ret = -1;

	if (_IOC_TYPE(cmd) != LGIB_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > LGIB_IOC_MAXNR)
		return -ENOTTY;
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	switch (cmd) {
	case LGIB_SUSPEND_TO_RAM:
		ret = lgib_suspend_to_ram();
		break;

	default:
		break;
	}

	return ret;
}

#ifdef CONFIG_COMPAT
static long lgib_compat_ioctl(struct file *filp, unsigned int cmd,
						unsigned long arg)
{
	return lgib_ioctl(filp, cmd, arg);
}
#endif

static const struct file_operations lgib_fops = {
	.open = lgib_open,
	.release = lgib_release,
	.unlocked_ioctl = lgib_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = lgib_compat_ioctl,
#endif
};

static struct miscdevice lgib_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "lgib",
	.fops = &lgib_fops,
};

static int __init lgib_device_init(void)
{
	return misc_register(&lgib_device);
};

device_initcall(lgib_device_init);

#endif	/* CONFIG_LG_INSTANT_BOOT */

