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
 *  Linux proc interface for vbi device.
 *	vbi device will teach you how to make device driver with new platform.
 *
 *  author		won.hur (won.hur@lge.com)
 *  version		1.0
 *  date		2012.04.16
 *  note		Additional information.
 *
 *  @addtogroup lg115x_vbi
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
#include "vbi_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#include "vbi_module.h"
#include "vbi_data.h"
#include "vbi_kwrap.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_COMMAND,
	PROC_ID_CC_COUNT,
	PROC_ID_VBI_DEBUG,
	PROC_ID_TTX_PRINT,
	PROC_ID_CC_PRINT,
	PROC_ID_VBI_KWRAP_DEBUG,
	PROC_ID_VBI_STATUS,
	PROC_ID_DATA_PROFILER,
	PROC_ID_FIX_CC_PARITY,
	PROC_ID_TTX_UNIT_TEST,
	PROC_ID_TTX_ENABLE_HAMM_ERROR_FIX,
	PROC_ID_TTX_BUFFER_RESET,
	PROC_ID_CC_BUFFER_RESET,
	PROC_ID_VBI_SERVICE,
	PROC_ID_WSS_BUFFER_RESET,
	PROC_ID_VPS_BUFFER_RESET,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void	VBI_PROC_Init (void);
void	VBI_PROC_Cleanup (void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern UINT32	gVBIBreakPrintOnOff;

extern VBI_KWRAP_DEBUGGER_T gVBIDebugModeStatus;

extern sBufInform cc_buf;
extern volatile void *gVBI_data_mem_addr;
extern volatile void *gVBI_CC_CGMS_data_mem_addr;
extern unsigned int gVBIVpsMemoryStart;
extern unsigned int gVBIWssMemoryStart;
extern UINT16 vbi_service_set;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _vbi_proc_vbi_debug_read(struct seq_file *m);
static ssize_t _vbi_proc_vbi_debug_write(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _vbi_proc_cc_print_read(struct seq_file *m);
static ssize_t _vbi_proc_cc_print_write(struct file *file, const char __user *buf, size_t size, loff_t *off);

static void _vbi_proc_vbi_status_read(struct seq_file *m, void* data);

static void _vbi_proc_data_profiler_read(struct seq_file *m);
static ssize_t _vbi_proc_data_profiler_write(struct file *file, const char __user *buf, size_t size, loff_t *off);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRW_DEFINE_EX(_vbi_proc_vbi_debug_fops, _vbi_proc_vbi_debug_read, _vbi_proc_vbi_debug_write)
OS_PROC_SEQRW_DEFINE_EX(_vbi_proc_cc_print_fops, _vbi_proc_cc_print_read, _vbi_proc_cc_print_write)
OS_PROC_SEQRD_DEFINE_EX(_vbi_proc_vbi_status_fops, _vbi_proc_vbi_status_read, 0)
OS_PROC_SEQRW_DEFINE_EX(_vbi_proc_data_profiler_fops, _vbi_proc_data_profiler_read, _vbi_proc_data_profiler_write)

static OS_PROC_DESC_TABLE_T	_g_vbi_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND , OS_PROC_FLAG_WRITE },
	{ "cc_count",	PROC_ID_CC_COUNT, OS_PROC_FLAG_READ },
	{ "vbi_debug",	PROC_ID_VBI_DEBUG,     OS_PROC_FLAG_SEQRW, (void*)&_vbi_proc_vbi_debug_fops},
	{ "ttx_print",	PROC_ID_TTX_PRINT    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cc_print",	PROC_ID_CC_PRINT,     OS_PROC_FLAG_SEQRW, (void*)&_vbi_proc_cc_print_fops},
	{ "vbi_kwrap_debug",	PROC_ID_VBI_KWRAP_DEBUG    , OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "vbi_status",		PROC_ID_VBI_STATUS,     OS_PROC_FLAG_SEQRD, (void*)&_vbi_proc_vbi_status_fops},
	{ "data_profiler",	PROC_ID_DATA_PROFILER,     OS_PROC_FLAG_SEQRW, (void*)&_vbi_proc_data_profiler_fops},
	{ "fix_cc_parity", PROC_ID_FIX_CC_PARITY,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ "ttx_unit_test", PROC_ID_TTX_UNIT_TEST,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ "ttx_hamm_enable", PROC_ID_TTX_ENABLE_HAMM_ERROR_FIX,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ "ttx_buffer_reset", PROC_ID_TTX_BUFFER_RESET,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ "cc_buffer_reset", PROC_ID_CC_BUFFER_RESET,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ "vbi_service", PROC_ID_VBI_SERVICE,	OS_PROC_FLAG_READ},
	{ "wss_buffer_reset", PROC_ID_WSS_BUFFER_RESET,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ "vps_buffer_reset", PROC_ID_VPS_BUFFER_RESET,	OS_PROC_FLAG_READ |OS_PROC_FLAG_WRITE},
	{ NULL, 		PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _vbi_proc_vbi_debug_read(struct seq_file *m)
{
	if (!m)	return;

	seq_printf(m, "echo item(number) type > vbi_debug \n");
	seq_printf(m, "VBI_PRINT	[%d] \n", LX_LOGM_LEVEL_NOTI);
	seq_printf(m, "VBI_INFO	[%d] \n", LX_LOGM_LEVEL_INFO);
	seq_printf(m, "VBI_WARN	[%d] \n", LX_LOGM_LEVEL_WARNING);
	seq_printf(m, "VBI_DEBUG	[%d] \n", LX_LOGM_LEVEL_DEBUG);
	seq_printf(m, "VBI_ERROR	[%d] \n", LX_LOGM_LEVEL_ERROR);
	seq_printf(m, "VBI_INTR_PRINT	[%d] \n", LX_LOGM_LEVEL_TRACE+0);
	seq_printf(m, "TTX_PRINT	[%d] \n", LX_LOGM_LEVEL_TRACE+1);
	seq_printf(m, "TTX_TRACE	[%d] \n", LX_LOGM_LEVEL_TRACE+1);
	seq_printf(m, "CC_PRINT	[%d] \n", LX_LOGM_LEVEL_TRACE+2);
	seq_printf(m, "CC_TRACE	[%d] \n", LX_LOGM_LEVEL_TRACE+2);
	seq_printf(m, "TTX_PKT_PRINT	[%d] \n", LX_LOGM_LEVEL_TRACE+4);
	seq_printf(m, "CC_PKT_PRINT	[%d] \n", LX_LOGM_LEVEL_TRACE+5);
	seq_printf(m, "VPS_PKT_PRINT	[%d] \n", LX_LOGM_LEVEL_TRACE+6);
	seq_printf(m, "WSS_PKT_TRACE	[%d] \n", LX_LOGM_LEVEL_TRACE+7);

	return;
}

static ssize_t _vbi_proc_vbi_debug_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	UINT32 type, onoff;
	int ret;
	__attribute__((unused)) static int count = 0;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "%d %d", &type, &onoff)) != 2) {
		printk("Wrong usage. ret = %d\n", ret);
		return size;
	}

	if(onoff == 0)
	{
		OS_DEBUG_DisableModuleByIndex(g_vbi_debug_fd, type);
		printk("VBI_PRINT_TYPE[%d] is disabled.\n", type);
	}
	else
	{
		OS_DEBUG_EnableModuleByIndex(g_vbi_debug_fd, type, 0);
		printk("VBI_PRINT_TYPE[%d] is enabled Color is [%d].\n", type, 0);
	}

	return size;
}

