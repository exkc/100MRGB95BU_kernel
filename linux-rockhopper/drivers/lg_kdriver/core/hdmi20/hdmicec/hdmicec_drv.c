#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/cec.h>
#include <linux/circ_buf.h>
#include <linux/vmalloc.h>
#include <media/cec.h>
#include <linux/version.h>
#include <linux/jiffies.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/clock.h>
#endif
#include "hdmicec_drv.h"
#include "os_util.h"
#include "hdmi20_drv.h"
#include "sys_io.h"
#include "proc_util.h"

#define LGDT_CEC_NAME	"lgdt-cec"
#define CEC_VERSION_1_4	5
#define CEC_VENDOR_ID	0x00e091 /* need to check lge vendor id */
#define CEC_DRV_VER		2025070400

#ifndef LX_CHIP_O26
#define LX_CHIP_O26 LX_CHIP_UNKNOWN
#endif

#define E60_CRG_HDMI_SYN_REGISTER_BASE	0xC3320000	// E60 CRG_SUB:HDMI_SYN
#define O22_CRG_HDMI_SYN_REGISTER_BASE	0xC8950000	// E60 CTOP CRG HDMI(hdmi_syn)
#define M23_CRG_HDMI_SYN_REGISTER_BASE	0xC47B0000	// M23 CRG SUB Register(hdmi(cvi_syn))
#define O24_CRG_HDMI_SYN_REGISTER_BASE	0xC8D40000	// O24 CRG SUB Register(hdmi(cvi_syn))
#define O26_CRG_HDMI_SYN_REGISTER_BASE	0xC8740000	// O26 CRG SUB Register(hdmi(hdmi_syn))

#define E60_CTOP_WOV_REGISTER_BASE	0xF3011400
#define O20_CTOP_WOV_REGISTER_BASE	0xc3300800
#define O22_CTOP_WOV_REGISTER_BASE	0xF3082000
#define M23_CTOP_WOV_REGISTER_BASE	0xC8515000	//M23 CTOP_PAD Register
#define O24_CTOP_WOV_REGISTER_BASE	0xC63F5000	//O24 CTOP_PAD Register
#define O26_CTOP_WOV_REGISTER_BASE	0xCA3A3000	//O26 CTOP_PAD(PAD_WOC) Register
#define O26_HDMIRX_RC_REGISTER_BASE	0xC8708000	//O26 HDMIRX_RC_Reigster (port0)

#define O20_HDMI_SYN_REGISTER_BASE	0xc9306000
#define E60_HDMI_SYN_REGISTER_BASE	0xc3321000		// CTOP_SYN:HDMI_SYN
#define O22_HDMI_SYN_REGISTER_BASE	0xc8972000		// CTOP_SYN:HDMI_BND
#define M23_HDMI_SYN_REGISTER_BASE	0xc47b1000		// M23 CTOP IPW Register : HDMI IPW
#define O24_HDMI_SYN_REGISTER_BASE	0xC8D41000		// O24 IPW Register : HDMI IPW
#define O26_HDMI_SYN_REGISTER_BASE	0xC8741000		// O24 IPW Register : HDMI IPW

#define O20_HDMI_REGISTER_BASE	0xc9110000
#define E60_HDMI_REGISTER_BASE	0xc3340000
#define O22_HDMI_REGISTER_BASE	0xC8900000
#define M23_HDMI_REGISTER_BASE	0xC47C0000
#define O24_HDMI_REGISTER_BASE	0xC8D00000	//CPU_HDMI_IP_TOP
#define O26_HDMI_REGISTER_BASE	0xC8700000	//CPU_HDMI_IP_TOP

//#define CEC_REGISTER_BASE	(HDMI_REGISTER_BASE + 0x2000)
/* CEC register offset */
#define CEC_RX_LENGTH			0x030
#define CEC_RX_DONE			0x031
#define CEC_TX_DONE			0x032
#define CEC_RX_DATA_BASE		0x034
#define CEC_NOTI_FROM_MiCOM		0x088
#define CEC_TX_LENGTH			0x130
#define CEC_TX_DATA_BASE		0x134
#define CEC_NOTI_FROM_ARM		0x188
#define HDMICEC_THREAD_TIMEOUT	10

#define DBG_BUF_WIDTH	128
#define DBG_BUF_LENGTH	1024
#define DBG_BUF_SIZE	((DBG_BUF_WIDTH)*(DBG_BUF_LENGTH))

#define _REG_WR(address,data)   \
	__sMapped_address=(u32 *)ioremap(address, sizeof(u32));\
do{\
	if(__sMapped_address == NULL) break;\
	*__sMapped_address = data;\
	iounmap((void *)__sMapped_address);\
}while(0);\

#define _REG_RD(address,data)   \
	__sMapped_address = (u32 *)ioremap(address, sizeof(u32));\
do{\
	if(__sMapped_address == NULL) {data = 0; break;}\
	data = (unsigned int)*__sMapped_address;\
	iounmap((void *)__sMapped_address);\
}while(0);\

