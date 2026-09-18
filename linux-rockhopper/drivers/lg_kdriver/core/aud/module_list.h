#ifndef _AUDIO_MODULE_LIST_H_
#define _AUDIO_MODULE_LIST_H_

#include <linux/kernel.h>

#include "module/uid.h"

#define AUD_MODLIST_CORE(uid)           AUD_MODID_PROC(uid)
#define AUD_MODLIST_PROC(uid)           AUD_MODLIST_CORE(uid)
#define AUD_MODLIST_MODIMPL(uid)        AUD_MODID_MODIMPL(uid)
#define AUD_MODLIST_MODINDEX(uid)       AUD_MODID_MODINDEX(uid)

#define AUD_MODLIST_UID(proc,impl,index) AUD_MODID_UID(proc,impl,index)

#define AUD_MODLIST_PROC_MAX            AUD_MODID_PROC_MAX
#define AUD_MODLIST_MODIMPL_MAX         AUD_MODID_MODIMPL_MAX
#define AUD_MODLIST_INDEX_MAX           AUD_MODID_INDEX_MAX

#define AUD_PORT_INPUT                  0x00
#define AUD_PORT_OUTPUT                 0x01

struct aud_mod_owner;
struct aud_mod_inst;
struct aud_proc_info;
struct aud_mod_impl;

struct aud_mod_impl *aud_modlist_register_impl (struct aud_proc_info *p, const char *name,
    int rank);
int aud_modlist_register_impl_port_buf_def (struct aud_proc_info *p, const char *name, int def_num,
    int max_num_au, int max_access_size);
struct aud_proc_info *aud_modlist_register_processor (void *pid, int *index);
int aud_modlist_unregister_processor (struct aud_proc_info *p);
struct aud_proc_info *aud_modlist_reset_dsp (unsigned int dsp_num);

struct aud_mod_owner *aud_modlist_new_ownerv (const char *name, va_list ap);
__printf (1, 2)
struct aud_mod_owner *aud_modlist_new_owner (const char *name, ...);
void aud_modlist_del_owner (struct aud_mod_owner *o);

struct aud_mod_inst *aud_modlist_create_inst (struct aud_mod_owner *o,
    const char *impl_name, int preferred_processor, bool sync);
void aud_modlist_destroy_inst (struct aud_mod_inst *inst);
int aud_modlist_connect_inst (struct aud_mod_owner *o, struct aud_mod_inst *inst_out,
    int port_out_index, struct aud_mod_inst *inst_in, int port_in_index, bool sync);
int aud_modlist_disconnect_inst_output (struct aud_mod_owner *o, struct aud_mod_inst *inst_out,
    int port_out_index);
int aud_modlist_disconnect_inst_input (struct aud_mod_owner *o, struct aud_mod_inst *inst_in,
    int port_in_index);
int aud_modlist_role_set (struct aud_mod_inst *inst, const char *role);

unsigned int aud_inst_create (struct aud_mod_owner *o, const char *impl_name,
    int preferred_processor, bool sync);
void aud_inst_destroy (struct aud_mod_owner *o, unsigned int uid);
int aud_inst_connect (struct aud_mod_owner *o, unsigned int uid_out, int port_out_index,
    unsigned int uid_in, int port_in_index, bool sync);
int aud_inst_disconnect_output (struct aud_mod_owner *o, unsigned int uid_out, int port_out_index);
int aud_inst_disconnect_input (struct aud_mod_owner *o, unsigned int uid_in, int port_in_index);
int aud_inst_role_set (struct aud_proc_info *p, unsigned int uid, const char *role);
unsigned int aud_inst_role_search (const char *role);

int aud_lm_create (struct aud_mod_owner *o, int index);
void aud_lm_destroy (struct aud_mod_owner *o, int index);
int aud_lm_disconnect_ln (struct aud_mod_owner *o, unsigned int legacy_out, int port_out_index,
    unsigned int uid_in, int port_in_index);
int aud_lm_disconnect_nl (struct aud_mod_owner *o, unsigned int uid_out, int port_out_index,
    unsigned int legacy_in, int port_in_index);

unsigned int aud_prepare_ext_buf (struct aud_mod_owner *o, unsigned int uid, unsigned int port,
    unsigned int in_out);
void aud_cleanup_ext_buf (struct aud_mod_owner *o, unsigned int uid, unsigned int port,
    unsigned int in_out);

int aud_modlist_init (void);
void aud_modlist_exit (void);

void aud_mod_name (struct aud_mod_owner *o, unsigned int uid, unsigned char *name);

void *aud_impl_register_helper (const char *impl_name,
    void *(*create_pre) (const char *impl_name, uint32_t uid),
    int (*create_post) (void *priv, const char *impl_name, uint32_t uid),
    int (*destroy_pre) (void *priv, const char *impl_name, uint32_t uid),
    int (*destroy_post) (void *priv, const char *impl_name, uint32_t uid));
void aud_impl_unregister_helper (const char *impl_name);

int aud_modlist_add_inst (struct aud_mod_owner *owner,
    const char *impl_name, unsigned int uid, int proc, bool sync);
int aud_modlist_remove_inst (struct aud_mod_owner *owner,
    const char *impl_name, unsigned int uid);

#endif
