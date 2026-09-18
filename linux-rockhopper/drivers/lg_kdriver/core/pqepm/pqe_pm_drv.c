/*****************************************************************************************
 * SIC R&D LAB, LG ELECTRONICS INC., SEOUL, KOREA
 * COPYRIGHT(c) 2011,2012 by LG Electronics Inc.
 *
 * All rights reserved. No part of this work covered by this copyright hereon
 * may be reproduced, stored in a retrieval system, in any form
 * or by any means, electronic, mechanical, photocopying, recording
 * or otherwise, without the prior written  permission of LG Electronics.
 ****************************************************************************************/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		<none>
 *  @version	1.0
 *  @date		2021-03-31
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "pqe_pm_impl.h"
#include <linux/sort.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct pqe_pm_ctx
{
	OS_SEM_T lock;
	UINT32 status;

	struct {
		int id;
		int dev_action;
		int hw_action;
		int monitor;
	} mask;

	struct pqe_pm_config config[PQE_PM_NUM_MAX];
	struct pqe_pm_config* sorted_config[PQE_PM_NUM_MAX];

	int (*hw_handler)(int hw_cmd);
	int *enable;

	void (*hw_dbg_status)(struct seq_file *m);
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
int	g_pqe_pm_debug_fd;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int	_pqe_pm_process_resume(int pm_id);
static int	_pqe_pm_process_suspend(int pm_id);
static void	_pqe_pm_reorder(void);

void pqe_pm_register_hw_dbg_status(void(*status)(struct seq_file *));
void pqe_pm_loop_cg_off_on(int type, int loop_num);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct pqe_pm_ctx _g_pqe_pm_ctx;

#define	get_device_action_string(id)	(((id)< PQE_PM_DEVICE_ACTION_MAX)? device_action_str_table[id] : "unknown")
#define	get_hw_action_string(id)		(((id)< PQE_PM_HW_ACTION_MAX)? hw_action_str_table[id] : "unknown")

static const char* device_action_str_table[] = {"SUSPEND_PREPARE", "SUSPEND", "SUSPEND_COMPLETED", "RESUNE_PREPARE", "RESUME", "RESUME_COMPLETED"};
static const char* hw_action_str_table[] = {"FW_SUSPEND", "CG_ON", "CG_OFF", "FW_RESUME" };

#define	check_mask_id(_a)	(_g_pqe_pm_ctx.mask.id & (1<<(_a)))
#define	check_mask_dev(_a)	(_g_pqe_pm_ctx.mask.dev_action & (1<<(_a)))
#define	check_mask_hw(_a)	(_g_pqe_pm_ctx.mask.hw_action & (1<<(_a)))
#define	check_mask_mon(_a)	(_g_pqe_pm_ctx.mask.monitor & (1<<(_a)))

/*========================================================================================
	Implementation Group
========================================================================================*/
void	pqe_pm_preinit(void)
{
	int	i;

	memset(&_g_pqe_pm_ctx, 0x0, sizeof(struct pqe_pm_ctx));

	for (i=0; i<PQE_PM_NUM_MAX; i++)
	{
		_g_pqe_pm_ctx.config[i].id = -1;
	}

	if (0)
	{

	}
#ifdef INCLUDE_O20_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O20)
	{
		pqe_pm_init_o20_hw_ctx();
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O22)
	{
		pqe_pm_init_o22_hw_ctx();
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_M23)
	{
		pqe_pm_init_m23_hw_ctx();
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O24)
	{
		pqe_pm_init_o24_hw_ctx();
	}
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O26)
	{
		pqe_pm_init_o26_hw_ctx();
	}
#endif
	else
	{
		printk("error. unknown chip 0x%x\n", lx_chip());
	}
	/* do nothing */
}

int		pqe_pm_initialize(void)
{
	g_pqe_pm_debug_fd = DBG_OPEN(PQE_PM_MODULE);

	if (g_pqe_pm_debug_fd<0)
	{
		printk("[pqepm] can't get debug handle\n");
	}
	else
	{
		OS_DEBUG_EnableModule (g_pqe_pm_debug_fd);
		OS_DEBUG_EnableModuleByIndex (g_pqe_pm_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED);
		OS_DEBUG_EnableModuleByIndex (g_pqe_pm_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW);
		OS_DEBUG_EnableModuleByIndex (g_pqe_pm_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_YELLOW);
	}

	OS_InitMutex(&_g_pqe_pm_ctx.lock, OS_SEM_ATTR_DEFAULT);

	pqe_pm_init_proc();

	return 0;
}

