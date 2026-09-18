#ifndef _AUDIO_PERI_CTRL_REG_H_
#define _AUDIO_PERI_CTRL_REG_H_

extern volatile uint32_t *peri_ctrl_reg;
extern const unsigned int peri_reg_size;

#ifdef _LNX_
#if defined(CHIP_NAME_o24)
extern volatile uint32_t *lnx2_hcr;            /* reg : hc, cmder, dscg, gb */
extern volatile uint32_t *lnx2_dma;
extern volatile uint32_t *lnx2_cecfc_ce0;
extern volatile uint32_t *lnx2_cecfc_ce1;
extern volatile uint32_t *lnx2_cecfc_ce2;
extern volatile uint32_t *lnx2_cecfc_ce3;
extern volatile uint32_t *lnx2_cecfc_cfc;
extern volatile uint32_t *lnx2_cecfc_top;
extern volatile uint32_t *lnx2_tm;             /* reg : tm, fedec */
extern volatile uint32_t *lnx2_hcr_host01;
extern volatile uint32_t *lnx2_hcr_host02;
extern volatile uint32_t *lnx2_hcr_host03;
extern volatile uint32_t *lnx2_hcr_host04;

extern const uint32_t lnx2_hcr_addr;      /*reg : hcr, cmder, dscg, gb*/
extern const uint32_t lnx2_dma_addr;
extern const uint32_t lnx2_cecfc_ce0_addr;
extern const uint32_t lnx2_cecfc_ce1_addr;
extern const uint32_t lnx2_cecfc_ce2_addr;
extern const uint32_t lnx2_cecfc_ce3_addr;
extern const uint32_t lnx2_cecfc_cfc_addr;
extern const uint32_t lnx2_cecfc_top_addr;
extern const uint32_t lnx2_tm_addr;       /* reg : tm, fedec */
extern const uint32_t lnx2_hcr_host01_addr;
extern const uint32_t lnx2_hcr_host02_addr;
extern const uint32_t lnx2_hcr_host03_addr;
extern const uint32_t lnx2_hcr_host04_addr;

extern const uint32_t lnx2_hcr_size;      /*reg : hcr, cmder, dscg, gb*/
extern const uint32_t lnx2_dma_size;
extern const uint32_t lnx2_cecfc_ce0_size;
extern const uint32_t lnx2_cecfc_ce1_size;
extern const uint32_t lnx2_cecfc_ce2_size;
extern const uint32_t lnx2_cecfc_ce3_size;
extern const uint32_t lnx2_cecfc_cfc_size;
extern const uint32_t lnx2_cecfc_top_size;
extern const uint32_t lnx2_tm_size;       /* reg : tm, fedec */
extern const uint32_t lnx2_hcr_host01_size;
extern const uint32_t lnx2_hcr_host02_size;
extern const uint32_t lnx2_hcr_host03_size;
extern const uint32_t lnx2_hcr_host04_size;
#elif defined(CHIP_NAME_o26)
extern volatile uint32_t *lnx2_hcr;
extern volatile uint32_t *lnx2_dsscr;
extern volatile uint32_t *lnx2_sscg;
extern volatile uint32_t *lnx2_dscg;
extern volatile uint32_t *lnx2_gsema;
extern volatile uint32_t *lnx2_gb;
extern volatile uint32_t *lnx2_rx_gdma;
extern volatile uint32_t *lnx2_tx_gdma;
extern volatile uint32_t *lnx2_dma;
extern volatile uint32_t *lnx2_cecfc_con_ce0;
extern volatile uint32_t *lnx2_cecfc_con_ce1;
extern volatile uint32_t *lnx2_cecfc_debug_ce0;
extern volatile uint32_t *lnx2_cecfc_debug_ce1;
extern volatile uint32_t *lnx2_tm;
extern volatile uint32_t *lnx2_pve;
extern volatile uint32_t *lnx2_mcu_mon;
extern volatile uint32_t *lnx2_hcr_host;

extern const uint32_t lnx2_hcr_addr;
extern const uint32_t lnx2_dsscr_addr;
extern const uint32_t lnx2_sscg_addr;
extern const uint32_t lnx2_dscg_addr;
extern const uint32_t lnx2_gsema_addr;
extern const uint32_t lnx2_gb_addr;
extern const uint32_t lnx2_rx_gdma_addr;
extern const uint32_t lnx2_tx_gdma_addr;
extern const uint32_t lnx2_dma_addr;
extern const uint32_t lnx2_cecfc_con_ce0_addr;
extern const uint32_t lnx2_cecfc_con_ce1_addr;
extern const uint32_t lnx2_cecfc_debug_ce0_addr;
extern const uint32_t lnx2_cecfc_debug_ce1_addr;
extern const uint32_t lnx2_tm_addr;
extern const uint32_t lnx2_pve_addr;
extern const uint32_t lnx2_mcu_mon_addr;
extern const uint32_t lnx2_hcr_host_addr;

extern const uint32_t lnx2_hcr_size;
extern const uint32_t lnx2_dsscr_size;
extern const uint32_t lnx2_sscg_size;
extern const uint32_t lnx2_dscg_size;
extern const uint32_t lnx2_gsema_size;
extern const uint32_t lnx2_gb_size;
extern const uint32_t lnx2_rx_gdma_size;
extern const uint32_t lnx2_tx_gdma_size;
extern const uint32_t lnx2_dma_size;
extern const uint32_t lnx2_cecfc_con_ce0_size;
extern const uint32_t lnx2_cecfc_con_ce1_size;
extern const uint32_t lnx2_cecfc_debug_ce0_size;
extern const uint32_t lnx2_cecfc_debug_ce1_size;
extern const uint32_t lnx2_tm_size;
extern const uint32_t lnx2_pve_size;
extern const uint32_t lnx2_mcu_mon_size;
extern const uint32_t lnx2_hcr_host_size;

#endif
extern void regs_lnx2_reg_write(unsigned int addr, unsigned int val);
extern void regs_lnx2_disable_WriteOnly (bool on);
#endif

#define PERI_REG_NAME(name)              *(volatile uint32_t *)((void *)peri_ctrl_reg + (PERIREG_##name))
#define PERI_REG_OFFSET(offset)          *(volatile uint32_t *)((void *)peri_ctrl_reg + offset)

#define PERI_WR_OFFSET(offset,value)     PERI_REG_OFFSET(offset) = (value)
#define PERI_RD_OFFSET(offset)           PERI_REG_OFFSET(offset)
#define PERI_WR_NAME(name,value)         PERI_REG_NAME(name) = (value)
#define PERI_RD_NAME(name)               PERI_REG_NAME(name)

#define PERIREG_OFFSET          10

#define PERIREG_CPUTODSP0       0x540
#define PERIREG_CPUTODSP1       0x544
#define PERIREG_CPUTODSP2       0x548
#define PERIREG_CPUTODSP3       0x54C

#define PERIREG_INT0_CLR        0x630
#define PERIREG_INT0_EN         0x634
#define PERIREG_INT0            0x638

#define PERIREG_INT1_CLR        0x640
#define PERIREG_INT1_EN         0x644
#define PERIREG_INT1            0x648

#define PERIREG_INT2_CLR        0x650
#define PERIREG_INT2_EN         0x654
#define PERIREG_INT2            0x658

#define PERIREG_INT3_CLR        0x660
#define PERIREG_INT3_EN         0x664
#define PERIREG_INT3            0x668

#define PERIREG_SWRESET         0x670

#endif
