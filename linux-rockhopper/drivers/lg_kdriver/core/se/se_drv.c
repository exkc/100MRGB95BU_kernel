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
 *  main driver implementation for se device.
 *	se device will teach you how to make device driver with new platform.
 *
 *  author		stan.kim@lge.com
 *  version		1.0
 *  date		2012.05
 *  note		Additional information.
 *
 *  @addtogroup
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/rmap.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/dma-mapping.h>
#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <linux/io.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <uapi/linux/sched/types.h>
#endif

#include <linux/vmalloc.h>

#include <net/sock.h>

#include <asm/io.h>
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>

#include <linux/mman.h>
#include <linux/arm-smccc.h>

#include "ree_kdrv.h"
#include "se_drv_impl.h"

#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif

#include "dmabuf_importer.h"

static struct device *internal_dev;


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define SMC_THREAD_SCHED_FIFO_PRIORITY	92
#define SMC_THREAD_SCHED_NORMAL_PRIORITY	0

#define SE_TZ_SCHED_WAIT		100		// 100usec
#define SE_USE_YIELD_AS_WAIT	1

#define SE_WAIT					100		// 100usec
#define SE_WAIT_RETRY			50000	// Max : SE_DMA_WAIT_RETRY * SE_DMA_WAIT = 5sec
#define SE_WAIT_LOOP			0x1000000	// > DMA 10MBytes

#ifndef _SE_STANDALONE_

#define SE_USE_NET_LINK			0
#define SE_ACK_MSG_TIMEOUT		3000	// 3000msec
#else	// _SE_STANDALONE_
#define SE_USE_NET_LINK			0

#endif	// _SE_STANDALONE_

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef _SE_STANDALONE_

#define SE_ERROR(fmt, args...)	DBG_PRINT(_gSeInfo.debugFd, LX_LOGM_LEVEL_ERROR, fmt, ##args)
#define SE_WARN(fmt, args...)	DBG_PRINT(_gSeInfo.debugFd, LX_LOGM_LEVEL_WARNING, fmt, ##args)
#define SE_NOTI(fmt, args...)	DBG_PRINT(_gSeInfo.debugFd, LX_LOGM_LEVEL_NOTI, fmt, ##args)
#define SE_INFO(fmt, args...)	DBG_PRINT(_gSeInfo.debugFd, LX_LOGM_LEVEL_INFO, fmt, ##args)
#define SE_DEBUG(fmt, args...)	DBG_PRINT(_gSeInfo.debugFd, LX_LOGM_LEVEL_DEBUG, fmt, ##args)
#define SE_TRACE(fmt, args...)	DBG_PRINT(_gSeInfo.debugFd, LX_LOGM_LEVEL_TRACE, fmt, ##args)

#else	// _SE_STANDALONE_

#define SE_ERROR(fmt, args...)	printk("E:%s(%d):"fmt, __FUNCTION__, __LINE__, ##args)
#define SE_WARN(fmt, args...)	printk("W:%s(%d):"fmt, __FUNCTION__, __LINE__, ##args)
#define SE_NOTI(fmt, args...)	printk("N:%s(%d):"fmt, __FUNCTION__, __LINE__, ##args)
#define SE_INFO(fmt, args...)	printk("I:%s(%d):"fmt, __FUNCTION__, __LINE__, ##args)
#define SE_DEBUG(fmt, args...)	printk("D:%s(%d):"fmt, __FUNCTION__, __LINE__, ##args)
#define SE_TRACE(fmt, args...)	printk("T:%s(%d):"fmt, __FUNCTION__, __LINE__, ##args)

#endif	// _SE_STANDALONE_

#define SE_CHECK(arg, process)	if (arg) {\
									SE_ERROR("%s(%d)\n", __FILE__, __LINE__);\
									process;\
								}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#define __asmeq(x, y)  ".ifnc " x "," y " ; .err ; .endif\n\t"
