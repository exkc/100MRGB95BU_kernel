
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#include "common/ipc_reg_offs.h"
#include "ipc/adec_ipc.h"
#include "ipc/adec_ipc_dbg.h"
#include "imc/adec_imc.h"
#include "imc/aimc_internal.h"
#include "imc/cmd/module_cmd_manager.h"

#include "reg_peri_ctrl.h"
#include "reg_dsp_ctrl.h"
#include "ipc_regs.h"

#include "module_list.h"
#include "user_imc.h"
#include "kaimc.h"
#include "regs.h"

#include "os_util.h"
#include "hma_alloc.h"

#include "log.h"
#include "dsp_control.h"
#include "block_manager.h"

logm_define (aud_kaimc, log_level_noti);
#define trace(fmt,args...)  logm_trace(aud_kaimc,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_kaimc,fmt,##args)
#define info(fmt,args...)   logm_info(aud_kaimc,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_kaimc,fmt,##args)
#define error(fmt,args...)  logm_error(aud_kaimc,fmt,##args)

#define AUDIO_IMC_LOCK()		mutex_lock(&_gaimc_mutex)
#define AUDIO_IMC_UNLOCK()		mutex_unlock(&_gaimc_mutex)

#define AUDIO_IMC_WQ_LOCK()		mutex_lock(&_gaimc_wq_mutex)
#define AUDIO_IMC_WQ_UNLOCK()	mutex_unlock(&_gaimc_wq_mutex)

struct aimc
{
    struct _ImcInfo imc_info;
    struct list_head noti_list;

    bool dead[NUM_OF_DSP];
    int evt_id[NUM_OF_DSP];
};

struct noti_info
{
    struct list_head list;

    int (*callback_func) (void *, int, void *);
    void *callback_param;
    struct work_struct ws;

    unsigned int target;
    unsigned int event;
    bool repeat;
    unsigned int action_id;

    struct mutex param_lock;
    struct list_head param_list;
};

struct noti_param
{
    struct list_head list;

    int size;
    unsigned char param[0];
};

static struct aimc _gaimc = { };

struct aimc *gaimc = &_gaimc;
static struct _ImcInfo *gimc_info;
static bool stop_imc = false;
static struct aud_mod_owner *gowner;

void aimc_send_irq (int dspnum)
{
    if (dspnum == 0)
    {
        PERI_WR_NAME (CPUTODSP0, 1);
    }
    else if (dspnum == 1)
    {
        PERI_WR_NAME (CPUTODSP1, 1);
    }
    else if (dspnum == 2)
    {
        PERI_WR_NAME (CPUTODSP2, 1);
    }
    else
    {
#if (NUM_OF_DSP >= 4)
        PERI_WR_NAME (CPUTODSP3, 1);
#endif
    }
}

struct ipc_desc
{
    int dsp_index;
    const char *name;
    uint32_t syncWord;
    uint32_t bufSize;
    int role;                   // type of (IpcRole). or -1 for between dsps

    unsigned int ipcoff_base;
    unsigned int ipcoff_size;
    unsigned int ipcoff_wr;
    unsigned int ipcoff_rd;

    void (*send_irq) (void *);

    void *pIpc;
    void *ipcmem_base;
    phys_addr_t mem_paddr;
    void *mem_vaddr;
    volatile uint32_t *reg_wroff;
    volatile uint32_t *reg_rdoff;
};

static void irq_to_dsp (void *_param)
{
    struct ipc_desc *ipc = _param;

    trace ("irq to dsp%d\n", ipc->dsp_index);
    aimc_send_irq (ipc->dsp_index);
}

#define AUDIO_IPC_MAGIC_CODE        0x01444542
#define AUDIO_IPC_BUF_SIZE          0x19000     // 100Kbytes
#define AUDIO_IPC_DBG_MAGIC_CODE    0x19C0DB90

