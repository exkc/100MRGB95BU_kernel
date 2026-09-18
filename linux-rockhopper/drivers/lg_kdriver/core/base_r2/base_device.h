/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __BASE_DEVICE_H__
#define __BASE_DEVICE_H__

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

// define the minimum memory size for mali 400 (GPU)
//
// @note this value is not used for L8
#define KDRV_GPU_MIN_SIZE   (80*1024*1024)

// note) major 166 (LG1K_KDRV_MAJOR+26) is used by access USB in Linux
// note) major 29 is fixed for linux fb model

// driver major number
//
#define LG1K_KDRV_MAJOR     1100    /* 1100 ~ 1199 */

// device major number list.
// if major is zero, linux will assign empty major number for your module.
// kdriver will reserive total 30 major number. its range should be determined after test in the real system.
//
#define AAD_MAJOR           (LG1K_KDRV_MAJOR+0)
#define AAD_MINOR           0

#define ADEC_MAJOR          (LG1K_KDRV_MAJOR+1)
#define ADEC_MINOR          0

#define AFE_MAJOR           (LG1K_KDRV_MAJOR+2)
#define AFE_MINOR           0

#define AUDIO_MAJOR         (LG1K_KDRV_MAJOR+3)
#define AUDIO_MINOR         0

#define CI_MAJOR            (LG1K_KDRV_MAJOR+4)
#define CI_MINOR            0

#define DE_MAJOR            (LG1K_KDRV_MAJOR+5)
#define DE_MINOR            0

#define DEMOD_MAJOR         (LG1K_KDRV_MAJOR+6)
#define DEMOD_MINOR         0

#define DENC_MAJOR          (LG1K_KDRV_MAJOR+7)
#define DENC_MINOR          0

#define FBDEV_MAJOR         29
#define FBDEV_MINOR         0

#define GFX_MAJOR           (LG1K_KDRV_MAJOR+11)
#define GFX_MINOR           0

#define GPIO_MAJOR          (LG1K_KDRV_MAJOR+12)
#define GPIO_MINOR          0

#define SPI_MAJOR           (LG1K_KDRV_MAJOR+13)
#define SPI_MINOR           0


#define I2C_MAJOR           (LG1K_KDRV_MAJOR+14)
#define I2C_MINOR           0

#define PNG_MAJOR           (LG1K_KDRV_MAJOR+15)
#define PNG_MINOR           0

#define PE_MAJOR            (LG1K_KDRV_MAJOR+16)
#define PE_MINOR            0

#define PVR_MAJOR           (LG1K_KDRV_MAJOR+17)
#define PVR_MINOR           0

#define SDEC_MAJOR          (LG1K_KDRV_MAJOR+18)
#define SDEC_MINOR          0

#define SE_MAJOR            (LG1K_KDRV_MAJOR+19)
#define SE_MINOR            0

#define VBI_MAJOR           (LG1K_KDRV_MAJOR+20)
#define VBI_MINOR           0

#define VDEC_MAJOR          (LG1K_KDRV_MAJOR+21)
#define VDEC_MINOR          0

#define VENC_MAJOR          (LG1K_KDRV_MAJOR+22)
#define VENC_MINOR          0

#define SYS_MAJOR           (LG1K_KDRV_MAJOR+23)
#define SYS_MINOR           0

#define CLK_MAJOR           (LG1K_KDRV_MAJOR+24)
#define CLK_MINOR           0

#define MONITOR_MAJOR       (LG1K_KDRV_MAJOR+25)
#define MONITOR_MINOR       0


#define SCI_MAJOR           (LG1K_KDRV_MAJOR+27)
#define SCI_MINOR           0

#define MJPEG_MAJOR         (LG1K_KDRV_MAJOR+28)
#define MJPEG_MINOR         0

#define APR_MAJOR           (LG1K_KDRV_MAJOR+29)
#define APR_MINOR           0

#define BE_MAJOR            (LG1K_KDRV_MAJOR+30)
#define BE_MINOR            0

#define GPU_MAJOR           (LG1K_KDRV_MAJOR+31)
#define GPU_MINOR           0

#define OVI_MAJOR           (LG1K_KDRV_MAJOR+33)
#define OVI_MINOR           0

#ifdef INCLUDE_KDRV_MEMPROT
#define MEMPROT_MAJOR       (LG1K_KDRV_MAJOR+34)
#define MEMPROT_MINOR       0
#endif

#define HDMI_MAJOR          (LG1K_KDRV_MAJOR+36) //175
#define HDMI_MINOR          0

#define HDMI20_MAJOR        HDMI_MAJOR
#define HDMI20_MINOR        1

#define HDMI20_HDCP22RX0_MAJOR  HDMI_MAJOR
#define HDMI20_HDCP22RX0_MINOR  2

#define HDMI20_HDCP22RX1_MAJOR  HDMI_MAJOR
#define HDMI20_HDCP22RX1_MINOR  3

#define HDMI20_HDCP22TX0_MAJOR  HDMI_MAJOR
#define HDMI20_HDCP22TX0_MINOR  4


#define PM_MAJOR            (LG1K_KDRV_MAJOR+37)
#define PM_MINOR            0

#define TE_MAJOR            (LG1K_KDRV_MAJOR+38)
#define TE_MINOR            0

#define CIPLUS_MAJOR        (LG1K_KDRV_MAJOR+39)
#define CIPLUS_MINOR        0

#define EMMC_MAJOR          (LG1K_KDRV_MAJOR+40)
#define EMMC_MINOR          0

#define ATSC3_MAJOR         (LG1K_KDRV_MAJOR+41)
#define ATSC3_MINOR         0

#define SWCEC_MAJOR         (LG1K_KDRV_MAJOR+42)
#define SWCEC_MINOR         0

#define AUDFW_MAJOR         (LG1K_KDRV_MAJOR+43)
#define AUDFW_MINOR         0

#define UCOM_MAJOR          (LG1K_KDRV_MAJOR+44)
#define UCOM_MINOR          0

#define ARIB2_MAJOR         (LG1K_KDRV_MAJOR+45)
#define ARIB2_MINOR         0

#define IRB_MAJOR           (LG1K_KDRV_MAJOR+46)
#define IRB_MINOR           0

#define CRYPTO_MAJOR        (LG1K_KDRV_MAJOR+47)

#define SAMPLE_MAJOR        (LG1K_KDRV_MAJOR+98)
#define SAMPLE_MINOR        0
#define TEMPLATE_MAJOR      (LG1K_KDRV_MAJOR+99)
#define TEMPLATE_MINOR      0

#define LGBUS_MAJOR         270
#define LGBUS_MINOR         0

#ifdef INCLUDE_KDRV_SLT
#define SLT_MAJOR           290
#define SLT_MINOR           0
#endif

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __BASE_DEVICE_H__ */

