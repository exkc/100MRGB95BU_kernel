#ifndef _TE_DVB_CA_KAPI_H_
#define _TE_DVB_CA_KAPI_H_

#define TE_DVB_CA_MAGIC	'x'

struct te_dvb_ca_test_pkt_cnt {
        __u8 ch; // not used yet; future use
	__u16 cnt; // pkt count for test
};

#define TE_DVB_CA_TEST_PKT_CNT	_IOWR(TE_DVB_CA_MAGIC, 0, struct te_dvb_ca_test_pkt_cnt)

#endif // _TE_DVB_CA_KAPI_H_
