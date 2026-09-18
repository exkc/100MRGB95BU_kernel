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
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <asm/io.h>

#include "base_types.h"
#include "debug_util.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "vsc_cg.h"

#ifdef INCLUDE_KDRV_BE
#include "be_kapi.h"
#include "../be/be_def.h"
#include "../be/frc/frc_hal.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
struct vsc_cg_ctx {
    unsigned int update;
    struct vsc_cg_cfg *cfgs;
    int(*set_cfg)(struct vsc_cg_cfg *);
    void(*status)(struct seq_file *);
};

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
void vsc_cg_register_status(void(*status)(struct seq_file *));
void vsc_cg_print_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static struct vsc_cg_cfg _g_vsc_cg_cfgs[] = {
    {.name="dnsr0",.ip=vsc_cg_ip_dnsr0,.en=0},
    {.name="dnsr1",.ip=vsc_cg_ip_dnsr1,.en=0},
    {.name=NULL},
};

static struct vsc_cg_ctx _g_vsc_cg_ctx;

static uint _g_vsc_cg_dbg = 1;
module_param_named(vsc_cg_dbg, _g_vsc_cg_dbg, uint, 0644);

/*========================================================================================
 *	 Implemontation Group
 *=======================================================================================*/
void vsc_cg_register_set_cfg(int(*set_cfg)(struct vsc_cg_cfg *))
{
    if (!set_cfg)   return;
    _g_vsc_cg_ctx.set_cfg = set_cfg;
}

void vsc_cg_register_status(void(*status)(struct seq_file *))
{
    if (!status)   return;
    _g_vsc_cg_ctx.status = status;
}

int vsc_cg_init(void)
{
    memset(&_g_vsc_cg_ctx,0,sizeof(_g_vsc_cg_ctx));
    _g_vsc_cg_ctx.cfgs = _g_vsc_cg_cfgs;

    if (0) { }
#ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26) {
        extern void vsc_cg_o26_init(void);
        vsc_cg_o26_init();
    }
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24) {
        extern void vsc_cg_o24_init(void);
        vsc_cg_o24_init();
    }
#endif
    else {
        //not support
    }

    return 0;
}

int vsc_cg_handler(char *cmd)
{
    int ret = 0;
    int skip = 1;
    size_t cmd_len;
    char *tok, *sav_tok;
    char cmd_org[128];
    char delim[] = ":= \t\n";
    struct vsc_cg_ctx *p = &_g_vsc_cg_ctx;
    struct vsc_cg_cfg *p_cfg;

    if (!cmd)           return -1;
    if (!p->set_cfg)    return 0;//not support
    if (!p->cfgs)       return 0;//not support

    DE_NOTI("cmd (%s)\n",cmd);
    p->update = 0;

    cmd_len = (strlen(cmd)>126)? 126:strlen(cmd);
    strncpy(cmd_org,cmd,cmd_len);
    cmd_org[cmd_len] = '\0';

    tok=simple_strtok(cmd, delim, &sav_tok);
    if (tok) {
        if (!strncasecmp(tok,"REQ_CG_CTRL", strlen("REQ_CG_CTRL"))) {
            skip = 0;
        }
    }

    if (skip) {
        DE_NOTI("tok(%s) sav_tok(%s) skip\n",tok,sav_tok);
        return 0;//do nothing
    }

    tok=simple_strtok(NULL, delim, &sav_tok);
    while (tok) {
        p_cfg = p->cfgs;
        while (p_cfg->name) {
            if (!strncasecmp(tok, p_cfg->name, strlen(p_cfg->name)))
            {
                tok=simple_strtok(NULL, delim, &sav_tok);
                if (tok)
                {
                    unsigned int en = 0;
                    DE_NOTI("tok(%s) sav_tok(%s) chk en\n",tok,sav_tok);
                    if(1 != sscanf(tok, "%d", &en))
                    {
                        DE_ERROR("invalid param(%s)\n", tok);
                    }
                    p_cfg->en = en;
                    p_cfg->dbg = _g_vsc_cg_dbg;
                    if (p->set_cfg) {
                        p->update |= p_cfg->ip;
                        DE_NOTI("set_cfg(%s) ip:0x%x en:%d (up:0x%x)\n",p_cfg->name,p_cfg->ip,p_cfg->en,p->update);
                        ret = p->set_cfg(p_cfg);
                    }
                }
                break;
            }
            p_cfg++;
        }

        tok=simple_strtok(NULL, delim, &sav_tok);
    }

    if (p->update) {
        OS_MsecSleep(1);
        DE_NOTI("send done(up:0x%x)\n",p->update);
        vsc_cg_noti_to_mcu("%s done",cmd_org);
    }

    return 0;
}

int vsc_cg_noti_to_mcu(const char *fmt, ...)
{
    #ifdef INCLUDE_KDRV_BE
    int len;
    va_list ap;
    char buf[128]="cpu_noti ";
    size_t prefix_len = strlen(buf);
    LX_BE_FRC_CMD_T param;

    va_start(ap, fmt);
    len = vsnprintf(buf+prefix_len, 64, fmt, ap);
    va_end(ap);
    if (len <= 0 || len >= (64+prefix_len)) return -1;

    memset(&param,0,sizeof(param));
    strncpy(param.str,buf,strlen(buf));
    DE_NOTI("str(%d)(%s)\n",len,param.str);
    BE_FRC_HAL_RunCommand(&param);
    #endif
    return 0;
}

void vsc_cg_print_status(struct seq_file *m)
{
    struct vsc_cg_ctx *p = &_g_vsc_cg_ctx;
    struct vsc_cg_cfg *p_cfg;

    seq_printf(m, "=============================================================\n");
    seq_printf(m, "cg status\n");
    seq_printf(m, "=============================================================\n");
    seq_printf(m, "module param : vsc_cg_dbg:%x\n",_g_vsc_cg_dbg);
    seq_printf(m, "=============================================================\n");
    p_cfg = p->cfgs;
    while (p_cfg->name) {
        seq_printf(m, "%-9s : ip:0x%x, en:%d, dbg:%d\n",p_cfg->name,p_cfg->ip,p_cfg->en,p_cfg->dbg);
        seq_printf(m, "=============================================================\n");
        p_cfg++;
    }
    if (p->status) {p->status(m);}
    seq_printf(m, "=============================================================\n");
}
