#ifndef _AUDIO_DSP_CTRL_REG_H_
#define _AUDIO_DSP_CTRL_REG_H_

extern volatile uint32_t *dsp_ctrl_reg;
extern const unsigned int dsp_reg_size;

#define DSP_REG_NAME(name)              *(volatile uint32_t *)((void *)dsp_ctrL_reg + (DSPREG_##name))
#define DSP_REG_OFFSET(offset)          *(volatile uint32_t *)((void *)dsp_ctrL_reg + offset)

#define DSP_WR_OFFSET(offset,value)     DSP_REG_OFFSET(offset) = (value)
#define DSP_RD_OFFSET(offset)           DSP_REG_OFFSET(offset)
#define DSP_WR_NAME(name,value)         DSP_REG_NAME(name) = (value)
#define DSP_RD_NAME(name)               DSP_REG_NAME(name)

#define DSPREG_OFFSET           0x100

#define DSPREG_DSP0OFFSET5      0x000
#define DSPREG_DSP0OFFSET6      0x004
#define DSPREG_DSP0OFFSET68     0x008
#define DSPREG_RUNSTALL0        0x020
#define DSPREG_STATVECSEL0      0x024
#define DSPREG_DSP0PRID         0x02c
#define DSPREG_DEBUGEN0         0x040

#define DSPREG_DSP1OFFSET5      0x100
#define DSPREG_DSP1OFFSET6      0x104
#define DSPREG_DSP1OFFSET68     0x108
#define DSPREG_DSP1OFFSET7      0x10c
#define DSPREG_RUNSTALL1        0x120
#define DSPREG_STATVECSEL1      0x124
#define DSPREG_DSP1PRID         0x12c
#define DSPREG_DEBUGEN1         0x140

#define DSPREG_DSP2OFFSET5      0x200
#define DSPREG_DSP2OFFSET6      0x204
#define DSPREG_DSP2OFFSET68     0x208
#define DSPREG_DSP2OFFSET7      0x20c
#define DSPREG_RUNSTALL2        0x220
#define DSPREG_STATVECSEL2      0x224
#define DSPREG_DSP2PRID         0x22c
#define DSPREG_DEBUGEN2         0x240

#define DSPREG_DSP3OFFSET5      0x300
#define DSPREG_DSP3OFFSET6      0x304
#define DSPREG_DSP3OFFSET68     0x308
#define DSPREG_DSP3OFFSET7      0x30c
#define DSPREG_RUNSTALL3        0x320
#define DSPREG_STATVECSEL3      0x324
#define DSPREG_DSP3PRID         0x32c
#define DSPREG_DEBUGEN3         0x340
#endif
