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


/** @file vpq_hwrap.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- master pe kwrap file includes init & misc functions
 *
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

#ifdef INCLUDE_KDRV_BE

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_def.h"
#include "be_kapi.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_be.h"
#include "be_proc.h"
#include "frc_hal.h"
#include "pe_cmn.h"
#include "led_hal.h"
#include "pe_csc.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

#define _VPQ_BE_CSC_X100002H(x, bit)	_VPQ_BE_ConvCscX10000ToHex((SINT16)(x), (UINT8)(bit))

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
static UINT32 _VPQ_BE_ConvCscX10000ToHex(SINT16 input, UINT8 signBit)
{
	UINT32 output = 0;
	SINT32 temp = 0;

	temp = (SINT32)((input*4096)/10000);

	if (temp&((0x1)<<signBit))
		output = temp | ( 0xffffffff << signBit );
	else
		output = temp & ( 0xffffffff >> (31-signBit) );

	return output;
}



/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

int vpq_hwrap_memc_setmotioncomp(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	LX_BE_FRC_MEMC_MODE_T mode;
	struct v4l2_ext_memc_motion_comp_info *p_data;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	p_data = (struct v4l2_ext_memc_motion_comp_info *)p_param->p_data;

	/* UI(0:off, 1:low, 2:high, 3:user, 4: 55pull do wn), FW(0:off, 1:low, 2:medium,  3:high, 4:user, 5: 55pull down) */
	do {
			mode.u8Blur = p_data->blur_level;
			mode.u8Judder = p_data->judder_level;
			mode.u8MemcType = p_data->memc_type;

			switch (mode.u8MemcType) {
				case 1:
						mode.u8MemcType = 2;
					break;
				case 2:
						mode.u8MemcType = 3;
					break;
				case 3:
						mode.u8MemcType = 4;
					break;
				case 4:
						mode.u8MemcType = 5;
					break;
				case 5:
						mode.u8MemcType = 1;
					break;
				case 6:
						mode.u8MemcType = 6;
					break;
				default :
						mode.u8MemcType = 0;
					break;
				}
					PE_PRINT_VPQ_BE("u8Blur: %d, u8Judder: %d, u8MemcType: %d\n", mode.u8Blur, mode.u8Judder,mode.u8MemcType);
		}while(0);

	ret = BE_FRC_HAL_ControlMemc(&mode);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. BE_FRC_HAL_ControlMemc()\n");

	return ret;
}

int vpq_hwrap_memc_lowdelaymode(unsigned int *p_param)
{
	int ret = RET_OK;
	LX_BE_FRC_LOW_DELAY_T mode;
	
	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	
	mode.u32Lowdelay = (*p_param)? 1:0;	
	
	ret = BE_FRC_HAL_Set_Low_Delay(&mode);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. BE_FRC_HAL_ControlMemc()\n");
	
	return ret;
}

int vpq_hwrap_memc_motionpro(unsigned int *p_param)
{
	int ret = RET_OK;	
	LX_BE_FRC_MOTION_PRO_T mode;
	
	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");

	mode.u32MotionPro = *p_param;
	
	ret = BE_FRC_HAL_Set_Motion_Pro(&mode);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. BE_FRC_HAL_ControlMemc()\n");

	return ret;
}