void	pqe_pm_cleanup(void)
{
	/* do nothing */

	pqe_pm_cleanup_proc();
}

void pqe_pm_register_hw_handler(int(*handler)(int))
{
	_g_pqe_pm_ctx.hw_handler = handler;
}

void pqe_pm_register_enable(int* enable)
{
	_g_pqe_pm_ctx.enable = enable;
}

void pqe_pm_register_hw_dbg_status(void(*status)(struct seq_file *))
{
	_g_pqe_pm_ctx.hw_dbg_status = status;
}

int pqe_pm_register(struct pqe_pm_config* pCfg)
{
	int i;
	int	pm_id = -1;
	int	ret = RET_ERROR;

    if (!pCfg || !pCfg->name[0])
	{
		pqe_pm_error("pcfg null\n");
		return RET_ERROR;
	}

	pqe_pm_assert(RET_OK == OS_LockMutex(&_g_pqe_pm_ctx.lock));

	for (i=0; i<PQE_PM_NUM_MAX; i++)
	{
		if (_g_pqe_pm_ctx.config[i].id == -1)
		{
			pm_id = i; break;
		}
	}

	if (pm_id<0)
	{
		pqe_pm_error("no empty slot\n"); goto func_exit;
	}

	memcpy(&_g_pqe_pm_ctx.config[pm_id], pCfg, sizeof(struct pqe_pm_config));
	_g_pqe_pm_ctx.config[pm_id].id = pm_id;

	if (pCfg->opt & PQE_PM_OPT_MONITOR)
	{
		// do nothing
	}
	else
	{
		// make device status "enabled" by default
		_g_pqe_pm_ctx.status |= (1<<pm_id);
	}

	pCfg->id = pm_id;
	pqe_pm_noti("device(%s) registerd. order=%03d, id=%02d\n", pCfg->name, pCfg->order, pCfg->id);

	_pqe_pm_reorder();

	/* call resume ? */

	ret = RET_OK;
func_exit:
	OS_UnlockMutex(&_g_pqe_pm_ctx.lock);

	return pm_id;
}
EXPORT_SYMBOL(pqe_pm_register);

int pqe_pm_unregister(int pm_id)
{
	int	ret = RET_ERROR;
	struct pqe_pm_config del_cfg;

	if (pm_id >= PQE_PM_NUM_MAX)
	{
		pqe_pm_error("invalid pm_id (%d)\n", pm_id);
		return RET_ERROR;
	}

	pqe_pm_assert(RET_OK == OS_LockMutex(&_g_pqe_pm_ctx.lock));

	pqe_pm_check_error(_g_pqe_pm_ctx.config[pm_id].id < 0, goto func_exit, "invalid pm_id %d\n", pm_id);

	memcpy(&del_cfg, &_g_pqe_pm_ctx.config[pm_id], sizeof(struct pqe_pm_config));
	pqe_pm_noti("device(%s) unregisted. order=%03d, id=%02d\n", del_cfg.name, del_cfg.order, del_cfg.id);

	memset(&_g_pqe_pm_ctx.config[pm_id], 0x0, sizeof(struct pqe_pm_config));
	_g_pqe_pm_ctx.config[pm_id].id = -1;

	if (_g_pqe_pm_ctx.config[pm_id].opt & PQE_PM_OPT_MONITOR)
	{
		// do nothing
	}
	else
	{
		_g_pqe_pm_ctx.status &= ~(1<<pm_id);
	}

	_pqe_pm_reorder();

	/* call suspend ? */

	ret = RET_OK;
func_exit:
	OS_UnlockMutex(&_g_pqe_pm_ctx.lock);

	return ret;
}
EXPORT_SYMBOL(pqe_pm_unregister);

int pqe_pm_request_resume(int pm_id)
{
	pqe_pm_assert(RET_OK == OS_LockMutex(&_g_pqe_pm_ctx.lock));
	_pqe_pm_process_resume(pm_id);
	OS_UnlockMutex(&_g_pqe_pm_ctx.lock);

	return RET_OK;
}
EXPORT_SYMBOL(pqe_pm_request_resume);

int pqe_pm_request_suspend(int pm_id)
{
	pqe_pm_assert(RET_OK == OS_LockMutex(&_g_pqe_pm_ctx.lock));
	_pqe_pm_process_suspend(pm_id);
	OS_UnlockMutex(&_g_pqe_pm_ctx.lock);

	return RET_OK;
}
EXPORT_SYMBOL(pqe_pm_request_suspend);

