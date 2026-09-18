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
 *  CI register details. ( used only within kdriver )
 *
 *  @author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2015.1.1
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef __CI_REGDEFS_H__
#define __CI_REGDEFS_H__

#include <linux/types.h>
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

#define CI_DEFINE_REG_CTRL(_name)	\
		typedef struct _name##_bit _name##_bit_t;	\
		union _##_name {					\
			_name##_bit_t	ctrl_bit;	\
			u16				ctrl;		\
		};								\
		typedef union _##_name _name##_t

struct ctrl_status_1_bit {
	u16		rsvd_0			:2,
			vccen_n			:1,
			rsvd_3			:2,
			en_pccard		:1,
			en_hw_hot_swap	:1,
			card_reset		:1,
			_rsvd			:8;
};
CI_DEFINE_REG_CTRL(ctrl_status_1);

struct ctrl_status_2_bit {
	u16		cd1				:1,
			cd2				:1,
			vs1				:1,
			vs2				:1,
			ready_ireq		:1,
			bvd1			:1,
			bvd2			:1,
			inpack			:1,
			iois16			:1,
			_rsvd			:7;
};
CI_DEFINE_REG_CTRL(ctrl_status_2);

struct ctrl_status_3_bit {
	u16		rsvd_0			:2,
			io_int_mode		:1,
			pod_ext_sig		:1,
			pod_mode		:1,
			card_is_mem		:1,
			_rsvd			:(8+2);
};
CI_DEFINE_REG_CTRL(ctrl_status_3);

struct pc_card_status_1_bit {
	u16		chip_mode		:5,
			c_flash_mode	:1,
			ide_mode		:1,
			_rsvd			:(8+1);
};
CI_DEFINE_REG_CTRL(pc_card_status_1);

struct pc_card_status_2_bit {
	u16		setup_timing	:8,
			command_timing	:8;
};
CI_DEFINE_REG_CTRL(pc_card_status_2);

struct pc_card_status_3_bit {
	u16		recovery_timing	:8,
			_rsvd			:8;
};
CI_DEFINE_REG_CTRL(pc_card_status_3);

struct burst_ctrl_bit {
	u16		recovery_timing	:8,
			_rsvd			:8;
};
CI_DEFINE_REG_CTRL(burst_ctrl);

struct timeout_ctrl_bit {
	u16		timeout_enable	:1,
			_rsvd			:(8+7);
};
CI_DEFINE_REG_CTRL(timeout_ctrl);

struct timeout_bit {
	u16		timeout_counter;
};
CI_DEFINE_REG_CTRL(timeout);

struct intr_flag_bit {
	u16		cd_changed		:1,
			rsvd_1			:1,
			hw_hs_done		:1,
			ireq			:1,
			bvd1			:1,
			bvd2			:1,
			stschg			:1,
			timeout			:1,
			_rsvd			:8;
};
CI_DEFINE_REG_CTRL(intr_flag);

struct intr_mask_bit {
	u16		cd_changed		:1,
			rsvd_1			:1,
			hw_hs_done		:1,
			ireq			:1,
			bvd1			:1,
			bvd2			:1,
			stschg			:1,
			timeout			:1,
			_rsvd			:8;
};
CI_DEFINE_REG_CTRL(intr_mask);

struct intr_ctrl_bit {
	u16		bvd1_pol		:1,
			bvd2_pol		:1,
			gpio_int_sel	:2,
			en_gpio_int		:1,
			ireq_pol		:1,
			cd_int_mode		:1,
			cd_pol			:1,
			_rsvd			:8;
};
CI_DEFINE_REG_CTRL(intr_ctrl);

struct pcmcia_idx_bit {
	u16		addr_idx		:10,
			_rsvd			:6;
};
CI_DEFINE_REG_CTRL(pcmcia_idx);

struct hs_ctrl_1_bit {
	u16		addr_idx		:10,
			_rsvd			:6;
};
CI_DEFINE_REG_CTRL(hs_ctrl_1);

struct hs_ctrl_2_bit {
	u16		power_on_interval0;
};
CI_DEFINE_REG_CTRL(hs_ctrl_2);

