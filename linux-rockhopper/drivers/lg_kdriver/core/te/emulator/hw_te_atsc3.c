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
 *  Emulator driver for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-01-07
 *  @note		Additional information.
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "te_impl.h"
#include "te_emul.h"
#include "te_emul_regs.h"


/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define IS_RO_REG_OFFSET(offset)	\
	((offset) == A3_REG_OFFSET_CH_DATA_WPTR(0) || \
	 (offset) == A3_REG_OFFSET_CH_DATA_WPTR(1) || \
	 (offset) == A3_REG_OFFSET_CH_DATA_WPTR(2) || \
	 (offset) == A3_REG_OFFSET_CH_DATA_WPTR(3) || \
	 (offset) == A3_REG_OFFSET_CH_META_WPTR(0) || \
	 (offset) == A3_REG_OFFSET_CH_META_WPTR(1) || \
	 (offset) == A3_REG_OFFSET_CH_META_WPTR(2) || \
	 (offset) == A3_REG_OFFSET_CH_META_WPTR(3))

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

enum
{
	DECODE_LAYER_INVALID = 0,
	DECODE_LAYER_BB,
	DECODE_LAYER_ALP,
	DECODE_LAYER_LGC,
};

enum
{
	LGC_DECODE_STATE_IDLE = 0,
	LGC_DECODE_STATE_SCD1,
	LGC_DECODE_STATE_SCD2,
	LGC_DECODE_STATE_SCD3,
	LGC_DECODE_STATE_TYPE,
	LGC_DECODE_STATE_LEN1,
	LGC_DECODE_STATE_LEN2,
	LGC_DECODE_STATE_CC,
	LGC_DECODE_STATE_CNT,
};

typedef struct
{
	UINT8	state;

	UINT8	plp_id;
	UINT16	len;

	UINT8	cc;

	UINT16	byte_cnt;
	UINT32	header;

	UINT32	skip_bytes;
} ATSC3_LGC_DECODER_T;


typedef struct
{
	UINT8	enable;
	UINT8	layer;

	UINT8	plp_flt_en;
	UINT8	plp_id;

} ATSC3_CH_CTRL_T;

typedef struct
{
	ATSC3_LGC_DECODER_T		lgc_decoder;
	ATSC3_CH_CTRL_T			ch_ctrl[A3_REG_CH_MAX];

} ATSC3_HW_T;


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

static ATSC3_HW_T hw;
static ATSC3_LGC_DECODER_T *lgcd = &hw.lgc_decoder;


static void RegWriteChConf(UINT8 idx, UINT32 val)
{
	ATSC3_CH_CTRL_T *ctrl;
	UINT32 ptr;

//	LOG_ATSC3("ATSC3: Configure Channel[%d] Val[0x%x]\n", idx, val);

	ctrl = &hw.ch_ctrl[idx];
	if(val&A3_REG_CH_CONF_ENABLE)
	{
		ptr = REG_READ(REG_ATSC3_OFFSET + A3_REG_OFFSET_CH_META_SPTR(idx));
		REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_CH_META_WPTR(idx), ptr);
//		LOG_ATSC3("ATSC3: META SPTR=0x%x\n", ptr);

		ptr = REG_READ(REG_ATSC3_OFFSET + A3_REG_OFFSET_CH_DATA_SPTR(idx));
		REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_CH_DATA_WPTR(idx), ptr);
//		LOG_ATSC3("ATSC3: DATA SPTR=0x%x\n", ptr);

		switch(val&A3_REG_CH_CONF_LAYER_MASK)
		{
			case A3_REG_CH_CONF_LAYER_LGC:
				ctrl->layer = DECODE_LAYER_LGC;
				break;

			case A3_REG_CH_CONF_LAYER_BB:
				ctrl->layer = DECODE_LAYER_BB;
				break;

			case A3_REG_CH_CONF_LAYER_ALP:
				ctrl->layer = DECODE_LAYER_ALP;
				break;

			case A3_REG_CH_CONF_LAYER_ALP_PAYLOAD:
			default:
				ctrl->layer = DECODE_LAYER_INVALID;
				break;
		}
		ctrl->enable = TRUE;
	}
	else
	{
		ctrl->enable = FALSE;
	}
	REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_CH_CONF(idx), val);
}