static int _pqe_pm_sort_compare(const void* a, const void* b)
{
	struct pqe_pm_config* cfg0 = *(struct pqe_pm_config**)a;
	struct pqe_pm_config* cfg1 = *(struct pqe_pm_config**)b;

	unsigned int id0 = cfg0->id;
	unsigned int id1 = cfg1->id;

	/* Order 가 큰 값이 앞쪽에 배치되게 한다 */
	if (cfg0->order != cfg1->order)
	{
		return (cfg0->order > cfg1->order)? -1:1;
	}

	/* Id 값이 작은 항목이 앞쪽에 배치되게 한다 */
	return (id0<id1)? -1: 1;
}

/* remake sorted_config list every item is added or removed
 * _pqe_pm_reorder() should be called after mutex is locked
 */
static void	_pqe_pm_reorder(void)
{
	int	i;
	struct pqe_pm_config* sorted_config[PQE_PM_NUM_MAX];

	for (i=0; i<PQE_PM_NUM_MAX; i++)
	{
		sorted_config[i] = &_g_pqe_pm_ctx.config[i];
	}

	/* do sort */
	sort(sorted_config, PQE_PM_NUM_MAX, sizeof(struct pqe_pm_config*),
		_pqe_pm_sort_compare, NULL);

	/* save */
	memcpy(_g_pqe_pm_ctx.sorted_config, sorted_config, sizeof(struct pqe_pm_config*)*PQE_PM_NUM_MAX);
}

static int	_pqe_pm_do_device_action(int action, bool reverse)
{
	int	i;
	int	error_cnt = 0;
	UINT64 tk[2];
	UINT64 start_tick, end_tick;

	start_tick = OS_GetUsecTicks();

	pqe_pm_check_noti(check_mask_dev(action), return RET_OK, "++ device action (%s) skip\n", get_device_action_string(action));
	pqe_pm_trace("++ device action (%s) begin\n", get_device_action_string(action));

	if (reverse)
	{
		for (i=PQE_PM_NUM_MAX-1; i>=0; i--)
		{
			struct pqe_pm_config* cfg = _g_pqe_pm_ctx.sorted_config[i];

			if (cfg && cfg->id != -1 && cfg->callback)
			{
				int	rc;
				pqe_pm_check_noti(check_mask_id(cfg->id), continue, "+++ (%s)(%d) action skip\n", cfg->name, cfg->id);

				tk[0] = OS_GetUsecTicks();
				rc = cfg->callback(action);
				tk[1] = OS_GetUsecTicks();

				pqe_pm_trace("+++ (%s)(%d) action rc=%d, ime=%d us\n", cfg->name, cfg->id, rc, (int)(tk[1]-tk[0]));
				pqe_pm_check_error(rc != RET_OK, ++error_cnt, "(%s) action 0x%x failed\n", cfg->name, action);
			}
		}
	}
	else
	{
		for (i=0; i<PQE_PM_NUM_MAX; i++)
		{
			struct pqe_pm_config* cfg = _g_pqe_pm_ctx.sorted_config[i];

			if (cfg && cfg->id != -1 && cfg->callback)
			{
				int	rc;
				pqe_pm_check_noti(check_mask_id(cfg->id), continue, "+++ (%s)(%d) action skip\n", cfg->name, cfg->id);

				tk[0] = OS_GetUsecTicks();
				rc = cfg->callback(action);
				tk[1] = OS_GetUsecTicks();

				pqe_pm_trace("+++ (%s)(%d) action rc=%d, ime=%d us\n", cfg->name, cfg->id, rc, (int)(tk[1]-tk[0]));
				pqe_pm_check_error(rc != RET_OK, ++error_cnt, "(%s) action 0x%x failed\n", cfg->name, action);
			}
		}
	}

	end_tick = OS_GetUsecTicks();
	pqe_pm_trace("++ device action (%s) completed. result=%s, time=%d us\n",
		get_device_action_string(action), (error_cnt==0)? "ok":"error", (int)(end_tick-start_tick));

	pqe_pm_check_error(error_cnt>0, /*nop*/, "total %d items failed\n", error_cnt);

	return (error_cnt==0)? RET_OK: RET_ERROR;
}

