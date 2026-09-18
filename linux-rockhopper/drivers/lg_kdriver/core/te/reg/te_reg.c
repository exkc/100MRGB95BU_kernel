/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
 *  sdec driver
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#include <lg1k/te/reg.h>
#include <lg1k/te/mcu.h>

#include "te_impl.h"
#include "te_reg_ctrl.h"

#ifdef TE_EMULATOR
#include "emulator/te_emul.h"
#endif

#define INIT_REG_CTRL(_c_,_a_,_s_)				\
do {								\
	_c_.phys.addr = ioremap(_a_, _s_);			\
	if (!(_c_).phys.addr) {					\
		log_error("ioremap(0x%08x) fail\n", _a_);	\
		return -ENOMEM;					\
	}							\
								\
	_c_.shdw.addr = kmalloc(_s_, GFP_KERNEL);		\
	if (!(_c_).shdw.addr) {					\
		log_error("kmalloc fail\n");			\
		return -ENOMEM;					\
	}							\
								\
	_c_.size = _s_;						\
} while(0)


struct te_reg_ctrl g_te_reg_ctrl;
u32 g_te_reg_log_mask;

static struct te_reg_ctrl *get_reg_ctrl(void)
{
	return &g_te_reg_ctrl;
}

static int reg_init(struct te_device *dev)
{
	int i;
	struct te_config *cfg = te_get_config();
	struct te_reg_addr_cfg *acfg = te_get_reg_addr_config();
	struct te_reg_ctrl *c = get_reg_ctrl();

	switch (lx_chip()) {
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		INIT_REG_CTRL(c->dumper, acfg->dumper, sizeof(DUMPER_REG_T));
		INIT_REG_CTRL(c->stcc, acfg->stcc, sizeof(FE_STCC_REG_T));
		break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
		INIT_REG_CTRL(c->dumper, acfg->dumper, sizeof(DUMPER_REG_T));
		INIT_REG_CTRL(c->stcc, acfg->stcc, sizeof(FE_STCC_REG_T));
		break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
		INIT_REG_CTRL(c->dumper, acfg->dumper, sizeof(DUMPER_REG_T));
		INIT_REG_CTRL(c->stcc, acfg->stcc, sizeof(FE_STCC_REG_T));
		break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	case LX_CHIP_O22:
		INIT_REG_CTRL(c->dumper, acfg->dumper, sizeof(DUMPER_REG_T));
		if (cfg->no_stcc_bug)
			break;

		INIT_REG_CTRL(c->stcc, acfg->stcc, sizeof(FE_STCC_REG_T));
		break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	case LX_CHIP_E60:
		INIT_REG_CTRL(c->stcc, acfg->stcc, sizeof(FE_STCC_Y21_REG_T));
		INIT_REG_CTRL(c->dumper, acfg->dumper, sizeof(DUMPER_REG_T));
		break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	case LX_CHIP_O20:
		INIT_REG_CTRL(c->stcc, acfg->stcc, sizeof(FE_STCC_Y21_REG_T));
		INIT_REG_CTRL(c->dumper, acfg->dumper, sizeof(DUMPER_REG_T));
		break;
#endif
	default:
		panic("Not supported chip !!! 0x%x\n", lx_chip());
	}

	INIT_REG_CTRL(c->tpi, acfg->tpi, sizeof(TPI_REG_T));
	INIT_REG_CTRL(c->top, acfg->top, sizeof(TOP_REG_T));
	INIT_REG_CTRL(c->pidf, acfg->pidf, sizeof(FE_PIDF_REG_T));
	INIT_REG_CTRL(c->tsbuf, acfg->tsbuf, sizeof(FE_TSBUF_REG_T));
	INIT_REG_CTRL(c->be, acfg->be, sizeof(BE_REG_T));
	INIT_REG_CTRL(c->ciplus, acfg->ciplus, sizeof(CIPLUS_REG_T));

	for (i = 0; i < cfg->num_dsc; i++) {
		INIT_REG_CTRL(c->dsc[i], acfg->dsc[i], sizeof(DSC_TOP_REG_T));
	}

	for (i = 0; i < cfg->num_upload; i++) {
		INIT_REG_CTRL(c->upload[i], acfg->upload[i],
			      sizeof(UPLOAD_REG_T));
	}

	for (i = 0; i < cfg->num_mcu; i++) {
		INIT_REG_CTRL(c->mcu[i], acfg->mcu[i], 0x200);
	}


	TE_REG_CTOP_Init();

	TE_REG_TOP_Init();
	TE_REG_TPI_Init();
	TE_REG_FE_TSBUF_Init();
	TE_REG_FE_STCC_Init();
	TE_REG_FE_PIDF_Init();

	TE_REG_BE_Init();
	TE_REG_UPLOAD_Init();
	TE_REG_CIPLUS_Init();

	te_reg_dumper_init();
	te_reg_dsc_init();

	return 0;
}

