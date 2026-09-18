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


/** @file
 *
 *  CI register details. ( used only within kdriver )
 *
 *  @author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2015.1.1
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef __CI_HW_OPS_H__
#define __CI_HW_OPS_H__

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/types.h>
#include <asm/io.h>
#include "ci_cfg.h"
#include "ci_regdefs.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HW_IO_OK			0
#define HW_IO_BUSY			1
#define HW_IO_FAIL			(-1)
#define MEM_ALLOC_FAILED	(-2)

#define	DATA_REG			0x00000000
#define	DATA32_REG			0x00008000		//for burst mode (32bit)
#define	COMM_REG			0x00000002
#define	STAT_REG			0x00000002
#define	SIZE_REG_LS			0x00000004
#define	SIZE_REG_MS			0x00000006

/* status register bit definitions */
#define	CI_RE				0x01
#define	CI_WE				0x02
#define	CI_FR				0x40
#define	CI_DA				0x80
#define CI_IIR				0x10 /* for CI plus */

/* command register bit definitions	*/
#define	CI_HC				0x01
#define	CI_SW				0x02
#define	CI_SR				0x04
#define	CI_RS				0x08 // avoid collision with RS in "dtv_msgs.h"
#define	CI_FRIE				0x40
#define	CI_DAIE				0x80

/* host & module buffer size */
#define HOST_BUF_SIZE		65535
#define	MOD_BUF_SIZE_MIN	16
#define	MOD_BUF_SIZE_MAX	65535

#define MAX_IO_BUF_SIZE		8192	//4096

#define CD_CHANGED				0x0001
#define HW_HOT_SWAP_DONE		0x0004
#define READY_IREQ				0x0008
#define CD_POL_VAL				0x80
#define POWER_OFF_SEQ			0x0000
#define POWER_ON_SEQ			0x0024
#define CD_CHANGED_DISABLE_INT	0xFFFF
#define CD_CHANGED_ENABLE_INT	0xFFFE

#define INIT_VAL				0x0000
#define CLK_128					0x0080
#define CLK_511					0X01FF
#define CLK_639 				0X027F
#define	CD1_CD2_HIGH			0x03
#define CD_POL					0x80

#define DA_STATUS				0x80

/* Control and Status1 */
#define VCC_SW0					0x0004
#define EN_PCCARD				0x0020
#define CARD_RESET				0x0080

/* Control and Status3 */
#define IO_INT_MODE				0x0004
#define POD_MODE				0x0010

/* PC Card Control1 */
#define CHIP_MODE_IO			0X001D
#define CHIP_MODE_ATTR			0X001B

/* for CI plus */
#define RESET_PHY_INT			0x10
#define IIR_STATUS				0x10

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define CI_READ8(dev, reg)				readb((volatile void *)(dev->reg_addr + reg))
#define CI_READ16(dev, reg)				readw((volatile void *)(dev->reg_addr + reg))
#define CI_READ32(dev, reg)				readl((volatile void *)(dev->reg_addr + reg))
#define CICAM_READ8(dev, reg)			readb((volatile void *)(dev->mod_addr + reg))
#define CICAM_READ16(dev, reg)			readw((volatile void *)(dev->mod_addr + reg))
#define CICAM_READ32(dev, reg)			readl((volatile void *)(dev->mod_addr + reg))

#define CI_WRITE8(dev, val, reg)		writeb((val), (volatile void *)(dev->reg_addr + reg))
#define CI_WRITE16(dev, val, reg)		writew((val), (volatile void *)(dev->reg_addr + reg))
#define CI_WRITE32(dev, val, reg)		writel((val), (volatile void *)(dev->reg_addr + reg))
#define CICAM_WRITE8(dev, val, reg)		writeb((val), (volatile void *)(dev->mod_addr + reg))
#define CICAM_WRITE16(dev, val, reg)	writew((val), (volatile void *)(dev->mod_addr + reg))
#define CICAM_WRITE32(dev, val, reg)	writel((val), (volatile void *)(dev->mod_addr + reg))

#define ci_cam_rd_status(cidev)				CICAM_READ8(cidev, STAT_REG)
#define ci_cam_rd_data(cidev)				CICAM_READ8(cidev, DATA_REG)
#define ci_cam_rd_size_ls(cidev)			CICAM_READ8(cidev, SIZE_REG_LS)
#define ci_cam_rd_size_ms(cidev)			CICAM_READ8(cidev, SIZE_REG_MS)

#define ci_cam_wr_cmd(cidev, val)			CICAM_WRITE8(cidev, val, COMM_REG)
#define ci_cam_wr_status(cidev, val)		CICAM_WRITE8(cidev, val, STAT_REG)
#define ci_cam_wr_data(cidev, val)			CICAM_WRITE8(cidev, val, DATA_REG)
#define ci_cam_wr_size_ls(cidev, val)		CICAM_WRITE8(cidev, val, SIZE_REG_LS)
#define ci_cam_wr_size_ms(cidev, val)		CICAM_WRITE8(cidev, val, SIZE_REG_MS)

#define ci_cam_rd_data32(cidev)				CICAM_READ32(cidev, DATA32_REG);
#define ci_cam_wr_data32(cidev, val)		CICAM_WRITE32(cidev, val, DATA32_REG);

#define ci_chk_da(status)					((status) & CI_DA)
#define ci_chk_fr(status)					((status) & CI_FR)
#define ci_chk_re(status)					((status) & CI_RE)
#define ci_chk_we(status)					((status) & CI_WE)
#define ci_chk_iir(status)					((status) & CI_IIR)