static void RegWriteChFilter(UINT8 idx, UINT32 val)
{
	ATSC3_CH_CTRL_T *ctrl;

	ctrl = &hw.ch_ctrl[idx];
	if(val&A3_REG_CH_FILTER_PLP_EN)
	{
		ctrl->plp_flt_en = TRUE;
	}
	else
	{
		ctrl->plp_flt_en = FALSE;
	}
	ctrl->plp_id = A3_REG_CH_FILTER_GET_PLP_ID(val);

	REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_CH_FILTER(idx), val);
}

static void RegWrite(UINT32 offset, UINT32 val)
{
	UINT32 v;
	UINT32 en;

	//LOG_ATSC3("ATSC3 : REG_WRITE offset=0x%x, val=0x%x\n", offset, val);

	if(offset >= A3_REG_SIZE)
	{
		LOG_ERROR("invalid offset(0x%x)\n", offset);
		return;
	}

	if(offset >= A3_REG_CH_OFFSET)
	{
		UINT8 idx;
		UINT32 ofs;
		ofs = offset - A3_REG_CH_OFFSET;

		idx = ofs / A3_REG_CH_SIZE;
		ofs = ofs % A3_REG_CH_SIZE;

		switch(ofs)
		{
			case A3_REG_CH_RESET_OFFSET:
				break;

			case A3_REG_CH_CONF_OFFSET:
				RegWriteChConf(idx, val);
				break;

			case A3_REG_CH_FILTER_OFFSET:
				RegWriteChFilter(idx, val);
				break;

			default:
				REG_WRITE(REG_ATSC3_OFFSET + offset, val);
				break;
		}
	}
	else
	{
		switch(offset)
		{
			case A3_REG_OFFSET_INTR_MCU_EN:
				// TODO: if already raised intr exist than send signal
				REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_INTR_MCU_EN, val);
				break;

			case A3_REG_OFFSET_INTR_MCU_CL:
				v = REG_READ(REG_ATSC3_OFFSET + A3_REG_OFFSET_INTR_MCU_ST);
				if(v)
				{
					v &= ~val;
					REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_INTR_MCU_ST, v);

					if(!v)
					{
						TE_EMUL_MCU_ClearIrqStatus(MCU_IRQ_NUM_ATSC3);
					}
				}
				break;

			case A3_REG_OFFSET_INTR_MCU_EV:
				en = REG_READ(REG_ATSC3_OFFSET + A3_REG_OFFSET_INTR_MCU_EN);
				en &= val;
				if(en)	/* if enabled intr */
				{
					v = REG_READ(REG_ATSC3_OFFSET + A3_REG_OFFSET_INTR_MCU_ST);
					v |= en;
					if(v)
					{
						REG_WRITE(REG_ATSC3_OFFSET + A3_REG_OFFSET_INTR_MCU_ST, v);
						TE_EMUL_MCU_SetIrqStatus(MCU_IRQ_NUM_ATSC3);
					}
				}
				break;

			default:
				REG_WRITE(REG_ATSC3_OFFSET + offset, val);
				break;
		}

	}
}

static UINT32 RegRead(UINT32 offset)
{
	UINT32 val;

	val = REG_READ(REG_ATSC3_OFFSET + offset);

	return val;
}


void TE_EMUL_ATSC3_RegWrite(UINT32 offset, UINT32 val)
{
	/* Read Only Registers */
	if(IS_RO_REG_OFFSET(offset))
	{
		LOG_ERROR("R/O Register(0x%x)\n", offset);
		return;
	}

	RegWrite(offset, val);
}