#define	HDMI20_CEC_BUF_INFO(cec, format, args...)								\
	do {																	\
	HDMI20_CEC_INFO(format, ##args);										\
	lgdt_cec_buf_print(cec, format, ##args);									\
	} while(0)

#define	HDMI20_CEC_BUF_DEBUG(cec, format, args...)								\
	do {																	\
	HDMI20_CEC_DEBUG(format, ##args);										\
	lgdt_cec_buf_print(cec, format, ##args);									\
	} while(0)

#define	HDMI20_CEC_BUF_ERROR(cec, format, args...)								\
	do {																	\
	HDMI20_CEC_ERROR(format, ##args);										\
	lgdt_cec_buf_print(cec, format, ##args);									\
	} while(0)

enum {
	PROC_ID_CEC_AUTHOR	= 0,
	PROC_ID_CEC_STATUS,
	PROC_ID_CEC_DMESG,
	PROC_ID_CEC_REG_DUMP,
	PROC_ID_CEC_TX,
	PROC_ID_CEC_WORKAROUND,
	PROC_ID_CEC_MAX,
};

struct lgdt_cec *_g_cec = NULL;

static unsigned int __attribute__((unused)) *__sMapped_address; // For DBG: REG Read/Write macro

struct lgdt_cec {
	struct cec_adapter	*adap;
	struct device		*dev;
	struct clk		*clk;
	void __iomem		*hdmi_base;
//	void __iomem		*hdmi_syn_base;
//	void __iomem		*ctop_wov_base;
	int			irq;
	u32			irq_status;
	u32			len;
	struct cec_notifier	*notifier;
	u8 cec_addr[DW_HDMI_MAX_ADDRS];
	u32 cec_valid_addrs;
	bool cec_enabled_adap;
	bool cec_enabled_hw;
	struct task_struct	*thread;
	u32 thread_running;
	u32 thread_sleep;
	u32 cec_intr_stat;
	u32 cec_intr_read_stat;
	wait_queue_head_t wait_head;
	int tx_result;
	int tx_ping;
	struct circ_buf cec_dbg_buf;
	int rx_busy_workaround;
	int rx_busy_workaround_done;
	int rx_poll_workaround;
	int rx_poll_count;
	unsigned long tx_fail_jiffies;
};

static int lgdt_cec_buf_print(struct lgdt_cec *cec, const char *fmt, ...);

static void _cec_proc_status_read(struct seq_file *m, void* data);
static void _cec_proc_reg_dump(struct seq_file *m, void* data);
static void _cec_proc_dmesg_read(struct seq_file *m, void* data);

static irqreturn_t hdmicec_irg_handler(int irq, void *handle);

OS_PROC_SEQRD_DEFINE_EX(_cec_proc_status_fops, _cec_proc_status_read, 0)
OS_PROC_SEQRD_DEFINE_EX(_cec_proc_reg_dump_fops, _cec_proc_reg_dump, 0)
OS_PROC_SEQRD_DEFINE_EX(_cec_proc_dmesg_fops, _cec_proc_dmesg_read, 0)

static void _read32(unsigned int addr, unsigned int *data)
{
	SYS_IO_ReadRegArray(addr, 4, data);
}
static void __attribute__((unused)) _write32(unsigned int addr, unsigned int data)
{
	SYS_IO_WriteRegArray(addr, 4, &data);
}
static void _writemask32(unsigned int addr, unsigned int data, unsigned int mask)
{
	unsigned int read_data;
	SYS_IO_ReadRegArray(addr, 4, &read_data);
	data = (read_data & ~mask) | (data & mask);
	SYS_IO_WriteRegArray(addr, 4, &data);
}

static inline void hdmi_writel(struct lgdt_cec *cec, u32 val, int reg)
{
	writel(val, cec->hdmi_base + reg);
}

static inline u32 hdmi_readl(struct lgdt_cec *cec, int reg)
{
	return readl(cec->hdmi_base + reg);
}

static void hdmi_modl(struct lgdt_cec *cec, u32 data, u32 mask, int reg)
{
	u32 val = hdmi_readl(cec, reg) & ~mask;

	val |= data & mask;
	hdmi_writel(cec, val, reg);
}

static void hdmi_mask_writel(struct lgdt_cec *cec, u32 data, int reg,
		u32 shift, u32 mask)
{
	hdmi_modl(cec, data << shift, mask, reg);
}

static __attribute__((unused)) u32 hdmi_mask_readl(struct lgdt_cec *cec, int reg, u32 shift,
		u32 mask)
{
	return (hdmi_readl(cec, reg) & mask) >> shift;
}

static u32 dw_hdmi_get_int_val(struct lgdt_cec *cec, u32 stat_reg,
		u32 mask_reg)
{
	return hdmi_readl(cec, stat_reg) & hdmi_readl(cec, mask_reg);
}

static void _cec_proc_status_read(struct seq_file *m, void* data)
{
	unsigned int r_data;

	seq_printf(m, "[CEC DEBUG] start of CEC status info\n");

	seq_printf(m, "[CEC DEBUG] cec enable adap : %d \n", _g_cec->cec_enabled_adap );
	seq_printf(m, "[CEC DEBUG] cec enable HW : %d \n", _g_cec->cec_enabled_hw );
	seq_printf(m, "[CEC DEBUG] cec HDMI_CEC_INT_MASK_N 0x%x \n", hdmi_readl(_g_cec, HDMI_CEC_INT_MASK_N));
	seq_printf(m, "[CEC DEBUG] rx busy workaround : %d \n", _g_cec->rx_busy_workaround);
	seq_printf(m, "[CEC DEBUG] rx busy workaround done : %d \n", _g_cec->rx_busy_workaround_done);
	seq_printf(m, "[CEC DEBUG] rx poll workaround : %d \n", _g_cec->rx_poll_workaround);
	seq_printf(m, "[CEC DEBUG] rx poll count : %d \n", _g_cec->rx_poll_count);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		_read32(O26_CRG_HDMI_SYN_REGISTER_BASE + 0xc, &r_data);			//reg_soft_rst_hdmirx_prt1_main_n(bit10)
		seq_printf(m, "[CEC DEBUG] check reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit15) : 0x%x, [%s]\n", r_data, ((r_data&0x8000)==0x8000)?"NG":"OK" );
	}
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		_read32(O24_CRG_HDMI_SYN_REGISTER_BASE + 0xc, &r_data);			//reg_soft_rst_hdmirx_prt1_main_n(bit10)
		seq_printf(m, "[CEC DEBUG] check reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit15) : 0x%x, [%s]\n", r_data, ((r_data&0x8000)==0x8000)?"NG":"OK" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		_read32(M23_CRG_HDMI_SYN_REGISTER_BASE + 0xc, &r_data);			//reg_soft_rst_hdmirx_prt1_main_n(bit10)
		seq_printf(m, "[CEC DEBUG] check reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit10) : 0x%x, [%s]\n", r_data, ((r_data&0x400)==0x400)?"NG":"OK" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		_read32(O22_CRG_HDMI_SYN_REGISTER_BASE + 0xc, &r_data);			//reg_soft_rst_hdmirx_prt1_main_n(bit11)
		seq_printf(m, "[CEC DEBUG] check reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit11) : 0x%x, [%s]\n", r_data, ((r_data&0x800)==0x800)?"NG":"OK" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		_read32(E60_CRG_HDMI_SYN_REGISTER_BASE + 0x4, &r_data);			//reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit7)
		seq_printf(m, "[CEC DEBUG] check reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit7) : 0x%x, [%s]\n", r_data, ((r_data&0x80)==0x80)?"NG":"OK" );
	}
	else
	{
		_read32(O20_HDMI_SYN_REGISTER_BASE + 0x8, &r_data);			//reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit7)
		seq_printf(m, "[CEC DEBUG] check reg_hdmi__soft_rst_hdmirx_prt1_main_n : 0x%x, [%s]\n", r_data, ((r_data&0x10)==0x10)?"NG":"OK" );
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		_read32(O26_HDMI_SYN_REGISTER_BASE + 0x8, &r_data);			//HDMI Link prt0 CEC enable
		seq_printf(m, "[CEC DEBUG] HDMI Link prt0 CEC enable : 0x%x, [%s]\n", r_data, ((r_data&0x1)==0x1)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		_read32(O24_HDMI_SYN_REGISTER_BASE + 0x8, &r_data);			//HDMI Link prt0 CEC enable
		seq_printf(m, "[CEC DEBUG] HDMI Link prt0 CEC enable : 0x%x, [%s]\n", r_data, ((r_data&0x1)==0x1)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		_read32(M23_HDMI_SYN_REGISTER_BASE + 0x8, &r_data);			//HDMI Link prt0 CEC enable
		seq_printf(m, "[CEC DEBUG] HDMI Link prt0 CEC enable : 0x%x, [%s]\n", r_data, ((r_data&0x1)==0x1)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		_read32(O22_HDMI_SYN_REGISTER_BASE + 0x0, &r_data);			//HDMI Link prt0 CEC enable
		seq_printf(m, "[CEC DEBUG] HDMI Link prt0 CEC enable : 0x%x, [%s]\n", r_data, ((r_data&0x1)==0x1)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		_read32(E60_HDMI_SYN_REGISTER_BASE + 0xC, &r_data);			//HDMI Link prt0 CEC enable
		seq_printf(m, "[CEC DEBUG] HDMI Link prt0 CEC enable : 0x%x, [%s]\n", r_data, ((r_data&0x1)==0x1)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) )
	{
		_read32(O20_HDMI_SYN_REGISTER_BASE + 0x38, &r_data);			//HDMI Link prt0 CEC enable
		seq_printf(m, "[CEC DEBUG] HDMI Link prt0 CEC enable : 0x%x, [%s]\n", r_data, ((r_data&0x1)==0x1)?"OK":"NG" );
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		_read32(O26_CTOP_WOV_REGISTER_BASE + 0x38, &r_data);			//reg_pad_HDMI_CEC_SMT(bit 19)
		seq_printf(m, "[CEC DEBUG] check HDMI_CEC_SMT disabled (bit 19) : 0x%x, [%s]\n", r_data, ((r_data&0x00080000)==0x0)?"OK":"NG" );

		_read32(O26_HDMIRX_RC_REGISTER_BASE + 0x2D8, &r_data);			//AD_CEC_GF_EN(bit 0)
		seq_printf(m, "[CEC DEBUG] check AD_CEC_GF_EN enabled (bit 0) : 0x%x, [%s]\n", r_data, ((r_data&0x00000001)==0x1)?"OK":"NG" );

		_read32(O26_CTOP_WOV_REGISTER_BASE + 0x11c, &r_data);			//reg_pad_HDMI_CEC_mux_sel(bit 19:16)
		seq_printf(m, "[CEC DEBUG] check HDMI_CEC_mux_sel (bit 19:16) : 0x%x, [%s]\n", r_data, ((r_data&0x000f0000)==0x0)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		_read32(O24_CTOP_WOV_REGISTER_BASE + 0x100, &r_data);			//reg_pad_HDMI_CEC_mux_sel(bit 31:28)
		seq_printf(m, "[CEC DEBUG] check HDMI_CEC_mux_sel (bit 23:20) : 0x%x, [%s]\n", r_data, ((r_data&0xf0000000)==0x0)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		_read32(M23_CTOP_WOV_REGISTER_BASE + 0x10c, &r_data);			//reg_pad_HDMI_CEC_mux_sel(bit 23:20)
		seq_printf(m, "[CEC DEBUG] check HDMI_CEC_mux_sel (bit 23:20) : 0x%x, [%s]\n", r_data, ((r_data&0x00f00000)==0x0)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		_read32(O22_CTOP_WOV_REGISTER_BASE + 0x114, &r_data);			//reg_pad_HDMI_CEC_mux_sel(bit 3:0)
		seq_printf(m, "[CEC DEBUG] check HDMI_CEC_mux_sel (bit 3:0) : 0x%x, [%s]\n", r_data, ((r_data&0x3)==0x0)?"OK":"NG" );
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		_read32(E60_CTOP_WOV_REGISTER_BASE + 0x7c, &r_data);			//wov_syn:reg_pad_HDMI_CEC_mux_sel(bit 15:12)
		seq_printf(m, "[CEC DEBUG] check HDMI_CEC_mux_sel (bit 15:12) : 0x%x, [%s]\n", r_data, ((r_data&0x3000)==0x2000)?"OK":"NG" );
	}

	r_data = hdmi_readl(_g_cec, HDMI_CEC_ADDR);
	if(r_data != ((_g_cec->cec_valid_addrs << HDMI_CEC_ADDR_FOLLOWER_ADDR_OFFSET) & HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK) )
		seq_printf(m, "[CEC DEBUG] logical address NG : in register [0x%x] != [0x%x] \n", r_data, ((_g_cec->cec_valid_addrs << HDMI_CEC_ADDR_FOLLOWER_ADDR_OFFSET) & HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK));
	else
		seq_printf(m, "[CEC DEBUG] logical address OK [0x%x] \n", r_data);

	seq_printf(m, "[CEC DEBUG] end of CEC status info\n");

	return;
}

static void _cec_proc_reg_dump(struct seq_file *m, void* data)
{
	unsigned int i;

	seq_printf(m, "[CEC DEBUG] start of CEC link register dump\n");

	for(i=HDMI_CEC_TX_CONTROL;i<=HDMI_CEC_TX_BITTIME_CONFIG;i+=4)
		seq_printf(m, "[Addr:0x%04x : 0x%08x\n", i, hdmi_readl(_g_cec, i) );

	for(i=HDMI_CEC_INT_STATUS;i<=HDMI_CEC_INT_FORCE;i+=4)
		seq_printf(m, "[Addr:0x%04x : 0x%08x\n", i, hdmi_readl(_g_cec, i) );

	seq_printf(m, "[CEC DEBUG] End of CEC link register dump\n");

	return;
}

static void _cec_proc_dmesg_read(struct seq_file *m, void* data)
{
	unsigned int pointer;
	seq_printf(m, "[CEC DEBUG] start of CEC debug message : head [%d], tail [%d]\n", _g_cec->cec_dbg_buf.head, _g_cec->cec_dbg_buf.tail);
	if(_g_cec->cec_dbg_buf.tail == _g_cec->cec_dbg_buf.head)
		seq_printf(m, "[CEC DEBUG] No MSG !!! \n");
	else if(_g_cec->cec_dbg_buf.tail > _g_cec->cec_dbg_buf.head)	//head to tail
		for(pointer = _g_cec->cec_dbg_buf.head; pointer < _g_cec->cec_dbg_buf.tail; pointer +=DBG_BUF_WIDTH)
			seq_printf(m, "%s\n", &_g_cec->cec_dbg_buf.buf[pointer]);
	else	//head to end, and start to tail
	{
		for(pointer = _g_cec->cec_dbg_buf.head; pointer < DBG_BUF_SIZE; pointer +=DBG_BUF_WIDTH)
			seq_printf(m, "%s\n", &_g_cec->cec_dbg_buf.buf[pointer]);
		for(pointer = 0; pointer < _g_cec->cec_dbg_buf.tail; pointer +=DBG_BUF_WIDTH)
			seq_printf(m, "%s\n", &_g_cec->cec_dbg_buf.buf[pointer]);
	}
	seq_printf(m, "[CEC DEBUG] end of CEC debug message\n");

	return;
}
/**********************************************************************
 * synopsis cec api 
 * *******************************************************************/

static void dw_hdmi_cec_clear_ints(struct lgdt_cec *cec)
{
	hdmi_writel(cec, ~0x0, HDMI_CEC_INT_CLEAR);
}

static void dw_hdmi_cec_enable_ints(struct lgdt_cec *cec)
{
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_RX_EOM_OFFSET,
			HDMI_CEC_INT_MASK_N_RX_EOM_MASK);
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_TX_DRIVE_ERR_OFFSET,
			HDMI_CEC_INT_MASK_N_TX_DRIVE_ERR_MASK);
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_TX_NRETRANSMIT_FAIL_OFFSET,
			HDMI_CEC_INT_MASK_N_TX_NRETRANSMIT_FAIL_MASK);
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_TX_LINE_ERR_OFFSET,
			HDMI_CEC_INT_MASK_N_TX_LINE_ERR_MASK);
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_TX_ARBLOST_OFFSET,
			HDMI_CEC_INT_MASK_N_TX_ARBLOST_MASK);
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_TX_NACK_OFFSET,
			HDMI_CEC_INT_MASK_N_TX_NACK_MASK);
	hdmi_mask_writel(cec, 0x1, HDMI_CEC_INT_MASK_N,
			HDMI_CEC_INT_MASK_N_TX_DONE_OFFSET,
			HDMI_CEC_INT_MASK_N_TX_DONE_MASK);

	HDMI20_CEC_BUF_INFO(cec, "%s cec HDMI_CEC_INT_MASK_N 0x%x ! ", __func__, hdmi_readl(cec, HDMI_CEC_INT_MASK_N));

	if(hdmi_readl(cec, HDMI_CEC_INT_MASK_N) == 0)
		HDMI20_CEC_BUF_INFO(cec,"%s cec HDMI_CEC_INT_MASK_N write error !!!!! ", __func__);
}

static void dw_hdmi_cec_disable_ints(struct lgdt_cec *cec)
{
	hdmi_writel(cec, 0x0, HDMI_CEC_INT_MASK_N);
	HDMI20_CEC_BUF_INFO(cec, "%s cec HDMI_CEC_INT_MASK_N 0x%x ! ", __func__, hdmi_readl(cec, HDMI_CEC_INT_MASK_N));
}

static void dw_hdmi_cec_tx_raw_status(struct lgdt_cec *cec, u32 stat)
{
	u32 error_mask = HDMI_CEC_INT_STATUS_TX_NRETRANSMIT_FAIL |
		HDMI_CEC_INT_STATUS_TX_NACK |
		HDMI_CEC_INT_STATUS_TX_DRIVE_ERR |
		HDMI_CEC_INT_STATUS_TX_LINE_ERR;
	u32 wait_flag = HDMI_CEC_STATUS_TX_BUSY |
		HDMI_CEC_STATUS_FRAME_SEND_PENDING;

	if (hdmi_readl(cec, HDMI_CEC_STATUS) & wait_flag) {
		HDMI20_CEC_BUF_DEBUG(cec, "%s: tx busy", __func__);
		return;
	}

	if (stat & HDMI_CEC_INT_STATUS_TX_ARBLOST) {
		HDMI20_CEC_BUF_ERROR(cec, "%s: arbitration lost", __func__);
		cec->tx_fail_jiffies =  jiffies;
		cec_transmit_done(cec->adap, CEC_TX_STATUS_ARB_LOST,
				1, 0, 0, 0);
		cec->tx_result = CEC_TX_STATUS_ARB_LOST;
		cec->tx_ping = 0;
		return;
	}

	if (stat & HDMI_CEC_INT_STATUS_TX_DONE) {
		HDMI20_CEC_BUF_DEBUG(cec, "%s: transmission done", __func__);
		cec_transmit_done(cec->adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
		cec->tx_result = CEC_TX_STATUS_OK;
		cec->tx_ping = 0;
		return;
	}

	if (stat & error_mask) {
		/* If we reached here we have an error */
		u8 status = 0, nack_cnt = 0, low_drive_cnt = 0, error_cnt = 0;

		if( cec->tx_ping == 0)
			HDMI20_CEC_BUF_ERROR(cec, "%s: error found (stat=0x%x)", __func__, stat);
		else
			HDMI20_CEC_BUF_DEBUG(cec, "%s: error found (stat=0x%x)", __func__, stat);

		// clear CEC_TX_STATUS_MAX_RETRIES : to enable kernel framwork to retry tx.
		//if (stat & HDMI_CEC_INT_STATUS_TX_NRETRANSMIT_FAIL)
		if ( (stat & HDMI_CEC_INT_STATUS_TX_NRETRANSMIT_FAIL) && (cec->tx_ping == 1))	// for polling
			status |= CEC_TX_STATUS_MAX_RETRIES;
		if (stat & HDMI_CEC_INT_STATUS_TX_NACK) {
			status |= CEC_TX_STATUS_NACK;
			nack_cnt = 1;
		}
		if (stat & HDMI_CEC_INT_STATUS_TX_DRIVE_ERR) {
			status |= CEC_TX_STATUS_LOW_DRIVE;
			low_drive_cnt = 1;
		}
		if (stat & HDMI_CEC_INT_STATUS_TX_LINE_ERR) {
			status |= CEC_TX_STATUS_ERROR;
			error_cnt = 1;
		}
		cec->tx_fail_jiffies =  jiffies;

		cec_transmit_done(cec->adap, status, 0, nack_cnt,
				low_drive_cnt, error_cnt);
		cec->tx_result = status;
		cec->tx_ping = 0;
		return;
	}
}

static int hdmicec_hw_init(struct lgdt_cec *cec, bool enable)
{
	HDMI20_CEC_BUF_INFO(cec, "%s : enable %d", __func__, enable);

//	if (!cec->cec_enabled_hw && enable) {
	if (enable) {
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ) {
			_writemask32(O26_CTOP_WOV_REGISTER_BASE + 0x38, 0x00000000, 0x00080000);	//wov_pad:PAD_WOC14 reg_pad_HDMI_CEC_SMT(0x0 : Schmitt-triger Enable->Disable)
			_writemask32(O26_HDMIRX_RC_REGISTER_BASE + 0x2D8, 0x00000001, 0x00000001);	//hdmirx_rc:AD_CEC_GF_EN(0x1 : Glitch Free Filter Disable->Enable)
		}
		hdmi_writel(cec, 0x332323, HDMI_CEC_RX_BITTIME_CONFIG);	//modify RX Start Bit Timing (AVTASK-671 : CEC CTS)
		hdmi_writel(cec, 0x1, HDMI_CEC_LOCK_CONTROL);	//unlock rx buffer
		dw_hdmi_cec_enable_ints(cec);
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
			_writemask32(O26_CTOP_WOV_REGISTER_BASE + 0x11c, 0x0, 0x000f0000);	//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x0 : hdmi cec )
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
			_writemask32(O24_CTOP_WOV_REGISTER_BASE + 0x100, 0x0, 0xf0000000);	//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x0 : hdmi cec )
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
			_writemask32(M23_CTOP_WOV_REGISTER_BASE + 0x10c, 0x0, 0x00f00000);	//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x0 : hdmi cec )
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
			_writemask32(O22_CTOP_WOV_REGISTER_BASE + 0x114, 0x0, 0x3);	//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x0 : hdmi cec ??? )
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
			_writemask32(E60_CTOP_WOV_REGISTER_BASE + 0x7c, 0x2000, 0x3000);	//wov_syn:reg_pad_HDMI_CEC_mux_sel (0x2 : hdmi cec)
		else
			_writemask32(O20_CTOP_WOV_REGISTER_BASE + 0x30, 0x10000, 0x10000);	//reg_use_hdmi_link_cec
//	} else if (cec->cec_enabled_hw && !enable) {
	} else if (!enable) {
		dw_hdmi_cec_disable_ints(cec);
//		cec->cec_valid_addrs = 0;
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
			_writemask32(O26_CTOP_WOV_REGISTER_BASE + 0x11c, 0x2, 0x000f0000);		//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x2 : micom cec ???)
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
			_writemask32(O24_CTOP_WOV_REGISTER_BASE + 0x100, 0x2, 0xf0000000);		//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x2 : micom cec ???)
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
			_writemask32(M23_CTOP_WOV_REGISTER_BASE + 0x10c, 0x2, 0x00f00000);		//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x2 : micom cec ???)
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
			_writemask32(O22_CTOP_WOV_REGISTER_BASE + 0x114, 0x2, 0x3);		//wov_pad:reg_pad_HDMI_CEC_mux_sel (0x2 : micom cec ???)
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
			_writemask32(E60_CTOP_WOV_REGISTER_BASE + 0x7c, 0x0000, 0x3000);		//wov_syn:reg_pad_HDMI_CEC_mux_sel (0x0 : micom cec)
		else
			_writemask32(O20_CTOP_WOV_REGISTER_BASE + 0x30, 0x00000, 0x10000);		//reg_use_hdmi_link_cec
	}

	return 0;
}

static int dw_hdmi_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	unsigned int i=0;
	struct lgdt_cec *cec = adap->priv;
	u32 wait_flag = HDMI_CEC_STATUS_TX_BUSY |
		/*HDMI_CEC_STATUS_RX_BUSY | */
		HDMI_CEC_STATUS_FRAME_SEND_PENDING;
	u32 hdmi_cec_status ;

	hdmi_cec_status = hdmi_readl(cec, HDMI_CEC_STATUS);

	HDMI20_CEC_BUF_INFO(cec, "%s: cec_status [0x%x], enable=%d", __func__, hdmi_cec_status, enable);

//	hdmicec_hw_init(cec, enable);
	if (enable == FALSE) {
		hdmi_mask_writel(cec, 0x0, HDMI_CEC_ADDR,
				HDMI_CEC_ADDR_FOLLOWER_ADDR_OFFSET,
				HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK);
		cec->cec_valid_addrs = 0;
		return 0;
	}

//	for(i=0; (i<100) && ((hdmi_cec_status & wait_flag) == wait_flag);i++) {
	for(i=0; (i<100) && (hdmi_cec_status & wait_flag);i++) {
		if(i%10)
			HDMI20_CEC_BUF_DEBUG(cec, "%s: tx busy status[0x%x] count:%d", __func__,hdmi_cec_status, i);
		else
			HDMI20_CEC_BUF_INFO(cec, "%s: tx busy status[0x%x] count:%d", __func__,hdmi_cec_status, i);
		usleep_range(10000,15000);
		hdmi_cec_status = hdmi_readl(cec, HDMI_CEC_STATUS);
	}

	cec->cec_enabled_adap = enable;

	return 0;
}

static int dw_hdmi_cec_adap_log_addr(struct cec_adapter *adap, u8 addr)
{
	struct lgdt_cec *cec = adap->priv;
	unsigned int i, free_idx = DW_HDMI_MAX_ADDRS;
	u32 tmp;

	HDMI20_CEC_BUF_DEBUG(cec, "%s: addr=0x%x", __func__, addr);

	if (!cec->cec_enabled_adap)
		return addr == CEC_LOG_ADDR_INVALID ? 0 : -EIO;

	if (addr == CEC_LOG_ADDR_INVALID) {
		hdmi_mask_writel(cec, 0x0, HDMI_CEC_ADDR,
				HDMI_CEC_ADDR_FOLLOWER_ADDR_OFFSET,
				HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK);
		cec->cec_valid_addrs = 0;
		return 0;
	}

	for (i = 0; i < DW_HDMI_MAX_ADDRS; i++) {
		bool is_valid = cec->cec_valid_addrs & (1 << i);

		if (free_idx == DW_HDMI_MAX_ADDRS && !is_valid)
			free_idx = i;
		if (is_valid && cec->cec_addr[i] == addr)
			return 0;
	}

	if (i == DW_HDMI_MAX_ADDRS) {
		i = free_idx;
		if (i == DW_HDMI_MAX_ADDRS)
			return -ENXIO;
	}

	cec->cec_addr[i] = addr;
	HDMI20_CEC_BUF_INFO(cec, "cec-addr: <%2u>: %*phC", DW_HDMI_MAX_ADDRS, DW_HDMI_MAX_ADDRS, cec->cec_addr);
	cec->cec_valid_addrs |= 1 << i;
	HDMI20_CEC_BUF_DEBUG(cec, "cec-addr: valid_addrs:0x%x, i:%d", cec->cec_valid_addrs, i);

	tmp = hdmi_readl(cec, HDMI_CEC_ADDR);
	/*
	tmp |= (BIT(i) << HDMI_CEC_ADDR_FOLLOWER_ADDR_OFFSET) &
		HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK;
		*/
	/* fix to directly set logical address from addr value */
	tmp |= (BIT(0) << addr) &
		HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK;
	HDMI20_CEC_BUF_INFO(cec, "%s: cec addr = 0x%x",__func__, tmp);
	hdmi_writel(cec, tmp, HDMI_CEC_ADDR);
	return 0;
}

static int dw_hdmi_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
		u32 signal_free_time, struct cec_msg *msg)
{
	struct lgdt_cec *cec = adap->priv;
	u32 wait_flag = HDMI_CEC_STATUS_TX_BUSY |
		HDMI_CEC_STATUS_FRAME_SEND_PENDING;
	u8 len = msg->len;
	unsigned int i;
	u32 tmp;
	static int busy_count = 0;
	u32 hdmi_cec_status ;

	unsigned long end_jiffies, elapsed_jiffies;

//	HDMI20_CEC_INFO("cec-tx: <%2u>: %*ph", msg->len, msg->len, msg->msg);

	if (len > 16) {
		HDMI20_CEC_BUF_ERROR(cec, "cec-tx: attempt(%d), sft(%d), <%2u>: %*phC", attempts, signal_free_time, msg->len, msg->len, msg->msg);
		HDMI20_CEC_BUF_ERROR(cec, "%s: len > 16 (%d)", __func__, len);
		return -EINVAL;
	}
	else 
		attempts = 0;	// disable H/W re-transmission.
		//attempts = max(1, attempts - 1);

	if( (msg->len == 1) && (msg->msg[0] > 0x0) && (msg->msg[0] < 0xe) ) 	// ping : 240108 : 0xc to 0xe(webos changed to ping upto 0xd device, so bsp must be changed not to tranmit ping twice)
	{
		HDMI20_CEC_BUF_DEBUG(cec, "cec-tx: attempt(%d), sft(%d), <%2u>: %*phC", attempts, signal_free_time, msg->len, msg->len, msg->msg);
		cec->tx_ping = 1;
	}
	else if( (msg->len == 5) && (msg->msg[0] == 0x0f) && (msg->msg[1] == 0x87)) 	// report vendor ID
	{
		HDMI20_CEC_BUF_DEBUG(cec, "cec-tx: attempt(%d), sft(%d), <%2u>: %*phC", attempts, signal_free_time, msg->len, msg->len, msg->msg);
		cec->tx_ping = 1;
	}
	else
		HDMI20_CEC_BUF_INFO(cec, "cec-tx: attempt(%d), sft(%d), <%2u>: %*phC", attempts, signal_free_time, msg->len, msg->len, msg->msg);

	hdmi_cec_status = hdmi_readl(cec, HDMI_CEC_STATUS);

#ifdef CEC_TX_RETRY
	for(i=0;i<2;i++) {
		if( (hdmi_cec_status & wait_flag) == 0)
			break;
		usleep_range(100000,200000);
		HDMI20_CEC_BUF_INFO(cec, "cec-tx:retry[%d] status[0x%x]  attempt(%d), sft(%d), <%2u>: %*phC", i, hdmi_cec_status, attempts, signal_free_time, msg->len, msg->len, msg->msg);
		hdmi_cec_status = hdmi_readl(cec, HDMI_CEC_STATUS);
	}
#endif
	if (hdmi_cec_status & wait_flag) {

		if(busy_count > 99)
		{
			HDMI20_CEC_BUF_ERROR(cec, "%s: tx is busy[status:0x%x] : for %d times", __func__,hdmi_cec_status, busy_count);
			busy_count = 10;
		}
		else if(busy_count > 10)
			HDMI20_CEC_BUF_DEBUG(cec, "%s: tx is busy[status:0x%x]", __func__,hdmi_cec_status);
		else 
			HDMI20_CEC_BUF_ERROR(cec, "%s: tx is busy[status:0x%x]", __func__,hdmi_cec_status);

		if ( ( cec->rx_busy_workaround == 1) && (hdmi_cec_status & HDMI_CEC_STATUS_RX_BUSY) ) 
		{
			busy_count++;

			if( cec->rx_busy_workaround_done == 0)
			{
				HDMI20_CEC_BUF_ERROR(cec, "%s: RX BUSY [status:0x%x] : count = %d", __func__, hdmi_cec_status, busy_count );
				if(busy_count > 4)
				{
#if 0	// disable LINK CEC, this will raise CECTX_DRIVER_ERR_IRQ
					if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
					{
						HDMI20_CEC_BUF_ERROR(cec, "Disable HDMI CEC");
						_writemask32(E60_HDMI_SYN_REGISTER_BASE + 0xC, 0x0, 0x1);		//HDMI Link prt0 CEC enable 
						msleep(100);
						HDMI20_CEC_BUF_ERROR(cec, "Enable HDMI CEC");
						_writemask32(E60_HDMI_SYN_REGISTER_BASE + 0xC, 0x1, 0x1);		//HDMI Link prt0 CEC enable 
					}
#else	// clear Log Addr
					tmp = hdmi_readl(cec, HDMI_CEC_ADDR);

					HDMI20_CEC_BUF_ERROR(cec, "RESET Log Addr : 0x%x", tmp);

					hdmi_writel(cec, 0, HDMI_CEC_ADDR);

					msleep(100);

					HDMI20_CEC_BUF_ERROR(cec, "%s: restore cec addr = 0x%x",__func__, tmp);

					hdmi_writel(cec, tmp, HDMI_CEC_ADDR);
					busy_count = 0;
					cec->rx_busy_workaround_done = 1;
#endif
				}
			}
		}
		else
			busy_count = 0;

		return -EBUSY;
	}
	else
	{
		busy_count = 0;
		cec->rx_busy_workaround_done = 0;	//fix : 250122
	}

	end_jiffies = jiffies;
	elapsed_jiffies = end_jiffies - cec->tx_fail_jiffies;

	if( (cec->tx_result != CEC_TX_STATUS_OK)	//previous tx failed
			&& (elapsed_jiffies < msecs_to_jiffies(15)) )
	{
		HDMI20_CEC_BUF_INFO(cec, "cec-tx [%lu]msec after tx fail 0x%x",elapsed_jiffies, cec->tx_result);
		//msleep(10);
		usleep_range(10000, 15000);
	}

	for (i = 0; i < HDMI_CEC_TX_DATA_MAX_LEN; i++)
		hdmi_writel(cec, 0x0, HDMI_CEC_TX_DATA(i));

	for (i = 0; i < len; i++) {
		tmp = hdmi_readl(cec, HDMI_CEC_TX_DATA(i / sizeof(u32)));
		tmp |= (msg->msg[i] << ((i % sizeof(u32)) * 8));
		hdmi_writel(cec, tmp, HDMI_CEC_TX_DATA(i / sizeof(u32)));
	}

	hdmi_mask_writel(cec, attempts, HDMI_CEC_CONFIG,
			HDMI_CEC_CONFIG_FRAME_NRETRANS_OFFSET,
			HDMI_CEC_CONFIG_FRAME_NRETRANS_MASK);

	hdmi_writel(cec, len - 1, HDMI_CEC_TX_COUNT);
	hdmi_writel(cec, 0x1, HDMI_CEC_TX_CONTROL);

	HDMI20_CEC_BUF_DEBUG(cec, "CEC TX data write done");

	return 0;
}

static const struct cec_adap_ops dw_hdmi_cec_adap_ops = {
	.adap_enable = dw_hdmi_cec_adap_enable,
	.adap_log_addr = dw_hdmi_cec_adap_log_addr,
	.adap_transmit = dw_hdmi_cec_adap_transmit,
};

/***************************************************************
 * *************************************************************/
static irqreturn_t hdmicec_irg_handler(int irq, void *handle)
{
	u32 cec_stat;
	//struct lgdt_cec *cec = _g_cec;
	struct lgdt_cec *cec = handle;

	if(cec == NULL)
		return -1;

	if(!cec->cec_enabled_hw)
		return -1;

	cec_stat = dw_hdmi_get_int_val(cec,
			HDMI_CEC_INT_STATUS,
			HDMI_CEC_INT_MASK_N);

	cec->cec_intr_stat = cec_stat;

	/* Clear interrupts */
	dw_hdmi_cec_clear_ints(cec);

	return IRQ_WAKE_THREAD;
}

static irqreturn_t hdmicec_irq_thread_handler(int irq, void *handle)
{
	struct lgdt_cec *cec = handle;
	u32 cec_stat;
	u32 rx_count_status;

	HDMI20_CEC_BUF_DEBUG(cec, "%s: irq=0x%x", __func__, cec->cec_intr_stat);

	dw_hdmi_cec_tx_raw_status(cec, cec->cec_intr_stat);

	cec_stat = cec->cec_intr_stat;
	cec->cec_intr_stat = 0;

	rx_count_status = hdmi_readl(cec, HDMI_CEC_RX_COUNT_STATUS);

	if ( (cec_stat & HDMI_CEC_INT_STATUS_RX_EOM) || ( (rx_count_status & BIT(8)) && cec->rx_poll_workaround ) )
	{
		struct cec_msg msg;
		u8 i;

		/*if (!(hdmi_readl(cec, HDMI_CEC_RX_COUNT_STATUS) & BIT(8)))
		  return IRQ_HANDLED;*/

		if ( !(cec_stat & HDMI_CEC_INT_STATUS_RX_EOM) && (rx_count_status & BIT(8)) ) {
			HDMI20_CEC_BUF_INFO(cec, "Without EOM Intr, rx_count_status : 0x%x", rx_count_status);
			cec->rx_poll_count++;
		}

		/* New message received */
		msg.len = (hdmi_readl(cec, HDMI_CEC_RX_COUNT_STATUS) & GENMASK(3,0)) + 1;
		if (msg.len > 16)
			msg.len = 16;

		for (i = 0; i < msg.len; i++) {
			u32 val = hdmi_readl(cec, HDMI_CEC_RX_DATA(i / sizeof(u32)));
			msg.msg[i] = (val >> ((i % sizeof(u32)) * 8)) & GENMASK(7,0);
		}

		hdmi_writel(cec, 0x1, HDMI_CEC_LOCK_CONTROL);
		cec_received_msg(cec->adap, &msg);

		if( (msg.len == 1) ) 	// ping
			HDMI20_CEC_BUF_DEBUG(cec, "cec-read: <%2u>: %*phC", msg.len, msg.len, msg.msg);
		else
			HDMI20_CEC_BUF_INFO(cec, "cec-read: <%2u>: %*phC", msg.len, msg.len, msg.msg);
	}

	return IRQ_HANDLED;
}

static inline int lgdt_cec_init(struct lgdt_cec *cec)
{

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		_writemask32(O26_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x8000);	//reg_soft_rst_hdmirx_prt1_main_n(bit15)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		_writemask32(O24_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x8000);	//reg_soft_rst_hdmirx_prt1_main_n(bit15)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		_writemask32(M23_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x400);	//reg_soft_rst_hdmirx_prt1_main_n(bit10)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		_writemask32(O22_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x800);	//reg_soft_rst_hdmirx_prt1_main_n(bit11)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		_writemask32(E60_CRG_HDMI_SYN_REGISTER_BASE + 0x4, 0x0, 0x80);	//reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit7)
	else
		_writemask32(O20_HDMI_SYN_REGISTER_BASE + 0x8, 0x0, 0x10);		//reg_hdmi__soft_rst_hdmirx_prt1_main_n

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		_writemask32(O26_HDMI_SYN_REGISTER_BASE + 0x8, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		_writemask32(O24_HDMI_SYN_REGISTER_BASE + 0x8, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		_writemask32(M23_HDMI_SYN_REGISTER_BASE + 0x8, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		_writemask32(O22_HDMI_SYN_REGISTER_BASE + 0x0, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		_writemask32(E60_HDMI_SYN_REGISTER_BASE + 0xC, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) )
		_writemask32(O20_HDMI_SYN_REGISTER_BASE + 0x38, 0x1, 0x1);		//HDMI Link prt0 CEC enable

	if(!cec->cec_enabled_hw)
	{
		hdmicec_hw_init(cec, TRUE);
		cec->cec_enabled_hw = TRUE;
	}

	cec->tx_result = CEC_TX_STATUS_OK;
	cec->rx_busy_workaround = 1;
	cec->rx_busy_workaround_done = 0;

	cec->rx_poll_workaround = 1;
	cec->rx_poll_count = 0;

	return 0;
}

static void lge_cec_adapter_config(struct cec_adapter *adap)
{
	if(adap) {
		adap->log_addrs.num_log_addrs = 1;
		adap->log_addrs.log_addr_type[0] = CEC_LOG_ADDR_TYPE_TV;
		adap->log_addrs.cec_version = CEC_VERSION_1_4;
		adap->log_addrs.vendor_id = CEC_VENDOR_ID;
	}
}

static int	_cec_readprocfunction(	UINT32 procId, char* buffer )
{
	int		ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_CEC_AUTHOR:
		{
			ret = snprintf( buffer, 96, "%s %d\n", "wonsik.do (wonsik.do@lge.com) :", CEC_DRV_VER  );
		}
		break;

		default:
		{
			ret = snprintf( buffer, 96, "%s(%d)\n", "unimplemented read proc", procId );
		}
		break;
	}

	return ret;
}

static int _cec_writeprocfunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_CEC_TX:
		{
			int i;
			int count = 0;
			unsigned long input_data;
			char __attribute__((unused)) input_string[CEC_MAX_MSG_SIZE*2];
			struct cec_msg tx_data;

			sscanf( command, "0x%lx", &input_data);
			printk("input data 0x%lx\n", input_data);

			count = 0;

			for (i=7;i >= 0; i --)
			{
				if(( (input_data>>( i * 8) )&0xff) != 0)
				{
					for (count = i; count >=0; count --)
					{
						tx_data.msg[i-count] = (input_data >> (count * 8)) & 0xff;
					}
					break;
				}
			}
			count ++;

			tx_data.len = i + 1;
			dw_hdmi_cec_adap_transmit(_g_cec->adap, 4, 5, &tx_data);
		}
		break;

		case PROC_ID_CEC_WORKAROUND:
		{
			unsigned int index, data;

			sscanf( command, "0x%x 0x%x", &index, &data);
			printk("input index 0x%x, data 0x%x\n", index, data);

			if(index == 0)
			{
				_g_cec->rx_busy_workaround = data;
				printk("rx_busy_workaround : 0x%x\n", _g_cec->rx_busy_workaround);
			}
			else
				printk("wrong index number : 0x%x\n", index);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

static OS_PROC_DESC_TABLE_T	_g_cec_device_proc_table[] =
{
	{ "author",		PROC_ID_CEC_AUTHOR  , OS_PROC_FLAG_READ },
	{ "cec_status",		PROC_ID_CEC_STATUS,     OS_PROC_FLAG_SEQRD, (void*)&_cec_proc_status_fops},
	{ "cec_dmesg",		PROC_ID_CEC_DMESG,     OS_PROC_FLAG_SEQRD, (void*)&_cec_proc_dmesg_fops},
	{ "cec_reg_dump",		PROC_ID_CEC_REG_DUMP,     OS_PROC_FLAG_SEQRD, (void*)&_cec_proc_reg_dump_fops},
	{ "cec_tx",		PROC_ID_CEC_TX,     OS_PROC_FLAG_WRITE},
	{ "cec_workaround",		PROC_ID_CEC_WORKAROUND,     OS_PROC_FLAG_WRITE},
	{ NULL, 		PROC_ID_CEC_MAX		, 0 }
};

static void	lgdt_cec_proc_init (void)
{
	OS_PROC_CreateEntryEx ( "cec", _g_cec_device_proc_table,
											_cec_readprocfunction,
											_cec_writeprocfunction );
}

static int lgdt_cec_alloc_dbg_buffer(struct lgdt_cec *cec)
{
	//cec->cec_dbg_buf.buf = kzalloc(DBG_BUF_SIZE, GFP_KERNEL);
	cec->cec_dbg_buf.buf = vzalloc(DBG_BUF_SIZE);

	if (!cec->cec_dbg_buf.buf)
		return -ENOMEM;

	cec->cec_dbg_buf.head = 0;
	cec->cec_dbg_buf.tail = 0;

	return 0;
}

static int __attribute__((unused)) lgdt_cec_reset_dbg_buffer(struct lgdt_cec *cec)
{
	if (!cec->cec_dbg_buf.buf)
		return -ENOMEM;

	cec->cec_dbg_buf.head = 0;
	cec->cec_dbg_buf.tail = 0;

	return 0;
}

static int lgdt_cec_put_dbg_data(struct lgdt_cec *cec, char *dbg_msg)
{
    if (!cec->cec_dbg_buf.buf)
        return -ENOMEM;

//	HDMI20_CEC_INFO("head:0x%x, tail:0x%x\n", cec->cec_dbg_buf.head, cec->cec_dbg_buf.tail);
	memcpy(&cec->cec_dbg_buf.buf[cec->cec_dbg_buf.tail], dbg_msg, DBG_BUF_WIDTH);
	cec->cec_dbg_buf.tail+= DBG_BUF_WIDTH;
	if(cec->cec_dbg_buf.tail >= DBG_BUF_SIZE)
		cec->cec_dbg_buf.tail = 0;
	if(cec->cec_dbg_buf.tail == cec->cec_dbg_buf.head)
	{
		cec->cec_dbg_buf.head+= DBG_BUF_WIDTH;
		if(cec->cec_dbg_buf.head >= DBG_BUF_SIZE)
			cec->cec_dbg_buf.head = 0;
	}

	return 0;
}


static int lgdt_cec_probe(struct platform_device *pdev)
{
	struct lgdt_cec *cec;
	struct resource *res[4];
	int ret = 0;

	cec = devm_kzalloc(&pdev->dev, sizeof(struct lgdt_cec), GFP_KERNEL);

	if (!cec)
		return -ENOMEM;

	init_waitqueue_head(&cec->wait_head);

	lgdt_cec_alloc_dbg_buffer(cec);

	res[0] = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	if (!res[0]) {
		HDMI20_CEC_ERROR(
			"Unable to allocate resources for device [%s]", res[0]->name);
		return -EBUSY;
	}

	HDMI20_CEC_INFO("cec res[0] start [0x%llx], size[0x%x]", res[0]->start, (UINT32)resource_size(res[0]));
	if (!devm_request_mem_region(&pdev->dev, res[0]->start, resource_size(res[0]),
		pdev->name)) {
		HDMI20_CEC_ERROR(
			"Unable to request mem region for device");
		return -EBUSY;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
	cec->hdmi_base = devm_ioremap(&pdev->dev, res[0]->start,resource_size(res[0]));
#else
	cec->hdmi_base = devm_ioremap_nocache(&pdev->dev, res[0]->start,resource_size(res[0]));
#endif

	if (!cec->hdmi_base) {
		HDMI20_CEC_ERROR("Unable to grab IOs for device");
		return -EBUSY;
	}

	/* set context info. */
	cec->dev = &pdev->dev;

	/* set context info. */
	platform_set_drvdata(pdev, cec);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		cec->irq = platform_get_irq(pdev, 0);
		if (cec->irq < 0) {
			HDMI20_CEC_ERROR("Unable to get irq for device");
			return -ENOENT;
		}
		else
			HDMI20_CEC_INFO("cec hdmi irq [%d]", cec->irq);

//		ret = request_irq(cec->irq, (irq_handler_t)hdmicec_irg_handler, 0, "hdmicec", NULL);
		ret = request_threaded_irq(cec->irq, hdmicec_irg_handler, hdmicec_irq_thread_handler, IRQF_TRIGGER_RISING, "hdmicec", cec);
	}

	cec->adap = cec_allocate_adapter(&dw_hdmi_cec_adap_ops, cec, LGDT_CEC_NAME,
		CEC_CAP_LOG_ADDRS | CEC_CAP_PHYS_ADDR | CEC_CAP_TRANSMIT/* |
		CEC_CAP_PASSTHROUGH */,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		CEC_MAX_LOG_ADDRS);
#else
		CEC_MAX_LOG_ADDRS, &pdev->dev);
#endif


	if (IS_ERR(cec->adap)) {
		ret |= -ENOMEM;
		HDMI20_CEC_ERROR("Couldn't create cec adapter");
		goto cec_error;
	}

	/* XXX: remove this; userspace should invoke ioctl S_LOG_ADDRS */
	lge_cec_adapter_config(cec->adap);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	ret |= cec_register_adapter(cec->adap, &pdev->dev);
#else
	ret |= cec_register_adapter(cec->adap);
#endif
	if (ret) {
		HDMI20_CEC_ERROR("Couldn't register device");
		goto cec_error;
	}

//	platform_set_drvdata(pdev, cec);

	lgdt_cec_init(cec);

	_g_cec = cec;

	lgdt_cec_proc_init ();


	return 0;

cec_error:
	cec_delete_adapter(cec->adap);

	return ret;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void lgdt_cec_remove(struct platform_device *pdev)
#else
static int lgdt_cec_remove(struct platform_device *pdev)
#endif
{
	struct lgdt_cec *cec = platform_get_drvdata(pdev);

	clk_disable_unprepare(cec->clk);

	cec_unregister_adapter(cec->adap);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

#ifdef CONFIG_PM
static int lgdt_cec_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct lgdt_cec *cec = platform_get_drvdata(pdev);

	HDMI20_CEC_BUF_INFO(cec, "%s : enable %d", __func__, cec->cec_enabled_adap);
	//dev_notice(&pdev->dev, "suspend\n");

	if(cec->cec_enabled_hw)
		hdmicec_hw_init(cec, FALSE);

	return 0;
}

static int lgdt_cec_resume(struct platform_device *pdev)
{
	struct lgdt_cec *cec = platform_get_drvdata(pdev);
	u32 tmp;

	HDMI20_CEC_BUF_INFO(cec, "%s : enable %d", __func__, cec->cec_enabled_adap);
	//dev_notice(&pdev->dev, "resume\n");

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		_writemask32(O26_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x8000);	//reg_soft_rst_hdmirx_prt1_main_n(bit15)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		_writemask32(O24_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x8000);	//reg_soft_rst_hdmirx_prt1_main_n(bit15)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		_writemask32(M23_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x400);	//reg_soft_rst_hdmirx_prt1_main_n(bit10)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		_writemask32(O22_CRG_HDMI_SYN_REGISTER_BASE + 0xc, 0x0, 0x800);	//reg_soft_rst_hdmirx_prt1_main_n(bit11)
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		_writemask32(E60_CRG_HDMI_SYN_REGISTER_BASE + 0x4, 0x0, 0x80);	//reg_hdmi__soft_rst_hdmirx_prt1_main_n(bit7)
	else
		_writemask32(O20_HDMI_SYN_REGISTER_BASE + 0x8, 0x0, 0x10);		//CTOP_SYN:hdmi:CRG_HDMI02:reg_hdmi__soft_rst_hdmirx_prt1_main_n

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		_writemask32(O26_HDMI_SYN_REGISTER_BASE + 0x8, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		_writemask32(O24_HDMI_SYN_REGISTER_BASE + 0x8, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		_writemask32(M23_HDMI_SYN_REGISTER_BASE + 0x8, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		_writemask32(O22_HDMI_SYN_REGISTER_BASE + 0x0, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		_writemask32(E60_HDMI_SYN_REGISTER_BASE + 0xC, 0x1, 0x1);		//HDMI Link prt0 CEC enable
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) )
		_writemask32(O20_HDMI_SYN_REGISTER_BASE + 0x38, 0x1, 0x1);		//HDMI Link prt0 CEC enable

	if(cec->cec_enabled_hw)
	{
		hdmicec_hw_init(cec, TRUE);

		if(cec->cec_valid_addrs)
		{
			HDMI20_CEC_BUF_INFO(cec, "cec-resume: valid_addrs:0x%x", cec->cec_valid_addrs);

			tmp = hdmi_readl(cec, HDMI_CEC_ADDR);
			tmp |= (cec->cec_valid_addrs << HDMI_CEC_ADDR_FOLLOWER_ADDR_OFFSET) &
				HDMI_CEC_ADDR_FOLLOWER_ADDR_MASK;
			HDMI20_CEC_BUF_INFO(cec, "%s: cec addr = 0x%x",__func__, tmp);
			hdmi_writel(cec, tmp, HDMI_CEC_ADDR);
		}
	}

	cec->tx_result = CEC_TX_STATUS_OK;
	cec->rx_busy_workaround_done = 0;

	return 0;
}
#endif

static void  lgdt_cec_release(struct device *dev)
{
	HDMI20_CEC_INFO("device released");
}

static const struct of_device_id lgdt_cec_of_match[] = {
	{ .compatible = "lge,lgdt-hdmi-cec", },
	{},
};
MODULE_DEVICE_TABLE(of, lgdt_cec_of_match);

struct platform_driver lgdt_cec_driver = {
	.driver = {
		.name = LGDT_CEC_NAME,
		.of_match_table = of_match_ptr(lgdt_cec_of_match),
		.owner = THIS_MODULE,
	},
	.probe = lgdt_cec_probe,
	.remove = lgdt_cec_remove,

#ifdef CONFIG_PM
	.suspend = lgdt_cec_suspend,
	.resume = lgdt_cec_resume,
#endif
};

static struct resource o26_cec_resources[] = {
	{
		.start	= O26_HDMI_REGISTER_BASE,
		.end	= O26_HDMI_REGISTER_BASE + 0x530C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmicec_register"
	},
	{
		.start	= O26_HDMI_SYN_REGISTER_BASE,
		.end	= O26_HDMI_SYN_REGISTER_BASE + 0x8 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctophdmibnd_register"
	},
	{
		.start	= O26_CTOP_WOV_REGISTER_BASE,
		.end	= O26_CTOP_WOV_REGISTER_BASE + 0x11c + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctopwov_register"
	},
	{
		.start	= O26_CRG_HDMI_SYN_REGISTER_BASE,
		.end	= O26_CRG_HDMI_SYN_REGISTER_BASE + 0xc + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "crghdmisyn_register"
	},
	{
		.start	= O26_HDMICEC_IRQ_PORT1,
		.end	= O26_HDMICEC_IRQ_PORT1,
		.flags	= IORESOURCE_IRQ,
		.name	= "irq",
	}
};


struct platform_device o26_cec_device = {
	.name = LGDT_CEC_NAME,
	.resource	= o26_cec_resources,
	.num_resources	= ARRAY_SIZE(o26_cec_resources),
	.id = 0,
	.id = -1,
	.dev = {
		.release = lgdt_cec_release,
	},
};


static struct resource o24_cec_resources[] = {
	{
		.start	= O24_HDMI_REGISTER_BASE,
		.end	= O24_HDMI_REGISTER_BASE + 0x530C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmicec_register"
	},
	{
		.start	= O24_HDMI_SYN_REGISTER_BASE,
		.end	= O24_HDMI_SYN_REGISTER_BASE + 0x8 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctophdmibnd_register"
	},
	{
		.start	= O24_CTOP_WOV_REGISTER_BASE,
		.end	= O24_CTOP_WOV_REGISTER_BASE + 0x10c + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctopwov_register"
	},
	{
		.start	= O24_CRG_HDMI_SYN_REGISTER_BASE,
		.end	= O24_CRG_HDMI_SYN_REGISTER_BASE + 0xc + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "crghdmisyn_register"
	},
	{
		.start	= O24_HDMICEC_IRQ_PORT1,
		.end	= O24_HDMICEC_IRQ_PORT1,
		.flags	= IORESOURCE_IRQ,
		.name	= "irq",
	}
};


struct platform_device o24_cec_device = {
	.name = LGDT_CEC_NAME,
	.resource	= o24_cec_resources,
	.num_resources	= ARRAY_SIZE(o24_cec_resources),
	.id = 0,
	.id = -1,
	.dev = {
		.release = lgdt_cec_release,
	},
};


//M23
static struct resource lgdt1315_cec_resources[] = {
	{
		.start	= M23_HDMI_REGISTER_BASE,
		.end	= M23_HDMI_REGISTER_BASE + 0x530C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmicec_register"
	},
	{
		.start	= M23_HDMI_SYN_REGISTER_BASE,
		.end	= M23_HDMI_SYN_REGISTER_BASE + 0x8 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctophdmibnd_register"
	},
	{
		.start	= M23_CTOP_WOV_REGISTER_BASE,
		.end	= M23_CTOP_WOV_REGISTER_BASE + 0x10c + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctopwov_register"
	},
	{
		.start	= M23_CRG_HDMI_SYN_REGISTER_BASE,
		.end	= M23_CRG_HDMI_SYN_REGISTER_BASE + 0xc + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "crghdmisyn_register"
	},
	{
		.start	= M23_HDMICEC_IRQ_PORT1,
		.end	= M23_HDMICEC_IRQ_PORT1,
		.flags	= IORESOURCE_IRQ,
		.name	= "irq",
	}
};


struct platform_device lgdt1315_cec_device = {
	.name = LGDT_CEC_NAME,
	.resource	= lgdt1315_cec_resources,
	.num_resources	= ARRAY_SIZE(lgdt1315_cec_resources),
	.id = 0,
	.id = -1,
	.dev = {
		.release = lgdt_cec_release,
	},
};

//O22
static struct resource lgdt1314_cec_resources[] = {
	{
		.start	= O22_HDMI_REGISTER_BASE,
		.end	= O22_HDMI_REGISTER_BASE + 0x530C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmicec_register"
	},
	{
		.start	= O22_HDMI_SYN_REGISTER_BASE,
		.end	= O22_HDMI_SYN_REGISTER_BASE + 0x8 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctophdmibnd_register"
	},
	{
		.start	= O22_CTOP_WOV_REGISTER_BASE,
		.end	= O22_CTOP_WOV_REGISTER_BASE + 0x114 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctopwov_register"
	},
	{
		.start	= O22_CRG_HDMI_SYN_REGISTER_BASE,
		.end	= O22_CRG_HDMI_SYN_REGISTER_BASE + 0x20 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "crghdmisyn_register"
	},
	{
		.start	= O22_HDMICEC_IRQ_PORT1,
		.end	= O22_HDMICEC_IRQ_PORT1,
		.flags	= IORESOURCE_IRQ,
		.name	= "irq",
	}
};


struct platform_device lgdt1314_cec_device = {
	.name = LGDT_CEC_NAME,
	.resource	= lgdt1314_cec_resources,
	.num_resources	= ARRAY_SIZE(lgdt1314_cec_resources),
	.id = 0,
	.id = -1,
	.dev = {
		.release = lgdt_cec_release,
	},
};

static struct resource lgdt1811_cec_resources[] = {
	{
		.start	= E60_HDMI_REGISTER_BASE,
		.end	= E60_HDMI_REGISTER_BASE + 0x530C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmicec_register"
	},
	{
		.start	= E60_HDMI_SYN_REGISTER_BASE,
		.end	= E60_HDMI_SYN_REGISTER_BASE + 0xC + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctophdmisyn_register"
	},
	{
		.start	= E60_CTOP_WOV_REGISTER_BASE,
		.end	= E60_CTOP_WOV_REGISTER_BASE + 0x108 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctopwov_register"
	},
	{
		.start	= E60_CRG_HDMI_SYN_REGISTER_BASE,
		.end	= E60_CRG_HDMI_SYN_REGISTER_BASE + 0x20 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "crghdmisyn_register"
	},
	{
		.start	= E60_HDMICEC_IRQ_PORT1,
		.end	= E60_HDMICEC_IRQ_PORT4,
		.flags	= IORESOURCE_IRQ,
		.name	= "irq",
	}
};


struct platform_device lgdt1811_cec_device = {
	.name = LGDT_CEC_NAME,
	.resource	= lgdt1811_cec_resources,
	.num_resources	= ARRAY_SIZE(lgdt1811_cec_resources),
	.id = 0,
	.id = -1,
	.dev = {
		.release = lgdt_cec_release,
	},
};

static struct resource lgdt1212_cec_resources[] = {
	{
		.start	= O20_HDMI_REGISTER_BASE,
		.end	= O20_HDMI_REGISTER_BASE + 0x530C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmicec_register"
	},
	{
		.start	= O20_HDMI_SYN_REGISTER_BASE,
		.end	= O20_HDMI_SYN_REGISTER_BASE + 0x34 + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "hdmisyn_register"
	},
	{
		.start	= O20_CTOP_WOV_REGISTER_BASE,
		.end	= O20_CTOP_WOV_REGISTER_BASE + 0x12C + 3,
		.flags	= IORESOURCE_MEM,
		.name	= "ctopwov_register"
	},
	/*
	{
		.start	= 20,
		.end	= 20,
		.flags	= IORESOURCE_IRQ,
		.name	= "irq",
	}
	*/
};


struct platform_device lgdt1212_cec_device = {
	.name = LGDT_CEC_NAME,
	.resource	= lgdt1212_cec_resources,
	.num_resources	= ARRAY_SIZE(lgdt1212_cec_resources),
	.id = 0,
	.id = -1,
	.dev = {
		.release = lgdt_cec_release,
	},
};

int hdmicec_init(void)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
#ifdef KDRV_CONFIG_PM
#if 0
		module_platform_driver(lgdt_cec_driver);
#else
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
		{
			if(platform_driver_register(&lgdt_cec_driver) < 0)
			{
				HDMI20_CEC_INFO("[%s] platform driver register failed",LGDT_CEC_NAME);
			}
			else
			{
				if(platform_device_register(&o26_cec_device))
				{
					platform_driver_unregister(&lgdt_cec_driver);
					HDMI20_CEC_INFO("[%s] platform device register failed",LGDT_CEC_NAME);
				}
				else
				{
					HDMI20_CEC_INFO("[%s] platform register done : ver %d ", LGDT_CEC_NAME, CEC_DRV_VER);
				}
			}
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		{
			if(platform_driver_register(&lgdt_cec_driver) < 0)
			{
				HDMI20_CEC_INFO("[%s] platform driver register failed",LGDT_CEC_NAME);
			}
			else
			{
				if(platform_device_register(&o24_cec_device))
				{
					platform_driver_unregister(&lgdt_cec_driver);
					HDMI20_CEC_INFO("[%s] platform device register failed",LGDT_CEC_NAME);
				}
				else
				{
					HDMI20_CEC_INFO("[%s] platform register done : ver %d ", LGDT_CEC_NAME, CEC_DRV_VER);
				}
			}
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
		{
			if(platform_driver_register(&lgdt_cec_driver) < 0)
			{
				HDMI20_CEC_INFO("[%s] platform driver register failed",LGDT_CEC_NAME);
			}
			else
			{
				if(platform_device_register(&lgdt1315_cec_device))
				{
					platform_driver_unregister(&lgdt_cec_driver);
					HDMI20_CEC_INFO("[%s] platform device register failed",LGDT_CEC_NAME);
				}
				else
				{
					HDMI20_CEC_INFO("[%s] platform register done : ver %d ", LGDT_CEC_NAME, CEC_DRV_VER);
				}
			}
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		{
			if(platform_driver_register(&lgdt_cec_driver) < 0)
			{
				HDMI20_CEC_INFO("[%s] platform driver register failed",LGDT_CEC_NAME);
			}
			else
			{
				if(platform_device_register(&lgdt1314_cec_device))
				{
					platform_driver_unregister(&lgdt_cec_driver);
					HDMI20_CEC_INFO("[%s] platform device register failed",LGDT_CEC_NAME);
				}
				else
				{
					HDMI20_CEC_INFO("[%s] platform register done : ver %d ", LGDT_CEC_NAME, CEC_DRV_VER);
				}
			}
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		{
			if(platform_driver_register(&lgdt_cec_driver) < 0)
			{
				HDMI20_CEC_INFO("[%s] platform driver register failed",LGDT_CEC_NAME);
			}
			else
			{
				if(platform_device_register(&lgdt1811_cec_device))
				{
					platform_driver_unregister(&lgdt_cec_driver);
					HDMI20_CEC_INFO("[%s] platform device register failed",LGDT_CEC_NAME);
				}
				else
				{
					HDMI20_CEC_INFO("[%s] platform register done : ver %d ", LGDT_CEC_NAME, CEC_DRV_VER);
				}
			}
		}
		else
		{
			if(platform_driver_register(&lgdt_cec_driver) < 0)
			{
				HDMI20_CEC_INFO("[%s] platform driver register failed",LGDT_CEC_NAME);
			}
			else
			{
				if(platform_device_register(&lgdt1212_cec_device))
				{
					platform_driver_unregister(&lgdt_cec_driver);
					HDMI20_CEC_INFO("[%s] platform device register failed",LGDT_CEC_NAME);
				}
				else
				{
					HDMI20_CEC_INFO("[%s] platform register done", LGDT_CEC_NAME);
				}
			}
		}
#endif
#endif
		return 0;
	}
	else
		return -1;
}

static int lgdt_cec_buf_print(struct lgdt_cec *cec, const char *fmt, ...)
{
	int ret;
	va_list     		args;
	char buf[DBG_BUF_WIDTH];
	unsigned int sec, usec;
	unsigned long clock;

	if (!cec->cec_dbg_buf.buf)
		return -ENOMEM;

	clock = sched_clock();
	sec = (clock / 1000000000);
	if(sec >= 100000)
		sec %= 100000;
	usec = (clock / 1000);
	if(usec >= 1000000)
		usec %= 1000000;

	ret = sprintf(buf, "[%5u.%6u][cec] ", sec, usec);
	
	va_start(args, fmt);
	ret |= vsnprintf(&buf[20], sizeof(buf)-20, fmt, args);				
	va_end(args);
//	printk("%s\n", buf);				
	ret |= lgdt_cec_put_dbg_data(cec, buf);

	return ret;
}

//module_platform_driver(lgdt_cec_driver);

MODULE_DESCRIPTION("lgdt HDMI CEC driver");
MODULE_AUTHOR("LGE");
MODULE_LICENSE("GPL");
