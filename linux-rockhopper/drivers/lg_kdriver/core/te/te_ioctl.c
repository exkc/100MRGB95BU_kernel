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
 *  ioctl function for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-03-28
 *  @note		Additional information.
 */

#include "te_impl.h"

#define log_ioctl_error(cmd, fmt, args...) \
 log_error("IOCTL('%c',%d) ERROR - " fmt, _IOC_TYPE(cmd), _IOC_NR(cmd), ##args)

int te_ioctl_usercopy(unsigned int cmd, unsigned long arg, te_ioctl_func_t func,
		      te_ioctl_param_func_t get_user_ptr, void *priv)
{
	int ret;
	u8 sparam[128];
	u32 ioc_size;
	struct te_ioctl_ptr_param ptr_param;
	void *mparam = NULL;
	void *ptr_buf = NULL;
	void *parg;

	ptr_param.dir = _IOC_NONE;
	if (_IOC_DIR(cmd) == _IOC_NONE) {
		ioc_size = 0;
		parg = (void *)arg;
	} else {
		ioc_size = _IOC_SIZE(cmd);

		/* if argments size over max sparam than allocate it  */
		if (ioc_size > sizeof(sparam)) {
			mparam = kmalloc(ioc_size, GFP_KERNEL);
			if (!mparam)
				return -ENOMEM;
			parg = mparam;
		} else {
			parg = sparam;
		}

		if (_IOC_DIR(cmd) & _IOC_WRITE) {
			/* copy arguments into kernel buffer */
			if (copy_from_user(parg, (void __user *)arg, ioc_size)) {
				log_ioctl_error(cmd,
						"copy_from_user argument\n");
				ret = -EFAULT;
				goto exit;
			}

			if (get_user_ptr) {
				if (get_user_ptr(priv, cmd, parg, &ptr_param)) {
					log_ioctl_error(cmd, "get_user_ptr\n");
					ret = -EFAULT;
					goto exit;
				}
			}
		}
	}

	if (ptr_param.dir != _IOC_NONE) {
		ptr_buf = kmalloc(ptr_param.size, GFP_KERNEL);
		if (!ptr_buf) {
			ret = -ENOMEM;
			goto exit;
		}

		*ptr_param.kernel_ptr = ptr_buf;
		if (ptr_param.dir & _IOC_WRITE) {
			/* copy arguments into kernel buffer */
			if (copy_from_user
			    (ptr_buf, ptr_param.user_ptr, ptr_param.size)) {
				log_ioctl_error(cmd,
						"copy_from_user user_ptr\n");
				ret = -EFAULT;
				goto exit;
			}
		}
	}

	ret = func(priv, cmd, parg);
	if (ret < 0)
		goto exit;

	if (ptr_param.dir != _IOC_NONE) {
		/* restore user ptr */
		*ptr_param.kernel_ptr = (void __force *)ptr_param.user_ptr;
		if (ptr_param.dir & _IOC_READ) {
			if (copy_to_user
			    (ptr_param.user_ptr, ptr_buf, ptr_param.size)) {
				log_ioctl_error(cmd, "copy_to_user user_ptr\n");
				ret = -EFAULT;
				goto exit;
			}
		}
	}

	if (_IOC_DIR(cmd) & _IOC_READ) {
		if (copy_to_user((void __user *)arg, parg, ioc_size)) {
			log_ioctl_error(cmd, "copy_to_user argument\n");
			ret = -EFAULT;
			goto exit;
		}
	}

 exit:
	if (ptr_buf)
		kfree(ptr_buf);
	if (mparam)
		kfree(mparam);

	return ret;
}

int te_ioctl_cache_ctrl(LX_TE_CACHE_CTRL_T *ctrl)
{
	int ret;
	enum te_data_direction dir;
	void *vaddr = (void __force *)te_ioctl_get_user_ptr(ctrl->vaddr);

	if (ctrl->op == LX_TE_CACHE_OP_INVAL)
		dir = TE_DATA_FROM_DEVICE;
	else
		dir = TE_DATA_TO_DEVICE;

	ret = te_cache_sync(ctrl->paddr, vaddr, ctrl->size, dir);

	return ret;
}