static int _pqe_pm_do_hw_action(int action)
{
	int	ret;
	UINT64 start_tick, end_tick;

	pqe_pm_check_error(!_g_pqe_pm_ctx.hw_handler, return RET_ERROR, "null hw_handler\n");

	pqe_pm_check_noti(check_mask_hw(action), return RET_OK, "++ hw action (%s) skip\n", get_hw_action_string(action));
	pqe_pm_trace("++ hw action (%s) begin\n", get_hw_action_string(action));

	start_tick = OS_GetUsecTicks();
	ret = _g_pqe_pm_ctx.hw_handler(action);
	end_tick = OS_GetUsecTicks();

	pqe_pm_trace("++ hw action (%s) completed. result=%s, time=%d us\n",
		get_hw_action_string(action), (ret==RET_OK)? "ok":"error", (int)(end_tick-start_tick));

	return ret;
}

/* runtime suspend 액션을 진행한다.
 * 추후 전용 kernel thread 에서 진행할 가능성에 대비하여 실제 액션 함수를 분리한다
 */
static int _pqe_pm_process_suspend(int pm_id)
{
	int rc;
	UINT64 start_tick, end_tick;
	UINT32 old_status = _g_pqe_pm_ctx.status;
	UINT32 new_status = old_status & ~(1<<pm_id);

	pqe_pm_check_error(pm_id<0, return RET_ERROR, "invalid pm_id (%d)\n", pm_id);
	pqe_pm_check_error(pm_id>=PQE_PM_NUM_MAX, return RET_ERROR, "invalid pm_id (%d)\n", pm_id);
	pqe_pm_check_error(_g_pqe_pm_ctx.config[pm_id].id<0, return RET_ERROR, "invalid id (%d)\n", pm_id);
	pqe_pm_check_error(!_g_pqe_pm_ctx.config[pm_id].name[0], return RET_ERROR, "not registered pm_id (%d)\n",pm_id);

	if (_g_pqe_pm_ctx.config[pm_id].opt & PQE_PM_OPT_MONITOR)
	{
		pqe_pm_noti("device(%d)(%s) permission denied\n",
			pm_id, _g_pqe_pm_ctx.config[pm_id].name);
		return RET_OK;
	}

	if (check_mask_mon(pm_id))
	{
		pqe_pm_noti("device(%d)(%s) check_mask_mon skip\n",
			pm_id, _g_pqe_pm_ctx.config[pm_id].name);
		return RET_OK;
	}

	pqe_pm_noti("device(%d)(%s) suspend. status change: 0x%08x -> 0x%08x\n",
		pm_id, _g_pqe_pm_ctx.config[pm_id].name, old_status, new_status);

	_g_pqe_pm_ctx.status = new_status;

	/* 이미 suspend 상태 OR 아직 suspend 상태에 머물러 있다면 */
	if (old_status == 0x0 || new_status != 0x0)
	{
		return RET_OK;
	}

	pqe_pm_check_error(!_g_pqe_pm_ctx.enable, return RET_OK, "null enable\n");
	pqe_pm_check_noti(*_g_pqe_pm_ctx.enable==0, return RET_OK, "not enabled\n");

	pqe_pm_check_error(!_g_pqe_pm_ctx.hw_handler, return RET_ERROR, "null hw_handler\n");

	pqe_pm_noti("+ all suspend begin\n");
	start_tick = OS_GetUsecTicks();

	/* prepare */
	rc =_pqe_pm_do_device_action(PQE_PM_DEVICE_SUSPEND_PREPARE, false);
	pqe_pm_assert(rc==RET_OK);

	/* FW stall */
	rc = _pqe_pm_do_hw_action(PQE_PM_HW_FW_SUSPEND);
	pqe_pm_assert(rc==RET_OK);

	/* device suspend */
	rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_SUSPEND, false);
	pqe_pm_assert(rc==RET_OK);

	/* clock gating on */
	rc = _pqe_pm_do_hw_action(PQE_PM_HW_CG_ON);
	pqe_pm_assert(rc==RET_OK);

	/* device suspend completed */
	rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_SUSPEND_COMPLETED, false);
	pqe_pm_assert(rc==RET_OK);

	end_tick = OS_GetUsecTicks();
	pqe_pm_noti("+ all suspend completed. time=%d us\n", (int)(end_tick-start_tick));

	return RET_OK;
}

/* runtime resume 액션을 진행한다.
 * 추후 전용 kernel thread 에서 진행할 가능성에 대비하여 실제 액션 함수를 분리한다
 */
