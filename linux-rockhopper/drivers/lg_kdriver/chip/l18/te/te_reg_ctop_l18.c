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
 *  te ctop functions
 *
 *  @author	Ilkyu KIm ( ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2017-04-11
 *  @note		Additional information.
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sys_regs.h"

#include "te_impl.h"
#include "te_reg.h"
#include "te_reg_ctrl.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define TRACE_ENTER(fmt,args...)							\
{ 															\
	if (unlikely(g_te_reg_log_mask & (1<<REG_LOG_CTOP)))	\
	{ 														\
		LOG_NOTI("@CTOP_REG : %s(" fmt ")", __F__, ##args);	\
	}														\
}

#define TRACE_EXIT(fmt,args...)								\
{ 															\
	if (unlikely(g_te_reg_log_mask & (1<<REG_LOG_CTOP)))	\
	{ 														\
		LOG_NOTI("~CTOP_REG : %s(" fmt ")", __F__, ##args);	\
	}														\
}


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

static DEFINE_SPINLOCK(ctop_reg_lock);

int L18_TE_REG_CTOP_SetInitValue(void)
{
	//unsigned long flag;

	TRACE_ENTER("");

	//spin_lock_irqsave(&ctop_reg_lock, flag);

	// Nothing to do

	//spin_unlock_irqrestore (&ctop_reg_lock, flag);

	return RET_OK;
}

int L18_TE_REG_SetCiInput(UINT8 src)
{
	unsigned long flag;
	int ret = RET_OK;
	UINT8 v;

	TRACE_ENTER("src=%d", src);

	switch(src)
	{
		case CI_INPUT_SRC_IN_DEMOD:		v = 0; break;
		case CI_INPUT_SRC_EXT_INPUT0:	v = 1; break;
		case CI_INPUT_SRC_TE:			v = 2; break;
		default:
			LOG_ERROR("not supported src(%d)", src);
			return RET_ERROR;
	}

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_L18A0_RdFL(CODEC_SYN, syn_codec02);
	CTOP_CTRL_L18A0_Wr01(CODEC_SYN, syn_codec02, reg_tp_output_mux_sel, v);
	CTOP_CTRL_L18A0_WrFL(CODEC_SYN, syn_codec02);

	spin_unlock_irqrestore (&ctop_reg_lock, flag);

	return ret;
}

int L18_TE_REG_GetCiInput(UINT8 *src)
{
	UINT8 v;
	unsigned long flag;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_L18A0_RdFL(CODEC_SYN, syn_codec02);
	CTOP_CTRL_L18A0_Rd01(CODEC_SYN, syn_codec02, reg_tp_output_mux_sel, v);

	spin_unlock_irqrestore (&ctop_reg_lock, flag);

	if(v == 0)		*src = CI_INPUT_SRC_IN_DEMOD;
	else if(v == 1)	*src = CI_INPUT_SRC_EXT_INPUT0;
	else if(v == 2) *src = CI_INPUT_SRC_TE;
	else			*src = CI_INPUT_SRC_NONE;

	TRACE_EXIT("*src=%d", *src);

	return RET_OK;
}


int L18_TE_REG_SetCiOutClk(UINT8 clk)
{
	unsigned long flag;
	UINT8 v;

	TRACE_ENTER("clk=%d", clk);

	switch(clk)
	{
		case OUTPUT_CLK_24MHZ:	v = 0; break;
		case OUTPUT_CLK_12MHZ:	v = 1; break;
		case OUTPUT_CLK_8MHZ:	v = 2; break;
		case OUTPUT_CLK_4MHZ:	v = 3; break;
		default:
			LOG_ERROR("not supported clk(%d)", clk);
			return RET_ERROR;
	}

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_L18A0_RdFL(CODEC_SYN, crg_codec00);
	CTOP_CTRL_L18A0_Wr01(CODEC_SYN, crg_codec00, te_ciout_clk_sel, v);
	CTOP_CTRL_L18A0_WrFL(CODEC_SYN, crg_codec00);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return RET_OK;
}

int L18_TE_REG_SetStccClockSource(UINT8 ch, UINT8 src)
{
	unsigned long flag;
	UINT8 v;

	CHECK_ERROR(ch > 2, return RET_INVALID_PARAMS, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = (src == STCC_CLK_SRC_FIXED) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_L18A0_RdFL(CODEC_SYN, crg_codec00);
	switch(ch)
	{
		case 0: CTOP_CTRL_L18A0_Wr01(CODEC_SYN, crg_codec00, te_ch0_sclk_sel, v); break;
		case 1: CTOP_CTRL_L18A0_Wr01(CODEC_SYN, crg_codec00, te_ch1_sclk_sel, v); break;
		case 2: CTOP_CTRL_L18A0_Wr01(CODEC_SYN, crg_codec00, te_ch2_sclk_sel, v); break;
		default: break;
	}
	CTOP_CTRL_L18A0_WrFL(CODEC_SYN, crg_codec00);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return RET_OK;
}

int L18_TE_REG_SetInOutPort(UINT8 port, UINT8 dir, UINT8 mode, UINT8 clk)
{
	int ret = RET_ERROR;
	unsigned long flag;

	TRACE_ENTER("port=%d,dir=%d,mode=%d,clk=%d", port, dir, mode, clk);

	spin_lock_irqsave(&ctop_reg_lock, flag);
	if(dir == PORT_DIR_OUTPUT)
	{
		UINT32 val;

		if(port == TPI_CAM_LOOP_BACK)
		{
			switch(clk)
			{
				case OUTPUT_CLK_24MHZ:	val = 0; break;
				case OUTPUT_CLK_12MHZ:	val = 1; break;
				case OUTPUT_CLK_8MHZ:	val = 2; break;
				case OUTPUT_CLK_4MHZ:	val = 3; break;
				default:
					LOG_ERROR("not supported clk(%d)", clk);
					ret = RET_INVALID_PARAMS;
					goto exit;
			}

			CTOP_CTRL_L18A0_RdFL(CODEC_SYN, crg_codec00);
			CTOP_CTRL_L18A0_Wr01(CODEC_SYN, crg_codec00, te_ciout_clk_sel, val);
			CTOP_CTRL_L18A0_WrFL(CODEC_SYN, crg_codec00);
		}
		else
		{
			LOG_ERROR("not supported port(%d)", port);
			ret = RET_INVALID_PARAMS;
			goto exit;
		}
	}
	else
	{
		LOG_ERROR("not supported dir(%d)", dir);
		ret = RET_INVALID_PARAMS;
		goto exit;
	}
	ret = RET_OK;
exit:
	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return ret;
}


int L18_TE_REG_GetDcoInputClock(UINT32 *freq)
{
	*freq = 189; //TODO: Check the clock selection
	return RET_OK;
}


int L18_TE_REG_SelectUart(UINT8 uart)
{
	const char *name;

	CTOP_CTRL_L18A0_RdFL(VDEC, syn_vdec05);
	if(uart == TE_UART_MCU0) //te mcu 0
	{
		CTOP_CTRL_L18A0_Wr01(VDEC, syn_vdec05, reg_uart0_sel, 6);
		TE_REG_SetUartMux(0);
		name = "unimcu";
	}
	else if(uart == TE_UART_MCU1)
	{
		LOG_ERROR("not supported uart[%d]", uart);
		return RET_INVALID_PARAMS;
	}
	else //arm
	{
		CTOP_CTRL_L18A0_Wr01(VDEC, syn_vdec05, reg_uart0_sel, 1);
		name = "arm";
	}

	CTOP_CTRL_L18A0_WrFL(VDEC, syn_vdec05);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return RET_OK;
}

int L18_TE_REG_SelectJtag(UINT8 jtag)
{
	const char *name;

	CTOP_CTRL_L18A0_RdFL(VDEC, syn_vdec04);
	if(jtag == TE_JTAG_MCU0)//te mcu 0
	{
		CTOP_CTRL_L18A0_Wr01(VDEC, syn_vdec04, reg_jtag0_sel, 4);
		name = "mcu0";
	}
	else if(jtag == TE_JTAG_MCU1)
	{
		LOG_ERROR("not supported jtag[%d]", jtag);
		return RET_INVALID_PARAMS;
	}
	else //arm
	{
		CTOP_CTRL_L18A0_Wr01(VDEC, syn_vdec04, reg_jtag0_sel, 0);
		name = "arm";
	}
	CTOP_CTRL_L18A0_WrFL(VDEC, syn_vdec04);

	LOG_NOTI("jtag0 is connected with %s\n", name);

	return RET_OK;
}