#endif

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
static int _SE_Open(struct inode *inode, struct file *filp);
static int _SE_Close(struct inode *inode, struct file *filp);
static int _SE_MMAP(struct file *file, struct vm_area_struct *vma);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int _SE_IOCTL(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
#endif
static long _SE_UNLOCKED_IOCTL(struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long _SE_COMPAT_IOCTL(struct file *file, unsigned int cmd, unsigned long arg);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

// SE Device Info
static struct _SeInfo_tag {
	uint32_t chip;
	uint32_t platform;

	int debugFd;

	// For TZ Operation
	struct task_struct *pTzOperationThread;

	struct completion compTzOperationStart;
	struct completion compTzOperationEnd;

	uint32_t tzArgs[8];
	int tzResult;

	uint8_t *pWaitMap;
	uint32_t *pWait;
#if (SE_USE_YIELD_AS_WAIT==0)
	wait_queue_head_t waitQueue;
#endif

#ifndef CFG_REE_KDRV_PRVATE_DATA_PER_FILE
	BOOLEAN bCachedMap;
#endif
	BOOLEAN bResume;

	OS_SEM_T lock;		// Operation Lock
	OS_SEM_T msgLock;	// message Lock

	struct sock *pNlSock;
	int nlPid;
	struct completion compNlRecvMsg;
	BOOLEAN bCompNlRecvMsg;

	char *pNlRetMsg;
	int nlRetMsgLength;

	// For Device
#ifndef CFG_REE_KDRV_RUTA_KDRV
	dev_t devNum;
	struct cdev cDev;
#else
	dev_t devNum[2];
	struct cdev cDev[2];
#endif
	struct file_operations fileOperations;
} _gSeInfo = {
	.debugFd			= -1,
	.pTzOperationThread = NULL,

	.pWaitMap			= NULL,
	.pWait				= NULL,

#ifndef CFG_REE_KDRV_PRVATE_DATA_PER_FILE
	.bCachedMap			= FALSE,
#endif
	.bResume			= FALSE,

	.pNlSock			= NULL,
	.nlPid				= -1,
	.bCompNlRecvMsg		= FALSE,

	.pNlRetMsg			= NULL,
	.nlRetMsgLength		= 0,

	.fileOperations 	= {
		.open			= _SE_Open,
		.release		= _SE_Close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
		.ioctl			= _SE_IOCTL,
#else
		.unlocked_ioctl = _SE_UNLOCKED_IOCTL,
#ifdef CONFIG_COMPAT
		.compat_ioctl	= _SE_COMPAT_IOCTL,
#endif
#endif
		.mmap			= _SE_MMAP,
		.read			= NULL,
		.write			= NULL,
	},
};


static int b_restored = 0;

static int b_invoked_init_cmd = 0;


/*
 * share 'shmem' to user with vm_mmap() & remap_pfn_range().
 *
 * Alternative of SE_IOR_GET_RESUME_STATUS & check_invoked_init_cmd().
 *
 *
 * 'shmem_to_share_user = kmalloc(MAX_USER_IO_MAP_SHM_SZ)' at probe().
 *
 * 'user' can get shm with SE_IOR_GET_MAP_USER_SHM_MEM 
 *  
 * 'shmem_to_share_user' will be cleared with zero at restore().
 *
 *
 * related to ioctl_user_map_shmem().
 *
 */
void *shmem_to_share_user = NULL;
dma_addr_t share_user_dma_addr;


#define SZ_2M				0x00200000
#define SZ_16K				0x00004000

void *rwsm_buffer_snapshot_2M;
void *rwsm_param_snapshot_16K;


#ifdef CONFIG_COMPAT

/*
 * referenced here
 * https://elixir.bootlin.com/linux/v5.4-rc1/source/drivers/firewire/core-cdev.c#L209
 */

static inline void __user *ulong_to_uptr(ulong value)
{
	if (is_compat_task())
		return compat_ptr(value);
	else
		return (void __user *)value;
}

#else

static inline void __user *ulong_to_uptr(ulong value)
{
	return (void __user *)value;
}

#endif


/*========================================================================================
    Implementation Group : Stand Alone
========================================================================================*/

#ifdef _SE_STANDALONE_

#define		LX_MAX_DEVICE_NAME		12
static char* kdrv_dev_node_name( struct device* dev, umode_t* mode)
{
	return kasprintf(GFP_KERNEL, "lg/%s", dev_name(dev));
}

static struct class kdrv_dev_class = {	.name = "lg",
										.devnode = kdrv_dev_node_name, };

static void OS_CreateDeviceClass(dev_t dev, const char* fmt, ...)
{
	va_list args;
	char dev_name[LX_MAX_DEVICE_NAME];

	va_start(args, fmt);
	vsnprintf(dev_name, LX_MAX_DEVICE_NAME, fmt, args);
	va_end(args);

	device_create(&kdrv_dev_class, NULL, dev, NULL, dev_name );
}


static void *vmap_phys(phys_addr_t addr, unsigned long size)
{
	return ioremap_wc(addr, size);
}

static void vunmap_phys(void *addr)
{
	iounmap(addr);
}

#endif	// _SE_STANDALONE_

/*========================================================================================
    Implementation Group : SE NetLink
========================================================================================*/

#if (SE_USE_NET_LINK==1)
static int _SE_nlSendMsg(void *pMsg, int msgLength)
{
	struct nlmsghdr *pNlh;
	struct sk_buff *pSkb;

	SE_CHECK(_gSeInfo.pNlSock==NULL, return -1);
	if (_gSeInfo.nlPid < 0) {
		SE_NOTI("Not ready to send\n");
		return -1;
	}

	pSkb = nlmsg_new(msgLength, 0);
	SE_CHECK(pSkb==NULL, { SE_ERROR("Failed to allocate new skb\n"); return -1; } );

	pNlh = nlmsg_put(pSkb, 0, 0, NLMSG_DONE, msgLength, 0);
	NETLINK_CB(pSkb).dst_group = 0; /* not in mcast group */
	memcpy(nlmsg_data(pNlh), pMsg, msgLength);

	init_completion(&_gSeInfo.compNlRecvMsg);
	_gSeInfo.bCompNlRecvMsg = TRUE;

	if (nlmsg_unicast(_gSeInfo.pNlSock, pSkb, _gSeInfo.nlPid) < 0) {	// Send message
		SE_NOTI("Failed to sending to user\n");
		return -1;
	}

	// Wait Response
	if (wait_for_completion_timeout(&_gSeInfo.compNlRecvMsg, msecs_to_jiffies(SE_ACK_MSG_TIMEOUT))<=0) {
		_gSeInfo.bCompNlRecvMsg = FALSE;
		SE_WARN("Response timeout\n");
	}

	return 0;
}

static void _SE_nlRecvMsg(struct sk_buff *pSkb)
{
	struct nlmsghdr *pNlh;
	char *pMsg;

	pNlh = (struct nlmsghdr *)pSkb->data;
	_gSeInfo.nlPid = pNlh->nlmsg_pid;	// pid of sending process
	pMsg = (char *)nlmsg_data(pNlh);

	if ((_gSeInfo.pNlRetMsg != NULL)&&(_gSeInfo.nlRetMsgLength > 0)) {
		strncpy(_gSeInfo.pNlRetMsg, pMsg, _gSeInfo.nlRetMsgLength);
		*(_gSeInfo.pNlRetMsg + _gSeInfo.nlRetMsgLength - 1) = '0';
	}

	if (_gSeInfo.bCompNlRecvMsg==TRUE) {
		_gSeInfo.bCompNlRecvMsg = FALSE;
		complete(&_gSeInfo.compNlRecvMsg);
	}
	SE_DEBUG("%d:%d\n", pNlh->nlmsg_pid, pNlh->nlmsg_len);
}
#endif

int SE_SendMsgToUser(void *pMsg, int msgLength, void *pRetMsg, int retMsgLength)
{
#if (SE_USE_NET_LINK==1)
	BOOLEAN bLock = TRUE;
	int result;

	if (OS_LockMutex(&_gSeInfo.msgLock)) {
		SE_WARN("Lock failed\n");
		bLock = FALSE;
	}

	_gSeInfo.pNlRetMsg = pRetMsg, _gSeInfo.nlRetMsgLength = retMsgLength;
	result = _SE_nlSendMsg(pMsg, msgLength);
	_gSeInfo.pNlRetMsg = NULL, _gSeInfo.nlRetMsgLength = 0;

	if (bLock) {
		OS_UnlockMutex(&_gSeInfo.msgLock);
	}

	return result;
#else
	return 0;
#endif
}

/*========================================================================================
    Implementation Group : SE CDEV
========================================================================================*/

#ifndef	CFG_REE_KDRV_RUTA_KDRV

#ifdef __aarch64__
static noinline int __TzCmd(u64 _x0, u64 _x1, u64 _x2, u64 _x3,
				u64 _x4, u64 _x5, u64 _x6, u64 _x7 )
{
	asm volatile(
		__asmeq("%0", "x0")
		__asmeq("%1", "x1")
		__asmeq("%2", "x2")
		__asmeq("%3", "x3")
		__asmeq("%4", "x4")
		__asmeq("%5", "x5")
		__asmeq("%6", "x6")
		__asmeq("%7", "x7")
		"smc	#0\n"
	: "+r"(_x0)
	: "r"(_x1), "r"(_x2), "r"(_x3), "r"(_x4), "r"(_x5), "r"(_x6), "r"(_x7));

	return _x0;
}

static void _TzCmd(void)
{
	u64 ret;

	ret = __TzCmd( _gSeInfo.tzArgs[0], _gSeInfo.tzArgs[1],
			_gSeInfo.tzArgs[2], _gSeInfo.tzArgs[3],
			_gSeInfo.tzArgs[4], _gSeInfo.tzArgs[5],
			_gSeInfo.tzArgs[6], _gSeInfo.tzArgs[7] );

	_gSeInfo.tzArgs[0] = ret;
}
#else

#include <asm/opcodes-sec.h>

static void _TzCmd(void)
{
	isb();
	dsb();
	dmb();

	asm volatile (
        "LDM    %1, {r0-r7}\n"
        __SMC(0)
	"MOV    %0, r0\n"
        : "=r" (_gSeInfo.tzArgs[0])
        : "r"  (_gSeInfo.tzArgs)
        : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r12"
    );
}
#endif

static int _RunTzCmd(void)
{
	do {
		_TzCmd();
		if (_gSeInfo.tzArgs[0]==TZOS_SMC_CMD_FOREIGN_IRQ) {
#if (SE_USE_YIELD_AS_WAIT==0)
			/*
			; Set current process state to interruptible sleep.
			*/
			set_current_state(TASK_INTERRUPTIBLE);

			/*
			; Take a nap and wake up after specified time.
			*/
			if (schedule_timeout(usecs_to_jiffies(SE_TZ_SCHED_WAIT))<0)	// Just Check
				SE_ERROR("Negative return in schedule_timeout()\n");
#else	// for performance
			yield();
#endif
		}
	} while (_gSeInfo.tzArgs[0]==TZOS_SMC_CMD_FOREIGN_IRQ);

	if (_gSeInfo.tzArgs[0]==TEE_SUCCESS)
		return 0;

	SE_NOTI("TZ Return (0x%x)\n", _gSeInfo.tzArgs[0]);
	return -1;
}
#endif


static int smc_kthread(void *pArg)
{
	while (!kthread_should_stop()) {
		wait_for_completion(&_gSeInfo.compTzOperationStart);
		init_completion(&_gSeInfo.compTzOperationStart);

#ifndef	CFG_REE_KDRV_RUTA_KDRV
		_gSeInfo.tzResult = _RunTzCmd();
#else
		_gSeInfo.tzResult = do_smc_with_args(&_gSeInfo.tzArgs[0]);
#endif

		complete(&_gSeInfo.compTzOperationEnd);
	}
	SE_NOTI("Stop thread\n");

	return 0;
}

static int _waitScResponse(void)
{
	int i;

	if (_gSeInfo.pWait==NULL)
		return 0;	// Not ready to Wait Signal

#if (SE_USE_YIELD_AS_WAIT==0)
	for (i=0; i<SE_WAIT_RETRY; i++) {
		if (*_gSeInfo.pWait==0) {
			return 0;
		}
		wait_event_timeout_interruptible(_gSeInfo.waitQueue, (*_gSeInfo.pWait==0), usecs_to_jiffies(SE_WAIT));
	}
#else	// for performance
	for (i=0; i<SE_WAIT_LOOP; i++) {
	/*
		if (*_gSeInfo.pWait==0) {
			return 0;
		}
		yield();
	*/
		rmb();
		if(readl_relaxed(_gSeInfo.pWait))
			yield();
		else
			return 0;
	}
#endif

	SE_ERROR("Time out!\n");
	return -EIO;

}
#if 0 /* Deprecated */
static int check_invoked_init_cmd(unsigned long arg)
{
	u32 cmd_x0;

	get_user(cmd_x0, (u32 __user *)arg);

	if (cmd_x0 != TZ_CMD_INIT_IF && b_invoked_init_cmd == 0) {

		printk("Warn: Please, need to init, (0x%x)\n", cmd_x0);

		return -1;
	}

	return 0;
}
#endif

static int _runTzOperation(unsigned long arg)
{
	void __user *uptr = ulong_to_uptr(arg);

	SE_CHECK(copy_from_user((void *)_gSeInfo.tzArgs, uptr, sizeof(_gSeInfo.tzArgs)), return -EIO);

	complete(&_gSeInfo.compTzOperationStart);
	wait_for_completion(&_gSeInfo.compTzOperationEnd);
	init_completion(&_gSeInfo.compTzOperationEnd);

	SE_CHECK(copy_to_user((void __user *)arg, (void *)_gSeInfo.tzArgs, sizeof(_gSeInfo.tzArgs)), return -EIO);

	if (_gSeInfo.tzResult)
		return -EIO;

	b_invoked_init_cmd = 1;

	return _waitScResponse();
}

static int _wait(unsigned long arg)
{
	uint32_t pageAddr;

	if (_gSeInfo.pWaitMap==NULL) {
		SE_CHECK(arg==0, return -EIO);

		pageAddr = arg & (~(PAGE_SIZE-1));
		_gSeInfo.pWaitMap = vmap_phys(pageAddr, PAGE_SIZE);
		SE_CHECK(_gSeInfo.pWaitMap==NULL, return -EIO);

		_gSeInfo.pWait = (uint32_t *)(_gSeInfo.pWaitMap + (arg - pageAddr));
#if (SE_USE_YIELD_AS_WAIT==0)
		init_waitqueue_head(&_gSeInfo.waitQueue);
#endif
	}

	return _waitScResponse();
}



#define CFG_REE_KDRV_MULTI_RETURN  1

#ifdef CFG_REE_KDRV_MULTI_RETURN

void smc_call(void); /* added to avoid '-Wmissing-prototypes' */

void smc_call(void)
{   
    struct arm_smccc_res res;
    
    ree_smccc_smc( _gSeInfo.tzArgs[0], _gSeInfo.tzArgs[1], _gSeInfo.tzArgs[2], 
					_gSeInfo.tzArgs[3], _gSeInfo.tzArgs[4], _gSeInfo.tzArgs[5],
                    _gSeInfo.tzArgs[6], _gSeInfo.tzArgs[7], &res);
    
    _gSeInfo.tzArgs[0] = res.a0;
    _gSeInfo.tzArgs[1] = res.a1;
    _gSeInfo.tzArgs[2] = res.a2;
    _gSeInfo.tzArgs[3] = res.a3;
}
#endif /* CFG_REE_KDRV_MULTI_RETURN */

static int _getMemCfg(SE_MEMCFG_T memCfg[])
{
#ifdef CFG_REE_KDRV_MULTI_RETURN
	if(lx_chip() >= LX_CHIP_O22) {
	
		struct arm_smccc_res res;
		unsigned long cmd = SMC_FAST_GET_WSM_CONFIG;

		ree_smccc_smc(cmd, 0, 0, 0, 0, 0, 0, 0, &res);

    	pr_info("_getMemInfo (0x%lx) (0x%lx) (0x%lx) (0x%lx)\n", 
											res.a0, res.a1, res.a2,res.a3);
	
		/* RWSM */
		memCfg[0].idx = 0;
		memCfg[0].base = res.a1 & 0x00000000FFFFFFFF;
		memCfg[0].size = (res.a1 >> 32) & 0x00000000FFFFFFFF;

		/* Overall secure mem */
		memCfg[1].idx = 1;
		memCfg[1].base = res.a2;
		memCfg[1].size = res.a3;

		return 0;
	}
#endif

	memCfg[0].idx = 0, memCfg[0].base = gpMemCfgSE->base, memCfg[0].size = gpMemCfgSE->size;
	memCfg[1].idx = 1, memCfg[1].base = gpMemCfgSE_TZFW->base, memCfg[1].size = gpMemCfgSE_TZFW->size;

	return 0;
}


#define SMC_FAST_TRUSTED_BINARY_LOADING	(0x305)
#define TBL_CMD_BUFFER_INIT				(0x1)
#define TBL_CMD_LOAD_DATA				(0x2)
#define TBL_CMD_LOAD_DATA_AND_VERIFY	(0x3)



#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)

#define CPU_TOP_BASE	(0xfd300000)
#define CHIP_ID_REG		(CPU_TOP_BASE + 0x1000)
#define FPGA_MASK		(0xF0000000)
#define ASIC_MASK		(0xA0000000)
static int _is_fpga(void)
{
	void* chip_id_reg = memremap((phys_addr_t)CHIP_ID_REG, 0x4, MEMREMAP_WC);
	unsigned int chip_id;

	if (chip_id_reg == NULL) {
		pr_err("(%s) memremap()=NULL, need to check CHIP_ID_REG\n", __func__);
		return 0;
	}

	chip_id = *((unsigned int *)chip_id_reg);

	memunmap(chip_id_reg);

	if( (chip_id&FPGA_MASK) == FPGA_MASK)
		return 1;

	return 0;
}

int se_trusted_binary_loading(unsigned int id, void* dest, void* src, unsigned int size)
{
	int ret = 0;
	ulong smc_cmd = SMC_FAST_TRUSTED_BINARY_LOADING;
	ulong tbl_cmd;

	struct arm_smccc_res res;

	SE_MEMCFG_T memCfg[2];
	void *wsbuf_va_ptr;
	ulong wsbuf_pa_addr;
	int wsbuf_size;
	int wsbuf_usable_size;

	ulong cur_src_addr = (ulong)src;
	ulong cur_dest_addr = (ulong)dest;
	ulong cur_packet_num = 0;

	int remains;

	if (src == NULL || size == 0) {
		SE_ERROR("Invalid param (0x%lx) (0x%lx) (0x%lx)\n",
						(ulong)src, (ulong)dest, (ulong)size);
		return -EIO;
	}

	//memcpy from src_address to dest_address because TZ is not activated on FPGA.
	if(_is_fpga()) {
		void* dest_va = memremap((phys_addr_t)dest, size, MEMREMAP_WC);

		if (dest_va == NULL) {

			pr_err("(%s) memremap()=NULL, need to check dest(0x%lx:%lu)\n",
					__func__,
					(ulong)dest, (ulong)size);

			return -ENOMEM;
		}

		memcpy(dest_va, src, size);
		memunmap(dest_va);

		return 0;
	}

	if (OS_LockMutex(&_gSeInfo.lock)) {
		SE_WARN("Lock failed\n");
		return -EIO;
	}

	_getMemCfg(memCfg);
	wsbuf_pa_addr = memCfg[0].base;
	wsbuf_size = memCfg[0].size;

	remains = size;

	//tbl buffer init
	tbl_cmd = TBL_CMD_BUFFER_INIT;
	ree_smccc_smc(smc_cmd, tbl_cmd, id, wsbuf_pa_addr, wsbuf_size, (ulong)dest, (ulong)size, 0, &res);

#ifdef TEE_SUCCESS
	if(res.a0 != TEE_SUCCESS) {
#else
	if(res.a0 != TZ_SUCCESS) {
#endif
		SE_ERROR("TBL Buffer init fail\n");
		OS_UnlockMutex(&_gSeInfo.lock);
		return -EIO;
	}

	wsbuf_usable_size = wsbuf_size / 2;
	while(remains > 0)
	{
		int cur_size;
		cur_packet_num++;

		if (wsbuf_usable_size >= remains){
			tbl_cmd = TBL_CMD_LOAD_DATA_AND_VERIFY;
			cur_size = remains;
		}

		else {
			tbl_cmd = TBL_CMD_LOAD_DATA;
			cur_size = wsbuf_usable_size;
		}

		wsbuf_va_ptr = memremap((phys_addr_t)wsbuf_pa_addr, wsbuf_usable_size, MEMREMAP_WC);

		if (wsbuf_va_ptr == NULL) {

			pr_err("(%s) memremap()=NULL, need to check wsbuf_pa(0x%lx:%lu)\n",
					__func__,
					(ulong)wsbuf_pa_addr, (ulong)wsbuf_usable_size);
			return -ENOMEM;
		}

		memcpy(wsbuf_va_ptr, (void*)cur_src_addr, cur_size);
		memunmap(wsbuf_va_ptr);

		ree_smccc_smc(smc_cmd, tbl_cmd, id, cur_packet_num, cur_size, 0, 0, 0, &res);

#ifdef TEE_SUCCESS
		if(res.a0 != TEE_SUCCESS) {
#else
		if(res.a0 != TZ_SUCCESS) {
#endif
			SE_ERROR("trusted binary loading fail (id:0x%x)\n", id);
			ret = -EIO;
			break;
		}

		cur_src_addr += cur_size;
		cur_dest_addr += cur_size;
		remains -= cur_size;
	}

	OS_UnlockMutex(&_gSeInfo.lock);

	return ret;
}

/* http://clm.lge.com/issue/browse/SICDTV-11649 */
int lgkree_req_secure_fwload(uint32_t id, void* dest, void* src, uint32_t size)
{
	int ret = 0;
	struct arm_smccc_res res = { 0, };
	ulong smc_cmd = TZ_CMD_SECURE_FWLOAD;
	


	if (src == NULL || size == 0) {
		SE_ERROR("Invalid param (0x%lx) (0x%lx) (0x%lx)\n",
						(ulong)src, (ulong)dest, (ulong)size);
		return -EIO;
	}

	/*
	 * memcpy from src_address to dest_address 
	 *  - because TZ is not activated on FPGA.
	 */
	if(_is_fpga()) {
		void* dest_va = memremap((phys_addr_t)dest, size, MEMREMAP_WC);

		if (dest_va == NULL) {

			pr_err("(%s)memremap()=NULL, need to check dest(0x%lx:%lu)\n",
					__func__,
					(ulong)dest, (ulong)size);
			return -ENOMEM;
		}

		memcpy(dest_va, src, size);
		memunmap(dest_va);

		return 0;
	}

	if (OS_LockMutex(&_gSeInfo.lock)) {
		SE_WARN("Lock failed\n");
		return -EIO;
	}

	ree_smccc_smc(smc_cmd, id, 
					(ulong)dest, (ulong)src, (ulong)size, 0, 0, 0, &res);


#ifdef TEE_SUCCESS
	if(res.a0 != TEE_SUCCESS) {
#else
	if(res.a0 != TZ_SUCCESS) {
#endif
		SE_ERROR("TBL Buffer init fail\n");
		OS_UnlockMutex(&_gSeInfo.lock);
		return -EIO;
	}

	OS_UnlockMutex(&_gSeInfo.lock);

	return ret;
}


#else

int se_trusted_binary_loading(unsigned int id, void* dest, void* src, unsigned int size)
{
	SE_ERROR("se_tbl not supported\n");
	return -EIO;
}

int lgkree_req_secure_fwload(uint32_t id, void* dest, void* src, uint32_t size)
{
	SE_ERROR("se_tbl not supported\n");
	return -EIO;
}

#endif

EXPORT_SYMBOL(se_trusted_binary_loading);
EXPORT_SYMBOL(lgkree_req_secure_fwload);



static int _getMemInfo(unsigned long arg)
{
	SE_MEMCFG_T memCfg[2];

	void __user *uptr = NULL;

	_getMemCfg(memCfg);

	uptr = ulong_to_uptr(arg);

	SE_CHECK(copy_to_user(uptr, (void *)(&memCfg[0]), sizeof(SE_MEMCFG_T)), return -EIO);

	uptr = ulong_to_uptr(arg+sizeof(SE_MEMCFG_T));

	SE_CHECK(copy_to_user(uptr, (void *)(&memCfg[1]), sizeof(SE_MEMCFG_T)), return -EIO);

	return 0;
}

#ifdef CFG_REE_KDRV_MEMREMAP_RWSM

struct remap_rwsm_info {
	ulong base;
	ulong size;
	void *map_ptr;
};

struct remap_rwsm_info *remap_rwsm = NULL;

static void init_remap_rwsm(void)
{
	int res = 0;

	SE_MEMCFG_T mem_cfg[2] = { };

	void *map_ptr = NULL;

	res = _getMemCfg(mem_cfg);

	if (res != 0 ||
		mem_cfg[0].base == 0 ||
		mem_cfg[0].size == 0 ||
		remap_rwsm != NULL) {

		pr_err("fail : init_remap (%d)\n", res);
		return;
	}

	map_ptr = memremap((phys_addr_t)mem_cfg[0].base,
						(size_t)mem_cfg[0].size,
						MEMREMAP_WB);

	if (map_ptr == NULL) {
		pr_err("fail : memremap\n");
		return;
	}

	remap_rwsm = kzalloc(sizeof(*remap_rwsm), GFP_KERNEL);

	if (remap_rwsm == NULL) {

		memunmap(map_ptr);
		pr_err("fail : no memory \n");
		return;
	}

	remap_rwsm->base = (ulong)mem_cfg[0].base;
	remap_rwsm->size = (ulong)mem_cfg[0].size;
	remap_rwsm->map_ptr = map_ptr;

	pr_info("success, init_remap (%d)\n", __LINE__);

	return;
}

static void cleanup_remap_rwsm(void)
{
	if (remap_rwsm != NULL) {

		memunmap(remap_rwsm->map_ptr);
		kfree(remap_rwsm);

		remap_rwsm = NULL;
	}

	return;
}

static void *get_remap_rwsm_kaddr(u64 base, u32 size)
{
	ulong addr1 = (ulong)base;
	ulong addr2 = (ulong)base + size -1;

	size_t offset = 0;

	void *ret_ptr = NULL;

	if (remap_rwsm == NULL) {
		pr_err("get_remap_rwsm_kaddr: bad state\n");
		return NULL;
	}

	if (addr1 >= remap_rwsm->base &&
	    addr1 < remap_rwsm->base + remap_rwsm->size &&
	    addr2 >= remap_rwsm->base &&
	    addr2 < remap_rwsm->base + remap_rwsm->size) {

		offset = addr1 - remap_rwsm->base;
		ret_ptr = (void *)(remap_rwsm->map_ptr + offset);

	} else
		pr_err("get_remap_rwsm_kaddr: bad param\n");

	return ret_ptr;
}

#endif

static int _cacheCtrl(struct file *filp, unsigned long arg)
{
	SE_CACHE_CTRL_T cacheCtrl;

	void __user *uptr = ulong_to_uptr(arg);

#ifdef CFG_REE_KDRV_MEMREMAP_RWSM

	void *kaddr_rwsm = NULL;
#endif


#ifdef CFG_REE_KDRV_PRVATE_DATA_PER_FILE

	struct ree_kdrv_file_priv_data *filp_priv =
		(struct ree_kdrv_file_priv_data *)filp->private_data;
#else
	(void)filp; /* to avoid warning */
#endif


	SE_CHECK(copy_from_user((void *)&cacheCtrl, uptr, sizeof(SE_CACHE_CTRL_T)), return -EIO);

	switch (cacheCtrl.operation) {
		case SE_CACHE_MAP :

#ifdef CFG_REE_KDRV_PRVATE_DATA_PER_FILE
			if (filp_priv != NULL)
				filp_priv->flag_mmap_cached = true;
			else
				pr_warn("ree_kdrv: filp_priv is null");
#else
			_gSeInfo.bCachedMap = TRUE;
#endif
			break;

		case SE_CACHE_INVALIDATE :

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))

#ifdef CFG_REE_KDRV_MEMREMAP_RWSM

			kaddr_rwsm = get_remap_rwsm_kaddr(cacheCtrl.paddr, cacheCtrl.size);
			if (kaddr_rwsm != NULL)
				dcache_inval_poc((unsigned long)kaddr_rwsm,
						(unsigned long)(kaddr_rwsm + cacheCtrl.size));
#else

			dcache_inval_poc((unsigned long)cacheCtrl.vaddr,
					(unsigned long)(cacheCtrl.vaddr + cacheCtrl.size));
#endif /* CFG_REE_KDRV_MEMREMAP_RWSM */

#else

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,0)
			__dma_map_area((void *)cacheCtrl.vaddr, cacheCtrl.size, DMA_FROM_DEVICE);//v7_dma_inv_range
#ifndef __aarch64__
			outer_inv_range((phys_addr_t)cacheCtrl.paddr, (phys_addr_t)cacheCtrl.paddr + cacheCtrl.size);
#endif
#else	//	LINUX_VERSION_CODE < KERNEL_VERSION(4,4,0)
			dmac_map_area(cacheCtrl.vaddr, cacheCtrl.size, DMA_FROM_DEVICE);//v7_dma_inv_range
			outer_inv_range((phys_addr_t)cacheCtrl.paddr, (phys_addr_t)cacheCtrl.paddr + cacheCtrl.size);
#endif

#endif
			break;

		case SE_CACHE_CLEAN :

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))

#ifdef CFG_REE_KDRV_MEMREMAP_RWSM
			kaddr_rwsm = get_remap_rwsm_kaddr(cacheCtrl.paddr, cacheCtrl.size);
			if (kaddr_rwsm != NULL)
				dcache_clean_poc((unsigned long)kaddr_rwsm,
						(unsigned long)(kaddr_rwsm + cacheCtrl.size));

#else
			dcache_clean_poc((unsigned long)cacheCtrl.vaddr,
						(unsigned long)(cacheCtrl.vaddr + cacheCtrl.size));
#endif /* CFG_REE_KDRV_MEMREMAP_RWSM */

#else

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,0)
			__dma_map_area((void *)cacheCtrl.vaddr, cacheCtrl.size, DMA_TO_DEVICE);//v7_dma_clean_range
#ifndef __aarch64__
			outer_clean_range((phys_addr_t)cacheCtrl.paddr, (phys_addr_t)cacheCtrl.paddr + cacheCtrl.size);
#endif
#else	//	LINUX_VERSION_CODE < KERNEL_VERSION(4,4,0)
			dmac_map_area(cacheCtrl.vaddr, cacheCtrl.size, DMA_TO_DEVICE);//v7_dma_clean_range
			outer_clean_range((phys_addr_t)cacheCtrl.paddr, (phys_addr_t)cacheCtrl.paddr + cacheCtrl.size);
#endif

#endif
			break;

		default :
			SE_ERROR("Not defined(%d)\n", cacheCtrl.operation);
			return -EINVAL;
	}

	return 0;
}

