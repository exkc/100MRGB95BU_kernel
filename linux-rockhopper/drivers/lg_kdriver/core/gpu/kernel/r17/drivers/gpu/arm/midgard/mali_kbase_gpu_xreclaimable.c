/*
 *
 * (C) COPYRIGHT 2010-2016 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */



/*
 * gpu xreclaimable API implementations
 */

#include <mali_kbase_gpu_xreclaimable.h>

static enum hrtimer_restart
gpu_xreclaimable_callback(struct hrtimer *timer)
{
	struct kbase_device *kbdev;
	unsigned long flags;

	kbdev = container_of(timer, struct kbase_device,
						time_xreclaimable);

	queue_work(kbdev->xreclaimable_wq, &kbdev->xreclaimable_work);

	spin_lock_irqsave(&kbdev->time_xreclaimable_lock, flags);

	if(kbdev->time_xreclaimable_running)
		hrtimer_start(&kbdev->time_xreclaimable,
			HR_TIMER_DELAY_MSEC(GPU_XRECLAIMABLE_PERIOD),
			HRTIMER_MODE_REL);

	spin_unlock_irqrestore(&kbdev->time_xreclaimable_lock, flags);

	return HRTIMER_NORESTART;
}

static void kbase_gpu_xreclaimable_wq(struct work_struct *data)
{
	struct kbase_device *kbdev;
	unsigned long xreclaimable_size;

	kbdev = container_of(data, struct kbase_device, xreclaimable_work);

	xreclaimable_size = get_gpu_pool_memory() << PAGE_SHIFT;
	low_mem_notify_set_xreclaimable_size(kbdev->gpu_xr, xreclaimable_size);
}

void kbase_gpu_xreclaimable_init(struct kbase_device *kbdev)
{
	struct workqueue_struct *wq;

	wq = alloc_workqueue("kbase_xreclaimabe",
			WQ_HIGHPRI | WQ_UNBOUND, 1);

	if (!wq)
		return;

	kbdev->xreclaimable_wq = wq;
	INIT_WORK(&kbdev->xreclaimable_work, kbase_gpu_xreclaimable_wq);
	hrtimer_init(&kbdev->time_xreclaimable,
			CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	spin_lock_init(&kbdev->time_xreclaimable_lock);

	kbdev->time_xreclaimable_running = true;
	kbdev->time_xreclaimable.function = gpu_xreclaimable_callback;
	hrtimer_start(&kbdev->time_xreclaimable,
			HR_TIMER_DELAY_MSEC(GPU_XRECLAIMABLE_PERIOD),
			HRTIMER_MODE_REL);
}

void kbase_gpu_xreclaimable_term(struct kbase_device *kbdev)
{
	unsigned long flags;

	spin_lock_irqsave(&kbdev->time_xreclaimable_lock, flags);
	kbdev->time_xreclaimable_running = false;
	spin_unlock_irqrestore(&kbdev->time_xreclaimable_lock, flags);
	hrtimer_cancel(&kbdev->time_xreclaimable);

	flush_workqueue(kbdev->xreclaimable_wq);
	destroy_workqueue(kbdev->xreclaimable_wq);
}