static struct ipc_desc ipc_descs[] = {
    /* *INDENT-OFF* */
    {0, "ipc-H20", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_WRITER,     AUD_IPCOFFS_MEM_IPC_A2D_BASE,  AUD_IPCOFFS_MEM_IPC_A2D_SIZE,  AUD_IPCOFFS_IPC_A2D_WPTR,  AUD_IPCOFFS_IPC_A2D_RPTR,  irq_to_dsp,},
    {0, "ipc-02H", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_READER,     AUD_IPCOFFS_MEM_IPC_D2A_BASE,  AUD_IPCOFFS_MEM_IPC_D2A_SIZE,  AUD_IPCOFFS_IPC_D2A_WPTR,  AUD_IPCOFFS_IPC_D2A_RPTR,  },
    {1, "ipc-H21", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_WRITER,     AUD_IPCOFFS_MEM_IPC_A2P_BASE,  AUD_IPCOFFS_MEM_IPC_A2P_SIZE,  AUD_IPCOFFS_IPC_A2P_WPTR,  AUD_IPCOFFS_IPC_A2P_RPTR,  irq_to_dsp,},
    {1, "ipc-12H", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_READER,     AUD_IPCOFFS_MEM_IPC_P2A_BASE,  AUD_IPCOFFS_MEM_IPC_P2A_SIZE,  AUD_IPCOFFS_IPC_P2A_WPTR,  AUD_IPCOFFS_IPC_P2A_RPTR,  },
    {2, "ipc-H22", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_WRITER,     AUD_IPCOFFS_MEM_IPC_A2M_BASE,  AUD_IPCOFFS_MEM_IPC_A2M_SIZE,  AUD_IPCOFFS_IPC_A2M_WPTR,  AUD_IPCOFFS_IPC_A2M_RPTR,  irq_to_dsp,},
    {2, "ipc-22H", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_READER,     AUD_IPCOFFS_MEM_IPC_M2A_BASE,  AUD_IPCOFFS_MEM_IPC_M2A_SIZE,  AUD_IPCOFFS_IPC_M2A_WPTR,  AUD_IPCOFFS_IPC_M2A_RPTR,  },
#if (NUM_OF_DSP >= 4)
    {3, "ipc-H23", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_WRITER,     AUD_IPCOFFS_MEM_IPC_A2E_BASE,  AUD_IPCOFFS_MEM_IPC_A2E_SIZE,  AUD_IPCOFFS_IPC_A2E_WPTR,  AUD_IPCOFFS_IPC_A2E_RPTR,  irq_to_dsp,},
    {3, "ipc-32H", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, IPC_ROLE_READER,     AUD_IPCOFFS_MEM_IPC_E2A_BASE,  AUD_IPCOFFS_MEM_IPC_E2A_SIZE,  AUD_IPCOFFS_IPC_E2A_WPTR,  AUD_IPCOFFS_IPC_E2A_RPTR,  },
#endif
    {0, "ipc-022", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_D2M_BASE,  AUD_IPCOFFS_MEM_IPC_D2M_SIZE,  },
    {2, "ipc-220", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_M2D_BASE,  AUD_IPCOFFS_MEM_IPC_M2D_SIZE,  },
#ifdef SUPPORT_SOUNDBAR
    {0, "ipc-021", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_D2P_BASE,  AUD_IPCOFFS_MEM_IPC_D2P_SIZE,  },
    {2, "ipc-120", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_P2D_BASE,  AUD_IPCOFFS_MEM_IPC_P2D_SIZE,  },
#endif
    {2, "ipc-221", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_M2P_BASE,  AUD_IPCOFFS_MEM_IPC_M2P_SIZE,  },
    {1, "ipc-122", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_P2M_BASE,  AUD_IPCOFFS_MEM_IPC_P2M_SIZE,  },
#if (NUM_OF_DSP >= 4)
    {3, "ipc-322", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_E2M_BASE,  AUD_IPCOFFS_MEM_IPC_E2M_SIZE,  },
    {2, "ipc-223", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_M2E_BASE,  AUD_IPCOFFS_MEM_IPC_M2E_SIZE,  },
    {3, "ipc-320", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_E2D_BASE,  AUD_IPCOFFS_MEM_IPC_E2D_SIZE,  },
    {0, "ipc-023", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_D2E_BASE,  AUD_IPCOFFS_MEM_IPC_D2E_SIZE,  },
#ifdef SUPPORT_SOUNDBAR
    {3, "ipc-321", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_E2P_BASE,  AUD_IPCOFFS_MEM_IPC_E2P_SIZE,  },
    {1, "ipc-123", AUDIO_IPC_MAGIC_CODE,     AUDIO_IPC_BUF_SIZE, -1,                  AUD_IPCOFFS_MEM_IPC_P2E_BASE,  AUD_IPCOFFS_MEM_IPC_P2E_SIZE,  },
#endif
#endif
    {0, "ipcdbg0", AUDIO_IPC_DBG_MAGIC_CODE, AUDIO_IPC_BUF_SIZE, IPC_ROLE_DBG_READER, AUD_IPCOFFS_MEM_IPC_DBGD_BASE, AUD_IPCOFFS_MEM_IPC_DBGD_SIZE, AUD_IPCOFFS_IPC_DBGD_WPTR, AUD_IPCOFFS_IPC_DBGD_RPTR, },
    {1, "ipcdbg1", AUDIO_IPC_DBG_MAGIC_CODE, AUDIO_IPC_BUF_SIZE, IPC_ROLE_DBG_READER, AUD_IPCOFFS_MEM_IPC_DBGP_BASE, AUD_IPCOFFS_MEM_IPC_DBGP_SIZE, AUD_IPCOFFS_IPC_DBGP_WPTR, AUD_IPCOFFS_IPC_DBGP_RPTR, },
    {2, "ipcdbg2", AUDIO_IPC_DBG_MAGIC_CODE, AUDIO_IPC_BUF_SIZE, IPC_ROLE_DBG_READER, AUD_IPCOFFS_MEM_IPC_DBGM_BASE, AUD_IPCOFFS_MEM_IPC_DBGM_SIZE, AUD_IPCOFFS_IPC_DBGM_WPTR, AUD_IPCOFFS_IPC_DBGM_RPTR, },
#if (NUM_OF_DSP >= 4)
    {3, "ipcdbg3", AUDIO_IPC_DBG_MAGIC_CODE, AUDIO_IPC_BUF_SIZE, IPC_ROLE_DBG_READER, AUD_IPCOFFS_MEM_IPC_DBGE_BASE, AUD_IPCOFFS_MEM_IPC_DBGE_SIZE, AUD_IPCOFFS_IPC_DBGE_WPTR, AUD_IPCOFFS_IPC_DBGE_RPTR, },
#endif
    /* *INDENT-ON* */
};

static DEFINE_MUTEX (_gaimc_mutex);
static DEFINE_MUTEX (_gaimc_wq_mutex);


static struct aud_proc_info *dsp_processor[NUM_OF_DSP];

static ADEC_RESULT manager_cmd (void *_module, int _cmd, ImcSenderInfo * _sender, void *_param,
    int _paramLen)
{
    trace ("cmd %x\n", _cmd);

    if (_sender == NULL)
    {
        error ("param(_sender) is null\n");
        return ADEC_ERR_NONE;
    }

    trace ("sender module=%d, core=%d, requestResponse=%d, id=%d, paramLen=%d\n",
        _sender->module, _sender->core, _sender->requesetReponse, _sender->id, _paramLen);

    switch (_cmd)
    {
        case MANAGER_CMD_ADD_PROCESSOR:
        case MANAGER_CMD_ADD_MODULE_IMPL:
        {
            unsigned int dsp_num = _sender->core - ADEC_CORE_DSP0;

            if (dsp_num >= ARRAY_SIZE (dsp_processor))
            {
                error ("wrong dsp number. %d\n", dsp_num);
                break;
            }

            if (_cmd == MANAGER_CMD_ADD_PROCESSOR)
            {
                dsp_processor[dsp_num] = aud_modlist_reset_dsp (dsp_num);
            }
            else
            {
                ManagerCmdAddModuleImpl *impl_param = _param;

                if (!dsp_processor[dsp_num])
                {
                    error ("no ADD_PROCESSOR\n");
                    break;
                }

                impl_param->name[sizeof (impl_param->name) - 1] = 0;

                aud_modlist_register_impl (dsp_processor[dsp_num], impl_param->name,
                    impl_param->rank);
            }

            break;
        }
        case MANAGER_CMD_ADD_MODULE_IMPL_PORT_BUF_DEF:
        {
            unsigned int dsp_num = _sender->core - ADEC_CORE_DSP0;
            ManagerCmdAddModuleImplPortBufDef *portbufdef_param = _param;

            if (dsp_num >= ARRAY_SIZE (dsp_processor))
            {
                error ("wrong dsp number. %d\n", dsp_num);
                break;
            }

            aud_modlist_register_impl_port_buf_def (dsp_processor[dsp_num], portbufdef_param->name,
                portbufdef_param->def_num, portbufdef_param->max_num_au,
                portbufdef_param->max_access_size);

            break;
        }

        case MANAGER_CMD_ADD_DONE:
        {
            unsigned int dsp_num = _sender->core - ADEC_CORE_DSP0;

            if (dsp_num >= ARRAY_SIZE (dsp_processor))
            {
                error ("wrong dsp number. %d\n", dsp_num);
                break;
            }

            IMC_RaiseNamedEvent (gimc_info, AUD_MODID_REGISTRY (ADEC_CORE_ARM),
                "firmware-init-done", &_sender->core, sizeof (_sender->core));
            break;
        }

        case MANAGER_CMD_DUMP_DONE:
        {
            unsigned int dsp_num = _sender->core - ADEC_CORE_DSP0;

            if (dsp_num >= ARRAY_SIZE (dsp_processor))
            {
                error ("wrong dsp number. %d\n", dsp_num);
                break;
            }

            info ("manager received dump done message\n");
            IMC_RaiseNamedEvent (gimc_info, AUD_MODID_REGISTRY (ADEC_CORE_ARM),
                "dsp-dump-done", &_sender->core, sizeof (_sender->core));
            break;
        }

        default:
            break;
    }

    if (_sender->requesetReponse == IMC_RESPONSE_REQUIRED)
    {
        ImcResponseParameter response;
        response.target = *_sender;
        response.sender = ADEC_MODULE_MAN_ARM;
        response.requestInterrupt = IMC_INTERRUPT_REQUIRED;
        response.cmd = _cmd;
        response.result = (ADEC_RESULT) ADEC_ERR_NOT_IMPLEMENTED;
        response.param = NULL;
        response.paramLen = 0;

        IMC_Response (IMC_GetLocalImc (0), &response);
    }

    return ADEC_ERR_NONE;
}

