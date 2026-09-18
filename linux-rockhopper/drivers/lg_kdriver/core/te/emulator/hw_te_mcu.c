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


/*----------------------------------------------------------------------------------------
 *   Type Definitions
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



void TE_EMUL_MCU_RegWrite(UINT8 mcu, UINT32 offset, UINT32 val)
{
	UINT32 v;
	UINT32 base = (mcu == 0) ? REG_MCU0_OFFSET : REG_MCU1_OFFSET;

//	LOG_NOTI("%s(mcu=%d,offset=0x%x,val=0x%x)\n", __FUNCTION__, mcu, offset, val);

	switch(offset)
	{
		case MCU_REG_OFFSET_INTR2CPU_CL:
			if(val&MCU_INTR_IPC_MASK)
			{
				v = REG_READ(base + MCU_REG_OFFSET_INTR2CPU_ST);
				v &= ~MCU_INTR_IPC_MASK;
				REG_WRITE(base + MCU_REG_OFFSET_INTR2CPU_ST, v);

				v = (mcu == 0) ? CPU_IRQ_NUM_MCU0 : CPU_IRQ_NUM_MCU1;
				TE_EMUL_CPU_ClearIrqStatus(v);
			}
			break;

		case MCU_REG_OFFSET_INTR2CPU_EV:	/* MCU TO CPU IPC */
			if(val&MCU_INTR_IPC_MASK)
			{
				v = REG_READ(base + MCU_REG_OFFSET_INTR2CPU_ST);
				v |= MCU_INTR_IPC_MASK;
				REG_WRITE(base + MCU_REG_OFFSET_INTR2CPU_ST, v);

				v = (mcu == 0) ? CPU_IRQ_NUM_MCU0 : CPU_IRQ_NUM_MCU1;
				TE_EMUL_CPU_SetIrqStatus(v);
			}
			break;



		case MCU_REG_OFFSET_INTR2MCU_CL:
			if(val&MCU_INTR_IPC_MASK)
			{
				v = REG_READ(base + MCU_REG_OFFSET_INTR2MCU_ST);
				v &= ~MCU_INTR_IPC_MASK;
				REG_WRITE(base + MCU_REG_OFFSET_INTR2MCU_ST, v);

				TE_EMUL_MCU_ClearIrqStatus(MCU_IRQ_NUM_IPC);
			}

			break;

		case MCU_REG_OFFSET_INTR2MCU_EV:	/* CPU TO MCU IPC */
			if(val&MCU_INTR_IPC_MASK)
			{
				v = REG_READ(base + MCU_REG_OFFSET_INTR2MCU_ST);
				v |= MCU_INTR_IPC_MASK;
				REG_WRITE(base + MCU_REG_OFFSET_INTR2MCU_ST, v);

				TE_EMUL_MCU_SetIrqStatus(MCU_IRQ_NUM_IPC);
			}
			break;

		default:
			REG_WRITE(base + offset, val);
			break;
	}
}




