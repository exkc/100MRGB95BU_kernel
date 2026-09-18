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
 *  main driver implementation for ci device.
 *	ci device will teach you how to make device driver with new platform.
 *
 *  author		Srinivasan Shanmugam	(srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#if	defined(KDRV_CONFIG_PM)	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "ci_util.h"
#include "ci_dev.h"
#include "ci_core.h"
#include "ci_ioctl.h"
#include "ci_hw_ops.h"
#include "ci_hw_cis.h"

/*
struct ci_param_opt {
	u32		func;
	u32		mode;
};
typedef struct ci_param_opt ci_param_opt_t;

struct ci_param_io {
	u8 		*buf;
	u16		size;
};
typedef struct ci_param_io ci_param_io_t;

struct ci_param_delay {
	u32		idx;
	u32		val;
};
typedef struct ci_param_delay ci_param_delay_t;
*/

union ci_param {
	u32										card_detect;
	u32										nego_buff_size;
	LX_CI_IOCTL_PARAM_CAMTYPE				cam_type;
	LX_CI_IOCTL_PARAM_VERSION				version;
	LX_CI_IOCTL_PARAM_OPROFILE				profile;
	LX_CI_IOCTL_PARAM_SPEED					speed;
	LX_CI_IOCTL_PARAM_ACCESSMODE_CHANGE		mode;
	LX_CI_IOCTL_PARAM_OPTION				option;
	u32										da_status;
	u32										iir_status;
	u32										mask;
	LX_CI_IOCTL_PARAM_T						io_access;
	LX_CI_IOCTL_PARAM_SETDELAY				delay;
	LX_CI_IOCTL_PARAM_REGISTER				reg;
};
typedef union ci_param ci_param_t; //FIXME: Remove!

typedef struct
{
	void __user		*user_ptr;		/* buffer pointer in ioctl param */
	void 			**kernel_ptr;	/* address of buffer pointer variable  */
	size_t			size;			/* size of buffer in ioctl param */
	int				dir;			/* _IOC_READ or _IOC_WRITE */
} IOCTL_USER_PTR_PARAM_T;

#ifdef CONFIG_COMPAT
#define IOCTL_GET_USER_PTR(ptr)					\
({												\
	void __user *uptr = (void __user*)(ptr);	\
	if(is_compat_task())						\
	{											\
		compat_uptr_t cptr = ptr_to_compat(uptr);	\
		uptr = compat_ptr(cptr);				\
	}											\
	uptr;										\
})
#else
#define IOCTL_GET_USER_PTR(ptr)	(void __user*)(ptr)
#endif

#define IOCTL_COPY_FROM_USER(to,from,n,fail_action) 		\
 {															\
	if (copy_from_user((void*)to, (void __user *)from, n)) {\
		LOG_ERROR("copy_from_user. magic:%c,num:%d\n", _IOC_TYPE(cmd), _IOC_NR(cmd)); \
		ret = -EFAULT;										\
		fail_action;										\
	}														\
}

#define IOCTL_COPY_TO_USER(to,from,n,fail_action)			\
{															\
	if (copy_to_user((void __user*)to, (void *)from, n)) {	\
		LOG_ERROR("copy_to_user. magic:%c,num:%d\n", _IOC_TYPE(cmd), _IOC_NR(cmd)); \
		ret = -EFAULT;										\
		fail_action;										\
	}														\
}

#define CI_GET_CIDEV_FROM_CHRDEV_DATA

/* !!! see ci_dev_base_open in ci_dev.c*/
int ci_open(struct inode *inode, struct file *filp)
{
	CI_DEV_T *cidev;
	int ret = 0;

	cidev = container_of(inode->i_cdev, CI_DEV_T, cdev);
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}

	CI_MUTEX_LOCK(cidev);

	if (!cidev->dev_open_count) {

	}

	filp->private_data = cidev;
	cidev->dev_open_count++;

	LOG_DBG1("> Open CI device file (%d:%d) cnt[%d]\n",
			imajor(inode), iminor(inode), cidev->dev_open_count);

	CI_MUTEX_UNLOCK(cidev);
	return ret;
}

int ci_close(struct inode *inode, struct file *filp)
{
	CI_DEV_T *cidev = filp->private_data;
	int ret = 0;

	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}

	CI_MUTEX_LOCK(cidev);

	if (cidev->dev_open_count) {
		cidev->dev_open_count--;
		if (!cidev->dev_open_count) {

		}
	}

	filp->private_data = NULL;

	LOG_DBG1("> Close CI device file (%d:%d) cnt[%d]\n",
			imajor(inode), iminor(inode), cidev->dev_open_count);

	CI_MUTEX_UNLOCK(cidev);
	return ret;
}

static int IOCTL_Reset(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_Reset(cidev);
}

