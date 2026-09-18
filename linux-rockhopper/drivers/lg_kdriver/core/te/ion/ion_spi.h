#ifndef _ION_SPI_H_
#define _ION_SPI_H_

#include <linux/types.h>

struct te_dev_ion;

enum dvbci_access_mode {
	MODE_IO_NONE = 0, // prevent understanding dummy as a command
	MODE_IO_LEGACY = 1, // mode change + access io
	MODE_REG_ACCESS = 2,
	MODE_SMC_ACCESS = 3,
	MODE_IO_FAST = 4, // access io only
	MODE_ATTRIBUTE_MEM = 5,
	MODE_ION_REG = 7,
};

enum dvbci_rw_direction {
	DIRECTION_WRITE = 0,
	DIRECTION_READ = 1
};

#define SPI_CMD_SIZE 3 // addr + cmd
#define SPI_MESSAGE_MAX_LEN 128 // SPI_CMD_SIZE + CAM_IO_MAX_BURST_SIZE * CAM_IO_FAST_PACKET_SIZE
#define SPI_ION_DEFAULT_CLK 15000000 // 15 Mhz

u8 ion_spi_gen_option(enum dvbci_rw_direction direction,
		      enum dvbci_access_mode mode, u8 len);
int ion_spi_send_message(struct te_dev_ion *dev, u8 *buf, u32 size,
		         u32 cmdsize);
int ion_spi_clk_config(struct te_dev_ion *dev, u32 clk);

#endif				//_CI_SPI_H_
