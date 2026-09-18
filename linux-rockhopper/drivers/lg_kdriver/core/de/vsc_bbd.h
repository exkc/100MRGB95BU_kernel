#ifndef	_VSC_BBD_H_
#define	_VSC_BBD_H_

#define VSC_BBD_NUM		(4)

struct vsc_bbd_reg_ctrl0 {
	unsigned int addr;
	union {
		unsigned int data;
		struct {
		unsigned int reg_bbd_en   : 1 ;  //     0
		unsigned int reg_hys_mode : 5 ;  //  5: 1	frame count for temporal smoothing of BBD result
		unsigned int reg_op_mode  : 1 ;  //     6	BBD operation mode 0 : auto detection, 1 : manual setting
		unsigned int rsvd         : 1 ;  //     7     reserved
		unsigned int reg_cnt_th   : 8 ;  // 15: 8	continuous Black pixel's count threshold for recognizing Black Boundary
		unsigned int reg_diff_th  : 8 ;  // 23:16	threshold for Black decision
		unsigned int reg_bbd_mux  : 3 ;  // 26:24	data select for BBD, 0 : Max(RGB), 1 : Y, 2 : G, 3 : B, 4 : R, others : Y
		};
	};
};

struct vsc_bbd_reg_isize {
	unsigned int addr;
	union {
		unsigned int data;
		struct {
		unsigned int hsize_i : 13;  // 12: 0
		unsigned int rsvd    : 3 ;  // 15:13     reserved
		unsigned int vsize_i : 13;  // 28:16
		};
	};
};

struct vsc_bbd_reg_stat0 {
	unsigned int addr;
	union {
		unsigned int data;
		struct {
		unsigned int x0   : 13;  // 12: 0
		unsigned int rsvd : 3 ;  // 15:13     reserved
		unsigned int y0   : 13;  // 28:16
		};
	};
};

struct vsc_bbd_reg_stat1 {
	unsigned int addr;
	union {
		unsigned int data;
		struct {
		unsigned int x1   : 13;  // 12: 0
		unsigned int rsvd : 3 ;  // 15:13     reserved
		unsigned int y1   : 13;  // 28:16
		};
	};
};

struct vsc_bbd_rect {
	unsigned short x;
	unsigned short y;
	unsigned short w;
	unsigned short h;
};

struct vsc_bbd_win {
	struct vsc_bbd_rect org;
	struct vsc_bbd_rect act;
};

struct vsc_bbd_cfg {
	int wid;

	int update;
	int step;

	int hdr_type;//see enum v4l2_ext_vsc_hdr_type
	int win_mode;//see enum v4l2_ext_vsc_win_mode

	short skip;
	short bbd_pos;//0:input,1:middle
	short same_cnt;
	short same_mask;

	unsigned short hsize;
	unsigned short vsize;
	unsigned short vfreq;

	struct vsc_bbd_reg_isize reg_isize;
	struct vsc_bbd_reg_stat0 reg_stat0;
	struct vsc_bbd_reg_stat1 reg_stat1;

	struct vsc_bbd_rect pre_bbd;
	struct vsc_bbd_rect ret_bbd;
	struct vsc_bbd_rect pre_act[VSC_BBD_NUM];
	struct vsc_bbd_rect pre_rpt;//pre reported
	struct vsc_bbd_win pre;

	struct vsc_bbd_rect cur_bbd;
	struct vsc_bbd_rect dif_bbd;
	struct vsc_bbd_win cur;
};

extern int vsc_bbd_init(void);
extern int vsc_bbd_status(char* buffer);
extern int vsc_bbd_command(char* command);
extern int vsc_bbd_setdbglevel(int level);
extern int vsc_bbd_getdbglevel(void);
extern int vsc_bbd_init_cfg(int wid, struct vsc_bbd_cfg *pcfg);
extern int vsc_bbd_checkupdate(struct vsc_bbd_cfg *pcfg);

#endif /* _VSC_BBD_H_ */