#define ci_rd_chk_da(cidev)					ci_chk_da(ci_cam_rd_status(cidev))
#define ci_rd_chk_fr(cidev)					ci_chk_fr(ci_cam_rd_status(cidev))
#define ci_rd_chk_re(cidev)					ci_chk_re(ci_cam_rd_status(cidev))
#define ci_rd_chk_we(cidev)					ci_chk_we(ci_cam_rd_status(cidev))
#define ci_rd_chk_iir(cidev)				ci_chk_iir(ci_cam_rd_status(cidev))
/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum
{
	PCMCIA_BUS_SPEED_MIN = 0x0,
	PCMCIA_BUS_SPEED_LOW,
	PCMCIA_BUS_SPEED_HIGH,
	PCMCIA_BUS_SPEED_MAX
} CI_BUS_SPEED_T;

typedef enum
{
	ACCESS_1BYTE_MODE = 0,
	ACCESS_2BYTE_MODE = 1,
	ACCESS_4BYTE_MODE = 2
} CI_ACCESS_MODE_T;

typedef enum
{
	WR_DATA_MIDDLE = 0,
	WR_DATA_LAST = 1,
} CI_WR_DATA_TYPE_T;

typedef enum
{
	WR_PWR_SKIP = 0,
	WR_PWR_CHK = 1,
} CI_WR_PWR_TYPE_T;

typedef enum
{
	CI_ERR_CHK_MODE_FULL		= 0,
	CI_ERR_CHK_MODE_SIMPLE,
	CI_ERR_CHK_MODE_MAX
} CI_ERR_CHK_MODE_T;

typedef enum {
	CD_POL_FLAG_REMOVE,
	CD_POL_FLAG_INSERT,
} CI_POL_FLAG_T;


static inline void ci_hw_reset_nego_info(CI_DEV_T *cidev)
{
	ci_nego_buff_size(cidev) = 0;
	ci_nego_step(cidev) = 0;
}

extern int ci_hw_change_access_mode(CI_DEV_T *cidev, u32 mode);

static inline void ci_hw_change_access_mode_byte(CI_DEV_T *cidev, int _cond)
{
	if (_cond) {
		ci_hw_change_access_mode(cidev, ACCESS_1BYTE_MODE);
	}
}

static inline void _hw_change_access_mode_word(CI_DEV_T *cidev, int _cond)
{
	if (_cond) {
		ci_hw_change_access_mode(cidev, ACCESS_2BYTE_MODE);
	}
}

static inline void ci_hw_change_access_mode_long(CI_DEV_T *cidev, int _cond)
{
	if (_cond) {
		ci_hw_change_access_mode(cidev, ACCESS_4BYTE_MODE);
	}
}

int ci_hw_verify_card_detection(CI_DEV_T *cidev, int opt, const char *func);
irqreturn_t CI_irq_handler(int irq, void *dev_id);
int CI_OPS_Init(CI_DEV_T *cidev);
int CI_OPS_Uninit(CI_DEV_T *cidev);
int CI_OPS_SetHWMode(CI_DEV_T *cidev, UINT16 mode, UINT16 val);
int CI_OPS_Reset(CI_DEV_T *cidev);
int CI_OPS_CAMInit(CI_DEV_T *cidev);
int CI_OPS_CAMOff(CI_DEV_T *cidev);
int CI_OPS_CAMOnCompleted(CI_DEV_T *cidev);
int CI_OPS_DetectCard(CI_DEV_T *cidev, UINT32 *status);
int CI_OPS_NegoBuff(CI_DEV_T *cidev, UINT32 *nego_buff_size);
int CI_OPS_SetPhysReset(CI_DEV_T *cidev);
int CI_OPS_SetRS(CI_DEV_T *cidev);
int CI_OPS_CheckCapability(CI_DEV_T *cidev, UINT32 *cam_type);
int CI_OPS_GetCiplusVer(CI_DEV_T *cidev, UINT32 *version);
int CI_OPS_GetCiplusOPProfile(CI_DEV_T *cidev, UINT32 *profile);
int CI_OPS_SetPcmciaSpeed(CI_DEV_T *cidev, UINT32 speed);
int CI_OPS_ChangeAccessMode(CI_DEV_T *cidev, UINT32 mode);
int CI_OPS_ControlOption(CI_DEV_T *cidev, u32 func, u32 *mode);
int CI_OPS_ReadDAStatus(CI_DEV_T *cidev, UINT32 *da_status);
int CI_OPS_ReadIIRStatus(CI_DEV_T *cidev, UINT32 *iir_status);
int CI_OPS_ShowRegisters(CI_DEV_T *cidev);
int CI_OPS_WriteReg(CI_DEV_T *cidev, UINT32 idx, UINT32 val);
int CI_OPS_Suspend(CI_DEV_T *cidev);
int CI_OPS_Resume(CI_DEV_T *cidev);
int CI_OPS_IO_ReadData(CI_DEV_T *cidev, UINT8* buf, UINT32* size);
int CI_OPS_IO_WriteData(CI_DEV_T *cidev, u8 *wbuf, u32 wsize);


int ci_hw_rd_io_chk_da(CI_DEV_T *cidev, int chk_cnt, int delay, char *dbg);
int ci_hw_wr_io_chk_da(CI_DEV_T *cidev, int chk_cnt, int delay, char *dbg);
int ci_hw_wr_io_chk_fr(CI_DEV_T *cidev, int chk_cnt, int delay, int chk_pwr, char *dbg);
int ci_hw_wr_io_chk_1st(CI_DEV_T *cidev, int chk_cnt, int delay, int mode, char *dbg);
int ci_hw_wr_io_chk_we(CI_DEV_T *cidev, int chk_cnt, int delay, int mode, int last_byte, char *dbg);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __CI_HW_OPS_H__ */


