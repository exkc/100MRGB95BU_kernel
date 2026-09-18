#ifndef _AUDIO_WOV_REG_H_
#define WOVREG__AUDIO_WOV_REG_H_

extern volatile uint32_t *wov_reg;

#define WOV_REG_NAME(name)              *(volatile uint32_t *)((void *)wov_reg + (WOVREG_##name))
#define WOV_REG_OFFSET(offset)          *(volatile uint32_t *)((void *)wov_reg + offset)

#define WOV_WR_OFFSET(offset,value)     WOV_REG_OFFSET(offset) = (value)
#define WOV_RD_OFFSET(offset)           WOV_REG_OFFSET(offset)
#define WOV_WR_NAME(name,value)         WOV_REG_NAME(name) = (value)
#define WOV_RD_NAME(name)               WOV_REG_NAME(name)

#define WOVREG_DSP_BRESET           0x0000
#define WOVREG_DSP_DRESET           0x0004
#define WOVREG_BUS_USER             0x0014
#define WOVREG_CPU_INT              0x0020
#define WOVREG_CPU_INT_MASK         0x0024
#define WOVREG_CPU_INT_EN           0x0028
#define WOVREG_CPU_INT_RD           0x0034
#define WOVREG_MICOM_INT            0x0038
#define WOVREG_MICOM_INT_MASK       0x003C
#define WOVREG_MICOM_INT_EN         0x0040
#define WOVREG_MICOM_INT_RD         0x0048
#define WOVREG_DSP_INT              0x004C
#define WOVREG_DSP_INT_MASK         0x0050
#define WOVREG_DSP_INT_EN           0x0054
#define WOVREG_DSP_INT_RD           0x005C
#define WOVREG_SAI_INT_STATE        0x0060
#define WOVREG_NMI_INT              0x0064
#define WOVREG_NMI_INT_MASK         0x0068
#define WOVREG_SAI_INT_MASK         0x006C
#define WOVREG_SAI_INT_CLEAR        0x0070
#define WOVREG_SAI_INT_DEST         0x0074
#define WOVREG_OCDHALTONRESET       0x0080
#define WOVREG_RUNSTALL             0x0084
#define WOVREG_STATVECTORSEL        0x0088
#define WOVREG_XOCDMODE             0x0090
#define WOVREG_PWAITMODE            0x0094
#define WOVREG_PRID                 0x0098
#define WOVREG_PDEBUGDATA           0x00A0
#define WOVREG_PDEBUGENABLE         0x00A4
#define WOVREG_PDEBUGINBPIF         0x00A8
#define WOVREG_PDEBUGINST           0x00AC
#define WOVREG_PDEBUGPC             0x00B0
#define WOVREG_PDEBUGSTATUS         0x00B4
#define WOVREG_OFFSET5              0x00C0
#define WOVREG_OFFSET6              0x00C4
#define WOVREG_OFFSET68             0x00DC
#define WOVREG_OFFSET7              0x00E0
#define WOVREG_OFFSET8              0x00E4
#define WOVREG_OFFSET9              0x00E8
#define WOVREG_DSP_INT_MICOM        0x0100
#define WOVREG_DSP_INT_MASK_MICOM   0x0104
#define WOVREG_DSP_INT_EN_MICOM     0x0108
#define WOVREG_DSP_INT_RD_MICOM     0x0110
#define WOVREG_SAICTRL              0x0200
#define WOVREG_SAIEN                0x0204
#define WOVREG_DSPMODE              0x0208
#define WOVREG_SWRESET              0x020C
#define WOVREG_STR_ADDR             0x0210
#define WOVREG_END_ADDR             0x0214
#define WOVREG_READ_ADDR            0x0218
#define WOVREG_AF_LVL               0x021C
#define WOVREG_INT_LVL              0x0220
#define WOVREG_INT_EN               0x0224
#define WOVREG_DATA_FORMAT          0x0228
#define WOVREG_WPTR_STATUS          0x022C
#define WOVREG_BUF_READ_STATUS      0x0230

#endif