static int _sendMsg(unsigned long arg)
{
	unsigned char msg[SE_IOW_SEND_MSG_LENGTH];

	void __user *uptr = ulong_to_uptr(arg);

	// Message
	SE_CHECK(copy_from_user((void *)msg, uptr, sizeof(msg)), return -EIO);

	// Send
	if (SE_SendMsgToUser(msg, sizeof(msg), msg, sizeof(msg))) {
		SE_ERROR("Failed Send Msg\n");
		return -EINVAL;
	}

	// Result
	SE_CHECK(copy_to_user(uptr, (void *)msg, sizeof(msg)), return -EIO);

	return 0;
}


static int ioctl_user_map_shmem(unsigned long arg)
{
	unsigned long vma_addr;
	struct vm_area_struct * vma;

	vma_addr = vm_mmap(0,
			0L,
			MAX_USER_IO_MAP_SHM_SZ,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			0);

	if (IS_ERR((void*)vma_addr)) {

		pr_err("%d,%s fail vm_mmap\n", __LINE__, __func__);

		return -ENOMEM;
	}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,8,0))

	mmap_read_lock(current->mm);
#endif

	vma = find_vma(current->mm, vma_addr);

	if (vma == NULL) {

		pr_err("%d,%s fail find_vma\n", __LINE__, __func__);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,8,0))

		mmap_read_unlock(current->mm);
