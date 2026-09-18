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
 *  ipc driver
 *
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-02-02
 *  @note		Additional information.
 */

#include <lg1k/te/mcu.h>

#include "te_impl.h"
#include "ipc_core.h"

#define USE_IPC_TIMEOUT_CHECKER	/* check ipc queue evenif ipc interrupt not raised */

#if CONFIG_LX_BOARD_FPGA
#define IPC_MAX_TIMEOUT				(100*5)
#else
#define IPC_MAX_TIMEOUT				100
#endif

struct ipc_stats {
	u32 send_msg;
	u32 send_queue_overflow;
	u32 recv_msg;
	u32 ack_msg;
	u32 log_msg;
	u32 timeout;

	u8 err_msg_cnt;
};

struct ipc_dev {
	volatile bool enabled;

	u16 seq_num;

	struct mutex mutex;
	spinlock_t spinlock;
#ifdef USE_IPC_TIMEOUT_CHECKER
	struct completion timeout_completion;
	struct work_struct timeout_work;
#endif

	struct list_head wait_list_head;
	spinlock_t wait_list_lock;

	struct ipc_stats stats;

	struct ipc ipc;

};

struct ipc_wait {
	u16 id;
	u16 return_value;

	struct list_head list;
	struct completion completion;
};

static void process_recv_queue(struct ipc *ipc);

static int te_ipc_err_cnt = 5;
module_param(te_ipc_err_cnt, int, 0644);

static int check_ready(struct ipc_dev *dev, struct ipc *ipc)
{
	unsigned long timeout_jiffies;

	timeout_jiffies = jiffies + msecs_to_jiffies(IPC_MAX_TIMEOUT);

	while (time_is_after_jiffies(timeout_jiffies)) {
		if (!dev->enabled)
			return -EINVAL;

		if (ipc->state == IPC_STATE_READY)
			return 0;

		mutex_unlock(&dev->mutex);
		msleep(1);
		mutex_lock(&dev->mutex);
	}

	process_recv_queue(ipc);

	if (ipc->state == IPC_STATE_READY)
		return 0;

	return -ETIME;
}

static void init_ack_waiting(struct ipc_dev *dev, struct ipc *ipc,
			     struct ipc_wait *wait)
{
	unsigned long flag;

	wait->id = dev->seq_num;
	init_completion(&wait->completion);

	/* add to wait list */
	spin_lock_irqsave(&dev->wait_list_lock, flag);
	list_add_tail(&wait->list, &dev->wait_list_head);
	spin_unlock_irqrestore(&dev->wait_list_lock, flag);
}

#ifdef USE_IPC_TIMEOUT_CHECKER
static void ack_timeout_work(struct work_struct *work)
{
	struct ipc_dev *dev;

	dev = container_of(work, struct ipc_dev, timeout_work);

	process_recv_queue(&dev->ipc);

	complete(&dev->timeout_completion);
}

