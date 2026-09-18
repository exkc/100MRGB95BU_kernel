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
 *  @author		raxis.lim
 *  @version	1.0
 *  @date		2011-04-03
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
GFX_M19_MEM_MAP_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void		GFX_M19_stop(void);
extern int 		GFX_M19_RunFlushCommand(void);
extern int 		GFX_M19_RunStartCommand(void);
extern int 		GFX_M19_PauseCommand(void);
extern int		GFX_M19_ResumeCommand(void);
extern int		GFX_M19_StopCommand(void);
extern int		GFX_M19_SwResetCommand(void);
extern void		GFX_M19_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue);
extern BOOLEAN	GFX_M19_IsGfxIdle(void);
extern void		GFX_M19_GetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_M19_SetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_M19_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port);
extern void		GFX_M19_SetInputConfigure(GFX_PORT_CONFIGURE_T *port);
extern void		GFX_M19_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void		GFX_M19_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_M19_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_M19_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_M19_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_M19_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void		GFX_M19_SetInterruptMode(UINT32 uiMode);
extern void		GFX_M19_SetAckMode(UINT32 *mode);
extern void		GFX_M19_GetAckMode(UINT32 *mode);
extern int		GFX_M19_SetCLUT(int port, int size , UINT32 *data);
extern void		GFX_M19_SetCommandDelayReg(UINT16 delay);
extern UINT16 	GFX_M19_GetCommandDelayReg(void);
extern void		GFX_M19_DumpRegister(void);
extern int 		GFX_M19_RunSuspend(void);
extern int 		GFX_M19_RunResume(void);

extern void		GFX_M19_InitScaler(void);

extern int		GFX_M19_RunClkOnCommand(void);
extern int		GFX_M19_RunClkOffCommand(void);
extern BOOLEAN	GFX_M19_ClkCheck(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T*	GFX_M19_GetCfg		(void);
int 				GFX_M19_InitHW		(void);
int 				GFX_M19_ShutdownHW	(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	GFX_HAL_T		g_gfx_hal_m19 =
{
	.GetCfg					= GFX_M19_GetCfg,
	.InitHW					= GFX_M19_InitHW,
	.ShutdownHW				= GFX_M19_ShutdownHW,
	.RunSuspend				= GFX_M19_RunSuspend,
	.RunResume				= GFX_M19_RunResume,

	.RunFlushCommand		= GFX_M19_RunFlushCommand,
	.RunStartCommand		= GFX_M19_RunStartCommand,
	.RunPauseCommand		= GFX_M19_PauseCommand,
	.RunResumeCommand		= GFX_M19_ResumeCommand,
	.RunStopCommand			= GFX_M19_StopCommand,
	.RunSwResetCommand		= GFX_M19_SwResetCommand,

	.GetComQueueStatus		= GFX_M19_GetComQueueStatus,

	.GetOperationStatus		= GFX_M19_GetOperationStatus,
	.SetOperationStatus		= GFX_M19_SetOperationStatus,
	.GetInputConfigure		= GFX_M19_GetInputConfigure,
	.SetInputConfigure		= GFX_M19_SetInputConfigure,
	.GetBlendConfigure		= GFX_M19_GetBlendConfigure,
	.SetBlendConfigure		= GFX_M19_SetBlendConfigure,
	.SetBlendingOut			= GFX_M19_SetBlendingOut,
	.GetOutputConfigure		= GFX_M19_GetOutputConfigure,
	.SetOutputConfigure		= GFX_M19_SetOutputConfigure,
	.SetScalerConfigure		= GFX_M19_SetScalerConfigure,
	.SetCLUT				= GFX_M19_SetCLUT,
	.SetCommandDelayReg		= GFX_M19_SetCommandDelayReg,
	.GetCommandDelayReg		= GFX_M19_GetCommandDelayReg,

	.IsGfxIdle				= GFX_M19_IsGfxIdle,
	.DumpRegister			= GFX_M19_DumpRegister,

	.RunClkOnCommand		= GFX_M19_RunClkOnCommand,
	.RunClkOffCommand		= GFX_M19_RunClkOffCommand,
	.ClkCheck				= GFX_M19_ClkCheck,
};

static	LX_GFX_CFG_T 		g_gfx_cfg_m19 =
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

/** get M19 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_M19_GetCfg(void)
{
    return &g_gfx_cfg_m19;
}

void	GFX_M19_InitHAL( GFX_HAL_T*	hal )
{
	memcpy( hal, &g_gfx_hal_m19, sizeof(GFX_HAL_T));

	g_gfx_cfg_m19.workaround.bad_dst_addr_stuck      = 0;
	g_gfx_cfg_m19.workaround.scaler_read_buf_stuck   = 0;
	g_gfx_cfg_m19.workaround.srcblt_op_stuck         = 0;
	g_gfx_cfg_m19.workaround.write_op_stuck          = 0;
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