static int handle_imc (struct _ImcInfo *imc, IpcHeader * header)
{
    int proc_id;

    proc_id = AUD_MODLIST_CORE (header->targetInfo.target);
    if (proc_id == 0)
        proc_id = ModuleList_FindModule (header->targetInfo.target);

    trace ("proc %d, cmd %x, sender %x, target %x, target action %x\n", proc_id,
        header->cmd, header->senderInfo.sender,
        header->targetInfo.target, header->targetInfo.actionFlag);
    if (proc_id == ADEC_CORE_ARM || header->senderInfo.sender == ADEC_CORE_ARM)
    {
        IMC_ProcessHeader (imc, header);
        return 0;
    }

    return ausrimc_post_imc (proc_id, header, header->param);
}

static int imc_ipc_send (struct _ImcInfo *imc_info, unsigned int target_processor,
    struct _IpcHeader *ipc_header, void *param)
{
    void *ipc_handle = NULL;
    ADEC_RESULT res;
    int i;

    if (stop_imc)
    {
        return ADEC_ERR_NONE;
    }

    for (i = 0; i < NUM_OF_DSP; i++)
    {
        if (target_processor == ADEC_CORE_DSP0 + i)
        {
            ipc_handle = ipc_descs[i * 2].pIpc;
            break;
        }
    }

    if (!ipc_handle)
    {
        int processor_id;

        processor_id = AUD_MODLIST_CORE (ipc_header->targetInfo.target);
        debug ("send ipc to proc%d\n", processor_id);

        return ausrimc_post_imc (processor_id, ipc_header, param);
    }

    res = IPC_WriteCommand (ipc_handle, ipc_header, param, 1);

    return -res;
}

int aimc_process_header (IpcHeader * header)
{
    int ret, proc_id;

    proc_id = ModuleList_FindModule (header->targetInfo.target);

    AUDIO_IMC_WQ_LOCK ();
    if (gimc_info)
    {
        struct _ImcInfo *imc = gimc_info;

        if (proc_id == ADEC_CORE_ARM)
            ret = IMC_ProcessHeader (imc, header);
        else
            ret = imc_ipc_send (imc, proc_id, header, header->param);
    }
    else
    {
        error ("no imc\n");
        ret = -1;
    }
    AUDIO_IMC_WQ_UNLOCK ();

    return ret;
}

/* command handler */
struct command_handler
{
    struct command_handler *next;

    unsigned int target;
    int (*handler) (void *arg, unsigned int cmd, void *param, unsigned int param_size);
    void *arg;
};

static struct command_handler *handler_root;
static DEFINE_MUTEX (handler_root_lock);

static int imc__register_command_handler (struct _ImcInfo *imc_info, unsigned int target,
    int (*command_handler) (void *arg, unsigned int cmd, void *param, unsigned int param_size),
    void *command_handler_arg)
{
    struct command_handler *new;
    int res = 0;

    mutex_lock (&handler_root_lock);
    new = handler_root;
    while (new)
    {
        if (new->target == target)
            break;
        new = new->next;
    }
    if (!new)
    {
        new = kzalloc (sizeof (*new), GFP_KERNEL);
        if (new)
        {
            new->target = target;

            new->next = handler_root;
            handler_root = new;
        }
    }

    if (new)
    {
        new->handler = command_handler;
        new->arg = command_handler_arg;
    }
    else
    {
        error ("Oops\n");
        res = -1;
    }
    mutex_unlock (&handler_root_lock);

    return res;
}

void aimc__unregister_command_handler (struct _ImcInfo *imc_info, unsigned int target)
{
    struct command_handler *now, *pre;

    mutex_lock (&handler_root_lock);
    pre = NULL;
    now = handler_root;
    while (now)
    {
        if (now->target == target)
        {
            if (!pre)
                handler_root = now->next;
            else
                pre->next = now->next;
            kfree (now);

            break;
        }
        pre = now;
        now = now->next;
    }

    if (!now)
        error ("no such uid. %x\n", target);
    mutex_unlock (&handler_root_lock);
}

static int imc_dispatch_command (struct _ImcInfo *imc_info, unsigned int target,
    unsigned int cmd, void *param, unsigned int param_size,
    unsigned int sender, unsigned int message_id, unsigned int flags)
{
    struct command_handler *now, handler;
    int res = 0;

#if 0
    if (cmd == BM_CMD_PROCESS_EVT_REMOTE &&
        ADEC_MODULE_EXT_BUF_0 <= target && target <= ADEC_MODULE_EXT_BUF_14)
    {
        AUDIO_BufferTriggerExtBuf (target, param);
        return 0;
    }
#endif

    mutex_lock (&handler_root_lock);
    now = handler_root;
    while (now)
    {
        if (now->target == target)
            break;
        now = now->next;
    }

    if (now)
    {
        PFN_ImcCmdProc h;
        ImcSenderInfo sender_info = { };

        handler = *now;
        mutex_unlock (&handler_root_lock);

        debug ("from %x to %x, cmd %x\n", sender, target, cmd);
        sender_info.module = sender;
        sender_info.id = message_id;
        sender_info.core = ModuleList_FindModule (sender);

        h = (void *) handler.handler;
        res = h (handler.arg, cmd, &sender_info, param, param_size);
        res = -res;
    }
    else
    {
        error ("no handler for %x\n", target);
        res = -1;
        mutex_unlock (&handler_root_lock);
    }

    return res;
}

