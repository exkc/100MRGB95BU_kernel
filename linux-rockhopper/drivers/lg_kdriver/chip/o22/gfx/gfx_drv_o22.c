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
 *  @author     hwanwook.lee
 *  @version    1.0
 *  @date       2017-06-07
 *  @note       Additional information.
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>           /**< printk() */
#include <linux/slab.h>             /**< kmalloc() */
#include <linux/fs.h>               /**< everything\ldots{} */
#include <linux/types.h>            /**< size_t */
#include <linux/fcntl.h>            /**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>           /**< For request_region, check_region etc */
#include <asm/io.h>                 /**< For ioremap_nocache */
#include <linux/workqueue.h>        /**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "gfx_impl.h"
#include "gfx_reg_o22.h"

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
    UINT32  addr_sw_de_sav;
    UINT32  addr_sw_cpu_gpu;
    UINT32  addr_sw_cpu_shadow;
}
GFX_O22_MEM_MAP_T;

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void     GFX_O22_stop(void);
extern int      GFX_O22_RunFlushCommand(void);
extern int      GFX_O22_RunStartCommand(void);
extern int      GFX_O22_PauseCommand(void);
extern int      GFX_O22_ResumeCommand(void);
extern int      GFX_O22_StopCommand(void);
extern int      GFX_O22_SwResetCommand(void);
extern void     GFX_O22_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T* queue);
extern BOOLEAN  GFX_O22_IsGfxIdle(void);
extern void     GFX_O22_GetOperationStatus(GFX_CMD_OP_T* operate);
extern void     GFX_O22_SetOperationStatus(GFX_CMD_OP_T* operate);
extern void     GFX_O22_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T* port);
extern void     GFX_O22_SetInputConfigure(GFX_PORT_CONFIGURE_T* port);
extern void     GFX_O22_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void     GFX_O22_GetBlendConfigure(GFX_BLEND_CONFIGURE_T* blend);
extern void     GFX_O22_SetBlendConfigure(GFX_BLEND_CONFIGURE_T* blend);
extern void     GFX_O22_GetOutputConfigure(GFX_OUT_CONFIGURE_T* port);
extern void     GFX_O22_SetOutputConfigure(GFX_OUT_CONFIGURE_T* port);
extern void     GFX_O22_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void     GFX_O22_SetInterruptMode(UINT32 uiMode);
extern void     GFX_O22_SetAckMode(UINT32* mode);
extern void     GFX_O22_GetAckMode(UINT32* mode);
extern int      GFX_O22_SetCLUT(int port, int size, UINT32* data);
extern void     GFX_O22_SetCommandDelayReg(UINT16 delay);
extern UINT16   GFX_O22_GetCommandDelayReg(void);
extern void     GFX_O22_DumpRegister(void);
extern int      GFX_O22_RunSuspend(void);
extern int      GFX_O22_RunResume(void);

extern void     GFX_O22_InitScaler(void);

extern BOOLEAN  GFX_O22_ClkCheck(void);
extern int      GFX_O22_RunClkOnCommand(void);
extern int      GFX_O22_RunClkOffCommand(void);

