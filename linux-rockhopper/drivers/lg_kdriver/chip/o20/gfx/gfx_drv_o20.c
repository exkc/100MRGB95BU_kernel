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
extern void		GFX_O20_stop(void);
extern int 		GFX_O20_RunFlushCommand(void);
extern int 		GFX_O20_RunStartCommand(void);
extern int 		GFX_O20_PauseCommand(void);
extern int		GFX_O20_ResumeCommand(void);
extern int		GFX_O20_StopCommand(void);
extern int		GFX_O20_SwResetCommand(void);
extern void		GFX_O20_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue);
extern BOOLEAN	GFX_O20_IsGfxIdle(void);
extern void		GFX_O20_GetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_O20_SetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_O20_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port);
extern void		GFX_O20_SetInputConfigure(GFX_PORT_CONFIGURE_T *port);
extern void		GFX_O20_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void		GFX_O20_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_O20_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_O20_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_O20_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_O20_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void		GFX_O20_SetInterruptMode(UINT32 uiMode);
extern void		GFX_O20_SetAckMode(UINT32 *mode);
extern void		GFX_O20_GetAckMode(UINT32 *mode);
extern int		GFX_O20_SetCLUT(int port, int size , UINT32 *data);
extern void		GFX_O20_SetCommandDelayReg(UINT16 delay);
extern UINT16 	GFX_O20_GetCommandDelayReg(void);
extern void		GFX_O20_DumpRegister(void);
extern int 		GFX_O20_RunSuspend(void);
extern int 		GFX_O20_RunResume(void);

extern void		GFX_O20_InitScaler(void);

extern int		GFX_O20_RunClkOnCommand(void);
extern int		GFX_O20_RunClkOffCommand(void);
extern BOOLEAN	GFX_O20_ClkCheck(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T*	GFX_O20_GetCfg		(void);
int 				GFX_O20_InitHW		(void);
int 				GFX_O20_ShutdownHW	(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	GFX_HAL_T		g_gfx_hal_o20_dummy =
{
	.GetCfg					= GFX_O20_GetCfg,
	.InitHW					= GFX_O20_InitHW,
	.ShutdownHW				= GFX_O20_ShutdownHW,
	.RunSuspend				= GFX_O20_RunSuspend,
	.RunResume				= GFX_O20_RunResume,

	.RunFlushCommand		= GFX_O20_RunFlushCommand,
	.RunStartCommand		= GFX_O20_RunStartCommand,
	.RunPauseCommand		= GFX_O20_PauseCommand,
	.RunResumeCommand		= GFX_O20_ResumeCommand,
	.RunStopCommand			= GFX_O20_StopCommand,
	.RunSwResetCommand		= GFX_O20_SwResetCommand,

	.GetComQueueStatus		= GFX_O20_GetComQueueStatus,

	.GetOperationStatus		= GFX_O20_GetOperationStatus,
	.SetOperationStatus		= GFX_O20_SetOperationStatus,
	.GetInputConfigure		= GFX_O20_GetInputConfigure,
	.SetInputConfigure		= GFX_O20_SetInputConfigure,
	.GetBlendConfigure		= GFX_O20_GetBlendConfigure,
	.SetBlendConfigure		= GFX_O20_SetBlendConfigure,
	.SetBlendingOut			= GFX_O20_SetBlendingOut,
	.GetOutputConfigure		= GFX_O20_GetOutputConfigure,
	.SetOutputConfigure		= GFX_O20_SetOutputConfigure,
	.SetScalerConfigure		= GFX_O20_SetScalerConfigure,
	.SetCLUT				= GFX_O20_SetCLUT,
	.SetCommandDelayReg		= GFX_O20_SetCommandDelayReg,
	.GetCommandDelayReg		= GFX_O20_GetCommandDelayReg,

	.IsGfxIdle				= GFX_O20_IsGfxIdle,
	.DumpRegister			= GFX_O20_DumpRegister,

	.RunClkOnCommand		= GFX_O20_RunClkOnCommand,
	.RunClkOffCommand		= GFX_O20_RunClkOffCommand,
	.ClkCheck				= GFX_O20_ClkCheck,
};

static	LX_GFX_CFG_T 		g_gfx_cfg_o20_null =
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

/** get O20 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_O20_GetCfg(void)
{
    return &g_gfx_cfg_o20_null;
}

void	GFX_O20_InitHAL( GFX_HAL_T*	hal )
{
	memcpy( hal, &g_gfx_hal_o20_dummy, sizeof(GFX_HAL_T));

	g_gfx_cfg_o20_null.workaround.bad_dst_addr_stuck      = 0;
	g_gfx_cfg_o20_null.workaround.scaler_read_buf_stuck   = 0;
	g_gfx_cfg_o20_null.workaround.srcblt_op_stuck         = 0;
	g_gfx_cfg_o20_null.workaround.write_op_stuck          = 0;
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