struct hs_ctrl_3_bit {
	u16		enable_interval0;
};
CI_DEFINE_REG_CTRL(hs_ctrl_3);

struct hs_ctrl_4_bit {
	u16		enable_interval1;
};
CI_DEFINE_REG_CTRL(hs_ctrl_4);

struct hs_ctrl_5_bit {
	u16		card_insert_done_interval0;
};
CI_DEFINE_REG_CTRL(hs_ctrl_5);

struct hs_ctrl_6_bit {
	u16		card_insert_done_interval1;
};
CI_DEFINE_REG_CTRL(hs_ctrl_6);

struct hs_ctrl_7_bit {
	u16		card_removal_done_interval0;
};
CI_DEFINE_REG_CTRL(hs_ctrl_7);

struct hs_ctrl_8_bit {
	u16		card_removal_done_interval1;
};
CI_DEFINE_REG_CTRL(hs_ctrl_8);

enum {
	CREG_CTRL_STATUS_1		= 0x0000,
	CREG_CTRL_STATUS_2		= 0x0002,
	CREG_CTRL_STATUS_3		= 0x0004,
	/* */
	CREG_PC_CARD_CTRL_1		= 0x0006,
	CREG_PC_CARD_CTRL_2		= 0x0008,
	CREG_PC_CARD_CTRL_3		= 0x000A,
	/* */
	CREG_RSVD_0C			= 0x000C,
	CREG_RSVD_0E			= 0x000E,
	/* */
	CREG_BUSRT_CTRL			= 0x0010,
	CREG_TIMEOUT_CTRL		= 0x0012,
	CREG_TIMEOUT			= 0x0014,
	/* */
	CREG_RSVD_16			= 0x0016,
	CREG_RSVD_18			= 0x0018,
	CREG_RSVD_1A			= 0x001A,
	CREG_RSVD_1C			= 0x001C,
	CREG_RSVD_1E			= 0x001E,
	CREG_RSVD_20			= 0x0020,
	CREG_RSVD_22			= 0x0022,
	CREG_RSVD_24			= 0x0024,
	/* */
	CREG_INTR_FLAG			= 0x0026,
	CREG_INTR_MASK			= 0x0028,
	CREG_INTR_CTRL			= 0x002A,
	/* */
	CREG_PCMCIA_IDX			= 0x002C,
	/* */
	CREG_HS_CTRL_1			= 0x002E,
	CREG_HS_CTRL_2			= 0x0030,
	CREG_HS_CTRL_3			= 0x0032,
	CREG_HS_CTRL_4			= 0x0034,
	CREG_HS_CTRL_5			= 0x0036,
	CREG_HS_CTRL_6			= 0x0038,
	CREG_HS_CTRL_7			= 0x003A,
	CREG_HS_CTRL_8			= 0x003C,
};

struct ci_reg {
	ctrl_status_1_t			ctrl_status_1;
	ctrl_status_2_t			ctrl_status_2;
	ctrl_status_3_t			ctrl_status_3;
	/* */
	pc_card_status_1_t		pc_card_status_1;
	pc_card_status_2_t		pc_card_status_2;
	pc_card_status_3_t		pc_card_status_3;
	/* */
	u16						rsvd_oc[2];
	/* */
	burst_ctrl_t			burst_ctrl;
	timeout_ctrl_t			timeout_ctrl;
	timeout_t				timeout;
	/* */
	u16						rsvd_16c[8];
	/* */
	intr_flag_t				intr_flag;
	intr_mask_t				intr_mask;
	intr_ctrl_t				intr_ctrl;
	/* */
	pcmcia_idx_t			pcmcia_idx;
	/* */
	hs_ctrl_1_t				hs_ctrl_1;
	hs_ctrl_2_t				hs_ctrl_2;
	hs_ctrl_3_t				hs_ctrl_3;
	hs_ctrl_4_t				hs_ctrl_4;
	hs_ctrl_5_t				hs_ctrl_5;
	hs_ctrl_6_t				hs_ctrl_6;
	hs_ctrl_7_t				hs_ctrl_7;
	hs_ctrl_8_t				hs_ctrl_8;
};
typedef struct ci_reg ci_reg_t;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __CI_REGDEFS_H__ */

