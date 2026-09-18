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
#include "gfx_reg_o24.h"

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
GFX_O24_MEM_MAP_T;

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void     GFX_O24_stop(void);
extern int      GFX_O24_RunFlushCommand(void);
extern int      GFX_O24_RunStartCommand(void);
extern int      GFX_O24_PauseCommand(void);
extern int      GFX_O24_ResumeCommand(void);
extern int      GFX_O24_StopCommand(void);
extern int      GFX_O24_SwResetCommand(void);
extern void     GFX_O24_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T* queue);
extern BOOLEAN  GFX_O24_IsGfxIdle(void);
extern void     GFX_O24_GetOperationStatus(GFX_CMD_OP_T* operate);
extern void     GFX_O24_SetOperationStatus(GFX_CMD_OP_T* operate);
extern void     GFX_O24_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T* port);
extern void     GFX_O24_SetInputConfigure(GFX_PORT_CONFIGURE_T* port);
extern void     GFX_O24_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void     GFX_O24_GetBlendConfigure(GFX_BLEND_CONFIGURE_T* blend);
extern void     GFX_O24_SetBlendConfigure(GFX_BLEND_CONFIGURE_T* blend);
extern void     GFX_O24_GetOutputConfigure(GFX_OUT_CONFIGURE_T* port);
extern void     GFX_O24_SetOutputConfigure(GFX_OUT_CONFIGURE_T* port);
extern void     GFX_O24_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void     GFX_O24_SetInterruptMode(UINT32 uiMode);
extern void     GFX_O24_SetAckMode(UINT32* mode);
extern void     GFX_O24_GetAckMode(UINT32* mode);
extern int      GFX_O24_SetCLUT(int port, int size, UINT32* data);
extern void     GFX_O24_SetCommandDelayReg(UINT16 delay);
extern UINT16   GFX_O24_GetCommandDelayReg(void);
extern void     GFX_O24_DumpRegister(void);
extern int      GFX_O24_RunSuspend(void);
extern int      GFX_O24_RunResume(void);

extern void     GFX_O24_InitScaler(void);

extern BOOLEAN  GFX_O24_ClkCheck(void);
extern int      GFX_O24_RunClkOnCommand(void);
extern int      GFX_O24_RunClkOffCommand(void);

