/*
	SystemIC Center, LG Electronics
    COPYRIGHT(c) LGE CO.,LTD. 2020. SEOUL, KOREA.\n
    All rights are reserved.\n
    No part of this work covered by the copyright hereon may be
    reproduced, stored in a retrieval system, in any form or
    by any means, electronic, mechanical, photocopying, recording
    or otherwise, without the prior permission of LG Electronics.
    
	@code
    ASD Group, SystemIC Center, LG Electronics
    @endcode

    @file	pmt_drv.c
    @author	hyunsoo0802.lim@lg.com
    @date	2020/01/01
    @brief  BUS Performance MoniToring Driver 
*/


#ifndef _PERF_MON_TARGET_DRV_C_
#define _PERF_MON_TARGET_DRV_C_


/*=========================================================================================*
| Header files																			   
*==========================================================================================*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <linux/vmalloc.h>
#include "pmt.h"

/*=========================================================================================*
| Symbolic Constant																			   
*==========================================================================================*/
MODULE_LICENSE("Dual BSD/GPL");

#define PMT_DEBUG_ENABLE		0
#define PMT_DEBUG(fmt, args...) \
	do { if(PMT_DEBUG_ENABLE) printk(fmt,## args); } while(0)

#define	PMT_ERROR(fmt,args...)		printk("[BUS_PMT-Err] %s:%d " fmt, __F__, __LINE__, ##args)

#define PMT_CHECK_CODE(__checker,__if_action,fmt,args...)   \
		__CHECK_IF_ERROR(__checker, PMT_ERROR, __if_action , fmt, ##args )

/*=========================================================================================*
| Type definitions																			   
*==========================================================================================*/

//Address : volatile void
typedef struct {
	UINT32				irq;
	UINT32				irqEnable;
	UINT32				count;
	volatile void**		reg;
	UINT32**			freq;			//[chipMode][count]
	UINT32				rfTimerInit;
	UINT32				intrEnable;
	UINT32				intrClear;
	UINT32				vsyncIntr;
}bus_ctrl_t;

typedef struct	{
	volatile void*		chipReg;
	UINT32				chipMode;
	bus_ctrl_t			bus;
	pmt_ops_t			func;
} 
pmt_ctrl_t;

/*=========================================================================================*
| Function Prototype
*==========================================================================================*/
int pmt_module_init(void);
void pmt_module_exit(void);
void signal_send(void);

int pmt_open(struct inode *i_psInode, struct file *i_psFilePtr); 
void pmt_start(void);
void pmt_stop(void);
void pmt_end(void);
static long pmt_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long pmt_compat_ioctl( struct file* filp, unsigned int cmd, unsigned long arg);
#endif

static int MyFasync(int fd, struct file *filp, int mode);	


void pmt_init_config(UINT32 *data);
void pmt_init_tbl(REG_LIST_T* addr_tbl, REG_MULTIPLE_T* value_tbl, REG_MULTIPLE_T* addr, UINT32 nValue);
void pmt_read(REG_LIST_T* addr, REG_MULTIPLE_T* data);
void pmt_write_reg(UINT32 *data, UINT32 nValue);

static irqreturn_t pmt_irq(int irq, void *dev);

/*==========================================================================================*
| Global variables																			   
*==========================================================================================*/
pmt_ops_t pmt_func = 
{
	.init_config = pmt_init_config,
	.init_tbl = pmt_init_tbl,
	.start = pmt_start,
	.stop = pmt_stop,
	.read = pmt_read,
	.write_reg = pmt_write_reg,
	.end = pmt_end,
};

struct file_operations pmt_fops = 
{
	.open = pmt_open,
	.unlocked_ioctl = pmt_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = pmt_compat_ioctl,
#endif
	.fasync = MyFasync,
	.release = NULL,
	.mmap	= NULL,
};

static pmt_ctrl_t pmt_ctrl;
static struct fasync_struct *async_queue;


static REG_LIST_T addrIP;
static REG_MULTIPLE_T dataIP;

static REG_LIST_T addrReg;
static REG_MULTIPLE_T dataReg;

/*=========================================================================================*
| Function Definitions																			   
*==========================================================================================*/

int pmt_module_init(void) 
{
	int ret = RET_ERROR;

	/* Registering device */
	ret	= register_chrdev(PMT_MAJOR_NUM, PMT_DEV_NAME, &pmt_fops);
	if (ret < 0) 
	{
		printk("<1>%s: cannot obtain major number %d\n", PMT_MODULE_NAME, ret);
		return ret;
	}
	else
	{
		ret = PMT_MAJOR_NUM;
		printk("<1>%s: Major number %d assigned\n", PMT_MODULE_NAME, ret);
	}
	printk("\n\n\n\nINFO(pmt_module_init)-  Inserting module:%s\n\n\n\n", PMT_MODULE_NAME);

	/* create perfmon class */
    
	{
        static struct class* class = NULL;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
        class = class_create(PMT_MODULE_NAME);
#else
        class = class_create(THIS_MODULE, PMT_MODULE_NAME);
#endif
        device_create (class, NULL, MKDEV(PMT_MAJOR_NUM,0), NULL, PMT_MODULE_NAME);
    }
	
	return 0;
}

void pmt_module_exit(void)
{
	unregister_chrdev(PMT_MAJOR_NUM, PMT_DEV_NAME);
}

module_init(pmt_module_init);
module_exit(pmt_module_exit);

void signal_send(void)
{
	kill_fasync(&async_queue, SIGIO, POLL_IN);
}
static int MyFasync(int fd, struct file *filp, int mode)
{
	return fasync_helper(fd,filp,mode,&async_queue);
}

/*
; file operation function
*/
int pmt_open(struct inode *i_psInode, struct file *i_psFilePtr) 
{
	PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

	pmt_ctrl.func = pmt_func;
	return 0;
}

void pmt_init_config(UINT32 *data)
{
	//data_index[0] = maxPacketSize
	//data_index[1] = chipID
	//data_index[2] = chipReg
	int i, j, data_index = 3;
	PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

	//Init Variable
	pmt_end();
	
	pmt_ctrl.bus.irq = data[data_index++];
	pmt_ctrl.bus.irqEnable = 0;
	pmt_ctrl.bus.count = data[data_index++];

	pmt_ctrl.bus.reg = (volatile void**)vmalloc(sizeof(volatile void*) * pmt_ctrl.bus.count);
	PMT_CHECK_CODE(pmt_ctrl.bus.reg==NULL, return, "out of memory\n");
	for (i = 0; i < pmt_ctrl.bus.count; i++)
	{
		pmt_ctrl.bus.reg[i] = (volatile void*)ioremap((ULONG)data[data_index++], 0x200);
		PMT_CHECK_CODE(pmt_ctrl.bus.reg[i]==NULL, return, "ioremap failed\n");
	}

	//2 : FPGA/ASIC
	pmt_ctrl.bus.freq = (UINT32**)vmalloc(sizeof(UINT32*) * 2);
	PMT_CHECK_CODE(pmt_ctrl.bus.freq==NULL, return, "out of memory\n");
	for (i = 0; i < 2; i++)
	{
		pmt_ctrl.bus.freq[i] = (UINT32*)vmalloc(sizeof(UINT32) * pmt_ctrl.bus.count);
		PMT_CHECK_CODE(pmt_ctrl.bus.freq[i]==NULL, return, "out of memory\n");

		for (j = 0; j < pmt_ctrl.bus.count; j++)
		{
			pmt_ctrl.bus.freq[i][j] = data[data_index++];
		}
	}

	pmt_ctrl.bus.rfTimerInit = data[data_index++];
	pmt_ctrl.bus.intrEnable = data[data_index++];
	pmt_ctrl.bus.intrClear = data[data_index++];
	pmt_ctrl.bus.vsyncIntr = data[data_index++];

	if (request_irq(pmt_ctrl.bus.irq, pmt_irq, IRQF_SHARED | IRQF_TRIGGER_HIGH, "BUS", (void*)&pmt_ctrl))
		printk("[BUS_PMT] request_irq LBUS in %s is failed\n", __F__);
	else
	{
		disable_irq(pmt_ctrl.bus.irq);
		PMT_REG_WR(pmt_ctrl.bus.reg[LBUS_IDX] + pmt_ctrl.bus.intrEnable, 0x1);
	}
}

void pmt_init_tbl(REG_LIST_T* addr_tbl, REG_MULTIPLE_T* value_tbl, REG_MULTIPLE_T* addr, UINT32 nValue)
{
	int i;
	PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

	addr_tbl->nValue = nValue;
	addr_tbl->value	= (volatile void**)vmalloc(sizeof(volatile void*) * nValue);
	PMT_CHECK_CODE(addr_tbl->value==NULL, return, "out of memory\n");

	value_tbl->nValue = nValue;
	value_tbl->value = (UINT32 *)vmalloc(sizeof(UINT32) * nValue);
	PMT_CHECK_CODE(value_tbl->value==NULL, return, "out of memory\n");

	for(i=0; i<addr_tbl->nValue; i++)
	{
		addr_tbl->value[i] = (volatile void*)ioremap((unsigned long)addr->value[i], 4);
		PMT_CHECK_CODE(addr_tbl->value[i]==NULL, return, "ioremap for i[%d] 0x%08x failed\n", i, addr->value[i]);
	}
}

void pmt_read(REG_LIST_T* addr, REG_MULTIPLE_T* data)
{
    int i;
    PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

    for(i=0; i<addr->nValue; i++)
    {
		data->value[i] = PMT_REG_RD(addr->value[i]);
		//printk("reg(0x%08x) -> %08x\n", addr->value[i], data->value[i]);
    }
}

void pmt_write_reg(UINT32 *data, UINT32 nValue)
{
	int i;
	volatile void* addr_reg;

	for(i = 0; i < nValue; i += 2)
	{
		//Address
		addr_reg = (volatile void*)ioremap(*data++, 4);
		PMT_CHECK_CODE(addr_reg==NULL, return, "ioremap failed\n");
	
		//Data
		PMT_REG_WR(addr_reg, *data++);

		if (addr_reg)
			iounmap(addr_reg);
	}
}

static irqreturn_t pmt_irq(int irq, void *dev)
{
	PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

	PMT_REG_WR(pmt_ctrl.bus.reg[LBUS_IDX] + pmt_ctrl.bus.intrClear, 0x1);

	if (pmt_ctrl.bus.irqEnable == 1)
		signal_send();
	return IRQ_HANDLED;
}

void pmt_start(void)
{
	PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

	enable_irq(pmt_ctrl.bus.irq);
	pmt_ctrl.bus.irqEnable = 1;
}

void pmt_stop(void)
{
	PMT_DEBUG("[BUS_PMT] ______________________ %s ______________________\n", __F__);

	disable_irq(pmt_ctrl.bus.irq);
	pmt_ctrl.bus.irqEnable = 0;
}

void pmt_end(void)
{
	int i;

	PMT_DEBUG(" [BUS_PMT] ______________________ %s ______________________\n", __F__);

	if (pmt_ctrl.bus.irq)
	{
		free_irq(pmt_ctrl.bus.irq,(void*)&pmt_ctrl);
		PMT_REG_WR(pmt_ctrl.bus.reg[LBUS_IDX] + pmt_ctrl.bus.intrEnable, 0x0);
		pmt_ctrl.bus.irqEnable = 0;
	}
	pmt_ctrl.bus.irq = 0;

	if (pmt_ctrl.bus.reg)
	{
		for (i = 0; i < pmt_ctrl.bus.count; i++)
		{
			if (pmt_ctrl.bus.reg[i])
				iounmap(pmt_ctrl.bus.reg[i]);
		}
		vfree(pmt_ctrl.bus.reg);
	}
	pmt_ctrl.bus.reg = 0;

	if (pmt_ctrl.bus.freq)
	{
		for (i = 0; i < 2; i++)
		{
			if (pmt_ctrl.bus.freq[i])
				vfree(pmt_ctrl.bus.freq[i]);
		}
		vfree(pmt_ctrl.bus.freq);
	}
	pmt_ctrl.bus.freq = 0;

	if (pmt_ctrl.chipReg)
		iounmap(pmt_ctrl.chipReg);
	pmt_ctrl.chipReg = 0;
}

#ifdef CONFIG_COMPAT
static long pmt_compat_ioctl (struct file* filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case IOCTL_PMT_INIT_CONFIG:
		case IOCTL_PMT_INIT_TBL:
		case IOCTL_PMT_WRITE_REG:
		case IOCTL_PMT_FAST_START:
		case IOCTL_PMT_FAST_STOP:
		{
			REG_MULTIPLE_T arg_buf;

			PMT_DEBUG("[BUS_PMT] compat_ioctl pointer pre-processing..\n");

			PMT_CHECK_CODE(copy_from_user((void *)&arg_buf, (void __user *)arg, sizeof(REG_MULTIPLE_T)),
					return -EFAULT, "copy_from_user error\n");

			arg_buf.value = (UINT32*)(uintptr_t)arg_buf.compat_Data;

			PMT_CHECK_CODE(copy_to_user((void __user *)arg, (void *)&arg_buf, sizeof(REG_MULTIPLE_T)),
					return -EFAULT, "copy_to_user error\n");
		}
		break;
		default:
		{
			/* do nothing */
		}
		break;
	}

	return pmt_ioctl(filp, cmd, arg);
}
#endif

static long pmt_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int i = 0;
	UINT32 nValue;
	UINT32 packetCmd;
	UINT32 *buf;
	PMT_DEBUG("ioctl : cmd 0x%08x, cmd_idx %d\n", cmd, (int)_IOC_NR(cmd));

	switch(cmd)
	{
		case IOCTL_PMT_INIT_CONFIG:
			{
				REG_MULTIPLE_T reg;

				PMT_CHECK_CODE(copy_from_user((void *)&reg, (void __user *)arg, sizeof(REG_MULTIPLE_T)),
						return -EFAULT, "copy_from_user error\n");

				nValue = reg.nValue;
				buf = (UINT32*)vmalloc(sizeof(UINT32)*nValue);
				PMT_CHECK_CODE(buf==NULL, return -EFAULT, "out of memory\n");

				PMT_CHECK_CODE(copy_from_user(buf, (void __user *)reg.value, sizeof(UINT32) * nValue),
						return -EFAULT, "copy_from_user error\n");

				reg.value = (UINT32 *)vmalloc(sizeof(UINT32)*nValue);
				PMT_CHECK_CODE(reg.value==NULL, return -EFAULT, "out of memory\n");

				memcpy(reg.value, buf,sizeof(UINT32)*nValue);

				pmt_ctrl.func.init_config(reg.value);
				
				vfree(reg.value);
				vfree(buf);
			}
			break;
		case IOCTL_PMT_CHIP_ID:
			{
				UINT32 data;
				PMT_CHECK_CODE(copy_from_user((void *)&data, (void *)arg, sizeof(UINT32)),
						return -EFAULT, "copy_from_user error\n");

				pmt_ctrl.chipReg = (volatile void*)ioremap((ULONG)data, 4);
				PMT_CHECK_CODE(pmt_ctrl.chipReg==NULL, return -EFAULT, "ioremap failed\n");

				data = PMT_REG_RD(pmt_ctrl.chipReg);
			
				if((data & 0xF0000000) == 0xF0000000)
					pmt_ctrl.chipMode = FPGA_IDX;
				else
					pmt_ctrl.chipMode = ASIC_IDX;

				PMT_CHECK_CODE(copy_to_user((void __user*)arg, (void *)&data, sizeof(UINT32)),
						return -EFAULT, "copy_to_user error\n");
			}
			break;
		case IOCTL_PMT_INIT_TBL:
			{
				REG_MULTIPLE_T init;
				PMT_CHECK_CODE(copy_from_user((void *)&init, (void __user *)arg, sizeof(REG_MULTIPLE_T)),
						return -EFAULT, "copy_from_user error\n");

				nValue 		= init.nValue;
				packetCmd	= init.cmd;
				buf			= (UINT32*)vmalloc((sizeof(UINT32)*nValue));
				PMT_CHECK_CODE(buf==NULL, return -EFAULT, "out of memory\n");

				PMT_CHECK_CODE(copy_from_user(buf, (void __user *)init.value, sizeof(UINT32)*init.nValue),
						return -EFAULT, "copy_from_user error\n");

				init.value = (UINT32*)vmalloc(sizeof(UINT32)*nValue);
				PMT_CHECK_CODE(init.value==NULL, return -EFAULT, "out of memory\n");

				memcpy(init.value, buf,sizeof(UINT32)*nValue);

				if(packetCmd == CMD_INIT_ADDR)
				{
					pmt_ctrl.func.init_tbl(&addrIP, &dataIP, &init, nValue);
				}
				else //CMD_READ_REG
				{
					pmt_ctrl.func.init_tbl(&addrReg, &dataReg, &init, nValue);
					vfree(init.value);
				}
				vfree(buf);
			}
			break;
		case IOCTL_PMT_READ:
			{
				pmt_ctrl.func.read(&addrIP, &dataIP);

				PMT_CHECK_CODE(copy_to_user((void __user*)arg, (void*)dataIP.value, sizeof(UINT32)*dataIP.nValue),
						return -EFAULT, "copy_to_user error\n");
			}
			break;
		case IOCTL_PMT_READ_REG:
			{
				pmt_ctrl.func.read(&addrReg, &dataReg);
	
				PMT_CHECK_CODE(copy_to_user((void __user*)arg, (void*)dataReg.value, sizeof(UINT32)* dataReg.nValue),
						return -EFAULT, "copy_to_user error\n");
	
				for(i = 0; i < addrReg.nValue; i++)
				{
					if(addrReg.value[i])
						iounmap(addrReg.value[i]);
				}
	
				vfree(addrReg.value);
				vfree(dataReg.value);
			}
			break;
		case IOCTL_PMT_WRITE_REG:
			{
				REG_MULTIPLE_T reg;

				PMT_CHECK_CODE(copy_from_user((void *)&reg, (void __user *)arg, sizeof(REG_MULTIPLE_T)),
						return -EFAULT, "copy_from_user error\n");

				nValue = reg.nValue;
				buf = (UINT32*)vmalloc(sizeof(UINT32)*nValue);
				PMT_CHECK_CODE(buf==NULL, return -EFAULT, "out of memory\n");

				PMT_CHECK_CODE(copy_from_user(buf, (void __user *)reg.value, sizeof(UINT32) * nValue),
						return -EFAULT, "copy_from_user error\n");

				reg.value = (UINT32 *)vmalloc(sizeof(UINT32)*nValue);
				PMT_CHECK_CODE(reg.value==NULL, return -EFAULT, "out of memory\n");
				memcpy(reg.value, buf,sizeof(UINT32)*nValue);

				pmt_ctrl.func.write_reg(reg.value, nValue);

				vfree(reg.value);
				vfree(buf);
			}
			break;
		case IOCTL_PMT_DEBUG_PRINT:
			{
				UINT32 index = 0;

				PMT_CHECK_CODE(copy_from_user((void *)&index, (void __user *)arg, sizeof(UINT32)),
						return -EFAULT, "copy_from_user error\n");
				if (index == 0)
					printk("[BUS_PMT] operation : INIT_POST_CMD\n");
				else
					printk("[BUS_PMT] operation : [0x%02X] - OK\n", index);
			}
			break;
		case IOCTL_PMT_START:
			{
				pmt_ctrl.func.start();
			}
			break;
		case IOCTL_PMT_STOP:
			{
				pmt_ctrl.func.stop();
			}
			break;
		case IOCTL_PMT_END:
			{
				pmt_ctrl.func.end();
			}
			break;
		case IOCTL_PMT_EXIT:
			{
			}
			break;

		default:
		{
			PMT_ERROR("[BUS_PMT] cmd error : unknown cmd !!\n");
			return -EFAULT;
		}
		break;
	}

	return 0;
}
#endif /*_PERF_MON_TARGET_DRV_C_*/