static void _vbi_proc_cc_print_read(struct seq_file *m)
{
	if (!m)	return;

	seq_printf(m, "echo item (1:on, 0:off) > cc_print \n");
	seq_printf(m, "mode:0 disable CC print\n");
	seq_printf(m, "mode:1 PrintCCData\n");
	seq_printf(m, "mode:2 PrintResultofLineDetect\n");
	seq_printf(m, "mode:3 PrintCGMSData\n");
	seq_printf(m, "mode:4 PrintWSSData\n");

	return;
}

static ssize_t _vbi_proc_cc_print_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	UINT32 mode = 0; 
	int ret;
	__attribute__((unused)) static int count = 0;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "%d", &mode)) != 1) {
		printk("Wrong usage. ret = %d\n", ret);
		return size;
	}

	vbi_kwrap_cc_setdebugmodekprint(mode);

	return size;
}

static void _vbi_proc_vbi_status_read(struct seq_file *m, void* data)
{
	if (!m)	return;

	seq_printf(m, "CC: header:0x%x,tail:0x%x, count:%d\n", cc_buf.header, cc_buf.tailer, cc_buf.count);
	if(gVBI_data_mem_addr != NULL)
	{
		seq_printf(m, "line_count [29:22],status[19:16],data1[15:8],data0[7:0]\n");
		seq_printf(m, "cc data head :%4ph\n", (UINT8 *)(gVBI_data_mem_addr + cc_buf.header) );
	}
	if(gVBI_CC_CGMS_data_mem_addr != NULL)
	{
		seq_printf(m, "preamble:3,status:1,datacount:1,linecount:2,data0/1/2\n");
		seq_printf(m, "cgms data :%10ph\n", (UINT8 *)gVBI_CC_CGMS_data_mem_addr);
	}
	if( (gVBI_data_mem_addr != NULL) && (gVBIVpsMemoryStart != 0))
	{
		seq_printf(m, "vps data :%16ph\n", (UINT8 *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBIVpsMemoryStart) );
	}
	if( (gVBI_data_mem_addr != NULL) && gVBIWssMemoryStart != 0)
	{
		seq_printf(m, "wss data :%16ph\n", (UINT8 *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBIWssMemoryStart));
	}
	if(VBI_get_buffer_ptr() != NULL)
	{
		seq_printf(m, "TTX: getaddr:0x%x, putaddr:0x%x\n", VBI_get_ttx_parameter_ptr()->GetAddr, VBI_get_ttx_parameter_ptr()->PutAddr);
		seq_printf(m, "TTX data :%48ph\n", (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)VBI_get_ttx_parameter_ptr()->PutAddr) );
	}

	seq_printf(m, "Mask Status [Break : %d]/[TTX : %d]/[CC : %d]/[WSS : %d]/[VPS %d]/[CGMS %d]\n",\
			gVBIBreakPrintOnOff,\
			gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_TTX],\
			gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CC], \
			gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_WSS],\
			gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_VPS],\
			gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CGMS]);

	seq_printf(m, "FIX_CC_PARITY : %d \n", gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_FIX_CC_PARITY]);
	seq_printf(m, "TTX_UNIT_TEST : %d \n", gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_TARA_UNIT_TEST]);
	seq_printf(m, "TTX_ENABLE_HAMM_ERROR_FIX : %d \n", gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX]);

	return;
}

