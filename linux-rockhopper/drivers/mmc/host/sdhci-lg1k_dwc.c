/*
 * drivers/mmc/host/sdhci-lg1k.c
 *
 * Support of SDHCI platform devices for lg115x
 *
 * Copyright (C) 2013 LG Electronics
 *
 * Author: Chanho Min <chanho.min@lge.com>
 *             Hankyung Yu <hankyung.yu@lge.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/dma-mapping.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/sizes.h>
#include <linux/delay.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/host.h>

#include "sdhci-pltfm.h"
#include "sdhci-lg1k.h"
#ifdef CONFIG_MMC_CQHCI
#include "cqhci.h"
#endif

#define BOUNDARY_OK(addr, len) \
	((addr | (SZ_128M - 1)) == ((addr + len - 1) | (SZ_128M - 1)))

static const struct of_device_id sdhci_lg1k_dwc_dt_ids[];

static inline struct sdhci_lg1k_drv_data *sdhci_lg1k_dwc_get_driver_data(
			struct platform_device *pdev)
{
#ifdef CONFIG_OF
	if (pdev->dev.of_node) {
		const struct of_device_id *match;
		match = of_match_node(sdhci_lg1k_dwc_dt_ids, pdev->dev.of_node);
		return (struct sdhci_lg1k_drv_data *)match->data;
	}
#endif
	return (struct sdhci_lg1k_drv_data *)
			platform_get_device_id(pdev)->driver_data;
}

/*
 * If DMA addr spans 128MB boundary, we split the DMA transfer into two
 * so that each DMA transfer doesn't exceed the boundary.
 */
static void lg1k_dwc_adma_write_desc(struct sdhci_host *host, void **desc,
				     dma_addr_t addr, int len, unsigned int cmd)
{
	int tmplen, offset;

	if (addr >= 0x100000000) {
		pr_err("EMMC : OVER 4GB ADDRESS 0x%llx\n", addr);
	}

	if (likely(!len || BOUNDARY_OK(addr, len))) {
		sdhci_adma_write_desc(host, desc, addr, len, cmd);
		return;
	}

	offset = addr & (SZ_128M - 1);
	tmplen = SZ_128M - offset;
	sdhci_adma_write_desc(host, desc, addr, tmplen, cmd);

	addr += tmplen;
	len -= tmplen;
	sdhci_adma_write_desc(host, desc, addr, len, cmd);
}

static void lg1k_dwc_set_tran_desc(struct cqhci_host *cq_host, u8 **desc,
						dma_addr_t addr, int len, bool end, bool dma64)
{
	int tmplen, offset;

	if (likely(!len || BOUNDARY_OK(addr, len))) {
		cqhci_set_tran_desc(*desc, addr, len, end, dma64);
		return;
	}

	offset = addr & (SZ_128M - 1);
	tmplen = SZ_128M - offset;
	cqhci_set_tran_desc(*desc, addr, tmplen, false, dma64);

	addr += tmplen;
	len -= tmplen;
	*desc += cq_host->trans_desc_len;
	cqhci_set_tran_desc(*desc, addr, len, end, dma64);
}

#ifdef CONFIG_OF
#define SDHCI_DS_50OHM_SYNOPSYS		0x8
#define SDHCI_CTRL_HS400_SYNOPSYS	0x0007

#define EMMC_VENDOR1_BASE			0x100
#define _MSHC_CTRL_R				0x8
#define _MMC_CTRL_R					0x2c
#define _AT_CTRL_R					0x40
#define _AT_STAT_R					0x44

#define EMMC_CMDQ_BASE				0x200
#define EMMC_VENDOR2_BASE			0x300
#define _PHY_CNFG					0x00
#define _SDCLKDL_CNFG				0x1c
#define _SMPLDL_CNFG				0x20
#define _DLL_CTRL_CNFG 				0x24
#define _DLL_DLCNFG_OFFST_MSTTSTDC	0x28
#define _DLL_STAT_BTCNFG 			0x2c

#define CLOCK_NOT_INVERT			0
#define CLOCK_INVERT				1

#define LG1K_DWC_CLOCK_ALL			0
#define LG1K_DWC_CLOCK_SD			1


static struct sdhci_lg1k_drv_data lg1k_51_dwc_drv_data = {
	.host_rev = EMMC_HOST_51,
	.pm_enable = 1,
};

static inline struct sdhci_lg1k_drv_data *lg1k_dwc_get_drv_data(void)
{
	return (struct sdhci_lg1k_drv_data *)&lg1k_51_dwc_drv_data;
}

static void _lg1k_dwc_regdump(	void __iomem *memp,
								unsigned int size, unsigned int offset)
{
	unsigned int i;

	for (i = 0; i < size; i += 16) {
		pr_info("0x%02X : 0x%08X 0x%08X 0x%08X 0x%08X\n",
			i + offset,
			readl(memp + i + offset + 0),
			readl(memp + i + offset + 4),
			readl(memp + i + offset + 8),
			readl(memp + i + offset + 12));
	}
}

static void lg1k_dwc_regdump(struct sdhci_host *host)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

#define	REG_BASE_0_OFFSET 0
#define	REG_BASE_1_OFFSET 0x100
#define	REG_BASE_2_OFFSET 0x200
#define	REG_BASE_3_OFFSET 0x300

#define	REG_BASE_0_SIZE 96
#define	REG_BASE_1_SIZE 96
#define	REG_BASE_2_SIZE 96
#define	REG_BASE_3_SIZE 64

