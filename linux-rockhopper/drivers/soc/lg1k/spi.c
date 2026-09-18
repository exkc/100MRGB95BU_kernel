#include <linux/kernel.h>

#include <linux/amba/bus.h>
#include <linux/amba/pl022.h>
#include <linux/sizes.h>
#include <linux/spi/spi.h>
#include <linux/of.h>
#include "../../spi/spi-dw.h"


struct pl022_ssp_controller spi0_data = {
	.bus_id		= 0,
};

struct pl022_ssp_controller spi1_data = {
	.bus_id		= 1,
};

#ifdef CONFIG_SPI_SPIDEV
static struct pl022_config_chip dummy_chip_info = {
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
};

static struct spi_board_info lg115x_spi_board_info[] __initdata = {
	{
		.modalias       = "lg1k_spi",
		.bus_num        = 0,
		.chip_select    = 0,
		.max_speed_hz   = 16000000,
		.controller_data = &dummy_chip_info,
		.mode           = SPI_MODE_0,
	}, {
		.modalias       = "lg1k_spi",
		.bus_num        = 1,
		.chip_select    = 0,
		.max_speed_hz   = 16000000,
		.controller_data = &dummy_chip_info,
		.mode           = SPI_MODE_0,
	},
};
struct dw_spi_chip_data {
    u32 cr0;
    u32 rx_sample_dly;  /* RX sample delay */
};
struct dw_spi_chip_data dummy_dw_chip_info ;
struct dw_spi_mmio {
       struct dw_spi  dws;
       struct clk     *clk;
};

struct dw_spi_mmio dwspi_data =
{
       .dws = {
               .bus_num = 0,
               .num_cs = 1,
       },
       .clk = NULL,
};

static struct spi_board_info lg121x_spi_board_info[] __initdata = {
	{
		.modalias       = "lg1k_spi",
		.bus_num        = 0,
		.chip_select    = 0,
		.max_speed_hz   = 50000000,
		.controller_data = &dummy_dw_chip_info,
		.mode           = SPI_MODE_0,
	}, {
		.modalias       = "lg1k_spi",
		.bus_num        = 1,
		.chip_select    = 0,
		.max_speed_hz   = 16000000,
		.controller_data = &dummy_chip_info,
		.mode           = SPI_MODE_0,
	},
};

static struct spi_board_info lg1215_spi_board_info[] __initdata = {
	{
		.modalias       = "lg1k_spi",
		.bus_num        = 0,
		.chip_select    = 0,
		.max_speed_hz   = 50000000,
		.controller_data = &dummy_dw_chip_info,
		.mode           = SPI_MODE_0,
	}, {
		.modalias       = "lg1k_spi",
		.bus_num        = 1,
		.chip_select    = 0,
		.max_speed_hz   = 16000000,
		.controller_data = &dummy_chip_info,
		.mode           = SPI_MODE_0,
	}, {
		.modalias       = "lg1k_spi",
		.bus_num        = 2,
		.chip_select    = 0,
		.max_speed_hz   = 50000000,
		.controller_data = &dummy_dw_chip_info,
		.mode           = SPI_MODE_0,
	},
};
#endif

static int __init lg115x_init_spi(void)
{
#ifdef CONFIG_SPI_SPIDEV
	if (of_machine_is_compatible("lge,lg1213") ||
	    of_machine_is_compatible("lge,lg1214")) {
		return spi_register_board_info(lg121x_spi_board_info,
			ARRAY_SIZE(lg121x_spi_board_info));
	} else if (of_machine_is_compatible("lge,lg1215")) {
		return spi_register_board_info(lg1215_spi_board_info,
			ARRAY_SIZE(lg1215_spi_board_info));
	} else {
		return spi_register_board_info(lg115x_spi_board_info,
			ARRAY_SIZE(lg115x_spi_board_info));
	}
#else
	return 0;
#endif
}
late_initcall(lg115x_init_spi);
