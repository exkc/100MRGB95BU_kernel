/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

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
 *  dpc file for VBE device
 *
 *  author
 *  version		1.0
 *  date		2025.03.12
 *  note
 *
 *  @addtogroup BE
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
#include <linux/init.h>
//#include <linux/wait.h>

#include "os_util.h"
#include "debug_util.h"
#include "be_dbg.h"
#include "vbe_dpc.h"
#include "vbe_dpc_algo.h"
#include "pwm_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum vbe_dpc_state {
    vbe_dpc_state_none = 0,
    vbe_dpc_state_normal,
    vbe_dpc_state_rcv_chg_clk_n_wait,
    vbe_dpc_state_stop_evt_n_ctl_off,
    vbe_dpc_state_stop_evt_n_wake_up,
    vbe_dpc_state_chg_clk_done,
    vbe_dpc_state_max
};

struct vbe_dpc_cfg {
	struct work_struct work;
	struct workqueue_struct *work_q;
	struct vbe_dpc_algo_param ap;
	LX_BE_PWM_PARAMS_T pwm;
	unsigned int fixclk;
	int cnt;
	int run;
	int prerun;
	unsigned int clk_cond;
	wait_queue_head_t clk_wq;
	unsigned int clk;
	unsigned int state;
};

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
static void _vbe_dpc_work(struct work_struct *work);

void vbe_dpc_status(struct seq_file *m, void* data);
int vbe_dpc_command(char* command);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct vbe_dpc_cfg _g_vbe_dpc_cfg;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
int vbe_dpc_init(void)
{
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;
	struct vbe_dpc_algo_param *ap = &p->ap;

	memset(p,0,sizeof(struct vbe_dpc_cfg));

	init_waitqueue_head(&p->clk_wq);

	p->work_q = create_singlethread_workqueue("vbe-dpc-wq");
	if (!p->work_q) {
		BE_ERROR("create work_q fail\n");
		return -1;
	}

	INIT_WORK(&p->work, _vbe_dpc_work);

	memset(&p->pwm,0,sizeof(p->pwm));
	p->pwm.portMask = 0x2;
	p->pwm.portParams[1].enable         = 0;
	p->pwm.portParams[1].lockModeEn     = 0;
	p->pwm.portParams[1].pwmOutput      = 1;
	p->pwm.portParams[1].scanningModeEn = 0;
	p->pwm.portParams[1].lowPowerModeEn = 0;
	p->pwm.portParams[1].adaptFreqEn    = 0;
	p->pwm.portParams[1].adaptFreqDb.freq_48nHz = 96;
	p->pwm.portParams[1].adaptFreqDb.freq_50nHz = 100;
	p->pwm.portParams[1].adaptFreqDb.freq_60nHz = 120;
	p->pwm.portParams[1].frequency = 5000;
	p->pwm.portParams[1].offset = 0;
	p->pwm.portParams[1].duty = 0;

	ap->fixapl = -1;
	ap->fixduty = -1;

	ap->lutx[0]  = 0   ;
	ap->lutx[1]  = 30  ;
	ap->lutx[2]  = 50  ;
	ap->lutx[3]  = 71  ;
	ap->lutx[4]  = 101 ;
	ap->lutx[5]  = 153 ;
	ap->lutx[6]  = 204 ;
	ap->lutx[7]  = 255 ;
	ap->lutx[8]  = 306 ;
	ap->lutx[9]  = 409 ;
	ap->lutx[10] = 511 ;
	ap->lutx[11] = 613 ;
	ap->lutx[12] = 716 ;
	ap->lutx[13] = 818 ;
	ap->lutx[14] = 921 ;
	ap->lutx[15] = 1023;

	ap->luty[0]  = 90;
	ap->luty[1]  =  0;
	ap->luty[2]  =  0;
	ap->luty[3]  =  3;
	ap->luty[4]  = 20;
	ap->luty[5]  = 20;
	ap->luty[6]  = 20;
	ap->luty[7]  = 20;
	ap->luty[8]  = 20;
	ap->luty[9]  = 20;
	ap->luty[10] = 20;
	ap->luty[11] = 20;
	ap->luty[12] = 20;
	ap->luty[13] = 20;
	ap->luty[14] = 20;
	ap->luty[15] = 13;

	BE_NOTI("done\n");
	return 0;
}

