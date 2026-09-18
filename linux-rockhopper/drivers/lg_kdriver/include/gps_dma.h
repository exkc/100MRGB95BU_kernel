#ifndef GPS_DMA_H
#define GPS_DMA_H
struct source_frame_info {
	unsigned int addr_y;
	unsigned int addr_c;
	unsigned int stride;
	unsigned int width;
	unsigned int height;
	unsigned int map_type;
        unsigned int scan_type;
        unsigned int bpp;
        unsigned int hdr_type;
        unsigned int hdr_ott_meta_addr;
	unsigned int color_sample;
};

struct target_frame_info {
	unsigned int addr_y;
	unsigned int addr_c;
	unsigned int width;
	unsigned int height;
	unsigned int format;
	unsigned int crc_y;
	unsigned int crc_c;
	unsigned int crc_mode;
};

int dma_start(struct source_frame_info *src_info, struct target_frame_info *dst_info);
#endif //#ifdef GPS_DMA_H

