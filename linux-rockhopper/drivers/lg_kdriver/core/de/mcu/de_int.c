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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.02.17
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*------------------------------------------------------------------------------
 *   Control Constants
 *----------------------------------------------------------------------------*/
//#define USE_IPC_FOR_MCU1

/*------------------------------------------------------------------------------
 *   File Inclusions
 *----------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>

#include "base_types.h"
#include "os_util.h"

#include "de_ver_def.h"

#include "de_kapi.h"
#include "de_def.h"

#include "de_int_def.h"
#include "de_ipc_def.h"
#include "de_ipc.h"
#include "de_int.h"
#include "hal/de_hal_def.h"
#include "hal/ipc_phys_hal.h"
#include "de_hal.h"

#ifdef INCLUDE_KDRV_BE
#include "v4l2_vbe.h"
#endif

/*------------------------------------------------------------------------------
 *   Constant Definitions
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *   Macro Definitions
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *   Type Definitions
 *----------------------------------------------------------------------------*/
typedef struct {
	int (*cb_func)(void);
} DE_VSYNC_CB;
DE_VSYNC_CB vsync_cb;
DE_VSYNC_CB srcsync_cb;
DE_VSYNC_CB seamless_cb;

/*------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *   External Variables
 *----------------------------------------------------------------------------*/
extern struct workqueue_struct *module_highpri_wq[MODULE_MAX];
extern MODULE_WORKLIST_T 	module_work_list[MODULE_MAX];
extern spinlock_t gModSpin_lock[MODULE_MAX];

/*------------------------------------------------------------------------------
 *   global Functions
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *   global Variables
 *----------------------------------------------------------------------------*/
// static unsigned int t_sec_prv,t_msec_prv;

/*------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *----------------------------------------------------------------------------*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void VIDEO_CPU_VSYNC_Tasklet(struct tasklet_struct *temp);
static void VIDEO_CPU_SRCSYNC_Tasklet(struct tasklet_struct *temp);
// static void DE_SEAMLESS_Callback(struct tasklet_struct *temp);
static void VIDEO_CPU_OSYNC_Tasklet(struct tasklet_struct *temp);
static void VIDEO_CPU_CTOP_Tasklet(struct tasklet_struct *temp);	//mhlee, ctop ctrl by interrupt
#else
static void VIDEO_CPU_VSYNC_Tasklet(unsigned long temp);
static void VIDEO_CPU_SRCSYNC_Tasklet(unsigned long temp);
// static void DE_SEAMLESS_Callback(unsigned long temp);
static void VIDEO_CPU_OSYNC_Tasklet(unsigned long temp);
static void VIDEO_CPU_CTOP_Tasklet(unsigned long temp);	//mhlee, ctop ctrl by interrupt
#endif

static void DE_IPC_Handler(void);
static void DE_VSYNC_Handler(void);
static irqreturn_t DE_IPC_interrupt(int irq,void *dev_id);
static irqreturn_t DE_IPC_interrupt2(int irq,void *dev_id);
static irqreturn_t DE_IPC_interrupt3(int irq,void *dev_id);

#ifdef USE_IPC_FOR_MCU1
static irqreturn_t BE_IPC_interrupt(int irq,void *dev_id);
#endif
static irqreturn_t DE_VSYNC_interrupt(int irq,void *dev_id);
static void check_mute(void);

/*------------------------------------------------------------------------------
 *   Static Variables
 *----------------------------------------------------------------------------*/