static int IOCTL_CAMInit(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_CAMInit(cidev);
}

static int IOCTL_CAMOff(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_CAMOff(cidev);
}

static int IOCTL_CAMOnCompleted(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_CAMOnCompleted(cidev);
}

static int IOCTL_SetPhysReset(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_SetPhysReset(cidev);
}

static int IOCTL_SetRS(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_SetRS(cidev);
}

static int IOCTL_CheckCIS(CI_DEV_T *cidev, void *parg)
{
	return CI_CIS_CheckCIS(cidev);
}

static int IOCTL_WriteCOR(CI_DEV_T *cidev, void *parg)
{
	return CI_CIS_WriteCOR(cidev);
}

static int IOCTL_NegoBuff(CI_DEV_T *cidev, void *parg)
{
	UINT32* nego_buff_size = parg;
	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	return CI_OPS_NegoBuff(cidev, nego_buff_size);
}

static int IOCTL_DetectCard(CI_DEV_T *cidev, void *parg)
{
	UINT32* card_detect = parg;
	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	return CI_OPS_DetectCard(cidev, card_detect);
}

static int IOCTL_CheckCapability(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_CAMTYPE *cam_type = parg;
	UINT32 chk_cam_type;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_CheckCapability(cidev, &chk_cam_type);
	if (ret == 0)
	{
		cam_type->uwCheckCAMType = chk_cam_type;
		cam_type->uwRtnValue = (chk_cam_type == -1)? -1 : 0;
	}
	else
	{
		cam_type->uwRtnValue = -1;
	}

	return ret;
}

static int IOCTL_GetCiplusVer(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_VERSION *version = parg;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_GetCiplusVer(cidev, &version->uwVersion);
	if (ret == 0)
	{
		version->uwRtnValue = (version->uwVersion == -1)? -1 : 0;
	}
	else
	{
		version->uwRtnValue = -1;
	}

	return ret;
}

static int IOCTL_GetCiplusOPProfile(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_OPROFILE *profile = parg;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_GetCiplusOPProfile(cidev, &profile->uwProfile);
	if (ret == 0)
	{
		profile->uwRtnValue = (profile->uwProfile == -1)? -1 : 0;
	}
	else
	{
		profile->uwRtnValue = -1;
	}

	return ret;
}

static int IOCTL_SetPcmciaSpeed(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_SPEED *speed = parg;
	UINT32 bus_speed;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	bus_speed = (speed->ui8Speed) ? PCMCIA_BUS_SPEED_HIGH : PCMCIA_BUS_SPEED_LOW;

	ret = CI_OPS_SetPcmciaSpeed(cidev, bus_speed);
	CHECK_ERROR(ret != 0, , "error : pcmcia speed - s[0x%X]\n", bus_speed);

	return ret;
}

static int IOCTL_ChangeAccessMode(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_ACCESSMODE_CHANGE *mode = parg;
	int t_mode;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	if (mode->ui32Mode == 0)
		t_mode = ACCESS_1BYTE_MODE;
	else if (mode->ui32Mode == 1)
		t_mode = ACCESS_2BYTE_MODE;
	else
		t_mode = ACCESS_4BYTE_MODE;

	ret = CI_OPS_ChangeAccessMode(cidev, t_mode);

	return ret;
}

static int IOCTL_ControlOption(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_OPTION *option = parg;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_ControlOption(cidev, option->ui32Option, &option->ui32Value);

	return ret;
}

static int IOCTL_ReadDAStatus(CI_DEV_T *cidev, void *parg)
{
	UINT32 *da_status = parg;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_ReadDAStatus(cidev, da_status);
	if(ret != 0)
	{
		LOG_ERROR("error: da_status");
		*da_status = 0;
	}
	else
	{
		LOG_INFO("DA register status : 0x%0X", *da_status);
	}

	return ret;
}

static int IOCTL_ReadIIRStatus(CI_DEV_T *cidev, void *parg)
{
	UINT32 *iir_status = parg;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_ReadIIRStatus(cidev, iir_status);
	if(ret != 0)
	{
		LOG_ERROR("error: iir_status");
		*iir_status = 0;
	}
	else
	{
		LOG_INFO("READ IIR status : 0x%0X", *iir_status);
	}

	return ret;
}


static int IOCTL_ReadData(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_T *io_access = parg;
	UINT8 *rbuf;

	UINT32 rsize;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	/* user buf control is inside function */
	io_access->pBuf = IOCTL_GET_USER_PTR(io_access->pBuf);

	rbuf = io_access->pBuf;
	rsize = io_access->sLength;

	ret = CI_OPS_IO_ReadData(cidev, rbuf, &rsize);
	io_access->sLength = rsize;

	return ret;
}