void GFX_O22_InitHAL(GFX_HAL_T*  hal);
int  GFX_O22_InitHW(void);
int  GFX_O22_ShutdownHW(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
volatile GFX_O22_REG_T* g_gfx_reg_o22 = NULL;
GFX_O22_REG_T*          g_gfx_reg_o22_cache = NULL;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T* GFX_O22_GetCfg(void);
int                 GFX_O22_InitHW(void);
int                 GFX_O22_ShutdownHW(void);
irqreturn_t         GFX_O22_ISRHandler(int irq, void* dev_id);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static const GFX_HAL_T g_gfx_hal_o22 =
{
    .GetCfg                 = GFX_O22_GetCfg,
    .InitHW                 = GFX_O22_InitHW,
    .ShutdownHW             = GFX_O22_ShutdownHW,
    .RunSuspend             = GFX_O22_RunSuspend,
    .RunResume              = GFX_O22_RunResume,

    .RunFlushCommand        = GFX_O22_RunFlushCommand,
    .RunStartCommand        = GFX_O22_RunStartCommand,
    .RunPauseCommand        = GFX_O22_PauseCommand,
    .RunResumeCommand       = GFX_O22_ResumeCommand,
    .RunStopCommand         = GFX_O22_StopCommand,
    .RunSwResetCommand      = GFX_O22_SwResetCommand,

    .GetComQueueStatus      = GFX_O22_GetComQueueStatus,

    .GetOperationStatus     = GFX_O22_GetOperationStatus,
    .SetOperationStatus     = GFX_O22_SetOperationStatus,
    .GetInputConfigure      = GFX_O22_GetInputConfigure,
    .SetInputConfigure      = GFX_O22_SetInputConfigure,
    .GetBlendConfigure      = GFX_O22_GetBlendConfigure,
    .SetBlendConfigure      = GFX_O22_SetBlendConfigure,
    .SetBlendingOut         = GFX_O22_SetBlendingOut,
    .GetOutputConfigure     = GFX_O22_GetOutputConfigure,
    .SetOutputConfigure     = GFX_O22_SetOutputConfigure,
    .SetScalerConfigure     = GFX_O22_SetScalerConfigure,
    .SetCLUT                = GFX_O22_SetCLUT,
    .SetCommandDelayReg     = GFX_O22_SetCommandDelayReg,
    .GetCommandDelayReg     = GFX_O22_GetCommandDelayReg,

    .IsGfxIdle              = GFX_O22_IsGfxIdle,

    .DumpRegister           = GFX_O22_DumpRegister,

    .RunClkOnCommand        = GFX_O22_RunClkOnCommand,
    .RunClkOffCommand       = GFX_O22_RunClkOffCommand,
    .ClkCheck               = GFX_O22_ClkCheck,
};

static  LX_GFX_CFG_T        g_gfx_cfg_o22 =
{
    .b_hw_scaler            = TRUE,
    .surface_blit_cmd_delay = 0xffff,       // normal gfx operation by APP.
    .screen_blit_cmd_delay  = 0xffff,       // internal gfx operation by KDRV.
#if CONFIG_LX_BOARD_FPGA
    .sync_wait_timeout      = 4000,         /* 4 sec for FPGA */
#else
    .sync_wait_timeout      = 500,          /* 500 ms. 튜닝 필요 */
#endif
    .sync_fail_retry_count  = 2,

    .hw_limit = {
        .max_surface_width      = 8191,     /* L9 has 13 bit width field  */
        .max_surface_stride     = 32767,    /* L9 has 15 bit stride field */
        .min_scaler_input_width = 12,       /* L9 doesn't strech below input width <= 12 */
    },
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get O22 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_O22_GetCfg(void)
{
    return &g_gfx_cfg_o22;
}

void    GFX_O22_InitHAL(GFX_HAL_T*  hal)
{
    memcpy(hal, &g_gfx_hal_o22, sizeof(GFX_HAL_T));

    switch (lx_chip_rev())
    {
        case LX_CHIP_REV(O22, A0):
        {
            g_gfx_cfg_o22.workaround.bad_dst_addr_stuck      = 0;
            g_gfx_cfg_o22.workaround.scaler_read_buf_stuck   = 0;
            g_gfx_cfg_o22.workaround.srcblt_op_stuck         = 0;
            g_gfx_cfg_o22.workaround.write_op_stuck          = 0;
        }
        break;

        default:
        {
            g_gfx_cfg_o22.workaround.bad_dst_addr_stuck      = 0;
            g_gfx_cfg_o22.workaround.scaler_read_buf_stuck   = 0;
            g_gfx_cfg_o22.workaround.srcblt_op_stuck         = 0;
            g_gfx_cfg_o22.workaround.write_op_stuck          = 0;
        }
        break;
    }
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

/** GFX interrupt handler
 *
 */
irqreturn_t GFX_O22_ISRHandler(int irq, void* dev_id)
{
    //  if ( GFX_IsGfxIdle() )
    {
        //      GFX_PRINT("#### GFX ISR - IDLE OK ####\n");
        GFX_WakeupWaitSync();
    }

    g_gfx_reg_o22->gfx_intr_clear.intr_clear = 0x1;
    GFX_PRINT("#### GFX ISR ####\n");

    return IRQ_HANDLED;
}

/** initialize O22 hardware
*
* @return RET_OK when success, RET_ERROR otherwise
*/

int GFX_O22_InitHW(void)
{
    static BOOLEAN b_os_init = FALSE;

    /* do ioremap */
    if (NULL == g_gfx_reg_o22)
    {
        g_gfx_reg_o22 = (GFX_O22_REG_T*)ioremap(gpGfxRegCfg->reg_base_addr, gpGfxRegCfg->reg_size);
        GFX_CHECK_ERROR(NULL == g_gfx_reg_o22, return RET_ERROR, "out of memory. can't ioremap\n");
    }

    if (NULL == g_gfx_reg_o22_cache)
    {
        g_gfx_reg_o22_cache = (GFX_O22_REG_T*)OS_Malloc(gpGfxRegCfg->reg_size);
        GFX_CHECK_ERROR(g_gfx_reg_o22_cache == NULL, return RET_ERROR, "out of memory\n");

        memset(g_gfx_reg_o22_cache, 0x0, gpGfxRegCfg->reg_size);
    }

    if (b_os_init == FALSE)
    {
        /* register GFX interrupt handler */
        GFX_CHECK_ERROR(request_irq(gpGfxRegCfg->irq_num, (irq_handler_t)GFX_O22_ISRHandler, 0, "gfx_irq", NULL), /* nop */,
                        "request_irq failed\n");

        b_os_init = TRUE;
    }

    /* Reset GFX H/W */
    GFX_O22_SwResetCommand();

    g_gfx_reg_o22->gfx_intr_ctrl.intr_gen_mode = 0; // batch command finish
    g_gfx_reg_o22->gfx_intr_ctrl.intr_en = 1;       // interrupt enable

    GFX_O22_InitScaler();
    return 0;
}

/** shutdown O22 hardware
 *
 * @return RET_OK when success, RET_ERROR otherwise
 */
int             GFX_O22_ShutdownHW(void)
{
    g_gfx_reg_o22->gfx_intr_ctrl.intr_en = 0;   // interrupt disable

    /* [TODO] more cleanup !!! */
    if (g_gfx_reg_o22)
    {
        iounmap((void*)g_gfx_reg_o22);
        g_gfx_reg_o22 = NULL;
    }

    if (g_gfx_reg_o22_cache)
    {
        OS_Free(g_gfx_reg_o22_cache);
        g_gfx_reg_o22_cache = NULL;
    }

    return 0;
}

/** @} */

