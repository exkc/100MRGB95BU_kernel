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
 *	History manager implementation for de and pe devices.
 *
 *
 *	author		arjun.purushothaman (arjun.purushothaman@lge.com)
 *	version		1.0
 *	date		2014.11.3
 *	note		Additional information.
 *
 *	@addtogroup lg1150_de
 *	@{
 */

#include <linux/slab.h>
#include <linux/string.h>
#include "os_util.h"
#include "base_device.h"
#include "history_mgr.h"
//#include "pe_history.h"
#include "de_history.h"

//global variables
//HIST_BUF_T g_history_buffer[HIST_MAX_NUM];	//buffer for module independent command history
HIST_BUF_T *g_history_buffer;
int g_hist_index = 0;	//reference index for combined history
int g_buf_ovflow_flag = 0;
int g_isPopActive = 0;
int gUseHistory = 0;
//FILE *histfile;
/*
HIST_BUF_T g_de_hist_buff[HIST_DE_MAX_NUM];	//buffer for only DE functions
int g_de_hist_index = 0;

HIST_BUF_T g_pe_hist_buff[HIST_PE_MAX_NUM];	//buffer for only PE functions
int g_pe_hist_index = 0;

//add other module history buffers here
*/

int Pop_Ioc_Hist(int show_num);

//global de function list
//Harish: Modified to store function indexed mapped to corresponding IOCTL index
//inplace of separate index function table
FUNC_NAME_LIST_T g_de_func_list[DE_IOC_MAXNR];

#ifdef USE_HISTORY	
//initialization function for history buffer
static int _init_hist_buf(BOOLEAN sel)
{
	int ret = RET_OK;
	int i;

      //Populate DE function table
      DE_Populate_Fn_Table();

	g_history_buffer = (HIST_BUF_T *)OS_Malloc(HIST_MAX_NUM*sizeof(HIST_BUF_T));
	for(i=0;i<HIST_MAX_NUM;i++)
	{
		g_history_buffer[i].t.sec  = 0;
		g_history_buffer[i].t.msec = 0;
		g_history_buffer[i].t.usec = 0;
		g_history_buffer[i].p      = NULL;
	}
	return ret;
}

static void reset_ioc_buf(void)
{
	int i;
	for(i=0;i<HIST_MAX_NUM;i++)
		{
			if(g_history_buffer[i].p != NULL) OS_Free(g_history_buffer[i].p);
			g_history_buffer[i].p = NULL;
		}
		OS_Free(g_history_buffer);
		g_history_buffer = (HIST_BUF_T *)OS_Malloc(HIST_MAX_NUM*sizeof(HIST_BUF_T));
		for(i=0;i<HIST_MAX_NUM;i++)
		{
			g_history_buffer[i].t.sec  = 0;
			g_history_buffer[i].t.msec = 0;
			g_history_buffer[i].t.usec = 0;
			g_history_buffer[i].p      = NULL;
		}
}
//Function to push timing info and reset the history buffer when buffer overflows
static void Push_Time_Buff_Reset_Check(void)
{
	TIME_ST_T t;
	OS_GetCurrentTicks(&t.sec, &t.msec, &t.usec);
	memcpy(&g_history_buffer[g_hist_index].t, (char*)&t, sizeof(TIME_ST_T));
	g_hist_index++;
	//reset the history buffer once it is full
	if(HIST_MAX_NUM == g_hist_index)
	{
		reset_ioc_buf();
		g_hist_index = 0;
		g_buf_ovflow_flag++;
	}
}
#endif
//Top Level Push Function to call module-wise push functions according to incoming ioctl command
int Push_Ioc_Hist(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;
#ifdef USE_HISTORY	
	int module_no,func_no;

	if((0==g_hist_index)&&(0==g_buf_ovflow_flag)){
		_init_hist_buf(TRUE);
	}

	//Do not push if a pop operation is going on
	if(g_isPopActive == 1){
		printk("History Push missed due to active History Print\n");
		return RET_ERROR;
	}

	//printk("passed cmd = 0x%08x\n",cmd);
	module_no = _IOC_TYPE(cmd);
	func_no = _IOC_NR(cmd);

	if(cmd == PE_IOWR_PKT){
		PE_Push_Hist(cmd,arg);
	} else{
		switch(module_no){
			case DE_IOC_MAGIC:{
				#if 0
					DE_Push_Hist(cmd,arg);
				#else

				#endif
			}break;
			default:{
				printk("History Push Not implemented for module %x\n",module_no);
				goto ERROR;
			}
		}
	}

	Push_Time_Buff_Reset_Check();

ERROR:
#endif
	return ret;
}

//Top level Pop function. Pops data using modulewise Pop functions
int Pop_Ioc_Hist(int show_num)
{
	int ret = RET_OK;
#ifdef USE_HISTORY	
	int popcount;
	UINT32 cmd;
	int module_no;
	if(g_history_buffer==NULL)
	{
		printk("No History Available\n");
		return RET_ERROR;
	}
	printk("\n--------------------History Begin---------------------");
	g_isPopActive = 1;
	for(popcount=0; popcount<show_num; popcount++){
			if(g_history_buffer[popcount].p == NULL){
				printk("\n--------------------History End------------------\n");
				break;
			}

			cmd = g_history_buffer[popcount].c;
			module_no = _IOC_TYPE(cmd);
			if(cmd == PE_IOWR_PKT){
				// not used !!!      PE_Pop_Hist(cmd,popcount);
			}else{
			switch(module_no){
				case DE_IOC_MAGIC:{
					DE_Pop_Hist(cmd,popcount);
				}break;
				default:{
				printk("History Pop Not implemented for module %x\n",module_no);
				}
			}
		}
	}
	g_isPopActive = 0;
#endif	
	return ret;
}
