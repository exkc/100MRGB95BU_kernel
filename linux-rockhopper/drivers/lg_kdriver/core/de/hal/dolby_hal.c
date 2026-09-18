/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  manjunath.goudar (manjunath.goudar@lge.com)
 * version	  1.0
 * date		  2016.03.29
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------
 *	 Control Constants
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 File Inclusions
 *--------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "base_types.h"
#include "base_device.h"
#include "os_util.h"

#include "de_model.h"
#include "de_kapi.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "de_hal_def.h"
#include "dolby_hal.h"
#ifdef USE_KDRV_CODES_FOR_M17
#include "m17/de/dolby_reg_m17.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M19
#include "m19/de/dolby_reg_m19.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O18
#include "o18/de/dolby_reg_o18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O20
#include "o20/de/dolby_reg_o20.h"
#endif
#ifdef USE_KDRV_CODES_FOR_E60
#include "e60/de/dolby_reg_e60.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O22
#include "o22/de/dolby_reg_o22.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O24
#include "o24/de/dolby_reg_o24.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O26
#include "o26/de/dolby_reg_o26.h"
#endif

/*----------------------------------------------------------------------------
 *	 Constant Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 Macro Definitions
 *--------------------------------------------------------------------------*/
#define CHECK_REG_NULL(fp) {if(fp == NULL || g_chip_id < 0)\
							{DE_ERROR("Error: %s is not supported in this chip %d.\n",#fp,g_chip_id); \
							return RET_ERROR;}}
#define GET_ID() g_chip_id

/*----------------------------------------------------------------------------
 *	 Type Definitions
 *--------------------------------------------------------------------------*/
