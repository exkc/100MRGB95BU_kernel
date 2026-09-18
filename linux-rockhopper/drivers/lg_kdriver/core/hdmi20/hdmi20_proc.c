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
 *  Linux proc interface for hdmi20 device.
 *	hdmi20 device will teach you how to make device driver with new platform.
 *
 *  author		won.hur (won.hur@lge.com)
 *  version		1.0
 *  date		2014.04.28
 *  note		Additional information.
 *
 *  @addtogroup lg115x_hdmi20
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
#include <linux/fs.h>

#include <asm/uaccess.h>
#include <linux/string.h>

#include "hdmi20_drv.h"
#include "hdmi20_cfg.h"
#include "hdmi20_module.h"

#include "proc_util.h"
#include "debug_util.h"

#include "hdmi21_engine/hdmi21_hal_driver.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI20_SNPRINTF_SIZE	64

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_VERSION,
	PROC_ID_COMMAND,
	PROC_ID_LINE_DBG,
	PROC_ID_LINE_AUD_DBG,
	PROC_ID_LOGLEVEL,
	PROC_ID_ALEDAPB,
	PROC_ID_CORRECT_EDID,
	PROC_ID_MAX,
};

enum
{
	PROC_ID_ESM_VERSION = 0,
	PROC_ID_ESM_LOG,
	PROC_ID_ESM_MAX,
};

enum
{
	PROC_ID_PORT_STATUS,
	PROC_ID_PORT_EDID,
	PROC_ID_PORT_DATAPKT,
	PROC_ID_PORT_DATAEMPKT,
	PROC_ID_PORT_HDCPSTATUS,
	PROC_ID_PORT_ISR,
	PROC_ID_PORT_PHYREG28,
	PROC_ID_PORT_PHYREG38,
	PROC_ID_PORT_PHYREG48,
	PROC_ID_PORT_LINK,
	PROC_ID_PORT_TOP, 	
	PROC_ID_PORT_ALED,
	PROC_ID_PORT_PHYDEFAULT,
	PROC_ID_PORT_EYE,
	PROC_ID_PORT_EDID_FILE_RW,
	PROC_ID_PORT_CAL_OS,
	PROC_ID_PORT_DDCMON,
	PROC_ID_PORT_MAX,
};

enum
{
	PROC_ID_DEVCON_VIDEO_STATUS,
	PROC_ID_DEVCON_AUDIO_STATUS,
	PROC_ID_DEVCON_PHY_STATUS,
	PROC_ID_DEVCON_LINK_STATUS,
	PROC_ID_DEVCON_EARC_STATUS,
	PROC_ID_DEVCON_TABLE_STATUS,
	PROC_ID_DEVCON_READ_TABLE_STATUS,
	PROC_ID_DEVCON_WRITE_TABLE_STATUS,
	PROC_ID_DEVCON_TYPE_MAX,
};

enum
{
	PROC_ID_LGTV_PORT0_STATUS,
	PROC_ID_LGTV_PORT1_STATUS,
	PROC_ID_LGTV_PORT2_STATUS,
	PROC_ID_LGTV_PORT3_STATUS,
	PROC_ID_LGTV_PORT4_STATUS,
	PROC_ID_LGTV_PORT0_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int LOGM_ObjMaskSet(SINT32 fd, UINT32 mask);
extern int LOGM_ObjMaskGet(SINT32 fd, UINT32 *mask);

extern int		g_hdmi20_debug_fd;
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
void	HDMI20_PROC_Init (void);
void	HDMI20_PROC_Cleanup (void);


/*----------------------------------------------------------------------------------------
	Static Variables
	----------------------------------------------------------------------------------------*/


static OS_PROC_DESC_TABLE_T	_g_hdmi20_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR,			OS_PROC_FLAG_READ },
	{ "version", 	PROC_ID_VERSION,		OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND, 		OS_PROC_FLAG_WRITE },
	{ "line",		PROC_ID_LINE_DBG, 		OS_PROC_FLAG_WRITE },
	{ "line_aud",	PROC_ID_LINE_AUD_DBG, 	OS_PROC_FLAG_WRITE },
	{ "loglevel",	PROC_ID_LOGLEVEL,	 	OS_PROC_FLAG_WRITE },
	{ "correct_edid",PROC_ID_CORRECT_EDID,	OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX, 		0 }
};