static void dspirq_ipc_message (void)
{
    AUDIO_IMC_WQ_LOCK ();

    if (gimc_info)
    {
        int i;

        for (i = 0; i < NUM_OF_DSP; i++)
        {
            while (1)
            {
                ADEC_RESULT ret;
                IpcHeader *header;

                ret = IPC_ReadHeaderAddr (ipc_descs[i * 2 + 1].pIpc, &header);
                if (ret != ADEC_ERR_NONE)
                    break;

                handle_imc (gimc_info, header);

                IPC_ReadHeaderDone (ipc_descs[i * 2 + 1].pIpc);
            }
        }
    }
    else
        error ("no imc\n");

    AUDIO_IMC_WQ_UNLOCK ();

    return;
}

static bool no_dsp_message;
module_param (no_dsp_message, bool, 0644);

static bool use_printk_message;
module_param (use_printk_message, bool, 0644);

static void aud0 (unsigned int ts, const char *str)
{
    if (!no_dsp_message)
    {
        unsigned long long lltmp;
        unsigned int sec, usec;

        lltmp = 100ULL * ts;
        do_div (lltmp, 9);
        usec = do_div (lltmp, 1000000);
        sec = lltmp;

        if (use_printk_message)
            printk ("aud0 %4u.%06u] %s", sec, usec, str);
        else
            noti ("%4u.%06u] %s", sec, usec, str);
    }

    return;
}

static void aud1 (unsigned int ts, const char *str)
{
    if (!no_dsp_message)
    {
        unsigned long long lltmp;
        unsigned int sec, usec;

        lltmp = 100ULL * ts;
        do_div (lltmp, 9);
        usec = do_div (lltmp, 1000000);
        sec = lltmp;

        if (use_printk_message)
            printk ("aud1 %4u.%06u] %s", sec, usec, str);
        else
            noti ("%4u.%06u] %s", sec, usec, str);
    }

    return;
}

static void aud2 (unsigned int ts, const char *str)
{
    if (!no_dsp_message)
    {
        unsigned long long lltmp;
        unsigned int sec, usec;

        lltmp = 100ULL * ts;
        do_div (lltmp, 9);
        usec = do_div (lltmp, 1000000);
        sec = lltmp;

        if (use_printk_message)
            printk ("aud2 %4u.%06u] %s", sec, usec, str);
        else
            noti ("%4u.%06u] %s", sec, usec, str);
    }

    return;
}

static void aud3 (unsigned int ts, const char *str)
{
    if (!no_dsp_message)
    {
        unsigned long long lltmp;
        unsigned int sec, usec;

        lltmp = 100ULL * ts;
        do_div (lltmp, 9);
        usec = do_div (lltmp, 1000000);
        sec = lltmp;

        if (use_printk_message)
            printk ("aud3 %4u.%06u] %s", sec, usec, str);
        else
            noti ("%4u.%06u] %s", sec, usec, str);
    }

    return;
}

void aud_log_default (int proc_num, unsigned int ts, const char *string)
{
    if (proc_num == ADEC_CORE_DSP0)
        aud0 (ts, string);
    else if (proc_num == ADEC_CORE_DSP1)
        aud1 (ts, string);
    else if (proc_num == ADEC_CORE_DSP2)
        aud2 (ts, string);
    else
        aud3 (ts, string);
}

void (*aud_log_print) (int proc_num, unsigned int ts, const char *string) = aud_log_default;

static void handle_message (int proc_num, unsigned int ts, unsigned int flags, unsigned int len,
    const char *str)
{
    static struct
    {
        unsigned int ts;
        char *str;
        unsigned int len;       // strlen (str)
    } bind[NUM_OF_DSP];
    char *tmp;

    proc_num -= ADEC_CORE_DSP0;

    if (flags & AUD_IPCM_FLAG_CONTINUE)
    {
        tmp = kmalloc (bind[proc_num].len + len, GFP_KERNEL);
        if (!tmp)
        {
            error ("no mem. proc %d, len %d, %d\n", proc_num, bind[proc_num].len, len);
            return;
        }

        if (bind[proc_num].str)
            memcpy (tmp, bind[proc_num].str, bind[proc_num].len);
        memcpy (tmp + bind[proc_num].len, str, len);

        if (bind[proc_num].str)
            kfree (bind[proc_num].str);
        else
            bind[proc_num].ts = ts;
        bind[proc_num].str = tmp;
        bind[proc_num].len += len - 1;
        bind[proc_num].ts = ts;
        return;
    }

    if (!bind[proc_num].str)
    {
        aud_log_print (proc_num + ADEC_CORE_DSP0, ts, str);
        return;
    }

    tmp = kmalloc (bind[proc_num].len + len, GFP_KERNEL);
    if (!tmp)
    {
        error ("no mem. proc %d, len %d, %d\n", proc_num, bind[proc_num].len, len);
        return;
    }
    memcpy (tmp, bind[proc_num].str, bind[proc_num].len);
    memcpy (tmp + bind[proc_num].len, str, len);
    kfree (bind[proc_num].str);

    aud_log_print (proc_num + ADEC_CORE_DSP0, bind[proc_num].ts, tmp);
    kfree (tmp);

    bind[proc_num].str = NULL;
    bind[proc_num].ts = 0;
    bind[proc_num].len = 0;
}

static void _aud0 (unsigned int ts, unsigned int flags, unsigned int len, const char *str)
{
    handle_message (ADEC_CORE_DSP0, ts, flags, len, str);
}

static void _aud1 (unsigned int ts, unsigned int flags, unsigned int len, const char *str)
{
    handle_message (ADEC_CORE_DSP1, ts, flags, len, str);
}

static void _aud2 (unsigned int ts, unsigned int flags, unsigned int len, const char *str)
{
    handle_message (ADEC_CORE_DSP2, ts, flags, len, str);
}

static void _aud3 (unsigned int ts, unsigned int flags, unsigned int len, const char *str)
{
    handle_message (ADEC_CORE_DSP3, ts, flags, len, str);
}

static int process_message (void *ipc, PFN_IpcDbgPrint print_func)
{
    ADEC_RESULT result;

    do
    {
        result = IPC_ReadDebug (ipc, print_func);
    }
    while (result == ADEC_ERR_NONE);

    if (result != ADEC_ERR_UNDERFLOW)
    {
        if (result == ADEC_ERR_DATA_CORRUPTED)
        {
            IPC_ClearRegister (ipc, 1);
        }
    }

    return 0;
}