#endif
		return -ENOMEM;
	}

	vma->vm_pgoff = 0;


	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,8,0))

	mmap_read_unlock(current->mm);

	mmap_write_lock(current->mm);

#endif

	if (remap_pfn_range(vma,
			    vma->vm_start,
			    PFN_DOWN(share_user_dma_addr),
			    MAX_USER_IO_MAP_SHM_SZ,
			    vma->vm_page_prot) < 0) {

		pr_err("%d,%s fail remap_pfn_range\n", __LINE__, __func__);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,8,0))

		mmap_write_unlock(current->mm);
#endif

		return -ENOMEM;
	}

	pr_info("user shared: info (%p) (%llx) (%lx)\n",
			shmem_to_share_user, share_user_dma_addr, vma_addr);


	put_user(vma_addr, (unsigned long long __user *)arg);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,8,0))

	mmap_write_unlock(current->mm);
#endif

	return 0;
}


static long _SE_UNLOCKED_IOCTL(struct file *file, unsigned int cmd, unsigned long arg)
{
	long result = -ENOTTY;

#ifndef CFG_REE_KDRV_RUTA_KDRV
	if (OS_LockMutex(&_gSeInfo.lock)) {
		SE_ERROR("Lock failed\n");
		return -EIO;
	}
#endif

//	wmb();

	switch (cmd) {
		case SE_IORW_RUN_TZ_OP :


/*
 * removed a check for SE_TZ_CMD_INIT_IF(). Temporary, need more check, later.
 */
#if 0
			if (check_invoked_init_cmd(arg) < 0) {

				put_user(TEE_ERROR_NO_DATA, (u32 __user *)arg);
				OS_UnlockMutex(&_gSeInfo.lock);

				return -EIO;
			}
#endif

#ifdef CFG_REE_KDRV_RUTA_KDRV
			if (OS_LockMutex(&_gSeInfo.lock)) {
				SE_ERROR("Lock failed\n");
				return -EIO;
			}
#endif
			result = _runTzOperation(arg);

#ifdef CFG_REE_KDRV_RUTA_KDRV

			OS_UnlockMutex(&_gSeInfo.lock);
#endif
			break;

		case SE_IOR_WAIT :
			result = _wait(arg);
			break;

		case SE_IOW_CACHE_CTRL :
			result = _cacheCtrl(file, arg);
			break;

		case SE_IOW_GET_MEM_INFO :
			result = _getMemInfo(arg);
			break;

		case SE_IORW_SEND_MSG :
			result = _sendMsg(arg);
			break;

		case SE_IO_CHECK_PERMISSION :
			if (!capable(CAP_SYS_RAWIO))
				result = 0;	// If doesn't have permission, return 0.
			break;

		case SE_IO_CHECK_RESUME :
			if (_gSeInfo.bResume==TRUE)
				result = 0;	// Return SUCCESS
			_gSeInfo.bResume = FALSE;	// Clean Resume Flag
			break;

		case SE_IOR_GET_RESUME_STATUS :
		{
			unsigned int status = 0;

			if (_gSeInfo.bResume == TRUE) {
				status += SE_DRV_STATUS_AFTER_RESUME;
				_gSeInfo.bResume = FALSE;
				SE_NOTI("catched resume(%x)\n", status);
			}

			if (b_restored == 1) {
				status += SE_DRV_STATUS_AFTER_RESTORE;
				b_restored = 0;
				SE_NOTI("catched restore(%x)\n", status);
			}

			//SE_NOTI("catched status = %u\n", status);

			put_user(status, (unsigned int __user *)arg);

			result = 0;

			break;
		}

		case SE_IOR_GET_SMC_THREAD_SCHED_POLICY :
		{

			struct task_struct *p =_gSeInfo.pTzOperationThread;

			if(p->policy == SCHED_NORMAL || p->policy == SCHED_FIFO)
			{
				result = p->policy;
			}
			else
			{
				result = -EIO;
			}

			break;
		}

		case SE_IOWR_SET_SMC_THREAD_SCHED_POLICY:
		{
			int retval = -EIO;
			int req_policy;
			//struct task_struct *p =_gSeInfo.pTzOperationThread;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0))

			struct sched_param param = {0, };
#endif

			void __user *uptr = ulong_to_uptr(arg);

			SE_CHECK(copy_from_user((void *)&req_policy, uptr, sizeof(req_policy)), return -EIO);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0))

			if(req_policy == SCHED_FIFO)
				param.sched_priority = SMC_THREAD_SCHED_FIFO_PRIORITY;
			else if(req_policy == SCHED_NORMAL)
				param.sched_priority = SMC_THREAD_SCHED_NORMAL_PRIORITY;

			retval = sched_setscheduler_nocheck(_gSeInfo.pTzOperationThread, req_policy, &param);
#else

			retval = 0;

			if(req_policy == SCHED_FIFO)
				sched_set_fifo(_gSeInfo.pTzOperationThread);

			else if(req_policy == SCHED_NORMAL)
				sched_set_normal(_gSeInfo.pTzOperationThread, 0);
#endif

			if(retval != 0)
			{
				SE_ERROR("Can't change priority\n");
			}

			result = retval;

			break;
		}

		case SE_IOR_GET_MAP_USER_SHM_MEM:

			result = ioctl_user_map_shmem(arg);

			break;