#define	REG_TOP_0_OFFSET 0
#define	REG_TOP_1_OFFSET 0x60

#define	REG_TOP_0_SIZE 32
#define	REG_TOP_1_SIZE 32

	pr_info("LG1K_DWC REG DUMP ------\n");
	_lg1k_dwc_regdump(host->ioaddr, REG_BASE_0_SIZE, REG_BASE_0_OFFSET);
	_lg1k_dwc_regdump(host->ioaddr, REG_BASE_1_SIZE, REG_BASE_1_OFFSET);
	_lg1k_dwc_regdump(host->ioaddr, REG_BASE_2_SIZE, REG_BASE_2_OFFSET);
	_lg1k_dwc_regdump(host->ioaddr, REG_BASE_3_SIZE, REG_BASE_3_OFFSET);
	pr_info("LG1K_DWC TOP DUMP ------\n");
	_lg1k_dwc_regdump(drv_data->top_reg, REG_TOP_0_SIZE, REG_TOP_0_OFFSET);
	_lg1k_dwc_regdump(drv_data->top_reg, REG_TOP_1_SIZE, REG_TOP_1_OFFSET);
	pr_info("------------------------\n\n");
}

static void lg1k_dwc_clock_disable(struct sdhci_host *host, unsigned int mode)
{
	unsigned int delay = 30;

	if (sdhci_lg1k_get_inited(host))
		delay = 1;

	udelay(1);
	sdhci_lg1k_bit_clear(host, SDHCI_CLOCK_CONTROL, 2);
	udelay(delay);
	if (mode == LG1K_DWC_CLOCK_ALL) {
		sdhci_lg1k_bit_clear(host, SDHCI_CLOCK_CONTROL, 0);
		udelay(delay);
	}
}

static void lg1k_dwc_clock_enable(struct sdhci_host *host, unsigned int mode)
{
	unsigned int delay = 30;
	unsigned long timeout;

	if (sdhci_lg1k_get_inited(host))
		delay = 1;

	if (mode == LG1K_DWC_CLOCK_ALL) {
		sdhci_lg1k_bit_set(host, SDHCI_CLOCK_CONTROL, 0);
		udelay(delay);
	}
	sdhci_lg1k_bit_set(host, SDHCI_CLOCK_CONTROL, 2);
	udelay(delay);

	timeout = 50000;
	while (!(sdhci_readw(host, SDHCI_CLOCK_CONTROL)
		& SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			return;
		}
		timeout--;
		udelay(1);
	}
}

static void lg1k_dwc_clock_OnOff(struct sdhci_host *host, unsigned int on)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	unsigned long flags;

	spin_lock_irqsave(&drv_data->lock, flags);

	if (on & 1) {
		if (drv_data->cg_count == 0)
			lg1k_dwc_clock_enable(host, LG1K_DWC_CLOCK_SD);
		drv_data->cg_count++;
	} else {
		drv_data->cg_count--;
		if (drv_data->cg_count == 0)
			lg1k_dwc_clock_disable(host, LG1K_DWC_CLOCK_SD);
	}

	spin_unlock_irqrestore(&drv_data->lock, flags);
}

static u32 lg1k_dwc_readl(struct sdhci_host *host, int reg)
{
	u32 ret;

	ret = sdhci_lg1k_readl(host, reg);
	/*
	synopsys ip
	When cmd timeout occurs, cmd complete occurs within 5clock
	5clock at 300Khz is 17 microseconds.
	*/
	if ((reg == SDHCI_INT_STATUS) && ((ret & 0x18000) == 0x18000)) {
		udelay(17);
		ret = sdhci_lg1k_readl(host, reg);
	}

	/* don't support 64bi address for lg1212 */
	if (reg == SDHCI_CAPABILITIES)
		ret &= ~SDHCI_CAN_64BIT;

	return ret;
}

static void lg1k_dwc_writel(struct sdhci_host *host, u32 val, int reg)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	unsigned int cmdmode = 0;

	if ((reg == SDHCI_INT_STATUS) && (drv_data->hw_cg == 0))
	{
		/* data not present, don't busy check */
		cmdmode = (readl(host->ioaddr + SDHCI_TRANSFER_MODE) >> 16) & 0x23;
		if (cmdmode < 0x03)
			drv_data->xfer_complete |= 2;

		/* clock off when error occur */
		if (val & 0xffff0000)
			drv_data->xfer_complete = 3;

		if (val & 0x3)
			drv_data->xfer_complete |= (val & 0x3);
	}

	writel(val, host->ioaddr + reg);

	if ((reg == SDHCI_INT_STATUS) && (drv_data->hw_cg == 0))
	{
		if (drv_data->xfer_complete == 3) {
			lg1k_dwc_clock_OnOff(host, 0);
			drv_data->xfer_complete = 0;
		}
	}
}

static void lg1k_dwc_writew(struct sdhci_host *host, u16 val, int reg)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	if ((reg == SDHCI_COMMAND) && (drv_data->hw_cg == 0)) {
		drv_data->xfer_complete = 0;
		lg1k_dwc_clock_OnOff(host, 1);
	}

	if (reg == SDHCI_TRANSFER_MODE) {
		/*
		The following bits must be set in xfer_mode for CMDQ operation
		(multiblk_en[5] = 1, blk_cnt_en[1] = 0, dma_en[0] = 1)
		xfer_mode cannot be set alone and must be set with cmd reg
		*/
		if (drv_data->cqe_trigger == 1)
			val |= SDHCI_TRNS_MULTI;

		drv_data->cqe_trigger = 0;
	} else if (reg == SDHCI_COMMAND) {
		if ((val == 0x061b) &&
			 (sdhci_lg1k_readl(host, SDHCI_ARGUMENT) == 0x030f0101))
				drv_data->cqe_trigger = 1;
		else
			drv_data->cqe_trigger = 0;
	}

	sdhci_lg1k_writew(host, val, reg);
}