static void _vbi_proc_data_profiler_read(struct seq_file *m)
{
	if (!m)	return;

	if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter] > 0)
	{
		seq_printf(m, "ProFilter is still running. Please wait until profiling is done!\n");
		seq_printf(m, "ProFilter status [error][proceed]/[total] : [%d]/[%d]/[%d]\n", gVBIDebugModeStatus.dataProfile.error_count, gVBIDebugModeStatus.dataProfile.full_count,gVBIDebugModeStatus.dataProfile.max_count_value);
	}
	else
	{
		if(	gVBIDebugModeStatus.dataProfile.full_count == 0)
		{
			seq_printf(m, "ProFilter did not operate or there was no processed data to proceed.\n");
			seq_printf(m, "echo 1(enable)/0(disable) > data_profiler\n");
			seq_printf(m, "or\n");
			seq_printf(m, "echo num(max_count_value not 0 or 1) > data_profiler\n");
		}
		else
		{
			//float performance = (float)(gVBIDebugModeStatus.dataProfile.full_count - gVBIDebugModeStatus.dataProfile.error_count);
			//performance = performance / (float)gVBIDebugModeStatus.dataProfile.full_count;

			seq_printf(m, "Profile Result [ERROR]/[TOTAL] : [%u]/[%u]\n",	gVBIDebugModeStatus.dataProfile.error_count, gVBIDebugModeStatus.dataProfile.full_count);
			//	seq_printf(m, "VBI HW data slicer performance is :[%f] percent\n",performance*100);
		}
	}

	return;
}

