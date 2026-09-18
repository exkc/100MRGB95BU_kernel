
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/io.h>

#include "regs.h"
#include "fwload_wov.h"
#include "hma_alloc.h"
#include "ipc_regs.h"

#include "log.h"

logm_define (aud_regs, log_level_noti);
#define trace(fmt,args...)  logm_trace(aud_regs,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_regs,fmt,##args)
#define info(fmt,args...)   logm_info(aud_regs,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_regs,fmt,##args)
#define error(fmt,args...)  logm_error(aud_regs,fmt,##args)

#if defined(CHIP_NAME_m23) || defined(CHIP_NAME_o24) || defined(CHIP_NAME_o26)
#define PERI_REG_BASE       (0xf2810000)
#define DSP_REG_BASE        (0xf2820000)
#define AUD_IPC_BASE        (0xf2830000)

#define PERI_REG_SIZE       (0x1600)
#define DSP_REG_SIZE        (0x0400)
#elif defined(CHIP_NAME_o22)
#define PERI_REG_BASE       (0xf2100000)
#define DSP_REG_BASE        (0xf2120000)
#define AUD_IPC_BASE        (0xf2110000)

#define PERI_REG_SIZE       (0x1600)
#define DSP_REG_SIZE        (0x0400)
#else
#error "Please Define Chip Definition"
#endif

#ifdef _LNX_
static unsigned int *mapped_addr;

#define LNX2_REG_WRITE(addr, data) \
        mapped_addr = (unsigned int *)ioremap (addr, sizeof(unsigned int));\
    do{\
        if(mapped_addr == NULL) break;\
        *mapped_addr = data;\
        iounmap((void *)mapped_addr);\
    }while(0);\

#define LNX2_REG_READ(addr, data) \
        mapped_addr = (unsigned int *)ioremap (addr, sizeof(unsigned int));\
    do{\
        if(mapped_addr == NULL) {data =0; break;}\
        data = (unsigned int)*mapped_addr;\
        iounmap((void *)mapped_addr);\
    }while(0);\