static void lg1k_dwc_out_phase(struct sdhci_host *host, unsigned int invert)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	unsigned int reg = 0;

#define TOP_CLOCK_CONTROL 0x18

	reg = readl(drv_data->top_reg + TOP_CLOCK_CONTROL);
	/* not inverting gated cclk_tx applied to EMMC */

	if (invert == CLOCK_NOT_INVERT)
		reg |= 0x1;
	else
		reg &= 0xfffffffe;

	writel(reg, drv_data->top_reg + TOP_CLOCK_CONTROL);
}

static void lg1k_dwc_otap_disable(struct sdhci_host *host)
{
	sdhci_writel(host, 0x00000200, EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);
	lg1k_dwc_out_phase(host, CLOCK_INVERT);
}

static void lg1k_dwc_itap_disable(struct sdhci_host *host)
{
	sdhci_writel(host, 0x0, EMMC_VENDOR1_BASE + _AT_CTRL_R);
	sdhci_writel(host, 0x0, EMMC_VENDOR1_BASE + _AT_STAT_R);

	sdhci_writel(host, 0x1A, EMMC_VENDOR2_BASE + _SMPLDL_CNFG);
}

static void lg1k_dwc_set_intap(struct sdhci_host *host, unsigned int in)
{
	unsigned int delayconfig = 0x18;

	/* Setup RX delay line
	  enable S/W tune & enable Tune Clk Stop */
	sdhci_writel(host, 0x00010010, EMMC_VENDOR1_BASE + _AT_CTRL_R);

	if (in >= 128) {
		in = in - 128;
		delayconfig = 0x19;
	}

	/* set RX delay code to 2 */
	sdhci_writel(host, in, EMMC_VENDOR1_BASE + _AT_STAT_R);

	/* through delayline &	input config 2 */
	sdhci_writel(host, delayconfig, EMMC_VENDOR2_BASE + _SMPLDL_CNFG);
}

