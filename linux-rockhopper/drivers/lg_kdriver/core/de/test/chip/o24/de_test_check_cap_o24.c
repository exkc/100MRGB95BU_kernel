/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 *	main driver implementation for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *	author
 *	version
 *	date
 *	note
 *
 *	@addtogroup
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
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/delay.h>

#include "os_util.h"
#include "base_device.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "util/de_test_util_o24.h"

#include "be_kapi.h"
#include "../../../../be/be_def.h"
#include "../../../../be/frc/frc_hal.h"

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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int v4l2_vsc_getlocalmute(int win);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int de_test_check_cap_o24_run(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_test_check_cap_o24_run(void)
{
	int ret = 1;
	static int start = 0;
	UINT32 pos_x=(1920+960);//view center pos
	UINT32 pos_y=(1080+540);//view center pos
	char *pat_str = "red(rgb)_cap";

	do {
		if (!start)
		{
			DE_NOTI("open\n");
			if (0 != (ret = de_test_util_o24_input_open("hdmi","4k","4k"))) {DE_ERROR("de_test_util_o24_input_open err\n");break;}
			start = 1;
			ret = 1;
			break;
		}

		if (0 != v4l2_vsc_getlocalmute(0))
		{
			DE_NOTI("local mute (%d)\n",v4l2_vsc_getlocalmute(0));
			if (++start>10)
			{
				DE_ERROR("local mute time out\n");
				ret = -1;
			}
			break;
		}

		#ifdef INCLUDE_KDRV_BE
		{
			//Usage : VTG [off(0)/on_dsp(1)/on_src(2)/on_osd(3)] [0(4K#5)/1(2K#3)/2(2K#1)/3(1K#1)] <freeze>
			LX_BE_FRC_CMD_T cmd = {.str="vtg 2 2"};
			DE_NOTI("cmd (%s)\n",cmd.str);
			if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
		}
		{
			#if 0
			Usage : VIEW bufid
			- bufid :
			2 = MVI_R2
			5 = M0_CAP
			8 = M0_TNR
			9 = M1_TNR
			10 = M0_OSC
			11 = M1_OSC
			12 = M1_CAP
			13 = S0_CAP
			14 = C0_CAP
			18 = D1_CAP
			19 = S0_CAP2
			20 = G1_CAP
			#endif
			LX_BE_FRC_CMD_T cmd = {.str="view 14"};
			DE_NOTI("cmd (%s)\n",cmd.str);
			if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
		}
		#endif

		msleep(500);

		DE_NOTI("run(%s)\n",pat_str);
		if (0 != (ret = de_test_util_o24_cvi_pat_on(pat_str))) {DE_ERROR("de_test_util_o24_cvi_pat_on(%s) err\n",pat_str);break;}
		if (0 != (ret = de_test_util_o24_check_cvi_o_pixel(pat_str,pos_x,pos_y))) {DE_ERROR("de_test_util_o24_check_cvi_o_pixel(%s) err\n",pat_str);break;}
	} while (0);

	if (ret<=0)
	{
		#ifdef INCLUDE_KDRV_BE
		{
			LX_BE_FRC_CMD_T cmd = {.str="vtg 0 0"};
			DE_NOTI("cmd (%s)\n",cmd.str);
			if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
		}
		{
			LX_BE_FRC_CMD_T cmd = {.str="view 0"};
			DE_NOTI("cmd (%s)\n",cmd.str);
			if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
		}
		#endif
		if (0 != de_test_util_o24_cvi_pat_off()) {DE_ERROR("de_test_util_o24_cvi_pat_off err\n");return -1;}
		if (0 != de_test_util_o24_input_close()) {DE_ERROR("de_test_util_o24_input_close err\n");return -1;}
		DE_NOTI("close\n");
		start = 0;
	}

	DE_NOTI("ret : %d\n",ret);
	return ret;
}