static void dspirq_debug_message (void)
{
    int i;
    PFN_IpcDbgPrint prints[] = {
        _aud0,
        _aud1,
        _aud2,
        _aud3,
    };

    AUDIO_IMC_WQ_LOCK ();

    for (i = 0; i < ARRAY_SIZE (ipc_descs); i++)
    {
        if (ipc_descs[i].role == IPC_ROLE_DBG_READER && ipc_descs[i].pIpc)
            process_message (ipc_descs[i].pIpc, prints[ipc_descs[i].dsp_index]);
    }

    AUDIO_IMC_WQ_UNLOCK ();

    return;
}

static void process_dspirq_workfunc (struct work_struct *data)
{
    dspirq_ipc_message ();
    dspirq_debug_message ();
}

struct audirq_desc
{
    const char *name;
    int dspnum;
    int irqnum;
};

#if defined(CHIP_NAME_o22)
#define AUD_DSP0_IRQ	O22_IRQ_INTR_AUD_DSP0_CPU
#define AUD_DSP1_IRQ	O22_IRQ_INTR_AUD_DSP1_CPU
#define AUD_DSP2_IRQ	O22_IRQ_INTR_AUD_DSP2_CPU
#define AUD_DSP3_IRQ	O22_IRQ_INTR_AUD_DSP3_CPU
#elif defined(CHIP_NAME_m23)
#define AUD_DSP0_IRQ	M23_IRQ_INTR_AUD_DSP0_CPU
#define AUD_DSP1_IRQ	M23_IRQ_INTR_AUD_DSP1_CPU
#define AUD_DSP2_IRQ	M23_IRQ_INTR_AUD_DSP2_CPU
#elif defined(CHIP_NAME_o24)
#define AUD_DSP0_IRQ	O24_IRQ_AUD_DSP0_CPU
#define AUD_DSP1_IRQ	O24_IRQ_AUD_DSP1_CPU
#define AUD_DSP2_IRQ	O24_IRQ_AUD_DSP2_CPU
#define AUD_DSP3_IRQ	O24_IRQ_AUD_DSP3_CPU
#elif defined(CHIP_NAME_o26)
#define AUD_DSP0_IRQ	O26_IRQ_AUD_DSP0_CPU
#define AUD_DSP1_IRQ	O26_IRQ_AUD_DSP1_CPU
#define AUD_DSP2_IRQ	O26_IRQ_AUD_DSP2_CPU
#define AUD_DSP3_IRQ	O26_IRQ_AUD_DSP3_CPU
#else
#error "Please Define Chip Definition"
#endif

static struct audirq_desc audirqs[] = {
    {"aud0", 0, AUD_DSP0_IRQ,},
    {"aud1", 1, AUD_DSP1_IRQ,},
    {"aud2", 2, AUD_DSP2_IRQ,},
#if (NUM_OF_DSP >= 4)
    {"aud3", 3, AUD_DSP3_IRQ,},
#endif
};

static void clear_audirq (struct audirq_desc *desc)
{
    if (desc->dspnum == 0)
    {
        PERI_WR_NAME (INT0_CLR, 1);
        PERI_WR_NAME (INT0_CLR, 0);
    }
    else if (desc->dspnum == 1)
    {
        PERI_WR_NAME (INT1_CLR, 1);
        PERI_WR_NAME (INT1_CLR, 0);
    }
    else if (desc->dspnum == 2)
    {
        PERI_WR_NAME (INT2_CLR, 1);
        PERI_WR_NAME (INT2_CLR, 0);
    }
    else
    {
#if (NUM_OF_DSP >= 4)
        PERI_WR_NAME (INT3_CLR, 1);
        PERI_WR_NAME (INT3_CLR, 0);
#endif
    }
}

static irqreturn_t audipc_handle_irq (int irq, void *dev)
{
    static DECLARE_WORK (process_dspirq_work, process_dspirq_workfunc);

    struct audirq_desc *desc = dev;

    clear_audirq (desc);

    queue_work (system_highpri_wq, &process_dspirq_work);

    return IRQ_HANDLED;
}

extern bool aud_disable_aad;
extern void renderer_set_basetime_ipc (unsigned int index, unsigned int clock_base_time,
    unsigned int stream_base_time, bool is_set, bool is_all_set);

int aimc_start (void)
{
    int result;
    int index;
    int dsp_index;
    int i;

    AUDIO_IMC_WQ_LOCK ();
    AUDIO_IMC_LOCK ();

    for (i = 0; i < AUD_IPCREG_SIZE / sizeof (uint32_t); i++)
        aud_reg_ipc[i] = 0;

    AUD_IPCREG (MEM_SHARE_BASE) = aud_phys_to_lgbus (aud_base_address ());
    AUD_IPCREG (VER_CHIP) = lx_chip_rev ();

    if (lx_chip_rev () != LX_CHIP_REV (O22, A0))        // 27M Issue. only for O22 A0(0x26A0).
        aud_disable_aad = false;

    AUD_IPCREG (AUD_DISABLE_AAD) = aud_disable_aad;
    noti ("aud_disable_aad = %d(Ver = 0x%X).\n", AUD_IPCREG (AUD_DISABLE_AAD), lx_chip_rev ());

    /* clear basetime IPC registers */
    renderer_set_basetime_ipc (0, 0xFFFFFFFF, 0xFFFFFFFF, false, true);

    // IMC
    if (gimc_info == NULL)
    {
        result = IMC_Init (&gaimc->imc_info, ADEC_CORE_ARM);
        if (result != 0)
        {
            error ("IMC_Init() error!!!\n");
            return -1;
        }

        gimc_info = &gaimc->imc_info;
    }

    // init IPC
    for (index = 0; index < ARRAY_SIZE (ipc_descs); index++)
    {
        struct ipc_desc *desc = ipc_descs + index;
        int dsp_index = desc->dsp_index;

        desc->reg_wroff = &AUD_IPCREG_OFFS (desc->ipcoff_wr);
        desc->reg_rdoff = &AUD_IPCREG_OFFS (desc->ipcoff_rd);
        AUD_IPCREG_OFFS (desc->ipcoff_base) = aud_phys_to_lgbus (desc->mem_paddr);
        AUD_IPCREG_OFFS (desc->ipcoff_size) = desc->bufSize;

        if (desc->role < 0)
            continue;

        desc->pIpc = kmalloc (IPC_GetStructSize (), GFP_KERNEL);
        if (!desc->pIpc)
        {
            error ("no mem\n");
            goto IMC_INIT_ERROR;
        }

        info ("desc%d : %p\n", dsp_index, desc->pIpc);
        result = IPC_Init (desc->pIpc, (void *) desc->reg_wroff, (void *) desc->reg_rdoff,
            desc->syncWord, desc->bufSize, NULL, desc->mem_vaddr, desc->role);
        if (result != 0)
        {
            error ("IPC_Init() Error - index=%u !!!\n", index);
            goto IMC_INIT_ERROR;
        }
        IPC_ClearRegister (desc->pIpc, 1);

        if (desc->send_irq)
            IPC_SetInterrupt (desc->pIpc, desc->send_irq, desc);
    }

    result = IMC_RegisterCmdProcessor (gimc_info, ADEC_MODULE_MAN_ARM, manager_cmd, NULL);
    if (result != 0)
    {
        error ("IMC_RegisterCmdProcessor() Error!!!\n");
        goto IMC_INIT_ERROR;
    }

    stop_imc = false;

    AUDIO_IMC_UNLOCK ();
    AUDIO_IMC_WQ_UNLOCK ();

    // for bin dump and prop
    aimc_register_bin_event_handler ();

    return 0;

  IMC_INIT_ERROR:
    gimc_info = NULL;

    for (dsp_index = 0; dsp_index < ARRAY_SIZE (ipc_descs); dsp_index++)
    {
        if (ipc_descs[dsp_index].pIpc)
        {
            kfree (ipc_descs[dsp_index].pIpc);
            ipc_descs[dsp_index].pIpc = NULL;
        }
    }

    AUDIO_IMC_UNLOCK ();
    AUDIO_IMC_WQ_UNLOCK ();

    return -1;
}

