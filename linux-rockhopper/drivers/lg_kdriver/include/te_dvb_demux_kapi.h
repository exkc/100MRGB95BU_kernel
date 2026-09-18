#ifndef _TE_DVB_DEMUX_KAPI_H_
#define _TE_DVB_DEMUX_KAPI_H_

#include <linux/dvbv5-ext/dvbv5-ext-demux.h>

#include "te_kapi.h"

#define TE_DVB_DEMUX_MAGIC	'x'

struct te_dvb_demux_prokey_info {
	__u32 base; //Deprecated
	enum dmx_ext_dscrmb_key_type type;
	__u8 size;
	__u8 use_iv;
};

struct te_dvb_demux_channel_input {
	enum lx_te_input_port port;
	__u8 reset;
};

struct te_dvb_demux_get_time {
	__u8 idx;	/* for gstcc idx selection */
	__u64 stc;	/* 90kHz tick */
	__u64 systime;	/* hrtimer clock (us) */
};

#define TE_DVB_DEMUX_SET_PROTECTKEY	_IOW(TE_DVB_DEMUX_MAGIC, 0, struct te_dvb_demux_prokey_info)
#define TE_DVB_DEMUX_SET_CHANNEL_INPUT	_IOW(TE_DVB_DEMUX_MAGIC, 1, struct te_dvb_demux_channel_input)
#define TE_DVB_DEMUX_GET_STC		_IOR(TE_DVB_DEMUX_MAGIC, 2, struct te_dvb_demux_get_time)
#define TE_DVB_DEMUX_GET_GSTC		_IOWR(TE_DVB_DEMUX_MAGIC, 3, struct te_dvb_demux_get_time)
#define TE_DVB_DEMUX_STC_ENABLE		_IO(TE_DVB_DEMUX_MAGIC, 4)
#define TE_DVB_DEMUX_STC_DISABLE	_IO(TE_DVB_DEMUX_MAGIC, 5)


#endif