static void lg1k_dwc_set_outtap(struct sdhci_host *host, unsigned int out)
{
	unsigned int reg;

	/* setup TX delay line */
	sdhci_writel(host, 0x00001000, EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	reg = (out << 16) + 0x1000;
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	reg = (out << 16);
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	/* not inverting gated cclk_tx applied to EMMC */
	lg1k_dwc_out_phase(host, CLOCK_NOT_INVERT);
}

static void lg1k_dwc_dll_init(struct sdhci_host *host)
{
	unsigned int reg;

	/* DLL slaves update delay input */
	sdhci_writel(host, 0x00002000, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);

	/* M/S DLL config (input clock select) */
	sdhci_writel(host, 0x00000060, EMMC_VENDOR2_BASE + _DLL_DLCNFG_OFFST_MSTTSTDC);

	/* DLL Load Val for revaldifation of lock */
	sdhci_writel(host, 0x00003000, EMMC_VENDOR2_BASE + _DLL_STAT_BTCNFG);

	reg = sdhci_readl(host, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
	reg &= 0x0000ffff;
	reg |= (10 << 16);
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
}

static void lg1k_dwc_dll_enable(struct sdhci_host *host)
{
	unsigned int dll_lock;
	unsigned int timeout = 10;
	unsigned int reg;

	sdhci_writel(host, 0x00004E30, EMMC_VENDOR2_BASE + _DLL_STAT_BTCNFG);

	reg = sdhci_readl(host, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
	reg &= 0xffff0000;
	reg |= 0x2501;
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);

	while(1){
		dll_lock = sdhci_readl(host, EMMC_VENDOR2_BASE + _DLL_STAT_BTCNFG);
		if(dll_lock & 0x00010000)
			break;

		if (timeout == 0) {
			pr_err("EMMC : DLL LOCK ERR\n");
			return;
		}

		timeout--;
		udelay(1000);
	}
}

/*
driver strength set
*/
static void lg1k_dwc_set_ds (struct sdhci_host *host, unsigned int ds)
{
	unsigned int reg;

	reg = sdhci_readl(host, EMMC_VENDOR2_BASE + _PHY_CNFG);
	reg &= 0xff00ffff;
	reg |= ((ds << 16) + (ds << 20));
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _PHY_CNFG);

	return;
}

/*
enhanced data strobe set
*/
static int lg1k_dwc_set_eds (struct sdhci_host *host, unsigned int onoff)
{
	unsigned int reg;
#define _EMMC_EDS_ENABLE				0x100

	reg = sdhci_readl(host, EMMC_VENDOR1_BASE + _MMC_CTRL_R);
	if (onoff == 0)
		reg &= ~_EMMC_EDS_ENABLE;
	else
		reg |= _EMMC_EDS_ENABLE;
	sdhci_writel(host, reg, EMMC_VENDOR1_BASE + _MMC_CTRL_R);

	return 0;
}

static void lg1k_dwc_reset_cmddata(struct sdhci_host *host)
{
	unsigned int timeout = 100;
	unsigned int reg;

	/* you must cmd & data line reset after clock change */
#define EMMC_CMD_RESET		25
#define EMMC_DATA_RESET		26

	sdhci_lg1k_bit_set(host, SDHCI_CLOCK_CONTROL, EMMC_CMD_RESET);
	mdelay(1);
	sdhci_lg1k_bit_set(host, SDHCI_CLOCK_CONTROL, EMMC_DATA_RESET);
	mdelay(1);

	while(1) {
		reg = sdhci_readl(host, SDHCI_CLOCK_CONTROL);
		if ((reg & 0x06000000) == 0)
			break;

		if (timeout == 0) {
			pr_err("EMMC : CMD/DATA Reset Timeout\n");
			lg1k_dwc_regdump(host);
			return;
		}

		timeout--;
		udelay(1000);
	}
}

static void lg1k_dwc_set_strobe(struct sdhci_host *host)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	unsigned int reg;
	unsigned int offset;

	if ((drv_data->strb & 0x80000000) == 0)
		return;

	offset = drv_data->strb & 0xff;

	sdhci_writel(host, 0x0002, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
	sdhci_writel(host, 0x1F60, EMMC_VENDOR2_BASE + _DLL_DLCNFG_OFFST_MSTTSTDC);

	reg = sdhci_readl(host, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
	reg |= 0x4;
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);

	reg = sdhci_readl(host, EMMC_VENDOR2_BASE + _DLL_DLCNFG_OFFST_MSTTSTDC);
	reg &= 0xFFFF00FF;
	reg |= (offset << 8);
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _DLL_DLCNFG_OFFST_MSTTSTDC);

	reg = sdhci_readl(host, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
	reg &= 0xFFFFFFFB;
	sdhci_writel(host, reg, EMMC_VENDOR2_BASE + _DLL_CTRL_CNFG);
}

static void lg1k_dwc_set_tap(struct sdhci_host *host)
{
	u16 ctrl2;
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	switch (ctrl2 & SDHCI_CTRL_UHS_MASK) {
		case SDHCI_CTRL_HS400_SYNOPSYS:
			lg1k_dwc_set_outtap(host, drv_data->hs400_out);
			lg1k_dwc_set_intap(host, drv_data->hs400_in);
			lg1k_dwc_dll_init(host);
			lg1k_dwc_clock_enable(host, LG1K_DWC_CLOCK_SD);
			lg1k_dwc_dll_enable(host);
			lg1k_dwc_clock_disable(host, LG1K_DWC_CLOCK_SD);
			lg1k_dwc_set_strobe(host);
			break;
		case SDHCI_CTRL_UHS_SDR104:
			if (host->clock <= 26000000) {
				lg1k_dwc_otap_disable(host);
				lg1k_dwc_itap_disable(host);
			} else if (host->clock > 52000000) {
				lg1k_dwc_set_outtap(host, drv_data->hs200_out);
				lg1k_dwc_set_intap(host, drv_data->hs200_in);
			} else {
				lg1k_dwc_set_outtap(host, drv_data->hs50_out);
				lg1k_dwc_set_intap(host, drv_data->hs50_in);
			}
			break;
		case SDHCI_CTRL_UHS_DDR50:
			lg1k_dwc_otap_disable(host);
			lg1k_dwc_set_intap(host, drv_data->hs50_in);
			break;
		case SDHCI_CTRL_UHS_SDR25:
			lg1k_dwc_otap_disable(host);
			lg1k_dwc_set_intap(host, drv_data->hs50_in);
			break;
		default:
			break;
	}
}

static void lg1k_dwc_unset_tap(struct sdhci_host *host)
{
	lg1k_dwc_itap_disable(host);
	lg1k_dwc_otap_disable(host);
}

static void lg1k_dwc_enhanced_strobe(struct mmc_host *host, struct mmc_ios *ios)
{
	struct sdhci_host *dwc_host;
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	if (ios->enhanced_strobe == false)
		return;

	dwc_host = mmc_priv(host);
	if (drv_data->host_rev == EMMC_HOST_51) {
		lg1k_dwc_set_eds(dwc_host, 1);
	}
}

static int lg1k_dwc_phy_setting(struct sdhci_host *host)
{
	unsigned int timeout = 10;
	unsigned int reg;
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	do {
		reg = sdhci_readl(host, EMMC_VENDOR2_BASE);
		if (reg == 0x2)
			break;

		mdelay(1);
		timeout--;

		if (timeout == 0) {
			pr_err("EMMC : DLL LOCK TIMEOUT\n");
			break;
		}
	} while (1);

	if (drv_data->internal_pullup == 1) {
		/*
			internal pull-up use
		*/
		sdhci_writel(host, 0x00880000, EMMC_VENDOR2_BASE);
		sdhci_writel(host, 0x04490449, EMMC_VENDOR2_BASE + 0x4);
		sdhci_writel(host, 0x04510441, EMMC_VENDOR2_BASE + 0x8);
		sdhci_writel(host, 0x00000449, EMMC_VENDOR2_BASE + 0xC);
		sdhci_writel(host, 0x00880001, EMMC_VENDOR2_BASE);
		sdhci_writel(host, 0x00000200, EMMC_VENDOR2_BASE + 0x1C);
		sdhci_writel(host, 0x0000001A, EMMC_VENDOR2_BASE + 0x20);
		sdhci_writel(host, 0x00000000, EMMC_VENDOR1_BASE + 0x40);
	} else {
		/*
			external pull-up use
		*/
		sdhci_writel(host, 0x00880000, EMMC_VENDOR2_BASE);
		sdhci_writel(host, 0x04410441, EMMC_VENDOR2_BASE + 0x4);
		sdhci_writel(host, 0x04410441, EMMC_VENDOR2_BASE + 0x8);
		sdhci_writel(host, 0x00000441, EMMC_VENDOR2_BASE + 0xC);
		sdhci_writel(host, 0x00880001, EMMC_VENDOR2_BASE);
		sdhci_writel(host, 0x00000200, EMMC_VENDOR2_BASE + 0x1C);
		sdhci_writel(host, 0x0000001A, EMMC_VENDOR2_BASE + 0x20);
		sdhci_writel(host, 0x00000000, EMMC_VENDOR1_BASE + 0x40);
	}
	return 0;
}

static unsigned int lg1k_dwc_get_clock(struct sdhci_host *host)
{
	unsigned int div;
	unsigned int reg;

#define DIV_LOW_MASK 0xFF00
#define DIV_HI_MASK  0xC0

	reg = sdhci_readl(host, SDHCI_CLOCK_CONTROL);
	div = ((reg & DIV_LOW_MASK) >> 8) +
		  ((reg & DIV_HI_MASK) << 2);

	if (div == 0)
		return host->max_clk;
	else {
		return (host->max_clk / (div * 2));
	}
}

static void lg1k_dwc_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	unsigned short reg;
	unsigned int pclock;

	if (clock == 0)
		return;

	lg1k_dwc_clock_disable(host, LG1K_DWC_CLOCK_ALL);

	sdhci_lg1k_set_clock(host, clock);

	lg1k_dwc_clock_disable(host, LG1K_DWC_CLOCK_SD);

	reg = sdhci_readw(host, SDHCI_HOST_CONTROL2) & SDHCI_CTRL_UHS_MASK;
	if (reg == SDHCI_CTRL_UHS_SDR12)
		lg1k_dwc_unset_tap(host);
	else
		lg1k_dwc_set_tap(host);

	if (clock >= 52000000)
		lg1k_dwc_set_ds(host, drv_data->host_ds);
	else
		lg1k_dwc_set_ds(host, SDHCI_DS_50OHM_SYNOPSYS);

	lg1k_dwc_clock_enable(host, LG1K_DWC_CLOCK_SD);

	mdelay(1);
	lg1k_dwc_reset_cmddata(host);

	pclock = lg1k_dwc_get_clock(host);
	if (pclock != drv_data->host_clock) {
		pr_info("emmc clock: EMMC: Clock changed to %u Hz from %u Hz\n",
		pclock, drv_data->host_clock);
		drv_data->host_clock = pclock;
	}
}

