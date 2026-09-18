/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file vbe_event.h
 *
 *  It is the header file for controling v4l2 BE driver.
 *
 *  @author
 *  @version
 *  @date
 *  @see
 */

#ifndef _VBE_EVENT_H
#define _VBE_EVENT_H

#include "vbe_cfg.h"

/**
* -. Disp CLK Change Scenario (http://jira.lge.com/issue/browse/AVTASK-1506)
* < clk change flag on stage : stage 0 (vbe_evt_state_normal), stage 1 (vbe_evt_state_rcv_chg_clk_n_wait), stage 2 (vbe_evt_state_stop_evt_n_ctl_off), stage 3 (vbe_evt_state_stop_evt_n_wake_up), step 4 (vbe_evt_state_chg_clk_done), >
* 01. ovi : change clk at random point in time, start -> "change clk" noti to vbe -> wait_work(timeout:100ms)
* 02. VBE: At any point, "I want to change CLK" Noti is received - > CLK Change flag on 1 (I will change CLK in the previous step)
* 03. vbe : vactive rising(T), led sync meet -> clk Change flag on to 2 if flag on is 1 - > Step 2 :pwm settingstop flag on + pwm en reg. set off + event does not occur (step 1~4)
* 04. hw : vsync falling(T), pwm off updated
* 05. vbe : Vactive Rising(T+1), led sync meets -> clk Change flag on is 2 then change to 3 -> Step 3: Sees PWM off written in HW at the time of view, wakeup ovi + event does not occur (stage 1~4)
* 06. ovi : vactive rising(T+1+a), change ovi settings such as pll when wakeup (w/ ms delay) - change > at the end of "done" noti to vbe (w/ new disp clk value)
* 07. vbe : vactive rising(T+1+a+sums), receive "done" noti -> clk change flag if flag on is 3 then change to 4 -> step 4: save new disp clk value, set pwmstop flag off
* 20. vbe : vactive rising(T+2), led sync meets -> clk Change flag on is 4 then change to 0 -> step 0:event occurs
* 21. user: vactive rising(T+2+a), receive event and lower duty
* 22. VBE: When you receive vactive rising(T+2+a+sums), pwm setting pwm on + pwm (w/ new clk value)
* 23. hw : vsync falling(T+2), pwm settings updated
* 24. Repeat the above 20~23 processes
**/

enum vbe_evt_state {
    vbe_evt_state_none = 0,
    vbe_evt_state_normal,
    vbe_evt_state_rcv_chg_clk_n_wait,
    vbe_evt_state_stop_evt_n_ctl_off,
    vbe_evt_state_stop_evt_n_wake_up,
    vbe_evt_state_chg_clk_done,
    vbe_evt_state_max
};

extern int vbe_event_init(void);
extern int vbe_evt_noti_chg_clk_wait(void);
extern int vbe_evt_noti_chg_clk_done(unsigned int clk);
extern int vbe_led_subscribe_event(struct vbe_priv *priv);
extern int vbe_led_unsubscribe_event(struct vbe_priv *priv);
extern int vbe_led_release(struct file *flie);
extern int vbe_led_wakeup(struct vbe_dev *drv, int sig);

#endif  /* _VBE_EVENT_H */