#define LNX2_IOREMAP(reg) \
        reg = ioremap (reg##_addr, reg##_size);\
    do{\
        if (!reg) \
        {\
            error ("cannot map lnx2 0x%08X (size:%d bytes) register\n", reg##_addr, reg##_size);\
            return -EIO;\
        }\
    }while (0);\

#if defined (CHIP_NAME_o24)
#define OFFSET_LNX2_CCTRL_DSCCR_CONFIG_0 (0x8838)       /* disable WO pslverr */

#define OFFSET_LNX2_HCR         (0x8000)
#define OFFSET_LNX2_CMDER       (0x9000)
#define OFFSET_LNX2_DSCG        (0xA000)
#define OFFSET_LNX2_GB          (0xB000)

#define OFFSET_LNX2_DMA         (0xC000)
#define OFFSET_LNX2_CECFC_CE0   (0xC800)
#define OFFSET_LNX2_CECFC_CE1   (0xC900)
#define OFFSET_LNX2_CECFC_CE2   (0xCA00)
#define OFFSET_LNX2_CECFC_CE3   (0xCB00)
#define OFFSET_LNX2_CECFC_CFC   (0xCC00)
#define OFFSET_LNX2_CECFC_TOP   (0xCD00)

#define OFFSET_LNX2_TM          (0xD000)
#define OFFSET_LNX2_PVE         (0xE000)

#define OFFSET_LNX2_HCR_HOST_01 (0xF800)
#define OFFSET_LNX2_HCR_HOST_02 (0xF810)
#define OFFSET_LNX2_HCR_HOST_03 (0xF820)
#define OFFSET_LNX2_HCR_HOST_04 (0xFFFC)

#define LNX2_DUMP_SIZE          (1024*4)
#define LNX2_DMA_SIZE           (64*4)
#define LNX2_CECFC_SIZE         (44*4)
#define LNX2_HCR_HOST_01_SIZE   (2*4)
#define LNX2_HCR_HOST_02_SIZE   (3*4)
#define LNX2_HCR_HOST_03_SIZE   (4*4)
#define LNX2_HCR_HOST_04_SIZE   (1*4)

#elif defined (CHIP_NAME_o26)
#define LNX2_REG_BASE                   (PERI_REG_BASE+0x50000)   /* O26 LNX2 BASE 0xF286_XXXX */

#define OFFSET_LNX2_REG_HCR             (0x0000)
#define OFFSET_LNX2_REG_DSSCR           (0x1000)
#define OFFSET_LNX2_REG_SSCG            (0x2000)
#define OFFSET_LNX2_REG_DSCG            (0x3000)
#define OFFSET_LNX2_REG_GSEMA           (0x4000)
#define OFFSET_LNX2_REG_GB              (0x5000)
#define OFFSET_LNX2_REG_RX_GDMA         (0x6000)
#define OFFSET_LNX2_REG_TX_GDMA         (0x7000)
#define OFFSET_LNX2_REG_DMA             (0x8000)
#define OFFSET_LNX2_REG_CECFC_CON_CE0   (0x9000)
#define OFFSET_LNX2_REG_CECFC_CON_CE1   (0x9000)
#define OFFSET_LNX2_REG_CECFC_DEBUG_CE0 (0x9400)
#define OFFSET_LNX2_REG_CECFC_DEBUG_CE1 (0x9400)
#define OFFSET_LNX2_REG_TM              (0xA000)
#define OFFSET_LNX2_REG_PVE             (0xB000)
#define OFFSET_LNX2_REG_MCU_MON         (0xC000)
#define OFFSET_LNX2_REG_HCR_HOST        (0xE000)

#define SIZE_LNX2_REG_HCR               (96*4)      /* (byte) */
#define SIZE_LNX2_REG_DSSCR             (16*4)
#define SIZE_LNX2_REG_SSCG              (52*4)
#define SIZE_LNX2_REG_DSCG              (52*4)
#define SIZE_LNX2_REG_GSEMA             (12*4)
#define SIZE_LNX2_REG_GB                (352*4)
#define SIZE_LNX2_REG_RX_GDMA           (48*4)
#define SIZE_LNX2_REG_TX_GDMA           (48*4)
#define SIZE_LNX2_REG_DMA               (60*4)
#define SIZE_LNX2_REG_CECFC_CON_CE0     (72*4)
#define SIZE_LNX2_REG_CECFC_CON_CE1     (72*4)
#define SIZE_LNX2_REG_CECFC_DEBUG_CE0   (48*4)
#define SIZE_LNX2_REG_CECFC_DEBUG_CE1   (48*4)
#define SIZE_LNX2_REG_TM                (116*4)
#define SIZE_LNX2_REG_PVE               (272*4)
#define SIZE_LNX2_REG_MCU_MON           (128*4)
#define SIZE_LNX2_REG_HCR_HOST          (16*4)
#endif

#endif

volatile uint32_t *peri_ctrl_reg;
volatile uint32_t *dsp_ctrl_reg;
volatile uint32_t *aud_reg_ipc;

const unsigned int peri_reg_size = PERI_REG_SIZE;
const unsigned int dsp_reg_size = DSP_REG_SIZE;

#ifdef _LNX_
#if defined(CHIP_NAME_o24)
volatile uint32_t *lnx2_hcr;    /* reg : hc, cmder, dscg, gb */
volatile uint32_t *lnx2_dma;
volatile uint32_t *lnx2_cecfc_ce0;
volatile uint32_t *lnx2_cecfc_ce1;
volatile uint32_t *lnx2_cecfc_ce2;
volatile uint32_t *lnx2_cecfc_ce3;
volatile uint32_t *lnx2_cecfc_cfc;
volatile uint32_t *lnx2_cecfc_top;
volatile uint32_t *lnx2_tm;     /* reg : tm, fedec */
volatile uint32_t *lnx2_hcr_host01;
volatile uint32_t *lnx2_hcr_host02;
volatile uint32_t *lnx2_hcr_host03;
volatile uint32_t *lnx2_hcr_host04;

const uint32_t lnx2_hcr_addr = PERI_REG_BASE + OFFSET_LNX2_HCR;    /* reg : hc, cmder, dscg, gb */
const uint32_t lnx2_dma_addr = PERI_REG_BASE + OFFSET_LNX2_DMA;
const uint32_t lnx2_cecfc_ce0_addr = PERI_REG_BASE + OFFSET_LNX2_CECFC_CE0;
const uint32_t lnx2_cecfc_ce1_addr = PERI_REG_BASE + OFFSET_LNX2_CECFC_CE1;
const uint32_t lnx2_cecfc_ce2_addr = PERI_REG_BASE + OFFSET_LNX2_CECFC_CE2;
const uint32_t lnx2_cecfc_ce3_addr = PERI_REG_BASE + OFFSET_LNX2_CECFC_CE3;
const uint32_t lnx2_cecfc_cfc_addr = PERI_REG_BASE + OFFSET_LNX2_CECFC_CFC;
const uint32_t lnx2_cecfc_top_addr = PERI_REG_BASE + OFFSET_LNX2_CECFC_TOP;
const uint32_t lnx2_tm_addr = PERI_REG_BASE + OFFSET_LNX2_TM;     /* reg : tm, fedec */
const uint32_t lnx2_hcr_host01_addr = PERI_REG_BASE + OFFSET_LNX2_HCR_HOST_01;
const uint32_t lnx2_hcr_host02_addr = PERI_REG_BASE + OFFSET_LNX2_HCR_HOST_02;
const uint32_t lnx2_hcr_host03_addr = PERI_REG_BASE + OFFSET_LNX2_HCR_HOST_03;
const uint32_t lnx2_hcr_host04_addr = PERI_REG_BASE + OFFSET_LNX2_HCR_HOST_04;

const uint32_t lnx2_hcr_size = LNX2_DUMP_SIZE * 4;      /* reg : hcr, cmder, dscg, gb */
const uint32_t lnx2_dma_size = LNX2_DMA_SIZE;
const uint32_t lnx2_cecfc_ce0_size = LNX2_CECFC_SIZE;
const uint32_t lnx2_cecfc_ce1_size = LNX2_CECFC_SIZE;
const uint32_t lnx2_cecfc_ce2_size = LNX2_CECFC_SIZE;
const uint32_t lnx2_cecfc_ce3_size = LNX2_CECFC_SIZE;
const uint32_t lnx2_cecfc_cfc_size = LNX2_CECFC_SIZE;
const uint32_t lnx2_cecfc_top_size = LNX2_CECFC_SIZE;
const uint32_t lnx2_tm_size = LNX2_DUMP_SIZE * 2;       /* reg : tm, fedec */
const uint32_t lnx2_hcr_host01_size = LNX2_HCR_HOST_01_SIZE;
const uint32_t lnx2_hcr_host02_size = LNX2_HCR_HOST_02_SIZE;
const uint32_t lnx2_hcr_host03_size = LNX2_HCR_HOST_03_SIZE;
const uint32_t lnx2_hcr_host04_size = LNX2_HCR_HOST_04_SIZE;
#elif defined(CHIP_NAME_o26)
volatile uint32_t *lnx2_hcr;
volatile uint32_t *lnx2_dsscr;
volatile uint32_t *lnx2_sscg;
volatile uint32_t *lnx2_dscg;
volatile uint32_t *lnx2_gsema;
volatile uint32_t *lnx2_gb;
volatile uint32_t *lnx2_rx_gdma;
volatile uint32_t *lnx2_tx_gdma;
volatile uint32_t *lnx2_dma;
volatile uint32_t *lnx2_cecfc_con_ce0;
volatile uint32_t *lnx2_cecfc_con_ce1;
volatile uint32_t *lnx2_cecfc_debug_ce0;
volatile uint32_t *lnx2_cecfc_debug_ce1;
volatile uint32_t *lnx2_tm;
volatile uint32_t *lnx2_pve;
volatile uint32_t *lnx2_mcu_mon;
volatile uint32_t *lnx2_hcr_host;

const uint32_t lnx2_hcr_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_HCR;
const uint32_t lnx2_dsscr_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_DSSCR;
const uint32_t lnx2_sscg_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_SSCG;
const uint32_t lnx2_dscg_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_DSCG;
const uint32_t lnx2_gsema_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_GSEMA;
const uint32_t lnx2_gb_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_GB;
const uint32_t lnx2_rx_gdma_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_RX_GDMA;
const uint32_t lnx2_tx_gdma_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_TX_GDMA;
const uint32_t lnx2_dma_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_DMA;
const uint32_t lnx2_cecfc_con_ce0_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_CECFC_CON_CE0;
const uint32_t lnx2_cecfc_con_ce1_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_CECFC_CON_CE1;
const uint32_t lnx2_cecfc_debug_ce0_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_CECFC_DEBUG_CE0;
const uint32_t lnx2_cecfc_debug_ce1_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_CECFC_DEBUG_CE1;
const uint32_t lnx2_tm_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_TM;
const uint32_t lnx2_pve_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_PVE;
const uint32_t lnx2_mcu_mon_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_MCU_MON;
const uint32_t lnx2_hcr_host_addr = LNX2_REG_BASE + OFFSET_LNX2_REG_HCR_HOST;

const uint32_t lnx2_hcr_size = SIZE_LNX2_REG_HCR;
const uint32_t lnx2_dsscr_size = SIZE_LNX2_REG_DSSCR;
const uint32_t lnx2_sscg_size = SIZE_LNX2_REG_SSCG;
const uint32_t lnx2_dscg_size = SIZE_LNX2_REG_DSCG;
const uint32_t lnx2_gsema_size = SIZE_LNX2_REG_GSEMA;
const uint32_t lnx2_gb_size = SIZE_LNX2_REG_GB;
const uint32_t lnx2_rx_gdma_size = SIZE_LNX2_REG_RX_GDMA;
const uint32_t lnx2_tx_gdma_size = SIZE_LNX2_REG_TX_GDMA;
const uint32_t lnx2_dma_size = SIZE_LNX2_REG_DMA;
const uint32_t lnx2_cecfc_con_ce0_size = SIZE_LNX2_REG_CECFC_CON_CE0;
const uint32_t lnx2_cecfc_con_ce1_size = SIZE_LNX2_REG_CECFC_CON_CE1;
const uint32_t lnx2_cecfc_debug_ce0_size = SIZE_LNX2_REG_CECFC_DEBUG_CE0;
const uint32_t lnx2_cecfc_debug_ce1_size = SIZE_LNX2_REG_CECFC_DEBUG_CE1;
const uint32_t lnx2_tm_size = SIZE_LNX2_REG_TM;
const uint32_t lnx2_pve_size = SIZE_LNX2_REG_PVE;
const uint32_t lnx2_mcu_mon_size = SIZE_LNX2_REG_MCU_MON;
const uint32_t lnx2_hcr_host_size = SIZE_LNX2_REG_HCR_HOST;
#endif
extern void regs_lnx2_disable_WriteOnly (bool on);
extern void regs_lnx2_reg_write(unsigned int addr, unsigned int val);
#endif

int __init aregs_init (void)
{
    peri_ctrl_reg = ioremap (PERI_REG_BASE, PERI_REG_SIZE);
    if (!peri_ctrl_reg)
    {
        error ("cannot map peri ctrl register.\n");
        return -EIO;
    }

    dsp_ctrl_reg = ioremap (DSP_REG_BASE, DSP_REG_SIZE);
    if (!dsp_ctrl_reg)
    {
        error ("cannot map dsp ctrl register.\n");
        return -EIO;
    }

    aud_reg_ipc = ioremap (AUD_IPC_BASE, AUD_IPCREG_SIZE);
    if (!aud_reg_ipc)
    {
        error ("cannot map ipc register.\n");
        return -EIO;
    }

#ifdef _LNX_
#if defined(CHIP_NAME_o24)
    LNX2_IOREMAP (lnx2_hcr);
    LNX2_IOREMAP (lnx2_dma);
    LNX2_IOREMAP (lnx2_cecfc_ce0);
    LNX2_IOREMAP (lnx2_cecfc_ce1);
    LNX2_IOREMAP (lnx2_cecfc_ce2);
    LNX2_IOREMAP (lnx2_cecfc_ce3);
    LNX2_IOREMAP (lnx2_cecfc_cfc);
    LNX2_IOREMAP (lnx2_cecfc_top);
    LNX2_IOREMAP (lnx2_tm);
    LNX2_IOREMAP (lnx2_hcr_host01);
    LNX2_IOREMAP (lnx2_hcr_host02);
    LNX2_IOREMAP (lnx2_hcr_host03);
    LNX2_IOREMAP (lnx2_hcr_host04);
#elif defined(CHIP_NAME_o26)
    LNX2_IOREMAP (lnx2_hcr);
    LNX2_IOREMAP (lnx2_dsscr);
    LNX2_IOREMAP (lnx2_sscg);
    LNX2_IOREMAP (lnx2_dscg);
    LNX2_IOREMAP (lnx2_gsema);
    LNX2_IOREMAP (lnx2_gb);
    LNX2_IOREMAP (lnx2_rx_gdma);
    LNX2_IOREMAP (lnx2_tx_gdma);
    LNX2_IOREMAP (lnx2_dma);
    LNX2_IOREMAP (lnx2_cecfc_con_ce0);
    LNX2_IOREMAP (lnx2_cecfc_con_ce1);
    LNX2_IOREMAP (lnx2_cecfc_debug_ce0);
    LNX2_IOREMAP (lnx2_cecfc_debug_ce1);
    LNX2_IOREMAP (lnx2_tm);
    LNX2_IOREMAP (lnx2_pve);
    LNX2_IOREMAP (lnx2_mcu_mon);
    LNX2_IOREMAP (lnx2_hcr_host);
#endif
#endif
    return 0;
}

void __exit aregs_exit (void)
{
    iounmap (aud_reg_ipc);

    iounmap (dsp_ctrl_reg);
    iounmap (peri_ctrl_reg);
#ifdef _LNX_
#if defined(CHIP_NAME_o24)
    iounmap (lnx2_hcr);         /* reg : hc, cmder, dscg, gb */
    iounmap (lnx2_dma);
    iounmap (lnx2_cecfc_ce0);
    iounmap (lnx2_cecfc_ce1);
    iounmap (lnx2_cecfc_ce2);
    iounmap (lnx2_cecfc_ce3);
    iounmap (lnx2_cecfc_cfc);
    iounmap (lnx2_cecfc_top);
    iounmap (lnx2_tm);          /* reg : tm, fedec */
    iounmap (lnx2_hcr_host01);
    iounmap (lnx2_hcr_host02);
    iounmap (lnx2_hcr_host03);
    iounmap (lnx2_hcr_host04);
#elif defined(CHIP_NAME_o26)
    iounmap (lnx2_hcr);
    iounmap (lnx2_dsscr);
    iounmap (lnx2_sscg);
    iounmap (lnx2_dscg);
    iounmap (lnx2_gsema);
    iounmap (lnx2_gb);
    iounmap (lnx2_rx_gdma);
    iounmap (lnx2_tx_gdma);
    iounmap (lnx2_dma);
    iounmap (lnx2_cecfc_con_ce0);
    iounmap (lnx2_cecfc_con_ce1);
    iounmap (lnx2_cecfc_debug_ce0);
    iounmap (lnx2_cecfc_debug_ce1);
    iounmap (lnx2_tm);
    iounmap (lnx2_pve);
    iounmap (lnx2_mcu_mon);
    iounmap (lnx2_hcr_host);
#endif
#endif
}

static void aregs_dump_register (unsigned int *addr, unsigned int size)
{
    int i;
    char buf[10 + 9 * 8], *b;

    b = buf;
    for (i = 0; i < size / 4;)
    {
        if (i % 8 == 0)
            b += sprintf (b, "%08x:", i * 4);
        b += sprintf (b, " %08x", addr[i]);
        i++;
        if (i % 8 == 0)
        {
            noti ("%s\n", buf);
            b = buf;
        }
    }
    if (i % 8 != 0)
        noti ("%s\n", buf);
}

void aregs_dump_control_registers (void)
{
    noti ("peri control:\n");
    aregs_dump_register ((void *) peri_ctrl_reg, PERI_REG_SIZE);
#ifndef _DOLBY_IPP_
    noti ("dsp control:\n");
    aregs_dump_register ((void *) dsp_ctrl_reg, DSP_REG_SIZE);
#endif
    noti ("ipc control:\n");
    aregs_dump_register ((void *) aud_reg_ipc, AUD_IPCREG_SIZE);
}

lgbus_addr_t aud_phys_to_lgbus (phys_addr_t address)
{
#ifndef CHIP_TYPE_FPGA
    return fwloadwov_wovbus_addr (address);
#else
    return address;
#endif
}

phys_addr_t aud_base_address (void)
{
    static phys_addr_t addr;

    if (!addr)
        hma_pool_info ("audio_buffer", &addr, NULL);

    return addr;
}

#if 0 // Unused function
int aud_buffer_size (void)
{
    static phys_addr_t addr;
    int size = 0;

    if (!addr)
        hma_pool_info ("audio_buffer", &addr, &size);

    return size;
}
#endif

#ifdef _LNX_
void regs_lnx2_disable_WriteOnly (bool on)
{
#if defined(CHIP_NAME_o24)
    uint32_t value = 0x0;

    if (on)                     // WO(Write Only) pslverr off
    {
        value = 0x01000001;
    }
    else                        // WO(Write Only) pslverr on
    {
        value = 0x00000001;
    }
    LNX2_REG_WRITE (PERI_REG_BASE + OFFSET_LNX2_CCTRL_DSCCR_CONFIG_0, value);
#elif defined(CHIP_NAME_o26)
    if (on)
    {
        LNX2_REG_WRITE (LNX2_REG_BASE + 0xE000, 0x0);   // ex. wr 0xCC5EE000 0x0
        LNX2_REG_WRITE (LNX2_REG_BASE + 0xE030, 0x0);   // setting APB PSLVERR as '0'
        LNX2_REG_WRITE (LNX2_REG_BASE + 0x5004, 0x1);   // setting for GB Debug register dump
    }
    else
    {
        LNX2_REG_WRITE (LNX2_REG_BASE + 0x5004, 0x0);   // setting for recovery to normal op
        LNX2_REG_WRITE (LNX2_REG_BASE + 0x9004, 0x0);   // setting for recovery to normal op
        LNX2_REG_WRITE (LNX2_REG_BASE + 0x9400, 0x0);   // setting for recovery to normal op
        LNX2_REG_WRITE (LNX2_REG_BASE + 0xE030, 0x1);   // setting for recovery to normal op
    }
#endif
}

void regs_lnx2_reg_write (unsigned int addr, unsigned int val)
{
#if defined(CHIP_NAME_o26)
    LNX2_REG_WRITE (LNX2_REG_BASE + addr, val);
#endif
}
#endif
