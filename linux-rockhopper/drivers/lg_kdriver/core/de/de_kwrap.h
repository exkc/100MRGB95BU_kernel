/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file de_kwrap.h
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     dongho7.park (dongho7.park@lge.com)
 *  @version    1.0
 *  @date       2010-02-07
 *  @note       Additional information.
 */

#ifndef	_DE_KWRAP_H_
#define	_DE_KWRAP_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define NUM_OF_CVI_FIR_COEF 8
#define	DE_MAX_INPUT_HSIZE 1920
#define	DE_MAX_INPUT_VSIZE 1200
#define	DE_FHD_DISPLAY_HSIZE 1920
#define	DE_FHD_DISPLAY_VSIZE 1080
#define DE_H1024_IS_HD 1024

#define DE_WIN_BlANK_USE	// use winblank from DE F/W rev.25048
#define SEE_TV
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * de input source type.
 */
typedef enum
{
	// Component Analog ports
	INPUT_SRC_VGA,
	INPUT_SRC_YPBPR_1,
	INPUT_SRC_YPBPR_2,

	// Composite Analog ports
	INPUT_SRC_ATV,
	INPUT_SRC_CVBS_1,
	INPUT_SRC_CVBS_2,
	INPUT_SRC_CVBS_3,

	// Seperate Analog Ports
	INPUT_SRC_SVIDEO_1,
	INPUT_SRC_SVIDEO_2,

	// SCART port
	INPUT_SRC_SCART_1,
	INPUT_SRC_SCART_RGB_1,
	INPUT_SRC_SCART_2,

	// HDMI ports
	INPUT_SRC_HDMI_A,
	INPUT_SRC_HDMI_B,
	INPUT_SRC_HDMI_C,
	INPUT_SRC_HDMI_D,

	// MVD ports
	INPUT_SRC_DTV,
	INPUT_SRC_DTV_MLINK,

	INPUT_SRC_STORAGE,

	INPUT_SRC_JPG,

	INPUT_SRC_VCS,
	INPUT_SRC_NUM,
	INPUT_SRC_NONE = INPUT_SRC_NUM,
}
kwrap_de_input_src_t;

/**
 * de msc shift type.
 */
typedef enum
{
	LX_DE_SHIFT_LEFT,
	LX_DE_SHIFT_RIGHT,
	LX_DE_SHIFT_UP,
	LX_DE_SHIFT_DOWN
}
lx_de_msc_shift_t;

/**
 * Structure used to get video delay time for AV sync adjustment
 * @see lx_de_frame_info_t
 */
typedef struct {
	UINT8 u8_cvd;
	UINT8 u8_pre3d;
	UINT8 u8_tnr;
	UINT8 u8_deinter;
	UINT8 u8_scaler;
} lx_de_frame_info_t;

/**
 * de vt extention parameters.
 */
 typedef struct {
 	UINT32       win_id;
 	UINT32       location;
	LX_DE_RECT_T input_region;
	LX_DE_RECT_T output_max_region;
	LX_DE_RECT_T output_active_region;
	UINT32       stride;
	LX_DE_SCAN_T scan;
	UINT32       is3D;
	UINT32       mute_status;
	UINT32       rate;
	UINT32       frz;
	UINT32       frc_mode;
} lx_de_vt_ext_param_t;

typedef enum {
	VTM_GET_CAPTURE_LOCATION,
	VTM_SET_CAPTURE_LOCATION,
	VTM_GET_OUTPUT_REGION,
	VTM_SET_OUTPUT_REGION,
	VTM_SET_INPUT_REGION,
	VTM_GET_INPUT_INFO,
	VTM_GET_OUTPUT_INFO,
	VTM_GET_MUTE_STATUS,
	VTM_SET_FREEZE,
	VTM_SET_RATE,
	VTM_GET_FREEZE_RATE
} lx_de_vt_ext_cmd_t;


struct header_fpp{
    int body_offset;    // pointer of body_fpp
    int buffer_num;    // total buffer number
    int width;
    int height;
    int stride;
    int buffer_index;  // last updated buffer
    int dummy[2];
};

struct header_bv{
    int body_offset; // pointer of body_bv
    int bv_width;
    int bv_height;
    int dummy[5];
};

struct body_fpp{
    unsigned int Y_addr[16];
    unsigned int C_addr[16];
    int curr_index;
};

struct body_bv{
    int protection;
    int curr_index;
    unsigned short origin_bv[256];
    int proc_index;
    int count;
    int table_index;
    unsigned short proc_bv[256];
};

