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
typedef struct
{
	UINT32	addr_sw_de_sav;
	UINT32	addr_sw_cpu_gpu;
	UINT32	addr_sw_cpu_shadow;
}
GFX_O18_MEM_MAP_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void		GFX_O18_stop(void);
extern int 		GFX_O18_RunFlushCommand(void);
extern int 		GFX_O18_RunStartCommand(void);
extern int 		GFX_O18_PauseCommand(void);
extern int		GFX_O18_ResumeCommand(void);
extern int		GFX_O18_StopCommand(void);
extern int		GFX_O18_SwResetCommand(void);
extern void		GFX_O18_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue);
extern BOOLEAN	GFX_O18_IsGfxIdle(void);
extern void		GFX_O18_GetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_O18_SetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_O18_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port);
extern void		GFX_O18_SetInputConfigure(GFX_PORT_CONFIGURE_T *port);
extern void		GFX_O18_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void		GFX_O18_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_O18_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_O18_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_O18_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_O18_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void		GFX_O18_SetInterruptMode(UINT32 uiMode);
extern void		GFX_O18_SetAckMode(UINT32 *mode);
extern void		GFX_O18_GetAckMode(UINT32 *mode);
extern int		GFX_O18_SetCLUT(int port, int size , UINT32 *data);
extern void		GFX_O18_SetCommandDelayReg(UINT16 delay);
extern UINT16 	GFX_O18_GetCommandDelayReg(void);
extern void		GFX_O18_DumpRegister(void);
extern int 		GFX_O18_RunSuspend(void);
extern int 		GFX_O18_RunResume(void);

extern void		GFX_O18_InitScaler(void);

extern int		GFX_O18_RunClkOnCommand(void);
extern int		GFX_O18_RunClkOffCommand(void);
extern BOOLEAN	GFX_O18_ClkCheck(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T*	GFX_O18_GetCfg		(void);
int 				GFX_O18_InitHW		(void);
int 				GFX_O18_ShutdownHW	(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	GFX_HAL_T		g_gfx_hal_o18_dummy =
{
	.GetCfg					= GFX_O18_GetCfg,
	.InitHW					= GFX_O18_InitHW,
	.ShutdownHW				= GFX_O18_ShutdownHW,
	.RunSuspend				= GFX_O18_RunSuspend,
	.RunResume				= GFX_O18_RunResume,

	.RunFlushCommand		= GFX_O18_RunFlushCommand,
	.RunStartCommand		= GFX_O18_RunStartCommand,
	.RunPauseCommand		= GFX_O18_PauseCommand,
	.RunResumeCommand		= GFX_O18_ResumeCommand,
	.RunStopCommand			= GFX_O18_StopCommand,
	.RunSwResetCommand		= GFX_O18_SwResetCommand,

	.GetComQueueStatus		= GFX_O18_GetComQueueStatus,

	.GetOperationStatus		= GFX_O18_GetOperationStatus,
	.SetOperationStatus		= GFX_O18_SetOperationStatus,
	.GetInputConfigure		= GFX_O18_GetInputConfigure,
	.SetInputConfigure		= GFX_O18_SetInputConfigure,
	.GetBlendConfigure		= GFX_O18_GetBlendConfigure,
	.SetBlendConfigure		= GFX_O18_SetBlendConfigure,
	.SetBlendingOut			= GFX_O18_SetBlendingOut,
	.GetOutputConfigure		= GFX_O18_GetOutputConfigure,
	.SetOutputConfigure		= GFX_O18_SetOutputConfigure,
	.SetScalerConfigure		= GFX_O18_SetScalerConfigure,
	.SetCLUT				= GFX_O18_SetCLUT,
	.SetCommandDelayReg		= GFX_O18_SetCommandDelayReg,
	.GetCommandDelayReg		= GFX_O18_GetCommandDelayReg,

	.IsGfxIdle				= GFX_O18_IsGfxIdle,
	.DumpRegister			= GFX_O18_DumpRegister,

	.RunClkOnCommand		= GFX_O18_RunClkOnCommand,
	.RunClkOffCommand		= GFX_O18_RunClkOffCommand,
	.ClkCheck				= GFX_O18_ClkCheck,
};

static	LX_GFX_CFG_T 		g_gfx_cfg_o18_null =
{
    .b_hw_scaler 			= TRUE,
    .surface_blit_cmd_delay = 0x0,			//0x40,
    .screen_blit_cmd_delay  = 0x0,			//0x20,
	.sync_wait_timeout		= 40,			/* 40 ms */
	.sync_fail_retry_count	= 2,

    .hw_limit = {
        .max_surface_width      = 8191,     /* L9 has 13 bit width field  */
        .max_surface_stride     = 32767,    /* L9 has 15 bit stride field */
        .min_scaler_input_width = 12,       /* L9 doesn't strech below input width <= 12 */
    },
};


/*========================================================================================
    Implementation Group
========================================================================================*/

/** get O18 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_O18_GetCfg(void)
{
    return &g_gfx_cfg_o18_null;
}

void	GFX_O18_InitHAL( GFX_HAL_T*	hal )
{
	memcpy( hal, &g_gfx_hal_o18_dummy, sizeof(GFX_HAL_T));

	g_gfx_cfg_o18_null.workaround.bad_dst_addr_stuck      = 0;
	g_gfx_cfg_o18_null.workaround.scaler_read_buf_stuck   = 0;
	g_gfx_cfg_o18_null.workaround.srcblt_op_stuck         = 0;
	g_gfx_cfg_o18_null.workaround.write_op_stuck          = 0;
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

