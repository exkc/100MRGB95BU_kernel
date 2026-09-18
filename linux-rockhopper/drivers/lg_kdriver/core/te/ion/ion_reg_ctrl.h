#ifndef _ION_REG_CTRL_H_
#define _ION_REG_CTRL_H_

#include <linux/types.h>
#include "sys_reg_base.h"
#include "ion_reg_db.h"

/* include either ion_io_reg.h or ion_ci_reg.h for TX operation
 * RX will use common CTOP register access
 */

/* the structure info for phys is only used for address calculation
 * there is no actual memory spaces
 */
struct ctop_reg_ctrl {
	union {
		u32 *addr;
		CTOP_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile CTOP_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct sadc_reg_ctrl {
	union {
		u32 *addr;
		volatile SADC_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile SADC_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct mcrg_reg_ctrl {
	union {
		u32 *addr;
		ION_MCRG_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile ION_MCRG_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct bnd_reg_ctrl {
	union {
		u32 *addr;
		BND_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile BND_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct scrg_reg_ctrl {
	union {
		u32 *addr;
		ION_SCRG_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile ION_SCRG_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct srds12to3_reg_ctrl {
	union {
		u32 *addr;
		SRDS12TO3_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile SRDS12TO3_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct srds32to1_reg_ctrl {
	union {
		u32 *addr;
		SRDS32TO1_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile SRDS32TO1_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct iomux_ctrl_reg_ctrl {
	union {
		u32 *addr;
		IOMUX_CTRL_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile IOMUX_CTRL_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct spi_to_ahb_reg_ctrl {
	union {
		u32 *addr;
		SPI_TO_AHB_REG_T *reg;
	} shdw;

	union {
		u32 *addr;
		volatile SPI_TO_AHB_REG_T *reg;
	} phys;

	u8 idx;
	u32 size;
	bool is_ctop;
};

struct ion_reg_ctrl {
	struct ctop_reg_ctrl top;
	struct sadc_reg_ctrl sadc[2];
	struct mcrg_reg_ctrl mcrg;
	struct bnd_reg_ctrl bnd;
	struct scrg_reg_ctrl scrg;
	struct srds12to3_reg_ctrl srds12to3;
	struct srds32to1_reg_ctrl srds32to1[2];
	struct iomux_ctrl_reg_ctrl iomux_ctrl;
	struct spi_to_ahb_reg_ctrl spi_to_ahb;
	bool en;
};

#define INIT_REG_CTRL(_c_, _i_, _a_, _s_)                 \
	do {                                              \
		_c_.phys.addr = (u32 *)_a_;               \
		_c_.is_ctop = false;                      \
		_c_.idx = _i_;                            \
                                                          \
		_c_.shdw.addr = kzalloc(_s_, GFP_KERNEL); \
		if (!(_c_).shdw.addr) {                   \
			log_error("kmalloc fail\n");      \
			return -ENOMEM;                   \
		}                                         \
                                                          \
		_c_.size = _s_;                           \
	} while (0)

#define UNINIT_REG_CTRL(_c_)          \
	do {                          \
		kfree(_c_.shdw.addr); \
	} while (0)

#define TX_TOP_REG_SHDW (TX_ION.top.shdw.reg)
#define TX_TOP_REG_PHYS (TX_ION.top.phys.reg)

#define TX_TOP_RdFL(_d, _r) TX_RdFL(_d, TX_TOP_REG_SHDW, TX_TOP_REG_PHYS, _r)
#define TX_TOP_WrFL(_d, _r) TX_WrFL(_d, TX_TOP_REG_SHDW, TX_TOP_REG_PHYS, _r)
#define TX_TOP_Wr01(_d, _r, _f01, _v01) \
	TX_Wr01(_d, TX_TOP_REG_SHDW, _r, _f01, _v01)
#define TX_TOP_Rd01(_d, _r, _f01, _v01) \
	TX_Rd01(_d, TX_TOP_REG_SHDW, _r, _f01, _v01)

#define TX_MCRG_REG_SHDW (TX_ION.mcrg.shdw.reg)
#define TX_MCRG_REG_PHYS (TX_ION.mcrg.phys.reg)

#define TX_MCRG_RdFL(_d, _r) TX_RdFL(_d, TX_MCRG_REG_SHDW, TX_MCRG_REG_PHYS, _r)
#define TX_MCRG_WrFL(_d, _r) TX_WrFL(_d, TX_MCRG_REG_SHDW, TX_MCRG_REG_PHYS, _r)
#define TX_MCRG_Wr01(_d, _r, _f01, _v01) \
	TX_Wr01(_d, TX_MCRG_REG_SHDW, _r, _f01, _v01)
#define TX_MCRG_Rd01(_d, _r, _f01, _v01) \
	TX_Rd01(_d, TX_MCRG_REG_SHDW, _r, _f01, _v01)

#define TX_SCRG_REG_SHDW (TX_ION.scrg.shdw.reg)
#define TX_SCRG_REG_PHYS (TX_ION.scrg.phys.reg)

#define TX_SCRG_RdFL(_d, _r) TX_RdFL(_d, TX_SCRG_REG_SHDW, TX_SCRG_REG_PHYS, _r)
#define TX_SCRG_WrFL(_d, _r) TX_WrFL(_d, TX_SCRG_REG_SHDW, TX_SCRG_REG_PHYS, _r)
#define TX_SCRG_Wr01(_d, _r, _f01, _v01) \
	TX_Wr01(_d, TX_SCRG_REG_SHDW, _r, _f01, _v01)
#define TX_SCRG_Rd01(_d, _r, _f01, _v01) \
	TX_Rd01(_d, TX_SCRG_REG_SHDW, _r, _f01, _v01)

#define TX_SRDS12TO3_REG_SHDW (TX_ION.srds12to3.shdw.reg)
#define TX_SRDS12TO3_REG_PHYS (TX_ION.srds12to3.phys.reg)

#define TX_SRDS12TO3_RdFL(_d, _r) \
	TX_RdFL(_d, TX_SRDS12TO3_REG_SHDW, TX_SRDS12TO3_REG_PHYS, _r)
#define TX_SRDS12TO3_WrFL(_d, _r) \
	TX_WrFL(_d, TX_SRDS12TO3_REG_SHDW, TX_SRDS12TO3_REG_PHYS, _r)
#define TX_SRDS12TO3_Wr01(_d, _r, _f01, _v01) \
	TX_Wr01(_d, TX_SRDS12TO3_REG_SHDW, _r, _f01, _v01)
#define TX_SRDS12TO3_Rd01(_d, _r, _f01, _v01) \
	TX_Rd01(_d, TX_SRDS12TO3_REG_SHDW, _r, _f01, _v01)

#define TX_IOMUX_CTRL_REG_SHDW (TX_ION.iomux_ctrl.shdw.reg)
#define TX_IOMUX_CTRL_REG_PHYS (TX_ION.iomux_ctrl.phys.reg)

#define TX_IOMUX_CTRL_RdFL(_d, _r) \
	TX_RdFL(_d, TX_IOMUX_CTRL_REG_SHDW, TX_IOMUX_CTRL_REG_PHYS, _r)
#define TX_IOMUX_CTRL_WrFL(_d, _r) \
	TX_WrFL(_d, TX_IOMUX_CTRL_REG_SHDW, TX_IOMUX_CTRL_REG_PHYS, _r)
#define TX_IOMUX_CTRL_Wr01(_d, _r, _f01, _v01) \
	TX_Wr01(_d, TX_IOMUX_CTRL_REG_SHDW, _r, _f01, _v01)
#define TX_IOMUX_CTRL_Rd01(_d, _r, _f01, _v01) \
	TX_Rd01(_d, TX_IOMUX_CTRL_REG_SHDW, _r, _f01, _v01)

#define TX_SPI_TO_AHB_REG_SHDW (TX_ION.spi_to_ahb.shdw.reg)
#define TX_SPI_TO_AHB_REG_PHYS (TX_ION.spi_to_ahb.phys.reg)

#define TX_SPI_TO_AHB_RdFL(_d, _r) \
	TX_RdFL(_d, TX_SPI_TO_AHB_REG_SHDW, TX_SPI_TO_AHB_REG_PHYS, _r)
#define TX_SPI_TO_AHB_WrFL(_d, _r) \
	TX_WrFL(_d, TX_SPI_TO_AHB_REG_SHDW, TX_SPI_TO_AHB_REG_PHYS, _r)
#define TX_SPI_TO_AHB_Wr01(_d, _r, _f01, _v01) \
	TX_Wr01(_d, TX_SPI_TO_AHB_REG_SHDW, _r, _f01, _v01)
#define TX_SPI_TO_AHB_Rd01(_d, _r, _f01, _v01) \
	TX_Rd01(_d, TX_SPI_TO_AHB_REG_SHDW, _r, _f01, _v01)

#endif //_ION_REG_CTRL_H_