struct fpp_bv_structure{
    struct header_fpp fpp;
    struct header_bv   bv;
	int enable;
	int bv_need;
    //void *payload;
    struct body_fpp   fpp_val;
	struct body_bv    bv_val;
};

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int de_kwrap_sethdmi444mode(UINT32 win, LX_DE_HDMI444_MODE_T mode);
int de_kwrap_gethdmi444mode(UINT32 win, LX_DE_HDMI444_MODE_T *mode);
int de_kwrap_getsourcestatus(LX_DE_SRC_STATUS_T *param);
int de_kwrap_getcapacity(LX_DE_CAPACITY_T *p_capa);
int de_kwrap_setipchdrmode(UINT8 i_ucWinID,LX_HDR_MODE_T i_IpcMode,LX_HDR_MODE_FROM_T i_From);
int de_kwrap_setlowdelaymode(UINT32 param);
int de_kwrap_setinnerpattern(LX_DE_INNER_PATTERN_T *param);
int de_kwrap_setwinsrcport(LX_DE_INPUT_SOURCE_T *param);

#if 0	//not used
int de_kwrap_open(void);
int de_kwrap_isopen(void);
int de_kwrap_close(void);
int de_kwrap_init(BOOLEAN isFullHD);
int de_kwrap_fw_download(LX_DE_FW_DWLD_T *param);
int de_kwrap_getfirmwareinfo(LX_DE_FIRMWARE_INFO_T *info);

int de_kwrap_getinnerpattern(LX_DE_INNER_PATTERN_T *param);
int de_kwrap_setbgcolor(UINT8 red, UINT8 green, UINT8 blue);
int de_kwrap_getoutfrrate(BOOLEAN *isForceFreeRun, UINT16 *dis_fr);
int de_kwrap_setwinblank(UINT8 wId, BOOLEAN bOnOff, UINT8 color);
int de_kwrap_getinputwin(UINT8 wId, LX_DE_RECT_T *pIn);
int de_kwrap_getoutwin(UINT8 wId, LX_DE_RECT_T *pOut);
int de_kwrap_getoutwincached(UINT8 wId, LX_DE_RECT_T *pOut);
int de_kwrap_setinputwin(UINT8 wId, LX_DE_RECT_T *pIn);
int de_kwrap_setoutwin(UINT8 wId, LX_DE_RECT_T *pOut);
int de_kwrap_setwindowinfo(LX_DE_WIN_INFO_T *pWinInfo);
int de_kwrap_setwinfreeze(LX_DE_WIN_FREEZE_T *param);
int de_kwrap_setdisout(BOOLEAN isOn);
int de_kwrap_setdisfmt(LX_DE_DIS_FMT_T dis_fmt);
int de_kwrap_getdisfmt(LX_DE_DIS_FMT_T *dis_fmt);
int de_kwrap_setfrrate(BOOLEAN isForceFreeRun, UINT16 frameRates);
int de_kwrap_setmultiwinenable(BOOLEAN isEnable);
int de_kwrap_getmultiwinenable(BOOLEAN *isEnable);
int de_kwrap_setcvisrctype(UINT8 wId, kwrap_de_input_src_t source);
int de_kwrap_setcvisrc(LX_DE_CVI_SRC_TYPE_T *param);

int de_kwrap_getmvicolorimetry(UINT8 wId, LX_DE_COLOR_STD_T *colorimetry);
int de_kwrap_setuart4mcu(BOOLEAN bUart4MCU);
int de_kwrap_setudmode(LX_DE_UD_CTRL_T udCtrl);
int de_kwrap_getudmode(LX_DE_UD_CTRL_T *isUD);
int de_kwrap_setcve(LX_DE_CVE_PATH_T path, LX_DE_CVE_TIMING_T standard);
int de_kwrap_setvcs(UINT32 inx, UINT32 data);
// for debug
int de_kwrap_regrd(UINT32 addr, UINT32 *data);
int de_kwrap_regwr(UINT32 addr, UINT32 data);

// DE additional adapation lists
int de_kwrap_setcvifir(UINT8 wId, LX_DE_CVI_SAMPLING_MODE_T sample_mode, LX_DE_CVI_INPUT_SRC_T cvi_input_src);
int de_kwrap_gethdmisamplemode(UINT16 hActive, UINT16 vActive, UINT8 scanType, UINT8 *hdmi_sample);
int de_kwrap_setcvitpg(UINT8 wId, BOOLEAN isPtnOn, LX_DE_CVI_TPG_COLOR_T ptnColor);
int de_kwrap_setcvicsamplemode(UINT8 wId, BOOLEAN enable);

