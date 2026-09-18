/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/


/** @file vpq_hwrap_hdr.h
 *
 *  application interface header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_VPQ_HWRAP_HDR_H_
#define	_VPQ_HWRAP_HDR_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/
/* 20210420, support HDR2SDR(AVTASK-528) */
#undef VPQ_HWRAP_SUPPORT_HDR2SDR

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
/* MI(ModeInfo) Type, see LX_PE_HDR_OP_MD_T */
enum vpq_hwrap_hdr_mi_type {
	VPQ_HWRAP_HDR_MI_NONE    = 0x00,	///< none
	VPQ_HWRAP_HDR_MI_CONNECT = 0x01,	///< connect, 0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg
	VPQ_HWRAP_HDR_MI_HDRTONE = 0x02,	///< hdr tone, 0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg
	VPQ_HWRAP_HDR_MI_HDRCASE = 0x04,	///< hdr case, 0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg
	VPQ_HWRAP_HDR_MI_COLMTRY = 0x08,	///< colorimetry, 0:601,1:709,2:2020
	VPQ_HWRAP_HDR_MI_HDR_OFF = 0x10,	///< hdr_off, 0:normal,1:hdr_off,2:pcc_only
	VPQ_HWRAP_HDR_MI_CUR_MOD = 0x20,	///< cur_mod, 0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg (read only)
	VPQ_HWRAP_HDR_MI_SUP_MOD = 0x40,	///< sup_mod, prime, 0:no,1:yes
	VPQ_HWRAP_HDR_MI_DISPBRI = 0x80,	///< display brigntness
	VPQ_HWRAP_HDR_MI_NUM     = 0xff	///< max num
};

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/
extern int vpq_hwrap_hdr_init(void);
extern int vpq_hwrap_sethdrmodeinfo(void *param);
extern int vpq_hwrap_gethdrmodeinfo(void *param);
extern int vpq_hwrap_sethdropmodeinfo(UINT32 type, LX_PE_HDR_MODE_INFO_T *param);
extern int vpq_hwrap_dbg_sethdreotflut(UINT32 wid, UINT32 type);
extern int vpq_hwrap_dbg_sethdroetflut(UINT32 wid, UINT32 type);
extern int vpq_hwrap_sethdrfunctionenable(int enable);
extern int vpq_hwrap_gethdrfunctionenable(void);
extern int vpq_hwrap_sethdrinvgamma(unsigned int *p_param);
extern int vpq_hwrap_gethdrinvgamma(unsigned int *p_param);
extern int vpq_hwrap_gethdrpicinfo(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_sethdreotf(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_gethdreotf(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_sethdrtonemap(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_gethdrtonemap(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_sethdrlowlevellut(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_sethdrcolorcorrection(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_gethdrcolorcorrection(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_sethlgygaintable(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_gethlgygaintable(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_setgamutmatrixpre(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getgamutmatrixpre(struct v4l2_ext_vpq_cmn_data *p_param);

#endif /* _VPQ_HWRAP_HDR_H_ */
