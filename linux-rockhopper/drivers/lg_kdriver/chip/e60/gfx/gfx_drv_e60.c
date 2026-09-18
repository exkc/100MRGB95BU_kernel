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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		hwanwook.lee
 *  @version	1.0
 *  @date		2017-06-07
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>			/**< printk() */
#include <linux/slab.h>			 	/**< kmalloc() */
#include <linux/fs.h> 				/**< everything\ldots{} */
#include <linux/types.h>		 	/**< size_t */
#include <linux/fcntl.h>			/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>			/**< For request_region, check_region etc */
#include <asm/io.h>					/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "gfx_impl.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void		GFX_E60_stop(void);
extern int 		GFX_E60_RunFlushCommand(void);
extern int 		GFX_E60_RunStartCommand(void);
extern int 		GFX_E60_PauseCommand(void);
extern int		GFX_E60_ResumeCommand(void);
extern int		GFX_E60_StopCommand(void);
extern int		GFX_E60_SwResetCommand(void);
extern void		GFX_E60_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue);
extern BOOLEAN	GFX_E60_IsGfxIdle(void);
extern void		GFX_E60_GetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_E60_SetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_E60_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port);
extern void		GFX_E60_SetInputConfigure(GFX_PORT_CONFIGURE_T *port);
extern void		GFX_E60_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void		GFX_E60_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_E60_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_E60_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_E60_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_E60_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void		GFX_E60_SetInterruptMode(UINT32 uiMode);
extern void		GFX_E60_SetAckMode(UINT32 *mode);
extern void		GFX_E60_GetAckMode(UINT32 *mode);
extern int		GFX_E60_SetCLUT(int port, int size , UINT32 *data);
extern void		GFX_E60_SetCommandDelayReg(UINT16 delay);
extern UINT16 	GFX_E60_GetCommandDelayReg(void);
extern void		GFX_E60_DumpRegister(void);
extern int 		GFX_E60_RunSuspend(void);
extern int 		GFX_E60_RunResume(void);

extern void		GFX_E60_InitScaler(void);

extern int		GFX_E60_RunClkOnCommand(void);
extern int		GFX_E60_RunClkOffCommand(void);
extern BOOLEAN	GFX_E60_ClkCheck(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T*	GFX_E60_GetCfg		(void);
int 				GFX_E60_InitHW		(void);
int 				GFX_E60_ShutdownHW	(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	GFX_HAL_T		g_gfx_hal_e60_dummy =
{
	.GetCfg					= GFX_E60_GetCfg,
	.InitHW					= GFX_E60_InitHW,
	.ShutdownHW				= GFX_E60_ShutdownHW,
	.RunSuspend				= GFX_E60_RunSuspend,
	.RunResume				= GFX_E60_RunResume,

	.RunFlushCommand		= GFX_E60_RunFlushCommand,
	.RunStartCommand		= GFX_E60_RunStartCommand,
	.RunPauseCommand		= GFX_E60_PauseCommand,
	.RunResumeCommand		= GFX_E60_ResumeCommand,
	.RunStopCommand			= GFX_E60_StopCommand,
	.RunSwResetCommand		= GFX_E60_SwResetCommand,

	.GetComQueueStatus		= GFX_E60_GetComQueueStatus,

	.GetOperationStatus		= GFX_E60_GetOperationStatus,
	.SetOperationStatus		= GFX_E60_SetOperationStatus,
	.GetInputConfigure		= GFX_E60_GetInputConfigure,
	.SetInputConfigure		= GFX_E60_SetInputConfigure,
	.GetBlendConfigure		= GFX_E60_GetBlendConfigure,
	.SetBlendConfigure		= GFX_E60_SetBlendConfigure,
	.SetBlendingOut			= GFX_E60_SetBlendingOut,
	.GetOutputConfigure		= GFX_E60_GetOutputConfigure,
	.SetOutputConfigure		= GFX_E60_SetOutputConfigure,
	.SetScalerConfigure		= GFX_E60_SetScalerConfigure,
	.SetCLUT				= GFX_E60_SetCLUT,
	.SetCommandDelayReg		= GFX_E60_SetCommandDelayReg,
	.GetCommandDelayReg		= GFX_E60_GetCommandDelayReg,

	.IsGfxIdle				= GFX_E60_IsGfxIdle,
	.DumpRegister			= GFX_E60_DumpRegister,

	.RunClkOnCommand		= GFX_E60_RunClkOnCommand,
	.RunClkOffCommand		= GFX_E60_RunClkOffCommand,
	.ClkCheck				= GFX_E60_ClkCheck,
};

static	LX_GFX_CFG_T 		g_gfx_cfg_e60_null =
{
    .b_hw_scaler 			= TRUE,
    .surface_blit_cmd_delay = 0x0,
    .screen_blit_cmd_delay  = 0x0,
	.sync_wait_timeout		= 0x0,
	.sync_fail_retry_count	= 0x0,

    .hw_limit = {
        .max_surface_width      = 8191,     /* L9 has 13 bit width field  */
        .max_surface_stride     = 32767,    /* L9 has 15 bit stride field */
        .min_scaler_input_width = 12,       /* L9 doesn't strech below input width <= 12 */
    },
};


/*========================================================================================
    Implementation Group
========================================================================================*/

/** get E60 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_E60_GetCfg(void)
{
    return &g_gfx_cfg_e60_null;
}

void	GFX_E60_InitHAL( GFX_HAL_T*	hal )
{
	memcpy( hal, &g_gfx_hal_e60_dummy, sizeof(GFX_HAL_T));

	g_gfx_cfg_e60_null.workaround.bad_dst_addr_stuck      = 0;
	g_gfx_cfg_e60_null.workaround.scaler_read_buf_stuck   = 0;
	g_gfx_cfg_e60_null.workaround.srcblt_op_stuck         = 0;
	g_gfx_cfg_e60_null.workaround.write_op_stuck          = 0;
}

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/

/** @} */