static int check_ipc_timeout(struct ipc_dev *dev, struct ipc_wait *wait)
{
	int ret;

	mutex_lock(&dev->mutex);
	reinit_completion(&dev->timeout_completion);
	schedule_work(&dev->timeout_work);
	ret = wait_for_completion_timeout(&dev->timeout_completion,
					  msecs_to_jiffies(IPC_MAX_TIMEOUT));
	mutex_unlock(&dev->mutex);

	if (ret <= 0) {
		log_ipc("%s : schedule_work not processed - "
			"maybe system crashed !!!\n", dev->ipc.name);
		return ret;
	}

	if (try_wait_for_completion(&wait->completion)) {
		if (dev->stats.err_msg_cnt < te_ipc_err_cnt) {
			log_noti("%s : irq not raised but ipc completed\n",
				 dev->ipc.name);
			dev->stats.err_msg_cnt++;

			if (dev->stats.err_msg_cnt >= te_ipc_err_cnt) {
				log_error("disable ipc message(cnt: %d/%d)\n",
					  dev->stats.err_msg_cnt,
					  te_ipc_err_cnt);
			}
		}
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}
#endif

static const char* ipc_error_str(IPC_RET_TYPE_T err)
{
	switch (err) {
		case IPC_RET_OK: return "OK";
		case IPC_RET_NOT_OK: return "NOT OK";
		case IPC_RET_INVALID_MSG: return "Invalid Message";
		case IPC_RET_NOT_SUPPORTED: return "Not supported";
		case IPC_RET_BUSY_NOT_OK: return "Busy";
		default: return "Unknown";
	}
}

static int wait_for_ack(struct ipc_dev *dev, struct ipc *ipc,
			struct ipc_wait *wait)
{
	int rc, ret;
	int timout_jiffies;
	unsigned long flag;

	timout_jiffies = msecs_to_jiffies(IPC_MAX_TIMEOUT);

	rc = wait_for_completion_timeout(&wait->completion, timout_jiffies);
#ifdef USE_IPC_TIMEOUT_CHECKER
	if (rc <= 0) {
		rc = check_ipc_timeout(dev, wait);
	} else if (dev->stats.err_msg_cnt > 0) {
		if (dev->stats.err_msg_cnt >= te_ipc_err_cnt) {
			log_noti("reenable ipc message\n");
			dev->stats.err_msg_cnt = 0;
		} else {
			dev->stats.err_msg_cnt--;
		}
	}
#endif

	if (rc <= 0) {
		struct ipc_wait *wait_in_list;

		log_error("%s : ipc not completed(%s)\n",
			  ipc->name, (rc == 0) ? "timeout" : "signal");

		/* remove from wait list */
		spin_lock_irqsave(&dev->wait_list_lock, flag);

		/* check wait in wait_list */
		list_for_each_entry(wait_in_list, &dev->wait_list_head, list) {
			if (wait_in_list == wait) {
				list_del(&wait_in_list->list);
				break;
			}
		}
		spin_unlock_irqrestore(&dev->wait_list_lock, flag);

		if (rc == 0) {
			dev->stats.timeout++;
			ret = -ETIME;
		} else {
			ret = rc;	/* -ERESTARTSYS */
		}
	} else {
		if (wait->return_value != IPC_RET_OK) {
			log_error("%s : ipc return(%d) error(%s)\n", ipc->name,
				  wait->return_value,
				  ipc_error_str(wait->return_value));
			if (wait->return_value == IPC_RET_BUSY_NOT_OK) {	//handle for filter request
				ret = -EBUSY;
			} else {
				ret = -EIO;
			}
		} else {
			log_ipc("%s : ipc %dms elapsed\n", ipc->name,
				jiffies_to_msecs(timout_jiffies - rc));
			ret = 0;
		}
	}

	return ret;
}

int _TE_IPC_Send(struct ipc *ipc, u16 type, const void *data, u32 size)
{
	int ret = 0;
	volatile IPC_MSG_T *msg;
	IPC_MSG_HEADER_T header;
	u32 head, tail, next_head;
	struct ipc_wait wait;
	struct ipc_queue *q;
	int rc;
	struct ipc_dev *dev;

	dev = container_of(ipc, struct ipc_dev, ipc);

	mutex_lock(&dev->mutex);

	/* check mcu ready */
	if (!dev->enabled) {
		log_error("%s : device not enabled", ipc->name);
		mutex_unlock(&dev->mutex);
		return -EPERM;
	}

	if (ipc->state != IPC_STATE_READY) {
		rc = check_ready(dev, ipc);
		if (rc != 0) {
			log_error("%s : not received ready signal", ipc->name);
			mutex_unlock(&dev->mutex);
			return rc;
		}
	}

	q = &ipc->send_queue;

	if (q->count > 1) {
		head = *q->head;
		tail = *q->tail;

		next_head = (head + 1) % q->count;
		if (next_head == tail) {
			log_error("%s : send queue full !\n", ipc->name);
			dev->stats.send_queue_overflow++;
			mutex_unlock(&dev->mutex);
			return -EBUSY;
		}
		msg = (IPC_MSG_T *)(q->data + head * q->msg_size);
	} else {
		next_head = 0;	/* to remove warning */
		msg = (IPC_MSG_T *)q->data;
	}

	/* save ipc command to the message buffer */
	/* !!! CAUTION
	 * if ipc registers are used as message buffer then have to access the data in 32bit unit */
	header.id = dev->seq_num;
	header.type = type;
	header.payload_len = size;

	msg->header = header;
	if (size > 0)
		memcpy((void *)msg->payload, data, size);

	if (IS_IPC_ACK_MODE(type)) {
		init_ack_waiting(dev, ipc, &wait);
	}

	dev->seq_num++;
	dev->stats.send_msg++;

	/* increase head. it means mcu can read messages anytime evenif ipc event not given */
	if (q->count > 1)
		*q->head = next_head;

	wmb();

	ipc->irq_send(ipc);

	mutex_unlock(&dev->mutex);

	if (IS_IPC_ACK_MODE(type)) {
		ret = wait_for_ack(dev, ipc, &wait);
	}

	return ret;
}

static int ipc_msg_ack(struct ipc *ipc, IPC_MSG_T *msg)
{
	unsigned long flag;
	struct ipc_wait *wait;
	u16 id;
	IPC_MSG_ACK_T *ack_msg = (IPC_MSG_ACK_T *)msg->payload;
	bool found = false;
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	id = ack_msg->id;

	spin_lock_irqsave(&dev->wait_list_lock, flag);
	list_for_each_entry(wait, &dev->wait_list_head, list) {
		if (wait->id == id) {
			wait->return_value = ack_msg->ret_value;

			list_del(&wait->list);
			complete(&wait->completion);
			found = true;
			break;
		}
	}
	spin_unlock_irqrestore(&dev->wait_list_lock, flag);

	if (unlikely(!found)) {
		log_warning("%s no wait list. id:%d\n", ipc->name, id);
	}

	return 0;
}

static void remove_all_in_wait_list(struct ipc_dev *dev)
{
	unsigned long flag;
	struct ipc_wait *wait, *wait2;

	/* remove all in wait list */
	spin_lock_irqsave(&dev->wait_list_lock, flag);
	list_for_each_entry_safe(wait, wait2, &dev->wait_list_head, list) {
		wait->return_value = 0xFFFF;

		list_del(&wait->list);
		complete(&wait->completion);
	}
	spin_unlock_irqrestore(&dev->wait_list_lock, flag);
}

static void process_recv_queue(struct ipc *ipc)
{
	int i;
	IPC_MSG_T *msg;
	IPC_MSG_HEADER_T *h;
	struct ipc_queue *q;
	u32 tail;
	unsigned long flag;
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	spin_lock_irqsave(&dev->spinlock, flag);
	for (i = 0; i < MAX_RECV_QUEUE; i++) {
		q = &ipc->recv_queue[i];

		tail = *q->tail;

		if (*q->head >= q->count) {
			log_error("%s receive queue[%d] broken !!!\n",
				  ipc->name, i);
			*q->head = tail;	/* reset queue head */
			continue;
		}

		while (tail != *q->head) {
			msg = (IPC_MSG_T *)(q->data + tail * q->msg_size);
			h = &msg->header;

			if (h->id != q->seqnum) {
				log_error("%s seqnum[%d](%d) != expected(%d)\n",
					  ipc->name, i, h->id, q->seqnum);
			}
			q->seqnum = h->id + 1;

			if (h->type == IPC_TYPE_ACK_MCU) {
				ipc_msg_ack(ipc, msg);
				dev->stats.ack_msg++;
			} else {
				_TE_IPC_Recv(ipc, msg);
				dev->stats.recv_msg++;
			}
			tail = (tail + 1) % q->count;
		}
		*q->tail = tail;
	}
	spin_unlock_irqrestore(&dev->spinlock, flag);

}

static irqreturn_t ipc_interrupt(int irq, void *dev_id)
{
	struct ipc *ipc = (struct ipc *)dev_id;

	if (!ipc->irq_status(ipc)) {
		return IRQ_NONE;
	}
	ipc->irq_clear(ipc);

	process_recv_queue(ipc);

	return IRQ_HANDLED;
}

struct ipc *_TE_IPC_Create(void)
{
	struct ipc_dev *dev;
	struct ipc *ipc;

	/* sizeof(struct ipc_dev) = 1048 - 2018.12.11 */
	dev = kzalloc(sizeof(struct ipc_dev), GFP_KERNEL);
	CHECK_ERROR(!dev, return NULL, "can't alloc memory");

	ipc = &dev->ipc;

	mutex_init(&dev->mutex);
	spin_lock_init(&dev->spinlock);
	INIT_LIST_HEAD(&dev->wait_list_head);
	spin_lock_init(&dev->wait_list_lock);

#ifdef USE_IPC_TIMEOUT_CHECKER
	init_completion(&dev->timeout_completion);
	INIT_WORK(&dev->timeout_work, ack_timeout_work);
#endif

	return ipc;
}

void _TE_IPC_Destroy(struct ipc *ipc)
{
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	kfree(dev);
}

int _TE_IPC_Init(struct ipc *ipc)
{
	int ret;
//      struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	/* check functions */
	CHECK_NULL_PARAM(ipc->reg_write);
	CHECK_NULL_PARAM(ipc->reg_read);
	CHECK_NULL_PARAM(ipc->enable);
	CHECK_NULL_PARAM(ipc->disable);
	CHECK_NULL_PARAM(ipc->irq_status);
	CHECK_NULL_PARAM(ipc->irq_clear);
	CHECK_NULL_PARAM(ipc->irq_send);
	CHECK_NULL_PARAM(ipc->set_user_addr);
	CHECK_NULL_PARAM(ipc->check_alive);
	CHECK_NULL_PARAM(ipc->set_logmask);

	/* initialize interrupt */
#ifdef TE_EMULATOR
	ret = TE_EMUL_CPU_IrqRequest(ipc->irq_num, ipc_interrupt, 0, ipc->name,
				     ipc);
#else
	ret = request_irq(ipc->irq_num, ipc_interrupt, 0, ipc->name, ipc);
#endif
	CHECK_ERROR(ret < 0, return ret, "dev:%s, request_irq failed(%d)\n",
		    ipc->name, ret);

	return 0;
}

int _TE_IPC_Enable(struct ipc *ipc)
{
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	mutex_lock(&dev->mutex);
	if (!dev->enabled) {
		// TODO: do something
		dev->enabled = true;
	}
	mutex_unlock(&dev->mutex);

	/* enable ipc */
	ipc->enable(ipc);

	return 0;
}

int _TE_IPC_Disable(struct ipc *ipc)
{
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	ipc->disable(ipc);

	mutex_lock(&dev->mutex);
	if (dev->enabled) {
		remove_all_in_wait_list(dev);
		memset(&dev->stats, 0, sizeof(dev->stats));
		dev->enabled = false;
	}
	mutex_unlock(&dev->mutex);

	return 0;
}

int _TE_IPC_CheckReady(struct ipc *ipc)
{
	int ret = -EIO;
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	mutex_lock(&dev->mutex);
	if (dev->enabled) {
		if (ipc->state == IPC_STATE_READY)
			ret = 0;
	}
	mutex_unlock(&dev->mutex);

	return ret;
}

int _TE_IPC_GetStatus(struct ipc *ipc, struct ipc_status *status)
{
	struct ipc_dev *dev = container_of(ipc, struct ipc_dev, ipc);

	mutex_lock(&dev->mutex);
	if (!dev->enabled) {
		memset(status, 0, sizeof(*status));
		mutex_unlock(&dev->mutex);
		return -EPERM;
	}

	status->ready = (ipc->state == IPC_STATE_READY) ? true : false;
	status->fw_ver = ipc->fw_ver;
	status->ipc_ver = ipc->ipc_ver;

	status->send_msg_count = dev->stats.send_msg;
	status->recv_msg_count = dev->stats.recv_msg;
	status->timeout_count = dev->stats.timeout;

	status->send_queue_overflow = dev->stats.send_queue_overflow;
	status->recv_queue_overflow[0] =
	    ipc->reg_read(ipc, IPC_REG_OFFSET_MCU_SEND_QUEUE0_OVF);
	status->recv_queue_overflow[1] =
	    ipc->reg_read(ipc, IPC_REG_OFFSET_MCU_SEND_QUEUE1_OVF);
	status->mcu_int_queue_overflow =
	    ipc->reg_read(ipc, IPC_REG_OFFSET_MCU_INT_QUEUE_OVF);

	mutex_unlock(&dev->mutex);

	return 0;
}

int _TE_IPC_CheckAlive(struct ipc *ipc)
{
	int rc;

	rc = ipc->check_alive(ipc);

	return rc;
}

int _TE_IPC_SetLogMask(struct ipc *ipc, u16 module_mask, u16 level_mask)
{
	return ipc->set_logmask(ipc, module_mask, level_mask);
}

int _TE_IPC_EnableLogMask(struct ipc *ipc, u16 module_mask, u16 level_mask)
{
	int rc, i;
	u16 old_val, new_val;

	for (i = 0; i < IPC_LOG_MODULE_MAX; i++) {
		if (module_mask & (0x1 << i)) {
			old_val = ipc->logmask[i];
			new_val = old_val | level_mask;

			if (old_val != new_val) {
				rc = ipc->set_logmask(ipc, (0x1 << i), new_val);
				if (rc != 0)
					return rc;
			}
		}
	}

	return 0;
}

int _TE_IPC_DisableLogMask(struct ipc *ipc, u16 module_mask, u16 level_mask)
{
	int rc, i;
	u16 old_val, new_val;

	for (i = 0; i < IPC_LOG_MODULE_MAX; i++) {
		if (module_mask & (0x1 << i)) {
			old_val = ipc->logmask[i];
			new_val = old_val & ~level_mask;

			if (old_val != new_val) {
				rc = ipc->set_logmask(ipc, (0x1 << i), new_val);
				if (rc != 0)
					return rc;
			}
		}
	}

	return 0;
}

int _TE_IPC_SetLogLevel(struct ipc *ipc, u8 module, u16 level_mask)
{
	CHECK_PARAM(module >= IPC_LOG_MODULE_MAX, "invalid module(%d)", module);

	return ipc->set_logmask(ipc, (0x1 << module), level_mask);
}

int _TE_IPC_GetLogLevel(struct ipc *ipc, u8 module, u16 *level_mask)
{
	CHECK_PARAM(module >= IPC_LOG_MODULE_MAX, "invalid module(%d)", module);

	*level_mask = ipc->logmask[module];

	return 0;
}

int _TE_IPC_SetConsoleEnable(struct ipc *ipc, bool enable)
{
	IPC_MSG_DEBUG_CONSOLE_T msg;

	msg.enable = enable;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_CONSOLE, &msg, sizeof(msg));
}