typedef struct {
	int (*dhdr_ip_init)(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit);
	int	(*dhdr_ip_getirqstatus)(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrHdrIrqStatus,int i_unFlag);
	int (*dhdr_ip_setirqstatus)(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *i_PtrIrqStatus,int i_unFlag);
	int (*dhdr_ip_gethdmimetadata)(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_PtrMetaData);
	int (*dhdr_ip_getottmetadata)(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_DM_MD_T *o_ptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_sptrFrames,UINT32 *o_sptrProfileId);
	int (*dhdr_ip_setconfig)(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
	int (*dhdr_ip_getconfig)(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig);
	int (*dhdr_ip_setlut)(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum);
	int (*dhdr_ip_start)(DOLBY_DEVICE_DATA_T *i_PtrDolby);
	int (*dhdr_ip_uninit)(DOLBY_DEVICE_DATA_T *o_PtrDolbyUninit);
	int (*dhdr_ip_setmdpath)(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path);
}DE_DHDR_IP_REG_CB_T;

DE_DHDR_IP_REG_CB_T gDolbyfn_all[7];
static int g_chip_id = 0;

/*----------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 External Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 global Functions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 global Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *	 Static Variables
 *--------------------------------------------------------------------------*/

/*============================================================================
 *	 Implementation Group
 *==========================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief select chip for call-back function 
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_Select_Chip(void)
{
#define REG_FN gDolbyfn_all[g_chip_id]

	int ret = RET_OK;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

#ifdef USE_KDRV_CODES_FOR_O18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O18) ) {
		g_chip_id = 3;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_O18_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_O18_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_O18_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_O18_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_O18_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_O18_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_O18_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_O18_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_O18_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_O18_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_O18_SetMdPath;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) ) {
		g_chip_id = 2;
		REG_FN.dhdr_ip_init				= NULL;
		REG_FN.dhdr_ip_getirqstatus		= NULL;
		REG_FN.dhdr_ip_setirqstatus		= NULL;
		REG_FN.dhdr_ip_gethdmimetadata	= NULL;
		REG_FN.dhdr_ip_getottmetadata	= NULL;
		REG_FN.dhdr_ip_setconfig		= NULL;
		REG_FN.dhdr_ip_getconfig		= NULL;
		REG_FN.dhdr_ip_setlut			= NULL;
		REG_FN.dhdr_ip_start			= NULL;
		REG_FN.dhdr_ip_uninit			= NULL;
		REG_FN.dhdr_ip_setmdpath		= NULL;
	} else
#endif

#ifdef USE_KDRV_CODES_FOR_M17
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_SetMdPath;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_M19
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M19) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_M19_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_M19_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_M19_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_M19_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_M19_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_M19_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_M19_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_M19_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_M19_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_M19_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_M19_SetMdPath;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O20
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_O20_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_O20_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_O20_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_O20_GetHDMIMetaData;
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,1)
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_O20_GetOTTMetaData;
#endif
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_O20_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_O20_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_O20_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_O20_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_O20_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_O20_SetMdPath;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_E60
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_E60_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_E60_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_E60_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_E60_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_E60_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_E60_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_E60_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_E60_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_E60_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_E60_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_E60_SetMdPath;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O22
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_O22_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_O22_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_O22_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_O22_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_O22_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_O22_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_O22_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_O22_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_O22_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_O22_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_O22_SetMdPath;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_M23
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
		g_chip_id = 1;
		DE_NOTI("not support\n");
		ret = RET_OK;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O24
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_O24_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_O24_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_O24_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_O24_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_O24_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_O24_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_O24_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_O24_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_O24_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_O24_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_O24_SetMdPath;
		ret = RET_OK;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O26
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) ) {
		g_chip_id = 1;
		REG_FN.dhdr_ip_init				= DE_DHDR_IP_REG_O26_Init;
		REG_FN.dhdr_ip_getirqstatus		= DE_DHDR_IP_REG_O26_GetIrqStatus;
		REG_FN.dhdr_ip_setirqstatus		= DE_DHDR_IP_REG_O26_SetIrqStatus;
		REG_FN.dhdr_ip_gethdmimetadata	= DE_DHDR_IP_REG_O26_GetHDMIMetaData;
		REG_FN.dhdr_ip_getottmetadata	= DE_DHDR_IP_REG_O26_GetOTTMetaData;
		REG_FN.dhdr_ip_setconfig		= DE_DHDR_IP_REG_O26_SetConfig;
		REG_FN.dhdr_ip_getconfig		= DE_DHDR_IP_REG_O26_GetConfig;
		REG_FN.dhdr_ip_setlut			= DE_DHDR_IP_REG_O26_SetLut;
		REG_FN.dhdr_ip_start			= DE_DHDR_IP_REG_O26_Start;
		REG_FN.dhdr_ip_uninit			= DE_DHDR_IP_REG_O26_UnInit;
		REG_FN.dhdr_ip_setmdpath		= DE_DHDR_IP_REG_O26_SetMdPath;
		ret = RET_OK;
	} else
#endif
	{
		g_chip_id = -1;
		DE_ERROR("not defined chip rev.\n");
		ret = RET_ERROR;
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize memory,irq & resource of  Dolby driver for OTT/HDMI mode
 *
 * @param *io_PtrDolbyInit [IN/OUT] takes dolby mode as input & gives 3D,TC & G2L LUT address as output
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_Init(DOLBY_DEVICE_DATA_T *io_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_init);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_init(io_PtrDolbyInit);
	}while(0);
	
	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Reads the IRQ status of HDR/MCU interrupt
 *
 * @param *o_PtrHdrIrqStatus [OUT] to get the IRQ status of HDR,MCU Interrupt Status
 *
 * @param i_unFlag [IN] Flag to decide MCU/HDR
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_GetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *o_PtrHdrIrqStatus,int i_unFlag)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_getirqstatus);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_getirqstatus(i_PtrDolby,o_PtrHdrIrqStatus,i_unFlag);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Gets the HDMI DM MetaData
 *
 * @param *o_PtrMetaData [OUT] HDMI DM MetaData
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_GetHDMIMetaData(DOLBY_DEVICE_DATA_T *i_sptrDolby,LX_DOLBY_DM_MD_T *o_sptrMetaData)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_gethdmimetadata);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_gethdmimetadata(i_sptrDolby,o_sptrMetaData);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Gets the OTT Comp & DM MetaData
 *
 * @param *o_PtrMetaData [OUT] OTT Comp & DM MetaData
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_GetOTTMetaData(DOLBY_DEVICE_DATA_T *i_sptrDolby,LX_DOLBY_DM_OTT_MD_T *o_sptrOTTDMMD,UINT32 *io_nptrFramePTS,UINT32 *io_usptrFrames,UINT32 *o_sptrProfileId)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_getottmetadata);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_getottmetadata(i_sptrDolby,(LX_DOLBY_DM_MD_T *)o_sptrOTTDMMD,io_nptrFramePTS,io_usptrFrames,o_sptrProfileId);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Configures the Composer & DM Dolby HDR IP
 *
 * @param *i_PtrConfig [IN] Composer & DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_SetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_setconfig);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_setconfig(i_PtrDolby,i_PtrConfig);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Get Composer & DM register values from Dolby HDR IP
 *
 * @param *i_PtrConfig [IN] Composer & DM register map values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_GetConfig(DOLBY_DEVICE_DATA_T *i_PtrDolby,LX_DOLBY_CONFIG_REG_T *i_PtrConfig)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_getconfig);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_getconfig(i_PtrDolby,i_PtrConfig);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Configures the 3D,TC & G2L DDR Address to Dolby HDR IP
 *
 * @param *i_PtrFrameNum [IN] Frame Number
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_SetLut(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 i_PtrFrameNum)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_setlut);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_setlut(i_PtrDolby,i_PtrFrameNum);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief PIC start for Dolby HDR IP
 *
 * @param void
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_Start(DOLBY_DEVICE_DATA_T *i_PtrDolby)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_start);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_start(i_PtrDolby);
	}while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Unintialization of dolby driver
 *
 * @param void
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_UnInit(DOLBY_DEVICE_DATA_T *o_PtrDolbyInit)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_uninit);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_uninit(o_PtrDolbyInit);
	}while(0);
	return ret;
}
/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief Set the IRQ status of HDR/MCU interrupt
 *
 * @param *o_PtrHdrIrqStatus [IN] to set the IRQ status of HDR,MCU Interrupt Status
 *
 * @param i_unFlag [IN] Flag to decide MCU/HDR
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_DHDR_IP_HAL_SetIrqStatus(DOLBY_DEVICE_DATA_T *i_PtrDolby,UINT32 *i_PtrIrqStatus,int i_unFlag)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_setirqstatus);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_setirqstatus(i_PtrDolby,i_PtrIrqStatus,i_unFlag);
	}while(0);

	return ret;
}


int DE_DHDR_IP_HAL_SetMDPath(DOLBY_DEVICE_DATA_T *io_PtrDolby,LX_HDR_HDMI_MD_PATH_T e_md_path)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ## %s %d\n",__F__,__L__);

	do {
		CHECK_REG_NULL(gDolbyfn_all[GET_ID()].dhdr_ip_setmdpath);
		ret = gDolbyfn_all[GET_ID()].dhdr_ip_setmdpath(io_PtrDolby,e_md_path);
	}while(0);

	return ret;
}

/**  @} */