static int IOCTL_WriteData(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_T *io_access = parg;
	UINT8 *wbuf;
	UINT32 wsize;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	/* user buf control is inside function */
	io_access->pBuf = IOCTL_GET_USER_PTR(io_access->pBuf);

	wbuf = io_access->pBuf;
	wsize = io_access->sLength;

	ret = CI_OPS_IO_WriteData(cidev, wbuf, wsize);

	return ret;
}

static int IOCTL_EnableLog(CI_DEV_T *cidev, void *parg)
{
	UINT32 *mask = parg;
	int ret = 0;
	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_DEBUG_SetLog(cidev, *mask);
	return ret;
}

static int IOCTL_ShowDelays(CI_DEV_T *cidev, void *parg)
{
	return CI_CORE_ShowDelays(cidev, LOG_LEVEL_NOTI);
}

static int IOCTL_ShowRegs(CI_DEV_T *cidev, void *parg)
{
	return CI_OPS_ShowRegisters(cidev);
}

static int IOCTL_WriteReg(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_PARAM_REGISTER *reg = parg;
	int ret = 0;

	CHECK_ERROR(!parg, return -EINVAL, "NULL parg");

	ret = CI_OPS_WriteReg(cidev, reg->uiOffset, reg->uiValue);
	if (ret != 0)
	{
		LOG_ERROR("error : write reg, i[0x%04X] v[0x%04X]\n", reg->uiOffset, reg->uiValue);
	}

	return ret;
}

static int IOCTL_DataTest(CI_DEV_T *cidev, void *parg)
{
	LOG_WARNING("IOCTL(CI_IO_DATA_TEST) disabled\n");
	return 0;
}

static int IOCTL_GetCISInfo(CI_DEV_T *cidev, void *parg)
{
	LX_CI_IOCTL_GET_CIS_INFO_T *p = parg;
	IOCTL_USER_PTR_PARAM_T param;
	void * ptr_buf = NULL;
	int rc;

	//TODO: Integrate to IoctlParam (All)
	param.user_ptr		= IOCTL_GET_USER_PTR(p->buf);
	param.kernel_ptr	= (void**)&p->buf;
	param.dir			= _IOC_READ;
	param.size			= p->maxlen;

	ptr_buf = kmalloc(param.size, GFP_KERNEL);
	if(ptr_buf == NULL) return -ENOMEM;

	*param.kernel_ptr = ptr_buf; //use kmalloc ptr

	rc = CI_CIS_GetCISString(cidev, p->tuplecode, &p->len, p->buf, p->maxlen);

	*param.kernel_ptr = param.user_ptr;
	if(rc == 0) //Only copy on success
	{
		if(copy_to_user((void __user*)param.user_ptr, (void *)ptr_buf, p->len))
		{
			LOG_ERROR("fail copy_to_user");
		}
	}

	if(ptr_buf) kfree(ptr_buf);
	return rc;
}