int vpq_hwrap_gamut_matrix_post(struct v4l2_ext_vpq_cmn_data *param, UINT16 *p_PccMatrix)
{
	int ret = RET_OK;
	v4l2_hwrap_pcc_lllut pcc_llut;
	LX_BE_PQ_PCC_PARAMS_T pccParams;
	LX_PE_CSC_LLLUT_CTRL_T pccLutParam;
	LX_BE_PQ_PCC_T pccParam;
	LX_BE_PQ_PCC_GAMMA_T gammaParam;
	LX_BE_PQ_PCC_MUX_BLEND_T muxParam;
	int i;
	if (param->version == 0x80)
	{
		v4l2_hwrap_gamut_post_v3 *data3;
		LX_PE_CSC_POST_PCC_CTRL_T csc_post_pcc_lut;
		if (!(data3 = OS_Malloc(sizeof(v4l2_hwrap_gamut_post_v3))))
		{
			PE_PRINT_ERROR("OS_Malloc error\n");
			if (data3)
			{
				OS_Free(data3);
			}
			return -ENOMEM;
		}
		if (copy_from_user(data3,(void __user *)param->p_data,sizeof(v4l2_hwrap_gamut_post_v3)))
		{
			PE_PRINT_ERROR("copy_from_user error v4l2_hwrap_gamut_post_v3\n");
			if (data3)
			{
				OS_Free(data3);
			}
			return -EINVAL;
		}

		if (sizeof(data3->matrix)/sizeof(data3->matrix[0])
			!= LX_BE_PQ_NUM_OF_PCC_COEF)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data3)
			{
				OS_Free(data3);
			}
			return -EINVAL;
		}

		if (sizeof(data3->mux_blend.b4p_lut_x)/sizeof(data3->mux_blend.b4p_lut_x[0])
			!= LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data3)
			{
				OS_Free(data3);
			}
			return -EINVAL;
		}

		if (sizeof(data3->mux_blend.b4p_lut_y)/sizeof(data3->mux_blend.b4p_lut_y[0])
			!= LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data3)
			{
				OS_Free(data3);
			}
			return -EINVAL;
		}
		if(copy_from_user(&pcc_llut,(void __user *)data3->pst_chip_data,sizeof(v4l2_hwrap_pcc_lllut)))
		{
			PE_PRINT_ERROR("copy_from_user error, v4l2_hwrap_pcc_lllut\n");
			if (data3)
			{
				OS_Free(data3);
			}
			return -EINVAL;
		}

		pccLutParam.win_id = 0;
		memcpy(&(pccLutParam.lllut_en), &pcc_llut, sizeof(v4l2_hwrap_pcc_lllut));
		csc_post_pcc_lut.win_id = 0;
		memcpy(&(csc_post_pcc_lut.sat_gain), &data3->post_pcc_lut, sizeof(v4l2_hwrap_csc_post_pcc_lut));

		PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, g:%d,d:%d\n",\
			param->version,param->length,param->wid,\
			data3->bGamma,data3->bDeGamma);
		PE_PRINT_VPQ_BE("m0:0x%x,m1:0x%x,m2:0x%x\n",\
			data3->matrix[0],data3->matrix[1],data3->matrix[2]);
		PE_PRINT_VPQ_BE("m3:0x%x,m4:0x%x,m5:0x%x\n",\
			data3->matrix[3],data3->matrix[4],data3->matrix[5]);
		PE_PRINT_VPQ_BE("m6:0x%x,m7:0x%x,m8:0x%x\n",\
			data3->matrix[6],data3->matrix[7],data3->matrix[8]);
		PE_PRINT_VPQ_BE("mb l3:%d,bl:%d,4p:%d,oe:%d\n",\
			data3->mux_blend.mux_l3d_in,data3->mux_blend.mux_blend_in,
			data3->mux_blend.mux_4p_lut_in,data3->mux_blend.mux_oetf_out);
		PE_PRINT_VPQ_BE("x0:0x%x,x1:0x%x,x2:0x%x,x3:0x%x\n",\
			data3->mux_blend.b4p_lut_x[0],data3->mux_blend.b4p_lut_x[1],
			data3->mux_blend.b4p_lut_x[2],data3->mux_blend.b4p_lut_x[3]);
		PE_PRINT_VPQ_BE("y0:0x%x,y1:0x%x,y2:0x%x,y3:0x%x\n",\
			data3->mux_blend.b4p_lut_y[0],data3->mux_blend.b4p_lut_y[1],
			data3->mux_blend.b4p_lut_y[2],data3->mux_blend.b4p_lut_y[3]);

		PE_PRINT_VPQ_BE("*csc_post_pcc_lut*\n"\
			"u_Sat_gain : %d, uHue_comp_gain : %d, uSta_comp_gain : %d\n"\
			"uLumaGainLUT_x[4]: %d, %d, %d, %d\n"\
			"uLumaGainLUT_y[4]: %d, %d, %d, %d\n"\
			"uSatGainLUT_x[5] : %d, %d, %d, %d, %d\n"\
			"uSatGainLUT_y[5] : %d, %d, %d, %d, %d\n",
			data3->post_pcc_lut.u_Sat_gain,data3->post_pcc_lut.uHue_comp_gain,data3->post_pcc_lut.uSta_comp_gain,\
			data3->post_pcc_lut.uLumaGainLUT_x[0],data3->post_pcc_lut.uLumaGainLUT_x[1],\
			data3->post_pcc_lut.uLumaGainLUT_x[2],data3->post_pcc_lut.uLumaGainLUT_x[3],\
			data3->post_pcc_lut.uLumaGainLUT_y[0],data3->post_pcc_lut.uLumaGainLUT_y[1],\
			data3->post_pcc_lut.uLumaGainLUT_y[2],data3->post_pcc_lut.uLumaGainLUT_y[3],\
			data3->post_pcc_lut.uSatGainLUT_x[0],data3->post_pcc_lut.uSatGainLUT_x[1],\
			data3->post_pcc_lut.uSatGainLUT_x[2],data3->post_pcc_lut.uSatGainLUT_x[3],data3->post_pcc_lut.uSatGainLUT_x[4],\
			data3->post_pcc_lut.uSatGainLUT_y[0],data3->post_pcc_lut.uSatGainLUT_y[1],\
			data3->post_pcc_lut.uSatGainLUT_y[2],data3->post_pcc_lut.uSatGainLUT_y[3],data3->post_pcc_lut.uSatGainLUT_y[4]);

		PE_PRINT_VPQ_BE("*pcc lllut*\n"\
			"lllut_en :%d, lllut_csc_en :%d,\n"\
			"lllut_r[0,1,2..125,126,127] :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"lllut_g[0,1,2..125,126,127] :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"lllut_b[0,1,2..125,126,127] :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"matrix:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"blend_in_sel: 0x%x\n"\
			"r2y_matrix : 0x%x,0x%x,0x%x\n"\
			"blend_lut_x :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"blend_lut_y :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"hue_gain :0x%x, sat_gain :0x%x,\n",\
			pccLutParam.lllut_en, pccLutParam.lllut_csc_en,\
			pccLutParam.lllut_r[0],pccLutParam.lllut_r[1],pccLutParam.lllut_r[2],\
			pccLutParam.lllut_r[125],pccLutParam.lllut_r[126],pccLutParam.lllut_r[127],\
			pccLutParam.lllut_g[0],pccLutParam.lllut_g[1],pccLutParam.lllut_g[2],\
			pccLutParam.lllut_g[125],pccLutParam.lllut_g[126],pccLutParam.lllut_g[127],\
			pccLutParam.lllut_b[0],pccLutParam.lllut_b[1],pccLutParam.lllut_b[2],\
			pccLutParam.lllut_b[125],pccLutParam.lllut_b[126],pccLutParam.lllut_b[127],\
			pccLutParam.matrix[0],pccLutParam.matrix[1],pccLutParam.matrix[2],\
			pccLutParam.matrix[3],pccLutParam.matrix[4],pccLutParam.matrix[5],\
			pccLutParam.matrix[6],pccLutParam.matrix[7],pccLutParam.matrix[8],\
			pccLutParam.blend_in_sel,\
			pccLutParam.r2y_matrix[0],pccLutParam.r2y_matrix[1],pccLutParam.r2y_matrix[2],\
			pccLutParam.blend_lut_x[0],pccLutParam.blend_lut_x[1],pccLutParam.blend_lut_x[2],\
			pccLutParam.blend_lut_x[3],pccLutParam.blend_lut_x[4],pccLutParam.blend_lut_x[5],\
			pccLutParam.blend_lut_y[0],pccLutParam.blend_lut_y[1],pccLutParam.blend_lut_y[2],\
			pccLutParam.blend_lut_y[3],pccLutParam.blend_lut_y[4],pccLutParam.blend_lut_y[5],\
			pccLutParam.hue_gain, pccLutParam.sat_gain);

		PE_PRINT_VPQ_BE("csc_post_pcc_lut :\n"\
			"sat_gain : %d, hue_comp_gain:%d, sat_comp_gain:%d,\n"\
			"luma_gain_lut_x[0~3] : %d, %d, %d, %d\n"\
			"luma_gain_lut_y[0~3] : %d, %d, %d, %d\n"\
			"sat_gain_lut_x[0~4] : %d, %d, %d, %d, %d\n"\
			"sat_gain_lut_y[0~4] : %d, %d, %d, %d, %d\n",\
			csc_post_pcc_lut.sat_gain,csc_post_pcc_lut.hue_comp_gain,csc_post_pcc_lut.sat_comp_gain,\
			csc_post_pcc_lut.luma_gain_lut_x[0],csc_post_pcc_lut.luma_gain_lut_x[1],csc_post_pcc_lut.luma_gain_lut_x[2],csc_post_pcc_lut.luma_gain_lut_x[3],\
			csc_post_pcc_lut.luma_gain_lut_y[0],csc_post_pcc_lut.luma_gain_lut_y[1],csc_post_pcc_lut.luma_gain_lut_y[2],csc_post_pcc_lut.luma_gain_lut_y[3],\
			csc_post_pcc_lut.sat_gain_lut_x[0],csc_post_pcc_lut.sat_gain_lut_x[1],csc_post_pcc_lut.sat_gain_lut_x[2],\
			csc_post_pcc_lut.sat_gain_lut_x[3],csc_post_pcc_lut.sat_gain_lut_x[4],\
			csc_post_pcc_lut.sat_gain_lut_y[0],csc_post_pcc_lut.sat_gain_lut_y[1],csc_post_pcc_lut.sat_gain_lut_y[2],\
			csc_post_pcc_lut.sat_gain_lut_y[3],csc_post_pcc_lut.sat_gain_lut_y[4]);

		for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
		{
			pccParams.matrix[i] = (UINT16)_VPQ_BE_CSC_X100002H(data3->matrix[i], 14);
			p_PccMatrix[i] = data3->matrix[i];
		}

		pccParams.bOetfGammaEn = data3->bGamma;
		pccParams.bEotfGammaEn = data3->bDeGamma;

		pccParams.u32MuxL3dIn = (UINT32)data3->mux_blend.mux_l3d_in;
		pccParams.u32MuxBlendIn = (UINT32)data3->mux_blend.mux_blend_in;
		pccParams.u32Mux4pLutIn = (UINT32)data3->mux_blend.mux_4p_lut_in;
		pccParams.u32MuxOetfOut = (UINT32)data3->mux_blend.mux_oetf_out;
		for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
		{
			pccParams.au32B4pLutX[i] = (UINT32)data3->mux_blend.b4p_lut_x[i];
			pccParams.au32B4pLutY[i] = (UINT32)data3->mux_blend.b4p_lut_y[i];
		}

		pccParams.bIsGet = FALSE;
		ret = BE_PQ_HAL_Set_PccParams(&pccParams);
		if (ret)
		{
			PE_PRINT_ERROR("BE_PQ_HAL_Set_PccParams error(%d)\n",ret);
			if (data3)
			{
				OS_Free(data3);
			}
			return ret;
		}

		ret = PE_CSC_SetLllut(&pccLutParam);
		if (ret)
		{
			PE_PRINT_ERROR("PE_CSC_SetLllut error(%d)\n",ret);
			if (data3)
			{
				OS_Free(data3);
			}
			return ret;
		}
		ret = PE_CSC_SetPostPcc(&csc_post_pcc_lut);
		if (ret)
		{
			PE_PRINT_ERROR("PE_CSC_SetPostPcc error(%d)\n",ret);
			if (data3)
			{
				OS_Free(data3);
			}
			return ret;
		}
		if (data3)
		{
			OS_Free(data3);
		}
	}
	else if (param->version >= 3)
	{
		v4l2_hwrap_gamut_post_v2 *data2;
		if (!(data2 = OS_Malloc(sizeof(v4l2_hwrap_gamut_post_v2))))
		{
			PE_PRINT_ERROR("OS_Malloc error\n");
			if (data2)
			{
				OS_Free(data2);
			}
			return -ENOMEM;
		}
		if (copy_from_user(data2,(void __user *)param->p_data,sizeof(v4l2_hwrap_gamut_post_v2)))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
			if (data2)
			{
				OS_Free(data2);
			}
			return -EINVAL;
		}

		if (sizeof(data2->matrix)/sizeof(data2->matrix[0])
			!= LX_BE_PQ_NUM_OF_PCC_COEF)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data2)
			{
				OS_Free(data2);
			}
			return -EINVAL;
		}

		if (sizeof(data2->mux_blend.b4p_lut_x)/sizeof(data2->mux_blend.b4p_lut_x[0])
			!= LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data2)
			{
				OS_Free(data2);
			}
			return -EINVAL;
		}

		if (sizeof(data2->mux_blend.b4p_lut_y)/sizeof(data2->mux_blend.b4p_lut_y[0])
			!= LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data2)
			{
				OS_Free(data2);
			}
			return -EINVAL;
		}

		if(copy_from_user(&pcc_llut,(void __user *)data2->pst_chip_data,sizeof(v4l2_hwrap_pcc_lllut)))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
			if (data2)
			{
				OS_Free(data2);
			}
			return -EINVAL;
		}

		pccLutParam.win_id = 0;
		memcpy(&(pccLutParam.lllut_en), &pcc_llut, sizeof(v4l2_hwrap_pcc_lllut));
		PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, g:%d,d:%d\n",\
			param->version,param->length,param->wid,\
			data2->bGamma,data2->bDeGamma);
		PE_PRINT_VPQ_BE("m0:0x%x,m1:0x%x,m2:0x%x\n",\
			data2->matrix[0],data2->matrix[1],data2->matrix[2]);
		PE_PRINT_VPQ_BE("m3:0x%x,m4:0x%x,m5:0x%x\n",\
			data2->matrix[3],data2->matrix[4],data2->matrix[5]);
		PE_PRINT_VPQ_BE("m6:0x%x,m7:0x%x,m8:0x%x\n",\
			data2->matrix[6],data2->matrix[7],data2->matrix[8]);
		PE_PRINT_VPQ_BE("mb l3:%d,bl:%d,4p:%d,oe:%d\n",\
			data2->mux_blend.mux_l3d_in,data2->mux_blend.mux_blend_in,
			data2->mux_blend.mux_4p_lut_in,data2->mux_blend.mux_oetf_out);
		PE_PRINT_VPQ_BE("x0:0x%x,x1:0x%x,x2:0x%x,x3:0x%x\n",\
			data2->mux_blend.b4p_lut_x[0],data2->mux_blend.b4p_lut_x[1],
			data2->mux_blend.b4p_lut_x[2],data2->mux_blend.b4p_lut_x[3]);
		PE_PRINT_VPQ_BE("y0:0x%x,y1:0x%x,y2:0x%x,y3:0x%x\n",\
			data2->mux_blend.b4p_lut_y[0],data2->mux_blend.b4p_lut_y[1],
			data2->mux_blend.b4p_lut_y[2],data2->mux_blend.b4p_lut_y[3]);

		PE_PRINT_VPQ_BE("*pcc lllut*\n"\
			"lllut_en :%d, lllut_csc_en :%d,\n"\
			"lllut_r[0,1,2..125,126,127] :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"lllut_g[0,1,2..125,126,127] :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"lllut_b[0,1,2..125,126,127] :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"matrix:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"blend_in_sel: 0x%x\n"\
			"r2y_matrix : 0x%x,0x%x,0x%x\n"\
			"blend_lut_x :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"blend_lut_y :0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
			"hue_gain :0x%x, sat_gain :0x%x,\n",\
			pccLutParam.lllut_en, pccLutParam.lllut_csc_en,\
			pccLutParam.lllut_r[0],pccLutParam.lllut_r[1],pccLutParam.lllut_r[2],\
			pccLutParam.lllut_r[125],pccLutParam.lllut_r[126],pccLutParam.lllut_r[127],\
			pccLutParam.lllut_g[0],pccLutParam.lllut_g[1],pccLutParam.lllut_g[2],\
			pccLutParam.lllut_g[125],pccLutParam.lllut_g[126],pccLutParam.lllut_g[127],\
			pccLutParam.lllut_b[0],pccLutParam.lllut_b[1],pccLutParam.lllut_b[2],\
			pccLutParam.lllut_b[125],pccLutParam.lllut_b[126],pccLutParam.lllut_b[127],\
			pccLutParam.matrix[0],pccLutParam.matrix[1],pccLutParam.matrix[2],\
			pccLutParam.matrix[3],pccLutParam.matrix[4],pccLutParam.matrix[5],\
			pccLutParam.matrix[6],pccLutParam.matrix[7],pccLutParam.matrix[8],\
			pccLutParam.blend_in_sel,\
			pccLutParam.r2y_matrix[0],pccLutParam.r2y_matrix[1],pccLutParam.r2y_matrix[2],\
			pccLutParam.blend_lut_x[0],pccLutParam.blend_lut_x[1],pccLutParam.blend_lut_x[2],\
			pccLutParam.blend_lut_x[3],pccLutParam.blend_lut_x[4],pccLutParam.blend_lut_x[5],\
			pccLutParam.blend_lut_y[0],pccLutParam.blend_lut_y[1],pccLutParam.blend_lut_y[2],\
			pccLutParam.blend_lut_y[3],pccLutParam.blend_lut_y[4],pccLutParam.blend_lut_y[5],\
			pccLutParam.hue_gain, pccLutParam.sat_gain);

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0))
		{
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
			{
				pccParams.matrix[i] = (UINT16)_VPQ_BE_CSC_X100002H(data2->matrix[i], 14);
				p_PccMatrix[i] = data2->matrix[i];
			}
			pccParams.bOetfGammaEn = data2->bGamma;
			pccParams.bEotfGammaEn = data2->bDeGamma;

			pccParams.u32MuxL3dIn = (UINT32)data2->mux_blend.mux_l3d_in;
			pccParams.u32MuxBlendIn = (UINT32)data2->mux_blend.mux_blend_in;
			pccParams.u32Mux4pLutIn = (UINT32)data2->mux_blend.mux_4p_lut_in;
			pccParams.u32MuxOetfOut = (UINT32)data2->mux_blend.mux_oetf_out;
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
			{
				pccParams.au32B4pLutX[i] = (UINT32)data2->mux_blend.b4p_lut_x[i];
				pccParams.au32B4pLutY[i] = (UINT32)data2->mux_blend.b4p_lut_y[i];
			}
			pccParams.bIsGet = FALSE;

			ret = BE_PQ_HAL_Set_PccParams(&pccParams);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_PccParams error(%d)\n",ret);
				if (data2)
				{
					OS_Free(data2);
				}
				return ret;
			}
		}
		else
		{
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
			{
				pccParam.matrix[i] = (UINT16)_VPQ_BE_CSC_X100002H(data2->matrix[i], 14);
				p_PccMatrix[i] = data2->matrix[i];
			}
			pccParam.bIsGet = FALSE;
			gammaParam.bOetfGammaEn = data2->bGamma;
			gammaParam.bEotfGammaEn = data2->bDeGamma;
			gammaParam.bIsGet = FALSE;
			muxParam.u32MuxL3dIn = (UINT32)data2->mux_blend.mux_l3d_in;
			muxParam.u32MuxBlendIn = (UINT32)data2->mux_blend.mux_blend_in;
			muxParam.u32Mux4pLutIn = (UINT32)data2->mux_blend.mux_4p_lut_in;
			muxParam.u32MuxOetfOut = (UINT32)data2->mux_blend.mux_oetf_out;
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
			{
				muxParam.au32B4pLutX[i] = (UINT32)data2->mux_blend.b4p_lut_x[i];
				muxParam.au32B4pLutY[i] = (UINT32)data2->mux_blend.b4p_lut_y[i];
			}
			muxParam.bIsGet = FALSE;
			ret = BE_PQ_HAL_Set_Pcc(&pccParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Pcc error(%d)\n",ret);
				if (data2)
				{
					OS_Free(data2);
				}
				return ret;
			}
			ret = BE_PQ_HAL_Set_PccGamma(&gammaParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_PccGamma error(%d)\n",ret);
				if (data2)
				{
					OS_Free(data2);
				}
				return ret;
			}
			ret = BE_PQ_HAL_Set_PccMuxBlend(&muxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_PccMuxBlend error(%d)\n",ret);
				if (data2)
				{
					OS_Free(data2);
				}
				return ret;
			}
		}
		ret = PE_CSC_SetLllut(&pccLutParam);
		if (ret)
		{
			PE_PRINT_ERROR("PE_CSC_SetLllut error(%d)\n",ret);
			if (data2)
			{
				OS_Free(data2);
			}
			return ret;
		}
		if (data2)
		{
			OS_Free(data2);
		}
	}
	else if (param->version >= 2)
	{
		v4l2_hwrap_gamut_post *data;
		if (!(data = OS_Malloc(sizeof(v4l2_hwrap_gamut_post))))
		{
			PE_PRINT_ERROR("OS_Malloc error\n");
			if (data)
			{
				OS_Free(data);
			}
			return -ENOMEM;
		}
		if (copy_from_user(data,(void __user *)param->p_data,sizeof(v4l2_hwrap_gamut_post)))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
			if (data)
			{
				OS_Free(data);
			}
			return -EINVAL;
		}

		if (sizeof(data->matrix)/sizeof(data->matrix[0]) 
			!= LX_BE_PQ_NUM_OF_PCC_COEF)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data)
			{
				OS_Free(data);
			}
			return -EINVAL;
		}

		if (sizeof(data->mux_blend.b4p_lut_x)/sizeof(data->mux_blend.b4p_lut_x[0])
			!= LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data)
			{
				OS_Free(data);
			}
			return -EINVAL;
		}

		if (sizeof(data->mux_blend.b4p_lut_y)/sizeof(data->mux_blend.b4p_lut_y[0])
			!= LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA)
		{
			PE_PRINT_ERROR("Invalid array size!\n");
			if (data)
			{
				OS_Free(data);
			}
			return -EINVAL;
		}

		PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, g:%d,d:%d\n",\
			param->version,param->length,param->wid,\
			data->bGamma,data->bDeGamma);
		PE_PRINT_VPQ_BE("m0:0x%x,m1:0x%x,m2:0x%x\n",\
			data->matrix[0],data->matrix[1],data->matrix[2]);
		PE_PRINT_VPQ_BE("m3:0x%x,m4:0x%x,m5:0x%x\n",\
			data->matrix[3],data->matrix[4],data->matrix[5]);
		PE_PRINT_VPQ_BE("m6:0x%x,m7:0x%x,m8:0x%x\n",\
			data->matrix[6],data->matrix[7],data->matrix[8]);
		PE_PRINT_VPQ_BE("mb l3:%d,bl:%d,4p:%d,oe:%d\n",\
			data->mux_blend.mux_l3d_in,data->mux_blend.mux_blend_in,
			data->mux_blend.mux_4p_lut_in,data->mux_blend.mux_oetf_out);
		PE_PRINT_VPQ_BE("x0:0x%x,x1:0x%x,x2:0x%x,x3:0x%x\n",\
			data->mux_blend.b4p_lut_x[0],data->mux_blend.b4p_lut_x[1],
			data->mux_blend.b4p_lut_x[2],data->mux_blend.b4p_lut_x[3]);
		PE_PRINT_VPQ_BE("y0:0x%x,y1:0x%x,y2:0x%x,y3:0x%x\n",\
			data->mux_blend.b4p_lut_y[0],data->mux_blend.b4p_lut_y[1],
			data->mux_blend.b4p_lut_y[2],data->mux_blend.b4p_lut_y[3]);

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0))
		{
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
			{
				pccParams.matrix[i] = (UINT16)_VPQ_BE_CSC_X100002H(data->matrix[i], 14);
				p_PccMatrix[i] = data->matrix[i];
			}
			pccParams.bIsGet = FALSE;
			pccParams.bOetfGammaEn = data->bGamma;
			pccParams.bEotfGammaEn = data->bDeGamma;
			pccParams.bIsGet = FALSE;
			pccParams.u32MuxL3dIn = (UINT32)data->mux_blend.mux_l3d_in;
			pccParams.u32MuxBlendIn = (UINT32)data->mux_blend.mux_blend_in;
			pccParams.u32Mux4pLutIn = (UINT32)data->mux_blend.mux_4p_lut_in;
			pccParams.u32MuxOetfOut = (UINT32)data->mux_blend.mux_oetf_out;
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
			{
				pccParams.au32B4pLutX[i] = (UINT32)data->mux_blend.b4p_lut_x[i];
				pccParams.au32B4pLutY[i] = (UINT32)data->mux_blend.b4p_lut_y[i];
			}
			pccParams.bIsGet = FALSE;

			ret = BE_PQ_HAL_Set_PccParams(&pccParams);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_PccParams error(%d)\n",ret);
				if (data)
				{
					OS_Free(data);
				}
				return ret;
			}
		}
		else
		{
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
			{
				pccParam.matrix[i] = (UINT16)_VPQ_BE_CSC_X100002H(data->matrix[i], 14);
				p_PccMatrix[i] = data->matrix[i];
			}
			pccParam.bIsGet = FALSE;
			gammaParam.bOetfGammaEn = data->bGamma;
			gammaParam.bEotfGammaEn = data->bDeGamma;
			gammaParam.bIsGet = FALSE;

			muxParam.u32MuxL3dIn = (UINT32)data->mux_blend.mux_l3d_in;
			muxParam.u32MuxBlendIn = (UINT32)data->mux_blend.mux_blend_in;
			muxParam.u32Mux4pLutIn = (UINT32)data->mux_blend.mux_4p_lut_in;
			muxParam.u32MuxOetfOut = (UINT32)data->mux_blend.mux_oetf_out;
			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
			{
				muxParam.au32B4pLutX[i] = (UINT32)data->mux_blend.b4p_lut_x[i];
				muxParam.au32B4pLutY[i] = (UINT32)data->mux_blend.b4p_lut_y[i];
			}
			muxParam.bIsGet = FALSE;

			ret = BE_PQ_HAL_Set_Pcc(&pccParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Pcc error(%d)\n",ret);
				if (data)
				{
					OS_Free(data);
				}
				return ret;
			}
			ret = BE_PQ_HAL_Set_PccGamma(&gammaParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_PccGamma error(%d)\n",ret);
				if (data)
				{
					OS_Free(data);
				}
				return ret;
			}
			ret = BE_PQ_HAL_Set_PccMuxBlend(&muxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_PccMuxBlend error(%d)\n",ret);
				if (data)
				{
					OS_Free(data);
				}
				return ret;
			}
		}
		if (data)
		{
			OS_Free(data);
		}
	}
	return ret;
}



#endif