void GFX_O24_InitHAL(GFX_HAL_T*  hal);
int  GFX_O24_InitHW(void);
int  GFX_O24_ShutdownHW(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
volatile GFX_O24_REG_T* g_gfx_reg_o24 = NULL;
GFX_O24_REG_T*          g_gfx_reg_o24_cache = NULL;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T* GFX_O24_GetCfg(void);
int                 GFX_O24_InitHW(void);
int                 GFX_O24_ShutdownHW(void);
irqreturn_t         GFX_O24_ISRHandler(int irq, void* dev_id);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static const GFX_HAL_T g_gfx_hal_o24 =
{
    .GetCfg                 = GFX_O24_GetCfg,
    .InitHW                 = GFX_O24_InitHW,
    .ShutdownHW             = GFX_O24_ShutdownHW,
    .RunSuspend             = GFX_O24_RunSuspend,
    .RunResume              = GFX_O24_RunResume,

    .RunFlushCommand        = GFX_O24_RunFlushCommand,
    .RunStartCommand        = GFX_O24_RunStartCommand,
    .RunPauseCommand        = GFX_O24_PauseCommand,
    .RunResumeCommand       = GFX_O24_ResumeCommand,
    .RunStopCommand         = GFX_O24_StopCommand,
    .RunSwResetCommand      = GFX_O24_SwResetCommand,

    .GetComQueueStatus      = GFX_O24_GetComQueueStatus,

    .GetOperationStatus     = GFX_O24_GetOperationStatus,
    .SetOperationStatus     = GFX_O24_SetOperationStatus,
    .GetInputConfigure      = GFX_O24_GetInputConfigure,
    .SetInputConfigure      = GFX_O24_SetInputConfigure,
    .GetBlendConfigure      = GFX_O24_GetBlendConfigure,
    .SetBlendConfigure      = GFX_O24_SetBlendConfigure,
    .SetBlendingOut         = GFX_O24_SetBlendingOut,
    .GetOutputConfigure     = GFX_O24_GetOutputConfigure,
    .SetOutputConfigure     = GFX_O24_SetOutputConfigure,
    .SetScalerConfigure     = GFX_O24_SetScalerConfigure,
    .SetCLUT                = GFX_O24_SetCLUT,
    .SetCommandDelayReg     = GFX_O24_SetCommandDelayReg,
    .GetCommandDelayReg     = GFX_O24_GetCommandDelayReg,

    .IsGfxIdle              = GFX_O24_IsGfxIdle,

    .DumpRegister           = GFX_O24_DumpRegister,

    .RunClkOnCommand        = GFX_O24_RunClkOnCommand,
    .RunClkOffCommand       = GFX_O24_RunClkOffCommand,
    .ClkCheck               = GFX_O24_ClkCheck,
};

static  LX_GFX_CFG_T        g_gfx_cfg_o24 =
{
    .b_hw_scaler            = TRUE,
    .surface_blit_cmd_delay = 0xffff,       // normal gfx operation by APP.
    .screen_blit_cmd_delay  = 0xffff,       // internal gfx operation by KDRV.
#if CONFIG_LX_BOARD_FPGA
    .sync_wait_timeout      = 30000,        /* 30 sec. enough timeout required for FPGA */
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

/** get O24 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_O24_GetCfg(void)
{
    return &g_gfx_cfg_o24;
}

void    GFX_O24_InitHAL(GFX_HAL_T*  hal)
{
    memcpy(hal, &g_gfx_hal_o24, sizeof(GFX_HAL_T));

    switch (lx_chip_rev())
    {
        case LX_CHIP_REV(O24, A0):
        {
            g_gfx_cfg_o24.workaround.bad_dst_addr_stuck      = 0;
            g_gfx_cfg_o24.workaround.scaler_read_buf_stuck   = 0;
            g_gfx_cfg_o24.workaround.srcblt_op_stuck         = 0;
            g_gfx_cfg_o24.workaround.write_op_stuck          = 0;
        }
        break;

        default:
        {
            g_gfx_cfg_o24.workaround.bad_dst_addr_stuck      = 0;
            g_gfx_cfg_o24.workaround.scaler_read_buf_stuck   = 0;
            g_gfx_cfg_o24.workaround.srcblt_op_stuck         = 0;
            g_gfx_cfg_o24.workaround.write_op_stuck          = 0;
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
irqreturn_t GFX_O24_ISRHandler(int irq, void* dev_id)
{
    //  if ( GFX_IsGfxIdle() )
    {
        //      GFX_PRINT("#### GFX ISR - IDLE OK ####\n");
        GFX_WakeupWaitSync();
    }

    g_gfx_reg_o24->gfx_intr_clear.intr_clear = 0x1;
    GFX_PRINT("#### GFX ISR ####\n");

    return IRQ_HANDLED;
}

/** initialize O24 hardware
*
* @return RET_OK when success, RET_ERROR otherwise
*/

int GFX_O24_InitHW(void)
{
    static BOOLEAN b_os_init = FALSE;

    /* do ioremap */
    if (NULL == g_gfx_reg_o24)
    {
        g_gfx_reg_o24 = (GFX_O24_REG_T*)ioremap(gpGfxRegCfg->reg_base_addr, gpGfxRegCfg->reg_size);
        GFX_CHECK_ERROR(NULL == g_gfx_reg_o24, return RET_ERROR, "out of memory. can't ioremap\n");
    }

    if (NULL == g_gfx_reg_o24_cache)
    {
        g_gfx_reg_o24_cache = (GFX_O24_REG_T*)OS_Malloc(gpGfxRegCfg->reg_size);
        GFX_CHECK_ERROR(g_gfx_reg_o24_cache == NULL, return RET_ERROR, "out of memory\n");

        memset(g_gfx_reg_o24_cache, 0x0, gpGfxRegCfg->reg_size);
    }

    if (b_os_init == FALSE)
    {
        /* register GFX interrupt handler */
        GFX_CHECK_ERROR(request_irq(gpGfxRegCfg->irq_num, (irq_handler_t)GFX_O24_ISRHandler, 0, "gfx_irq", NULL), /* nop */,
                        "request_irq failed\n");

        b_os_init = TRUE;
    }

    /* Reset GFX H/W */
    GFX_O24_SwResetCommand();

    g_gfx_reg_o24->gfx_intr_ctrl.intr_gen_mode = 0; // batch command finish
    g_gfx_reg_o24->gfx_intr_ctrl.intr_en = 1;       // interrupt enable

    GFX_O24_InitScaler();
    return 0;
}

/** shutdown O24 hardware
 *
 * @return RET_OK when success, RET_ERROR otherwise
 */
int             GFX_O24_ShutdownHW(void)
{
    g_gfx_reg_o24->gfx_intr_ctrl.intr_en = 0;   // interrupt disable

    /* [TODO] more cleanup !!! */
    if (g_gfx_reg_o24)
    {
        iounmap((void*)g_gfx_reg_o24);
        g_gfx_reg_o24 = NULL;
    }

    if (g_gfx_reg_o24_cache)
    {
        OS_Free(g_gfx_reg_o24_cache);
        g_gfx_reg_o24_cache = NULL;
    }

    return 0;
}

/** @} */

