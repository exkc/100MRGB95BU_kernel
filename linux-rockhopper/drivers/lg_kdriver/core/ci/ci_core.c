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
 *  Core driver implementation for ci device.
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2010.02.19
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
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/cdev.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/memory.h>

#include "ci_util.h"
#include "ci_dev.h"
#include "ci_core.h"
#include "ci_hw_ops.h"

///////////////////////////////////////////////////////////////////////////////

/**
 * @brief
 *   core bridge function : H/W suspend
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CORE_Suspend(CI_DEV_T *cidev)
{
	int ret = 0;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ret = CI_OPS_Suspend(cidev);
	return ret;
}

/**
 * @brief
 *   core bridge function : H/W resume
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CORE_Resume(CI_DEV_T *cidev)
{
	int ret = 0;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ret = CI_OPS_Resume(cidev);
	return ret;
}

/**
 * @brief
 *   core bridge function : Initialize CI host block
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CORE_Init(CI_DEV_T *cidev)
{
	int ret = 0;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ret = CI_OPS_Init(cidev);
	return ret;
}

/**
 * @brief
 *   core bridge function : Uninitialize CI host block
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CORE_Uninit(CI_DEV_T *cidev)
{
	int ret = 0;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ret = CI_OPS_Uninit(cidev);
	return ret;
}

#define CI_PRINT_DELAY(_idx, _cidev, _target)	\
	LOGM_PRINT(g_ci_debug_fd, _idx, "[%02d] %32s [%4d] \n",	\
		_target,									\
		ci_get_delaystr(_target),					\
		_cidev->cfg->delays[_target])

/**
 * @brief
 *   core bridge function : show current delay parameters
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CORE_ShowDelays(CI_DEV_T *cidev, int level)
{
	int i;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	for(i=0; i< DELAY_ENTRY_MAX; i++)
	{
		CI_PRINT_DELAY(level, cidev, i);
	}

	return 0;
}

