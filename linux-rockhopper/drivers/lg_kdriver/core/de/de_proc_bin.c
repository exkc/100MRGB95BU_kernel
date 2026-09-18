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
 *  Linux proc interface for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *  author		dongho7.park (dongho7.park@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_de
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
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/delay.h>
#include "os_util.h"
#include "be_kapi.h"
#include "../be/be_def.h"
#include "../be/frc/frc_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* ver, yyyy/mm/dd/hh:mm */
#define DE_PROC_BIN_VER  "2019/08/08/15:30"

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int de_proc_bin_download(char* command);
int de_proc_bin_read_function(int id);
int de_proc_bin_write_function(int id, char* command);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_proc_bin_read_function(int id)
{
	printk("[%d] ver : %s\n",id,DE_PROC_BIN_VER);

	switch (id)
	{
		case 0:
		{
			printk("Usage : echo [bin] [address] > /proc/lg/de/bin_download\n");
			printk("eg. echo binary.bin 0xfabcfabc > /proc/lg/de/bin_download\n");
			printk("Usage : echo sendfw > /proc/lg/de/bin_download\n");
		}break;
		default:
			break;
	}
	return 0;
}

int de_proc_bin_write_function(int id, char* command)
{
	switch (id)
	{
		case 0:
		{
			de_proc_bin_download(command);
		}break;
		default:
			break;
	}
	return 0;
}

static int de_proc_bin_is_valid_addr(unsigned int addr)
{
	int valid = 1;

	if (addr == 0) valid = 0;
	else if (addr < 0x10000000) valid = 0;
	else if (addr >= 0x40000000 && addr < 0x40020000) valid = 0;
	else if (addr >= 0x50000000 && addr < 0x50200000) valid = 0;
	else if (addr >= 0xC0000000) valid = 0;
	else if (addr < 0x36400000) valid = 0;
	else if (addr >= 0x80000000 && addr < 0x95800000) valid = 0;
	else if ((addr&3) != 0) valid = 0;

	return valid;
}

static int de_proc_bin_sendfw(unsigned int addr, int size)
{
	LX_BE_FRC_CMD_T params;

	if (0 == de_proc_bin_is_valid_addr(addr) || size<=0)
	{
		printk("send fail : not ready(addr:0x%08x)(size:%d)\n\n",addr,size);
		return -100;
	}

	memset(params.str,0,256);
	snprintf(params.str,256,"sendfw 0x%08x %d",addr,size);
	printk("command : %s\n\n",params.str);
#ifdef INCLUDE_KDRV_BE
	BE_FRC_HAL_RunCommand(&params);
#endif

	return 0;
}

#define DE_PROC_BIN_ALLOC_SIZE  (4*1024*1024)
#define DE_PROC_BIN_STEP_MAX    (100)
static int de_proc_bin_download(char* command)
{
	int ret = 0;
	int ret0 = 0;
	struct file *filp = NULL;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
	mm_segment_t old_fs;
#endif
	int bin_size = 0;
	int alloc_size = 0;
	int rd_size = 0;
	int i = 0;
	int last_step = 0;
	char *p_bin = NULL;
	char *p_vmaddr = NULL;
	char bin_name[32];
	unsigned int wr_addr = 0;
	unsigned int in_addr = 0;
	unsigned int vm_addr = 0;
	unsigned int vm_ofst = 0;
	loff_t cur_f_pos = 0;
	static int send_size = 0;
	static unsigned int send_addr = 0;

	printk("\n");
	if (!command)	{printk("command null\n");return -1;}

	memset(bin_name,0,32);
	sscanf(command,"%s 0x%x",bin_name,&in_addr);

	if (!strcmp(bin_name, "sendfw"))	{return de_proc_bin_sendfw(send_addr,send_size);}
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
	old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	set_fs(KERNEL_DS);
#else
	set_fs(get_ds());
#endif
#endif
	do {
		if (0 == de_proc_bin_is_valid_addr(in_addr)){printk("invalid in_addr(0x%08x)\n",in_addr);ret = -2;break;}

		printk("searching : %s (0x%08x)\n",bin_name,in_addr);

		filp = filp_open(bin_name,O_RDONLY,0);

		if (IS_ERR(filp))	{printk("no bin file(%p)\n",filp);ret = -3;break;}

		printk("search : ok\n");

		bin_size = vfs_llseek(filp,0,SEEK_END);
		vfs_llseek(filp,0,SEEK_SET);

		if (bin_size<=0)	{printk("invalid bin_size(%d)\n",bin_size);ret = -4;break;}
		if (bin_size>=(DE_PROC_BIN_ALLOC_SIZE*DE_PROC_BIN_STEP_MAX)){printk("too big bin_size(%d)\n",bin_size);ret = -5;break;}

		alloc_size = DE_PROC_BIN_ALLOC_SIZE;

		printk("bin_size:%d(0x%x),alloc_size:%d(0x%x)\n",bin_size,bin_size,alloc_size,alloc_size);

		filp->f_pos = 0;
		do {
			printk("[%02d]----------------------------------------------------------\n",i);
			p_bin = NULL;
			p_vmaddr = NULL;
			do {
				printk("[%02d]kmalloc(alloc_size:%d(0x%x))\n",i,alloc_size,alloc_size);
				p_bin = (char *)kmalloc(alloc_size,GFP_KERNEL);
				if (!p_bin)		{printk("[%02d]kmalloc error\n",i);ret = -10;break;}

				rd_size = bin_size - filp->f_pos;
				printk("[%02d]estimate0(rd_size:%d)(bin_size:%d)(f_pos:%d)\n",i,rd_size,bin_size,(int)filp->f_pos);
				if (rd_size<=0)	{printk("[%02d]rd_size is wrong(%d)\n",i,rd_size);ret = -11;break;}

				if (rd_size<=alloc_size)	last_step = 1;
				printk("[%02d]estimate1(rd_size:%d)(alloc_size:%d)(last_step:%d)\n",i,rd_size,alloc_size,last_step);

				if (rd_size>alloc_size)		rd_size=alloc_size;
				cur_f_pos = filp->f_pos;
				printk("[%02d]kernel_read(rd_size:%d)(f_pos:%d)\n",i,rd_size,(int)filp->f_pos);
				ret0 = kernel_read(filp,p_bin,rd_size,&filp->f_pos);//vfs_read(legacy)
				if (ret0<0)		{printk("[%02d]kernel_read error(%d)\n",i,ret0);ret = -12;break;}

				wr_addr = in_addr + cur_f_pos;
				printk("[%02d]estimate2(wr_addr:0x%08x)(in_addr:0x%08x)(cur:%d)(f_pos:%d)\n",i,wr_addr,in_addr,(int)cur_f_pos,(int)filp->f_pos);
				if (0 == de_proc_bin_is_valid_addr(wr_addr)){printk("[%02d]invalid wr_addr(0x%08x)\n",i,wr_addr);ret = -13;break;}

				vm_addr = (wr_addr>>12)<<12;//4k align
				vm_ofst = wr_addr - vm_addr;

				printk("[%02d]estimate3(vm_addr:0x%08x)(wr_addr:0x%08x)(vm_ofst:%d(0x%x))\n",i,vm_addr,wr_addr,vm_ofst,vm_ofst);
				if (vm_ofst<0)	{printk("[%02d]vm_ofst is wrong(%d)\n",i,vm_ofst);ret = -14;break;}

				printk("[%02d]vmap(vm_addr:0x%08x)(rd_size:%d(0x%x))(vm_ofst:%d(0x%x))\n",i,vm_addr,rd_size,rd_size,vm_ofst,vm_ofst);

				p_vmaddr = (char *)vmap_phys(vm_addr,rd_size+vm_ofst);
				if (!p_vmaddr)	{printk("[%02d]vmap_phys null\n",i);ret = -15;break;}

				printk("[%02d]memcpy(rd_size:%d(0x%x))\n",i,rd_size,rd_size);
				memcpy((char *)((uintptr_t)p_vmaddr+(uintptr_t)vm_ofst),p_bin,rd_size);
				wmb();
			} while(0);
			if (p_bin)			kfree(p_bin);
			if (p_vmaddr)		vunmap_phys((void*)p_vmaddr);
			printk("[%02d]end this step(last_step:%d)(ret:%d)-------------------------\n",i,last_step,ret);
			i++;
			msleep(1);
		} while(i<DE_PROC_BIN_STEP_MAX && last_step==0 && ret==0);
	} while(0);
	if (filp) filp_close(filp,NULL);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
	set_fs(old_fs);
#endif
	if (ret == 0)
	{
		send_addr = in_addr;
		send_size = bin_size;
		printk("backup(in_addr:0x%08x)(bin_size:%d(0x%x))\n",send_addr,send_size,send_size);
	}

	printk("done(bin_size:%d(0x%x))(f_pos:%d)(ret:%d)\n\n",bin_size,bin_size,(int)cur_f_pos,ret);

	return ret;
}

/** @} */