int vbe_dpc_noti_chg_clk_wait(void)
{
	int ret;
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;

	if (p->state == vbe_dpc_state_none) {
		BE_NOTI("skip\n");
		return 0;
	}

	p->state = vbe_dpc_state_rcv_chg_clk_n_wait;

	BE_NOTI("state to %d, wait_event\n",p->state);
	p->clk_cond = 0;
	ret = wait_event_interruptible_timeout(p->clk_wq,p->clk_cond,msecs_to_jiffies(50));
	if (ret == 0) {
		BE_NOTI("time out\n");
	}
	else if (ret < 0) {
		BE_NOTI("received signal\n");
	}
	else {
		BE_NOTI("wakeup\n");
	}

	return 0;
}

int vbe_dpc_noti_chg_clk_done(unsigned int clk)
{
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;

	if (p->state == vbe_dpc_state_none) {
		BE_NOTI("skip\n");
		return 0;
	}

	BE_PWM_HAL_SetClk(clk);
	p->clk = clk;
	p->state = vbe_dpc_state_chg_clk_done;

	return 0;
}

int vbe_dpc_sync_handler(void)
{
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;

	queue_work(p->work_q, &p->work);

	return 0;
}

static int vbe_dpc_work_prepare(struct vbe_dpc_cfg *p)
{
	if (!p) {
		BE_ERROR("p null\n");
		return -1;
	}

	if (p->prerun != p->run) {
		p->pwm.portParams[1].enable = p->run;
		p->prerun = p->run;
		p->state = (p->run)? vbe_dpc_state_normal:vbe_dpc_state_none;
		BE_NOTI("state to %d (run:%d)\n",p->state,p->run);
	}
	else if (p->state == vbe_dpc_state_rcv_chg_clk_n_wait) {
		BE_PWM_HAL_SetCtrlStop(1);
		p->state = vbe_dpc_state_stop_evt_n_ctl_off;
		BE_NOTI("state to vbe_dpc_state_stop_evt_n_ctl_off\n");
	}
	else if (p->state == vbe_dpc_state_stop_evt_n_ctl_off) {
		p->clk_cond = 1;
		wake_up_interruptible_all(&p->clk_wq);
		p->state = vbe_dpc_state_stop_evt_n_wake_up;
		BE_NOTI("state to vbe_dpc_state_stop_evt_n_wake_up\n");
	}
	else if (p->state == vbe_dpc_state_chg_clk_done) {
		BE_PWM_HAL_SetCtrlStop(0);
		p->state = vbe_dpc_state_normal;
		BE_NOTI("state to vbe_dpc_state_normal\n");
	}

	return 0;
}

static void _vbe_dpc_work(struct work_struct *work)
{
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;
	struct vbe_dpc_algo_param *ap = &p->ap;

	vbe_dpc_work_prepare(p);

	if (p->state != vbe_dpc_state_normal) {
		BE_PRINT_DPC("skip\n");
		return;
	}

	if (vbe_dpc_algo_update(ap)) {
		BE_ERROR("vbe_dpc_algo_update err\n");
		return;
	}

	p->pwm.portParams[1].duty = (ap->fixduty >= 0 && ap->fixduty <= 255)? (UINT32)ap->fixduty:ap->finalduty;
	if (BE_PWM_HAL_SetPwmParams(&p->pwm)) {
		BE_ERROR("BE_PWM_HAL_SetPwmParams err\n");
		return;
	}

	BE_PRINT_DPC("%s apl:%4d duty:%3d(%3d)\n",ap->run? "run":"stop",ap->readapl,p->pwm.portParams[1].duty,ap->finalduty);

	p->cnt = (p->cnt < 9999)? (p->cnt+1):0;
}

