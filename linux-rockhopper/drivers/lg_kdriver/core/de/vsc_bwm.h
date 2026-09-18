#ifndef	_VSC_BWM_H_
#define	_VSC_BWM_H_

enum vsc_bwm_opt
{
	VSC_BWM_OPT_INPUT = 0x0,
	VSC_BWM_OPT_SIZE,
	VSC_BWM_OPT_HDR,
	VSC_BWM_OPT_HDMI444,
	VSC_BWM_OPT_MAX
};

struct vsc_bwm_cfg
{
	UINT32 input;//see v4l2_ext_vsc_input_src

	struct {
		UINT32 w;
		UINT32 h;
		UINT32 rate;//x10 hz
	} size;

	UINT32 hdr;//see enum v4l2_ext_vsc_hdr_type

	UINT32 hdmi444;
};

extern int vsc_bwm_init(void);
extern int vsc_bwm_set_config(enum vsc_bwm_opt opt, struct vsc_bwm_cfg *cfg);
extern int vsc_bwm_noti(void);
extern int vsc_bwm_help(char* buffer);
extern int vsc_bwm_set_dbg(char* command);

#endif /* _VSC_BWM_H_ */