void aimc_stop (void)
{
    int i;

    AUDIO_IMC_WQ_LOCK ();
    AUDIO_IMC_LOCK ();

    stop_imc = true;

    for (i = 0; i < ARRAY_SIZE (ipc_descs); i++)
    {
        if (ipc_descs[i].pIpc)
        {
            kfree (ipc_descs[i].pIpc);
            ipc_descs[i].pIpc = NULL;
        }
    }

    AUDIO_IMC_UNLOCK ();
    AUDIO_IMC_WQ_UNLOCK ();

    return;
}

static int aimc_send_command_rsp (struct aimc *imc, unsigned int cmd, unsigned int source,
    unsigned int target, void *param, unsigned int param_size, PFN_ImcResponse callback,
    void *callback_param)
{
    ImcCommandParameter imcParam = { };
    ADEC_RESULT res;
    unsigned int response_id = 0;

    debug ("send cmd(0x%08x) to target(0x%08x). param size %d, cb %pf\n", cmd, target, param_size,
        callback);

    imcParam.cmd = cmd;
    imcParam.callback = callback;
    imcParam.callbackParam = callback_param;
    imcParam.param = param;
    imcParam.paramLength = param_size;
    imcParam.requestInterrupt = IMC_INTERRUPT_REQUIRED;
    if (callback)
        imcParam.requestResponse = IMC_RESPONSE_REQUIRED;
    else
        imcParam.requestResponse = IMC_RESPONSE_NOT_REQUIRED;
    imcParam.source = ADEC_MODULE_MAN_ARM;
    imcParam.target = target;

    res = IMC_SendCommand (gimc_info, &imcParam, &response_id);

    return -res;
}

static int imc_send_command (struct aimc *imc, unsigned int cmd, unsigned int source,
    unsigned int target, void *param, unsigned int param_size)
{
    return aimc_send_command_rsp (imc, cmd, source, target, param, param_size, NULL, NULL);
}

int __init aimc_init (void)
{
    int i;

    aimc_port_dispatch_command = imc_dispatch_command;
    aimc_port_ipc_send = imc_ipc_send;
    aimc_port__register_command_handler = imc__register_command_handler;
    aimc_port_send_command = imc_send_command;

    gowner = aud_modlist_new_owner ("default");

    for (i = 0; i < ARRAY_SIZE (audirqs); i++)
    {
        int ret;

        ret =
            request_irq (audirqs[i].irqnum, audipc_handle_irq, IRQF_TRIGGER_HIGH | IRQF_SHARED,
            audirqs[i].name, &audirqs[i]);
        if (ret < 0)
            error ("request_irq() failed for dsp %s\n", audirqs[i].name);
    }

    for (i = 0; i < ARRAY_SIZE (ipc_descs); i++)
    {
        struct ipc_desc *desc = ipc_descs + i;

        desc->mem_paddr = hma_alloc_user ("audio_buffer", desc->bufSize, 4096, desc->name);
        if (!desc->mem_paddr)
        {
            error ("mem alloc failed for %s\n", desc->name);
            continue;
        }

        desc->mem_vaddr = hma_map (desc->mem_paddr, desc->bufSize);
        if (!desc->mem_vaddr)
        {
            error ("mem map failed for %s\n", desc->name);
            continue;
        }
    }

    INIT_LIST_HEAD (&gaimc->noti_list);

    for (i = 0; i < NUM_OF_DSP; i++)
        gaimc->dead[i] = false;

    aimc_start ();

    return 0;
}

void __exit aimc_exit (void)
{
    int i;

    if (gimc_info)
    {
        IMC_Finalize (gimc_info);
        gimc_info = NULL;
    }

    for (i = 0; i < ARRAY_SIZE (ipc_descs); i++)
    {
        struct ipc_desc *desc = ipc_descs + i;

        if (desc->pIpc)
        {
            kfree (desc->pIpc);
            desc->pIpc = NULL;
        }

        hma_unmap (desc->mem_vaddr);
        hma_free ("audio_buffer", desc->mem_paddr);
    }

    for (i = 0; i < ARRAY_SIZE (audirqs); i++)
    {
        free_irq (audirqs[i].irqnum, &audirqs[i]);
    }

    aud_modlist_del_owner (gowner);
}

static int audio_imc_sync_timeout = 5;
module_param (audio_imc_sync_timeout, int, 0644);

static DEFINE_MUTEX (sync_lock);
static LIST_HEAD (sync_list);
struct sync_info
{
    struct list_head list;

    bool called;
    int result;
    void *resp_param;
    int resp_param_size;
    wait_queue_head_t wq;
};

static void response_sync (int result, void *param, int param_len, void *cb_param)
{
    struct sync_info *now, *sync;

    debug ("got response. sync %p, result %d\n", cb_param, result);

    mutex_lock (&sync_lock);
    sync = NULL;
    list_for_each_entry (now, &sync_list, list)
    {
        if (now == cb_param)
        {
            sync = now;
            break;
        }
    }
    if (sync)
    {
        sync->called = TRUE;
        sync->result = result;
        if (sync->resp_param && sync->resp_param_size > 0 && param)
        {
            if (sync->resp_param_size == param_len)
                memcpy (sync->resp_param, param, sync->resp_param_size);
            else
            {
                error ("param length is different. %d, %d\n", param_len, sync->resp_param_size);
                sync->result = -EINVAL;
            }
        }

        wake_up_all (&sync->wq);
    }
    else
        error ("unknown callback param. %p\n", cb_param);
    mutex_unlock (&sync_lock);

    return;
}