static int	_pqe_pm_process_resume(int pm_id)
{
	int	rc;
	UINT64 start_tick, end_tick;
	UINT32 old_status = _g_pqe_pm_ctx.status;
	UINT32 new_status = old_status | (1<<pm_id);

	pqe_pm_check_error(pm_id<0, return RET_ERROR, "invalid pm_id (%d)\n", pm_id);
	pqe_pm_check_error(pm_id>=PQE_PM_NUM_MAX, return RET_ERROR, "invalid pm_id (%d)\n", pm_id);
	pqe_pm_check_error(_g_pqe_pm_ctx.config[pm_id].id<0, return RET_ERROR, "invalid id (%d)\n", pm_id);
	pqe_pm_check_error(!_g_pqe_pm_ctx.config[pm_id].name[0], return RET_ERROR, "not registered pm_id (%d)\n",pm_id);

	if (_g_pqe_pm_ctx.config[pm_id].opt & PQE_PM_OPT_MONITOR)
	{
		pqe_pm_noti("device(%d)(%s) permission denied\n",
			pm_id, _g_pqe_pm_ctx.config[pm_id].name);
		return RET_OK;
	}

	if (check_mask_mon(pm_id))
	{
		pqe_pm_noti("device(%d)(%s) check_mask_mon skip\n",
			pm_id, _g_pqe_pm_ctx.config[pm_id].name);
		return RET_OK;
	}

	pqe_pm_noti("device(%d)(%s) resume. status change: 0x%08x -> 0x%08x\n",
		pm_id, _g_pqe_pm_ctx.config[pm_id].name, old_status, new_status);

	_g_pqe_pm_ctx.status = new_status;

	/* 이미 active 상태이면 */
	if (old_status>0x0)
	{
		return RET_OK;
	}

	pqe_pm_check_error(!_g_pqe_pm_ctx.enable, return RET_OK, "null enable\n");
	pqe_pm_check_noti(*_g_pqe_pm_ctx.enable==0, return RET_OK, "not enabled\n");

	pqe_pm_check_error(!_g_pqe_pm_ctx.hw_handler, return RET_ERROR, "null hw_handler\n");

	pqe_pm_noti("+ all resume begin\n");
	start_tick = OS_GetUsecTicks();

	/* prepare */
	rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_RESUME_PREPARE, true);
	pqe_pm_assert(rc==RET_OK);

	/* clock gating off */
	rc = _pqe_pm_do_hw_action(PQE_PM_HW_CG_OFF);
	pqe_pm_assert(rc==RET_OK);

	/* device resume */
	rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_RESUME, true);
	pqe_pm_assert(rc==RET_OK);

	/* fw restart */
	rc = _pqe_pm_do_hw_action(PQE_PM_HW_FW_RESUME);
	pqe_pm_assert(rc==RET_OK);

	/* device resume completed */
	rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_RESUME_COMPLETED, true);
	pqe_pm_assert(rc==RET_OK);

	end_tick = OS_GetUsecTicks();
	pqe_pm_noti("+ all resume completed. time=%d us\n", (int)(end_tick-start_tick));

	return RET_OK;
}

void pqe_pm_dbg_set_mask(int type, int data)
{
	if (type == 0) {
		_g_pqe_pm_ctx.mask.id = data;
	} else if (type == 1) {
		_g_pqe_pm_ctx.mask.dev_action = data;
	} else if (type == 2) {
		_g_pqe_pm_ctx.mask.hw_action = data;
	} else if (type == 3) {
		static UINT32 org_status = 0;
		if (!org_status) {
			org_status = _g_pqe_pm_ctx.status;
		}
		_g_pqe_pm_ctx.status = (org_status & ~(data));
		_g_pqe_pm_ctx.mask.monitor = data;
	}
}