void vbe_dpc_status(struct seq_file *m, void* data)
{
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;
	struct vbe_dpc_algo_param *ap = &p->ap;
	unsigned int *l;

	seq_printf(m, "\n<usage>\n");
	seq_printf(m, "echo dpc run > command\n");
	seq_printf(m, "echo dpc stop > command\n");
	seq_printf(m, "echo dpc fixclk 673920000 > command\n");
	seq_printf(m, "(eg. 120:594000000, 144:673920000, 165:735815520)\n");
	seq_printf(m, "echo dpc fixclk off > command\n");
	seq_printf(m, "echo dpc cur2pre 1 > command\n");
	seq_printf(m, "echo dpc fixapl 1023 > command\n");
	seq_printf(m, "echo dpc fixapl off > command\n");
	seq_printf(m, "echo dpc fixduty 255 > command\n");
	seq_printf(m, "echo dpc fixduty off > command\n");
	seq_printf(m, "echo dpc dbgprint 3 > command\n");
	seq_printf(m, "echo dpc dbgprint off > command\n");
	seq_printf(m, "echo dpc iirgain 256 > command\n");
	seq_printf(m, "echo dpc lutx 0,30,50,71, 101,153,204,255, 306,409,511,613, 716,818,921,1023 > command\n");
	seq_printf(m, "echo dpc luty 90,0,0,3, 20,20,20,20, 20,20,20,20, 20,20,20,13 > command\n");
	seq_printf(m, "echo dpc luty 90,0,0,7, 53,53,53,53, 53,53,53,53, 53,53,34,13 > command\n");
	seq_printf(m, "echo dpc luty 90,255,232,212, 180,198,219,240, 219,175,136, 104,77,56,34,13 > command\n");
	seq_printf(m, "echo dpc luty 255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,255 > command\n");
	seq_printf(m, "echo 0xCC8E3518 > /proc/lg/base/reg_rd\n");

	seq_printf(m, "\n<status>\n");
	seq_printf(m, "dpc : %s fixclk:%d, cnt:%d\n",(ap->run)? "run":"stop",p->fixclk,p->cnt);
	seq_printf(m, "algo: cur2pre:%d, interval:%d, iirgain:%d, dbgprint:%d\n",ap->cur2pre,ap->interval,ap->iirgain,ap->dbgprint);
	seq_printf(m, "apl : fix:%d, read:%d, pre:%d, cur:%d, final:%d\n",ap->fixapl,ap->readapl,ap->preapl,ap->curapl,ap->finalapl);
	seq_printf(m, "duty: fix:%d, pre:%d, cur:%d, final:%d\n",ap->fixduty,ap->preduty,ap->curduty,ap->finalduty);
	l = ap->lutx;
	seq_printf(m, "lutx: %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d\n",\
		l[0],l[1],l[2],l[3], l[4],l[5],l[6],l[7], l[8],l[9],l[10],l[11], l[12],l[13],l[14],l[15]);
	l = ap->luty;
	seq_printf(m, "luty: %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d\n",\
		l[0],l[1],l[2],l[3], l[4],l[5],l[6],l[7], l[8],l[9],l[10],l[11], l[12],l[13],l[14],l[15]);
}

