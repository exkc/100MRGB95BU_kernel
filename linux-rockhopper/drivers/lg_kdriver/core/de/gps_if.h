
#ifndef __GPS_IF_H__
#define __GPS_IF_H__

#include "de_kapi.h"
#include "de_def.h"
#include "de_io.h"


#define GPS_MAX_INSTANCE 8
#define GPS_MAX_BUFFER   3


struct gps_instance_info{
   UINT32 buf_index[3]; // index of write-done
   UINT32 ret_w;  // after changing size, fw updates this value
   UINT32 ret_h;
   UINT32 fr;
   UINT32 pts;
   UINT32 err_no; // pre-defined error number
};

struct gps_shared_mem_to_cpu {
   UINT32 write_done_id; // [31:0] each bit = vdec id
   struct gps_instance_info gps_instance[GPS_MAX_INSTANCE];
};

struct gps_shared_mem_to_mcu {
   UINT32 lock_buffer_index[8]; // buffer index of each instance
   UINT32 lock_buffer_flag[GPS_MAX_INSTANCE][GPS_MAX_BUFFER];  // 1:lock, 0:unlock
   UINT32 count[GPS_MAX_INSTANCE];
   UINT32 bbd_en[GPS_MAX_INSTANCE];            // bbd enable, 1:on, 0:off
};

typedef union {
	UINT32 udata32;
	struct {
	UINT32 source       :8;     // 7: 0
	UINT32 update       :4;		//11: 8
	UINT32 resvd0       :20;
	};
}gps_bbd_cnt_t;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 h            :16;     //15: 0
	UINT32 w            :16;     //31:16
	};
}gps_bbd_rect_t;

typedef struct gps_bbd_info {
   gps_bbd_cnt_t cnt;   // bbd cnt
   gps_bbd_rect_t in;   // gps in
   gps_bbd_rect_t out;  // gps out
   UINT32 org_stat0[5]; // bbd_stat0, [0]T ~ [n]T-n
   UINT32 org_stat1[5]; // bbd_stat1, [0]T ~ [n]T-n
   UINT32 mod_stat0[5]; // bbd_stat0, [0]T ~ [n]T-n
   UINT32 mod_stat1[5]; // bbd_stat1, [0]T ~ [n]T-n
   UINT32 dif_stat0;    // dif_stat0, DIF(T,T-1)
   UINT32 dif_stat1;    // dif_stat1, DIF(T,T-1)
}gps_bbd_info_t;

struct gps_shared_mem_status {
   gps_bbd_info_t bbd_info[8];
   UINT32 crc_y;
   UINT32 crc_c;
};

int gps_if_init(void);
int gps_if_uninit(void);
int gps_if_control(LX_DE_GPS_CTRL_T *p);
int gps_if_wait_intr(unsigned int ctrl);
int gps_if_get_data(int *pInst, struct gps_instance_info *pData);
int gps_if_get_index(unsigned int instance_id, unsigned int *idx);
int gps_if_lock_buffer(unsigned int instance, unsigned int idx, unsigned int flag, unsigned int log_enable);
int gps_if_set_bbd(unsigned int instance, unsigned int *mode);
int gps_if_get_bbd(unsigned int instance, unsigned int *info);
int gps_if_dma_start(LX_DE_GPSDMA_IPC_T stParams, unsigned int crc_mode);
int gps_if_get_crc(unsigned int crc_mode, unsigned int *crc_y, unsigned int *crc_c);

#endif

