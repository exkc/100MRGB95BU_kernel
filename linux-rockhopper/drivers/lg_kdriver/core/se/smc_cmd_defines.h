/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2023 by LG Electronics Inc.
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
 *  smc command between REE and TEE
 *
 *  author		
 *  version		1.0
 *  date		2023.01.14
 *  note		Additional information.
 *
 */

#ifndef _SMC_CMD_DEFINES_H_
#define _SMC_CMD_DEFINES_H_

/* 
 * Legacy SMC Command definations in tz_if.h
 * These definations should be replaced with commands 
 * fulfilling SMC Calling Convention. 
 */
#define SMC_FAST_GET_WSM_CONFIG             (0x304)
#define TZ_CMD_INIT_IF                		(0x02)
#define TZOS_SMC_CMD_FOREIGN_IRQ      		(8004)
/* reek_drv --> secure_os */
#define SMC_RETURN_FROM_RMT					(8005)



/*
 * SMC Command definations fulfilling SMC Calling Convention.
 */
#define SMC_FAST_CALL 						(1 << 31)
#define SMC_STD_CALL 						(0 << 31)

#define SMC_64 								(1 << 30)
#define SMC_32								(0 << 30)

#define SMC_OEN_OFFSET 						(24)
#define SMC_OEN_MASK 						(0x3F << SMC_OEN_OFFSET) /*6 bits*/
#define SMC_OEN_SIP 						(2 << SMC_OEN_OFFSET)
#define SMC_OEN_STD 						(4 << SMC_OEN_OFFSET)

/* 0x8200ff08 */
#define LGE_SMC_TOGGLED_ASC 				(0xff08)
#define TZ_CMD_TOGGLED_ASC_CMD 	\
			((uint32_t)(SMC_FAST_CALL|SMC_OEN_SIP|LGE_SMC_TOGGLED_ASC)) 

/* 0x8200ff09 */
#define LGE_SMC_SECURE_FWLOAD 				(0xff09)
#define TZ_CMD_SECURE_FWLOAD 	\
			((uint32_t)(SMC_FAST_CALL|SMC_OEN_SIP|LGE_SMC_SECURE_FWLOAD)) 

/* 0x8200ff0a */
#define LGE_SMC_GET_RMT_RWSM_CONFIG 		(0xff0a)
#define TZ_CMD_GET_RMT_RWSM_CONFIG 	\
			((uint32_t)(SMC_FAST_CALL|SMC_OEN_SIP|LGE_SMC_GET_RMT_RWSM_CONFIG))

/* 0x8200ff0b */
#define LGE_SMC_RETURN_FROM_RMT 			(0xff0b)
#define TZ_CMD_RETURN_FROM_RMT 	\
			((uint32_t)(SMC_STD_CALL|SMC_OEN_SIP|LGE_SMC_RETURN_FROM_RMT))



#define LGTEE_RMT_SMC_MASK					(0xFFFFF000)
#define LGTEE_RMT_SMC_FUNC_MASK				(0x00000FFF)

/* secure_os in x0 --> reek_drv */
#define LGTEE_RMT_SMC_FUNC_FOREIGN_IRQ 		(LGTEE_RMT_SMC_MASK | 0x1)
#define LGTEE_RMT_SMC_FUNC_RUTA 			(LGTEE_RMT_SMC_MASK | 0x2)
#define LGTEE_RMT_SMC_FUNC_WSM_ALLOC 		(LGTEE_RMT_SMC_MASK | 0x3)
#define LGTEE_RMT_SMC_FUNC_WSM_FREE 		(LGTEE_RMT_SMC_MASK | 0x4)

/* check if remote secure monitor call */
#define IS_RMT_SMC(res) ((res & LGTEE_RMT_SMC_MASK) == LGTEE_RMT_SMC_MASK)



struct rmt_param {
	u32	a0;
	u32	a1;
	u32	a2;
	u32	a3;
	u32	a4;
	u32	a5;
	u32	a6;
	u32	a7;
};


void ree_smccc_smc( ulong a0, ulong a1, ulong a2, ulong a3, ulong a4, 
					ulong a5, ulong a6, ulong a7, struct arm_smccc_res *res);

void handle_remote_smc(struct rmt_param *rparam);

int do_smc_with_args(u32 *smc_args);



#endif /* _SMC_CMD_DEFINES_H_ */