static void lg1k_dwc_set_clockgating(struct sdhci_host *host,
				     unsigned int onoff)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	u32 reg;

#define TOP_CLOCK_CONTROL 0x18

	reg = readl(drv_data->top_reg + TOP_CLOCK_CONTROL);
	if (onoff)
		reg |= 0x2;
	else
		reg &= 0xfffffffd;
	writel(reg, drv_data->top_reg + TOP_CLOCK_CONTROL);
}

static void lg1k_dwc_set_uhs_signaling(struct sdhci_host *host,
				       unsigned int uhs)
{
	u32 clock = 0;
	u16 overmode = 0;
	u16 ctrl2;
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	if (uhs == MMC_TIMING_MMC_HS400) {
		overmode = SDHCI_CTRL_HS400_SYNOPSYS;
		if (drv_data->hw_cg)
			lg1k_dwc_set_clockgating(host, 1);
	}

	clock = sdhci_lg1k_set_uhs_signaling(host, uhs, overmode);

	ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctrl2 |= SDHCI_CTRL_VDD_180;
	sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);

	if (clock) {
		lg1k_dwc_set_clock(host, clock);
		host->mmc->ios.clock = lg1k_dwc_get_clock(host);
		host->clock = lg1k_dwc_get_clock(host);
	}

	return;
}

void lg1k_dwc_syntop_reset_legacy(void)
{
	void __iomem *dwc_syntop = NULL;
	u32 offset = 0xc;
	u32 value = 0xf;
	u32 reg;

	if (of_machine_is_compatible("lge,lg1212")) {
#define O20_EMMC_CNTROLLER_SYNTOP	0xc9307000
		dwc_syntop = ioremap(O20_EMMC_CNTROLLER_SYNTOP, 4096);
		offset = 0x14;
		value = 0x1e;
	}

#define O22_EMMC_CNTROLLER_SYNTOP	0xc8050000
	if (of_machine_is_compatible("lge,lg1213"))
		dwc_syntop = ioremap(O22_EMMC_CNTROLLER_SYNTOP, 4096);

#define M23_EMMC_CNTROLLER_SYNTOP	0xc4750000
	if (of_machine_is_compatible("lge,lg1315"))
		dwc_syntop = ioremap(M23_EMMC_CNTROLLER_SYNTOP, 4096);

#define O24_EMMC_CNTROLLER_SYNTOP	0xC4240000
	if (of_machine_is_compatible("lge,lg1214"))
		dwc_syntop = ioremap(O24_EMMC_CNTROLLER_SYNTOP, 4096);

#define O26_EMMC_CNTROLLER_SYNTOP	0xC6210000
	if (of_machine_is_compatible("lge,lg1215"))
		dwc_syntop = ioremap(O26_EMMC_CNTROLLER_SYNTOP, 4096);

	if (dwc_syntop == NULL)
		return;

	writel(value, dwc_syntop + offset);
	mdelay(1);
	writel(0, dwc_syntop + offset);

	iounmap(dwc_syntop);
}

