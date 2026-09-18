#ifndef _KAIMC_H_
#define _KAIMC_H_

#include <linux/init.h>

enum aimc_event { AIMC_EVENT_FIRMWARE_INIT };

struct aimc;
extern int aimc_send_command (struct aimc *imc, unsigned int cmd,
    unsigned int source, unsigned int target,
    void *param, unsigned int param_size);
int aimc_send_command_sync (struct aimc *imc, unsigned int cmd,
    unsigned int source, unsigned int target,
    void *param, unsigned int param_size);
int aimc_send_command_return (struct aimc *imc, unsigned int cmd, unsigned int source,
    unsigned int target, void *param, unsigned int param_size);

extern void aimc_send_irq (int dspnum);

extern int aimc_set_property (unsigned int target, char *prop_fmt, ...);
extern int aimc_get_property (unsigned int target, char *name, int *pRetValue);
extern unsigned int aimc_module_create (const char *module_name, int preferred_processor);
extern int aimc_module_destroy (unsigned int module_uid);
extern int aimc_module_connect (unsigned int uid1, int port1, unsigned int uid2, int port2);
extern int aimc_module_disconnect_output (unsigned int uid, int port);
extern int aimc_module_disconnect_input (unsigned int uid, int port);
void aimc_set_dsp_dead (unsigned int dsp_num, bool dead);

struct _IpcHeader;
extern int aimc_process_header (struct _IpcHeader * header);

int aimc_register_named_event (void *cb_param, int (*cb_func) (void *, int, void *),
    unsigned int target, const char *event_name, bool repeat);
void aimc_unregister_named_event (int event_id);

extern int aimc_raise_named_event (unsigned int target, const char *name, void *param, unsigned int param_size);

int aimc_start (void);
void aimc_stop (void);
void aimc_register_bin_event_handler (void);
void aimc_unregister_bin_event_handler (void);

extern int __init aimc_init (void);
extern void __exit aimc_exit (void);

void aud_log_default (int proc_num, unsigned int ts, const char *string);

#endif