// mcu 0

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static DECLARE_TASKLET(Video_WDG_tasklet, VIDEO_CPU_WDG_FROM_MCU);
static DECLARE_TASKLET(Video_IPC_tasklet, VIDEO_CPU_ISR_FROM_MCU);
static DECLARE_TASKLET(Video_DMA_tasklet, VIDEO_CPU_DMA_FROM_MCU);
static DECLARE_TASKLET(Video_JPG_tasklet, VIDEO_CPU_JPG_FROM_MCU);
static DECLARE_TASKLET(Video_USB_tasklet, VIDEO_CPU_USB_FROM_MCU);
static DECLARE_TASKLET(Video_WEL_tasklet, VIDEO_CPU_WEL_FROM_MCU);
static DECLARE_TASKLET(Video_WER_tasklet, VIDEO_CPU_WER_FROM_MCU);
// static DECLARE_TASKLET(Video_AMZ_tasklet, DE_SEAMLESS_Callback);
static DECLARE_TASKLET(Video_VSYNC_tasklet, VIDEO_CPU_VSYNC_Tasklet);
static DECLARE_TASKLET(Video_SRCSYNC_tasklet, VIDEO_CPU_SRCSYNC_Tasklet);
static DECLARE_TASKLET(Video_DHDR_tasklet, VIDEO_CPU_DHDR_Tasklet);
static DECLARE_TASKLET(Video_DELAY_tasklet, VIDEO_CPU_VIDEO_DELAY_FROM_MCU);
static DECLARE_TASKLET(Video_GPS_tasklet, VIDEO_CPU_GPS_Tasklet);
static DECLARE_TASKLET(Video_MUTE_tasklet, VIDEO_CPU_MUTE_Tasklet);
static DECLARE_TASKLET(Video_OSYNC_tasklet, VIDEO_CPU_OSYNC_Tasklet);
static DECLARE_TASKLET(Video_CTOP_tasklet, VIDEO_CPU_CTOP_Tasklet);	//mhlee, ctop ctrl by interrupt
#else
static DECLARE_TASKLET(Video_WDG_tasklet, VIDEO_CPU_WDG_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_IPC_tasklet, VIDEO_CPU_ISR_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_DMA_tasklet, VIDEO_CPU_DMA_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_JPG_tasklet, VIDEO_CPU_JPG_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_USB_tasklet, VIDEO_CPU_USB_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_WEL_tasklet, VIDEO_CPU_WEL_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_WER_tasklet, VIDEO_CPU_WER_FROM_MCU,  0UL);
// static DECLARE_TASKLET(Video_AMZ_tasklet, DE_SEAMLESS_Callback,  0UL);
static DECLARE_TASKLET(Video_VSYNC_tasklet, VIDEO_CPU_VSYNC_Tasklet,  0UL);
static DECLARE_TASKLET(Video_SRCSYNC_tasklet, VIDEO_CPU_SRCSYNC_Tasklet,  0UL);
static DECLARE_TASKLET(Video_DHDR_tasklet, VIDEO_CPU_DHDR_Tasklet,  0UL);
static DECLARE_TASKLET(Video_DELAY_tasklet, VIDEO_CPU_VIDEO_DELAY_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_GPS_tasklet, VIDEO_CPU_GPS_Tasklet,  0UL);
static DECLARE_TASKLET(Video_MUTE_tasklet, VIDEO_CPU_MUTE_Tasklet,  0UL);
static DECLARE_TASKLET(Video_OSYNC_tasklet, VIDEO_CPU_OSYNC_Tasklet,  0UL);
static DECLARE_TASKLET(Video_CTOP_tasklet, VIDEO_CPU_CTOP_Tasklet,  0UL);	//mhlee, ctop ctrl by interrupt
#endif

// mcu 1
#ifdef USE_IPC_FOR_MCU1
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static DECLARE_TASKLET(Video_WDG_1_tasklet, VIDEO_CPU_WDG_FROM_MCU_1);
static DECLARE_TASKLET(Video_IPC_1_tasklet, VIDEO_CPU_ISR_FROM_MCU_1);
static DECLARE_TASKLET(Video_ACK_1_tasklet, VIDEO_CPU_ACK_FROM_MCU_1);
#else
static DECLARE_TASKLET(Video_WDG_1_tasklet, VIDEO_CPU_WDG_FROM_MCU_1,  0UL);
static DECLARE_TASKLET(Video_IPC_1_tasklet, VIDEO_CPU_ISR_FROM_MCU_1,  0UL);
static DECLARE_TASKLET(Video_ACK_1_tasklet, VIDEO_CPU_ACK_FROM_MCU_1,  0UL);
#endif
#endif

static DECLARE_WAIT_QUEUE_HEAD(wqVsync);
static DECLARE_WAIT_QUEUE_HEAD(wqVsync1);
static DECLARE_WAIT_QUEUE_HEAD(wqVsync2);
static DECLARE_WAIT_QUEUE_HEAD(wqVsync3);

static int de_vsync_event_wakeup[4] = { 0 };
static int de_int_stop_handler = 0;