void lg1k_dwc_syntop_reset(void)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	void __iomem *dwc_syntop = NULL;
	u32 offset = 0x0;
	u32 base = 0x0;
	u32 reg;

	if (drv_data->reset_reg != 0) {
		offset = drv_data->reset_reg & 0xFFF;
		base = drv_data->reset_reg & 0xFFFFF000;
		dwc_syntop = ioremap(base, 4096);

		reg = readl(dwc_syntop + offset) | drv_data->reset_value;
		writel(reg, dwc_syntop + offset);
		mdelay(1);
		reg &= ~drv_data->reset_value;
		writel(reg, dwc_syntop + offset);

		iounmap(dwc_syntop);
	} else {
		lg1k_dwc_syntop_reset_legacy();
	}
}

static void lg1k_dwc_reset(struct sdhci_host *host, u8 mask)
{
	unsigned int reg;
	unsigned long timeout;

	lg1k_dwc_unset_tap(host);

	if (mask == SDHCI_RESET_ALL)
	{
		lg1k_dwc_syntop_reset();

		sdhci_lg1k_bit_clear(host, SDHCI_CLOCK_CONTROL, 2);
		mdelay(1);
		sdhci_lg1k_bit_clear(host, SDHCI_CLOCK_CONTROL, 0);
		mdelay(1);

		sdhci_writel(host, 0x01000000, SDHCI_CLOCK_CONTROL);
		/* Wait max 100 ms */
		timeout = 100;

		/* hw clears the bit when it's done */
		while (sdhci_readb(host, SDHCI_SOFTWARE_RESET) & mask) {
			if (timeout == 0) {
				pr_err("%s: Reset 0x%x never completed.\n",
					mmc_hostname(host->mmc), (int)mask);
				lg1k_dwc_regdump(host);
				return;
			}
			timeout--;
			mdelay(1);
		}
	}
	else
		sdhci_reset(host, mask);

	if (mask == SDHCI_RESET_ALL) {
		/* CARD IS EMMC SET */
		reg = sdhci_readl(host, EMMC_VENDOR1_BASE +  _MMC_CTRL_R);
		reg |= 0x1;
		sdhci_writel(host, reg, EMMC_VENDOR1_BASE +  _MMC_CTRL_R);

		/* 1.8v signaling must set */
		reg = sdhci_readl(host, SDHCI_AUTO_CMD_STATUS);
		reg |= (0x8 << 16);
		sdhci_writel(host, reg, SDHCI_AUTO_CMD_STATUS);

		lg1k_dwc_phy_setting(host);

		/* command conflict error check disable */
		reg = sdhci_readl(host, EMMC_VENDOR1_BASE +  _MSHC_CTRL_R);
		reg &= 0xfffffffe;
		sdhci_writel(host, reg, EMMC_VENDOR1_BASE +  _MSHC_CTRL_R);
	}
	return;
}

static int lg1k_dwc_select_drive_strength(struct mmc_card *card,
				 unsigned int max_dtr, int host_drv,
				 int card_drv, int *drv_type)
{
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	return drv_data->device_ds;
}

static int lg1k_dwc_execute_tuning(struct sdhci_host *host, unsigned int opcode)
{


	return 0;
}

/*
                 50ohm, 33ohm, 66ohm, 100ohm, 40ohm
standard table     0      1      2       3      4
synopsys table    0x8    0xe    0x4     0x0    0xc
*/
static unsigned int lg1k_dwc_ds_convert(unsigned int standard_ds)
{
	unsigned int dwc_ds[5] = {0x8, 0xe, 0x4, 0x0, 0xc};

	if (standard_ds >= 5)
		standard_ds = 0;

	return dwc_ds[standard_ds];
}

#ifdef CONFIG_MMC_CQHCI
static u32 lg1k_dwc_cqhci_irq(struct sdhci_host *host, u32 intmask)
{
	int cmd_error = 0;
	int data_error = 0;

	if (!sdhci_cqe_irq(host, intmask, &cmd_error, &data_error))
		return intmask;

	cqhci_irq(host->mmc, intmask, cmd_error, data_error);

	return 0;
}

static void sdhci_lg1k_dumpregs(struct mmc_host *mmc)
{
	sdhci_dumpregs(mmc_priv(mmc));
}

static void lg1k_dwc_cqe_enable(struct mmc_host *mmc)
{
	sdhci_cqe_enable(mmc);
}

static void lg1k_dwc_cqe_disable(struct mmc_host *mmc, bool recovery)
{
	sdhci_cqe_disable(mmc, recovery);
}

void lg1k_dwc_cqe_write_l(struct cqhci_host *host, u32 val, int reg)
{
	u32 temp;
	struct sdhci_host *sd_host = mmc_priv(host->mmc);
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();

	if (reg == CQHCI_VENDOR) {
		if (drv_data->hw_cg == 0) {
			if (val == CQHCI_EMMC_CLK_OFF)
				lg1k_dwc_clock_OnOff(sd_host, 0);
			else if (val == CQHCI_EMMC_CLK_ON)
				lg1k_dwc_clock_OnOff(sd_host, 1);
		}
		return;
	}

	if (reg == CQHCI_CTL) {
		if (val  == 0) {
			temp = cqhci_readl(host, CQHCI_CFG);
			temp |= 0x1;
			writel(temp, host->mmio + CQHCI_CFG);
		}
	}

	writel(val, host->mmio + reg);

	if (reg == CQHCI_CTL) {
		if (val == CQHCI_HALT) {
			temp = cqhci_readl(host, CQHCI_CFG);
			temp &= 0xfffffffe;
			writel(temp, host->mmio + CQHCI_CFG);
		}
	}
}

