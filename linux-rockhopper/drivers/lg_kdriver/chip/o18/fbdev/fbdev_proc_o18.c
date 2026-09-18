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
#include "fbdev_hw_o18.h"
#include "osd_reg_o18.h"
#include "osd_shp_reg_o18.h"
#include "osd_afbc_reg_o18.h"
#include "top_ctrl_osd_reg_o18.h"

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
	PROC_ID_O18_OSD_SR 	= 0,
	PROC_ID_O18_OSD_SR_GAIN,
	PROC_ID_O18_DIAG_HW,
	PROC_ID_O18_HEALTH_CHECK,
	PROC_ID_O18_MAX
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static  void	FBDEV_O18_PROC_DiagHW(struct seq_file* m);
static  void	FBDEV_O18_PROC_HealthCheck(struct seq_file* m);

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
OS_PROC_SEQRD_DEFINE(fbdev_o18_hw_diag_proc_fops, FBDEV_O18_PROC_DiagHW)
OS_PROC_SEQRD_DEFINE(fbdev_o18_hw_health_check_proc_fops, FBDEV_O18_PROC_HealthCheck)

const static OS_PROC_DESC_TABLE_T g_fbdev_o18_device_proc_table[] =
{
    { "osd_sr",		PROC_ID_O18_OSD_SR,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "osd_sr_gain",PROC_ID_O18_OSD_SR_GAIN,OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "diag", 		PROC_ID_O18_DIAG_HW,	OS_PROC_FLAG_SEQRD, (void*)&fbdev_o18_hw_diag_proc_fops },
	{ "check_stuck",PROC_ID_O18_HEALTH_CHECK,OS_PROC_FLAG_SEQRD, (void*)&fbdev_o18_hw_health_check_proc_fops },
    {  NULL,		PROC_ID_O18_MAX     	,0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static  void	FBDEV_O18_PROC_DiagHW(struct seq_file* m)
{
	FBDEV_O18_CMN_DiagHW(m);
}

static  void	FBDEV_O18_PROC_HealthCheck(struct seq_file* m)
{
	int	i;
	UINT32	mon_reg;

	UINT64 time_start = local_clock();
	UINT32 diff_ns;

	for (i=1000; i>0; i--)
	{
		OSDX_O18_RdFL(osd_status_mon_data[0], reg_status_mon_data);
		mon_reg = OSDX_O18_Rd(osd_status_mon_data[0], reg_status_mon_data);

		diff_ns = (UINT32)local_clock() - time_start;

		/* print diff_us & mon_data */
		seq_printf(m, "%8d %8d %8d\n", diff_ns/1000, mon_reg, (mon_reg & ~0x40000) );

		udelay(100);
	}
}

static int FBDEV_O18_ReadProcFunc( UINT32 procId, char* buffer )
{
    int ret;

    /* TODO: add your proc_write implementation */
    switch(procId)
    {
        case PROC_ID_O18_OSD_SR:
        {
            int len = 0;
            len += sprintf( buffer + len, "[usage] echo on_off_val > /proc/lg/fbdev/chip/osd_sr\n");
            ret = len;
        }
        break;

		case PROC_ID_O18_OSD_SR_GAIN:
        {
			UINT32 gain;
			int len = 0;

			 FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

			 OSD_SHP_RdFL(shp_lti_ctrl_00);
			 OSD_SHP_Rd01(shp_lti_ctrl_00, reg_lti_2d_gain, gain);

			/* print user-requested gain value & real HW value which normalized to 8bit */
			len += sprintf( buffer + len, " 0x%02x 0x%02x\n", hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain, gain);
			ret = len;
 		}
		break;

		default:
		{
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

static int FBDEV_O18_WriteProcFunc( UINT32 procId, char* command )
{
    switch( procId )
    {
        case PROC_ID_O18_OSD_SR:
        {
            int onoff;

            sscanf( command, " %d", &onoff );

			FBDEV_O18_CMN_SRCtrl((onoff==1)? TRUE:FALSE);
        }
        break;

        case PROC_ID_O18_OSD_SR_GAIN:
        {
            UINT32 gain;
            FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

            sscanf( command, " 0x%x", &gain);

            /* if gain is not valid 8bit value, DO NOT change HW gain configuration */
            if (gain & 0xffffff00 ) break;

            hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain = gain;

			OSD_SHP_RdFL(shp_lti_ctrl_00);
			OSD_SHP_Wr01(shp_lti_ctrl_00, reg_lti_2d_gain, gain);
			OSD_SHP_WrFL(shp_lti_ctrl_00);
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

void	FBDEV_O18_CreateProc ( struct proc_dir_entry* parent_proc )
{
    OS_PROC_CreateEntry("chip", parent_proc, (OS_PROC_DESC_TABLE_T*)g_fbdev_o18_device_proc_table,
									FBDEV_O18_ReadProcFunc,
                                    FBDEV_O18_WriteProcFunc);
}

