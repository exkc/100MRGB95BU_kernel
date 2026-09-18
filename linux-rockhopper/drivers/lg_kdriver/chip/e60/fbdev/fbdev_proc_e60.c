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
 *  @author		raxis.lim
 *  @version	1.0
 *  @date		2016-05-19
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_e60.h"
#include "osd_reg_e60.h"
//#include "osd_shp_reg_e60.h"
#include "osd_afbc_reg_e60.h"
#include "osd_cco_top_reg_e60.h"

#include "proc_util.h"
#include <linux/seq_file.h>
#include <linux/delay.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/clock.h>
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
	PROC_ID_E60_OSD_SR 	= 0,
	PROC_ID_E60_OSD_SR_GAIN,
	PROC_ID_E60_DIAG_HW,
	PROC_ID_E60_HW_CTX,
	PROC_ID_E60_HEALTH_CHECK,
	PROC_ID_E60_ESTREAMER_WRITE,
	PROC_ID_E60_OSD_SETUP,
	PROC_ID_E60_OSD_SHP_CFG,
	PROC_ID_E60_MAX
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static  void	FBDEV_E60_PROC_DiagHW(struct seq_file* m);
static  void	FBDEV_E60_PROC_HealthCheck(struct seq_file* m);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRD_DEFINE(fbdev_e60_hw_diag_proc_fops, FBDEV_E60_PROC_DiagHW)
OS_PROC_SEQRD_DEFINE(fbdev_e60_hw_health_check_proc_fops, FBDEV_E60_PROC_HealthCheck)