static void DecodeLGC(UINT8 data)
{
	if(lgcd->state == LGC_DECODE_STATE_CNT &&
		lgcd->byte_cnt == lgcd->len)
	{
		lgcd->state = LGC_DECODE_STATE_IDLE;
		lgcd->skip_bytes = 188 - (8+lgcd->byte_cnt)%188;
	}

	switch(lgcd->state)
	{
		case LGC_DECODE_STATE_IDLE:
			if(lgcd->skip_bytes)
			{
				lgcd->skip_bytes--;
				break;
			}
		case LGC_DECODE_STATE_SCD1:
		case LGC_DECODE_STATE_SCD2:
		case LGC_DECODE_STATE_SCD3:
			if(data == 0x5A)
				lgcd->state += 1;	/* goto next step */
			else
			{
				if(lgcd->state != LGC_DECODE_STATE_IDLE)
				{
					printk("SYNC DROP !!!\n");
					lgcd->state = LGC_DECODE_STATE_IDLE;
				}
			}
			break;

		case LGC_DECODE_STATE_TYPE:
			if((data&0xC0) == 0xC0) /* bit7:1 & bit6:1 = bb-frame has error */
			{
				lgcd->state = LGC_DECODE_STATE_IDLE;
			}
			else
			{
				lgcd->plp_id = data&0x3F;
				lgcd->state = LGC_DECODE_STATE_LEN1;
				lgcd->header = (UINT32)data << 24;
			}
			break;

		case LGC_DECODE_STATE_LEN1:
			lgcd->len = (UINT16)data << 8;
			lgcd->header |= (UINT32)data << 16;
			lgcd->state = LGC_DECODE_STATE_LEN2;
			break;

		case LGC_DECODE_STATE_LEN2:
			lgcd->len |= data;
			lgcd->header |= (UINT32)data << 8;
			lgcd->state = LGC_DECODE_STATE_CC;
			break;

		case LGC_DECODE_STATE_CC:
			lgcd->cc = data;
			if(lgcd->len == 0)
				lgcd->state = LGC_DECODE_STATE_IDLE;
			else
			{
				lgcd->byte_cnt = 0;
				lgcd->header |= data;
				lgcd->state = LGC_DECODE_STATE_CNT;
			}
			break;

		case LGC_DECODE_STATE_CNT:
			lgcd->byte_cnt++;
			break;

		default:
			break;
	}
}

static void DecodeBB(UINT8 idx, UINT8 data)
{
	UINT32 addr, sptr, wptr, eptr;

	if(lgcd->state == LGC_DECODE_STATE_CNT)
	{
		if(lgcd->byte_cnt == 0)
		{
			addr = RegRead(A3_REG_OFFSET_CH_META_WPTR(idx));

			/* write the meta info */
			sptr = RegRead(A3_REG_OFFSET_CH_DATA_SPTR(idx));
			wptr = RegRead(A3_REG_OFFSET_CH_DATA_WPTR(idx));

			MEM_WRITE(addr+0, lgcd->header);
			MEM_WRITE(addr+12, wptr);

			addr += 16;
			eptr = RegRead(A3_REG_OFFSET_CH_META_EPTR(idx));
			if(addr >= eptr)
			{
				addr = RegRead(A3_REG_OFFSET_CH_META_SPTR(idx));
			}
			RegWrite(A3_REG_OFFSET_CH_META_WPTR(idx), addr);

			RegWrite(A3_REG_OFFSET_INTR_MCU_EV, A3_REG_INTR_CH_META_WR_INTR_BIT(idx));
		}
		else
		{
			wptr = RegRead(A3_REG_OFFSET_CH_DATA_WPTR(idx));
			MEM_WRITE8(wptr, data);
			wptr++;

			eptr = RegRead(A3_REG_OFFSET_CH_DATA_EPTR(idx));
			if(wptr == eptr)
			{
				sptr = RegRead(A3_REG_OFFSET_CH_DATA_SPTR(idx));
				RegWrite(A3_REG_OFFSET_CH_DATA_WPTR(idx), sptr);
			}
			else
			{
				RegWrite(A3_REG_OFFSET_CH_DATA_WPTR(idx), wptr);
			}

			if(lgcd->byte_cnt == lgcd->len)
			{
				// Send Event
			}
		}
	}

}


static void PutData(UINT8 data)
{
	int i;

	DecodeLGC(data);

	for(i=0; i<A3_REG_CH_MAX; i++)
	{
		ATSC3_CH_CTRL_T *ctrl = &hw.ch_ctrl[i];

		if(ctrl->enable)
		{
			if(ctrl->plp_flt_en && ctrl->plp_id != lgcd->plp_id)
			{
				continue;
			}

			switch(ctrl->layer)
			{
				case DECODE_LAYER_BB:
					DecodeBB(i, data);
					break;

				case DECODE_LAYER_ALP:
					break;

				default:	/* LG Container */
					break;
			}
		}
	}

}



void TE_EMUL_ATSC3_PutStream(const UINT8* buf, UINT32 size)
{
	int i;

	for(i=0; i<size; i++)
	{
		PutData(buf[i]);
	}
}
EXPORT_SYMBOL(TE_EMUL_ATSC3_PutStream);