void aimc_set_dsp_dead (unsigned int dsp_num, bool dead)
{
    noti ("dsp%d is %s\n", dsp_num, (dead) ? "DEAD" : "ALIVE");

    if (dsp_num >= NUM_OF_DSP)
        return;

    gaimc->dead[dsp_num] = dead;
}

static bool aimc_is_dsp_dead (int dsp_num)
{
    if (0 > dsp_num || dsp_num >= NUM_OF_DSP)
        return false;

    return gaimc->dead[dsp_num];
}

static int send_command_sync (struct aimc *imc, unsigned int cmd, unsigned int source,
    unsigned int target, void *param, unsigned int param_size, int *result, bool param_copy)
{
    int ret;
    unsigned long sync_timeout;
    struct sync_info sync = { };
    unsigned int proc_num = AUD_MODID_PROC (target);

    if (stop_imc)
    {
        return 0;
    }

    // only dsp
    if (ADEC_CORE_DSP0 <= proc_num && proc_num < (ADEC_CORE_DSP0 + NUM_OF_DSP))
    {
        int dsp_num = proc_num - ADEC_CORE_DSP0;

        if (aimc_is_dsp_dead (dsp_num))
        {
            noti ("dsp%d is dead... ignore cmd(0x%08x) to target(0x%08x)\n", dsp_num, cmd, target);
            return 0;
        }
    }
    else if (proc_num >= ADEC_CORE_START_PROC)
    {
        if (ausrimc_get_task_status_normal (proc_num) == false)
        {
            error ("target task is not normal.. send async\n");
            return aimc_send_command_rsp (imc, cmd, source, target, param, param_size, NULL, NULL);
        }
    }

    init_waitqueue_head (&sync.wq);
    if (param_copy && param != NULL && param_size > 0)
    {
        sync.resp_param = param;
        sync.resp_param_size = param_size;
    }

    mutex_lock (&sync_lock);
    list_add (&sync.list, &sync_list);
    mutex_unlock (&sync_lock);

    debug ("send sync cmd(0x%08x) to target(0x%08x). param size %d\n", cmd, target, param_size);

    ret =
        aimc_send_command_rsp (imc, cmd, source, target, param, param_size, response_sync,
        (void *) &sync);
    if (ret)
    {
        mutex_lock (&sync_lock);
        list_del (&sync.list);
        mutex_unlock (&sync_lock);
        return -ret;
    }

#if defined (CHIP_TYPE_FPGA)
#define ADD_TIMES 10    // ADD_TIMES 3은 1회 실패. sufficient value로 10 설정.
#else
#define ADD_TIMES 1
#endif
    // in suspending, set timeout as 100 ms for prevent DPM timeout
    if (bm_get_suspended ())
        sync_timeout = msecs_to_jiffies (100) * ADD_TIMES;
    else
        sync_timeout = audio_imc_sync_timeout * HZ * ADD_TIMES;

    /* wait response callback */
    ret = wait_event_interruptible_timeout (sync.wq, sync.called, sync_timeout);
    if (!ret)
    {
        error ("sync timeout. cmd(0x%08x) to target(0x%08x), param %p\n", cmd, target, &sync);
        ret = -ETIMEDOUT;
    }
    else if (ret < 0)
    {
        error ("interrupted\n");
        ret = -EINTR;
    }
    else
    {
        debug ("result %d\n", sync.result);

        if (result)
            *result = sync.result;
        ret = 0;
    }

    mutex_lock (&sync_lock);
    list_del (&sync.list);
    mutex_unlock (&sync_lock);

    return ret;
}

int aimc_send_command_sync (struct aimc *imc, unsigned int cmd, unsigned int source,
    unsigned int target, void *param, unsigned int param_size)
{
    return send_command_sync (imc, cmd, source, target, param, param_size, NULL, false);
}

EXPORT_SYMBOL (aimc_send_command_sync);

int aimc_send_command_return (struct aimc *imc, unsigned int cmd, unsigned int source,
    unsigned int target, void *param, unsigned int param_size)
{
    return send_command_sync (imc, cmd, source, target, param, param_size, NULL, true);
}

int aimc_set_property (unsigned int target, char *prop_fmt, ...)
{
    ImcCmdSetProp *param;
    int len;
    va_list ap;

    if (!target)
    {
        error ("no target. %s\n", prop_fmt);
        return -1;
    }

    va_start (ap, prop_fmt);
    len = vsnprintf (NULL, 0, prop_fmt, ap);
    va_end (ap);

    param = kmalloc (sizeof (*param) + len + 1, GFP_KERNEL);
    if (!param)
    {
        error ("no mem. %s\n", prop_fmt);
        return -1;
    }

    param->len = len;

    va_start (ap, prop_fmt);
    vsnprintf (param->str, len + 1, prop_fmt, ap);
    va_end (ap);

    info ("'%08x' len %d, prop '%s'\n", target, len, param->str);
    imc_send_command (NULL, ADEC_CMD_SET_PROP, 0, target, param, sizeof (*param) + len + 1);

    kfree (param);
    return 0;
}

int aimc_get_property (unsigned int target, char *name, int *pRetValue)
{
    ImcCmdGetProp *param;
    int size;
    int ret;

    size = strlen (name) + 1;
    size = (size > sizeof (ImcCmdGetProp)) ? sizeof (ImcCmdGetProp) : size;
    param = kzalloc (sizeof (ImcCmdGetProp), GFP_KERNEL);
    if (!param)
    {
        error ("no mem. %s\n", name);
        return -ENOMEM;
    }

    strncpy (param->name, name, size);
    param->name[size - 1] = '\0';

    info ("'%08x' prop '%s'\n", target, param->name);

    ret = send_command_sync (NULL, ADEC_CMD_GET_PROP, 0, target, param, size, pRetValue, false);
    kfree (param);
    return ret;
}

unsigned int aimc_module_create (const char *impl_name, int preferred_processor)
{
    return aud_inst_create (gowner, impl_name, preferred_processor, false);
}

int aimc_module_destroy (unsigned int uid)
{
    aud_inst_destroy (gowner, uid);
    return 0;
}

int aimc_module_connect (unsigned int uid1, int port1, unsigned int uid2, int port2)
{
    return aud_inst_connect (gowner, uid1, port1, uid2, port2, false);
}

int aimc_module_disconnect_output (unsigned int uid, int port)
{
    return aud_inst_disconnect_output (gowner, uid, port);
}

