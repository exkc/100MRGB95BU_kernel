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
 *  misc driver for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-01-07
 *  @note		Additional information.
 */

#include <linux/freezer.h>

#include "te_impl.h"

#define MONITOR_INTERVAL		20	/* ms */
#define MIN_TIMER_INTERVAL		50	/* ms */

enum te_timer_type {
	TE_TIMER_THREAD = 0,
	TE_TIMER_WORKQUEUE,
};

struct te_timer {
	bool used;
	bool oneshot;
	bool halt;
	u32 interval;
	void (*func)(void *);
	void *arg;
	u64 timeout;
	enum te_timer_type type;

	struct list_head list;
	struct delayed_work work;
};

static DEFINE_MUTEX(timer_lock);
static DEFINE_MUTEX(halt_lock);

static void timer_work(struct work_struct *work)
{
	struct te_timer *t = container_of(work, struct te_timer, work.work);

	if (t->func)
		t->func(t->arg);

	if (!t->oneshot) {
		queue_delayed_work(system_freezable_wq, &t->work,
				   msecs_to_jiffies(t->interval));
	} else {
		//t->used = false; //not needed
	}
}

static struct te_timer *create_timer(struct te_device *dev, u32 interval,
				     bool oneshot, enum te_timer_type type,
				     void (*func)(void *), void *arg)
{
	struct te_timer *timer;

	timer = kzalloc(sizeof(*timer), GFP_KERNEL);
	CHECK_ERROR(!timer, return NULL, "no memory");

	if (interval < MIN_TIMER_INTERVAL)
		interval = MIN_TIMER_INTERVAL;

	timer->interval = interval;
	timer->oneshot = oneshot;
	timer->func = func;
	timer->arg = arg;
	timer->type = type;

	if (type == TE_TIMER_THREAD) {
		timer->used = true;
		timer->timeout = te_get_ms_tick() + interval;

		mutex_lock(&timer_lock);
		list_add_tail(&timer->list, &dev->timer.list);
		mutex_unlock(&timer_lock);
	} else {
		INIT_DELAYED_WORK(&timer->work, timer_work);
		queue_delayed_work(system_freezable_wq, &timer->work,
				   msecs_to_jiffies(timer->interval));
	}

	return timer;
}

/**
 * te_add_timer - It will create a timer and invoke a func every interval time.
 * @interval: timeout in ms
 * @func: the function to call when timer expires
 * @arg: argument passed to func
 *
 * The function callback is called in normal thread NOT isr when timer expries
 *
 * Return: pointer to struct te_timer on success, or NULL on error.
 */
struct te_timer *te_add_timer(struct te_device *dev, u32 interval,
			      void (*func)(void *), void *arg)
{
	return create_timer(dev, interval, false, TE_TIMER_THREAD, func, arg);
}

/**
 * te_add_oneshot_timer - It will create a timer and invoke a func one time
 * @timeout: timeout in ms
 * @func: the function to call when timer expires
 * @arg: argument passed to func
 *
 * The function callback is called in normal thread NOT isr when timer expries
 *
 * Return: pointer to struct te_timer on success, or NULL on error.
 */
struct te_timer *te_add_oneshot_timer(struct te_device *dev, u32 timeout,
				      void (*func)(void *), void *arg)
{
	return create_timer(dev, timeout, true, TE_TIMER_THREAD, func, arg);
}

/**
 * te_add_workqueue_timer - It will create a workqueue and invoke a func every
 * interval time.
 * @time: timeout in ms (interval for repeat)
 * @func: the function to call when timer expires
 * @arg: argument passed to func
 *
 * The function callback is called in normal thread NOT isr when timer expries
 *
 * Return: pointer to struct te_timer on success, or NULL on error.
 */
struct te_timer *te_add_workqueue_timer(struct te_device *dev, u32 time,
					void (*func)(void *), void *arg)
{
	return create_timer(dev, time, false, TE_TIMER_WORKQUEUE, func, arg);
}

/**
 * te_add_oneshot_workqueue_timer - It will create a workqueue and invoke a func
 * only one time
 * @time: timeout in ms
 * @func: the function to call when timer expires
 * @arg: argument passed to func
 *
 * The function callback is called in normal thread NOT isr when timer expries
 *
 * Return: pointer to struct te_timer on success, or NULL on error.
 */
struct te_timer *te_add_oneshot_workqueue_timer(struct te_device *dev, u32 time,
						void (*func)(void *),
						void *arg)
{
	return create_timer(dev, time, true, TE_TIMER_WORKQUEUE, func, arg);
}

void te_del_timer(struct te_timer *timer)
{
	if (timer->type == TE_TIMER_THREAD) {
		mutex_lock(&timer_lock);
		list_del(&timer->list);
		mutex_unlock(&timer_lock);
	} else {
		cancel_delayed_work_sync(&timer->work);
	}

	kfree(timer);
}

static int timer_thread(void *param)
{
	bool frozen, do_func;
	struct te_timer *t;
	void (*func)(void *) = NULL;
	void *arg;
	u64 ctime;
	struct te_device *dev = param;

	set_freezable();

	while (!kthread_freezable_should_stop(&frozen)) {
		ctime = te_get_ms_tick();
		mutex_lock(&halt_lock);

		if (dev->timer.halt) { // prevent to run timer list
			mutex_unlock(&halt_lock);
			msleep(MONITOR_INTERVAL);
			continue;
		}

		mutex_lock(&timer_lock);

		list_for_each_entry(t, &dev->timer.list, list) {
			if (t->used && ctime >= t->timeout) {
				if (t->oneshot)
					t->used = false;
				else
					t->timeout = ctime + t->interval;

				func = t->func;
				arg = t->arg;
				break;	/* execute only one timer */
			}
		}
		mutex_unlock(&timer_lock);

		if (func) {
			func(arg);
			func = NULL;
			do_func = true;
		} else {
			do_func = false;
		}

		mutex_unlock(&halt_lock);

		if (!do_func)
			msleep(MONITOR_INTERVAL);
	}

	return 0;
}

static int timer_dev_init(struct te_device *dev)
{
	int ret;

	INIT_LIST_HEAD(&dev->timer.list);

	dev->timer.thread = kthread_run(timer_thread, dev, "te_timer");
	if (IS_ERR(dev->timer.thread)) {
		ret = PTR_ERR(dev->timer.thread);
		log_error("failed to run kthread(%d)", ret);
		return ret;
	}

	return 0;
}

//cannot called this by timer call (use workqueue type timer)
void te_halt_timer(struct te_device *dev, bool halt)
{
	mutex_lock(&halt_lock);
	dev->timer.halt = halt;
	mutex_unlock(&halt_lock);

	log_noti("timer %s", halt ? "halted" : "recovered");
}

static void timer_dev_release(struct te_device *dev)
{
	struct te_timer *t, *t2;

	kthread_stop(dev->timer.thread);
	list_for_each_entry_safe(t, t2, &dev->timer.list, list) {
		kfree(t);
	}
}

const struct te_sub_driver te_timer_driver = {
	.name = "te_timer",
	.early_init = timer_dev_init,
	.release = timer_dev_release,
};