int de_kwrap_setdvrfmtctrl(UINT8 isOn, LX_DE_SCAN_T scan_type, UINT16 h_size, UINT16 v_size, UINT32 fr_rate);
int de_kwrap_getdvrfmtctrl(LX_DE_DVR_DISFMT_T *dvr_param);

int de_kwrap_setsubscalerfreeze(BOOLEAN isOn);
int de_kwrap_setcvifreeze(LX_DE_CVI_CAPTURE_FREEZE_T cap_freeze);
int de_kwrap_set_cvirwvideoframebuffer(LX_DE_CVI_RW_VIDEO_FRAME_T param);
int de_kwrap_read_cvivideoframebuffer(LX_DE_CVI_RW_VIDEO_FRAME_T param, UINT16 hoffset, UINT16 voffset);
int de_kwrap_read_cvivideoframebuffer_4k(LX_DE_CVI_RW_VIDEO_FRAME_T param, UINT16 hoffset, UINT16 voffset, int cvi_b_mode);
int de_kwrap_debugenable_cvivideoframebuffer(int enable);
int de_kwrap_setscartrgbbypassmode(int Bypass_Enable);
int de_kwrap_getzorderandalphablending(LX_DE_ZLIST_T *param);
int de_kwrap_setzorderandalphablending(LX_DE_ZLIST_T param);
int de_kwrap_setadcsrcchangeflag(BOOLEAN enable);
int de_kwrap_getlowdelaymode(LX_DE_LOW_DELAY_T *param);

int de_kwrap_setmultivision(UINT16 w_block, UINT16 h_block, UINT16 x, UINT16 y);
int de_kwrap_getcapturerawimage(LX_DE_PAR_CAPTURE_RAW_IMAGE_T *capture_info);

int de_kwrap_setdbgctrl(LX_DE_SET_DBG_T param);
void	de_kwrap_debug_test (void);
void	de_kwrap_reg_debug_test (void);

int de_kwrap_setifconfig(LX_DE_IF_CONFIG_T *param);
int de_kwrap_3dinoutctrl(LX_DE_3D_INOUT_CTRL_T *param);
int de_kwrap_getsysstatus(LX_DE_SYS_STATUS_T *param);
int de_kwrap_setoperation(LX_DE_OPERATION_CTRL_T *param);
int de_kwrap_setsuboperation(LX_DE_SUB_OPERATION_CTRL_T *param);
int de_kwrap_capturevideoframe(LX_DE_CAPTURE_CTRL_T *param);
int de_kwrap_framecapture(UINT32 isOn, LX_DE_CAPTURE_CTRL_T *param);
int de_kwrap_getscalerinfo(LX_DE_SCALER_INFO_T *param);
int de_kwrap_setoutputmode(LX_DE_OUTPUT_MODE_T *param);
int de_kwrap_setsrcmirror(LX_DE_SRC_MIRROR_T param);

#if 1 // for fpga verification
int de_kwrap_clidbg(LX_DE_SET_EVAL_DBG_T param);
int de_kwrap_getfd(void);
#endif // #if 0

int de_kwrap_setvtm(LX_DE_VTM_FRAME_INFO_T *param);
int de_kwrap_getvtm(LX_DE_VTM_FRAME_INFO_T *param);
int de_kwrap_getvtmbuffer(LX_DE_VTM_FRAME_INFO_T *param);
int de_kwrap_getvtmindex(LX_DE_WIN_ID_T win_id, UINT32 *idx);
int de_kwrap_getvtmstatus(LX_DE_WIN_ID_T win_id, LX_DE_VTM_FRAME_INFO_T *param);
int de_kwrap_vtmframecontrol(LX_DE_WIN_ID_T win_id, UINT32 read_flag, UINT32 rate);
int de_kwrap_setactfmtdetect(LX_DE_ACT_FORMAT_T param);

int de_kwrap_cap_open(void);
int de_kwrap_cap_isopen(void);
int de_kwrap_cap_close(void);
int de_kwrap_cap_capturevideoframe(LX_DE_CAPTURE_CTRL_T *param);
int de_kwrap_cap_framecapture(UINT32 isOn, LX_DE_CAPTURE_CTRL_T *param);