static void reg_release(struct te_device *dev)
{
	// TODO
}

void __iomem *TE_REG_GetBaseAddr(LX_TE_BLOCK_T block)
{
	void __iomem *addr;
	struct te_reg_ctrl *c = get_reg_ctrl();

	switch (block) {
	case LX_TE_BLOCK_TOP:
		addr = (void __iomem *)c->top.phys.addr;
		break;
	case LX_TE_BLOCK_TPI:
		addr = (void __iomem *)c->tpi.phys.addr;
		break;
	case LX_TE_BLOCK_FE_PIDF:
		addr = (void __iomem *)c->pidf.phys.addr;
		break;
	case LX_TE_BLOCK_FE_TSBUF:
		addr = (void __iomem *)c->tsbuf.phys.addr;
		break;
	case LX_TE_BLOCK_FE_STCC:
		addr = (void __iomem *)c->stcc.phys.addr;
		break;
	case LX_TE_BLOCK_BE_TOP:
		addr = (void __iomem *)c->be.phys.addr;
		break;
	case LX_TE_BLOCK_UPLOAD0:
		addr = (void __iomem *)c->upload[0].phys.addr;
		break;
	case LX_TE_BLOCK_UPLOAD1:
		addr = (void __iomem *)c->upload[1].phys.addr;
		break;
	case LX_TE_BLOCK_MCU0:
		addr = (void __iomem *)c->mcu[0].phys.addr;
		break;
	case LX_TE_BLOCK_MCU1:
		addr = (void __iomem *)c->mcu[1].phys.addr;
		break;
	case LX_TE_BLOCK_CIPLUS:
		addr = (void __iomem *)c->ciplus.phys.addr;
		break;
	case LX_TE_BLOCK_A3:
		addr = (void __iomem *)c->atsc3.phys.addr;
		break;
	case LX_TE_BLOCK_ARIB2:
		addr = (void __iomem *)c->arib2.phys.addr;
		break;
	case LX_TE_BLOCK_DUMPER:
		addr = (void __iomem *)c->dumper.phys.addr;
		break;
	case LX_TE_BLOCK_DSC0:
		addr = (void __iomem *)c->dsc[0].phys.addr;
		break;
	case LX_TE_BLOCK_DSC1:
		addr = (void __iomem *)c->dsc[1].phys.addr;
		break;
	default:
		addr = NULL;
		break;
	}

	return addr;
}

u32 TE_REG_GetSize(LX_TE_BLOCK_T block)
{
	u32 size;
	struct te_reg_ctrl *c = get_reg_ctrl();

	switch (block) {
	case LX_TE_BLOCK_TOP:
		size = c->top.size;
		break;
	case LX_TE_BLOCK_TPI:
		size = c->tpi.size;
		break;
	case LX_TE_BLOCK_FE_PIDF:
		size = c->pidf.size;
		break;
	case LX_TE_BLOCK_FE_TSBUF:
		size = c->tsbuf.size;
		break;
	case LX_TE_BLOCK_FE_STCC:
		size = c->stcc.size;
		break;
	case LX_TE_BLOCK_BE_TOP:
		size = c->be.size;
		break;
	case LX_TE_BLOCK_UPLOAD0:
		size = c->upload[0].size;
		break;
	case LX_TE_BLOCK_UPLOAD1:
		size = c->upload[1].size;
		break;
	case LX_TE_BLOCK_MCU0:
		size = c->mcu[0].size;
		break;
	case LX_TE_BLOCK_MCU1:
		size = c->mcu[1].size;
		break;
	case LX_TE_BLOCK_CIPLUS:
		size = c->ciplus.size;
		break;
	case LX_TE_BLOCK_A3:
		size = c->atsc3.size;
		break;
	case LX_TE_BLOCK_ARIB2:
		size = c->arib2.size;
		break;
	case LX_TE_BLOCK_DUMPER:
		size = c->dumper.size;
		break;
	case LX_TE_BLOCK_DSC0:
		size = c->dsc[0].size;
		break;
	case LX_TE_BLOCK_DSC1:
		size = c->dsc[1].size;
		break;
	default:
		size = 0;
		break;
	}
	return size;
}