int vbe_dpc_command(char* command)
{
	int i, temp;
	char *tok, *sav_tok;
	char delim[] = ",{}:= \t\n";
	struct vbe_dpc_cfg *p = &_g_vbe_dpc_cfg;
	struct vbe_dpc_algo_param *ap = &p->ap;

	if (!command)	return 0;

	tok=simple_strtok(command, delim, &sav_tok);

	while(tok)
	{
		if (!strncasecmp(tok, "run", strlen("run"))) {
			p->run = ap->run = 1;
			break;
		}

		if (!strncasecmp(tok, "stop", strlen("stop"))) {
			p->run = ap->run = 0;
			break;
		}

		if (!strncasecmp(tok, "fixclk", strlen("fixclk"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				if (!strncasecmp(tok, "off", strlen("off"))) {
					temp = 673920000;
				}
				else {
					temp = simple_strtol(tok, NULL, 0);
				}

				/* 120:594000000,144:673920000,165:735815520 */
				if (temp >= 200000000 && temp <= 800000000) {
					p->fixclk = temp;
					BE_PWM_HAL_SetClk(p->fixclk);
					break;
				}
				printk("skip:%d\n",temp);
			}
			break;
		}

		if (!strncasecmp(tok, "cur2pre", strlen("cur2pre"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				ap->cur2pre = simple_strtol(tok, NULL, 0);
				printk("cur2pre:%d\n",ap->cur2pre);
			}
			break;
		}

		if (!strncasecmp(tok, "fixapl", strlen("fixapl"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				if (!strncasecmp(tok, "off", strlen("off"))) {
					ap->fixapl = -1;
				}
				else {
					temp = simple_strtol(tok, NULL, 0);
					if (temp >= 0 && temp <= 1023) {
						ap->fixapl = temp;
						break;
					}
					printk("skip:%d\n",temp);
				}
			}
			break;
		}

		if (!strncasecmp(tok, "fixduty", strlen("fixduty"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				if (!strncasecmp(tok, "off", strlen("off"))) {
					ap->fixduty = -1;
				}
				else {
					temp = simple_strtol(tok, NULL, 0);
					if (temp >= 0 && temp <= 255) {
						ap->fixduty = temp;
						break;
					}
					printk("skip:%d\n",temp);
				}
			}
			break;
		}

		if (!strncasecmp(tok, "iirgain", strlen("iirgain"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				temp = simple_strtol(tok, NULL, 0);
				if (temp >= 0 && temp <= 256) {
					ap->iirgain = temp;
					break;
				}
				printk("skip:%d\n",temp);
			}
			break;
		}

		if (!strncasecmp(tok, "dbgprint", strlen("dbgprint"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				if (!strncasecmp(tok, "off", strlen("off"))) {
					ap->dbgprint = 0;
				}
				else {
					temp = simple_strtol(tok, NULL, 0);
					if (temp >= 0) {
						ap->dbgprint = temp;
						break;
					}
					printk("skip:%d\n",temp);
				}
			}
			break;
		}

		if (!strncasecmp(tok, "lutx", strlen("lutx"))) {
			for (i=0; i<DPC_LUT_NUM; i++) {
				tok=simple_strtok(NULL, delim, &sav_tok);
				if(!tok) break;
				temp = simple_strtol(tok, NULL, 0);
				if (temp >= 0 && temp <= 1023) {
					ap->lutx[i] = temp;
				}
				else {
					printk("[%2d] skip:%d\n",i,temp);
				}
			}
			break;
		}

		if (!strncasecmp(tok, "luty", strlen("luty"))) {
			for (i=0; i<DPC_LUT_NUM; i++) {
				tok=simple_strtok(NULL, delim, &sav_tok);
				// printk("[%2d] tok=(%s)\n",i,tok);
				if(!tok) break;
				temp = simple_strtol(tok, NULL, 0);
				if (temp >= 0 && temp <= 255) {
					// printk("[%2d] luty:%d <- %d\n",i,temp,ap->luty[i]);
					ap->luty[i] = temp;
				}
				else {
					printk("[%2d] skip:%d\n",i,temp);
				}
			}
			break;
		}

		/* test */
		if (!strncasecmp(tok, "getv", strlen("getv"))) {
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				temp = simple_strtol(tok, NULL, 0);
				printk("getv:%d\n",temp);
			}
			break;
		}

		tok=simple_strtok(NULL, delim, &sav_tok);
	}

	return 0;
}