int aimc_module_disconnect_input (unsigned int uid, int port)
{
    return aud_inst_disconnect_input (gowner, uid, port);
}

static void noti_handler_work (struct work_struct *work)
{
    struct noti_info *noti = container_of (work, struct noti_info, ws);
    struct noti_param *noti_param;

    mutex_lock (&noti->param_lock);
    while ((noti_param = list_first_entry_or_null (&noti->param_list, struct noti_param, list)))
    {
        list_del (&noti_param->list);
        mutex_unlock (&noti->param_lock);

        info ("call: action %x(event %x, module %x). %ps(%p, %d)\n",
            noti->action_id, noti->event, noti->target,
            noti->callback_func, noti_param->param, noti_param->size);

        noti->callback_func (noti_param->param, noti_param->size, noti->callback_param);
        kfree (noti_param);

        mutex_lock (&noti->param_lock);
    }
    mutex_unlock (&noti->param_lock);

    if (noti->repeat == false)
    {
        info ("action once. free\n");
        kfree (noti);
    }
}

static int cb_func_local (void *cbParam, void *param, unsigned int param_size)
{
    struct noti_info *noti = (struct noti_info *) cbParam;
    struct noti_param *noti_param;

    if (!noti)
    {
        return ADEC_ERR_NONE;
    }

    info ("noti: action %x(event %x, module %x). %ps\n",
        noti->action_id, noti->event, noti->target, noti->callback_func);

    noti_param = kzalloc (sizeof (struct noti_param) + param_size, GFP_KERNEL);
    if (!noti_param)
    {
        error ("no memory %ps. param_size %d\n", noti->callback_func, param_size);
        return -1;
    }

    if (param_size > 0)
    {
        memcpy (noti_param->param, param, param_size);
    }
    noti_param->size = param_size;

    mutex_lock (&noti->param_lock);
    list_add_tail (&noti_param->list, &noti->param_list);
    mutex_unlock (&noti->param_lock);

    if (noti->repeat == false)
    {
        info ("action once. remove from list\n");
        list_del (&noti->list);
    }
    queue_work (system_highpri_wq, &noti->ws);

    return ADEC_ERR_NONE;
}

// <= 0 : error
//  > 0 : success, event_id
int aimc_register_named_event (void *cb_param, int (*cb_func) (void *, int, void *),
    unsigned int target, const char *event_name, bool repeat)
{
    int event_id = 0;
    struct noti_info *noti;

    /* allocate event noti info structure */
    noti = kzalloc (sizeof (struct noti_info), GFP_KERNEL);
    if (!noti)
    {
        error ("no memory.\n");
        return 0;
    }

    INIT_LIST_HEAD (&noti->list);
    noti->callback_func = cb_func;
    noti->callback_param = cb_param;
    noti->target = target;
    noti->repeat = repeat;
    INIT_LIST_HEAD (&noti->param_list);
    INIT_WORK (&noti->ws, noti_handler_work);
    mutex_init (&noti->param_lock);

    /* register */
    AUDIO_IMC_WQ_LOCK ();
    AUDIO_IMC_LOCK ();

    event_id =
        IMC_RegisterNamedEvent (&gaimc->imc_info, event_name, target, repeat ? 0 : 1, cb_func_local,
        noti);

    noti->event = event_id;
    if (event_id < ADEC_ERR_NONE)
    {
        error ("IMC_RegisterNamedEvent : [%d]\n", event_id);
        kfree (noti);
    }
    else
    {
        list_add (&noti->list, &gaimc->noti_list);

        info ("register event ID %x(event %s, module %x)\n", noti->event, event_name, noti->target);
    }

    AUDIO_IMC_UNLOCK ();
    AUDIO_IMC_WQ_UNLOCK ();

    return event_id;
}

EXPORT_SYMBOL (aimc_register_named_event);

void aimc_unregister_named_event (int event_id)
{
    struct noti_info *noti = NULL;
    bool found = false;

    AUDIO_IMC_WQ_LOCK ();
    AUDIO_IMC_LOCK ();

    IMC_UnregisterNamedEvent (&gaimc->imc_info, event_id);

    list_for_each_entry (noti, &gaimc->noti_list, list)
    {
        if (noti->event == event_id)
        {
            list_del (&noti->list);
            found = true;
            break;
        }
    }

    AUDIO_IMC_UNLOCK ();
    AUDIO_IMC_WQ_UNLOCK ();

    if (found)
    {
        struct noti_param *noti_param;

        flush_work (&noti->ws);

        mutex_lock (&noti->param_lock);
        while ((noti_param = list_first_entry_or_null (&noti->param_list, struct noti_param, list)))
        {
            list_del (&noti_param->list);
            kfree (noti_param);
        }
        mutex_unlock (&noti->param_lock);

        kfree (noti);
    }
}

EXPORT_SYMBOL (aimc_unregister_named_event);

int aimc_raise_named_event (unsigned int event_source, const char *name, void *param,
    unsigned int param_size)
{
    return IMC_RaiseNamedEvent (gimc_info, event_source, name, param, param_size);
}

static int _cb_bin_event (void *_param, int _paramLen, void *_cbParam)
{
    ImcCmdbinEvent *evt = (ImcCmdbinEvent *) _param;

    if (evt->create)
    {
        noti ("request to add %s 0x%x in CPU%d to list\n", evt->impl_name, evt->uid,
            evt->proscessor - ADEC_CORE_DSP0);
        aud_modlist_add_inst (gowner, evt->impl_name, evt->uid, evt->proscessor, false);
    }
    else
    {
        noti ("request to remove %s 0x%x in CPU%d from list\n", evt->impl_name, evt->uid,
            evt->proscessor - ADEC_CORE_DSP0);
        aud_modlist_remove_inst (gowner, evt->impl_name, evt->uid);
    }

    return 0;
}

void aimc_register_bin_event_handler (void)
{
    int dsp = 0;
    unsigned int target = 0;

    for (dsp = 0; dsp < NUM_OF_DSP; dsp++)
    {
        if (gaimc->evt_id[dsp])
            aimc_unregister_named_event (gaimc->evt_id[dsp]);

        target = AUD_MODID_INTERNALM (dsp + ADEC_CORE_DSP0);
        gaimc->evt_id[dsp] = aimc_register_named_event (NULL, _cb_bin_event, target, "bin", true);
    }
}

void aimc_unregister_bin_event_handler (void)
{
    int dsp = 0;

    for (dsp = 0; dsp < NUM_OF_DSP; dsp++)
    {
        if (gaimc->evt_id[dsp])
            aimc_unregister_named_event (gaimc->evt_id[dsp]);
        gaimc->evt_id[dsp] = 0;
    }
}