static void _HDMI20_PORT0_ReadLGTVStatus(struct seq_file *m);
static void _HDMI20_PORT1_ReadLGTVStatus(struct seq_file *m);
static void _HDMI20_PORT2_ReadLGTVStatus(struct seq_file *m);
static void _HDMI20_PORT3_ReadLGTVStatus(struct seq_file *m);
static void _HDMI20_PORT4_ReadLGTVStatus(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _HDMI20_ESM_GetVersion(struct seq_file *m);
static void _HDMI20_ESM_GetLog(struct seq_file *m);

static ssize_t _HDMI20_ESM_SetVersion(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_ESM_SetLog(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _HDMI20_PORT0_ReadEye(struct seq_file *m);
static void _HDMI20_PORT1_ReadEye(struct seq_file *m);
static void _HDMI20_PORT2_ReadEye(struct seq_file *m);
static void _HDMI20_PORT3_ReadEye(struct seq_file *m);
static void _HDMI20_PORT4_ReadEye(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadPhy48(struct seq_file *m);
static void _HDMI20_PORT1_ReadPhy48(struct seq_file *m);
static void _HDMI20_PORT2_ReadPhy48(struct seq_file *m);
static void _HDMI20_PORT3_ReadPhy48(struct seq_file *m);
static void _HDMI20_PORT4_ReadPhy48(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadPhy38(struct seq_file *m);
static void _HDMI20_PORT1_ReadPhy38(struct seq_file *m);
static void _HDMI20_PORT2_ReadPhy38(struct seq_file *m);
static void _HDMI20_PORT3_ReadPhy38(struct seq_file *m);
static void _HDMI20_PORT4_ReadPhy38(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadPhy28(struct seq_file *m);
static void _HDMI20_PORT1_ReadPhy28(struct seq_file *m);
static void _HDMI20_PORT2_ReadPhy28(struct seq_file *m);
static void _HDMI20_PORT3_ReadPhy28(struct seq_file *m);
static void _HDMI20_PORT4_ReadPhy28(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadLinkAPB(struct seq_file *m);
static void _HDMI20_PORT1_ReadLinkAPB(struct seq_file *m);
static void _HDMI20_PORT2_ReadLinkAPB(struct seq_file *m);
static void _HDMI20_PORT3_ReadLinkAPB(struct seq_file *m);
static void _HDMI20_PORT4_ReadLinkAPB(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadTopAPB(struct seq_file *m);
static void _HDMI20_PORT1_ReadTopAPB(struct seq_file *m);
static void _HDMI20_PORT2_ReadTopAPB(struct seq_file *m);
static void _HDMI20_PORT3_ReadTopAPB(struct seq_file *m);
static void _HDMI20_PORT4_ReadTopAPB(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadAledAPB(struct seq_file *m);
static void _HDMI20_PORT1_ReadAledAPB(struct seq_file *m);
static void _HDMI20_PORT2_ReadAledAPB(struct seq_file *m);
static void _HDMI20_PORT3_ReadAledAPB(struct seq_file *m);
static void _HDMI20_PORT4_ReadAledAPB(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadPhyDefault(struct seq_file *m);
static void _HDMI20_PORT1_ReadPhyDefault(struct seq_file *m);
static void _HDMI20_PORT2_ReadPhyDefault(struct seq_file *m);
static void _HDMI20_PORT3_ReadPhyDefault(struct seq_file *m);
static void _HDMI20_PORT4_ReadPhyDefault(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadDataIsr(struct seq_file *m);
static void _HDMI20_PORT1_ReadDataIsr(struct seq_file *m);
static void _HDMI20_PORT2_ReadDataIsr(struct seq_file *m);
static void _HDMI20_PORT3_ReadDataIsr(struct seq_file *m);
static void _HDMI20_PORT4_ReadDataIsr(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadHdcpStatus(struct seq_file *m);
static void _HDMI20_PORT1_ReadHdcpStatus(struct seq_file *m);
static void _HDMI20_PORT2_ReadHdcpStatus(struct seq_file *m);
static void _HDMI20_PORT3_ReadHdcpStatus(struct seq_file *m);
static void _HDMI20_PORT4_ReadHdcpStatus(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadDataEmPkt(struct seq_file *m);
static void _HDMI20_PORT1_ReadDataEmPkt(struct seq_file *m);
static void _HDMI20_PORT2_ReadDataEmPkt(struct seq_file *m);
static void _HDMI20_PORT3_ReadDataEmPkt(struct seq_file *m);
static void _HDMI20_PORT4_ReadDataEmPkt(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadDataPkt(struct seq_file *m);
static void _HDMI20_PORT1_ReadDataPkt(struct seq_file *m);
static void _HDMI20_PORT2_ReadDataPkt(struct seq_file *m);
static void _HDMI20_PORT3_ReadDataPkt(struct seq_file *m);
static void _HDMI20_PORT4_ReadDataPkt(struct seq_file *m);
static ssize_t _HDMI20_PORT0_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_PrintStatus(struct seq_file *m);
static void _HDMI20_PORT1_PrintStatus(struct seq_file *m);
static void _HDMI20_PORT2_PrintStatus(struct seq_file *m);
static void _HDMI20_PORT3_PrintStatus(struct seq_file *m);
static void _HDMI20_PORT4_PrintStatus(struct seq_file *m);
static ssize_t _HDMI20_PORT0_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static void _HDMI20_PORT0_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT1_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT2_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT3_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT4_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT0_FILE_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT1_FILE_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT2_FILE_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT3_FILE_ReadEDID(struct seq_file *m);
static void _HDMI20_PORT4_FILE_ReadEDID(struct seq_file *m);

static ssize_t _HDMI20_PORT0_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);

static ssize_t _HDMI20_PORT0_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _HDMI20_PORT0_ReadCalOS(struct seq_file *m);
static void _HDMI20_PORT1_ReadCalOS(struct seq_file *m);
static void _HDMI20_PORT2_ReadCalOS(struct seq_file *m);
static void _HDMI20_PORT3_ReadCalOS(struct seq_file *m);
static void _HDMI20_PORT4_ReadCalOS(struct seq_file *m);

static ssize_t _HDMI20_PORT0_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _HDMI20_PORT0_ReadDdcMon(struct seq_file *m);
static void _HDMI20_PORT1_ReadDdcMon(struct seq_file *m);
static void _HDMI20_PORT2_ReadDdcMon(struct seq_file *m);
static void _HDMI20_PORT3_ReadDdcMon(struct seq_file *m);
static void _HDMI20_PORT4_ReadDdcMon(struct seq_file *m);

static ssize_t _HDMI20_PORT0_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT1_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT2_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT3_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_PORT4_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _HDMI20_DEVCON_Video_PrintStatus(struct seq_file *m);
static void _HDMI20_DEVCON_Audio_PrintStatus(struct seq_file *m);
static void _HDMI20_DEVCON_Phy_PrintStatus(struct seq_file *m);
static void _HDMI20_DEVCON_Link_PrintStatus(struct seq_file *m);
static void _HDMI20_DEVCON_Earc_PrintStatus(struct seq_file *m);
static void _HDMI20_DEVCON_Table_PrintStatus(struct seq_file *m);
static ssize_t _HDMI20_DEVCON_Video_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_Audio_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_Phy_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_Link_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_Earc_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_Table_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_ReadTable_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);
static ssize_t _HDMI20_DEVCON_WriteTable_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off);


OS_PROC_SEQRW_DEFINE_EX(lgtv_hdmi20_port0_status_proc_fops, _HDMI20_PORT0_ReadLGTVStatus, _HDMI20_PORT0_WriteLGTVStatus) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(lgtv_hdmi20_port1_status_proc_fops, _HDMI20_PORT1_ReadLGTVStatus, _HDMI20_PORT1_WriteLGTVStatus) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(lgtv_hdmi20_port2_status_proc_fops, _HDMI20_PORT2_ReadLGTVStatus, _HDMI20_PORT2_WriteLGTVStatus) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(lgtv_hdmi20_port3_status_proc_fops, _HDMI20_PORT3_ReadLGTVStatus, _HDMI20_PORT3_WriteLGTVStatus) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(lgtv_hdmi20_port4_status_proc_fops, _HDMI20_PORT4_ReadLGTVStatus, _HDMI20_PORT4_WriteLGTVStatus) /* port #4 */



OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_esm_version_proc_fops, _HDMI20_ESM_GetVersion, _HDMI20_ESM_SetVersion) 
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_esm_log_proc_fops, 	 _HDMI20_ESM_GetLog, _HDMI20_ESM_SetLog)


OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_eye_fops, _HDMI20_PORT0_ReadEye, _HDMI20_PORT0_WriteEye) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_eye_fops, _HDMI20_PORT1_ReadEye, _HDMI20_PORT1_WriteEye) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_eye_fops, _HDMI20_PORT2_ReadEye, _HDMI20_PORT2_WriteEye) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_eye_fops, _HDMI20_PORT3_ReadEye, _HDMI20_PORT3_WriteEye) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_eye_fops, _HDMI20_PORT4_ReadEye, _HDMI20_PORT4_WriteEye) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_phydefault_fops, _HDMI20_PORT0_ReadPhyDefault, _HDMI20_PORT0_WritePhyDefault) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_phydefault_fops, _HDMI20_PORT1_ReadPhyDefault, _HDMI20_PORT1_WritePhyDefault) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_phydefault_fops, _HDMI20_PORT2_ReadPhyDefault, _HDMI20_PORT2_WritePhyDefault) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_phydefault_fops, _HDMI20_PORT3_ReadPhyDefault, _HDMI20_PORT3_WritePhyDefault) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_phydefault_fops, _HDMI20_PORT4_ReadPhyDefault, _HDMI20_PORT4_WritePhyDefault) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_aledapb_fops, _HDMI20_PORT0_ReadAledAPB, _HDMI20_PORT0_WriteAledAPB) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_aledapb_fops, _HDMI20_PORT1_ReadAledAPB, _HDMI20_PORT1_WriteAledAPB) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_aledapb_fops, _HDMI20_PORT2_ReadAledAPB, _HDMI20_PORT2_WriteAledAPB) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_aledapb_fops, _HDMI20_PORT3_ReadAledAPB, _HDMI20_PORT3_WriteAledAPB) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_aledapb_fops, _HDMI20_PORT4_ReadAledAPB, _HDMI20_PORT4_WriteAledAPB) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_topapb_fops, _HDMI20_PORT0_ReadTopAPB, _HDMI20_PORT0_WriteTopAPB) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_topapb_fops, _HDMI20_PORT1_ReadTopAPB, _HDMI20_PORT1_WriteTopAPB) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_topapb_fops, _HDMI20_PORT2_ReadTopAPB, _HDMI20_PORT2_WriteTopAPB) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_topapb_fops, _HDMI20_PORT3_ReadTopAPB, _HDMI20_PORT3_WriteTopAPB) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_topapb_fops, _HDMI20_PORT4_ReadTopAPB, _HDMI20_PORT4_WriteTopAPB) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_linkapb_fops, _HDMI20_PORT0_ReadLinkAPB, _HDMI20_PORT0_WriteLinkAPB) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_linkapb_fops, _HDMI20_PORT1_ReadLinkAPB, _HDMI20_PORT1_WriteLinkAPB) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_linkapb_fops, _HDMI20_PORT2_ReadLinkAPB, _HDMI20_PORT2_WriteLinkAPB) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_linkapb_fops, _HDMI20_PORT3_ReadLinkAPB, _HDMI20_PORT3_WriteLinkAPB) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_linkapb_fops, _HDMI20_PORT4_ReadLinkAPB, _HDMI20_PORT4_WriteLinkAPB) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_phy_reg48_fops, _HDMI20_PORT0_ReadPhy48, _HDMI20_PORT0_WritePhy48) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_phy_reg48_fops, _HDMI20_PORT1_ReadPhy48, _HDMI20_PORT1_WritePhy48) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_phy_reg48_fops, _HDMI20_PORT2_ReadPhy48, _HDMI20_PORT2_WritePhy48) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_phy_reg48_fops, _HDMI20_PORT3_ReadPhy48, _HDMI20_PORT3_WritePhy48) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_phy_reg48_fops, _HDMI20_PORT4_ReadPhy48, _HDMI20_PORT4_WritePhy48) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_phy_reg38_fops, _HDMI20_PORT0_ReadPhy38, _HDMI20_PORT0_WritePhy38) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_phy_reg38_fops, _HDMI20_PORT1_ReadPhy38, _HDMI20_PORT1_WritePhy38) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_phy_reg38_fops, _HDMI20_PORT2_ReadPhy38, _HDMI20_PORT2_WritePhy38) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_phy_reg38_fops, _HDMI20_PORT3_ReadPhy38, _HDMI20_PORT3_WritePhy38) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_phy_reg38_fops, _HDMI20_PORT4_ReadPhy38, _HDMI20_PORT4_WritePhy38) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_phy_reg28_fops, _HDMI20_PORT0_ReadPhy28, _HDMI20_PORT0_WritePhy28) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_phy_reg28_fops, _HDMI20_PORT1_ReadPhy28, _HDMI20_PORT1_WritePhy28) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_phy_reg28_fops, _HDMI20_PORT2_ReadPhy28, _HDMI20_PORT2_WritePhy28) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_phy_reg28_fops, _HDMI20_PORT3_ReadPhy28, _HDMI20_PORT3_WritePhy28) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_phy_reg28_fops, _HDMI20_PORT4_ReadPhy28, _HDMI20_PORT4_WritePhy28) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_isr_proc_fops, _HDMI20_PORT0_ReadDataIsr, _HDMI20_PORT0_WriteDataIsr) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_isr_proc_fops, _HDMI20_PORT1_ReadDataIsr, _HDMI20_PORT1_WriteDataIsr) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_isr_proc_fops, _HDMI20_PORT2_ReadDataIsr, _HDMI20_PORT2_WriteDataIsr) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_isr_proc_fops, _HDMI20_PORT3_ReadDataIsr, _HDMI20_PORT3_WriteDataIsr) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_isr_proc_fops, _HDMI20_PORT4_ReadDataIsr, _HDMI20_PORT4_WriteDataIsr) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_hdcpstatus_proc_fops, _HDMI20_PORT0_ReadHdcpStatus, _HDMI20_PORT0_WriteHdcpStatus) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_hdcpstatus_proc_fops, _HDMI20_PORT1_ReadHdcpStatus, _HDMI20_PORT1_WriteHdcpStatus) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_hdcpstatus_proc_fops, _HDMI20_PORT2_ReadHdcpStatus, _HDMI20_PORT2_WriteHdcpStatus) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_hdcpstatus_proc_fops, _HDMI20_PORT3_ReadHdcpStatus, _HDMI20_PORT3_WriteHdcpStatus) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_hdcpstatus_proc_fops, _HDMI20_PORT4_ReadHdcpStatus, _HDMI20_PORT4_WriteHdcpStatus) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_empkt_proc_fops, _HDMI20_PORT0_ReadDataEmPkt, _HDMI20_PORT0_WriteDataEmPkt) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_empkt_proc_fops, _HDMI20_PORT1_ReadDataEmPkt, _HDMI20_PORT1_WriteDataEmPkt) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_empkt_proc_fops, _HDMI20_PORT2_ReadDataEmPkt, _HDMI20_PORT2_WriteDataEmPkt) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_empkt_proc_fops, _HDMI20_PORT3_ReadDataEmPkt, _HDMI20_PORT3_WriteDataEmPkt) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_empkt_proc_fops, _HDMI20_PORT4_ReadDataEmPkt, _HDMI20_PORT4_WriteDataEmPkt) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_pkt_proc_fops, _HDMI20_PORT0_ReadDataPkt, _HDMI20_PORT0_WriteDataPkt) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_pkt_proc_fops, _HDMI20_PORT1_ReadDataPkt, _HDMI20_PORT1_WriteDataPkt) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_pkt_proc_fops, _HDMI20_PORT2_ReadDataPkt, _HDMI20_PORT2_WriteDataPkt) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_pkt_proc_fops, _HDMI20_PORT3_ReadDataPkt, _HDMI20_PORT3_WriteDataPkt) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_pkt_proc_fops, _HDMI20_PORT4_ReadDataPkt, _HDMI20_PORT4_WriteDataPkt) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_status_proc_fops, _HDMI20_PORT0_PrintStatus, _HDMI20_PORT0_Cmd) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_status_proc_fops, _HDMI20_PORT1_PrintStatus, _HDMI20_PORT1_Cmd) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_status_proc_fops, _HDMI20_PORT2_PrintStatus, _HDMI20_PORT2_Cmd) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_status_proc_fops, _HDMI20_PORT3_PrintStatus, _HDMI20_PORT3_Cmd) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_status_proc_fops, _HDMI20_PORT4_PrintStatus, _HDMI20_PORT4_Cmd) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_edid_proc_fops, _HDMI20_PORT0_ReadEDID, _HDMI20_PORT0_WriteEDID) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_edid_proc_fops, _HDMI20_PORT1_ReadEDID, _HDMI20_PORT1_WriteEDID) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_edid_proc_fops, _HDMI20_PORT2_ReadEDID, _HDMI20_PORT2_WriteEDID) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_edid_proc_fops, _HDMI20_PORT3_ReadEDID, _HDMI20_PORT3_WriteEDID) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_edid_proc_fops, _HDMI20_PORT4_ReadEDID, _HDMI20_PORT4_WriteEDID) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_edid_file_rw_proc_fops, _HDMI20_PORT0_FILE_ReadEDID, _HDMI20_PORT0_FILE_WriteEDID) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_edid_file_rw_proc_fops, _HDMI20_PORT1_FILE_ReadEDID, _HDMI20_PORT1_FILE_WriteEDID) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_edid_file_rw_proc_fops, _HDMI20_PORT2_FILE_ReadEDID, _HDMI20_PORT2_FILE_WriteEDID) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_edid_file_rw_proc_fops, _HDMI20_PORT3_FILE_ReadEDID, _HDMI20_PORT3_FILE_WriteEDID) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_edid_file_rw_proc_fops, _HDMI20_PORT4_FILE_ReadEDID, _HDMI20_PORT4_FILE_WriteEDID) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_cal_os_fops, _HDMI20_PORT0_ReadCalOS, _HDMI20_PORT0_WriteCalOS) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_cal_os_fops, _HDMI20_PORT1_ReadCalOS, _HDMI20_PORT1_WriteCalOS) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_cal_os_fops, _HDMI20_PORT2_ReadCalOS, _HDMI20_PORT2_WriteCalOS) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_cal_os_fops, _HDMI20_PORT3_ReadCalOS, _HDMI20_PORT3_WriteCalOS) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_cal_os_fops, _HDMI20_PORT4_ReadCalOS, _HDMI20_PORT4_WriteCalOS) /* port #4 */

OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port0_ddcmon_fops, _HDMI20_PORT0_ReadDdcMon, _HDMI20_PORT0_WriteDdcMon) /* port #0 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port1_ddcmon_fops, _HDMI20_PORT1_ReadDdcMon, _HDMI20_PORT1_WriteDdcMon) /* port #1 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port2_ddcmon_fops, _HDMI20_PORT2_ReadDdcMon, _HDMI20_PORT2_WriteDdcMon) /* port #2 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port3_ddcmon_fops, _HDMI20_PORT3_ReadDdcMon, _HDMI20_PORT3_WriteDdcMon) /* port #3 */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_port4_ddcmon_fops, _HDMI20_PORT4_ReadDdcMon, _HDMI20_PORT4_WriteDdcMon) /* port #4 */



OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_video_status_proc_fops, _HDMI20_DEVCON_Video_PrintStatus, _HDMI20_DEVCON_Video_Cmd)	/* DevCon : Video */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_audio_status_proc_fops, _HDMI20_DEVCON_Audio_PrintStatus, _HDMI20_DEVCON_Audio_Cmd)	/* DevCon : Audio */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_phy_status_proc_fops, 	 _HDMI20_DEVCON_Phy_PrintStatus, _HDMI20_DEVCON_Phy_Cmd) 	/* DevCon : Phy */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_link_status_proc_fops,  _HDMI20_DEVCON_Link_PrintStatus, _HDMI20_DEVCON_Link_Cmd)	/* DevCon : Link */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_earc_status_proc_fops,  _HDMI20_DEVCON_Earc_PrintStatus, _HDMI20_DEVCON_Earc_Cmd)	/* DevCon : Earc */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_table_status_proc_fops, _HDMI20_DEVCON_Table_PrintStatus, _HDMI20_DEVCON_Table_Cmd)	/*DevCon : Table */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_read_table_status_proc_fops, _HDMI20_DEVCON_Table_PrintStatus,  _HDMI20_DEVCON_ReadTable_Cmd)	/*DevCon : Table */
OS_PROC_SEQRW_DEFINE_EX(_g_hdmi20_devcon_write_table_status_proc_fops, _HDMI20_DEVCON_Table_PrintStatus, _HDMI20_DEVCON_WriteTable_Cmd)	/*DevCon : Table */