#ifdef CFG_REE_KDRV_RUTA_KDRV
		
				case RUTA_IOR_GET_RMT_RWSM :
					result = ruta_kdrv_get_rmt_rwsm(arg);
					break;
		
				case RUTA_IORW_RECV :
					result = ruta_kdrv_recv(arg);
					break;
		
				case RUTA_IORW_SEND :
					result = ruta_kdrv_send(arg);
					break;
#endif

		case DMA_BUF_IO_GET_INFO_FROM_FD:
			result = dmabuf_ioctl_get_info(internal_dev, arg);
			break;

		case DMA_BUF_IO_TEST_EXPORT:
			result = dmabuf_ioctl_test_export(internal_dev, arg);
			break;

		default :
			SE_ERROR("Not defined(%d) 0x%x\n", cmd, cmd);
			break;
	}

#ifndef CFG_REE_KDRV_RUTA_KDRV
	OS_UnlockMutex(&_gSeInfo.lock);
#endif

	return result;
}

#ifdef CONFIG_COMPAT

#define RUTA_IOR_GET_RMT_RWSM_COMPAT	_IOWR(SE_IOC_MAGIC, 2, compat_uptr_t)
#define RUTA_IORW_RECV_COMPAT			_IOWR(SE_IOC_MAGIC, 3, compat_uptr_t)
#define RUTA_IORW_SEND_COMPAT			_IOWR(SE_IOC_MAGIC, 4, compat_uptr_t)