/*==============================================================================
 *   Implementation Group
 *============================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt request
 */
int DE_INT_Init(void)
{
	int ret = RET_OK;
	int i;
	int num_de_ipc_irq = 0, num_de_irq = 0;
	int num_de_ipc_irq_ex[2] = {0,0};

	vsync_cb.cb_func = NULL;
	srcsync_cb.cb_func = NULL;
	seamless_cb.cb_func = NULL;

	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) )
		return RET_OK;

	for(i=SOC_MCU_0;i<SOC_MCU_MAX;i++)
	{
		if(ipc_phys_hal_GetIrqNum(i, &num_de_ipc_irq, &num_de_irq)) {
			DE_ERROR("get irq num in %s is failed\n", __FUNCTION__);
			return -1;
		}
		switch(i)
		{
			case SOC_MCU_0:
			default:
				if (request_irq(num_de_ipc_irq,             \
							(irq_handler_t)DE_IPC_interrupt,\
							0,"DE2IPC", NULL)) {
					DE_ERROR("request_irq in %s is failed\n", __FUNCTION__);
					return -1;
				}
				if (request_irq(num_de_irq,                   \
							(irq_handler_t)DE_VSYNC_interrupt,\
							0,"DE2VSYNC", NULL)) {
					DE_ERROR("request_irq in %s is failed\n", __FUNCTION__);
					return -1;
				}
				if (RET_OK == ipc_phys_hal_GetIrqNum_ex(num_de_ipc_irq_ex,2)) {
					if (num_de_ipc_irq_ex[0]) {
						if (request_irq(num_de_ipc_irq_ex[0],             \
									(irq_handler_t)DE_IPC_interrupt2,\
									0,"DE2IPC2", NULL)) {
							DE_ERROR("request_irq in %s is failed\n", __FUNCTION__);
							return -1;
						}
					}
					if (num_de_ipc_irq_ex[1]) {
						if (request_irq(num_de_ipc_irq_ex[1],             \
									(irq_handler_t)DE_IPC_interrupt3,\
									0,"DE2IPC3", NULL)) {
							DE_ERROR("request_irq in %s is failed\n", __FUNCTION__);
							return -1;
						}
					}
				}
				break;
			case SOC_MCU_1:
#ifdef USE_IPC_FOR_MCU1
				if (request_irq(num_de_ipc_irq,             \
							(irq_handler_t)BE_IPC_interrupt,\
							0,"BE2IPC", NULL)) {
					DE_ERROR("request_irq in %s is failed\n", __FUNCTION__);
					return -1;
				}
#else
				DE_NOTI("Currently not supported mcu[%d]\n", i);
#endif
				break;
		}

	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt free
 */
int DE_INT_Cleanup(void)
{
	int ret = RET_OK;
	int num_de_irq = 0, num_de_ipc_irq = 0;

	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) )
		return RET_OK;

	if(ipc_phys_hal_GetIrqNum(0, &num_de_ipc_irq, &num_de_irq)) {
		DE_ERROR("get irq num in %s is failed\n", __FUNCTION__);
		return -1;
	}

	free_irq(num_de_ipc_irq, NULL);
	free_irq(num_de_irq, NULL);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief register call-back function for vsync
 */