static const struct cqhci_host_ops sdhci_lg1k_cqhci_ops = {
	.write_l = lg1k_dwc_cqe_write_l,
	.disable = lg1k_dwc_cqe_disable,
	.enable	= lg1k_dwc_cqe_enable,
	.dumpregs = sdhci_lg1k_dumpregs,
	.set_tran_desc  = lg1k_dwc_set_tran_desc,
};
#endif

static void lg1k_dwc_platform_init(struct sdhci_host *host)
{
	struct platform_device *pdev = to_platform_device(host->mmc->parent);
	struct device_node *np = pdev->dev.of_node;
	struct sdhci_lg1k_drv_data *drv_data = sdhci_lg1k_dwc_get_driver_data(pdev);
	u32 intap_delay = 0;
	u32 outtap_delay = 0;
	u32 host_ds = 0;
	u32 cqe = 0;
	u32 caps = 0;
	u32 caps2 = 0;
	u32 op_mode = 0;
	u32 extra;
#ifdef CONFIG_MMC_CQHCI
	struct cqhci_host *cq_host;
#endif

	/*
	 * extra adma table cnt for cross 128M boundary handling.
	 */
	extra = DIV_ROUND_UP_ULL(dma_get_required_mask(&pdev->dev), SZ_128M);
	if (extra > SDHCI_MAX_SEGS)
		extra = SDHCI_MAX_SEGS;
	host->adma_table_cnt += extra;

	drv_data->top_reg = of_iomap(np, 1);

	of_property_read_u32(np, "op-mode", &op_mode);

	if (op_mode == 0) {
		caps |= MMC_CAP_UHS_DDR50 | MMC_CAP_NEED_RSP_BUSY;
		caps2 |= MMC_CAP2_HS400_1_8V | MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS400_ES;
	} else {
		/*
		 * FIXME: This will be moved to sdhci_read_caps
		 * host->quirks |= SDHCI_QUIRK_MISSING_CAPS;
		 * host->caps = 0x3c4dc381;
		 * host->caps1 = 0x08008077;
		 * host->quirks2 |= SDHCI_QUIRK2_BROKEN_HS200;
		 * host->quirks2 |= SDHCI_QUIRK2_BROKEN_DDR50;
		*/
		sdhci_read_caps(host);
	}

	caps |= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA;
	caps2 |= MMC_CAP2_FULL_PWR_CYCLE | MMC_CAP2_NO_SDIO | MMC_CAP2_NO_SD;

	if (!drv_data->top_reg) {
		dev_err(&pdev->dev, "Failed to map IO space\n");
		goto fail;
	}

	if (of_property_read_u32(np, "intap-delay", &intap_delay) < 0) {
		goto fail;
	}

	if (of_property_read_u32(np, "outtap-delay", &outtap_delay) < 0) {
		goto fail;
	}

	if (of_property_read_u32(np, "strobe", &drv_data->strb) < 0)
		drv_data->strb = 0;

	if (of_property_read_u32(np, "device-ds", &drv_data->device_ds) < 0)
		drv_data->device_ds = 0;

	if (of_property_read_u32(np, "host-ds", &host_ds) < 0)
		drv_data->host_ds = SDHCI_DS_50OHM_SYNOPSYS;
	else
		drv_data->host_ds = lg1k_dwc_ds_convert(host_ds);

	if (of_property_read_u32(np, "hw-clockgating", &drv_data->hw_cg) < 0)
		drv_data->hw_cg = 0;

	if (of_property_read_u32(np, "internal-pullup", &drv_data->internal_pullup) < 0)
		drv_data->internal_pullup = 0;

	if (of_property_read_u32(np, "reset-reg", &drv_data->reset_reg) < 0)
		drv_data->reset_reg = 0;

#define EMMC_DEFAULT_RESET_VALUE	0xf
	if (of_property_read_u32(np, "reset-value", &drv_data->reset_value) < 0)
		drv_data->reset_value = EMMC_DEFAULT_RESET_VALUE;

#ifdef CONFIG_MMC_CQHCI
	if (of_property_read_u32(np, "cqe-enable", &cqe) < 0)
		cqe = 0;

	if (cqe == 0x1)
		caps2 |= MMC_CAP2_CQE;
	else if (cqe == 0x3)
		caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
#endif

	host->mmc->caps |= caps;
	host->mmc->caps2 |= caps2;
	host->quirks2 |= SDHCI_QUIRK2_BROKEN_1_8V | SDHCI_QUIRK2_ACMD23_BROKEN;

	drv_data->cg_count = 0;
	drv_data->xfer_complete = 0;

	drv_data->hs50_out = outtap_delay & 0xFF;
	drv_data->hs200_out = (outtap_delay >> 16) & 0xFF;
	drv_data->hs400_out = (outtap_delay >> 24) & 0xFF;

	drv_data->hs50_in = intap_delay & 0xFF;
	drv_data->hs200_in = (intap_delay >> 16) & 0xFF;
	drv_data->hs400_in = (intap_delay >> 24) & 0xFF;

#ifdef CONFIG_MMC_CQHCI
	if (cqe) {
		cq_host = devm_kzalloc(host->mmc->parent,
					sizeof(*cq_host), GFP_KERNEL);

		cq_host->mmio = host->ioaddr + EMMC_CMDQ_BASE;
		cq_host->ops = &sdhci_lg1k_cqhci_ops;
	}
#endif

	spin_lock_init(&drv_data->lock);

	mmc_of_parse(host->mmc);

	host->mmc_host_ops.hs400_enhanced_strobe = lg1k_dwc_enhanced_strobe;

	host->mmc_host_ops.select_drive_strength = lg1k_dwc_select_drive_strength;

#ifdef CONFIG_MMC_CQHCI
	if (cqe)
		cqhci_init(cq_host, host->mmc, 0);
#endif
	return;

fail:
	host->quirks2 |= SDHCI_QUIRK2_BROKEN_HS200|SDHCI_QUIRK2_BROKEN_DDR50;
	iounmap(drv_data->top_reg);
}

