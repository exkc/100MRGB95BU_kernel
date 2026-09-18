#ifndef	_TE_NAGRA_KAPI_H_
#define	_TE_NAGRA_KAPI_H_

//NOTE: This extension is used for nagra simbad
#include <linux/dvbv5-ext/dvbv5-ext-demux.h>

#define DMX_NAGRA_NONCE_LEN 16
#define DMX_NAGRA_STATE_LEN (DMX_NAGRA_NONCE_LEN + 16)

struct dmx_ext_nagra_key {
	enum dmx_ext_dscrmb_key_type key_type;
	__u8 key_size; //for contents
	__u8 key_encrypted;
	__u8 data[32];
	__u8 iv_size;
	__u8 iv_encrypted;
	__u8 iv[32];
	__u8 comm_iv[16]; //for message
};

struct dmx_ext_nagra_algo {
	enum dmx_ext_dscrmb_type desc_type;
	__u8 channel_mode;
};

struct dmx_ext_nagra_nonce {
	__u8 nonce[DMX_NAGRA_NONCE_LEN];
};

struct dmx_ext_nagra_state {
	__u8 data[DMX_NAGRA_STATE_LEN];
	__u8 comm_iv[16];
};

#define DMX_EXT_CID_NAGRA_ALGO	90
#define DMX_EXT_CID_NAGRA_KEY	91
#define DMX_EXT_CID_NAGRA_GET_STATUS 92
#define DMX_EXT_CID_NAGRA_GET_NONCE 93
#define DMX_EXT_CID_NAGRA_SET_STATE 94


#endif				/* _TE_NAGRA_KAPI_H_ */