const static OS_PROC_DESC_TABLE_T g_fbdev_e60_device_proc_table[] =
{
	// (2020/09/17) E60 에서는 OSD SHP 기능을 OSD kdriver 에서 수행하지 않음
#if 0
	{ "osd_sr",		PROC_ID_E60_OSD_SR,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "osd_sr_gain",PROC_ID_E60_OSD_SR_GAIN,OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
#endif
	{ "diag", 		PROC_ID_E60_DIAG_HW,	OS_PROC_FLAG_SEQRD, (void*)&fbdev_e60_hw_diag_proc_fops },
	{ "hw_ctx",		PROC_ID_E60_HW_CTX,	OS_PROC_FLAG_SEQRD, (void*)&fbdev_e60_hw_diag_proc_fops },
	{ "check_stuck",PROC_ID_E60_HEALTH_CHECK,OS_PROC_FLAG_SEQRD, (void*)&fbdev_e60_hw_health_check_proc_fops },
	{ "estreamer_write", PROC_ID_E60_ESTREAMER_WRITE, OS_PROC_FLAG_WRITE },
    { "osd_setup",	PROC_ID_E60_OSD_SETUP,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "osd_shp_cfg",PROC_ID_E60_OSD_SHP_CFG,OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    {  NULL,		PROC_ID_E60_MAX     	,0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static  void	FBDEV_E60_PROC_DiagHW(struct seq_file* m)
{
	FBDEV_E60_CMN_DiagHW(m);
}

static  void	FBDEV_E60_PROC_HealthCheck(struct seq_file* m)
{
#if FBDEV_E60_NOT_IMPL("register map 봐야 함")
	int	i;
	UINT32	mon_reg;

	UINT64 time_start = local_clock();
	UINT32 diff_ns;

	for (i=1000; i>0; i--)
	{
		OSDX_E60_RdFL(osd_status_mon_data[0], reg_status_mon_data);
		mon_reg = OSDX_E60_Rd(osd_status_mon_data[0], reg_status_mon_data);

		diff_ns = (UINT32)local_clock() - time_start;

		/* print diff_us & mon_data */
		seq_printf(m, "%8d %8d %8d\n", diff_ns/1000, mon_reg, (mon_reg & ~0x40000) );

		udelay(100);
	}
#else
	seq_printf(m, "n/a\n");
#endif
}

static int FBDEV_E60_ReadProcFunc( UINT32 procId, char* buffer )
{
    int ret;

    /* TODO: add your proc_write implementation */
    switch(procId)
    {
        case PROC_ID_E60_OSD_SR:
        {
#if FBDEV_E60_NOT_IMPL("아직 미구현")
            int len = 0;
            len += sprintf( buffer + len, "[usage] echo value > /proc/lg/fbdev/chip/osd_sr\n");
            len += sprintf( buffer + len, "        value = 0:off, 1:on\n");
            ret = len;
#else
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
#endif
        }
        break;

		case PROC_ID_E60_OSD_SR_GAIN:
        {
#if FBDEV_E60_NOT_IMPL("아직 미구현")
			UINT32 gain;
			int len = 0;

			 FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

			 SHP_CTRL_RdFL(0, shp_lti_ctrl_00);
			 SHP_CTRL_Rd01(0, shp_lti_ctrl_00, reg_lti_2d_gain, gain);

			/* print user-requested gain value & real HW value which normalized to 8bit */
			len += sprintf( buffer + len, "sw=%3d hw=%3dn", hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain, gain);
            len += sprintf( buffer + len, "[usage] echo value > /proc/lg/fbdev/chip/osd_sr_gain\n");
            len += sprintf( buffer + len, "        value = 0~255\n");
			ret = len;
#else
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
#endif
 		}
		break;

		case PROC_ID_E60_OSD_SETUP:
		{
            int len = 0;
            len += sprintf( buffer + len, "re-setup osd layer for test\n");
            len += sprintf( buffer + len, "[usage] echo fbId > /proc/lg/fbdev/chip/osd_setup\n");
            len += sprintf( buffer + len, "        fbId = 0:fb0 1:fb1 3:fb3\n");
            ret = len;
		}
		break;

		case PROC_ID_E60_OSD_SHP_CFG:
		{
            int len = 0;
            len += sprintf( buffer + len, "test osd sharpness config\n");
            len += sprintf( buffer + len, "[usage] echo val > /proc/lg/fbdev/chip/osd_shp_cfg\n");
            len += sprintf( buffer + len, "        val = hd, fhd, uhdn");
            ret = len;

		}
		break;

		case PROC_ID_E60_HW_CTX:
		{

			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
		}
		break;

		default:
		{
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

static int FBDEV_E60_WriteProcFunc( UINT32 procId, char* command )
{
    switch( procId )
    {
        case PROC_ID_E60_OSD_SR:
        {
            int onoff;

            sscanf(command, " %d", &onoff);

			FBDEV_E60_CMN_SRCtrl((onoff==1)? TRUE:FALSE);
        }
        break;

        case PROC_ID_E60_OSD_SR_GAIN:
        {
#if FBDEV_E60_NOT_IMPL("아직 미구현")
            UINT32 gain;
            FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

            sscanf(command, " 0x%x", &gain);

            /* if gain is not valid 8bit value, DO NOT change HW gain configuration */
            if (gain & 0xffffff00 ) break;

            hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain = gain;

			SHP_CTRL_RdFL(0, shp_lti_ctrl_00);
			SHP_CTRL_Wr01(0, shp_lti_ctrl_00, reg_lti_2d_gain, gain);
			SHP_CTRL_WrFL(0, shp_lti_ctrl_00);
#endif
        }
        break;

		case PROC_ID_E60_ESTREAMER_WRITE:
		{
#if FBDEV_E60_NOT_IMPL("아직 미구현")
			UINT32	fbmem;
			int		width = 1024;
			int		height= 4320;
			int		xoffset = 0;
			int		en		= 1;

            sscanf(command, " 0x%x", &fbmem);

			FBDEV_NOTI("++ write estreamer y:0x%08x c:0x%08x xoff:%d en:%d\n", fbmem, fbmem + (width*height), xoffset, en);

			OS_WrReg(0xC9011520, fbmem);
			OS_WrReg(0xC9011524, fbmem + (width*height));
			OS_WrReg(0xC9011528, (en<<16) | (xoffset & 0xffff));
#endif
		}
		break;

		case PROC_ID_E60_OSD_SETUP:
		{
			UINT32 fb_dev_id;
            sscanf(command, " %d", &fb_dev_id);

			FBDEV_E60_CMN_InitOSDLayer(fb_dev_id);
		}
		break;

		case PROC_ID_E60_OSD_SHP_CFG:
		{
            FBDEV_HW_CMD_DATA_T hw_cmd;
			UINT32 osd_res_info = 0;

			if (!strncasecmp(command, "hd", strlen("hd")))
			{
				osd_res_info = 1;
			}
			else if (!strncasecmp(command, "fhd", strlen("fhd")) || !strncasecmp(command, "2k", strlen("2k")))
			{
				osd_res_info = 2;
			}
			else if (!strncasecmp(command, "uhd", strlen("uhd")) || !strncasecmp(command, "4k", strlen("4k")))
			{
				osd_res_info = 3;
			}
			else
			{
				FBDEV_WARN("unknown args: %s\n", command);
				osd_res_info = 0;
			}

            hw_cmd.gen[0] = LX_FBDEV_ID_OSD0;
            hw_cmd.gen[1] = osd_res_info;

            (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_OSD_SHP_AUTO_CONFIG, &hw_cmd);
		}
		break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return strlen(command);
}

void	FBDEV_E60_CreateProc ( struct proc_dir_entry* parent_proc )
{
    OS_PROC_CreateEntry("chip", parent_proc, (OS_PROC_DESC_TABLE_T*)g_fbdev_e60_device_proc_table,
									FBDEV_E60_ReadProcFunc,
                                    FBDEV_E60_WriteProcFunc);
}

