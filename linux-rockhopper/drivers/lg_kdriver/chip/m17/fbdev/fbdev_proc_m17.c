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
#include "fbdev_hw_m17.h"
#include "osd_reg_m17.h"
#include "osd_shp_reg_m17.h"
#include "osd_afbc_reg_m17.h"
#include "top_ctrl_osd_reg_m17.h"

#include "proc_util.h"
#include <linux/seq_file.h>

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
	PROC_ID_M17_OSD_SR 	= 0,
	PROC_ID_M17_OSD_SR_GAIN,
	PROC_ID_M17_DIAG_HW,
	PROC_ID_M17_MAX
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static  void	FBDEV_M17_PROC_DiagHW(struct seq_file* m);

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
OS_PROC_SEQRD_DEFINE(fbdev_m17_hw_diag_proc_fops, FBDEV_M17_PROC_DiagHW)

const static OS_PROC_DESC_TABLE_T g_fbdev_m17_device_proc_table[] =
{
    { "osd_sr",		PROC_ID_M17_OSD_SR,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "osd_sr_gain",PROC_ID_M17_OSD_SR_GAIN,OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "diag", 		PROC_ID_M17_DIAG_HW,	OS_PROC_FLAG_SEQRD, (void*)&fbdev_m17_hw_diag_proc_fops },
    {  NULL,		PROC_ID_M17_MAX     	,0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static  void	FBDEV_M17_PROC_DiagHW(struct seq_file* m)
{
	FBDEV_M17_CMN_DiagHW(m);
}

static int FBDEV_M17_ReadProcFunc( UINT32 procId, char* buffer )
{
    int ret;

    /* TODO: add your proc_write implementation */
    switch(procId)
    {
        case PROC_ID_M17_OSD_SR:
        {
            int len = 0;
            len += sprintf( buffer + len, "[usage] echo on_off_val > /proc/lg/fbdev/chip/osd_sr\n");
            ret = len;
        }
        break;

		case PROC_ID_M17_OSD_SR_GAIN:
		{
			UINT32 gain;
            int len = 0;

			FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

			OSD_SHP_RdFL(shp_dj_ctrl_04);
			OSD_SHP_Rd01(shp_dj_ctrl_04, reg_dj_ti_gain, gain);

			/* convert 5 bit to 8 bit (0~31) -> (0~255) */
			gain <<= 3;

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

static int FBDEV_M17_WriteProcFunc( UINT32 procId, char* command )
{
    switch( procId )
    {
        case PROC_ID_M17_OSD_SR:
        {
            int onoff;
			FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

            sscanf( command, " %d", &onoff );

			if(onoff<0)
			{
				hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].auto_mode = TRUE;
			}
			else
			{
				hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].auto_mode = FALSE;
				FBDEV_M17_CMN_SRCtrl((onoff==1)? TRUE:FALSE);
			}
        }
        break;

		case PROC_ID_M17_OSD_SR_GAIN:
		{
			UINT32 gain;
			FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

            sscanf( command, " 0x%x", &gain);

			/* if gain is not valid 8bit value, DO NOT change HW gain configuration */
			if (gain & 0xffffff00 ) break;

			hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain = gain;

			/* convert 8 bit to 5 bit (0~255) -> (0~31) */
			gain >>= 3;

			OSD_SHP_RdFL(shp_dj_ctrl_04);
			OSD_SHP_Wr01(shp_dj_ctrl_04, reg_dj_ti_gain, gain);
			OSD_SHP_WrFL(shp_dj_ctrl_04);
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

void	FBDEV_M17_CreateProc ( struct proc_dir_entry* parent_proc )
{
    OS_PROC_CreateEntry("chip", parent_proc, (OS_PROC_DESC_TABLE_T*)g_fbdev_m17_device_proc_table,
									FBDEV_M17_ReadProcFunc,
                                    FBDEV_M17_WriteProcFunc);
}