int de_kwrap_sethdmiport(UINT8 wId, UINT32 hdmi_port);
int de_kwrap_gethdmiport(UINT8 wId);
int de_kwrap_setsubwindow(UINT8 wId);
int de_kwrap_getvtmcapa(LX_DE_VT_CAPA_PARAM_T *p_vt_capa);
int de_kwrap_getvtmconfig(lx_de_vt_ext_cmd_t cmd, lx_de_vt_ext_param_t *p_param);
int de_kwrap_setvtmconfig(lx_de_vt_ext_cmd_t cmd, lx_de_vt_ext_param_t *p_param);
int de_kwrap_cmdvtm(lx_de_vt_ext_cmd_t cmd, lx_de_vt_ext_param_t *p_param);
int de_kwrap_setvtmblockstate(LX_DE_VTM_BLOCK_STATE_T *pstBlockState);
int de_kwrap_setdelaybuffer(UINT32 vpSrcId, UINT8 ubuffer);
int de_kwrap_setsubwinmode(LX_DE_SUB_MODE_T sub_mode);
int de_kwrap_getsubwinmode(LX_DE_SUB_MODE_T *param);
int de_kwrap_setsubwinshape(LX_DE_SUB_MGF_SHAPE_T sub_shape, LX_DE_RECT_T orgWin);
int de_kwrap_setsignagemode(BOOLEAN isEnable);
int de_kwrap_sethdmitxinfo(LX_DE_HDMITX_OUTPUT_INFO_T  hdmitx_info);
int de_kwrap_setsourcesizewin(UINT8 wId, LX_DE_RECT_T *inSize, LX_DE_RECT_T *inWin);
int de_kwrap_getsourcesizewin(UINT8 wId, LX_DE_RECT_T *inSize);
int de_kwrap_set4kdualmode(BOOLEAN bOnOff);
int de_kwrap_getsourcecapturebuffer(LX_DE_CVI_RW_VIDEO_FRAME_T param);
int de_kwrap_setdhdrinit(void);
int de_kwrap_setdhdr(LX_DE_DOLBYHDR_INFO_T *param);
int de_kwrap_setdhdrstatus(int dir, LX_DE_DOLBYHDR_INFO_T *param);
int de_kwrap_getdhdrstatus(LX_DE_DOLBYHDR_INFO_T *param);
int de_kwrap_waitdhdrint(UINT32 *param);

int de_kwrap_setgcpinit(void);
int de_kwrap_setgcp(LX_DE_GCP_INFO_T *param);
int de_kwrap_setgcpstatus(int dir, LX_DE_GCP_INFO_T *param);
int de_kwrap_getgcpstatus(LX_DE_GCP_INFO_T *param);
int de_kwrap_waitgcpint(UINT32 *param);

int de_kwrap_dhdripinit(UINT8 i_ucWinID,LX_DOLBY_IO_MAP_T *io_sPtrDolbyInit);
int de_kwrap_dhdripgethdmimetadata(UINT8 i_ucWinID,LX_DOLBY_DM_MD_TYPE *io_eMDType,LX_DOLBY_DM_MD_T *o_sPtrMetaData);
int de_kwrap_dhdripgetottmetadata(UINT8 i_ucWindId,UINT32 *o_nptrFlag);
int de_kwrap_dhdripmdreadunblock(UINT8 i_ucWinID);
int de_kwrap_dhdripuninit(UINT8 i_ucWinID);
int de_kwrap_dhdripgetconfig(UINT8 i_ucWinId,LX_DOLBY_CONFIG_REG_T *o_sPtrDolbyConfigParam);
int de_kwrap_dhdripsetconfig(UINT8 i_ucWinID,LX_DOLBY_CONFIG_REG_T *i_sPtrDolbyConfigParam);
int de_kwrap_dhdripsetlutconfig(UINT8 i_ucWinId,UINT32 *i_nptrFrameNum);
int de_kwrap_dhdripstart(UINT8 i_ucWinID);
int de_kwrap_dhdripsethdmi_md_path(UINT8 i_ucWinID,LX_HDR_HDMI_MD_PATH_T e_md_path);

int de_kwrap_setlowdelaybysourcesync(UINT32 uLowDelay);
int de_kwrap_sethighframerate(UINT32 uHfr);
int de_kwrap_setrotate(LX_DE_ROTATE_INFO_T rotate);
int de_kwrap_fpp_initialize(int bv_need, UINT32 **base, UINT32 *size);
int de_kwrap_getcapturebufferinfo(UINT32 *vt0_base, UINT32 *vt0_size, UINT32 *vt1_base, UINT32 *vt1_size);
#endif
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

