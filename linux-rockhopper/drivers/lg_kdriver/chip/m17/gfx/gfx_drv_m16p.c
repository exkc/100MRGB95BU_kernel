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
GFX_M16P_MEM_MAP_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void		GFX_M16P_stop(void);
extern int 		GFX_M16P_RunFlushCommand(void);
extern int 		GFX_M16P_RunStartCommand(void);
extern int 		GFX_M16P_PauseCommand(void);
extern int		GFX_M16P_ResumeCommand(void);
extern int		GFX_M16P_StopCommand(void);
extern int		GFX_M16P_SwResetCommand(void);
extern void		GFX_M16P_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue);
extern BOOLEAN	GFX_M16P_IsGfxIdle(void);
extern void		GFX_M16P_GetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_M16P_SetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_M16P_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port);
extern void		GFX_M16P_SetInputConfigure(GFX_PORT_CONFIGURE_T *port);
extern void		GFX_M16P_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void		GFX_M16P_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_M16P_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_M16P_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_M16P_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_M16P_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void		GFX_M16P_SetInterruptMode(UINT32 uiMode);
extern void		GFX_M16P_SetAckMode(UINT32 *mode);
extern void		GFX_M16P_GetAckMode(UINT32 *mode);
extern int		GFX_M16P_SetCLUT(int port, int size , UINT32 *data);
extern void		GFX_M16P_SetCommandDelayReg(UINT16 delay);
extern UINT16 	GFX_M16P_GetCommandDelayReg(void);
extern void		GFX_M16P_DumpRegister(void);
extern int 		GFX_M16P_RunSuspend(void);
extern int 		GFX_M16P_RunResume(void);

extern void		GFX_M16P_InitScaler(void);

extern int		GFX_M16P_RunClkOnCommand(void);
extern int		GFX_M16P_RunClkOffCommand(void);
extern BOOLEAN	GFX_M16P_ClkCheck(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T*	GFX_M16P_GetCfg		(void);
int 				GFX_M16P_InitHW		(void);
int 				GFX_M16P_ShutdownHW	(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	GFX_HAL_T		g_gfx_hal_m16 =
{
	.GetCfg					= GFX_M16P_GetCfg,
	.InitHW					= GFX_M16P_InitHW,
	.ShutdownHW				= GFX_M16P_ShutdownHW,
	.RunSuspend				= GFX_M16P_RunSuspend,
	.RunResume				= GFX_M16P_RunResume,

	.RunFlushCommand		= GFX_M16P_RunFlushCommand,
	.RunStartCommand		= GFX_M16P_RunStartCommand,
	.RunPauseCommand		= GFX_M16P_PauseCommand,
	.RunResumeCommand		= GFX_M16P_ResumeCommand,
	.RunStopCommand			= GFX_M16P_StopCommand,
	.RunSwResetCommand		= GFX_M16P_SwResetCommand,

	.GetComQueueStatus		= GFX_M16P_GetComQueueStatus,

	.GetOperationStatus		= GFX_M16P_GetOperationStatus,
	.SetOperationStatus		= GFX_M16P_SetOperationStatus,
	.GetInputConfigure		= GFX_M16P_GetInputConfigure,
	.SetInputConfigure		= GFX_M16P_SetInputConfigure,
	.GetBlendConfigure		= GFX_M16P_GetBlendConfigure,
	.SetBlendConfigure		= GFX_M16P_SetBlendConfigure,
	.SetBlendingOut			= GFX_M16P_SetBlendingOut,
	.GetOutputConfigure		= GFX_M16P_GetOutputConfigure,
	.SetOutputConfigure		= GFX_M16P_SetOutputConfigure,
	.SetScalerConfigure		= GFX_M16P_SetScalerConfigure,
	.SetCLUT				= GFX_M16P_SetCLUT,
	.SetCommandDelayReg		= GFX_M16P_SetCommandDelayReg,
	.GetCommandDelayReg		= GFX_M16P_GetCommandDelayReg,

	.IsGfxIdle				= GFX_M16P_IsGfxIdle,
	.DumpRegister			= GFX_M16P_DumpRegister,

	.RunClkOnCommand		= GFX_M16P_RunClkOnCommand,
	.RunClkOffCommand		= GFX_M16P_RunClkOffCommand,
	.ClkCheck				= GFX_M16P_ClkCheck,
};

static	LX_GFX_CFG_T 		g_gfx_cfg_m16 =
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

/** get M16P specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_M16P_GetCfg(void)
{
    return &g_gfx_cfg_m16;
}

void	GFX_M16P_InitHAL( GFX_HAL_T*	hal )
{
	memcpy( hal, &g_gfx_hal_m16, sizeof(GFX_HAL_T));

	g_gfx_cfg_m16.workaround.bad_dst_addr_stuck      = 0;
	g_gfx_cfg_m16.workaround.scaler_read_buf_stuck   = 0;
	g_gfx_cfg_m16.workaround.srcblt_op_stuck         = 0;
	g_gfx_cfg_m16.workaround.write_op_stuck          = 0;
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