static long _SE_COMPAT_IOCTL(struct file *file, unsigned int cmd, unsigned long arg)
{
	unsigned int compat_cmd = cmd;
	unsigned long compat_arg = arg;


	if (cmd == RUTA_IOR_GET_RMT_RWSM_COMPAT) {
		compat_cmd = RUTA_IOR_GET_RMT_RWSM;
		compat_arg = (unsigned long)compat_ptr(arg);
	}

	if (cmd == RUTA_IORW_RECV_COMPAT) {
		compat_cmd = RUTA_IORW_RECV;
		compat_arg = (unsigned long)compat_ptr(arg);
	}

	if (cmd == RUTA_IORW_SEND_COMPAT) {
		compat_cmd = RUTA_IORW_SEND;
		compat_arg = (unsigned long)compat_ptr(arg);
	}

	return _SE_UNLOCKED_IOCTL(file, compat_cmd, compat_arg);
}

#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int _SE_IOCTL(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	return (int)_SE_UNLOCKED_IOCTL(file, cmd, arg);
}
#endif

static int _SE_MMAP(struct file *file, struct vm_area_struct *vma)
{
#ifdef CFG_REE_KDRV_PRVATE_DATA_PER_FILE

	struct ree_kdrv_file_priv_data *filp_priv =
		(struct ree_kdrv_file_priv_data *)file->private_data;
#endif


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,3,0))

		vm_flags_set(vma, VM_IO|VM_DONTEXPAND|VM_DONTDUMP);
#elif (LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0))
		vma->vm_flags |= VM_RESERVED;//to prevent swapout
#else
		vma->vm_flags |= VM_IO|VM_DONTEXPAND|VM_DONTDUMP;//to prevent swapout
#endif

	/*
	 * Normal Bufferable Memory
	 * - pgprot_writecombine() : Normal Bufferable
	 * - pgprot_noncached() : Strongly Ordered
	 */
#ifdef CFG_REE_KDRV_PRVATE_DATA_PER_FILE

	if (filp_priv != NULL) {

		if (filp_priv->flag_mmap_cached == false) {
			/*
			pr_info("ree_kdrv: vm_page_prot = pgprot_writecombine(m:%d)(0x%lx)\n",
										filp_priv->minor_num,
										(ulong)(vma->vm_end - vma->vm_start));
			*/

			vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
		} else {
			/*
			pr_info("ree_kdrv: vm_page_prot = (default) (m:%d)(0x%lx)\n",
										filp_priv->minor_num,
										(ulong)(vma->vm_end - vma->vm_start));
			*/
		}

		filp_priv->flag_mmap_cached = false;

	} else {
		/* if null, pgprot_writecombine */
		pr_warn("ree_kdrv: filp_priv = null\n");
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}

#else
	if (_gSeInfo.bCachedMap==FALSE)
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	_gSeInfo.bCachedMap = FALSE;

#endif

	return remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
		vma->vm_end - vma->vm_start, vma->vm_page_prot);
}

static int _SE_Open(struct inode *inode, struct file *filp)
{
#ifdef CFG_REE_KDRV_PRVATE_DATA_PER_FILE

	struct ree_kdrv_file_priv_data *filp_priv = NULL;

	filp_priv = kzalloc(sizeof(struct ree_kdrv_file_priv_data), GFP_KERNEL);

	if (filp_priv == NULL) {
	       pr_warn("ree_kdrv: no mem for private_data at %s\n", __func__);

	} else {
		filp_priv->flag_mmap_cached = false;
		filp_priv->minor_num = iminor(inode);
		filp->private_data = (void *)filp_priv;
	}
#endif

	return 0;
}

static int _SE_Close(struct inode *inode, struct file *filp)
{

#ifdef CFG_REE_KDRV_PRVATE_DATA_PER_FILE

	if (filp->private_data != NULL) {

	       pr_info("ree_kdrv: free private_data\n");
	       kfree(filp->private_data);
	}
#endif

/*
    Deprecated:
        Can't make a guarantee for a sending messages to user
        when user process is closing with a signal.
*/
#if 0
	char msg[16];
	int pidClose;

	pidClose = (int)task_tgid_nr(current);
	if (_gSeInfo.nlPid==pidClose) {
		SE_NOTI("Closed by Receiver\n");
		return 0;
	}

	//	NOTE :
	//	To wait finishing ioctl of closing process, it can protect tz param.
	//	During ioctl operation in closing process, shold be wait ioctl done
	//	to avoid tz param chaning in user level Close Handler.
	//	Lock & Unlock can wait ioctl done.
	if (OS_LockMutex(&_gSeInfo.lock)) {
		SE_ERROR("Lock failed\n");
		return -EIO;
	}
	OS_UnlockMutex(&_gSeInfo.lock);

	snprintf(msg, sizeof(msg), "close:%d", pidClose);
	if (SE_SendMsgToUser(msg, strlen(msg)+1, NULL, 0)) {
		SE_NOTI("Failed Send Msg\n");
	}

	return 0;

#endif
	pr_info("ree_kdrv: release(%d)\n", (int)task_tgid_nr(current));

	return 0;
}