static const OS_PROC_DESC_TABLE_T lgtv_hdmi20_port_proc_table[] = {
	{ "hdmi.p0", 	PROC_ID_LGTV_PORT0_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&lgtv_hdmi20_port0_status_proc_fops },
	{ "hdmi.p1", 	PROC_ID_LGTV_PORT1_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&lgtv_hdmi20_port1_status_proc_fops },
	{ "hdmi.p2", 	PROC_ID_LGTV_PORT2_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&lgtv_hdmi20_port2_status_proc_fops },
	{ "hdmi.p3", 	PROC_ID_LGTV_PORT3_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&lgtv_hdmi20_port3_status_proc_fops },
	{ "hdmi.p4", 	PROC_ID_LGTV_PORT4_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&lgtv_hdmi20_port4_status_proc_fops },
	{ NULL,			PROC_ID_PORT_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_hdmi20_esm_proc_table[] = {
    { "version", 	PROC_ID_ESM_VERSION,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_esm_version_proc_fops },
	{ "log", 		PROC_ID_ESM_LOG,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_esm_log_proc_fops},
	{ NULL,			PROC_ID_ESM_MAX, 0 } };


static const OS_PROC_DESC_TABLE_T _g_hdmi20_port0_proc_table[] = {
    { "status", 	PROC_ID_PORT_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_status_proc_fops },
	{ "edid", 		PROC_ID_PORT_EDID,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_edid_proc_fops},
	{ "pkt", 		PROC_ID_PORT_DATAPKT,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_pkt_proc_fops},
	{ "empkt", 		PROC_ID_PORT_DATAEMPKT,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_empkt_proc_fops},
	{ "hdcp",		PROC_ID_PORT_HDCPSTATUS,OS_PROC_FLAG_SEQRW,	(void*)&_g_hdmi20_port0_hdcpstatus_proc_fops},
	{ "isr", 		PROC_ID_PORT_ISR,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_isr_proc_fops},
	{ "phy0x28",	PROC_ID_PORT_PHYREG28,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_phy_reg28_fops},
	{ "phy0x38",	PROC_ID_PORT_PHYREG38,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_phy_reg38_fops},
	{ "phy0x48",	PROC_ID_PORT_PHYREG48,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_phy_reg48_fops},
	{ "link",		PROC_ID_PORT_LINK,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_linkapb_fops},
	{ "top",		PROC_ID_PORT_TOP,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_topapb_fops},
	{ "aled",		PROC_ID_PORT_ALED,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_aledapb_fops},
	{ "phydefault",	PROC_ID_PORT_PHYDEFAULT, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_phydefault_fops},
	{ "eye",		PROC_ID_PORT_EYE, 		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_eye_fops},
	{ "edid_file_rw",PROC_ID_PORT_EDID_FILE_RW, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_edid_file_rw_proc_fops},
	{ "offset",      PROC_ID_PORT_CAL_OS, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_cal_os_fops},
	{ "ddcmon",		PROC_ID_PORT_DDCMON, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port0_ddcmon_fops},
	{ NULL,			PROC_ID_PORT_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_hdmi20_port1_proc_table[] = {
    { "status", 	PROC_ID_PORT_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_status_proc_fops },
	{ "edid", 		PROC_ID_PORT_EDID,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_edid_proc_fops},
	{ "pkt", 		PROC_ID_PORT_DATAPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_pkt_proc_fops},
	{ "empkt", 		PROC_ID_PORT_DATAEMPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_empkt_proc_fops},
	{ "hdcp",		PROC_ID_PORT_HDCPSTATUS, 	OS_PROC_FLAG_SEQRW,	(void*)&_g_hdmi20_port1_hdcpstatus_proc_fops},
	{ "isr", 		PROC_ID_PORT_ISR,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_isr_proc_fops},
	{ "phy0x28",	PROC_ID_PORT_PHYREG28,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_phy_reg28_fops},
	{ "phy0x38",	PROC_ID_PORT_PHYREG38,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_phy_reg38_fops},
	{ "phy0x48",	PROC_ID_PORT_PHYREG48,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_phy_reg48_fops},
	{ "link",		PROC_ID_PORT_LINK,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_linkapb_fops},
	{ "top",		PROC_ID_PORT_TOP,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_topapb_fops},
	{ "aled",		PROC_ID_PORT_ALED,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_aledapb_fops},
	{ "phydefault",	PROC_ID_PORT_PHYDEFAULT, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_phydefault_fops},
	{ "eye",		PROC_ID_PORT_EYE, 		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_eye_fops},
	{ "edid_file_rw",PROC_ID_PORT_EDID_FILE_RW, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_edid_file_rw_proc_fops},
	{ "offset",      PROC_ID_PORT_CAL_OS, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_cal_os_fops},
	{ "ddcmon",		PROC_ID_PORT_DDCMON, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port1_ddcmon_fops},
	{ NULL,			PROC_ID_PORT_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_hdmi20_port2_proc_table[] = {
    { "status", 	PROC_ID_PORT_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_status_proc_fops },
	{ "edid", 		PROC_ID_PORT_EDID,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_edid_proc_fops},
	{ "pkt", 		PROC_ID_PORT_DATAPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_pkt_proc_fops},
	{ "empkt", 		PROC_ID_PORT_DATAEMPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_empkt_proc_fops},
	{ "hdcp",		PROC_ID_PORT_HDCPSTATUS, 	OS_PROC_FLAG_SEQRW,	(void*)&_g_hdmi20_port2_hdcpstatus_proc_fops},
	{ "isr", 		PROC_ID_PORT_ISR,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_isr_proc_fops},
	{ "phy0x28",	PROC_ID_PORT_PHYREG28,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_phy_reg28_fops},
	{ "phy0x38",	PROC_ID_PORT_PHYREG38,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_phy_reg38_fops},
	{ "phy0x48",	PROC_ID_PORT_PHYREG48,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_phy_reg48_fops},
	{ "link",		PROC_ID_PORT_LINK,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_linkapb_fops},
	{ "top",		PROC_ID_PORT_TOP,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_topapb_fops},
	{ "aled",		PROC_ID_PORT_ALED,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_aledapb_fops},
	{ "phydefault",	PROC_ID_PORT_PHYDEFAULT, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_phydefault_fops},
	{ "eye",		PROC_ID_PORT_EYE, 		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_eye_fops},
	{ "edid_file_rw",PROC_ID_PORT_EDID_FILE_RW, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_edid_file_rw_proc_fops},
	{ "offset",      PROC_ID_PORT_CAL_OS, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_cal_os_fops},
	{ "ddcmon",		PROC_ID_PORT_DDCMON, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port2_ddcmon_fops},
	{ NULL,			PROC_ID_PORT_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_hdmi20_port3_proc_table[] = {
    { "status", 	PROC_ID_PORT_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_status_proc_fops },
	{ "edid", 		PROC_ID_PORT_EDID,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_edid_proc_fops},
	{ "pkt", 		PROC_ID_PORT_DATAPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_pkt_proc_fops},
	{ "empkt", 		PROC_ID_PORT_DATAEMPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_empkt_proc_fops},
	{ "hdcp",		PROC_ID_PORT_HDCPSTATUS, 	OS_PROC_FLAG_SEQRW,	(void*)&_g_hdmi20_port3_hdcpstatus_proc_fops},
	{ "isr", 		PROC_ID_PORT_ISR,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_isr_proc_fops},
	{ "phy0x28",	PROC_ID_PORT_PHYREG28,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_phy_reg28_fops},
	{ "phy0x38",	PROC_ID_PORT_PHYREG38,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_phy_reg38_fops},
	{ "phy0x48",	PROC_ID_PORT_PHYREG48,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_phy_reg48_fops},
	{ "link",		PROC_ID_PORT_LINK,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_linkapb_fops},
	{ "top",		PROC_ID_PORT_TOP,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_topapb_fops},
	{ "aled",		PROC_ID_PORT_ALED,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_aledapb_fops},
	{ "phydefault",	PROC_ID_PORT_PHYDEFAULT, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_phydefault_fops},
	{ "eye",		PROC_ID_PORT_EYE, 		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_eye_fops},
	{ "edid_file_rw",PROC_ID_PORT_EDID_FILE_RW, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_edid_file_rw_proc_fops},
	{ "ddcmon",		PROC_ID_PORT_DDCMON, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_ddcmon_fops},
	{ "offset",      PROC_ID_PORT_CAL_OS, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port3_cal_os_fops},
	{ NULL,			PROC_ID_PORT_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_hdmi20_port4_proc_table[] = {
    { "status", 	PROC_ID_PORT_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_status_proc_fops },
	{ "edid", 		PROC_ID_PORT_EDID,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_edid_proc_fops},
	{ "pkt", 		PROC_ID_PORT_DATAPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_pkt_proc_fops},
	{ "empkt", 		PROC_ID_PORT_DATAEMPKT,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_empkt_proc_fops},
	{ "hdcp",		PROC_ID_PORT_HDCPSTATUS, 	OS_PROC_FLAG_SEQRW,	(void*)&_g_hdmi20_port4_hdcpstatus_proc_fops},
	{ "isr", 		PROC_ID_PORT_ISR,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_isr_proc_fops},
	{ "phy0x28",	PROC_ID_PORT_PHYREG28,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_phy_reg28_fops},
	{ "phy0x38",	PROC_ID_PORT_PHYREG38,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_phy_reg38_fops},
	{ "phy0x48",	PROC_ID_PORT_PHYREG48,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_phy_reg48_fops},
	{ "link",		PROC_ID_PORT_LINK,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_linkapb_fops},
	{ "top",		PROC_ID_PORT_TOP,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_topapb_fops},
	{ "aled",		PROC_ID_PORT_ALED,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_aledapb_fops},
	{ "phydefault",	PROC_ID_PORT_PHYDEFAULT, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_phydefault_fops},
	{ "eye",		PROC_ID_PORT_EYE, 		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_eye_fops},
	{ "edid_file_rw",PROC_ID_PORT_EDID_FILE_RW, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_edid_file_rw_proc_fops},
	{ "offset",      PROC_ID_PORT_CAL_OS, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_cal_os_fops},
	{ "ddcmon",		PROC_ID_PORT_DDCMON, OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_port4_ddcmon_fops},
	{ NULL,			PROC_ID_PORT_MAX, 0 } };

static const OS_PROC_DESC_TABLE_T _g_hdmi20_devcon_proc_table[] = {
	{ "video", 	PROC_ID_DEVCON_VIDEO_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_video_status_proc_fops },
	{ "audio", 	PROC_ID_DEVCON_AUDIO_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_audio_status_proc_fops },
	{ "phy", 	PROC_ID_DEVCON_PHY_STATUS,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_phy_status_proc_fops },
	{ "link", 	PROC_ID_DEVCON_LINK_STATUS,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_link_status_proc_fops },
	{ "earc", 	PROC_ID_DEVCON_EARC_STATUS,		OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_earc_status_proc_fops },
	{ "table", 	PROC_ID_DEVCON_TABLE_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_table_status_proc_fops },
	{ "read_table", 	PROC_ID_DEVCON_READ_TABLE_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_read_table_status_proc_fops },
	{ "write_table", 	PROC_ID_DEVCON_WRITE_TABLE_STATUS,	OS_PROC_FLAG_SEQRW, (void*)&_g_hdmi20_devcon_write_table_status_proc_fops },
	{ NULL,		PROC_ID_DEVCON_TYPE_MAX, 0 } };

/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of hdmi20 device
 *
*/
static int	_HDMI20_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret = 0;
	UINT32	mask = 0;


	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer, HDMI20_SNPRINTF_SIZE,"%s\n", "won.hur (won.hur@lge.com)");
		}
		break;

		case PROC_ID_VERSION:
		{
			ret = snprintf(buffer, HDMI20_SNPRINTF_SIZE,"HDMI2.0 Driver Ver : 0x%x\n", HDMI20_Module_SwVersion());
		}
		break;
		case PROC_ID_LINE_DBG:
		{
			ret = snprintf(buffer, HDMI20_SNPRINTF_SIZE, "Line Debugger => [%d]\n", HDMI20_Module_Get_Line_Debugger());
		}
		break;
		case PROC_ID_LINE_AUD_DBG:
		{
			ret = snprintf(buffer, HDMI20_SNPRINTF_SIZE, "Line Audio Debugger => [%d]\n", HDMI20_Module_Get_Audio_Line_Debugger());
		}
		break;
		case PROC_ID_LOGLEVEL:
		{	
			LOGM_ObjMaskGet(g_hdmi20_debug_fd, &mask); 
			ret = snprintf(buffer, HDMI20_SNPRINTF_SIZE, "HDMI20 LOGM Mask(Default : 0xF, All but Audio : 0xDDF) => [0x%08x]\n",mask); 
		}
		break;
		default:
		{
			ret = snprintf( buffer, HDMI20_SNPRINTF_SIZE,"%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

/*
 * write_proc implementation of hdmi20 device
 *
*/
static int _HDMI20_WriteProcFunction( UINT32 procId, char* command )
{
	UINT32 mask = 0;
	int 	__args[HDMI20_SNPRINTF_SIZE]  = {0,};

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{

			if( sscanf(command, "%d %d 0x%x", &__args[0], &__args[1], &__args[2]) != 3) {
				if( sscanf(command, "%d %d %d", &__args[0], &__args[1], &__args[2]) != 3) {
					printk("Wrong usage. Usage => [2](port) [2](type) [0x1234 or 1234](value)\n");
					break;
				}
			}

			HDMI20_Module_Set_DBGTool(__args[1], __args[0], __args[2]);
		}
		break;
		case PROC_ID_LINE_DBG:
		{
			sscanf( command, "%d", __args); 	
			printk("Write Line Debugger Value to [%d]\n", __args[0]);
			HDMI20_Module_Set_Line_Debugger((UINT32)__args[0]);
		}
		break;
		case PROC_ID_LINE_AUD_DBG:
		{
			sscanf( command, "%d", __args); 	
			printk("Write Audio Line Debugger Value to [%d]\n", __args[0]);
			HDMI20_Module_Set_Audio_Line_Debugger((UINT32)__args[0]);
		}
		break;
		case PROC_ID_LOGLEVEL:
		{
			if(sscanf( command, "0x%x", __args) == 1) {

			mask = (UINT32)__args[0];

			LOGM_ObjMaskSet(g_hdmi20_debug_fd, mask);
			printk("HDMI20 Logm Mask Set to [0x%08x]\n", mask);
			}
			else{
				printk("Wrong Input format\n\t usage : echo '0x12345' > loglevel");
			}
		}
		break;
		case PROC_ID_ALEDAPB:
		{

		}
		break;
		case PROC_ID_CORRECT_EDID:
		{
			int port = 0;
			bool isChanged = false;
			int ret = RET_ERROR;
			if( strlen(command) != 2 )
			{
				printk("Invalid input data\n\t usage : echo [port-num] > correct_edid");
				break;
			} else {
				sscanf( command, "%d", &__args[0]);	
				port = __args[0];
				if( port < 0 || port > 4){
					printk("Wrong input port[%02d] \n", port);
					break;
				}
			}

			ret = HDMI20_Module_Set_Calculate_EDID_CheckSum(port, &isChanged);
			if( ret != RET_OK )
			{
				printk("Failed to update Port[%02d] edid check-sum!\n", port);
			} else {
				printk("Port[%02d] edid check-sum is updated! (changed:%s)\n", port, (isChanged)?"YES":"NO");
			}

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


static void _HDMI20_PORT0_ReadLGTVStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLGTVStatus(0, m);	
}

static void _HDMI20_PORT1_ReadLGTVStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLGTVStatus(1, m);	
}

static void _HDMI20_PORT2_ReadLGTVStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLGTVStatus(2, m);	
}

static void _HDMI20_PORT3_ReadLGTVStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLGTVStatus(3, m);	
}

static void _HDMI20_PORT4_ReadLGTVStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLGTVStatus(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}

static ssize_t _HDMI20_PORT1_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}

static ssize_t _HDMI20_PORT2_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}

static ssize_t _HDMI20_PORT3_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}

static ssize_t _HDMI20_PORT4_WriteLGTVStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	return 0;
}



static void _HDMI20_ESM_GetVersion(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ESM_GetVersion(m);
}

static void _HDMI20_ESM_GetLog(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ESM_GetLog(m);
}

static ssize_t _HDMI20_ESM_SetVersion(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_ESM_SetVersion(file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_ESM_SetLog(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_ESM_SetLog(file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadEye(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEye(0, m);	
}

static void _HDMI20_PORT1_ReadEye(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEye(1, m);	
}

static void _HDMI20_PORT2_ReadEye(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEye(2, m);	
}

static void _HDMI20_PORT3_ReadEye(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEye(3, m);	
}

static void _HDMI20_PORT4_ReadEye(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEye(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEye(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEye(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEye(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEye(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteEye(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEye(4, file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadPhyDefault(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhyDefault(0, m);	
}

static void _HDMI20_PORT1_ReadPhyDefault(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhyDefault(1, m);	
}

static void _HDMI20_PORT2_ReadPhyDefault(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhyDefault(2, m);	
}

static void _HDMI20_PORT3_ReadPhyDefault(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhyDefault(3, m);	
}

static void _HDMI20_PORT4_ReadPhyDefault(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhyDefault(4, m);	
}

static ssize_t _HDMI20_PORT0_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhyDefault(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhyDefault(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhyDefault(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhyDefault(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WritePhyDefault(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhyDefault(4, file, buf,size, off);
	return size;
}


static void _HDMI20_PORT0_ReadAledAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadAledAPB(0, m);	
}

static void _HDMI20_PORT1_ReadAledAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadAledAPB(1, m);	
}

static void _HDMI20_PORT2_ReadAledAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadAledAPB(2, m);	
}

static void _HDMI20_PORT3_ReadAledAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadAledAPB(3, m);	
}

static void _HDMI20_PORT4_ReadAledAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadAledAPB(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteAledAPB(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteAledAPB(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteAledAPB(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteAledAPB(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteAledAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteAledAPB(4, file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadTopAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadTopAPB(0, m);	
}

static void _HDMI20_PORT1_ReadTopAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadTopAPB(1, m);	
}

static void _HDMI20_PORT2_ReadTopAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadTopAPB(2, m);	
}

static void _HDMI20_PORT3_ReadTopAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadTopAPB(3, m);	
}

static void _HDMI20_PORT4_ReadTopAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadTopAPB(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteTopAPB(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteTopAPB(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteTopAPB(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteTopAPB(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteTopAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteTopAPB(4, file, buf,size, off);
	return size;
}


static void _HDMI20_PORT0_ReadLinkAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLinkAPB(0, m);	
}

static void _HDMI20_PORT1_ReadLinkAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLinkAPB(1, m);	
}

static void _HDMI20_PORT2_ReadLinkAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLinkAPB(2, m);	
}

static void _HDMI20_PORT3_ReadLinkAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLinkAPB(3, m);	
}

static void _HDMI20_PORT4_ReadLinkAPB(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadLinkAPB(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteLinkAPB(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteLinkAPB(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteLinkAPB(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteLinkAPB(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteLinkAPB(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteLinkAPB(4, file, buf,size, off);
	return size;
}



static void _HDMI20_PORT0_ReadPhy48(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy48(0, m);	
}

static void _HDMI20_PORT1_ReadPhy48(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy48(1, m);	
}

static void _HDMI20_PORT2_ReadPhy48(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy48(2, m);	
}

static void _HDMI20_PORT3_ReadPhy48(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy48(3, m);	
}

static void _HDMI20_PORT4_ReadPhy48(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy48(4, m);	
}

static ssize_t _HDMI20_PORT0_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy48(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy48(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy48(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy48(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WritePhy48(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy48(4, file, buf,size, off);
	return size;
}


static void _HDMI20_PORT0_ReadPhy38(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy38(0, m);	
}

static void _HDMI20_PORT1_ReadPhy38(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy38(1, m);	
}

static void _HDMI20_PORT2_ReadPhy38(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy38(2, m);	
}

static void _HDMI20_PORT3_ReadPhy38(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy38(3, m);	
}

static void _HDMI20_PORT4_ReadPhy38(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy38(4, m);	
}

static ssize_t _HDMI20_PORT0_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy38(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy38(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy38(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy38(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WritePhy38(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy38(4, file, buf,size, off);
	return size;
}




static void _HDMI20_PORT0_ReadPhy28(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy28(0, m);	
}

static void _HDMI20_PORT1_ReadPhy28(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy28(1, m);	
}

static void _HDMI20_PORT2_ReadPhy28(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy28(2, m);	
}

static void _HDMI20_PORT3_ReadPhy28(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy28(3, m);	
}

static void _HDMI20_PORT4_ReadPhy28(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPhy28(4, m);	
}

static ssize_t _HDMI20_PORT0_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy28(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy28(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy28(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy28(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WritePhy28(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePhy28(4, file, buf,size, off);
	return size;
}




static void _HDMI20_PORT0_ReadDataIsr(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadIsr(0, m);	
}

static void _HDMI20_PORT1_ReadDataIsr(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadIsr(1, m);	
}

static void _HDMI20_PORT2_ReadDataIsr(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadIsr(2, m);	
}

static void _HDMI20_PORT3_ReadDataIsr(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadIsr(3, m);	
}

static void _HDMI20_PORT4_ReadDataIsr(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadIsr(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteIsr(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteIsr(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteIsr(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteIsr(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteDataIsr(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteIsr(4, file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadHdcpStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadHDCPStatus(0, m);
}

static void _HDMI20_PORT1_ReadHdcpStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadHDCPStatus(1, m);
}

static void _HDMI20_PORT2_ReadHdcpStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadHDCPStatus(2, m);
}

static void _HDMI20_PORT3_ReadHdcpStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadHDCPStatus(3, m);
}

static void _HDMI20_PORT4_ReadHdcpStatus(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadHDCPStatus(4, m);
}

static ssize_t _HDMI20_PORT0_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteHDCPStatus(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteHDCPStatus(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteHDCPStatus(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteHDCPStatus(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteHdcpStatus(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteHDCPStatus(4, file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadDataEmPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEmPkt(0, m);	
}

static void _HDMI20_PORT1_ReadDataEmPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEmPkt(1, m);	
}

static void _HDMI20_PORT2_ReadDataEmPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEmPkt(2, m);	
}

static void _HDMI20_PORT3_ReadDataEmPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEmPkt(3, m);	
}

static void _HDMI20_PORT4_ReadDataEmPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEmPkt(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEmPkt(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEmPkt(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEmPkt(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEmPkt(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteDataEmPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEmPkt(4, file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadDataPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPkt(0, m);	
}

static void _HDMI20_PORT1_ReadDataPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPkt(1, m);	
}

static void _HDMI20_PORT2_ReadDataPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPkt(2, m);	
}

static void _HDMI20_PORT3_ReadDataPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPkt(3, m);	
}

static void _HDMI20_PORT4_ReadDataPkt(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPkt(4, m);	
}

static ssize_t _HDMI20_PORT0_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePkt(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePkt(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePkt(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePkt(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteDataPkt(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePkt(4, file, buf,size, off);
	return size;
}

static void _HDMI20_PORT0_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEDID(0, m);	
}

static void _HDMI20_PORT1_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEDID(1, m);	
}

static void _HDMI20_PORT2_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEDID(2, m);	
}

static void _HDMI20_PORT3_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEDID(3, m);	
}

static void _HDMI20_PORT4_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadEDID(4, m);	
}

static void _HDMI20_PORT0_FILE_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_FILE_ReadEDID(0, m);
}

static void _HDMI20_PORT1_FILE_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_FILE_ReadEDID(1, m);
}

static void _HDMI20_PORT2_FILE_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_FILE_ReadEDID(2, m);
}

static void _HDMI20_PORT3_FILE_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_FILE_ReadEDID(3, m);
}

static void _HDMI20_PORT4_FILE_ReadEDID(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_FILE_ReadEDID(4, m);
}

static ssize_t _HDMI20_PORT0_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEDID(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEDID(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEDID(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEDID(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteEDID(4, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT0_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_FILE_WriteEDID(0, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_FILE_WriteEDID(1, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_FILE_WriteEDID(2, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_FILE_WriteEDID(3, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_FILE_WriteEDID(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_FILE_WriteEDID(4, file, buf, size, off);
	return size;
}

static void _HDMI20_PORT0_ReadCalOS(struct seq_file *m )
{
	HDMI20_Module_ProcHandler_ReadCalOS(0, m);
}

static void _HDMI20_PORT1_ReadCalOS(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadCalOS(1, m);
}

static void _HDMI20_PORT2_ReadCalOS(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadCalOS(2, m);
}

static void _HDMI20_PORT3_ReadCalOS(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadCalOS(3, m);
}

static void _HDMI20_PORT4_ReadCalOS(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadCalOS(4, m);
}

static ssize_t _HDMI20_PORT0_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	//HDMI20_Module_ProcHandler_ReadCalOS(0, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	//HDMI20_Module_ProcHandler_ReadCalOS(1, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	//HDMI20_Module_ProcHandler_ReadCalOS(2, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	//HDMI20_Module_ProcHandler_ReadCalOS(3, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteCalOS(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	//HDMI20_Module_ProcHandler_ReadCalOS(4, file, buf, size, off);
	return size;
}


static void _HDMI20_PORT0_ReadDdcMon(struct seq_file *m )
{
	HDMI20_Module_ProcHandler_ReadDdcMon(0, m);
}

static void _HDMI20_PORT1_ReadDdcMon(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadDdcMon(1, m);
}

static void _HDMI20_PORT2_ReadDdcMon(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadDdcMon(2, m);
}

static void _HDMI20_PORT3_ReadDdcMon(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadDdcMon(3, m);
}

static void _HDMI20_PORT4_ReadDdcMon(struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadDdcMon(4, m);
}

static ssize_t _HDMI20_PORT0_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteDdcMon(0, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteDdcMon(1, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteDdcMon(2, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteDdcMon(3, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_WriteDdcMon(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WriteDdcMon(4, file, buf, size, off);
	return size;
}



static void _HDMI20_PORT0_PrintStatus (struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPort(m, 0);
}

static void _HDMI20_PORT1_PrintStatus (struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPort(m, 1);
}

static void _HDMI20_PORT2_PrintStatus (struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPort(m, 2);
}

static void _HDMI20_PORT3_PrintStatus (struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPort(m, 3);
}

static void _HDMI20_PORT4_PrintStatus (struct seq_file *m)
{
	HDMI20_Module_ProcHandler_ReadPort(m, 4);
}

static ssize_t _HDMI20_PORT0_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePort(0, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT1_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePort(1, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT2_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePort(2, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT3_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePort(3, file, buf,size, off);
	return size;
}

static ssize_t _HDMI20_PORT4_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_Module_ProcHandler_WritePort(4, file, buf,size, off);
	return size;
}


static void _HDMI20_DEVCON_Video_PrintStatus(struct seq_file *m)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_VIDEO;
	HDMI20_Module_ProcHandler_ReadDevCon(m, type) ;
}

static void _HDMI20_DEVCON_Audio_PrintStatus(struct seq_file *m)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_AUDIO;
	HDMI20_Module_ProcHandler_ReadDevCon(m, type);
}

static void _HDMI20_DEVCON_Phy_PrintStatus(struct seq_file *m)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_PHY;
	HDMI20_Module_ProcHandler_ReadDevCon(m, type);
}

static void _HDMI20_DEVCON_Link_PrintStatus(struct seq_file *m)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_LINK;
	HDMI20_Module_ProcHandler_ReadDevCon(m, type);
}

static void _HDMI20_DEVCON_Earc_PrintStatus(struct seq_file *m)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_EARC;
	HDMI20_Module_ProcHandler_ReadDevCon( m, type);
}

static void _HDMI20_DEVCON_Table_PrintStatus(struct seq_file *m)
{
	//HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_TABLE;
	HDMI20_DevCtrl_PrintPhyRegTable(m);
}

static ssize_t _HDMI20_DEVCON_Video_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_VIDEO;
	HDMI20_Module_ProcHandler_WriteDevCon(type, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_Audio_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_AUDIO;
	HDMI20_Module_ProcHandler_WriteDevCon(type, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_Phy_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_PHY;
	HDMI20_Module_ProcHandler_WriteDevCon(type, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_Link_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_LINK;
	HDMI20_Module_ProcHandler_WriteDevCon(type, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_Earc_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_EARC;
	HDMI20_Module_ProcHandler_WriteDevCon(type, file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_Table_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
//	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_TABLE;
	HDMI20_DevCtrl_WritePhyRegTable(file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_ReadTable_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
//	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_READ_TABLE;
	HDMI20_DevCtrl_ReadPhyRegTableMode(file, buf, size, off);
	return size;
}

static ssize_t _HDMI20_DEVCON_WriteTable_Cmd(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
//	HDMI20_DEV_CONTROL_TYPE_T type = HDMI20_DEV_CONTROL_WRITE_TABLE;
	HDMI20_DevCtrl_WritePhyRegTableMode(file, buf, size, off);
	return size;
}

/**
 * initialize proc utility for hdmi20 device
 *
 * @see HDMI20_Init
*/

static struct proc_dir_entry* _g_hdmi20_proc_dir;

void	HDMI20_PROC_Init (void)
{
	_g_hdmi20_proc_dir = OS_PROC_CreateEntryEx  ( HDMI20_MODULE,   _g_hdmi20_device_proc_table,
											_HDMI20_ReadProcFunction,
											_HDMI20_WriteProcFunction );

	OS_PROC_CreateEntry( "port0", _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_port0_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "port1", _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_port1_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "port2", _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_port2_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "port3", _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_port3_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "port4", _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_port4_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "devctrl", _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_devcon_proc_table, NULL, NULL );
	OS_PROC_CreateEntry( "esm",     _g_hdmi20_proc_dir, (OS_PROC_DESC_TABLE_T*)_g_hdmi20_esm_proc_table, NULL, NULL );

	/* TV lab request : http://clm.lge.com/issue/browse/SCDCR-2657 */
	{
		struct proc_dir_entry *proc_entry = OS_PROC_GetLinuxTvEntry();

		if (!proc_entry)
		{
			printk("proc_entry for hdmi20 is not ready\n");
			return;
		}

		OS_PROC_CreateEntry( "hdmi_status", proc_entry, (OS_PROC_DESC_TABLE_T*)lgtv_hdmi20_port_proc_table, NULL, NULL );
	}


}

/**
 * cleanup proc utility for hdmi20 device
 *
 * @see HDMI20_Cleanup
*/
void	HDMI20_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( HDMI20_MODULE );
}

/** @} */