/* /proc/lg/pqepm/status */
void pqe_pm_print_status(struct seq_file *m)
{
	int	i;
	int	cnt = 0;

	pqe_pm_assert(RET_OK == OS_LockMutex(&_g_pqe_pm_ctx.lock));

	seq_printf(m, "-----------------------------------------------------------------\n");
	seq_printf(m, "see guide : http://collab.lge.com/main/x/YGeiT\n");
	seq_printf(m, "param  : cat /sys/module/lg1k/parameters/pqepm_[chip]\n");
	seq_printf(m, "enable : echo 1 > /sys/module/lg1k/parameters/pqepm_[chip]\n");
	seq_printf(m, "enable : set bootopts lg1k.pqepm_[chip]=1\n");
	seq_printf(m, "suspend test : echo 0 > /proc/lg/pqepm/request_test\n");
	seq_printf(m, "resume test  : echo 1 > /proc/lg/pqepm/request_test\n");
	seq_printf(m, "hide OSD : echo 0 0 > /proc/lg/fbdev/viewctrl\n");
	seq_printf(m, "show OSD : echo 0 1 > /proc/lg/fbdev/viewctrl\n");
	seq_printf(m, "-----------------------------------------------------------------\n");

	seq_printf(m, "%-10s (%08x):", "0.mask.id", _g_pqe_pm_ctx.mask.id);
	for (i=31; i>=0; i--) {
		if (check_mask_id(i)) {
			seq_printf(m," %d",i);
		}
	}
	seq_printf(m, "\n");

	seq_printf(m, "%-10s (%08x):", "1.mask.dev", _g_pqe_pm_ctx.mask.dev_action);
	for (i=31; i>=0; i--) {
		if (i<PQE_PM_DEVICE_ACTION_MAX) {
			seq_printf(m, " %s(%d)", get_device_action_string(i),check_mask_dev(i)? 1:0);
		}
	}
	seq_printf(m, "\n");

	seq_printf(m, "%-10s (%08x):", "2.mask.hw", _g_pqe_pm_ctx.mask.hw_action);
	for (i=31; i>=0; i--) {
		if (i<PQE_PM_HW_ACTION_MAX) {
			seq_printf(m, " %s(%d)", get_hw_action_string(i),check_mask_hw(i)? 1:0);
		}
	}
	seq_printf(m, "\n");

	seq_printf(m, "%-10s (%08x):", "3.mask.mon", _g_pqe_pm_ctx.mask.monitor);
	for (i=31; i>=0; i--) {
		if (check_mask_mon(i)) {
			seq_printf(m," %d",i);
		}
	}
	seq_printf(m, "\n");

	seq_printf(m, "-----------------------------------------------------------------\n");
	seq_printf(m, "%-16s %-5s %-5s %-22s %-8s %-3s\n", "name", "order", "id", "callback", "status", "opt");
	seq_printf(m, "-----------------------------------------------------------------\n");

	for (i=0; i<PQE_PM_NUM_MAX; i++)
	{
		struct pqe_pm_config* cfg = _g_pqe_pm_ctx.sorted_config[i];

		if (cfg && cfg->name[0] && cfg->id != -1 )
		{
			seq_printf(m, "%-16s %-5d %-5d %-22px %-8s %-3x\n",
					cfg->name,
					cfg->order,
					cfg->id,
					cfg->callback,
					(_g_pqe_pm_ctx.status & (1<<cfg->id))? "o":"x",
					cfg->opt);

			cnt++;
		}
	}

	seq_printf(m, "-----------------------------------------------------------------\n");
	seq_printf(m, "total %d items dumped\n", cnt);
	seq_printf(m, "-----------------------------------------------------------------\n");

	OS_UnlockMutex(&_g_pqe_pm_ctx.lock);
}

/* /proc/lg/pqepm/dbg_hw */
void pqe_pm_print_dbg_hw(struct seq_file *m)
{
	if (_g_pqe_pm_ctx.hw_dbg_status)
	{
		_g_pqe_pm_ctx.hw_dbg_status(m);
	}
}

void pqe_pm_loop_cg_off_on(int type, int loop_num)
{
	int rc,i;
	pqe_pm_noti("loop_num : %d\n",loop_num);
	if (loop_num <= 0)	return;

	for (i=0; i<loop_num; i++)
	{
		pqe_pm_noti("%d.1) loop cg off (%d/%d)\n",type,i,loop_num);
		rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_RESUME_PREPARE, true);
		rc = _pqe_pm_do_hw_action(PQE_PM_HW_CG_OFF);
		rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_RESUME, true);
		rc = _pqe_pm_do_hw_action(PQE_PM_HW_FW_RESUME);
		rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_RESUME_COMPLETED, true);
		usleep_range(500000, 500000);//500ms
		pqe_pm_noti("%d.2) loop cg on (%d/%d)\n",type,i,loop_num);
		rc =_pqe_pm_do_device_action(PQE_PM_DEVICE_SUSPEND_PREPARE, false);
		rc = _pqe_pm_do_hw_action(PQE_PM_HW_FW_SUSPEND);
		rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_SUSPEND, false);
		rc = _pqe_pm_do_hw_action(PQE_PM_HW_CG_ON);
		rc = _pqe_pm_do_device_action(PQE_PM_DEVICE_SUSPEND_COMPLETED, false);pqe_pm_assert(rc==RET_OK);
		usleep_range(500000, 500000);//500ms
	}

}