static int se_suspend(struct device *dev)
{
	(void)dev;

#ifdef KDRV_CONFIG_PM_SE
	SE_NOTI("Suspend\n");
#endif
	return 0;
}

static int se_resume(struct device *dev)
{
	(void)dev;

#ifdef KDRV_CONFIG_PM_SE
	SE_NOTI("Resume\n");
#endif
	_gSeInfo.bResume = TRUE;

	return 0;
}

static void *alloc_rwsm_snapshot_buffer(u32 size)
{
	struct page ** pages;

	u32 npages;

	int i = 0;

	void *vmap_addr;


	npages = ((size + PAGE_SIZE - 1) & ~(PAGE_SIZE-1)) >> PAGE_SHIFT;

	pr_info("%s: alloc_page (%u, %u)\n", __func__, size, npages);


	pages = kmalloc(sizeof(struct page *)*npages, GFP_KERNEL);

	if (pages == NULL) {

		pr_err("%s:no mem\n", __func__);

		return NULL;
	}

	for (i=0; i<npages; i++) {

		pages[i] = alloc_page(GFP_KERNEL);

		if (pages[i] == NULL) {

			pr_err("%s:no page [%d]\n", __func__, i);

			kfree(pages);

			return NULL;
		}
	}

	vmap_addr = vmap(pages, npages, 0, pgprot_writecombine(PAGE_KERNEL));

	kfree(pages);

	return vmap_addr;
}


#define RWSM_SNAP_MAKING (1)
#define RWSM_SNAP_VERIFY (2)
#define RWSM_SNAP_RESTORE (3)

static int do_snapshot_about_rwsm(u32 type)
{
	SE_MEMCFG_T memCfg[2];

	ulong rwsm_base;
	ulong rwsm_size;

	void *rwsm_va;

	ulong rwsm_param_offset;

	if (rwsm_buffer_snapshot_2M == NULL 
		|| rwsm_param_snapshot_16K == NULL) {

		pr_warn("%s, warn no item (%p, %p)\n", __func__,
				rwsm_buffer_snapshot_2M,
				rwsm_param_snapshot_16K);

		return 0;
	}

	_getMemCfg(memCfg);

	rwsm_base = memCfg[0].base;
	rwsm_size = memCfg[0].size;

	rwsm_param_offset = rwsm_size - SZ_16K;


	pr_info("%s, try to do for rwsm snap (%u) (%lx) (%lx) (%lx)\n",
						__func__,
						type,
						rwsm_base,
						rwsm_size,
						rwsm_param_offset);


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 6, 0))

	rwsm_va = memremap(rwsm_base, rwsm_size, MEMREMAP_WC);
#else
	rwsm_va = ioremap_wc(rwsm_base, rwsm_size);
#endif

	if (rwsm_va == NULL) {

		pr_err("(%s)memremap()=NULL, need to check rwsm(0x%lx:%lu)\n",
				__func__,
				(ulong)rwsm_base, (ulong)rwsm_size);
		return -ENOMEM;
	}

	switch(type) {

	case RWSM_SNAP_MAKING:
		memcpy(rwsm_buffer_snapshot_2M, rwsm_va, SZ_2M);
		memcpy(rwsm_param_snapshot_16K,
			(void *)((ulong)rwsm_va + rwsm_param_offset),
			SZ_16K);
		break;

	case RWSM_SNAP_VERIFY:
		if (memcmp(rwsm_buffer_snapshot_2M, rwsm_va, SZ_2M) != 0) {

			pr_warn("%s, warn not match 2M\n", __func__);
		}

		if (memcmp(rwsm_param_snapshot_16K,
			(void *)((ulong)rwsm_va + rwsm_param_offset),
			SZ_16K) != 0) {

			pr_warn("%s, warn not match 16K\n", __func__);
		}
		break;

	case RWSM_SNAP_RESTORE:
		memcpy(rwsm_va, rwsm_buffer_snapshot_2M, SZ_2M);
		memcpy((void *)((ulong)rwsm_va + rwsm_param_offset),
			rwsm_param_snapshot_16K,
			SZ_16K);
		break;
	default:
		pr_warn("%s, warn do nothing(%u)\n", __func__, type);
		break;
	}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 6, 0))

	memunmap(rwsm_va);
#else
	iounmap(rwsm_va);
#endif

	return 0;
}

static int se_restore(struct device *dev)
{

	do_snapshot_about_rwsm(RWSM_SNAP_RESTORE);

	if (_gSeInfo.pWait != NULL) {
		if (*_gSeInfo.pWait != 0) {
			SE_NOTI("noti: *_gSeInfo.pWait = %u\n", *_gSeInfo.pWait);
			*_gSeInfo.pWait = 0;
		}
	}

	b_restored = 1;

	b_invoked_init_cmd = 0;

	/*
	 * memset(zero) at restore, (at a snapshot booting started)
	 * related to check a loaded uta. (about a open-session in ca)
	 */
	memset(shmem_to_share_user, 0x0, MAX_USER_IO_MAP_SHM_SZ);

	pr_info("restore: (%p) (%llx) clear\n",
			shmem_to_share_user, share_user_dma_addr);

	SE_NOTI("Restore\n");

	return 0;
}

static int _SE_Probe(struct platform_device *pdev)
{

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0))

	shmem_to_share_user = dma_alloc_attrs(&pdev->dev,
			MAX_USER_IO_MAP_SHM_SZ,
			&share_user_dma_addr,
			GFP_KERNEL,
			DMA_ATTR_WRITE_COMBINE);
#else
	struct page * page;
	u32 order;

	pr_info("probe: alloc_pages\n");

	order = get_order(MAX_USER_IO_MAP_SHM_SZ);

	page = alloc_pages(GFP_KERNEL , order);

	if (page == NULL) {

		pr_err("nwd fail alloc_pages\n");
		return -1;
	}

	share_user_dma_addr = page_to_phys(page);

	shmem_to_share_user = vmap(&page, 1, 0, pgprot_writecombine(PAGE_KERNEL));

#endif

	pr_info("probe: info (%p) (%llx)\n",
			shmem_to_share_user, share_user_dma_addr);

	if (shmem_to_share_user == NULL) {

		pr_err("nwd fail, kmalloc(PAGE_SIZE , GFP_KERNEL)\n");

		return -1;
	}

	memset(shmem_to_share_user, 0x0, MAX_USER_IO_MAP_SHM_SZ);

	rwsm_buffer_snapshot_2M = alloc_rwsm_snapshot_buffer(SZ_2M);

	rwsm_param_snapshot_16K = alloc_rwsm_snapshot_buffer(SZ_16K);


	pr_info("%s probe: %p, %p\n", __func__,
		rwsm_buffer_snapshot_2M, rwsm_param_snapshot_16K);


#ifdef CFG_REE_KDRV_MEMREMAP_RWSM

	init_remap_rwsm();
#endif

	SE_NOTI("Probe\n");

	return 0;
}

static int  _SE_Remove(struct platform_device *pdev)
{

	if (shmem_to_share_user != NULL) {

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0))

		dma_free_attrs(&pdev->dev,
				MAX_USER_IO_MAP_SHM_SZ,
				shmem_to_share_user,
				share_user_dma_addr,
				DMA_ATTR_WRITE_COMBINE);
#else
		u32 order;

		order = get_order(MAX_USER_IO_MAP_SHM_SZ);

		vunmap(shmem_to_share_user);

		__free_pages(phys_to_page(share_user_dma_addr), order);
#endif

	}

#ifdef CFG_REE_KDRV_MEMREMAP_RWSM

	cleanup_remap_rwsm();
#endif

	SE_NOTI("Remove\n");

	return 0;
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))

static void drv_remove(struct platform_device *pdev)
{

	(void)_SE_Remove(pdev);
}
#endif

static void _SE_Release(struct device *dev)
{
	SE_NOTI("Release\n");
}

/*
 *	module platform driver structure
 */


