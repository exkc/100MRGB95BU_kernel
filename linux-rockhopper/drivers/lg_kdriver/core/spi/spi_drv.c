/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  main driver implementation for spi device.
 *	spi device will teach you how to make device driver with new platform.
 *
 *  author		ingyu.yang (ingyu.yang@lge.com)
 *  				jun.kong (jun.kong@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_spi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_SPI_DEVICE_READ_WRITE_FOPS
#undef	SPI_DRV_PRINT_ENABLE
//#define SPI_DRV_PRINT_ENABLE
//static void Debug_SPI_Print(void);


#define USE_KERNEL_RECV_IN_SLAVE

//#define USE_KERNELMEM_DIRESET

//#define USE_KERNELMEM_DIRESET_TX
/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include <asm/uaccess.h>
#include <linux/poll.h>
#include "os_util.h"
#include "base_device.h"
#include "base_types.h"
#include "spi_drv.h"
#include "gpio_core.h"
//#include "spi_reg.h"
//#include "spi_core.h"

#include <linux/spi/spi.h>
#include <linux/amba/pl022.h>
#include <asm/io.h>
#include <asm/memory.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
//#include <linux/malloc.h>




#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/amba/bus.h>
#include <linux/amba/pl022.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/dmaengine.h>
#include <linux/dma-mapping.h>
#include <linux/scatterlist.h>
#include <linux/pm_runtime.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/pinctrl/consumer.h>

//#include <linux/amba/pl080.h>
#include <linux/amba/pl08x.h>
#include <linux/device.h>
#include <linux/of_platform.h>

#include <asm/cacheflush.h>
#include "sys_regs.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

static DEFINE_MUTEX(spi_mutex);

#define SPI_COPY_FROM_USER(d,s,l) 							\
		do {												\
			if (copy_from_user((void*)d, (void *)s, l)) {	\
				SPI_ERROR("ioctl: copy_from_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)

#define SPI_COPY_FROM_USER_ER_FREE(d,s,l) 							\
		do {												\
			if (copy_from_user((void*)d, (void *)s, l)) {	\
				SPI_ERROR("ioctl: copy_from_user\n");		\
				kfree(d);								\
				return -EFAULT; 							\
			}												\
		} while(0)

#define SPI_COPY_TO_USER(d,s,l) 							\
		do {												\
			if (copy_to_user((void*)d, (void *)s, l)) { 	\
				SPI_ERROR("ioctl: copy_to_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)

void __iomem * spi_en_base =NULL;
static DEFINE_MUTEX (lock);
#define SPI_VALID_BUF_SIZE 0x8000
#define SPI_VALID_CH_NUM 0x3
#define SPIDRV_LOCK_INIT(dev)		OS_InitMutex(&dev->lock, OS_SEM_ATTR_DEFAULT)
#define SPIDRV_LOCK(dev)			OS_LockMutex(&dev->lock)
#define SPIDRV_UNLOCK(dev)		OS_UnlockMutex(&dev->lock)

#if 1
#define SSP_WRITE_BITS(reg, val, mask, sb) \
 ((reg) = (((reg) & ~(mask)) | (((val)<<(sb)) & (mask))))

/*
 * This macro is also used to define some default values.
 * It will just shift val by sb steps to the left and mask
 * the result with mask.
 */
#define GEN_MASK_BITS(val, mask, sb) \
 (((val)<<(sb)) & (mask))

#define DRIVE_TX		0
#define DO_NOT_DRIVE_TX		1

#define DO_NOT_QUEUE_DMA	0
#define QUEUE_DMA		1

#define RX_TRANSFER		1
#define TX_TRANSFER		2


#if 1
#define PL080_INT_STATUS			(0x00)
#define PL080_TC_STATUS				(0x04)
#define PL080_TC_CLEAR				(0x08)
#define PL080_ERR_STATUS			(0x0C)
#define PL080_ERR_CLEAR				(0x10)
#define PL080_RAW_TC_STATUS			(0x14)
#define PL080_RAW_ERR_STATUS			(0x18)
#define PL080_EN_CHAN				(0x1c)
#define PL080_SOFT_BREQ				(0x20)
#define PL080_SOFT_SREQ				(0x24)
#define PL080_SOFT_LBREQ			(0x28)
#define PL080_SOFT_LSREQ			(0x2C)

#define PL080_CONFIG				(0x30)
#define PL080_CONFIG_M2_BE			(1 << 2)
#define PL080_CONFIG_M1_BE			(1 << 1)
#define PL080_CONFIG_ENABLE			(1 << 0)

#define PL080_SYNC				(0x34)

/* Per channel configuration registers */


#define PL080_CH_SRC_ADDR			(0x00)
#define PL080_CH_DST_ADDR			(0x04)
#define PL080_CH_LLI				(0x08)
#define PL080_CH_CONTROL			(0x0C)
#define PL080_CH_CONFIG				(0x10)
#define PL080S_CH_CONTROL2			(0x10)
#define PL080S_CH_CONFIG			(0x14)

#define PL080_LLI_ADDR_MASK			(0x3fffffff << 2)
#define PL080_LLI_ADDR_SHIFT			(2)
#define PL080_LLI_LM_AHB2			(1 << 0)

#define PL080_CONTROL_TC_IRQ_EN			(1 << 31)
#define PL080_CONTROL_PROT_MASK			(0x7 << 28)
#define PL080_CONTROL_PROT_SHIFT		(28)
#define PL080_CONTROL_PROT_CACHE		(1 << 30)
#define PL080_CONTROL_PROT_BUFF			(1 << 29)
#define PL080_CONTROL_PROT_SYS			(1 << 28)
#define PL080_CONTROL_DST_INCR			(1 << 27)
#define PL080_CONTROL_SRC_INCR			(1 << 26)
#define PL080_CONTROL_DST_AHB2			(1 << 25)
#define PL080_CONTROL_SRC_AHB2			(1 << 24)
#define PL080_CONTROL_DWIDTH_MASK		(0x7 << 21)
#define PL080_CONTROL_DWIDTH_SHIFT		(21)
#define PL080_CONTROL_SWIDTH_MASK		(0x7 << 18)
#define PL080_CONTROL_SWIDTH_SHIFT		(18)
#define PL080_CONTROL_DB_SIZE_MASK		(0x7 << 15)
#define PL080_CONTROL_DB_SIZE_SHIFT		(15)
#define PL080_CONTROL_SB_SIZE_MASK		(0x7 << 12)
#define PL080_CONTROL_SB_SIZE_SHIFT		(12)
#define PL080_CONTROL_TRANSFER_SIZE_MASK	(0xfff << 0)
#define PL080S_CONTROL_TRANSFER_SIZE_MASK	(0x1ffffff << 0)
#define PL080_CONTROL_TRANSFER_SIZE_SHIFT	(0)

#define PL080_BSIZE_1				(0x0)
#define PL080_BSIZE_4				(0x1)
#define PL080_BSIZE_8				(0x2)
#define PL080_BSIZE_16				(0x3)
#define PL080_BSIZE_32				(0x4)
#define PL080_BSIZE_64				(0x5)
#define PL080_BSIZE_128				(0x6)
#define PL080_BSIZE_256				(0x7)

#define PL080_WIDTH_8BIT			(0x0)
#define PL080_WIDTH_16BIT			(0x1)
#define PL080_WIDTH_32BIT			(0x2)

#define PL080N_CONFIG_ITPROT			(1 << 20)
#define PL080N_CONFIG_SECPROT			(1 << 19)
#define PL080_CONFIG_HALT			(1 << 18)
#define PL080_CONFIG_ACTIVE			(1 << 17)  /* RO */
#define PL080_CONFIG_LOCK			(1 << 16)
#define PL080_CONFIG_TC_IRQ_MASK		(1 << 15)
#define PL080_CONFIG_ERR_IRQ_MASK		(1 << 14)
#define PL080_CONFIG_FLOW_CONTROL_MASK		(0x7 << 11)
#define PL080_CONFIG_FLOW_CONTROL_SHIFT		(11)
#define PL080_CONFIG_DST_SEL_MASK		(0xf << 6)
#define PL080_CONFIG_DST_SEL_SHIFT		(6)
#define PL080_CONFIG_SRC_SEL_MASK		(0xf << 1)
#define PL080_CONFIG_SRC_SEL_SHIFT		(1)
#define PL080_CONFIG_ENABLE			(1 << 0)

#define PL080_FLOW_MEM2MEM			(0x0)
#define PL080_FLOW_MEM2PER			(0x1)
#define PL080_FLOW_PER2MEM			(0x2)
#define PL080_FLOW_SRC2DST			(0x3)
#define PL080_FLOW_SRC2DST_DST			(0x4)
#define PL080_FLOW_MEM2PER_PER			(0x5)
#define PL080_FLOW_PER2MEM_PER			(0x6)
#define PL080_FLOW_SRC2DST_SRC			(0x7)

#endif
/*
 * Macros to access SSP Registers with their offsets
 */
#define SSP_CR0(r)	(r + 0x000)
#define SSP_CR1(r)	(r + 0x004)
#define SSP_DR(r)	(r + 0x008)
#define SSP_SR(r)	(r + 0x00C)
#define SSP_CPSR(r)	(r + 0x010)
#define SSP_IMSC(r)	(r + 0x014)
#define SSP_RIS(r)	(r + 0x018)
#define SSP_MIS(r)	(r + 0x01C)
#define SSP_ICR(r)	(r + 0x020)
#define SSP_DMACR(r)	(r + 0x024)
#define SSP_ITCR(r)	(r + 0x080)
#define SSP_ITIP(r)	(r + 0x084)
#define SSP_ITOP(r)	(r + 0x088)
#define SSP_TDR(r)	(r + 0x08C)

#define SSP_PID0(r)	(r + 0xFE0)
#define SSP_PID1(r)	(r + 0xFE4)
#define SSP_PID2(r)	(r + 0xFE8)
#define SSP_PID3(r)	(r + 0xFEC)

#define SSP_CID0(r)	(r + 0xFF0)
#define SSP_CID1(r)	(r + 0xFF4)
#define SSP_CID2(r)	(r + 0xFF8)
#define SSP_CID3(r)	(r + 0xFFC)

/*
 * SSP Control Register 0  - SSP_CR0
 */
#define SSP_CR0_MASK_DSS	(0x0FUL << 0)
#define SSP_CR0_MASK_FRF	(0x3UL << 4)
#define SSP_CR0_MASK_SPO	(0x1UL << 6)
#define SSP_CR0_MASK_SPH	(0x1UL << 7)
#define SSP_CR0_MASK_SCR	(0xFFUL << 8)

/*
 * The ST version of this block moves som bits
 * in SSP_CR0 and extends it to 32 bits
 */
#define SSP_CR0_MASK_DSS_ST	(0x1FUL << 0)
#define SSP_CR0_MASK_HALFDUP_ST	(0x1UL << 5)
#define SSP_CR0_MASK_CSS_ST	(0x1FUL << 16)
#define SSP_CR0_MASK_FRF_ST	(0x3UL << 21)

/*
 * SSP Control Register 0  - SSP_CR1
 */
#define SSP_CR1_MASK_LBM	(0x1UL << 0)
#define SSP_CR1_MASK_SSE	(0x1UL << 1)
#define SSP_CR1_MASK_MS		(0x1UL << 2)
#define SSP_CR1_MASK_SOD	(0x1UL << 3)

/*
 * The ST version of this block adds some bits
 * in SSP_CR1
 */
#define SSP_CR1_MASK_RENDN_ST	(0x1UL << 4)
#define SSP_CR1_MASK_TENDN_ST	(0x1UL << 5)
#define SSP_CR1_MASK_MWAIT_ST	(0x1UL << 6)
#define SSP_CR1_MASK_RXIFLSEL_ST (0x7UL << 7)
#define SSP_CR1_MASK_TXIFLSEL_ST (0x7UL << 10)
/* This one is only in the PL023 variant */
#define SSP_CR1_MASK_FBCLKDEL_ST (0x7UL << 13)

/*
 * SSP Status Register - SSP_SR
 */
#define SSP_SR_MASK_TFE		(0x1UL << 0) /* Transmit FIFO empty */
#define SSP_SR_MASK_TNF		(0x1UL << 1) /* Transmit FIFO not full */
#define SSP_SR_MASK_RNE		(0x1UL << 2) /* Receive FIFO not empty */
#define SSP_SR_MASK_RFF		(0x1UL << 3) /* Receive FIFO full */
#define SSP_SR_MASK_BSY		(0x1UL << 4) /* Busy Flag */

/*
 * SSP Clock Prescale Register  - SSP_CPSR
 */
#define SSP_CPSR_MASK_CPSDVSR	(0xFFUL << 0)

/*
 * SSP Interrupt Mask Set/Clear Register - SSP_IMSC
 */
#define SSP_IMSC_MASK_RORIM (0x1UL << 0) /* Receive Overrun Interrupt mask */
#define SSP_IMSC_MASK_RTIM  (0x1UL << 1) /* Receive timeout Interrupt mask */
#define SSP_IMSC_MASK_RXIM  (0x1UL << 2) /* Receive FIFO Interrupt mask */
#define SSP_IMSC_MASK_TXIM  (0x1UL << 3) /* Transmit FIFO Interrupt mask */

/*
 * SSP Raw Interrupt Status Register - SSP_RIS
 */
/* Receive Overrun Raw Interrupt status */
#define SSP_RIS_MASK_RORRIS		(0x1UL << 0)
/* Receive Timeout Raw Interrupt status */
#define SSP_RIS_MASK_RTRIS		(0x1UL << 1)
/* Receive FIFO Raw Interrupt status */
#define SSP_RIS_MASK_RXRIS		(0x1UL << 2)
/* Transmit FIFO Raw Interrupt status */
#define SSP_RIS_MASK_TXRIS		(0x1UL << 3)

/*
 * SSP Masked Interrupt Status Register - SSP_MIS
 */
/* Receive Overrun Masked Interrupt status */
#define SSP_MIS_MASK_RORMIS		(0x1UL << 0)
/* Receive Timeout Masked Interrupt status */
#define SSP_MIS_MASK_RTMIS		(0x1UL << 1)
/* Receive FIFO Masked Interrupt status */
#define SSP_MIS_MASK_RXMIS		(0x1UL << 2)
/* Transmit FIFO Masked Interrupt status */
#define SSP_MIS_MASK_TXMIS		(0x1UL << 3)

/*
 * SSP Interrupt Clear Register - SSP_ICR
 */
/* Receive Overrun Raw Clear Interrupt bit */
#define SSP_ICR_MASK_RORIC		(0x1UL << 0)
/* Receive Timeout Clear Interrupt bit */
#define SSP_ICR_MASK_RTIC		(0x1UL << 1)

/*
 * SSP DMA Control Register - SSP_DMACR
 */
/* Receive DMA Enable bit */
#define SSP_DMACR_MASK_RXDMAE		(0x1UL << 0)
/* Transmit DMA Enable bit */
#define SSP_DMACR_MASK_TXDMAE		(0x1UL << 1)

/*
 * SSP Integration Test control Register - SSP_ITCR
 */
#define SSP_ITCR_MASK_ITEN		(0x1UL << 0)
#define SSP_ITCR_MASK_TESTFIFO		(0x1UL << 1)

/*
 * SSP Integration Test Input Register - SSP_ITIP
 */
#define ITIP_MASK_SSPRXD		 (0x1UL << 0)
#define ITIP_MASK_SSPFSSIN		 (0x1UL << 1)
#define ITIP_MASK_SSPCLKIN		 (0x1UL << 2)
#define ITIP_MASK_RXDMAC		 (0x1UL << 3)
#define ITIP_MASK_TXDMAC		 (0x1UL << 4)
#define ITIP_MASK_SSPTXDIN		 (0x1UL << 5)

/*
 * SSP Integration Test output Register - SSP_ITOP
 */
#define ITOP_MASK_SSPTXD		 (0x1UL << 0)
#define ITOP_MASK_SSPFSSOUT		 (0x1UL << 1)
#define ITOP_MASK_SSPCLKOUT		 (0x1UL << 2)
#define ITOP_MASK_SSPOEn		 (0x1UL << 3)
#define ITOP_MASK_SSPCTLOEn		 (0x1UL << 4)
#define ITOP_MASK_RORINTR		 (0x1UL << 5)
#define ITOP_MASK_RTINTR		 (0x1UL << 6)
#define ITOP_MASK_RXINTR		 (0x1UL << 7)
#define ITOP_MASK_TXINTR		 (0x1UL << 8)
#define ITOP_MASK_INTR			 (0x1UL << 9)
#define ITOP_MASK_RXDMABREQ		 (0x1UL << 10)
#define ITOP_MASK_RXDMASREQ		 (0x1UL << 11)
#define ITOP_MASK_TXDMABREQ		 (0x1UL << 12)
#define ITOP_MASK_TXDMASREQ		 (0x1UL << 13)

/*
 * SSP Test Data Register - SSP_TDR
 */
#define TDR_MASK_TESTDATA		(0xFFFFFFFF)

/*
 * Message State
 * we use the spi_message.state (void *) pointer to
 * hold a single state value, that's why all this
 * (void *) casting is done here.
 */
#define STATE_START			((void *) 0)
#define STATE_RUNNING			((void *) 1)
#define STATE_DONE			((void *) 2)
#define STATE_ERROR			((void *) -1)

/*
 * SSP State - Whether Enabled or Disabled
 */
#define SSP_DISABLED			(0)
#define SSP_ENABLED			(1)

/*
 * SSP DMA State - Whether DMA Enabled or Disabled
 */
#define SSP_DMA_DISABLED		(0)
#define SSP_DMA_ENABLED			(1)

/*
 * SSP Clock Defaults
 */
#define SSP_DEFAULT_CLKRATE 0x2
#define SSP_DEFAULT_PRESCALE 0x40

/*
 * SSP Clock Parameter ranges
 */
#define CPSDVR_MIN 0x02
#define CPSDVR_MAX 0xFE
#define SCR_MIN 0x00
#define SCR_MAX 0xFF

/*
 * SSP Interrupt related Macros
 */
#define DEFAULT_SSP_REG_IMSC  0x0UL
#define DISABLE_ALL_INTERRUPTS DEFAULT_SSP_REG_IMSC
#define ENABLE_ALL_INTERRUPTS (~DEFAULT_SSP_REG_IMSC)

#define CLEAR_ALL_INTERRUPTS  0x3

#define SPI_POLLING_TIMEOUT 10000

/*
 * The type of reading going on on this chip
 */
enum ssp_reading {
	READING_NULL,
	READING_U8,
	READING_U16,
	READING_U32
};

/**
 * The type of writing going on on this chip
 */
enum ssp_writing {
	WRITING_NULL,
	WRITING_U8,
	WRITING_U16,
	WRITING_U32
};

/**
 * struct vendor_data - vendor-specific config parameters
 * for PL022 derivates
 * @fifodepth: depth of FIFOs (both)
 * @max_bpw: maximum number of bits per word
 * @unidir: supports unidirection transfers
 * @extended_cr: 32 bit wide control register 0 with extra
 * features and extra features in CR1 as found in the ST variants
 * @pl023: supports a subset of the ST extensions called "PL023"
 */
struct vendor_data {
	int fifodepth;
	int max_bpw;
	bool unidir;
	bool extended_cr;
	bool pl023;
	bool loopback;
};

/**
 * struct pl022 - This is the private SSP driver data structure
 * @adev: AMBA device model hookup
 * @vendor: vendor data for the IP block
 * @phybase: the physical memory where the SSP device resides
 * @virtbase: the virtual memory where the SSP is mapped
 * @clk: outgoing clock "SPICLK" for the SPI bus
 * @master: SPI framework hookup
 * @master_info: controller-specific data from machine setup
 * @kworker: thread struct for message pump
 * @kworker_task: pointer to task for message pump kworker thread
 * @pump_messages: work struct for scheduling work to the message pump
 * @queue_lock: spinlock to syncronise access to message queue
 * @queue: message queue
 * @busy: message pump is busy
 * @running: message pump is running
 * @pump_transfers: Tasklet used in Interrupt Transfer mode
 * @cur_msg: Pointer to current spi_message being processed
 * @cur_transfer: Pointer to current spi_transfer
 * @cur_chip: pointer to current clients chip(assigned from controller_state)
 * @next_msg_cs_active: the next message in the queue has been examined
 *  and it was found that it uses the same chip select as the previous
 *  message, so we left it active after the previous transfer, and it's
 *  active already.
 * @tx: current position in TX buffer to be read
 * @tx_end: end position in TX buffer to be read
 * @rx: current position in RX buffer to be written
 * @rx_end: end position in RX buffer to be written
 * @read: the type of read currently going on
 * @write: the type of write currently going on
 * @exp_fifo_level: expected FIFO level
 * @dma_rx_channel: optional channel for RX DMA
 * @dma_tx_channel: optional channel for TX DMA
 * @sgt_rx: scattertable for the RX transfer
 * @sgt_tx: scattertable for the TX transfer
 * @dummypage: a dummy page used for driving data on the bus with DMA
 * @cur_cs: current chip select (gpio)
 * @chipselects: list of chipselects (gpios)
 */
struct pl022 {
	struct amba_device		*adev;
	struct vendor_data		*vendor;
	resource_size_t			phybase;
	void __iomem			*virtbase;
	struct clk			*clk;
	struct spi_master		*master;
	struct pl022_ssp_controller	*master_info;
	/* Message per-transfer pump */
	struct tasklet_struct		pump_transfers;
	struct spi_message		*cur_msg;
	struct spi_transfer		*cur_transfer;
	struct chip_data		*cur_chip;
	bool				next_msg_cs_active;
	void				*tx;
	void				*tx_end;
	void				*rx;
	void				*rx_end;
	enum ssp_reading		read;
	enum ssp_writing		write;
	//u32				exp_fifo_level; // jun.kong remove
	int				exp_fifo_level;      // jun.kong add
	enum ssp_rx_level_trig		rx_lev_trig;
	enum ssp_tx_level_trig		tx_lev_trig;
	/* DMA settings */
#ifdef CONFIG_DMA_ENGINE
	struct dma_chan			*dma_rx_channel;
	struct dma_chan			*dma_tx_channel;
	struct sg_table			sgt_rx;
	struct sg_table			sgt_tx;
	char				*dummypage;
	bool				dma_running;
#endif
	int cur_cs;
	int *chipselects;
};
struct chip_data {
	u32 cr0;
	u16 cr1;
	u16 dmacr;
	u16 cpsr;
	u8 n_bytes;
	bool enable_dma;
	enum ssp_reading read;
	enum ssp_writing write;
	void (*cs_control) (u32 command);
	int xfer_type;
};

#endif

unsigned long long isrstart = 0;
unsigned long long isrend = 0;
extern struct spi_device tspidev ;

;
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	main control block for spi device.
 *	each minor device has unique control block
 *
 */

typedef struct SPI_DEVICE_t
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
	//int	 					isrArray[INT_ARRAY_NUM];
// END of command device

// BEGIN of device specific data
	OS_SEM_T				mutex;
// END of device specific data
}
SPI_DEVICE_T;


#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
}SPI_DRVDATA_T;
#endif




//SPI_INTR_CALLBACK_T _spi_isr_func[SPI_PIN_MAX]= {{NULL},};
//SPI_INTR_INFO_T	 spi_isr_info[SPI_PIN_MAX] = {{0,0},};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	SPI_PROC_Init(void);
extern	void	SPI_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int	g_spi_debug_fd;
int 	g_spi_major = SPI_MAJOR;
int 	g_spi_minor = SPI_MINOR;
int spi_intr_pin = 0;
int spi_intr_pin_value = 0;

//UINT32 g_poll_intr_idx = 0;
unsigned int crc = 0;

spinlock_t spiPoll_lock;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      SPI_Open(struct inode * node, struct file * fp);
static int      SPI_Close(struct inode * node, struct file * fp);
static long		SPI_Ioctl (struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long		SPI_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg);
#endif

#ifdef SUPPORT_SPI_DEVICE_READ_WRITE_FOPS
static ssize_t  SPI_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  SPI_Write(struct file *, const char *, size_t, loff_t *);
#endif

int SPI_DevResume(void);
int  SPI_probe(struct platform_device *pdev);

static unsigned int SPI_Poll(struct file *filp, poll_table *wait);
struct pl022  *pPl022 = NULL;
unsigned int spir1cnt = 0;
unsigned int spir2cnt = 0;
unsigned int spir3cnt = 0;
unsigned int spir4cnt = 0;
unsigned int spir5cnt = 0;
unsigned int spiw1cnt = 0;
unsigned int sptestcnt = 0;
unsigned int okcnt = 0;
unsigned int tx_rx_size = 0x1000;
unsigned int polling_period = 10;
unsigned int regkdrvisr = 0;

UINT16 spififo[32]={0,};


unsigned int ignore_once = 0;
unsigned int spimode = GPIO_INTR;
unsigned int txdelay = 20;
unsigned int rxcheckdelay = 30;


u32 llicnt = 0;
u32 dintrcnt = 0;
int sendstatus = 0;
int readstatus = 0;


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for spi device
*/
static SPI_DEVICE_T*		g_spi_device;

/**
 * file I/O description for spi device
 *
*/
static struct file_operations g_spi_fops =
{
	.open 	= SPI_Open,
	.release= SPI_Close,
	.unlocked_ioctl	= SPI_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= SPI_CompatIoctl,
#endif
#ifdef SUPPORT_SPI_DEVICE_READ_WRITE_FOPS
	.read 	= SPI_Read,
	.write 	= SPI_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
	.poll	= SPI_Poll,
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK, -1 : NOT OK
 *
 */


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))

static int SPI_suspend(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_SPI
    SPI_DRVDATA_T  *drv_data;
	struct platform_device *pdev = to_platform_device(dev);

    printk("SPI - suspend BEGIN\n");
    drv_data = platform_get_drvdata(pdev);

 //   SPI_DevSuspend();

    drv_data->is_suspended = 1;
    printk("SPI - suspend OK\n");
#endif

    return 0;
}

#else
static int SPI_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef KDRV_CONFIG_PM_SPI
    SPI_DRVDATA_T  *drv_data;

    printk("SPI - suspend BEGIN\n");
    drv_data = platform_get_drvdata(pdev);

  //  SPI_DevSuspend();

    drv_data->is_suspended = 1;
    printk("SPI - suspend OK\n");
#endif

    return 0;
}
#endif


/**
 *
 * resuming module.
 *
 * @param   struct platform_device *
 * @return  int 0 : OK , -1 : NOT OK
 *
 */

int SPI_DevResume(void)
{
	return 0;
}


 #if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))

static int SPI_resume(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_SPI
    SPI_DRVDATA_T  *drv_data;
	struct platform_device *pdev = to_platform_device(dev);

    printk("SPI - resume BEGIN\n");

    drv_data = platform_get_drvdata(pdev);
    if(drv_data->is_suspended == 0)
    {
        printk("SPI - resume FAIL\n");
        return -1;
    }

    SPI_DevResume();

    drv_data->is_suspended = 0;
    printk("SPI - resume OK\n");
#endif
    return 0;
}

 #else
static int SPI_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_SPI
    SPI_DRVDATA_T  *drv_data;

    printk("SPI - resume BEGIN\n");

    drv_data = platform_get_drvdata(pdev);
    if(drv_data->is_suspended == 0)
    {
        printk("SPI - resume FAIL\n");
        return -1;
    }

   // SPI_DevResume();

    drv_data->is_suspended = 0;
    printk("SPI - resume OK\n");
#endif
    return 0;
}
 #endif

 #if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))
//#ifdef KDRV_CONFIG_PM_SPI
static struct dev_pm_ops pm_ops = {
       SET_LATE_SYSTEM_SLEEP_PM_OPS(SPI_suspend, SPI_resume)
};
//#endif
#endif
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
 int  SPI_probe(struct platform_device *pdev)
{

	SPI_DRVDATA_T *drv_data;

	drv_data = (SPI_DRVDATA_T *)kmalloc(sizeof(SPI_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	SPI_NOTI("[%s] done probe\n", SPI_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function, this function will be called in rmmod spi module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
static void  SPI_remove(struct platform_device *pdev)
#else
static int  SPI_remove(struct platform_device *pdev)
#endif
{
	SPI_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	SPI_NOTI("released\n");

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
#else
	return 0;
#endif
}

/**
 *
 * module release function. this function will be called in rmmod module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void  SPI_release(struct device *dev)
{
	SPI_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))

static struct platform_driver spi_driver =
{
	.probe		= SPI_probe,
	.remove		= SPI_remove,

	/* suspend move late suspend */
	/* resume  move ealry resume */
	.driver		=
	{
		.name	= SPI_MODULE,
		.pm = &pm_ops,
	},
};

#else
static struct platform_driver spi_driver =
{
	.probe		= SPI_probe,
	.remove		= SPI_remove,

	.suspend		= SPI_suspend,
	.resume		= SPI_resume,
	.driver		=
	{
		.name	= SPI_MODULE,
	},
};
#endif




static struct platform_device spi_platform_device = {
	.name = SPI_MODULE,
	.id = 0,
	.id = -1,
	.dev = {
		.release = SPI_release,
	},

};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */

#define CS_GPIO44	0xfd4503fc
#define CS_GPIO48	0xfd4603fc
#define CS_GPIO63	0xfd4703fc
#define CS_GPIO67	0xfd4803fc
#define SPI_SBUF_SIZE	20
#define O24SPI_CS_BASE	{CS_GPIO44,CS_GPIO48}
#define O22SPI_CS_BASE	{CS_GPIO63,CS_GPIO67}

#define SPI_MODE_MASK       (SPI_CPHA | SPI_CPOL | SPI_CS_HIGH \
                    | SPI_LSB_FIRST | SPI_3WIRE | SPI_LOOP \
                    | SPI_NO_CS | SPI_READY | SPI_TX_DUAL \
                    | SPI_TX_QUAD | SPI_RX_DUAL | SPI_RX_QUAD)

#define SPI_HW_NUM 2
#if defined (CHIP_NAME_o24)
	#define USE_SPIKDRV
#elif defined (CHIP_NAME_o26)
	#undef SPI_HW_NUM
	#define SPI_HW_NUM 3
	#define USE_SPIKDRV
#else
#endif


#ifdef USE_SPIKDRV
struct mutex spich_mutex[SPI_HW_NUM];
static struct spi_device *spid[SPI_HW_NUM] = {(struct spi_device *)NULL,};

	#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
	#else
		#if 0
		static struct spi_master * spim[SPI_HW_NUM] ={(struct spi_master *)NULL,};
		static void __iomem *cs_outbase[SPI_HW_NUM] = {NULL,};
		static void __iomem *enable_base[SPI_HW_NUM] = {NULL,};
		static void __iomem *dir_base[SPI_HW_NUM] = {NULL,};

		enum dw_ssi_type {
			SSI_MOTO_SPI = 0,
			SSI_TI_SSP,
			SSI_NS_MICROWIRE,
		};

		struct dw_spi_chip {
			u8 poll_mode;
			u8 type;
			void (*cs_control)(u32 command);
		};


		static void dw_cs(unsigned int val)
		{
			#if 0
			if(0){}
			else if(lx_chip() == LX_CHIP_O24)
			{
				unsigned int reg;
				reg = readl_relaxed(cs_outbase[0]);

				if(val)
				{
					writel_relaxed( reg & ~(val <<4),cs_outbase[0]);
				}
				else
				{
					writel_relaxed( reg | !val << 4 ,cs_outbase[0]);
				}
			}
			#endif
		}

		static void pl022_cs(unsigned int val)
		{
			#if 0
			if(0){}
			else if(lx_chip() == LX_CHIP_O24)
			{
				unsigned int reg;
				reg = readl_relaxed(cs_outbase[1]);
				if(val)
				{
					writel_relaxed( reg & ~(val <<2),cs_outbase[1]);
				}
				else
				{
					writel_relaxed( reg | !val << 2 ,cs_outbase[1]);
				}
			}
			#endif
		}

		struct dw_spi_chip dw_chip_info ={

		#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
			.type = SSI_MOTO_SPI ,
		#else
			.poll_mode = 1,
			.type = SSI_MOTO_SPI ,
			.cs_control = dw_cs,
		#endif
		};

		static struct pl022_config_chip pl022_chip_info = {
			.com_mode = POLLING_TRANSFER,
			.iface = SSP_INTERFACE_MOTOROLA_SPI,
			.hierarchy = SSP_MASTER,
			.slave_tx_disable = 0,
			.rx_lev_trig = SSP_RX_1_OR_MORE_ELEM,
			.tx_lev_trig = SSP_TX_1_OR_MORE_EMPTY_LOC,
			.ctrl_len = SSP_BITS_8,
			.wait_state = SSP_MWIRE_WAIT_ZERO,
			.duplex = SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,
			.clkdelay = SSP_FEEDBACK_CLK_DELAY_NONE,
		#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
		#else
			.cs_control = pl022_cs,
		#endif
		};

		static  struct spi_board_info spi0_hw =
		{
			.modalias       = "spidev",
			.bus_num        = 0,
			.chip_select    = 1,
			.max_speed_hz   = 25000000,
			.controller_data = &dw_chip_info,
			.mode           = SPI_MODE_0,
		};

		static  struct spi_board_info spi1_hw =
		{
			.modalias = "spidev",
			.max_speed_hz = 2000000,
			.bus_num = 1,
			.chip_select    = 1,
			.mode = SPI_MODE_0,
			.controller_data = &pl022_chip_info,
		};

		static  struct spi_board_info *spibinfo[SPI_HW_NUM]=
		{
			&spi0_hw,
			&spi1_hw
		};
		#endif
	#endif //below 6.12
#endif //USE_SPIKDRV

int spi_config (unsigned char ch, unsigned char  mode ,unsigned int speed )
{
#if defined (USE_SPIKDRV)
	struct spi_device * spi;
	unsigned int tmp = 0;
	#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
	int ret = -1;
	char devstr[100];
	struct device * dev ;


	if(spid[ch] == NULL)
	{
		snprintf(devstr,sizeof(devstr),"spi%d.0",(int)ch);
		dev = bus_find_device_by_name(&spi_bus_type, NULL, devstr);
		if (!dev){
				printk("no spi device[%d]\n",ch);
				return -ENODEV;
		}

		spid[ch]= to_spi_device(dev);

		if(spid[ch] == NULL)
		{
			printk( "check spi config param  %d\n", ret);
			return -1;
		}
	}
	spi = spid[ch];

	tmp |= spi->mode & ~SPI_MODE_MASK;
	spi->mode = (u16)tmp;

	spi->bits_per_word = 8;
	spi->max_speed_hz = speed;
	ret = spi_setup(spi);

	return ret;
	#else
	int ret = -1;
	char devstr[100];
	struct device * dev ;
	//unsigned int mode_save;
	//unsigned int speed_save ;

	if(spid[ch] == NULL)
	{
		snprintf(devstr,sizeof(devstr),"spi%d.0",(int)ch);
		dev = bus_find_device_by_name(&spi_bus_type, NULL, devstr);
		if (!dev){
				printk("no spi device[%d]\n",ch);
				return -ENODEV;
		}
		spid[ch]= to_spi_device(dev);

		if(spid[ch] == NULL)
		{
			printk( "check spi config param  %d\n", ret);
			return -1;
		}

		//mode_save = spi->mode;
		//speed_save = spi->max_speed_hz;
	}

	spi = spid[ch];

	tmp |= spi->mode & ~SPI_MODE_MASK;
	/* need in 5.4 kernel for removing cs inversion*/
	tmp |= SPI_CS_HIGH;
	spi->mode = (u16)tmp;

	spi->bits_per_word = 8;
	spi->max_speed_hz = speed;
	ret = spi_setup(spi);
		//printk( "ch %d spi speed %d\n", ch, speed_save);
	return ret;
	#endif
#else
	return 0;
#endif
}


int spi_send (unsigned char ch, unsigned char  *data, int len, int cmdlen)
{
#if defined (USE_SPIKDRV)
	#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
	UINT8 * rxBuf = NULL;
	UINT8 sbuf[SPI_SBUF_SIZE]={0,};
	int ret,i;
	struct spi_device * spi;
	struct spi_transfer t;
	struct spi_message m;

	spi = spid[ch];

	if(spid[ch] == NULL)
	{
		printk ("check spi[%d] allocation\n",ch);
		return -1;
	}

	rxBuf = sbuf;
	memset( &t,0x0,sizeof( struct spi_transfer));
	memset( &m,0x0,sizeof( struct spi_message));

	if(len > SPI_SBUF_SIZE)
	{
		rxBuf =  (UINT8*) kmalloc(sizeof(UINT8)*len,GFP_KERNEL);
	}

	t.tx_buf = data;
	t.rx_buf = rxBuf;
	t.len = len;
	t.bits_per_word = 8;
	/* removed in 6.12 */
	//t.delay_usecs = 0;
	t.speed_hz = spi->max_speed_hz;


	if(ch < SPI_HW_NUM)
	{
		mutex_lock(&spich_mutex[ch]);
		spi_message_init (&m);
		spi_message_add_tail (&t, &m);

		ret = spi_sync (spid[ch], &m);
		mutex_unlock(&spich_mutex[ch]);


		if (ret < 0)
		{
			printk ("spi send failed. [%d]\n",ret);
			return -1;
		}

		if( cmdlen > 0)
		{
			for(i= cmdlen; i < len; i++)
			{
				data[i]= rxBuf[i];
			}
		}

		if( len > SPI_SBUF_SIZE)
		{
			kfree(rxBuf);
		}
		return ret;

	}
	else
	{
		printk("check ch[%d]\n",ch);
		return -1;
	}
	return 0;
	#else
	UINT8 * rxBuf = NULL;
	UINT8 sbuf[SPI_SBUF_SIZE]={0,};
	int ret,i;
	struct spi_device * spi;
	struct spi_transfer t;
	struct spi_message m;

	spi = spid[ch];

	if(spid[ch] == NULL)
	{
		printk ("check spi[%d] allocation\n",ch);
		return -1;
	}

	rxBuf = sbuf;
	memset( &t,0x0,sizeof( struct spi_transfer));
	memset( &m,0x0,sizeof( struct spi_message));

	if(len > SPI_SBUF_SIZE)
	{
		rxBuf =  (UINT8*) kmalloc(sizeof(UINT8)*len,GFP_KERNEL);
	}

	t.tx_buf = data;
	t.rx_buf = rxBuf;
	t.len = len;
	t.delay_usecs = 0;
	t.bits_per_word = 8;
	t.speed_hz = spi->max_speed_hz;


	if(ch < SPI_HW_NUM)
	{
		mutex_lock(&spich_mutex[ch]);
		spi_message_init (&m);
		spi_message_add_tail (&t, &m);

		ret = spi_sync (spid[ch], &m);
		mutex_unlock(&spich_mutex[ch]);


		if (ret < 0)
		{
			printk ("spi send failed. [%d]\n",ret);
			return -1;
		}

		if( cmdlen > 0)
		{
			for(i= cmdlen; i < len; i++)
			{
				data[i]= rxBuf[i];
			}
		}

		if( len > SPI_SBUF_SIZE)
		{
			kfree(rxBuf);
		}
		return ret;

	}
	else
	{
		printk("check ch[%d]\n",ch);
		return -1;
	}
	return 0;
	#endif
#else
	return 0;
#endif
}


void SPI_PreInit(void)
{
#if defined (CHIP_NAME_o24)


	#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
	#else
	#if 0
	unsigned int reg;
	int i = 0;
	if(0){}
	else if(lx_chip() == LX_CHIP_O24)
	{
		cs_outbase[0] = ioremap(CS_GPIO44,0x4);
		cs_outbase[1] = ioremap(CS_GPIO48,0x4);

		/* 0:origcs 1:gpio44 */
		enable_base[0] = ioremap(0xcc97210c,0x4);
		reg = readl_relaxed(enable_base[0]);
		reg &= 0xfffff0ff;
		writel_relaxed( reg | 0x100,enable_base[0]);

		/* gpio44 set dir as out */
		dir_base[0] = ioremap(0xfd450400,0x4);
		reg = readl_relaxed(dir_base[0]);
		writel_relaxed( reg | 0x10,dir_base[0]);
	}

	for( i= 0 ; i < SPI_HW_NUM ; i++)
	{
		spim[i] = spi_busnum_to_master(i);

		if(!spim[i])
		{
			printk("ch %d no spim \n",i);
			return;
		}

		spim[i]->num_chipselect++;

		spid[i] = spi_new_device (spim[i], spibinfo[i]);

		if(!spid[i])
		{
			printk("ch %d no spinew \n",i);
			return;
		}

		spid[i]->chip_select = 0;

		//_spi_dev[i] = spid[i];
		spi_config (i,SPI_MODE_0  ,2000000);
		mutex_init(&spich_mutex[i]);
	}
	#endif
	#endif
#endif
}

int SPI_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for spi device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */

	g_spi_debug_fd = DBG_OPEN( SPI_MODULE );
	if(g_spi_debug_fd < 0) return -1;

	OS_DEBUG_EnableModule ( g_spi_debug_fd );

	OS_DEBUG_EnableModuleByIndex ( g_spi_debug_fd, SPI_MSG_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_spi_debug_fd, SPI_MSG_NOTI, DBG_COLOR_NONE );

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&spi_driver) < 0)
	{
		SPI_ERROR("[%s] platform driver register failed\n",SPI_MODULE);
	}
	else
	{
		if(platform_device_register(&spi_platform_device))
		{
			platform_driver_unregister(&spi_driver);
			SPI_ERROR("[%s] platform device register failed\n",SPI_MODULE);
		}
		else
		{
			SPI_NOTI("[%s] platform register done\n", SPI_MODULE);
		}
	}
#endif

	//SPI_DevInit();

	g_spi_device = (SPI_DEVICE_T*)OS_KMalloc( sizeof(SPI_DEVICE_T)*SPI_MAX_DEVICE );

	if ( NULL == g_spi_device ){
		SPI_ERROR("out of memory. can't allocate %d bytes\n", (int)sizeof(SPI_DEVICE_T)* SPI_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_spi_device, 0x0, sizeof(SPI_DEVICE_T)* SPI_MAX_DEVICE );

	if (g_spi_major)
	{
		dev = MKDEV( g_spi_major, g_spi_minor );
		err = register_chrdev_region(dev, SPI_MAX_DEVICE, SPI_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_spi_minor, SPI_MAX_DEVICE, SPI_MODULE );
		g_spi_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		SPI_ERROR("can't register spi device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<SPI_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_spi_major, g_spi_minor+i );
		cdev_init( &(g_spi_device[i].cdev), &g_spi_fops );
		g_spi_device[i].devno		= dev;
		g_spi_device[i].cdev.owner = THIS_MODULE;
		g_spi_device[i].cdev.ops   = &g_spi_fops;

		/* TODO: initialize minor device */
		/* END */

		err = cdev_add (&(g_spi_device[i].cdev), dev, 1 );

		if (err)
		{
			SPI_ERROR("error (%d) while adding spi device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
		OS_CreateDeviceClass ( g_spi_device[i].devno, "%s%d", SPI_MODULE, i );
	}

	SPI_PROC_Init ( );
	return 0;
}

void SPI_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_spi_major, g_spi_minor );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&spi_driver);
	platform_device_unregister(&spi_platform_device);
#endif
	SPI_PROC_Cleanup( );

	/* cleanup proc system */
	//SPI_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<SPI_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_spi_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, SPI_MAX_DEVICE );

	OS_Free( g_spi_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for spi device
 *
 */
static int SPI_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    SPI_DEVICE_T*	my_dev;
	//return 0;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SPI_DEVICE_T, cdev);

    /* TODO : add your device specific code */


	/* END */

	if(my_dev->dev_open_count == 0)
	{

	}

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    SPI_NOTI("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for spi device
 *
 */
static int SPI_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    SPI_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SPI_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    SPI_NOTI("device closed (%d:%d)\n", major, minor );
    return 0;
}



#if 0

static struct pl022_config_chip spi1_rx_info = {
        .com_mode = POLLING_TRANSFER,
        .iface = SSP_INTERFACE_MOTOROLA_SPI,
       // .hierarchy = SSP_SLAVE,
        .hierarchy = SSP_MASTER,
        .slave_tx_disable = 0,
        .rx_lev_trig = SSP_RX_1_OR_MORE_ELEM,
        .tx_lev_trig = SSP_TX_1_OR_MORE_EMPTY_LOC,
        .ctrl_len = SSP_BITS_8,
        .wait_state = SSP_MWIRE_WAIT_ZERO,
        .duplex = SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,
        .clkdelay = SSP_FEEDBACK_CLK_DELAY_NONE,
	.cs_control = select_dummy_chip,
};

static struct pl022_config_chip spi1_rx_intr_info = {
        .com_mode = INTERRUPT_TRANSFER,
        .iface = SSP_INTERFACE_MOTOROLA_SPI,
        .hierarchy = SSP_SLAVE,
       // .hierarchy = SSP_SLAVE,
        .slave_tx_disable = 0,
        .rx_lev_trig = SSP_RX_1_OR_MORE_ELEM,
        .tx_lev_trig = SSP_TX_1_OR_MORE_EMPTY_LOC,
        .ctrl_len = SSP_BITS_8,
        .wait_state = SSP_MWIRE_WAIT_ZERO,
        .duplex = SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,
        .clkdelay = SSP_FEEDBACK_CLK_DELAY_NONE,
	.cs_control = select_dummy_chip,
};
static struct pl022_config_chip spi1_rx_dma_info = {
        .com_mode = DMA_TRANSFER,
        .iface = SSP_INTERFACE_MOTOROLA_SPI,
        .hierarchy = SSP_SLAVE,
        //.hierarchy = SSP_MASTER,
        .slave_tx_disable = 0,
        .rx_lev_trig = SSP_RX_1_OR_MORE_ELEM,
        .tx_lev_trig = SSP_TX_1_OR_MORE_EMPTY_LOC,
        .ctrl_len = SSP_BITS_8,
        .wait_state = SSP_MWIRE_WAIT_ZERO,
        .duplex = SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,
        .clkdelay = SSP_FEEDBACK_CLK_DELAY_NONE,
	.cs_control = select_dummy_chip,
};



static struct spi_board_info spi1_chip_slave =
{
        .modalias = "spi1",
        .max_speed_hz = 16000000,
        .bus_num = 1,
        .chip_select = 0,
        .mode = SPI_MODE_0,
     //  .controller_data = &d14_chip_info,
       .controller_data = &spi1_rx_dma_info,
       // .controller_data = &d14_chip_intr_info,
};
#endif



#if 0
static int send (void *data, int len)
{
        struct spi_transfer t =
        {
                .tx_buf = data,
                .len = len,
                .delay_usecs = 10,//d14_spi_delay_us,
                .cs_change = 0,
        };
        struct spi_message m;

        spi_message_init (&m);
        spi_message_add_tail (&t, &m);

        return spi_sync (pSpi_device[1], &m);
}

static int recv16 (u16 *data,void *data2, int len)
{
        struct spi_transfer t =
        {
				.rx_buf = data,
                .len = len,

        };
        struct spi_message m;
        spi_message_init (&m);
        spi_message_add_tail (&t, &m);

        return spi_sync (pSpi_device[1], &m);
        //return spi_sync (spikdrv_device, &m);
		//return spi_sync (&tspidev, &m);
}

static int recv (u8 *data,void *data2, int len)
{
        struct spi_transfer t =
        {
				.rx_buf = data,
                .len = len,

        };
        struct spi_message m;
        spi_message_init (&m);
        spi_message_add_tail (&t, &m);

        return spi_sync (pSpi_device[1], &m);
        //return spi_sync (spikdrv_device, &m);
		//return spi_sync (&tspidev, &m);
}

static int _mem_read (unsigned int addr,
                __user unsigned char *buf, int len, int user)
{
        unsigned int a;
        int c;
        struct spi_transfer t;
        struct spi_message m;
        unsigned char w[9], r[9];
        int ret = 0;

        if ((addr & 3) || (len & 3))
        {
                SPI_NOTI ("not aligned address or size. %08x, %d\n", addr, len);
                return -1;
        }

        a = addr;
        c = 0;
        while (c < len)
        {
                int ret;

                memset (w, 0, sizeof(w));
                memset (r, 0, sizeof(r));
                w[0] = (a>>24)&0xff;
                w[1] = (a>>16)&0xff;
                w[2] = (a>> 8)&0xff;
                w[3] = (a>> 0)&0xff;
                w[3] |= 1;
                w[4] = 0;

                /* make spi message */
                spi_message_init(&m);
			#if 0
			  printk ("111.\n");
			  ((struct spi_device *)(m.spi))->chip_select = 0;
			  printk ("2222.\n");
			#endif

                memset (&t, 0, sizeof (t));
                t.tx_buf = w;
                t.rx_buf = r;
                t.len = 9;
                t.delay_usecs = 10;// d14_spi_delay_us;
                //t.cs_change = 0;
                spi_message_add_tail(&t, &m);
                ret = spi_sync(pSpi_device[1], &m);
                if (ret < 0)
                {
                        SPI_ERROR ("spi sync failed.\n");
                        break;
                }

                if (user)
                {
                        put_user (r[8], buf+c+0);
                        put_user (r[7], buf+c+1);
                        put_user (r[6], buf+c+2);
                        put_user (r[5], buf+c+3);
                }
                else
                {
                        buf[c+0] = r[8];
                        buf[c+1] = r[7];
                        buf[c+2] = r[6];
                        buf[c+3] = r[5];
                }

                a += 4;
                c += 4;
        }

        return ret;
}

int mem_read (unsigned int addr, __user unsigned char *buf, int len)
{
        return _mem_read (addr, buf, len, 1);
}

static int _mem_write (unsigned int addr,
                __user unsigned char *buf, int len, int user)
{
        unsigned int a;
        int c;
        unsigned char *tmp;
        int ret = 0;

        len = (len+3)&~3;
        if (addr & 3)
        {
                SPI_ERROR ("not aligned address. %08x\n", addr);
                return -1;
        }

        a = addr;
        c = 0;
        tmp = kmalloc (5+256*4, GFP_KERNEL);
        if (!tmp)
        {
                SPI_ERROR ("no mem?\n");
                return -ENOMEM;
        }

        while (c < len)
        {
                int count;

                //debug ("address %08x, len %d, c %d\n", a, len, c);

                count = 256;
                if ((len - c)/4 < count)
                        count = (len - c)/4;
                //debug ("count %d\n", count);

                tmp[0] = (a>>24)&0xff;
                tmp[1] = (a>>16)&0xff;
                tmp[2] = (a>> 8)&0xff;
                tmp[3] = (a>> 0)&0xff;
                tmp[3] |= 2;
                tmp[4] = count-1;

                if (user)
                {
                        if (copy_from_user (tmp+5, buf+c, count*4) > 0)
                        {
                                SPI_ERROR ("Oops?\n");
                                ret = -EFAULT;
                                break;
                        }
                }
                else
                        memcpy (tmp+5, buf+c, count*4);

			#if 0
                //if (!big_endian)
                {
                        int i;

                        for (i=0; i<count; i++)
                        {
                                swap (tmp[5+i*4+0], tmp[5+i*4+3]);
                                swap (tmp[5+i*4+1], tmp[5+i*4+2]);
                        }
                }
			#endif

                send (tmp, 5 + count*4);

                a += count*4;
                c += count*4;
        }

        kfree (tmp);

        return ret;
}

int mem_write (unsigned int addr, __user unsigned char *buf, int len)
{
        return _mem_write (addr, buf, len, 1);
}

int reg_write (unsigned int addr, unsigned int reg)
{
        unsigned char tmp[8];

        tmp[0] = (addr>>24)&0xff;
        tmp[1] = (addr>>16)&0xff;
        tmp[2] = (addr>> 8)&0xff;
        tmp[3] = (addr>> 0)&0xff;
        tmp[4] = (reg>>24)&0xff;
        tmp[5] = (reg>>16)&0xff;
        tmp[6] = (reg>> 8)&0xff;
        tmp[7] = (reg>> 0)&0xff;

        send (tmp, 8);

        return 0;
}

int reg_read (int reg, unsigned int *data)
{
        int ret;
        ret = _mem_read (reg, (unsigned char*)data, 4, 0);
        return ret;
}
#endif

struct pl022_ssp_controller spi0_kdrvdata = {
	.bus_id		= 0,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
#else
	.num_chipselect	= 1,
#endif
    .enable_dma = 1,
    .dma_filter = pl08x_filter_id,
    .dma_tx_param = "sspk0_tx",
    .dma_rx_param = "sspk0_rx",
};


struct pl022_ssp_controller spi1_kdrvdata = {
	.bus_id		= 1,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
#else
	.num_chipselect	= 2,
#endif
    .enable_dma = 1,
    .dma_filter = pl08x_filter_id,
    .dma_tx_param = "sspk1_tx",
    .dma_rx_param = "sspk1_rx",
};



/**
 * ioctl handler for spi device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static long SPI_Ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	SPI_DEVICE_T*	spi_dev;
	LX_SPI_RW_DATA_T param;
	int err = 0, ret = 0;
	/*
	 * get current spi device object
	 */
	spi_dev = (SPI_DEVICE_T*)file->private_data;

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != SPIKDRV_IOC_MAGIC){
	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > SPI_IOC_MAXNR){
	DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
	return -ENOTTY;
    }

	/* TODO : add some check routine for your device */

    /*
     * check if user memory is valid or not.
     * if memory can't be accessed from kernel, return error (-EFAULT)
     */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    if (_IOC_DIR(cmd) & (_IOC_READ | _IOC_WRITE))
        err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
#else
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
#endif

    if (err){
	DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
	_IOC_NR(cmd),
	(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
	(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
	(void*)arg );
	return -EFAULT;
	}


	SPI_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd){
		case LXDRV_SPI_KDRV_IF_INIT:
		{

			SPI_COPY_FROM_USER(&param, arg, sizeof(LX_SPI_RW_DATA_T));
			if(param.ch >= SPI_HW_NUM){
			        SPI_ERROR ("check spi channel\n");
			        return -ENODEV;
			}


		}
		break;
#if 0
		case LXDRV_SPI_KDRV_IF_WRITE:
		{
			SPI_COPY_FROM_USER(&param, arg, sizeof(LX_SPI_RW_DATA_T));
			ret = reg_write (param.addr,param.data);
		}
		break;
		case LXDRV_SPI_KDRV_IF_READ:
		{
			SPI_COPY_FROM_USER(&param, arg, sizeof(LX_SPI_RW_DATA_T));
			ret = reg_read (param.addr,&(param.data));
			SPI_COPY_TO_USER(arg, &param, sizeof(LX_SPI_RW_DATA_T));
			//SPI_ERROR("LXDRV_SPI_KDRV_IF_READ: [%d]\n",ret);
			break;
		}
		case LXDRV_SPI_KDRV_IF_BURSTWRITE:
		{
			SPI_COPY_FROM_USER(&param, arg, sizeof(LX_SPI_RW_DATA_T));

			ret = mem_write(param.addr, param.buf, param.bufsize);
		}
		break;
#endif

	    default:
	    {
			SPI_ERROR("ioctl: default\n");
			/* redundant check but it seems more readable */
			ret = -ENOTTY;
		}
		break;
    }
    return ret;
}

#ifdef CONFIG_COMPAT
static long SPI_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd)
	{
	case LXDRV_SPI_TRANSMIT:
	case LXDRV_SPI_KDRV_IF_INIT:
	case LXDRV_SPI_KDRV_IF_WRITE:
	case LXDRV_SPI_KDRV_IF_READ:
	case LXDRV_SPI_KDRV_IF_BURSTWRITE:
	case LXDRV_SPI_KDRV_IF_CHANGEPARAM:
	case LXDRV_SPI_KDRV_IF_POLLINKDRV:
	case LXDRV_SPI_KDRV_IF_WWR:
	case LXDRV_SPI_KDRV_IF_RRD:
	case LXDRV_SPI_KDRV_IF_WR:
	case LXDRV_SPI_KDRV_IF_RD:
	{
		LX_SPI_RW_DATA_T arg_lx_spi_rw_data_t;

		ret = copy_from_user(&arg_lx_spi_rw_data_t, (void *)arg,
							 sizeof(LX_SPI_RW_DATA_T));
		if (ret)
		{
			return -EINVAL;
		}

		arg_lx_spi_rw_data_t.buf =
			(UINT8 *)(uintptr_t)arg_lx_spi_rw_data_t.compat_buf;

		ret = copy_to_user((void *)arg, &arg_lx_spi_rw_data_t,
						   sizeof(LX_SPI_RW_DATA_T));
		if (ret)
		{
			return -EINVAL;
		}

		break;
	}
	default:
		break;
	}

	ret = SPI_Ioctl(file, cmd, arg);

	return ret;
}
#endif

static unsigned int SPI_Poll(struct file *filp, poll_table *wait)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",SPI_Init);
#else
module_init(SPI_Init);
#endif
module_exit(SPI_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("spi driver");
MODULE_LICENSE("GPL");



#endif

/** @} */

