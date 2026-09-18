/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *	board specific configuration
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version		1.0
 *  date		2009.11.14
 *
 *  @addtogroup lg1150_base
 * @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "debug_util.h"

#ifdef INCLUDE_KDRV_SYS
#include "sys_drv.h"
#endif

#ifdef INCLUDE_KDRV_DEMOD
#include "demod_drv.h"
#endif

#ifdef INCLUDE_KDRV_AFE
#include "afe_drv.h"
#endif

#ifdef INCLUDE_KDRV_DE
#include "de_drv.h"
#endif
#ifdef INCLUDE_KDRV_PQE
#include "pqe_drv.h"
#endif
#ifdef INCLUDE_KDRV_HDMI
#include "hdmi_drv.h"
#endif
#ifdef INCLUDE_KDRV_HDMI20
#include "hdmi20_drv.h"
#endif
#ifdef INCLUDE_KDRV_DENC
#include "denc_drv.h"
#endif
#ifdef INCLUDE_KDRV_PE
#include "pe_drv.h"
#endif

#ifdef INCLUDE_KDRV_GPIO
#include "gpio_drv.h"
#endif

#ifdef INCLUDE_KDRV_I2C
#include "i2c_drv.h"
#endif /* INCLUDE_KDRV_I2C */

#ifdef INCLUDE_KDRV_TE
#include "te_drv.h"
#endif /* INCLUDE_KDRV_TE */

//remains for legacy backup
#ifdef INCLUDE_KDRV_LEGACY_CI
#include "ci_drv.h"
#endif /* INCLUDE_KDRV_LEGACY_CI */

#ifdef INCLUDE_KDRV_VBI
#include "vbi_drv.h"
#endif /* INCLUDE_KDRV_VBI */

#ifdef INCLUDE_KDRV_OVI
#include "ovi_drv.h"
#endif /* INCLUDE_KDRV_OVI */

#ifdef INCLUDE_KDRV_BE
#include "be_drv.h"
#endif /* INCLUDE_KDRV_BE */

#ifdef INCLUDE_KDRV_PNG
#include "png_drv.h"
#endif /* INCLUDE_KDRV_PNG */

#ifdef INCLUDE_KDRV_MJPEG
#include "mjpeg_drv.h"
#endif /* INCLUDE_KDRV_MJPEG */

#ifdef INCLUDE_KDRV_GPU
#include "gpu_drv.h"
#endif

#ifdef INCLUDE_KDRV_GFX
#include "gfx_drv.h"
#endif
#ifdef INCLUDE_KDRV_FBDEV
#include "fbdev_drv.h"
#endif

#include "afbc_sw_drv.h"

#ifdef INCLUDE_KDRV_SE
#include "se_drv.h"
#endif

#ifdef INCLUDE_KDRV_MONITOR
#include "monitor_drv.h"
#endif

#ifdef INCLUDE_KDRV_APR
#include "apr_drv.h"
#endif

#ifdef INCLUDE_KDRV_MEMPROT
#include "memprot_drv.h"
#endif

#ifdef INCLUDE_KDRV_LGBUS
#include "lgbus_drv.h"
#endif /* INCLUDE_KDRV_LGBUS */

#ifdef INCLUDE_KDRV_SLT
#include "slt_drv.h"
#endif /* INCLUDE_KDRV_SLT */

#ifdef INCLUDE_KDRV_EMMC
#include "emmc_drv.h"
#endif

//// ENABLE_PM_KDRV
#ifdef INCLUDE_KDRV_PM
#include "pm_drv.h"
#endif

#ifdef INCLUDE_KDRV_VIP
#include "vip_drv.h"
#endif


#ifdef INCLUDE_KDRV_SPI
#include "spi_drv.h"
#endif

#ifdef INCLUDE_KDRV_SWCEC
#include "swcec_drv.h"
#endif

#ifdef INCLUDE_KDRV_UCOM
#include "ucom_drv.h"
#endif

#ifdef INCLUDE_KDRV_IRB
#include "irb_drv.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#ifdef INCLUDE_KDRV_PWM
#include "lg1k_pwm_drv.h"
#endif