static ssize_t _vbi_proc_data_profiler_write(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[256];
	UINT32 mode = 0; 
	int ret;
	__attribute__((unused)) static int count = 0;

	/* Size Check */
	if( size == 0) {
		printk("[%s:%d] size is 0\n", __F__, __L__);
		return size;
	}

	if(*off != 0) {
		printk("[%s:%d] Do not support multi write\n", __F__, __L__);
		return size;
	}

	if(size>sizeof(cmdbuf)-1) {
		printk("[%s:%d] userbuf too long to proceed.\n", __F__, __L__);
		return size;
	}

	if(copy_from_user(cmdbuf, buf, size)>0) {
		printk("[%s:%d] copy from user error\n", __F__, __L__);
		return size;
	}

	/* Make sure last word is NULL to proceed string print*/
	cmdbuf[size-1]= 0;

	if( (ret = sscanf(cmdbuf, "%d", &mode)) != 1) {
		printk("Wrong usage. ret = %d\n", ret);
		return size;
	}

	if(mode == 1)  
	{
		vbi_kwrap_resetdataprofilter();
		gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter] = 1;
	}
	else if(mode == 0)
		gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter] = 0;
	else
		gVBIDebugModeStatus.dataProfile.max_count_value = mode;

	return size;
}
/*
 * read_proc implementation of vbi device
 *
*/
static int	_VBI_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer, 48, "%s\n", "wonsik.do (wonsik.do@lge.com):20020500" );
		}
		break;

		case PROC_ID_CC_COUNT:
		{
			//ret = sprintf( buffer, "data count in CC buffer = %d\n", TTX_CC_GetVBIBufferInform() );
		}
		break;

		case PROC_ID_TTX_PRINT:
		{
			ret = snprintf( buffer, 48, "%s\n", "echo (1:on, 0:off) > ttx_print" );
		}
		break;

		case PROC_ID_VBI_KWRAP_DEBUG:
		{
			printk("Mask Status [Break : %d]/[TTX : %d]/[CC : %d]/[WSS : %d]/[VPS %d]/[CGMS %d]\n",\
					gVBIBreakPrintOnOff,\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_TTX],\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CC], \
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_WSS],\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_VPS],\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CGMS]);
			ret = snprintf( buffer, 96, "echo Type(0:TTX, 1:CC, 2:WSS, 3:VPS, 4:CGMS, 5:BREAK) on_off(1/0) >  vbi_kwrap_debug\n");
		}
		break;

		case PROC_ID_FIX_CC_PARITY:
		{
			printk("FIX_CC_PARITY : %d \n", gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_FIX_CC_PARITY]);
			ret = snprintf( buffer, 96, "echo item (1:on, 0:off) > fix_cc_parity \n");
		}
		break;

		case PROC_ID_TTX_UNIT_TEST:
		{
			printk("TTX_UNIT_TEST : %d \n", gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_TARA_UNIT_TEST]);
			ret = snprintf( buffer, 96, "echo item (1:on, 0:off) > ttx_unit_test \n");
		}
		break;

		case PROC_ID_TTX_ENABLE_HAMM_ERROR_FIX:
		{
			printk("TTX_ENABLE_HAMM_ERROR_FIX : %d \n", gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX]);
			ret = snprintf( buffer, 96, "echo item (1:on, 0:off) > ttx_hamm_enable \n");
		}
		break;

		case PROC_ID_VBI_SERVICE:
		{
			ret = snprintf( buffer, 96, "vbi service set 0x%x\n", vbi_service_set);
		}
		break;

		case PROC_ID_TTX_BUFFER_RESET:
		{
			ret = snprintf( buffer, 48, "%s\n", "echo 1 > ttx_buffer_reset");
		}
		break;

		case PROC_ID_CC_BUFFER_RESET:
		{
			ret = snprintf( buffer, 48, "%s\n", "echo 1 > cc_buffer_reset");
		}
		break;

		case PROC_ID_WSS_BUFFER_RESET:
		{
			ret = snprintf( buffer, 48, "%s\n", "echo 1 > wss_buffer_reset");
		}
		break;

		case PROC_ID_VPS_BUFFER_RESET:
		{
			ret = snprintf( buffer, 48, "%s\n", "echo 1 > vps_buffer_reset");
		}
		break;

		default:
		{
			ret = snprintf( buffer, 48, "%s\n", "unimplemented read proc");
		}
	}

	return ret;
}