static int se_drv_freeze(struct device *dev)
{
	do_snapshot_about_rwsm(RWSM_SNAP_MAKING);

	return 0;
}


static int se_drv_thaw(struct device *dev)
{
	do_snapshot_about_rwsm(RWSM_SNAP_VERIFY);

	return 0;
}


static struct dev_pm_ops se_pm_ops = {
	.suspend = se_suspend,
	.resume = se_resume,
	.restore = se_restore,
	.freeze = se_drv_freeze,
	.thaw = se_drv_thaw,
};

static struct platform_driver _se_driver =
{
	.probe		= _SE_Probe,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
	.remove		= drv_remove,
#else
	.remove		= _SE_Remove,
#endif
	.driver		= {
		.name = SE_MODULE,
		.pm = &se_pm_ops,
	},
};

static struct platform_device _se_device = {
	.name = SE_MODULE,
	.id = -1,
	.dev = {
		.release = _SE_Release,
	},
};

/*========================================================================================
    Implementation Group : SE Module
========================================================================================*/
/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void SE_PreInit(void)
{
    /* TODO: do something */
}

int SE_Init(void)
{
	int mi = 0; /*minior number*/
		
#ifndef _SE_STANDALONE_

	/* Get the handle of debug output for se device.
	*
	* Most module should open debug handle before the real initialization of module.
	* As you know, debug_util offers 4 independent debug outputs for your device driver.
	* So if you want to use all the debug outputs, you should initialize each debug output
	* using OS_DEBUG_EnableModuleByIndex() function.
	*/
	_gSeInfo.debugFd = DBG_OPEN(SE_MODULE);
	if (_gSeInfo.debugFd < 0) {
		printk("[SE] can't get debug handle\n");
	}
	else {
		OS_DEBUG_EnableModule(_gSeInfo.debugFd);
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED );		// error
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW );	// warn
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE );		// noti
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, LX_LOGM_LEVEL_INFO, DBG_COLOR_NONE );		// info
		//OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, LX_LOGM_LEVEL_DEBUG, DBG_COLOR_NONE );		// debug
		//OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, LX_LOGM_LEVEL_TRACE, DBG_COLOR_GREEN );		// trace
		//OS_DEBUG_EnableModuleByIndex ( g_gfx_debug_fd, LX_LOGM_LEVEL_TRACE + 1, DBG_COLOR_NONE );		// user macro
	}

	_gSeInfo.chip = lx_chip_rev();
	_gSeInfo.platform = lx_chip_plt();

#else	// _SE_STANDALONE_

	_gSeInfo.chip = 0;
	_gSeInfo.platform = 0;

#endif	// _SE_STANDALONE_

	SE_InitCfg();

#if 0	// Currently Not Used
	switch (_gSeInfo.platform) {
		case LX_CHIP_PLATFORM_GP :
			break;

		case LX_CHIP_PLATFORM_COSMO :
			break;

		default :
			SE_WARN("Unknown Platform Setting : Use default\n");
			break;
	}

	switch (_gSeInfo.chip) {
		case LX_CHIP_REV(L9,A0):
		case LX_CHIP_REV(L9,A1):
		case LX_CHIP_REV(L9,B0):
		case LX_CHIP_REV(L9,B1):
		case LX_CHIP_REV(H13,A0):
		case LX_CHIP_REV(H13,A1):
		case LX_CHIP_REV(H13,B0):
		case LX_CHIP_REV(M14,A0):
		case LX_CHIP_REV(M14,A1):
		case LX_CHIP_REV(H14,A0):
			break;

		default :
			SE_WARN("Unknown Chip Setting : Use default\n");
			break;
	}
#endif

	// for Sync of tz operation thread
	init_completion(&_gSeInfo.compTzOperationStart);
	init_completion(&_gSeInfo.compTzOperationEnd);

	// for Operations
	OS_InitMutex(&_gSeInfo.lock, OS_SEM_ATTR_DEFAULT);
	OS_InitMutex(&_gSeInfo.msgLock, OS_SEM_ATTR_DEFAULT);

	// Thread create
	_gSeInfo.pTzOperationThread = kthread_create(smc_kthread, NULL, "smc_kthread");
	if (IS_ERR(_gSeInfo.pTzOperationThread)) {
		SE_ERROR("while kthread_create()\n");
		_gSeInfo.pTzOperationThread = NULL;
		return -EIO;
	}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0))

	// Set Real-Time Priority
	{
		struct sched_param param = { 0 };

		param.sched_priority = SMC_THREAD_SCHED_NORMAL_PRIORITY;
		if (sched_setscheduler(_gSeInfo.pTzOperationThread, SCHED_NORMAL, &param)!=0) {
			SE_ERROR("Can't change priority\n");
		}
	}
#else

	sched_set_normal(_gSeInfo.pTzOperationThread, 0);

#endif

	// Start thread
	wake_up_process(_gSeInfo.pTzOperationThread);

	// Register Driver
	if (platform_driver_register(&_se_driver)) {
		SE_ERROR("platform_driver_register error\n");
	}
	else {
		if (platform_device_register(&_se_device)) {
			SE_ERROR("platform_device_register error\n");
			platform_driver_unregister(&_se_driver);
		}
 	}

	internal_dev = &_se_device.dev;

#ifndef CFG_REE_KDRV_RUTA_KDRV
	// Register Device
	_gSeInfo.devNum = MKDEV(SE_MAJOR, SE_MINOR);
	SE_CHECK(register_chrdev_region(_gSeInfo.devNum, 1, SE_MODULE), return -EIO);
	cdev_init(&_gSeInfo.cDev, &_gSeInfo.fileOperations);
	SE_CHECK(cdev_add(&_gSeInfo.cDev, _gSeInfo.devNum, 1), return -EIO);
	OS_CreateDeviceClass(_gSeInfo.devNum, "%s%d", SE_MODULE, 0);
#else
	/* 
 	 * /dev/lg/se0 
 	 * /dev/lg/se1
 	 */
	for(mi = 0; mi < 2; mi++) {
		_gSeInfo.devNum[mi] = MKDEV(SE_MAJOR, mi);
		SE_CHECK(register_chrdev_region(_gSeInfo.devNum[mi], 1, SE_MODULE), return -EIO);
		cdev_init(&_gSeInfo.cDev[mi], &_gSeInfo.fileOperations);
		SE_CHECK(cdev_add(&_gSeInfo.cDev[mi], _gSeInfo.devNum[mi], 1), return -EIO);
		OS_CreateDeviceClass(_gSeInfo.devNum[mi], "%s%d", SE_MODULE, mi);
	}

	if (ree_ruta_kdrv_init() < 0) {
		
		return -ENOMEM;
	}

#endif

#if (SE_USE_NET_LINK==1)
	// NetLink Socket
	{
		struct netlink_kernel_cfg cfg = {
			.input = _SE_nlRecvMsg,
		};

		_gSeInfo.pNlSock = netlink_kernel_create(&init_net, SE_NETLINK, &cfg);
		SE_CHECK(_gSeInfo.pNlSock==NULL, ;);
	}
#endif

	// initialize proc system
	SE_PROC_Init();

	return 0;
}

void SE_Cleanup(void)
{
	// cleanup proc system
	SE_PROC_Cleanup();

	// Stop Thread
	if (_gSeInfo.pTzOperationThread!=NULL) {
		kthread_stop(_gSeInfo.pTzOperationThread);
		complete(&_gSeInfo.compTzOperationStart);
		_gSeInfo.pTzOperationThread = NULL;
	}

	// iounmap
	if (_gSeInfo.pWaitMap!=NULL)
		vunmap_phys(_gSeInfo.pWaitMap);

#if (SE_USE_NET_LINK==1)
	// Release NetLink Socket
	netlink_kernel_release(_gSeInfo.pNlSock);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(KDRV_GLOBAL_LINK) || defined(MAKE_SE_MODULE)
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP) && !defined(MAKE_SE_MODULE)
user_initcall_grp("kdrv",SE_Init);
#else
module_init(SE_Init);
#endif
module_exit(SE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("SE driver");
MODULE_LICENSE("GPL");
#endif
/** @} */

