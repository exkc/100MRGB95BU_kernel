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
 *	main driver implementation for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *	author
 *	version
 *	date
 *	note
 *
 *	@addtogroup
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
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/pm_runtime.h>
#include <linux/vmalloc.h>
#include <linux/seq_file.h>

#include "os_util.h"
#include "base_device.h"
#include "de_def.h"
#include "de_drv.h"
#include "de_io.h"
#include "hal/ipc_hal.h"
#include "mcu/de_int.h"
#include "de_hal.h"
#include "resource_mgr.h"
#include "vsc_fw.h"
#ifdef INCLUDE_KDRV_SE
#include "se_drv.h"
#endif
#include "hma_alloc.h"
#include "vsc_print.h"
#include "vsc_util.h"

#include "pqefw0.h"
#include "pqefw1.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VSC_FW_NOTI_STR_SIZE 64
#define VSC_FW_NOTI_BUF_MAX 100
#define VSC_FW_TASK_DELAY_MSEC 50

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VSC_FW_NOTI_BACKUP(_fmt, args...)	\
    {\
        char _vsc_fw_str_buf[VSC_FW_NOTI_STR_SIZE];\
        DE_NOTI(_fmt, ##args);\
        snprintf(_vsc_fw_str_buf, VSC_FW_NOTI_STR_SIZE, _fmt, ##args);\
        _vsc_fw_backup_log(_vsc_fw_str_buf);\
    }

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum vsc_fw_flag {
    VSC_FW_FLAG_NONE = 0,
    VSC_FW_FLAG_DBG,
    VSC_FW_FLAG_MAX
};

struct vsc_fw_log {
    UINT32 sec;
    UINT32 msec;
    UINT32 usec;
    char str[VSC_FW_NOTI_STR_SIZE];
};

struct vsc_fw_alloc {
    int idx;
    unsigned int flag;//see enum vsc_fw_flag
    void *data;
    char *path;
    unsigned int length;
    char *path_new;
    unsigned int length_new;
    unsigned int fw_size;
    unsigned int alloc_size;
};

struct vsc_fw_ctx {
    int fw_opt;//see enum vsc_fw_opt
    int usr_opt;//see enum vsc_fw_opt
    unsigned int year;
    unsigned int max_num;
    unsigned int usr_num;
    struct task_struct *task;
    struct vsc_fw_alloc alloc[VSC_FW_MAX_NUM];
    struct vsc_fw_log log[VSC_FW_NOTI_BUF_MAX];
    struct vsc_fw_load load;
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void vsc_fw_print_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
const char *_g_vsc_fw_from_str[VSC_FW_FROM_MAX] = {"normal","thread","usrbin","resume","thaw","restore","rpm_res","rpm_sup"};
const char *_g_vsc_fw_opt_str[VSC_FW_OPT_MAX] = {"none","skip","bin","user","local","header","dbgmap"};
const char *_g_vsc_fw_cfg_str[DE_FW_CFG_MAX_NUM] = {"header","skip","bin2ddr","usr2ddr","map2ddr","path","6","7","8","9","str"};
const char *_g_vsc_fw_act_str[VSC_FW_LOAD_MAX] = {"none","stop","prepare","complete"};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _vsc_fw_init_fw_opt(void);
static int _vsc_fw_backup_log(char *data);
static int _vsc_fw_mgr_io_de_init(void);
static int _vsc_fw_get_file_name(int idx, char *name, unsigned int length);
static int _vsc_fw_alloc_path(struct vsc_fw_alloc *p_alloc, void *p, unsigned int flag);
static int _vsc_fw_alloc_backup(struct vsc_fw_alloc *p_alloc);
static int _vsc_fw_free_backup(struct vsc_fw_alloc *p_alloc);
static int _vsc_fw_chk_ready(void);
static int _vsc_fw_io_print_usrlog(LX_DE_FW_DWLD_T *param);
static int _vsc_fw_thread(void *ptr);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct vsc_fw_ctx _g_vsc_fw_ctx;

static uint _g_vsc_fw_delay_msec = 100;//20230731,fix bin loading fail(from webos1005)
module_param_named(pqefw_delay, _g_vsc_fw_delay_msec, uint, 0644);
static uint _g_vsc_fw_timeout_msec = 10000;
module_param_named(pqefw_timeout, _g_vsc_fw_timeout_msec, uint, 0644);
static uint _g_vsc_fw_keep_symbol = 1;//0:legacy,1:keep symbol(SICDTV-14467)
module_param_named(pqefw_keep_symbol, _g_vsc_fw_keep_symbol, uint, 0644);
static uint _g_vsc_fw_use_int_pool = 1;//0:legacy,1:use int. pool(SICDTV-14467)
module_param_named(pqefw_use_int_pool, _g_vsc_fw_use_int_pool, uint, 0644);

#define VSC_FW_DBG_PANIC_1ST_FAIL   1
#define VSC_FW_DBG_PANIC_2ND_FAIL   2
#define VSC_FW_DBG_BIN_CRC_MATCH    3
#define VSC_FW_DBG_TEST_NOT_ALIVE   4
#define VSC_FW_DBG_TEST_DO_RETRY    5
#define VSC_FW_DBG_TEST_NO_RETRY    6
static uint _g_vsc_fw_dbg = 0;//(SICDTV-14467)
module_param_named(pqefw_dbg, _g_vsc_fw_dbg, uint, 0644);

/*========================================================================================
	Implementation Group
========================================================================================*/
static int vsc_fw_is_working(void)
{
    return (_g_vsc_fw_dbg == VSC_FW_DBG_TEST_NOT_ALIVE)? 0:DE_HAL_IPCisAlive();
}

static int vsc_fw_load_register(struct vsc_fw_ctx *ctx)
{
    int ret = 0;

    if (!ctx)   return -1;

    if (0) { }
#ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26) {
        extern int de_reg_o26_fwload_register(struct vsc_fw_load *load);
        ret = de_reg_o26_fwload_register(&ctx->load);
    }
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24) {
        extern int de_reg_o24_fwload_register(struct vsc_fw_load *load);
        ret = de_reg_o24_fwload_register(&ctx->load);
    }
#endif
    else {
        //not support
    }

    return ret;
}

int vsc_fw_init(void)
{
    int ret,i;
    UINT32 max_num = 1;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;

    memset(&_g_vsc_fw_ctx,0,sizeof(_g_vsc_fw_ctx));
    _vsc_fw_init_fw_opt();

    for (i=0; i<VSC_FW_MAX_NUM; i++)
    {
        p_ctx->alloc[i].idx = i;
    }

    ret = DE_HAL_FW_GetMaxNum(&max_num);
    if (ret!=0)     max_num=1;
    if (max_num==0) max_num=1;
    p_ctx->max_num = max_num;

    if ((lx_chip() >= LX_CHIP_O24) || ((lx_chip() == LX_CHIP_M23) && (lx_board_opt() & LX_BOARD_OPT_SLT)) || (p_ctx->usr_opt == VSC_FW_OPT_USR))
    {
        p_ctx->usr_num = max_num;
    }

    ret = vsc_fw_load_register(p_ctx);

    VSC_FW_NOTI_BACKUP("init done (num:%d,max:%d)\n",p_ctx->usr_num,p_ctx->max_num);
    return 0;
}

unsigned int vsc_fw_get_user_bin_num(void)
{
    return _g_vsc_fw_ctx.usr_num;
}

int vsc_fw_init_late(unsigned int flag)
{
    #if 0   //do nothing for VSC_FW_OPT_USR
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    if (flag == CALL_FROM_USER && p_ctx->fw_opt == VSC_FW_OPT_USR)
    {
        VSC_FW_NOTI_BACKUP("init_late : restore ipc\n");
        ipc_hal_restore();
    }
    #endif
    return 0;
}

int vsc_fw_view_log(void)
{
    UINT32 i;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_log *p_log;

    for (i=0; i<VSC_FW_NOTI_BUF_MAX; i++)
    {
        p_log = &(p_ctx->log[i]);
        if (p_log->sec==0 && p_log->msec==0 && p_log->usec==0)   break;
        printk("[%02d][%06d.%03d%03d] %s",i,p_log->sec,p_log->msec,p_log->usec,p_log->str);
    }

    return RET_OK;
}

/* see enum vsc_fw_from */
int vsc_fw_rpm(int from)
{
    if (from != VSC_FW_FROM_RPM_SUSPEND && from != VSC_FW_FROM_RPM_RESUME)
    {
        VSC_FW_NOTI_BACKUP("rpm not support from(%d)\n",from);
        return -1;
    }

    VSC_FW_NOTI_BACKUP("rpm (from:%s) : start\n",_g_vsc_fw_from_str[from]);

    if (from == VSC_FW_FROM_RPM_SUSPEND)
    {
        /* unregister handler */
        //de_srcsync_register(FALSE, test_src_sync, "srcsync_handler");
        //de_sync_register(FALSE, _set_sys_timestamp, "set_sys_time");

        /* TODO : stop apb access */

        /* ipc masking on before fw suspend */
        ipc_hal_set_mask(0xffffffff);
        VSC_FW_NOTI_BACKUP("ipc mask\n");

        /* fw suspend */
        do {
            UINT32 count = 0;
            DE_IO_SetMcuSuspend(1);
            while (1) {
                if (1 == DE_IPC_McuIsSuspend()) {
                    VSC_FW_NOTI_BACKUP("enter mcu suspend(retry count:%d)\n",count);
                    break;
                }
                msleep(1);
                count++;
                if (count == 100) {
                    VSC_FW_NOTI_BACKUP("timeout mcu suspend\n");
                    break;
                }
            }
        } while(0);

        /* ipc masking on after fw suspend */
        //ipc_hal_set_mask(0xffffffff);
        //ipc_hal_ready_to_use(0);//see v4l2_vsc_pqe_pm_cb

        /* stop intr handler after fw suspend */
        DE_INT_StopHandler(1);//see v4l2_vsc_pqe_pm_cb
    }
    else    //VSC_FW_FROM_RPM_RESUME
    {
        /* restart intr handler before fw resume */
        DE_INT_StopHandler(0);//see v4l2_vsc_pqe_pm_cb

        /* ipc masking off before fw resume */
        //ipc_hal_set_mask(0x0);
        //ipc_hal_ready_to_use(1);//see v4l2_vsc_pqe_pm_cb

        /* fw resume */
        do {
            UINT32 count = 0;
            DE_IO_SetMcuSuspend(0);
            while (1) {
                if (0 == DE_IPC_McuIsSuspend()) {
                    DE_NOTI("enter mcu resume(retry count:%d)\n",count);
                    break;
                }
                msleep(1);
                count++;
                if (count == 100) {
                    DE_NOTI("timeout mcu resume\n");
                    break;
                }
            }
        } while(0);

        /* ipc masking off after fw resume */
        ipc_hal_set_mask(0x0);
        DE_NOTI("ipc unmask\n");

        //ipc_hal_restore();

        /* TODO : start apb access */

        /* register handler */
        //de_srcsync_register(TRUE, test_src_sync, "srcsync_handler");
        //de_sync_register(TRUE, _set_sys_timestamp, "set_sys_time");
    }

    VSC_FW_NOTI_BACKUP("rpm (from:%s) : end\n",_g_vsc_fw_from_str[from]);
    return 0;
}

/* see enum vsc_fw_from */
int vsc_fw_download(int from)
{
    int ret = RET_OK;
    int idx;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_alloc *p_alloc;
    LX_DE_FW_DWLD_T fw;

    if (from < 0 || from >= VSC_FW_FROM_MAX)
    {
        VSC_FW_NOTI_BACKUP("load unknown from(%d)\n",from);
        return VSC_FW_RET_ERROR;
    }

    VSC_FW_NOTI_BACKUP("load(from:%s):start\n",_g_vsc_fw_from_str[from]);

    if (p_ctx->fw_opt == VSC_FW_OPT_SKIP)
    {
        VSC_FW_NOTI_BACKUP("load(from:%s):ret skip (opt)\n",_g_vsc_fw_from_str[from]);
        return VSC_FW_RET_SKIP;
    }

    if (from == VSC_FW_FROM_NORMAL || from == VSC_FW_FROM_THREAD)
    {
        if (0 != vsc_fw_get_user_bin_num())
        {
            VSC_FW_NOTI_BACKUP("load(from:%s):ret skip (usr)\n",_g_vsc_fw_from_str[from]);
            return VSC_FW_RET_SKIP;
        }

        if ((from == VSC_FW_FROM_NORMAL) && (p_ctx->fw_opt == VSC_FW_OPT_BIN))
        {
            ipc_hal_ready_to_use(0);
            _vsc_fw_mgr_io_de_init();//pre init because of sync register
            msleep(_g_vsc_fw_delay_msec);
            VSC_FW_NOTI_BACKUP("load(from:%s):next (delay:%d)(go to thread)\n",_g_vsc_fw_from_str[from],_g_vsc_fw_delay_msec);
            return VSC_FW_RET_NEXT;
        }

        for (idx = (p_ctx->max_num-1); idx>=0; idx--)
        {
            p_alloc = &(p_ctx->alloc[idx]);
            p_alloc->flag = VSC_FW_FLAG_DBG;
            ret = _vsc_fw_alloc_backup(p_alloc);

            fw.inx = idx;
            if (ret == RET_OK)
            {
                fw.cfg = DE_FW_CFG_COPY_MAP_TO_DDR;
                fw.size = p_alloc->fw_size;
                fw.pData = (char *)p_alloc->data;
            }
            else
            {
                fw.cfg = DE_FW_CFG_DOWNLOAD_HEADER;
                fw.size = 0;
                fw.pData = NULL;
            }
            ret = vsc_fw_io_download((void *)&fw,CALL_FROM_KERNEL);
        }

        VSC_FW_NOTI_BACKUP("load(from:%s):done (ret:%d)\n",_g_vsc_fw_from_str[from],ret);

        if (ret == RET_OK)
        {
            ipc_hal_ready_to_use(1);
            if (from == VSC_FW_FROM_THREAD)
            {
                VSC_FW_NOTI_BACKUP("load(from:%s):restore ipc\n",_g_vsc_fw_from_str[from]);
                ipc_hal_restore();
            }
            else
            {
                _vsc_fw_mgr_io_de_init();
            }
        }
    }
    else if (p_ctx->fw_opt == VSC_FW_OPT_LOCAL && from == VSC_FW_FROM_RESTORE)
    {
        _vsc_fw_init_fw_opt();
        vsc_fw_free_backup_all();
        ipc_hal_ready_to_use(0);
        _vsc_fw_mgr_io_de_init();
        VSC_FW_NOTI_BACKUP("load(from:%s):start thread (local)\n",_g_vsc_fw_from_str[from]);
        p_ctx->task = kthread_run(_vsc_fw_thread,(void *)p_ctx,"_vsc_fw_thread");
        if (!p_ctx->task)
        {
            VSC_FW_NOTI_BACKUP("load(from:%s):kthread_run err\n",_g_vsc_fw_from_str[from]);
        }
    }
    else if (vsc_fw_is_working() == 0)//VSC_FW_FROM_RESTORE,VSC_FW_FROM_RESUME
    {
        for (idx = (p_ctx->max_num-1); idx>=0; idx--)
        {
            p_alloc = &(p_ctx->alloc[idx]);

            fw.inx = idx;
            if (from == VSC_FW_FROM_RESUME)
            {
                VSC_FW_NOTI_BACKUP("load(from:%s)(i:%d):run fw (%d)\n",_g_vsc_fw_from_str[from],idx,p_alloc->fw_size);
                fw.cfg = DE_FW_CFG_CPY_TO_DDR_SKIP;
                fw.size = p_alloc->fw_size;
                fw.pData = (char *)p_alloc->data;
            }
            else if (p_alloc->data != NULL && p_alloc->fw_size > 0)
            {
                VSC_FW_NOTI_BACKUP("load(from:%s)(i:%d):map to ddr (%d)\n",_g_vsc_fw_from_str[from],idx,p_alloc->fw_size);
                fw.cfg = DE_FW_CFG_COPY_MAP_TO_DDR;
                fw.size = p_alloc->fw_size;
                fw.pData = (char *)p_alloc->data;
            }
            else
            {
                VSC_FW_NOTI_BACKUP("load(from:%s)(i:%d):header to ddr\n",_g_vsc_fw_from_str[from],idx);
                fw.cfg = DE_FW_CFG_DOWNLOAD_HEADER;
                fw.size = 0;
                fw.pData = NULL;
            }
            ret = vsc_fw_io_download((void *)&fw,CALL_FROM_KERNEL);
        }
        VSC_FW_NOTI_BACKUP("load(from:%s):done (ret:%d)\n",_g_vsc_fw_from_str[from],ret);
        if (ret == RET_OK)
        {
            _vsc_fw_mgr_io_de_init();
        }
    }
    else//VSC_FW_FROM_THAW
    {
        VSC_FW_NOTI_BACKUP("load(from:%s):nothing to do (already alive)\n",_g_vsc_fw_from_str[from]);
    }

    VSC_FW_NOTI_BACKUP("load(from:%s):end\n",_g_vsc_fw_from_str[from]);

    return (ret == RET_OK)? VSC_FW_RET_OK:VSC_FW_RET_ERROR;
}

int vsc_fw_io_download(void *param, unsigned int flag)
{
    int ret;
    int header_load = 1;
    int start_thread = 0;
    LX_DE_FW_DWLD_T *p;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_alloc *p_alloc;

    if (!param)
    {
        DE_ERROR("param null\n");
        return RET_ERROR;
    }

    p = (LX_DE_FW_DWLD_T *)param;

    if (flag == CALL_FROM_USER && p->cfg == DE_FW_CFG_PRINT_USR_STR)
    {
        _vsc_fw_io_print_usrlog(p);
        return RET_OK;
    }

    if (p_ctx->fw_opt == VSC_FW_OPT_SKIP)
    {
        VSC_FW_NOTI_BACKUP("ioload fw%d fw_opt skip\n",p->inx);
        return RET_OK;
    }

    do {
        if (p->cfg == DE_FW_CFG_CPY_TO_DDR_SKIP)
        {
            header_load = 0;
            break;
        }

        if (!p->size)                 break;
        if (p->size > ((16<<10)<<10)) break;
        if (p->size < 0)              break;
        if (!p->pData)                break;
        header_load = 0;
    } while(0);

    p_alloc = &(p_ctx->alloc[p->inx]);

    do {
        if (header_load == 1)
        {
            VSC_FW_NOTI_BACKUP("ioload fw%d cfg:%d -> header\n",p->inx,p->cfg);
            p->cfg = DE_FW_CFG_DOWNLOAD_HEADER;
            ret = DE_HAL_FW_DownloadFromHead(p);
        }
        else if (flag == CALL_FROM_USER)
        {
            if (p->cfg == DE_FW_CFG_BIN_PATH_INFO)
            {
                VSC_FW_NOTI_BACKUP("ioload fw%d cfg:%d(path) -> map\n",p->inx,p->cfg);
                do {
                    ret = _vsc_fw_alloc_path(p_alloc, param, flag);
                    if (ret != RET_OK)  {VSC_FW_NOTI_BACKUP("ioload fw%d _vsc_fw_alloc_path err\n",p->inx);break;}
                    VSC_FW_NOTI_BACKUP("ioload fw%d %d(%s)\n",p_alloc->idx,p_alloc->length,p_alloc->path);
                    if (p_ctx->fw_opt == VSC_FW_OPT_BIN)    {start_thread=1;break;}
                    p_alloc->flag = VSC_FW_FLAG_NONE;
                    ret = _vsc_fw_alloc_backup(p_alloc);
                    if (ret != RET_OK)  {VSC_FW_NOTI_BACKUP("ioload fw%d _vsc_fw_alloc_backup err\n",p->inx);break;}
                    VSC_FW_NOTI_BACKUP("ioload fw%d(%dk)(size:%d)\n",p_alloc->idx,p_alloc->alloc_size>>10,p_alloc->fw_size);
                    ret = vsc_fw_hal_load(p_alloc->idx,DE_FW_CFG_COPY_MAP_TO_DDR,p_alloc->fw_size,(char *)p_alloc->data);
                } while(0);
            }
            else
            {
                VSC_FW_NOTI_BACKUP("ioload fw%d cfg:%d(user) -> map\n",p->inx,p->cfg);
                do {
                    if (p_alloc->data)    {VSC_FW_NOTI_BACKUP("ioload fw%d data already\n",p->inx);ret=RET_OK;break;}
                    p_alloc->alloc_size = ((p->size + (0x1<<12))>>12)<<12;//4k align
                    p_alloc->fw_size = p->size;
                    p_alloc->data = (void *)vmalloc(p_alloc->alloc_size);
                    if (!p_alloc->data) {VSC_FW_NOTI_BACKUP("ioload fw%d alloc err\n",p->inx);ret=RET_ERROR;break;}
                    ret = copy_from_user(p_alloc->data, p->pData, p->size);
                    if (ret != RET_OK)  {VSC_FW_NOTI_BACKUP("ioload fw%d copy_from_user err\n",p->inx);break;}
                    VSC_FW_NOTI_BACKUP("ioload fw%d(%dk)(size:%d)\n",p_alloc->idx,p_alloc->alloc_size>>10,p_alloc->fw_size);
                    ret = vsc_fw_hal_load(p_alloc->idx,DE_FW_CFG_COPY_MAP_TO_DDR,p_alloc->fw_size,(char *)p_alloc->data);
                } while(0);
            }
        }
        else
        {
            VSC_FW_NOTI_BACKUP("ioload fw%d cfg:%d\n",p->inx,p->cfg);
            ret = vsc_fw_hal_load(p->inx, p->cfg, p->size, p->pData);
        }

        if (start_thread == 1)  break;
        if (p->inx != 0)        break;    //check MCU0 only

        if (ret == RET_OK) ret = _vsc_fw_chk_ready();

        if (ret == RET_TIMEOUT)
        {
            BREAK_WRONG(ret);
        }

        if (ret == RET_OK) ipc_hal_start(0, TRUE);

        VSC_FW_NOTI_BACKUP("ioload fw%d done(ret:%d)\n",p->inx,ret);

        if (flag == CALL_FROM_USER)
        {
            VSC_FW_NOTI_BACKUP("ioload fw%d enable ipc\n",p->inx);
            ipc_hal_ready_to_use(1);
        }
    } while(0);

    if (_g_vsc_fw_keep_symbol == 0 && p_alloc->data)
    {
        _vsc_fw_free_backup(p_alloc);
    }

    if (p->inx == 0 && start_thread == 1)
    {
        VSC_FW_NOTI_BACKUP("ioload fw%d start thread\n",p->inx);
        ipc_hal_ready_to_use(0);
        p_ctx->task = kthread_run(_vsc_fw_thread,(void *)p_ctx,"_vsc_fw_thread");
        if (!p_ctx->task)
        {
            VSC_FW_NOTI_BACKUP("ioload fw%d kthread_run err\n",p->inx);
        }
    }

    return ret;
}

static int _vsc_fw_hal_load_update_crc(struct vsc_fw_load_param *p)
{
    int i;
    unsigned int *c32;

    if (!p) {
        VSC_FW_NOTI_BACKUP("p null\n");
        return -1;
    }

    if (!p->bin_data) {
        VSC_FW_NOTI_BACKUP("data null(fw%d)\n",p->idx);
        return -1;
    }

    if (p->bin_size < (1<<10) || p->bin_size > ((16<<10)<<10)) {
        VSC_FW_NOTI_BACKUP("invalid size(fw%d)(%dKB)(%dKB)\n",p->idx,p->bin_size,p->hma_size);
        return -1;
    }

    c32 = (unsigned int *)(&p->crc);
    for (i=0; i<(sizeof(struct vsc_fw_crc)/sizeof(unsigned int)); i++)
    {
        c32[i] = *(unsigned int *)(p->bin_data + p->bin_size - 4 - (4*i));
    }

    VSC_FW_NOTI_BACKUP("update crc(fw%d)(0x%08x,0x%08x,0x%08x)\n",p->idx,p->crc.h.u32,p->crc.size,p->crc.crc);

    return 0;
}

static int _vsc_fw_hal_load_chk_valid(struct vsc_fw_load_param *p)
{
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    UINT32 secure_map, dbgmap_opt, signed_word;
    char *error_message = NULL;

    if (!p) {
        VSC_FW_NOTI_BACKUP("p null\n");
        return -1;
    }

    if (p->cfg != DE_FW_CFG_COPY_MAP_TO_DDR) {
        VSC_FW_NOTI_BACKUP("not support(fw%d)(cfg:%d)\n",p->idx,p->cfg);
        return -1;
    }

    if (!p->bin_data) {
        VSC_FW_NOTI_BACKUP("data null(fw%d)\n",p->idx);
        return -1;
    }

    if (p->bin_size < (1<<10) || p->bin_size > ((16<<10)<<10)) {
        VSC_FW_NOTI_BACKUP("invalid size(fw%d)(%dKB)(%dKB)\n",p->idx,p->bin_size,p->hma_size);
        return -1;
    }

    p->word = *((UINT32 *)p->bin_data);
    secure_map = (p->secure == 1)? 1:0;
    dbgmap_opt = (p_ctx->usr_opt == VSC_FW_OPT_DBGMAP)? 1:0;
    signed_word = (p->word == VSC_FW_HEAD_MAGIC)? 1:0;

    if (secure_map) {
        if (!dbgmap_opt) {
            if (!signed_word) {
                error_message = "ERR: secure map but unsigned";
            }
        }
        else {
            if (signed_word) {
                error_message = "ERR: nonsecure opt but signed";
            }
        }
    }
    else {
        if (signed_word) {
            error_message = "ERR: nonsecure map but signed";
        }
    }

    if (error_message) {
        p->err_mesg = error_message;
        VSC_FW_NOTI_BACKUP("%s(fw%d)(0x%08x)\n",error_message,p->idx,p->word);
        vsc_oprint("%s(fw%d)(0x%08x)\n",error_message,p->idx,p->word);
        return -1;
    }

    VSC_FW_NOTI_BACKUP("check done(fw%d)\n",p->idx);

    return 0;
}

static int _vsc_fw_hal_load_alloc(struct vsc_fw_load_param *p)
{
    if (!p->hma_base) {
        p->hma_base = hma_alloc_user(p->hma_pool, p->hma_size, (1<<14), p->name);//align:16k
        if (!p->hma_base) {
            VSC_FW_NOTI_BACKUP("hma_alloc fail(%s,%d,%s)\n",p->hma_pool,p->hma_size,p->name);
            return -1;
        }
        p->hma_base_bkup = p->hma_base;
        VSC_FW_NOTI_BACKUP("hma_alloc(0x%x:%s,%d,%s)\n",(UINT32)p->hma_base,p->hma_pool,p->hma_size,p->name);
    }

    return 0;
}

static int _vsc_fw_hal_load_vmap(struct vsc_fw_load_param *p)
{
    if (!p->vmap_base) {
        p->vmap_size = ((p->bin_size>>14)+1)<<14;//align:16k
        p->vmap_base = (void *)vmap_phys(p->vmap_phys, p->vmap_size);
        if (!p->vmap_base) {
            VSC_FW_NOTI_BACKUP("vmap fail(fw%d)(%d)\n",p->idx,p->vmap_size);
            return -1;
        }
        p->vmap_base_bkup = p->vmap_base;
        VSC_FW_NOTI_BACKUP("vmap(fw%d)(0x%x,%d)\n",p->idx,(UINT32)p->vmap_phys,p->vmap_size);
    }

    return 0;
}

static int _vsc_fw_hal_load_free(struct vsc_fw_load_param *p)
{
    if (p->hma_base) {
        hma_free(p->hma_pool, p->hma_base);
        VSC_FW_NOTI_BACKUP("hma_free(fw%d)(%s,0x%x)\n",p->idx,p->hma_pool,(UINT32)p->hma_base);
        p->hma_base = 0;
    }

    if (p->vmap_base) {
        vunmap_phys((void*)p->vmap_base);
        VSC_FW_NOTI_BACKUP("vunmap(fw%d)\n",p->idx);
        p->vmap_base = 0;
    }

    return 0;
}

int vsc_fw_hal_load(int idx, int cfg, int size, char *data)
{
    int ret = 0;
    int do_complete, do_free, do_lgkree_req, do_alloc, dst_to_rom, use_int_pool;
    UINT32 se_tbl_id;
    LX_DE_FW_DWLD_T fw;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_load *p_load = &(p_ctx->load);
    struct vsc_fw_load_param *p;

    if (idx < 0 || idx >= VSC_FW_MAX_NUM) {
        VSC_FW_NOTI_BACKUP("idx err(%d)\n",idx);
        return -1;
    }

    p = p_load->param[idx];

    if (p_load->handler && p) {
        if (p->idx != idx) {
            VSC_FW_NOTI_BACKUP("idx err(fw%d)(%d)(%s)\n",p->idx,idx,p->name);
            return -1;
        }

        p->cfg = cfg;
        p->bin_size = size;
        p->bin_data = data;

        do_complete = 0;
        do_alloc = 1;
        use_int_pool = 0;
        do_lgkree_req = 1;
        dst_to_rom = 1;
        do_free = 1;

        if (_g_vsc_fw_use_int_pool == 1) {
            do_alloc = 0;
            use_int_pool = 1;
        }

        if (p->cfg == DE_FW_CFG_CPY_TO_DDR_SKIP) {
            do_complete = 1;
        }
        else if (p_ctx->usr_opt == VSC_FW_OPT_DBGMAP) {
            do_alloc = 1;
            do_lgkree_req = 0;
            dst_to_rom = 0;
            do_free = 0;
        }
        else if (p->secure == 0) {
            do_alloc = 0;
            use_int_pool = 0;
            do_lgkree_req = 0;
        }

        ret = p_load->handler(p,VSC_FW_LOAD_PREPARE);

        do {
            if (do_complete)   break;

            ret = _vsc_fw_hal_load_chk_valid(p);
            if (ret < 0)    break;

            ret = _vsc_fw_hal_load_update_crc(p);
            if (ret < 0)    break;

            if (do_alloc) {
                ret = _vsc_fw_hal_load_alloc(p);
                if (ret < 0)    break;
                p->vmap_phys = p->hma_base;
            }
            else if (use_int_pool) {
                p->vmap_phys = p->int_base;
            }
            else {
                p->vmap_phys = p->dst_base;
            }

            ret = _vsc_fw_hal_load_vmap(p);
            if (ret < 0)    break;

            memcpy((void *)p->vmap_base, p->bin_data, p->bin_size);
            wmb();
            VSC_FW_NOTI_BACKUP("memcpy to vmap(fw%d)(%d)\n",p->idx,p->bin_size);

            if (do_lgkree_req) {
                p->src_base = p->vmap_phys;
                se_tbl_id = (p->idx==0)? 0x30:0x31;
#ifdef INCLUDE_KDRV_SE
                ret = lgkree_req_secure_fwload(se_tbl_id, (void *)p->dst_base, (void *)p->src_base, p->bin_size);
                if (ret < 0) {
                    VSC_FW_NOTI_BACKUP("lgkree fail(%d)(fw%d)\n",ret,p->idx);
                    break;
                }
                VSC_FW_NOTI_BACKUP("lgkree(fw%d)(0x%x from 0x%x,%d)\n",p->idx,(UINT32)p->dst_base,(UINT32)p->src_base,p->bin_size);
#endif
            }

            if (dst_to_rom) {
                p->rom_base = (UINT32)p->dst_base;
            }
            else {
                p->rom_base = (UINT32)p->hma_base;
            }

            do_complete = 1;
        } while(0);

        if (do_complete) {
            ret = p_load->handler(p,VSC_FW_LOAD_COMPLETE);
        }

        if (do_free) {
            _vsc_fw_hal_load_free(p);
        }
    }
    else {
        fw.inx = idx;
        fw.cfg = cfg;
        fw.size = size;
        fw.pData = data;

        VSC_FW_NOTI_BACKUP("hal_ld fw%d cfg:%d,size:%d\n",idx,cfg,size);

        ret = DE_HAL_FW_Download(&fw);
    }

    return ret;
}

int vsc_fw_alloc_backup_all(void)
{
    int ret = 0;
    int i;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_alloc *p_alloc;

    if (_g_vsc_fw_keep_symbol == 1)    return 0;

    for (i=0; i<p_ctx->max_num; i++)
    {
        p_alloc = &(p_ctx->alloc[i]);
        p_alloc->flag = VSC_FW_FLAG_NONE;
        ret = _vsc_fw_alloc_backup(p_alloc);
    }

    VSC_FW_NOTI_BACKUP("alloc_all done\n");
    return 0;
}

int vsc_fw_free_backup_all(void)
{
    int i;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_alloc *p_alloc;

    if (_g_vsc_fw_keep_symbol == 1)    return 0;

    for (i=0; i<p_ctx->max_num; i++)
    {
        p_alloc = &(p_ctx->alloc[i]);
        if (p_alloc->data)
        {
            _vsc_fw_free_backup(p_alloc);
        }
    }

    VSC_FW_NOTI_BACKUP("free_all done\n");
    return 0;
}

static unsigned int vsc_fw_get_board_year(void)
{
	unsigned int year = 0;

#ifdef BUILD_FEATURE_y29_board
	year = 29;
#elif defined BUILD_FEATURE_y28_board
	year = 28;
#elif defined BUILD_FEATURE_y27_board
	year = 27;
#elif defined BUILD_FEATURE_y26_board
	year = 26;
#elif defined BUILD_FEATURE_y25_board
	year = 25;
#elif defined BUILD_FEATURE_y24_board
	year = 24;
#elif defined BUILD_FEATURE_y23_board
	year = 23;
#elif defined BUILD_FEATURE_y22_board
	year = 22;
#endif

	return year;
}

static int _vsc_fw_init_fw_opt(void)
{
    char hw_opt[32];
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;

    p_ctx->fw_opt = VSC_FW_OPT_NONE;
    p_ctx->usr_opt = VSC_FW_OPT_NONE;

    if (RET_OK==OS_ScanKernelCmdline("dispopts=%s", hw_opt))
    {
        if (strstr(hw_opt,"skipfw"))
        {
            p_ctx->fw_opt = VSC_FW_OPT_SKIP;
        }
        else if (strstr(hw_opt,"fwheader"))
        {
            p_ctx->fw_opt = VSC_FW_OPT_HEADER;
        }
        else if (RET_OK==OS_ScanKernelCmdlineToken("snapshot"))
        {
            if (strstr(hw_opt,"localfw"))
            {
                p_ctx->fw_opt = VSC_FW_OPT_LOCAL;
            }
            else
            {
                p_ctx->fw_opt = VSC_FW_OPT_NONE;
            }
        }
        else if (strstr(hw_opt,"pqefw"))
        {
            p_ctx->fw_opt = VSC_FW_OPT_BIN;
        }

        if (strstr(hw_opt,"userfw"))
        {
            p_ctx->usr_opt = VSC_FW_OPT_USR;
        }
        else if (strstr(hw_opt,"debugmap"))
        {
            p_ctx->usr_opt = VSC_FW_OPT_DBGMAP;
        }
    }

    p_ctx->year = vsc_fw_get_board_year();

    VSC_FW_NOTI_BACKUP("init fw_opt:%s, usr_opt:%s, year:%d\n",_g_vsc_fw_opt_str[p_ctx->fw_opt],_g_vsc_fw_opt_str[p_ctx->usr_opt],p_ctx->year);

    return 0;
}

static int _vsc_fw_backup_log(char *data)
{
    UINT32 i;
    struct vsc_fw_log *p_log;
    static UINT32 cnt = 0;

    if (!data)  return 0;

    if (cnt>=VSC_FW_NOTI_BUF_MAX)    cnt = 0;

    p_log = &(_g_vsc_fw_ctx.log[cnt]);
    OS_GetCurrentTicks(&(p_log->sec), &(p_log->msec), &(p_log->usec));
    memset(p_log->str, 0, VSC_FW_NOTI_STR_SIZE);

    for (i=0;i<VSC_FW_NOTI_STR_SIZE;i++)
    {
        p_log->str[i] = data[i];
        if (data[i] == 0) break;
    }

    cnt++;

    return 0;
}

static int _vsc_fw_mgr_io_de_init(void)
{
    int ret = RET_OK;
    LX_DE_PANEL_TYPE_T panel_type;

    VSC_FW_NOTI_BACKUP("mgr_io_de_init\n");

    panel_type = LX_PANEL_TYPE_3840;
    ret = resource_mgr_ioctl(DE_IOW_DE_INIT,(unsigned long)&panel_type,CALL_FROM_KERNEL);

    return ret;
}

static int _vsc_fw_get_file_name(int idx, char *name, unsigned int length)
{
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;

    if (!name) {VSC_FW_NOTI_BACKUP("file_name name null\n");return RET_ERROR;}

    memset(name,0,length);

    if (lx_chip() == LX_CHIP_O22 && p_ctx->year == 22)
    {
        snprintf(name,length,"/pqefw%d_%s_%s.bin",idx,"y22","a0");
    }

    VSC_FW_NOTI_BACKUP("file_name%d name(%s)\n",idx,name);
    return RET_OK;
}

static int _vsc_fw_alloc_path(struct vsc_fw_alloc *p_alloc, void *param, unsigned int flag)
{
    int ret = RET_ERROR;
    LX_DE_FW_DWLD_T *p = (LX_DE_FW_DWLD_T *)param;
    char file_name[32];

    do {
        if (!p_alloc) {VSC_FW_NOTI_BACKUP("alloc_p p_alloc null\n");break;}
        if (!param) {VSC_FW_NOTI_BACKUP("alloc_p param null\n");break;}
        if (flag != CALL_FROM_USER) {VSC_FW_NOTI_BACKUP("alloc_p from kernel : skip\n");break;}
        if (p_alloc->path) {VSC_FW_NOTI_BACKUP("alloc_p%d path already(kfree)\n",p->inx);kfree((void *)p_alloc->path);}
        if (p->size > VSC_FW_NOTI_STR_SIZE)  {VSC_FW_NOTI_BACKUP("alloc_p%d size(%d) over\n",p->inx,p->size);break;}

        ret = _vsc_fw_get_file_name(p->inx,file_name,32);
        if (ret != RET_OK)  {VSC_FW_NOTI_BACKUP("alloc_p%d _vsc_fw_get_file_name err\n",p->inx);break;}

        p_alloc->length = p->size;
        p_alloc->path = (char *)kzalloc(p_alloc->length, GFP_KERNEL);
        if (!p_alloc->path) {VSC_FW_NOTI_BACKUP("alloc_p%d kzalloc err\n",p->inx);break;}
        ret = copy_from_user(p_alloc->path, p->pData, p_alloc->length);
        if (ret != RET_OK)  {VSC_FW_NOTI_BACKUP("alloc_p%d copy_from_user err\n",p->inx);break;}
        if (0 == strlen(file_name))
        {
            VSC_FW_NOTI_BACKUP("alloc_p%d org only\n",p->inx);
        }
        else
        {
            char new_path[VSC_FW_NOTI_STR_SIZE];
            char org_path[VSC_FW_NOTI_STR_SIZE];
            char *org_file = NULL;
            memset(new_path,0,VSC_FW_NOTI_STR_SIZE);
            memset(org_path,0,VSC_FW_NOTI_STR_SIZE);
            strncpy(org_path,p_alloc->path,p_alloc->length);
            //VSC_FW_NOTI_BACKUP("alloc_p%d org(%s)\n",p->inx,org_path);
            org_file = strrchr(org_path,'/');
            if (!org_file) {VSC_FW_NOTI_BACKUP("alloc_p%d no matching : skip\n",p->inx);break;}
            strncpy(new_path,org_path,strlen(org_path)-strlen(org_file));
            strcat(new_path,file_name);
            VSC_FW_NOTI_BACKUP("alloc_p%d new(%s)\n",p->inx,new_path);
            p_alloc->length_new = strlen(new_path)+1;
            if (p_alloc->path_new) {VSC_FW_NOTI_BACKUP("alloc_p%d path_new already(kfree)\n",p->inx);kfree((void *)p_alloc->path_new);}
            p_alloc->path_new = (char *)kzalloc(p_alloc->length_new,GFP_KERNEL);
            if (!p_alloc->path_new) {VSC_FW_NOTI_BACKUP("alloc_p%d kzalloc err\n",p->inx);ret=RET_ERROR;break;}
            strncpy(p_alloc->path_new,new_path,p_alloc->length_new);
        }
    } while(0);

    return ret;
}

static struct vsc_fw_alloc _g_vsc_fw_header[] = {
    {.idx=0,.data=(void *)g_pqe_PAK_FW0_O24,.fw_size=sizeof(g_pqe_PAK_FW0_O24)},
    {.idx=1,.data=(void *)g_pqe_PAK_FW1_O24,.fw_size=sizeof(g_pqe_PAK_FW1_O24)},
    {.data=NULL}
};

static int _vsc_fw_alloc_backup(struct vsc_fw_alloc *p_alloc)
{
    int ret,idx;
    struct file *vsc_filp = NULL;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
    mm_segment_t old_fs;
#endif
    int fw_size = 0;
    char fw_path[VSC_FW_NOTI_STR_SIZE];
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;

    if (!p_alloc)
    {
        VSC_FW_NOTI_BACKUP("alloc p_alloc null\n");
        return RET_ERROR;
    }

    if (p_alloc->data)
    {
        /* free always */
        if (_g_vsc_fw_keep_symbol == 0 || p_alloc->flag == VSC_FW_FLAG_DBG || p_alloc->flag == VSC_FW_FLAG_NONE)
        {
            _vsc_fw_free_backup(p_alloc);
        }
        else
        {
            VSC_FW_NOTI_BACKUP("alloc already\n");
            return RET_ERROR;
        }
    }

    if (p_ctx->fw_opt == VSC_FW_OPT_HEADER)
    {
        int header_allock_ok = 0;
        struct vsc_fw_alloc *p_header = _g_vsc_fw_header;
        while (p_header->data)
        {
            if (p_header->idx == p_alloc->idx)  break;
            p_header++;
        }

        do {
            if (!p_header->data)                break;
            if (p_header->fw_size < (1<<10))    break;
            fw_size = p_header->fw_size;
            p_alloc->alloc_size = ((fw_size + (0x1<<12))>>12)<<12;//4k align
            VSC_FW_NOTI_BACKUP("alloc fw%d(%dk)(size:%d) vm (header)\n",p_alloc->idx,p_alloc->alloc_size>>10,fw_size);
            p_alloc->data = (void *)vmalloc(p_alloc->alloc_size);
            if (!p_alloc->data)   {VSC_FW_NOTI_BACKUP("backup vmalloc error\n");break;}
            p_alloc->fw_size = p_header->fw_size;
            memcpy((char*)p_alloc->data,(char*)p_header->data,p_alloc->fw_size);
            VSC_FW_NOTI_BACKUP("alloc fw%d done (header)\n",p_alloc->idx);
            header_allock_ok = 1;
        } while(0);

        if (header_allock_ok == 1)  return RET_OK;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
    old_fs = get_fs();
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    set_fs(KERNEL_DS);
    #else
    set_fs(get_ds());
    #endif
#endif
    do {
        idx = p_alloc->idx;
        ret = RET_ERROR;

        do {
            if (p_alloc->flag == VSC_FW_FLAG_NONE)  break;
            memset(fw_path,0,VSC_FW_NOTI_STR_SIZE);
            snprintf(fw_path,VSC_FW_NOTI_STR_SIZE,"/var/firmware/pqefw%d.bin",idx);
            vsc_filp = filp_open(fw_path, O_RDONLY, 0);
            if (!IS_ERR(vsc_filp))  {VSC_FW_NOTI_BACKUP("backup open(%s)\n",fw_path);ret = RET_OK;break;}
            VSC_FW_NOTI_BACKUP("alloc fw%d no bin(%ld)\n",idx,PTR_ERR(vsc_filp));
        } while(0);

        do {
            if (ret == RET_OK)  break;
            if (!p_alloc->path_new) break;
            vsc_filp = filp_open(p_alloc->path_new, O_RDONLY, 0);
            if (!IS_ERR(vsc_filp))  {VSC_FW_NOTI_BACKUP("backup open(%s)\n",p_alloc->path_new);ret = RET_OK;break;}
            VSC_FW_NOTI_BACKUP("alloc fw%d no path_new(%ld)\n",idx,PTR_ERR(vsc_filp));
        } while(0);

        do {
            if (ret == RET_OK)  break;
            if (!p_alloc->path) break;
            vsc_filp = filp_open(p_alloc->path, O_RDONLY, 0);
            if (!IS_ERR(vsc_filp))  {VSC_FW_NOTI_BACKUP("backup open(%s)\n",p_alloc->path);ret = RET_OK;break;}
            VSC_FW_NOTI_BACKUP("alloc fw%d no path(%ld)\n",idx,PTR_ERR(vsc_filp));
        } while(0);

        if (ret != RET_OK)   break;

        do {
            fw_size = vfs_llseek(vsc_filp, 0, SEEK_END);
            vfs_llseek(vsc_filp, 0, SEEK_SET);

            if (!fw_size)	{VSC_FW_NOTI_BACKUP("alloc bin size zero\n");ret = RET_ERROR;break;}

            p_alloc->alloc_size = ((fw_size + (0x1<<12))>>12)<<12;//4k align

            VSC_FW_NOTI_BACKUP("alloc fw%d(%dk)(size:%d) vm,rd\n",idx,p_alloc->alloc_size>>10,fw_size);
            p_alloc->data = (void *)vmalloc(p_alloc->alloc_size);
            if (!p_alloc->data)   {VSC_FW_NOTI_BACKUP("backup vmalloc error\n");ret = RET_ERROR;break;}
            p_alloc->fw_size = fw_size;

            vsc_filp->f_pos = 0;
            ret = kernel_read(vsc_filp, p_alloc->data, p_alloc->fw_size, &vsc_filp->f_pos);//vfs_read(legacy)
            if (ret<0)  {VSC_FW_NOTI_BACKUP("alloc kernel_read error(%d)\n",ret);ret = RET_ERROR;break;}

            VSC_FW_NOTI_BACKUP("alloc fw%d done\n",idx);
            ret = RET_OK;
        } while(0);

        filp_close(vsc_filp, NULL);  /* filp_close(filp, current->files) ?  */
    } while(0);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
    set_fs(old_fs);
#endif
    return ret;
}

static int _vsc_fw_free_backup(struct vsc_fw_alloc *p_alloc)
{
    if (!p_alloc)
    {
        VSC_FW_NOTI_BACKUP("free p_alloc null\n");
        return -1;
    }

    if (!p_alloc->data)
    {
        VSC_FW_NOTI_BACKUP("free fw%d already\n",p_alloc->idx);
        return -1;
    }

    vfree(p_alloc->data);
    p_alloc->data = NULL;
    p_alloc->alloc_size = 0;
    p_alloc->fw_size = 0;

    VSC_FW_NOTI_BACKUP("free fw%d done\n",p_alloc->idx);
    return 0;
}

static int _vsc_fw_chk_pc_all(void)
{
    int i;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_load *p_load = &(p_ctx->load);
    struct vsc_fw_load_param *p;

    if (!p_load->handler)   return -1;//not support

    for (i = (p_ctx->max_num-1); i>=0; i--)
    {
        p = p_load->param[i];
        if (!p)   continue;
        p_load->handler(p,VSC_FW_UPDATE_PC);
        //DE_NOTI("fw%d pc:0x%08x\n",i,p->pc);
    }

    return 0;
}

static unsigned int _vsc_fw_is_exce(unsigned int idx)
{
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_load *p_load = &(p_ctx->load);
    struct vsc_fw_load_param *p;

    if (!p_load->handler) {
        DE_NOTI("not support\n");
        return 0;
    }

    if (idx >= p_ctx->max_num) {
        DE_NOTI("no such idx(%d)\n",idx);
        return 0;
    }

    p = p_load->param[idx];
    if (!p) {
        DE_NOTI("no such param(%d)\n",idx);
        return 0;
    }

    p_load->handler(p,VSC_FW_UPDATE_EXCE);
    return p->exce;
}

static int _vsc_fw_chk_crc_valid(struct vsc_fw_crc *crc)
{
    if (!crc) {
        DE_ERROR("null input\n");
        return -1;
    }

    return (crc->h.magic == VSC_FW_CRC_MAGIC && crc->h.num > 0)? 0:-1;
}

static int _vsc_fw_update_bin_crc(struct vsc_fw_load_param *p)
{
    int ret = -1;
    int offset;
    char *bin_data;

    if (!p) {
        DE_ERROR("null input\n");
        return ret;
    }

    if (0 != _vsc_fw_chk_crc_valid(&p->crc)) {
        DE_NOTI("not support\n");
        return ret;
    }

    do {
        if (!p->crc.size) {DE_ERROR("fw%d no crc.size\n",p->idx);break;}
        if (!p->bin_data) {DE_ERROR("fw%d no bin_data\n",p->idx);break;}
        if (!p->bin_size) {DE_ERROR("fw%d no bin_size\n",p->idx);break;}
        offset = p->bin_size - (p->crc.size + (p->crc.h.num*sizeof(unsigned int)));
        if (offset < 0) {DE_ERROR("fw%d wrong offset(%d)\n",p->idx,offset);break;}

        bin_data = p->bin_data + offset;
        p->bin_u32 = *((unsigned int *)bin_data);
        p->bin_crc = vsc_util_crc32((const void *)bin_data,p->crc.size);
        DE_NOTI("fw%d update bin_u32:0x%08x bin_crc:0x%08x offset:0x%08x\n",p->idx,p->bin_u32,p->bin_crc,offset);
        ret = 0;
    } while(0);

    return ret;
}

static int _vsc_fw_update_mem_crc(struct vsc_fw_load_param *p, UINT32 use_dbg)
{
    int ret = -1;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_load *p_load = &(p_ctx->load);
    UINT32 *vmap_base = NULL;
    phys_addr_t hma_base = 0;

    if (!p) {
        DE_ERROR("null input\n");
        return ret;
    }

    if (0 != _vsc_fw_chk_crc_valid(&p->crc)) {
        DE_NOTI("not support\n");
        return ret;
    }

    do {
        if (!p->crc.size) {DE_ERROR("fw%d no crc.size\n",p->idx);break;}
        if (!p->bin_size) {DE_ERROR("fw%d no bin_size\n",p->idx);break;}

        p->mem_src = p->rom_base;
        p->mem_size = (((p->crc.size)>>14) + 1)<<14;//16k align

        if (p->secure)
        {
            if (use_dbg) {
                if (!p->hma_pool) {DE_ERROR("fw%d%s no hma_pool\n",p->idx,p->name);break;}
                if (!p->hma_size) {DE_ERROR("fw%d%s no hma_size\n",p->idx,p->name);break;}
                hma_base = hma_alloc_user(p->hma_pool, p->hma_size, (1<<14), p->name);//align:16k
                if (!hma_base) {
                    DE_ERROR("fw%d hma_alloc fail(%s,%d,%s)\n",p->idx,p->hma_pool,p->hma_size,p->name);
                    break;
                }
                DE_NOTI("fw%d hma_alloc(0x%x:%s,%d,%s)\n",p->idx,(UINT32)hma_base,p->hma_pool,p->hma_size,p->name);
                p->mem_dst = (UINT32)hma_base;
            }
            else {
                p->mem_dst = (UINT32)p->int_base;
            }
            if (!p_load->handler) {DE_ERROR("fw%d no handler\n",p->idx);break;}
            DE_NOTI("fw%d mem_cpy 0x%08x to 0x%08x (%d)\n",p->idx,p->mem_src,p->mem_dst,p->mem_size);
            if (0 != p_load->handler(p,VSC_FW_MEM_CPY)) {DE_ERROR("fw%d mem_cpy err\n",p->idx);break;}
            msleep(1);
        }
        else
        {
            p->mem_dst = p->rom_base;
        }

        if (!p->mem_dst) {DE_ERROR("%d no mem_dst\n",p->idx);break;}
        DE_NOTI("fw%d vmap(0x%08x,%d)\n",p->idx,p->mem_dst,p->mem_size);
        vmap_base = (void *)vmap_phys(p->mem_dst,p->mem_size);
        if (!vmap_base) {
            DE_ERROR("fw%d vmap err\n",p->idx);
            return -1;
        }

        rmb();
        p->mem_crc = vsc_util_crc32((const void *)vmap_base,p->crc.size);
        DE_NOTI("fw%d update mem_crc:0x%08x, size:%d\n",p->idx,p->mem_crc,p->crc.size);
        ret = 0;
    } while(0);

    if (hma_base) hma_free(p->hma_pool,hma_base);
    if (vmap_base) vunmap_phys((void*)vmap_base);

    return ret;
}

static int _vsc_fw_chk_mem_crc_all(void)
{
    int i;
    unsigned int ref_crc;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_load *p_load = &(p_ctx->load);
    struct vsc_fw_load_param *p;

    if (!p_load->handler)   return -1;//not support

    for (i = (p_ctx->max_num-1); i>=0; i--)
    {
        ref_crc = 0;
        p = p_load->param[i];
        if (p) {
            //DE_NOTI("fw%d update\n",p->idx);
            //p_load->handler(p,VSC_FW_LOAD_STOP);//stall off only
            if (0 == _vsc_fw_update_mem_crc(p,0)) {
                if (p->crc.crc > 0) {
                    ref_crc = p->crc.crc;
                }
                if (_g_vsc_fw_dbg == VSC_FW_DBG_BIN_CRC_MATCH) {
                    if (0 == _vsc_fw_update_bin_crc(p)) {
                        ref_crc = p->bin_crc;
                    }
                }
            }
        }

        if (ref_crc > 0) {
            DE_NOTI("fw%d 0x%08x(%s) vs.0x%08x\n",i,p->mem_crc,(p->mem_crc == ref_crc)? "o":"x",ref_crc);
        }
    }

    return 0;
}

static int _vsc_fw_load_all(void)
{
    int i, ret = 0;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_alloc *p_alloc;
    LX_DE_FW_DWLD_T fw_h = {.cfg = DE_FW_CFG_DOWNLOAD_HEADER,.size=0,.pData=NULL};

    for (i = (p_ctx->max_num-1); i>=0; i--)
    {
        p_alloc = &(p_ctx->alloc[i]);
        if (p_alloc->data != NULL && p_alloc->fw_size > 0)
        {
            VSC_FW_NOTI_BACKUP("load_all fw%d(%dk)(size:%d)\n",p_alloc->idx,p_alloc->alloc_size>>10,p_alloc->fw_size);
            ret = vsc_fw_hal_load(p_alloc->idx,DE_FW_CFG_COPY_MAP_TO_DDR,p_alloc->fw_size,(char *)p_alloc->data);
        }
        else
        {
            fw_h.inx = i;
            VSC_FW_NOTI_BACKUP("load_all fw%d cfg:%d -> header\n",fw_h.inx,fw_h.cfg);
            ret = DE_HAL_FW_DownloadFromHead(&fw_h);
        }
    }

    return ret;
}

static int _vsc_fw_chk_ready(void)
{
    int ret = RET_OK;
    int ipc_is_alive = 0;
    UINT32 count = 0, kick_out = 0;
    UINT64 base_tick = OS_GetMsecTicks();
    UINT64 curr_tick, diff_tick;
    #ifdef USE_VIDEO_FOR_FPGA
    #define FW_DOWNLOAD_MSLEEP    (100)
    #define FW_DOWNLOAD_TIMEOUT   (20000)
    #define FW_DOWNLOAD_TIMEOUT2  (40000)
    #else
    #define FW_DOWNLOAD_MSLEEP    (1)
    #define FW_DOWNLOAD_TIMEOUT   (400)
    #define FW_DOWNLOAD_TIMEOUT2  (800)
    #endif

    while (1) {
        msleep(FW_DOWNLOAD_MSLEEP);
        count++;

        _vsc_fw_chk_pc_all();

        ipc_is_alive = (_g_vsc_fw_dbg == VSC_FW_DBG_TEST_DO_RETRY && kick_out == 0)? 0:vsc_fw_is_working();
        if (ipc_is_alive) {
            if (_vsc_fw_is_exce(0)) {
                DE_HAL_FW_DumpStatus();
            }
            VSC_FW_NOTI_BACKUP("fw is working\n");
            break;
        }

        curr_tick = OS_GetMsecTicks();
        diff_tick = (curr_tick > base_tick)? (curr_tick-base_tick):0;

        if (diff_tick > FW_DOWNLOAD_TIMEOUT) {
            count = (count < FW_DOWNLOAD_TIMEOUT)? FW_DOWNLOAD_TIMEOUT:FW_DOWNLOAD_TIMEOUT2;
        }

        kick_out = (count == FW_DOWNLOAD_TIMEOUT2)? 2:(count == FW_DOWNLOAD_TIMEOUT)? 1:0;

        if (kick_out)
        {
            VSC_FW_NOTI_BACKUP("vsc_fwload timeout(%d)\n",kick_out);
            _vsc_fw_chk_mem_crc_all();
            DE_HAL_FW_DumpStatus();

            if (kick_out == 1)
            {
                if (_g_vsc_fw_dbg == VSC_FW_DBG_PANIC_1ST_FAIL) {panic("vsc_fwload fail(%d)\n",count);}
                if (_g_vsc_fw_dbg == VSC_FW_DBG_TEST_NO_RETRY) {DE_NOTI("test no retry(%d)\n",count);ret = RET_TIMEOUT;break;}
                _vsc_fw_load_all();
                base_tick = OS_GetMsecTicks();
            }
            else
            {
                DE_ERROR("<<<error>>> de firmware is not working\n");
                if (_g_vsc_fw_dbg == VSC_FW_DBG_PANIC_2ND_FAIL) {panic("vsc_fwload fail(%d)\n",count);}
                ret = RET_TIMEOUT;
                break;
            }
        }
    }

    return ret;
}

static int _vsc_fw_io_print_usrlog(LX_DE_FW_DWLD_T *param)
{
    int ret;
    int str_size;
    char usr_str[VSC_FW_NOTI_STR_SIZE];
    LX_DE_FW_DWLD_T *p = param;

    if (!p)
    {
        VSC_FW_NOTI_BACKUP("usrlog p null\n");
        return 0;
    }

    if (!p->pData)
    {
        VSC_FW_NOTI_BACKUP("usrlog pData null\n");
        return 0;
    }

    if (p->size <= 0)
    {
        VSC_FW_NOTI_BACKUP("usrlog size(%d) wrong\n",p->size);
        return 0;
    }

    str_size = (p->size < VSC_FW_NOTI_STR_SIZE)? p->size:VSC_FW_NOTI_STR_SIZE;
    ret = copy_from_user(usr_str, p->pData, str_size);
    if (ret != RET_OK)
    {
        VSC_FW_NOTI_BACKUP("usrlog copy_from_user err(ret:%d)\n",ret);
    }

    //VSC_FW_NOTI_BACKUP("usrlog %2d(%s)\n",str_size,usr_str);
    VSC_FW_NOTI_BACKUP("usrlog(%s)\n",usr_str);
    return 0;
}

static int _vsc_fw_thread(void *ptr)
{
    int ret, idx, cnt_max;
    struct file *vsc_filp = NULL;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
    mm_segment_t old_fs;
#endif
    static int retry_cnt = 0;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_alloc *p_alloc;
    LX_DE_FW_DWLD_T fw;

    cnt_max = (VSC_FW_TASK_DELAY_MSEC > 0)? (_g_vsc_fw_timeout_msec/VSC_FW_TASK_DELAY_MSEC):0;
    VSC_FW_NOTI_BACKUP("thread start(cnt_max:%d)\n",cnt_max);

    while (1)
    {
        msleep(VSC_FW_TASK_DELAY_MSEC);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
        old_fs = get_fs();
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        set_fs(KERNEL_DS);
        #else
        set_fs(get_ds());
        #endif
#endif
        vsc_filp = filp_open("/var/firmware", O_RDONLY, 0);
        if (!IS_ERR(vsc_filp))
        {
            filp_close(vsc_filp, NULL);
            ret = RET_OK;
        }
        else
        {
            ret = RET_ERROR;
        }
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
        set_fs(old_fs);
#endif
        if (ret == RET_OK || retry_cnt > cnt_max)
        {
            VSC_FW_NOTI_BACKUP("thread alloc(cnt:%d)\n",retry_cnt);
            for (idx = (p_ctx->max_num-1); idx>=0; idx--)
            {
                p_alloc = &(p_ctx->alloc[idx]);
                p_alloc->flag = VSC_FW_FLAG_DBG;
                ret = _vsc_fw_alloc_backup(p_alloc);

                fw.inx = idx;
                if (ret == RET_OK)
                {
                    fw.cfg = DE_FW_CFG_COPY_MAP_TO_DDR;
                    fw.size = p_alloc->fw_size;
                    fw.pData = (char *)p_alloc->data;
                }
                else
                {
                    fw.cfg = DE_FW_CFG_DOWNLOAD_HEADER;
                    fw.size = 0;
                    fw.pData = NULL;
                }
                ret = vsc_fw_io_download((void *)&fw,CALL_FROM_KERNEL);
            }
            ipc_hal_ready_to_use(1);
            ipc_hal_restore();
            break;
        }

        retry_cnt++;
    }

    VSC_FW_NOTI_BACKUP("thread done(cnt:%d)\n",retry_cnt);
    return 0;
}

void vsc_fw_print_status(struct seq_file *m)
{
    int i, ret;
    char tool[16] = "?";
    unsigned int temp = 0;
    struct vsc_fw_ctx *p_ctx = &_g_vsc_fw_ctx;
    struct vsc_fw_load *p_load = &(p_ctx->load);
    struct vsc_fw_load_param *p_param;
    struct vsc_fw_alloc *p_alloc;

    seq_printf(m, "=============================================================\n");
    seq_printf(m, "fw status\n");
    seq_printf(m, "=============================================================\n");
    seq_printf(m, "module param : keep_symbol:%x, use_int_pool:%x, dbg:%x\n",_g_vsc_fw_keep_symbol,_g_vsc_fw_use_int_pool,_g_vsc_fw_dbg);
    seq_printf(m, "fw_opt:%s, usr_opt:%s, usr_num:%d, max_num:%d, year:%d\n",\
        (p_ctx->fw_opt>=0 && p_ctx->fw_opt<VSC_FW_OPT_MAX)? _g_vsc_fw_opt_str[p_ctx->fw_opt]:"na",\
        (p_ctx->usr_opt>=0 && p_ctx->usr_opt<VSC_FW_OPT_MAX)? _g_vsc_fw_opt_str[p_ctx->usr_opt]:"na",p_ctx->usr_num,p_ctx->max_num,p_ctx->year);
    seq_printf(m, "timeout:%d, delay:%d, task:%p\n",_g_vsc_fw_timeout_msec,VSC_FW_TASK_DELAY_MSEC,p_ctx->task);

    if (RET_OK==OS_ScanKernelCmdline("pqe.tool=%s",tool))
    {
        seq_printf(m, "pqe.tool:%s\n",tool);
    }

    if (RET_OK==OS_ScanKernelCmdline("pqe.year=%d",(char *)&temp))
    {
        seq_printf(m, "pqe.year:%d\n",temp);
    }

    seq_printf(m, "=============================================================\n");
    for (i=0; i<p_ctx->max_num; i++)
    {
        p_alloc = &(p_ctx->alloc[i]);
        seq_printf(m, "[%d] id:%d, flag:%d, fw:%4d, alloc:%4d, p:%p\n",i,p_alloc->idx,p_alloc->flag,p_alloc->fw_size,p_alloc->alloc_size,p_alloc->data);
        if (p_alloc->path)
        {
            seq_printf(m, "[%d] cur len:%d, path(%s)\n",i,p_alloc->length,p_alloc->path);
        }
        if (p_alloc->path_new)
        {
            seq_printf(m, "[%d] new len:%d, path(%s)\n",i,p_alloc->length_new,p_alloc->path_new);
        }
    }

    seq_printf(m, "=============================================================\n");
    seq_printf(m, "fwload handler:%p\n",p_load->handler);
    seq_printf(m, "=============================================================\n");

    for (i=0; i<VSC_FW_MAX_NUM; i++)
    {
        p_param = p_load->param[i];
        if (!p_param) continue;
        seq_printf(m, "%-15s : %d\n","idx",p_param->idx);
        seq_printf(m, "%-15s : %s\n","name",p_param->name);
        seq_printf(m, "%-15s : %d (%s)\n","action",p_param->action,(p_param->action>=0 && p_param->action<VSC_FW_LOAD_MAX)? _g_vsc_fw_act_str[p_param->action]:"na");
        seq_printf(m, "%-15s : %d\n","secure",p_param->secure);
        seq_printf(m, "%-15s : 0x%08x(%c%c%c%c)\n","word",p_param->word,(p_param->word>>24)&0xff,(p_param->word>>16)&0xff,(p_param->word>>8)&0xff,p_param->word&0xff);
        seq_printf(m, "%-15s : %d (%s)\n","cfg",p_param->cfg,(p_param->cfg>=0 && p_param->cfg<DE_FW_CFG_MAX_NUM)? _g_vsc_fw_cfg_str[p_param->cfg]:"na");
        seq_printf(m, "%-15s : %d\n","bin_size",p_param->bin_size);
        seq_printf(m, "%-15s : %p\n","bin_data",p_param->bin_data);
        seq_printf(m, "%-15s : %s\n","hma_pool",p_param->hma_pool);
        seq_printf(m, "%-15s : 0x%08x\n","hma_base",(UINT32)p_param->hma_base);
        seq_printf(m, "%-15s : 0x%08x\n","hma_base_bkup",(UINT32)p_param->hma_base_bkup);
        seq_printf(m, "%-15s : %d\n","hma_size",p_param->hma_size);
        seq_printf(m, "%-15s : %s\n","int_pool",p_param->int_pool);
        seq_printf(m, "%-15s : 0x%08x\n","int_base",(UINT32)p_param->int_base);
        seq_printf(m, "%-15s : 0x%08x\n","vmap_phys",(UINT32)p_param->vmap_phys);
        seq_printf(m, "%-15s : %p\n","vmap_base",p_param->vmap_base);
        seq_printf(m, "%-15s : %p\n","vmap_base_bkup",p_param->vmap_base_bkup);
        seq_printf(m, "%-15s : %d\n","vmap_size",p_param->vmap_size);
        seq_printf(m, "%-15s : 0x%08x\n","src_base",(UINT32)p_param->src_base);
        seq_printf(m, "%-15s : 0x%08x\n","dst_base",(UINT32)p_param->dst_base);
        seq_printf(m, "%-15s : 0x%08x\n","rom_base",p_param->rom_base);
        ret = _vsc_fw_update_mem_crc(p_param,1);
        seq_printf(m, "%-15s : 0x%08x\n","mem_src",p_param->mem_src);
        seq_printf(m, "%-15s : 0x%08x\n","mem_dst",p_param->mem_dst);
        seq_printf(m, "%-15s : %d\n","mem_size",p_param->mem_size);
        seq_printf(m, "%-15s : 0x%08x(ret:%d)\n","mem_crc",p_param->mem_crc,ret);
        seq_printf(m, "%-15s : 0x%08x\n","crc.h.u32",p_param->crc.h.u32);
        seq_printf(m, "%-15s : 0x%08x(%d)\n","crc.size",p_param->crc.size,p_param->crc.size);
        seq_printf(m, "%-15s : 0x%08x\n","crc.crc",p_param->crc.crc);
        ret = _vsc_fw_update_bin_crc(p_param);
        seq_printf(m, "%-15s : 0x%08x(ret:%d)\n","bin_crc",p_param->bin_crc,ret);
        seq_printf(m, "%-15s : 0x%08x\n","bin_u32",p_param->bin_u32);
        if (p_load->handler) p_load->handler(p_param,VSC_FW_UPDATE_PC);
        seq_printf(m, "%-15s : 0x%08x\n","pc",p_param->pc);
        if (p_load->handler) p_load->handler(p_param,VSC_FW_UPDATE_EXCE);
        seq_printf(m, "%-15s : 0x%08x\n","exce",p_param->exce);
        seq_printf(m, "%-15s : %s\n","err_mesg",(p_param->err_mesg)? p_param->err_mesg:"null");
        seq_printf(m, "=============================================================\n");
    }
}