/*
 * write_proc implementation of vbi device
 *
*/
static int _VBI_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("command string : %s\n", command );
		}
		break;

		case PROC_ID_TTX_PRINT:
		{
			UINT32 offON = 0; // 0:off, 1:on
			sscanf( command, "%d", &offON);

			if(offON == 1)
			{
				printk("Turning on TTXDataPrint.........\n");
				vbi_kwrap_ttx_setdebugmodekprint(1);
			}
			else
			{
				printk("Turning off TTXDataPrint.........\n");
				vbi_kwrap_ttx_setdebugmodekprint(0);
			}
		}
		break;

		case PROC_ID_VBI_KWRAP_DEBUG:
		{
			UINT32 type = 0;
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d %d", &type, &onoff);

			printk("Mask Status [Break : %d]/[TTX : %d]/[CC : %d]/[WSS : %d]/[VPS %d]/[CGMS %d]\n",\
					gVBIBreakPrintOnOff,\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_TTX],\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CC], \
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_WSS],\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_VPS],\
					gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CGMS]);\

			if(type == 5) gVBIBreakPrintOnOff = onoff;
			else if(onoff > 0) gVBIDebugModeStatus.printMask[type] = 1;
			else gVBIDebugModeStatus.printMask[type] = 0;
		}
		break;

		case PROC_ID_FIX_CC_PARITY:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
				gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_FIX_CC_PARITY] = 1;
			else
				gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_FIX_CC_PARITY] = 0;
		}
		break;

		case PROC_ID_TTX_UNIT_TEST:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
				gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_TARA_UNIT_TEST] = 1;
			else
				gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_TARA_UNIT_TEST] = 0;
		}
		break;

		case PROC_ID_TTX_ENABLE_HAMM_ERROR_FIX:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
				gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX] = 1;
			else
				gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX] = 0;
		}
		break;

		case PROC_ID_TTX_BUFFER_RESET:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
			{
				printk("ttx_buffer_reset !!! \n");
				vbi_kwrap_ttx_resetbuffer();
			}
		}
		break;

		case PROC_ID_CC_BUFFER_RESET:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
			{
				printk("cc_buffer_reset !!!\n");
				vbi_kwrap_cc_resetbuffer();
			}
		}
		break;

		case PROC_ID_WSS_BUFFER_RESET:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
			{
				printk("wss_buffer_reset !!!\n");
				vbi_kwrap_ttx_reset_wss();
			}
		}
		break;

		case PROC_ID_VPS_BUFFER_RESET:
		{
			UINT32 onoff = 0; // 0:off, 1:on

			sscanf( command, "%d", &onoff);

			if(onoff == 1)  
			{
				printk("vps_buffer_reset !!!\n");
				vbi_kwrap_ttx_reset_vps();
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

/**
 * initialize proc utility for vbi device
 *
 * @see VBI_Init
*/
void	VBI_PROC_Init (void)
{
	OS_PROC_CreateEntryEx  ( VBI_MODULE,   _g_vbi_device_proc_table,
											_VBI_ReadProcFunction,
											_VBI_WriteProcFunction );
}

/**
 * cleanup proc utility for vbi device
 *
 * @see VBI_Cleanup
*/
void	VBI_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( VBI_MODULE );
}

/** @} */