static struct sdhci_ops lg1k_51_dwc_ops = {
	.platform_init = lg1k_dwc_platform_init,
	.set_clock = lg1k_dwc_set_clock,
	.reset = lg1k_dwc_reset,
	.adma_write_desc = lg1k_dwc_adma_write_desc,
	.set_bus_width = sdhci_set_bus_width,
	.get_min_clock = sdhci_lg1k_get_min_clock,
	.get_max_clock = sdhci_lg1k_get_max_clock,
	.set_uhs_signaling = lg1k_dwc_set_uhs_signaling,
	.platform_execute_tuning = lg1k_dwc_execute_tuning,
	.read_l = lg1k_dwc_readl,
	.read_w = sdhci_lg1k_readw,
	.read_b = sdhci_lg1k_readb,
	.write_l = lg1k_dwc_writel,
	.write_w = lg1k_dwc_writew,
	.write_b = sdhci_lg1k_writeb,
#ifdef CONFIG_MMC_CQHCI
	.irq = lg1k_dwc_cqhci_irq,
#endif
};


static struct sdhci_pltfm_data dwc_lg1k_51_pdata = {
	.ops  = &lg1k_51_dwc_ops,
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL
			| SDHCI_QUIRK_FORCE_BLK_SZ_2048
			| SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN
			| SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
};
#endif

static int sdhci_lg1k_dwc_probe(struct platform_device *pdev)
{
#ifdef CONFIG_OF
	int ret = -1;
	struct device_node *np = pdev->dev.of_node;
	if (of_device_is_compatible(np, "lge,lg1k-dwc-5.1"))
		ret = sdhci_pltfm_init_and_add_host(pdev, &dwc_lg1k_51_pdata, 0);
	else
		dev_err(&pdev->dev, "Can't find compatible device \n");

	return ret;
#endif
}

static void sdhci_lg1k_dwc_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	sdhci_pltfm_remove(pdev);

	clk_disable_unprepare(pltfm_host->clk);
}

static struct platform_device_id sdhci_lg1k_dwc_driver_ids[] = {
	{
		.name		= "sdhci-lg1k_dwc",
		.driver_data	= (kernel_ulong_t)&lg1k_51_dwc_drv_data,
	},
	{}
};
MODULE_DEVICE_TABLE(platform, sdhci_lg1k_dwc_driver_ids);

static const struct of_device_id sdhci_lg1k_dwc_dt_ids[] = {
	{ .compatible = "lge,lg1k-dwc-5.1",
		.data = (void *)&lg1k_51_dwc_drv_data },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, sdhci_lg1k_dwc_dt_ids);

#ifdef CONFIG_PM_SLEEP
static int lg1k_dwc_sdhci_suspend(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	struct mmc_host *mmc = host->mmc;
	int ret = 0;

	if (drv_data->pm_enable) {
#ifdef CONFIG_MMC_CQHCI
		if (mmc->caps2 & MMC_CAP2_CQE) {
			ret = cqhci_suspend(mmc);
			if (ret) {
				return ret;
			}
		}
#endif

		drv_data->cg_count = 0;
		drv_data->host_clock = 0;
		sdhci_lg1k_set_inited(host, 0);
		ret = sdhci_suspend_host(host);
	}

	return ret;
}

static int lg1k_dwc_sdhci_resume(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_lg1k_drv_data *drv_data = lg1k_dwc_get_drv_data();
	int ret = 0;

	if (drv_data->pm_enable) {
		sdhci_lg1k_set_inited(host, 0);
		ret = sdhci_resume_host(host);
		if (ret) {
			return ret;
	}

#ifdef CONFIG_MMC_CQHCI
		if (host->mmc->caps2 & MMC_CAP2_CQE) {
			ret = cqhci_resume(host->mmc);
		}
#endif
	}

	return ret;
}
#endif	/* CONFIG_PM_SLEEP */
SIMPLE_DEV_PM_OPS(lg1k_dwc_sdhci_pm_ops, lg1k_dwc_sdhci_suspend, lg1k_dwc_sdhci_resume);

static struct platform_driver sdhci_driver = {
	.id_table	= sdhci_lg1k_dwc_driver_ids,
	.driver = {
		.name	= "sdhci-lg1k_dwc",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(sdhci_lg1k_dwc_dt_ids),
		.pm = &lg1k_dwc_sdhci_pm_ops,
	},
	.probe		= sdhci_lg1k_dwc_probe,
	.remove_new	= sdhci_lg1k_dwc_remove,
};

module_platform_driver(sdhci_driver);

MODULE_DESCRIPTION("LG1XXX Secure Digital Host Controller Interface driver");
MODULE_AUTHOR("Chanho Min <chanho.min@lge.com>, "
	      "Hankyung Yu <hankyung.yu@lge.com>"
	      "Wonmin Jung <wonmin.jung@lge.com>");
MODULE_LICENSE("GPL v2");