void DE_VSYNC_Register(char *str, int (*func)(void))
{
	int intr = 0;
	if(!strcmp(str, "vsync"))
		intr = 0;
	else if(!strcmp(str, "seamless"))
		intr = 1;
	else if(!strcmp(str, "srcsync"))
		intr = 2;
	else
		intr = -1;
	switch(intr)
	{
		case 0:
			vsync_cb.cb_func = func;
			break;
		case 1:
			seamless_cb.cb_func = func;
			break;
		case 2:
			srcsync_cb.cb_func = func;
			break;
		default:
			printk("%s : undefined handler!\n", __F__);
			break;
	}
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize vsync
 */
int DE_VSYNC_Init(void)
{
	int ret = RET_OK;
	ret = ipc_phys_hal_InitInterrupt(0, TRUE);
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief free vsync
 */
int DE_VSYNC_Free(void)
{
	int ret = RET_OK;
	ret = ipc_phys_hal_InitInterrupt(0, FALSE);
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief wait vsync with count-param
 */
int DE_VSYNC_WaitTimeOut(unsigned int wid, int timeout)
{
	if(wid > 3) return -1;
	switch(wid) {
		case 0:
		de_vsync_event_wakeup[0] = -1;
		wait_event_interruptible_timeout(wqVsync,              \
										!de_vsync_event_wakeup[0],\
										(long)timeout);
		break;
		case 1:
			de_vsync_event_wakeup[1] = -1;
			wait_event_interruptible_timeout(wqVsync1,			   \
											!de_vsync_event_wakeup[1],\
										(long)timeout);
		break;
		case 2:
			de_vsync_event_wakeup[2] = -1;
			wait_event_interruptible_timeout(wqVsync2,			   \
											!de_vsync_event_wakeup[2],\
											(long)timeout);
		break;
		case 3:
		default:
			de_vsync_event_wakeup[3] = -1;
			wait_event_interruptible_timeout(wqVsync3,			   \
											!de_vsync_event_wakeup[3],\
											(long)timeout);
		break;
	}
	if(de_vsync_event_wakeup[wid] == -1) return -1;
	return RET_OK;
}

/* 1:stop, else:normal */
int DE_INT_StopHandler(int flag)
{
	de_int_stop_handler = flag;
	return 0;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt handler which is comming from MCU
 */
extern void V4l2_gps_thread(struct work_struct *gps_work);
static void DE_IPC_Handler(void)
{
	UINT32 ipcStatus = 0;
	MODULE_WORKLIST_T *workList = NULL;
#if 0
	static int intr = 0,max_lat=500,avg_lat=0;
	struct timespec ts;
	unsigned int t_sec,t_msec,time_diff;
	ktime_t t;
#endif	
	unsigned long flags;

	ipc_phys_hal_GetIntrStatus(0, VIDEO_IPC_CPU, &ipcStatus);

	if (GET_CM(ipcStatus, VIDEO_IPC_INTERRUPT_ARM_MASK)) {
		DE_SYNC("VIDEO_IPC_CPU\n");
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_IPC_CPU, &ipcStatus);
		tasklet_schedule(&Video_IPC_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_DMA_INTERRUPT_ARM_MASK)) {
		DE_SYNC("VIDEO_DMA_CPU\n");
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_DMA_CPU, &ipcStatus);
		tasklet_schedule(&Video_DMA_tasklet);
	}

	if (de_int_stop_handler == 1) {
		if (GET_CM(ipcStatus, VIDEO_WDG_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearWDGStatus(0);
		}
		if (GET_CM(ipcStatus, VIDEO_WDG_MCU1_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearWDGStatus(1);
			DE_WARN("VIDEO_WDG_MCU1_INTERRUPT_ARM_MASK\n");
			//panic("WDG_MCU1_INTERRUPT %s:%d\n", __func__, __LINE__);
		}
		if (GET_CM(ipcStatus, VIDEO_JPG_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_JPG_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_USB_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_USB_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_WEL_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_WEL_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_WER_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_WER_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_AMZ_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_AMZ_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_DHDR_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_DHDR_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_DELAY_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_DELAY_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_GPS_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_GPS_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_GPW_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_GPW_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_LED_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_LED_CPU, &ipcStatus);
		}
		if (GET_CM(ipcStatus, VIDEO_CTOP_INTERRUPT_ARM_MASK)) {		//mhlee, ctop ctrl by interrupt
			ipc_phys_hal_ClearIPCStatus(0, VIDEO_CTOP_CPU, &ipcStatus);
		}
		/* cleanup unused interrupt bits */
		if (GET_BM(ipcStatus, VIDEO_UNUSED_INTERRUPT_ARM_MASK)) {
			ipc_phys_hal_cleanup_ipc_status(0);
		}
		return;
	}

	if (GET_CM(ipcStatus, VIDEO_WDG_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearWDGStatus(0);
		tasklet_schedule(&Video_WDG_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_WDG_MCU1_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearWDGStatus(1);
		DE_WARN("VIDEO_WDG_MCU1_INTERRUPT_ARM_MASK\n");
		//panic("WDG_MCU1_INTERRUPT %s:%d\n", __func__, __LINE__);
	}
	if (GET_CM(ipcStatus, VIDEO_JPG_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_JPG_CPU, &ipcStatus);
		tasklet_schedule(&Video_JPG_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_USB_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_USB_CPU, &ipcStatus);
		tasklet_schedule(&Video_USB_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_WEL_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_WEL_CPU, &ipcStatus);
		tasklet_schedule(&Video_WEL_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_WER_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_WER_CPU, &ipcStatus);
		if(lx_chip_rev() >= LX_CHIP_REV(M17,A0)){
			tasklet_schedule(&Video_VSYNC_tasklet);   // using interrupt bit'24 for vsync of M17 PQE
			check_mute();
		}
		else
			tasklet_schedule(&Video_WER_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_AMZ_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_AMZ_CPU, &ipcStatus);
		//tasklet_schedule(&Video_AMZ_tasklet);
		tasklet_schedule(&Video_GPS_tasklet);
	}	
	if (GET_CM(ipcStatus, VIDEO_DHDR_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_DHDR_CPU, &ipcStatus);
		tasklet_schedule(&Video_DHDR_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_DELAY_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_DELAY_CPU, &ipcStatus);
		tasklet_schedule(&Video_DELAY_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_GPW_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_GPW_CPU, &ipcStatus);
		tasklet_schedule(&Video_GPS_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_LED_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_LED_CPU, &ipcStatus);
		tasklet_schedule(&Video_OSYNC_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_GPS_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_GPS_CPU, &ipcStatus);
		if( LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) { // m23, o24, ...
			tasklet_schedule(&Video_GPS_tasklet); // for gps dma write-done
		}
		#if 0//ndef WQ_IMPL(fix coverity)

		#else
#if 0
		t = ktime_get_real();
		ts = ktime_to_timespec(t);
		t_sec = ts.tv_sec;
		t_msec= ts.tv_nsec/1000000;
		time_diff= (t_sec*1000+t_msec)-(t_sec_prv*1000+t_msec_prv);
		t_sec_prv = t_sec;
		t_msec_prv= t_msec;
		if(intr > 1)
			max_lat = time_diff>max_lat?time_diff:max_lat;
		DE_NOTI("INTR:: %d TimeDiff::%d MaxLatency::%d",intr++,time_diff,max_lat);
#endif
		workList = &module_work_list[MODULE_GPS];

		spin_lock_irqsave(&gModSpin_lock[MODULE_GPS],flags);
		while(workList){
			if(workList->wrk){
#if 0
				if(queue_work(module_highpri_wq[MODULE_GPS],workList->wrk)==false)
					DE_NOTI("INTR:: Work [0x%x] is not scheduled",workList->wrk);
#else
				queue_work(module_highpri_wq[MODULE_GPS],workList->wrk);
				//V4l2_gps_thread(workList->wrk);
#endif
			}
			workList = workList->next;
		}
		spin_unlock_irqrestore(&gModSpin_lock[MODULE_GPS],flags);
		#endif
	}
	if (GET_CM(ipcStatus, VIDEO_CTOP_INTERRUPT_ARM_MASK)) {		//mhlee, ctop ctrl by interrupt
		ipc_phys_hal_ClearIPCStatus(0, VIDEO_CTOP_CPU, &ipcStatus);
		tasklet_schedule(&Video_CTOP_tasklet);
	}
	/* cleanup unused interrupt bits */
	if (GET_BM(ipcStatus, VIDEO_UNUSED_INTERRUPT_ARM_MASK)) {
		ipc_phys_hal_cleanup_ipc_status(0);
	}
}
#ifdef USE_ND1_INTR_FOR_IPC
static void DE_IPC_HandlerClear(void)
{
	UINT32 ipcStatus;
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_IPC_CPU, &ipcStatus);
	ipc_phys_hal_ClearWDGStatus(0);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_DMA_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_JPG_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_USB_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_WEL_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_WER_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_DHDR_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_DELAY_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_AMZ_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_GPS_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_GPW_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_LED_CPU, &ipcStatus);
	ipc_phys_hal_ClearIPCStatus(0, VIDEO_CTOP_CPU, &ipcStatus);
}
#endif

#ifdef USE_IPC_FOR_MCU1
static void BE_IPC_Handler(void)
{
	int ret;
	UINT32 intrStatus;

	if (de_int_stop_handler == 1)	return;

	printk("%s : \n", __F__);

	ret = ipc_phys_hal_GetIntrStatus(1, VIDEO_INT_SWI, &intrStatus);
	if(intrStatus & MCU1_SWI_IPC)
	{	
		tasklet_schedule(&Video_IPC_1_tasklet);
	}
	if(intrStatus & MCU1_SWI_ACK)
	{
		tasklet_schedule(&Video_ACK_1_tasklet);
	}
	// clear interrupt
	if(intrStatus) ipc_phys_hal_ClearIPCStatus(1, VIDEO_INT_SWI, &intrStatus);

	ret = ipc_phys_hal_GetIntrStatus(1, VIDEO_INT_HWI, &intrStatus);

	if(intrStatus & (1 << MCU1_CPU_INT_WDG))
	{
		tasklet_schedule(&Video_WDG_1_tasklet);
	}
	if(intrStatus & (1 << MCU1_CPU_INT_DMA))
	{ }
	// clear interrupt
	if(intrStatus) ipc_phys_hal_ClearIPCStatus(1, VIDEO_INT_HWI, &intrStatus);
}
#endif

static void DE_VSYNC_Handler(void)
{
	if (de_int_stop_handler == 1)	return;

	do {
		if (!ipc_phys_hal_CheckIrq4Vsync(0)) break;
		tasklet_schedule(&Video_SRCSYNC_tasklet);
	} while (0);
}

#if 0
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void DE_SEAMLESS_Callback(struct tasklet_struct *temp)
#else
static void DE_SEAMLESS_Callback(unsigned long temp)
#endif
{
	if(seamless_cb.cb_func) seamless_cb.cb_func();
}
#endif

static void DE_VSYNC_Callback(BOOLEAN src_disp) /*src:0, disp:1 */
{
	if(!src_disp)
	{
		if(srcsync_cb.cb_func) srcsync_cb.cb_func();
	}
	else
	{
		if(vsync_cb.cb_func) vsync_cb.cb_func();
	}
}

LX_DE_VIDEO_DELAY_INFO_MEM_T gstParams = { 0 };
int DE_VSYNC_WakeUp(void)
{
	int i, ret, max_win=0;
	unsigned char intr_mask = 0, flag=0;
	LX_DE_VIDEO_DELAY_INFO_MEM_T stParams;

	ret = DE_HAL_GetVideoDelay(&stParams);
	if(ret < 0) return ret;

	if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
		max_win = 2;
	}
	else if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) ) {
		max_win = 4;
	}
	else
		max_win = 2;

	for(i=0;i<max_win;i++) {
		#if 0
		if((stParams.win[i].rect.w != gstParams.win[i].rect.w) \
			|| (stParams.win[i].rect.h != gstParams.win[i].rect.h) \
			|| (stParams.win[i].rect.x != gstParams.win[i].rect.x) \
			|| (stParams.win[i].rect.y != gstParams.win[i].rect.y)) {
			//intr_mask += (1 < i);
			intr_mask = 1;
		}
		#else
		if((stParams.win[i].rect.w != gstParams.win[i].rect.w)) {
			flag++;
		}
		if((stParams.win[i].rect.h != gstParams.win[i].rect.h)) {
			flag++;
		}
		if((stParams.win[i].rect.x != gstParams.win[i].rect.x)) {
			flag++;
		}
		if((stParams.win[i].rect.y != gstParams.win[i].rect.y)) {
			flag++;
		}
		if(flag) {
			intr_mask = intr_mask + (1 << i);
		}
		#endif
	}
	if(intr_mask)
	{
		DE_NOTI("update_win_ intr_mask = %x [%d,%d %dx%d] [%d,%d %dx%d] [%d,%d %dx%d] [%d,%d %dx%d] [%d,%d %dx%d] [%d,%d %dx%d]", intr_mask, \
			stParams.win[0].rect.x,stParams.win[0].rect.y,stParams.win[0].rect.w,stParams.win[0].rect.h, \
			gstParams.win[0].rect.x,gstParams.win[0].rect.y,gstParams.win[0].rect.w,gstParams.win[0].rect.h, \
			stParams.win[1].rect.x,stParams.win[1].rect.y,stParams.win[1].rect.w,stParams.win[1].rect.h, \
			gstParams.win[1].rect.x,gstParams.win[1].rect.y,gstParams.win[1].rect.w,gstParams.win[1].rect.h, \
			stParams.win[2].rect.x,stParams.win[2].rect.y,stParams.win[2].rect.w,stParams.win[2].rect.h, \
			gstParams.win[2].rect.x,gstParams.win[2].rect.y,gstParams.win[2].rect.w,gstParams.win[2].rect.h);
	}

	if(intr_mask & 1) {
		if (de_vsync_event_wakeup[0] < 0) de_vsync_event_wakeup[0]++;
		wake_up_interruptible(&wqVsync);
	}
	if(intr_mask & 2) {
		if (de_vsync_event_wakeup[1] < 0) de_vsync_event_wakeup[1]++;
		wake_up_interruptible(&wqVsync1);
	}
	if(intr_mask & 4) {
		if (de_vsync_event_wakeup[2] < 0) de_vsync_event_wakeup[2]++;
		wake_up_interruptible(&wqVsync2);
	}
	if(intr_mask & 8) {
		if (de_vsync_event_wakeup[3] < 0) de_vsync_event_wakeup[3]++;
		wake_up_interruptible(&wqVsync3);
	}

	memcpy(&gstParams, &stParams, sizeof(LX_DE_VIDEO_DELAY_INFO_MEM_T));
	
	return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void VIDEO_CPU_VSYNC_Tasklet(struct tasklet_struct *temp)
#else
static void VIDEO_CPU_VSYNC_Tasklet(unsigned long temp)
#endif
{
	DE_VSYNC_WakeUp();
	DE_VSYNC_Callback(1);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void VIDEO_CPU_SRCSYNC_Tasklet(struct tasklet_struct *temp)
#else
static void VIDEO_CPU_SRCSYNC_Tasklet(unsigned long temp)
#endif
{
	DE_VSYNC_Callback(0);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void VIDEO_CPU_OSYNC_Tasklet(struct tasklet_struct *temp)
#else
static void VIDEO_CPU_OSYNC_Tasklet(unsigned long temp)
#endif
{
#ifdef INCLUDE_KDRV_BE
	vbe_sync_handler();
#endif
}
//mhlee, ctop ctrl by interrupt
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void VIDEO_CPU_CTOP_Tasklet(struct tasklet_struct *temp)
#else
static void VIDEO_CPU_CTOP_Tasklet(unsigned long temp)
#endif
{
	ipc_phys_hal_CTOPIntr();
}

static irqreturn_t DE_IPC_interrupt2(int irq,void *dev_id)
{
	ipc_phys_hal_ClearIPCStatus2(0);
	DE_TRACE_23("ipc2\n");
	return IRQ_HANDLED;
}

static irqreturn_t DE_IPC_interrupt3(int irq,void *dev_id)
{
	ipc_phys_hal_ClearIPCStatus3(0);
	DE_TRACE_23("ipc3\n");
	return IRQ_HANDLED;
}

static irqreturn_t DE_IPC_interrupt(int irq,void *dev_id)
{
#ifdef USE_ND1_INTR_FOR_IPC
	if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
		DE_IPC_HandlerClear();
	}
	else
#endif
	{
	    DE_IPC_Handler();
	}
	return IRQ_HANDLED;
}

#ifdef USE_IPC_FOR_MCU1
static irqreturn_t BE_IPC_interrupt(int irq,void *dev_id)
{
    BE_IPC_Handler();

	return IRQ_HANDLED;
}
#endif

static irqreturn_t DE_VSYNC_interrupt(int irq,void *dev_id)
{
#ifdef USE_ND1_INTR_FOR_IPC
	if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
		DE_IPC_Handler();
	}
	else
#endif
	{
	    DE_VSYNC_Handler();
	}
	return IRQ_HANDLED;
}

static void check_mute(void)
{
	UINT32 i;
	static UINT32 mute1[4] = { 1 }, mute2[4] = { 1 };

	for(i=0;i<2;i++)
	{
		ipc_phys_hal_CheckMute(i, &mute1[i]);
		if(mute1[i] != mute2[i])
		{
			mute2[i] = mute1[i];
			// event posting
			tasklet_schedule(&Video_MUTE_tasklet);
		}
	}
}

/** @} */
