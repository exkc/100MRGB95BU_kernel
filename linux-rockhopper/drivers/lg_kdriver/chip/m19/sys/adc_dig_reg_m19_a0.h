/*
 * This file is a shock-absorber to bring-up.
 *
 * NOTE:--- From Leo Tolstoy's book Anna Karenina.
 * "Happy families are all alike; every unhappy family is unhappy in its own way."
 *
 * This file will be removed..... MUST....
 */

#ifndef  __ADC_DIG_REG_WTX_H__
#define  __ADC_DIG_REG_WTX_H__

/* why? why? why? 
   refer to bsp/kdriver/core/audio/chip/m19/audio_drv_hal_m19_a0.c
*/
typedef u32 AUD_SYN_REG_M19_A0;
typedef u32 CTOP_FMS_REG_M19_A0;

#define FIXME_MESSAGE_PRINTOUT_RET \
     { \
     int i; \
     for (i=0; i<10; i++) \
     printk("FIXME & REMOVE_ME: This is a invalid call," \
     "refer to SICDTV-5000. %s:(%d)\n", \
     __func__, __LINE__); \
     0; \
     }



/* M19A0 */

#define ACE_REG_M19A0_SHDW					(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_PHYS					(FIXME_MESSAGE_PRINTOUT_RET)

#define ACE_REG_M19A0_RdFL(_r)			(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_WrFL(_r)			(FIXME_MESSAGE_PRINTOUT_RET)

#define ACE_REG_M19A0_Rd(_r)			(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Wr(_r,_v)		(FIXME_MESSAGE_PRINTOUT_RET)


#define ACE_REG_M19A0_RdFd(_r,_f01)					(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Rd01(_r,_f01,_v01)				(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Rd02(_r,_f01,_v01,_f02,_v02)		(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) (FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_v04) (FIXME_MESSAGE_PRINTOUT_RET)

#define ACE_REG_M19A0_Wr01(_r,_f01,_v01)				(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Wr02(_r,_f01,_v01,_f02,_v02)		(FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03) (FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04) (FIXME_MESSAGE_PRINTOUT_RET)

#define ACE_REG_M19A0_READ(m,offset) (FIXME_MESSAGE_PRINTOUT_RET)
#define ACE_REG_M19A0_WRITE(m,offset,value) (FIXME_MESSAGE_PRINTOUT_RET)

#endif
/**  @} */