#include "os_util.h"
#include "base_device.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	void (*CfgModule)(void);
	int	 (*InitModule)(void);
	void (*CleanupModule)(void);
}
LX_DEVICE_INIT_DATA_T;
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static	LX_DEVICE_INIT_DATA_T	g_device_init_table[] =
{
#ifdef KDRV_GLOBAL_LINK

#ifdef INCLUDE_KDRV_PQE_PM
	{ pqe_pm_preinit,	pqe_pm_initialize,	pqe_pm_cleanup },
#endif
#ifdef INCLUDE_KDRV_SYS
	{ SYS_PreInit,		SYS_Init,		SYS_Cleanup },
#endif
#ifdef INCLUDE_KDRV_LGBUS
	{ LGBUS_PreInit,	LGBUS_Init,		LGBUS_Cleanup },
#endif
#ifdef INCLUDE_KDRV_SLT
	{ SLT_PreInit,		SLT_Init,		SLT_Cleanup },
#endif
#ifdef INCLUDE_KDRV_GPIO
	{ GPIO_PreInit,		GPIO_Init,		GPIO_Cleanup },
#endif
#ifdef INCLUDE_KDRV_I2C
	{ I2C_PreInit,		I2C_Init,		I2C_Cleanup },
#endif
#ifdef INCLUDE_KDRV_DE
	{ DE_MEM_PreInit,	DE_MEM_Init,	DE_MEM_Cleanup },
#endif
#ifdef INCLUDE_KDRV_OVI
	{ OVI_PreInit,		OVI_Init,		OVI_Cleanup },
#endif
#ifdef INCLUDE_KDRV_GFX
	{ GFX_PreInit,		GFX_Init,		GFX_Cleanup },
#endif
#ifdef INCLUDE_KDRV_DEMOD
	{ DEMOD_PreInit,	DEMOD_Init,		DEMOD_Cleanup },
#endif
#ifdef INCLUDE_KDRV_UCOM
	{ UCOM_PreInit,		UCOM_Init,		UCOM_Cleanup },
#endif
#ifdef INCLUDE_KDRV_TE
	{ TE_PreInit,		TE_Init,		TE_Cleanup },
#endif
#ifdef INCLUDE_KDRV_HDMI
	{ HDMI_PreInit,		HDMI_Init,		HDMI_Cleanup },
#endif
#ifdef INCLUDE_KDRV_HDMI20
	{ HDMI20_PreInit,		HDMI20_Init,	HDMI20_Cleanup },
#endif
#ifdef INCLUDE_KDRV_AFE
	{ AFE_PreInit,		AFE_Init,		AFE_Cleanup },
#endif
#ifdef INCLUDE_KDRV_DE
	{ DE_PreInit,		DE_Init,		DE_Cleanup },
#endif
#ifdef INCLUDE_KDRV_PQE
	{ PQE_PreInit,		PQE_Init,		PQE_Cleanup },
#endif
#ifdef INCLUDE_KDRV_DENC
	{ DENC_PreInit,		DENC_Init,		DENC_Cleanup },
#endif
#ifdef INCLUDE_KDRV_PE
	{ PE_PreInit,		PE_Init,		PE_Cleanup },
#endif
#ifdef INCLUDE_KDRV_LEGACY_CI
	{ CI_PreInit,		CI_Init,		CI_Cleanup },
#endif
#ifdef INCLUDE_KDRV_VBI
	{ VBI_PreInit,		VBI_Init,		VBI_Cleanup },
#endif
#ifdef INCLUDE_KDRV_BE
	{ BE_PreInit,		BE_Init,		BE_Cleanup },
#endif
#ifdef INCLUDE_KDRV_EMMC
        { EMMC_PreInit,         EMMC_Init,              EMMC_Cleanup },
#endif
#ifdef INCLUDE_KDRV_PM
	{ PM_PreInit,		PM_Init,		PM_Cleanup },
#endif
#ifdef INCLUDE_KDRV_PNG
	{ PNG_PreInit,		PNG_Init,		PNG_Cleanup },
#endif
#ifdef INCLUDE_KDRV_MJPEG
	{ MJPEG_PreInit,	MJPEG_Init,		MJPEG_Cleanup },
#endif
#ifdef INCLUDE_KDRV_GPU
	{ GPU_PreInit,		GPU_Init,		GPU_Cleanup },
#endif
#ifdef INCLUDE_KDRV_SE
//SE is separted from built-in kdriver
#ifndef MAKE_SE_MODULE
	{ SE_PreInit,		SE_Init,		SE_Cleanup },
#endif
#endif
#ifdef INCLUDE_KDRV_MONITOR
	{ MONITOR_PreInit,	MONITOR_Init,	MONITOR_Cleanup },
#endif
#ifdef INCLUDE_KDRV_APR
	{ APR_PreInit,		APR_Init,		APR_Cleanup },
#endif
#ifdef INCLUDE_KDRV_MEMPROT
	{ MEMPROT_PreInit, 	MEMPROT_Init,		MEMPROT_Cleanup },
#endif
#ifdef INCLUDE_KDRV_VIP
	{ VIP_PreInit,		VIP_Init,		VIP_Cleanup },
#endif

// afbc_sw is non-HW kdriver, so enabled always
	{ afbc_sw_preinit,	afbc_sw_init,	afbc_sw_cleanup },

#ifdef INCLUDE_KDRV_FBDEV
	{ FBDEV_PreInit,	FBDEV_Init,		FBDEV_Cleanup },
#endif

#ifdef INCLUDE_KDRV_SPI
	{ SPI_PreInit,		SPI_Init,		SPI_Cleanup },
#endif

#ifdef INCLUDE_KDRV_SWCEC
	{ SWCEC_PreInit,		SWCEC_Init,		SWCEC_Cleanup },
#endif

#ifdef INCLUDE_KDRV_IRB
	{ IRB_PreInit,		IRB_Init,		IRB_Cleanup },
#endif

#ifdef INCLUDE_KDRV_PWM
	{ lg1k_pwm_preinit, lg1k_pwm_init,	lg1k_pwm_cleanup },
#endif

#endif
	{ NULL,	NULL },
};

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void		BASE_DEV_PreInit	( void )
{
	int		i;
	int		num_devices = NELEMENTS(g_device_init_table);

	for ( i=0; i< num_devices; i++ )
	{
		if ( g_device_init_table[i].CfgModule) g_device_init_table[i].CfgModule();
	}
}

void		BASE_DEV_Init	( void )
{
	int		i;
	int		num_devices = NELEMENTS(g_device_init_table);

	for ( i=0; i< num_devices; i++ )
	{
		if ( g_device_init_table[i].InitModule ) g_device_init_table[i].InitModule();
	}
}

void		BASE_DEV_Cleanup	( void )
{
	int		i;
	int		num_devices = NELEMENTS(g_device_init_table);

	for ( i=0; i< num_devices; i++ )
	{
		if ( g_device_init_table[i].CleanupModule ) g_device_init_table[i].CleanupModule();
	}
}

/*========================================================================================
	Implementation Group
========================================================================================*/

/** @} */

