#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "REGISTER/register_o24.h"
#include "config.h"

#define debug(fmt,args...)	printk(KERN_DEBUG"%16s.%d: "fmt,__func__,__LINE__,##args)
#define info(fmt,args...)	printk(KERN_INFO"%16s.%d: "fmt,__func__,__LINE__,##args)
#define error(fmt,args...)	printk(KERN_ERR"%16s.%d: "fmt,__func__,__LINE__,##args)

#define IRQ_DMCU_I2E (32 + 160) /* DMCU I2E Interrupt */

#define UART_REG_BASE (0xC63F2020) /* UART PORT */

static volatile uint32_t *uart_reg;

struct intr_ipc {
	char name[12];
	volatile void *reg_ena;
	volatile void *reg_sts;
	volatile void *reg_raw;
	volatile void *reg_clr;
};
static struct intr_ipc ipc_dev;

static void ipc_cmd_function(struct work_struct *work)
{
	uint32_t port;

	/* command status */
	port = REG_ARD(gpREG_SYSTEM->sysgp0);

	/* uart mux */
	if (port >= 0 && port <= 2) {
		uart_reg[port] = 0x2;
		debug("dmc: cpu_uart port: %d\n", port);
	} else {
		debug("dmc: no operation provided. port: %d\n", port);
	}

	/* command clear */
	REG_AWR(gpREG_SYSTEM->sysgp0, 0);
}
static DECLARE_WORK(ipc_cmd_work, ipc_cmd_function);

static int dmcu_ipc_cmd(void)
{
	schedule_work(&ipc_cmd_work);

	return 0;
}

static irqreturn_t ipc_handler(int irq, void *dev_id)
{
	struct intr_ipc *dev = dev_id;

	uint32_t status = REG_RD(dev->reg_sts);

	REG_WR(dev->reg_clr, status);

	if (status & 0x1)
		dmcu_ipc_cmd();
	else
		error("dmc: not supported ipc; bit %x\n", status);

	return IRQ_HANDLED;
}

int dmcu_init(void)
{
	int result;

	uart_reg = ioremap(UART_REG_BASE, 12);
	if (!uart_reg) {
		error("dmc: ioremap failed\n");
		return -ENOMEM;
	}

	/* ipc interrupt (mcu to cpu) */
	strcpy(ipc_dev.name, "dmcu-ipc");

	ipc_dev.reg_ena = &(gpREG_MCU->ipci2einten);
	ipc_dev.reg_sts = &(gpREG_MCU->ipci2eintsts);
	ipc_dev.reg_raw = &(gpREG_MCU->ipci2eintrawsts);
	ipc_dev.reg_clr = &(gpREG_MCU->ipci2eintclr);

	result = request_irq(IRQ_DMCU_I2E, ipc_handler, IRQF_SHARED,
			     ipc_dev.name, &ipc_dev);

	if (result) {
		error("dmc: cannot allocate irq %d\n", IRQ_DMCU_I2E);
		return -EBUSY;
	}

	/* ipc enable */
	REG_AWR(gpREG_MCU->ipci2einten, 0x1);

	return 0;
}
