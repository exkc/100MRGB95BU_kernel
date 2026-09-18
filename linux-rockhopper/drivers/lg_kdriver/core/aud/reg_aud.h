#ifndef _AUDIO_AUD_REG_H_
#define AUDREG__AUDIO_AUD_REG_H_

extern volatile uint32_t *aud_reg;
extern const unsigned int aud_reg_size;

#define AUD_REG_NAME(name)              *(volatile uint32_t *)((void *)aud_reg + (AUDREG_##name))
#define AUD_REG_OFFSET(offset)          *(volatile uint32_t *)((void *)aud_reg + offset)

#define AUD_WR_OFFSET(offset,value)     AUD_REG_OFFSET(offset) = (value)
#define AUD_RD_OFFSET(offset)           AUD_REG_OFFSET(offset)
#define AUD_WR_NAME(name,value)         AUD_REG_NAME(name) = (value)
#define AUD_RD_NAME(name)               AUD_REG_NAME(name)

#define AUDREG_INT0_CLR                 0x704
#define AUDREG_SWRESET                  0x738
#define AUDREG_DIRQ0                    0x740
#define AUDREG_OFFSET68                 0x7d8

#endif