static int CI_IoctlDevice(struct file *filp, unsigned int cmd, void *parg)
{
	int ret = RET_ERROR;
	CI_DEV_T *cidev;
	int i, total;
	const DEV_IOCTL_FUNC_T ioctl_func[] =
	{
		IOCTL_FUNC_TYPE(CI_IO_RESET, IOCTL_Reset),
		IOCTL_FUNC_TYPE(CI_IOR_CAM_INIT, IOCTL_CAMInit),
		IOCTL_FUNC_TYPE(CI_IOR_CAM_POWEROFF, IOCTL_CAMOff),
		IOCTL_FUNC_TYPE(CI_IOR_CAM_POWERONCOMPLETED, IOCTL_CAMOnCompleted),
		IOCTL_FUNC_TYPE(CI_IO_SET_PHY_RESET, IOCTL_SetPhysReset),
		IOCTL_FUNC_TYPE(CI_IO_SET_RS, IOCTL_SetRS),

		IOCTL_FUNC_TYPE(CI_IOR_DETECT_CARD, IOCTL_DetectCard),
		IOCTL_FUNC_TYPE(CI_IO_CHECK_CIS, IOCTL_CheckCIS),
		IOCTL_FUNC_TYPE(CI_IO_WRITE_COR, IOCTL_WriteCOR),
		IOCTL_FUNC_TYPE(CI_IOR_NEGOTIATE_BUF_SIZE, IOCTL_NegoBuff),
		IOCTL_FUNC_TYPE(CI_IOR_CHECK_CAPABILITY, IOCTL_CheckCapability),
		IOCTL_FUNC_TYPE(CI_IOR_GET_CIPLUS_VERSION, IOCTL_GetCiplusVer),
		IOCTL_FUNC_TYPE(CI_IOR_GET_CIPLUS_OPROFILE, IOCTL_GetCiplusOPProfile),
		IOCTL_FUNC_TYPE(CI_IOW_SET_PCMCIA_SPEED, IOCTL_SetPcmciaSpeed),
		IOCTL_FUNC_TYPE(CI_IOW_CHANGE_ACCESSMODE, IOCTL_ChangeAccessMode),
		IOCTL_FUNC_TYPE(CI_IOWR_OPTION, IOCTL_ControlOption),

		IOCTL_FUNC_TYPE(CI_IOR_READ_DA_STATUS, IOCTL_ReadDAStatus),
		IOCTL_FUNC_TYPE(CI_IOR_READ_IIR_STATUS, IOCTL_ReadIIRStatus),
		IOCTL_FUNC_TYPE(CI_IOR_READ_DATA, IOCTL_ReadData),
		IOCTL_FUNC_TYPE(CI_IOW_WRITE_DATA, IOCTL_WriteData),

		IOCTL_FUNC_TYPE(CI_IOW_ENABLE_LOG, IOCTL_EnableLog),
		IOCTL_FUNC_TYPE(CI_IO_CAM_PRINT_DELAY_VALUES, IOCTL_ShowDelays),
		IOCTL_FUNC_TYPE(CI_IOR_PRINT_REG, IOCTL_ShowRegs),
		IOCTL_FUNC_TYPE(CI_IO_READ_REGISTERS, IOCTL_ShowRegs),
		IOCTL_FUNC_TYPE(CI_IOW_WRITE_REGISTER, IOCTL_WriteReg),

		IOCTL_FUNC_TYPE(CI_IO_DATA_TEST, IOCTL_DataTest),
		IOCTL_FUNC_TYPE(CI_IOWR_GET_CIS_INFO, IOCTL_GetCISInfo),
	};
	const DEV_IOCTL_FUNC_T *f;

	CHECK_ERROR(filp == NULL, return -EINVAL, "filp is NULL");

	cidev = filp->private_data;
	CHECK_ERROR(cidev == NULL, return -EINVAL, "cidev is NULL");
	CHECK_ERROR(!cidev->dev_open_count, return -EINVAL, "dev_open_count is zero");

	total = sizeof(ioctl_func)/sizeof(DEV_IOCTL_FUNC_T);

	for(i=0; i<total; i++)
	{
		f = &ioctl_func[i];
		if(cmd == f->ioctl_num)
		{
			CI_MUTEX_LOCK(cidev);
			ret = f->func(cidev, parg);
			CI_MUTEX_UNLOCK(cidev);

			CHECK_ERROR(ret < 0, goto func_exit, "%s failed:[%d]", f->name, ret);
			break;
		}

	}

	if(i == total)
	{
		LOG_ERROR("invalid command[0x%08x], magic=0x%02x, num=%d",
					cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		goto func_exit;
	}

func_exit:
	return ret;
}


static int CI_Ioctl(struct file *filp,
			unsigned int cmd, unsigned long arg,
			int (*func)(struct file *filp, unsigned int cmd, void *arg))
{
	UINT8 param[128];
	int ioc_dir;
	int ret  = -EINVAL;
	int ioc_size;

	BUG_ON(func == NULL);

	ioc_dir = _IOC_DIR(cmd);

	if(ioc_dir == _IOC_NONE)
	{
		ioc_size = 0;
	}
	else
	{
		ioc_size = _IOC_SIZE(cmd);

		if(ioc_size > sizeof(param))
		{
			LOG_ERROR("invalid ioctl. magic:%c,num:%d,size:%d\n",
				_IOC_TYPE(cmd), _IOC_NR(cmd), ioc_size);
			return -ENOMEM;
		}

		if(ioc_dir & _IOC_WRITE)
		{
			/* copy arguments into kernel buffer */
			IOCTL_COPY_FROM_USER(param, arg, ioc_size, return -EFAULT);

			//TODO: do user pointer handling
		}
	}

	/* call driver */
	ret = func(filp, cmd, (void*) param);

	if (ret < 0) {
		goto out;
	}

	//TODO: do user pointer handling

	if(ioc_dir & _IOC_READ)
	{
		IOCTL_COPY_TO_USER(arg, param, ioc_size, goto out);
	}

out:
	return ret;
}


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	return CI_Ioctl(filp, cmd, arg, CI_IoctlDevice);
}
#else
static long ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return (long)CI_Ioctl(filp, cmd, arg, CI_IoctlDevice);
}
#endif

const struct file_operations ci_fops_base =
{
	.open			= ci_open,
	.release		= ci_close,
	.unlocked_ioctl	= ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= ioctl,
#endif
#ifdef SUPPORT_CI_DEVICE_READ_WRITE_FOPS
	.read		 	= ci_read,
	.write 			= ci_write,
#else
	.read			= NULL,
	.write			= NULL,
#endif
};