int TE_REG_SetValue(LX_TE_REG_T *param)
{
	void __iomem *base;
	CHECK_PARAM(param->offset % 4 != 0, "offset is not aligned to 4byte\n");
	CHECK_PARAM(param->offset >= TE_REG_GetSize(param->block),
		    "offset is out of bounds\n");

	base = TE_REG_GetBaseAddr(param->block);
	if (!base)
		return -EINVAL;

	TE_WRITE32((uintptr_t)base + param->offset, param->value);

	return 0;
}

int TE_REG_GetValue(LX_TE_REG_T *param)
{
	void __iomem *base;
	CHECK_PARAM(param->offset % 4 != 0, "offset is not aligned to 4byte\n");
	CHECK_PARAM(param->offset >= TE_REG_GetSize(param->block),
		    "offset is out of bounds\n");

	base = TE_REG_GetBaseAddr(param->block);
	if (!base)
		return -EINVAL;

	param->value = TE_READ32((uintptr_t)base + param->offset);

	return 0;
}

int TE_REG_EnableLogMask(enum te_reg_log_bit bit)
{
	if (bit > 31 || bit < 0)
		return -EINVAL;

	g_te_reg_log_mask |= (1 << bit);

	return 0;
}

int TE_REG_DisableLogMask(enum te_reg_log_bit bit)
{
	if (bit > 31 || bit < 0)
		return -EINVAL;

	g_te_reg_log_mask &= ~(1 << bit);

	return 0;
}

int TE_REG_SetLogMask(u32 mask)
{
	g_te_reg_log_mask = mask;
	return 0;
}

u32 TE_REG_GetLogMask(void)
{
	return g_te_reg_log_mask;
}

void te_reg_dump(LX_TE_BLOCK_T block, printf_func_t prfn, void *arg)
{
	u32 offset, size, value;
	uintptr_t addr;

	addr = (uintptr_t)TE_REG_GetBaseAddr(block);
	size = TE_REG_GetSize(block);

	if (!addr || !size)
		return;

	for (offset = 0; offset < size; offset += 4) {
		value = TE_READ32(addr + offset);

		if ((offset % 16) == 0) {
			if (offset == 0)
				prfn(arg, "%04x : ", offset);
			else
				prfn(arg, "\n%04x : ", offset);
		}
		prfn(arg, "%08x ", value);
	}
	prfn(arg, "\n");
}

u32 te_reg_bits_to_type(const struct reg_bit_type_conv *list, u32 size, u32 v)
{
	int i;
	u32 type;
	const struct reg_bit_type_conv *c;

	type = 0;
	for (i = 0; i < size; i++) {
		c = &list[i];
		if (v & c->bit) {
			type |= c->type;
		}
	}

	return type;
}

u32 te_reg_type_to_bits(const struct reg_bit_type_conv *list, u32 size, u32 v)
{
	int i;
	u32 bits;
	const struct reg_bit_type_conv *c;

	bits = 0;
	for (i = 0; i < size; i++) {
		c = &list[i];
		if (v & c->type) {
			bits |= c->bit;
		}
	}

	return bits;
}

const struct te_sub_driver te_reg_driver = {
	.name = "te_reg",
	.early_init = reg_init,
	.release = reg_release,
};
