#ifndef _LXDVB_NAGRA_H_
#define _LXDVB_NAGRA_H_

#include "lxdvb_demux.h"
#include "te_nagra_kapi.h"

int dmx_nagra_set_desc_type(struct lxdvb_dmx_channel *channel,
			    struct dmx_ext_nagra_algo *param);
int dmx_nagra_set_desc_key(struct lxdvb_dmx_fh *fh,
			   struct dmx_ext_nagra_key *key);
int dmx_nagra_resume_desc_type(struct lxdvb_dmx_channel *channel,
			       enum dmx_ext_dscrmb_type type);
void dmx_nagra_cancel_desc_pid(struct lxdvb_dmx_filter *f);
int dmx_nagra_get_desc_key_inserted(struct lxdvb_dmx_fh *fh, s64 *status);
bool dmx_nagra_get_desc_enable(struct lxdvb_dmx_filter *f);
int dmx_nagra_get_nonce(struct lxdvb_dmx_fh *fh,
			struct dmx_ext_nagra_nonce *param);
int dmx_nagra_set_state(struct lxdvb_dmx_fh *fh,
			struct dmx_ext_nagra_state *param);
#endif /* _LXDVB_NAGRA_H_ */

