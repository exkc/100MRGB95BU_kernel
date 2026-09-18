
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include "alsa/alsa_machine.h"
#include "hal/hal.h"
#include "hal/hal_bc.h"
#include "driver.h"
#include "platform.h"

#include "module_list.h"
#include "user_imc.h"
#include "blind.h"
#include "ablind.h"
#include "kaimc.h"
#include "regs.h"
#include "proc.h"
#include "dsp_control.h"

#include "log.h"
#include "block_manager.h"

logm_define (aud_init, log_level_noti);

#define trace(fmt,args...)	logm_trace(aud_init,fmt,##args)
#define debug(fmt,args...)	logm_debug(aud_init,fmt,##args)
#define info(fmt,args...)	logm_info(aud_init,fmt,##args)
#define noti(fmt,args...)	logm_noti(aud_init,fmt,##args)
#define error(fmt,args...)	logm_error(aud_init,fmt,##args)

static char *aud_dsp0_init_cmds;
static char *aud_dsp1_init_cmds;
module_param (aud_dsp0_init_cmds, charp, 0644);
module_param (aud_dsp1_init_cmds, charp, 0644);

static void set_dsp_init_cmds (void)
{
    char **dsp_init_cmds[] = {
        &aud_dsp0_init_cmds,
        &aud_dsp1_init_cmds,
    };
    int i;

    for (i = 0; i < ARRAY_SIZE (dsp_init_cmds); i++)
    {
        if (*dsp_init_cmds[i])
        {
            aud_call_funcs (i, "%s", *dsp_init_cmds[i]);
        }
    }
}

static int __init mod_init (void)
{
    static int (*const init_funcs[]) (void) =
    {
        /* *INDENT-OFF* */
        aregs_init,
        aud_hal_init,
        aproc_init,
        aud_modlist_init,
        aimc_init,
        ausrimc_init,
        bm_init,
        ALSA_MACHINE_Init,
        aud_cdev_init,
        aud_platform_init,
        ablind_init,
        aud_dsp_control_init,
        NULL,
        /* *INDENT-ON* */
    };

    int i;

    extern bool audio_disable;

    if (audio_disable)
    {
        // do not initialize audio
        noti ("do not initialize audio\n");
        return 0;
    }

    noti ("..\n");
    for (i = 0; init_funcs[i]; i++)
    {
        int ret;

        ret = init_funcs[i] ();
        if (ret < 0)
        {
            error ("error %d on %pf()\n", ret, init_funcs[i]);
            return ret;
        }
    }

    set_dsp_init_cmds ();

    noti ("done.\n");

    return 0;
}

module_init (mod_init);

MODULE_AUTHOR ("LGE SIC");
MODULE_DESCRIPTION ("um3 audio dsp controller");
MODULE_LICENSE ("GPL");
