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

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>

#include "ci_util.h"
#include "ci_regdefs.h"
#include "ci_dev.h"
#include "ci_proc.h"
#include "ci_hw_cis.h"
#include "ci_hw_ops.h"

#define CI_PRINT_REG(_idx, _cidev, _reg, _name)	\
	LOGM_PRINT(g_ci_debug_fd, _idx, "[0x%02X] %32s [0x%04X]\n", _reg, _name, CI_READ16(_cidev, _reg))

static void PrintRegisters(CI_DEV_T *cidev, int level)
{
	int dbg_idx = level;

	CI_PRINT_REG(dbg_idx, cidev, CREG_CTRL_STATUS_1, "Control and Status 1");
	CI_PRINT_REG(dbg_idx, cidev, CREG_CTRL_STATUS_2, "Control and Status 2");
	CI_PRINT_REG(dbg_idx, cidev, CREG_CTRL_STATUS_3, "Control and Status 3");
	CI_PRINT_REG(dbg_idx, cidev, CREG_PC_CARD_CTRL_1, "PC Card Control 1");
	CI_PRINT_REG(dbg_idx, cidev, CREG_PC_CARD_CTRL_2, "PC Card Control 2");
	CI_PRINT_REG(dbg_idx, cidev, CREG_PC_CARD_CTRL_3, "PC Card Control 3");
	CI_PRINT_REG(dbg_idx, cidev, CREG_BUSRT_CTRL, "Burst Control");
	CI_PRINT_REG(dbg_idx, cidev, CREG_INTR_FLAG, "Interrupt Flag");
	CI_PRINT_REG(dbg_idx, cidev, CREG_INTR_MASK, "Interrupt Mask");
	CI_PRINT_REG(dbg_idx, cidev, CREG_INTR_CTRL, "Interrupt Control");
	CI_PRINT_REG(dbg_idx, cidev, CREG_PCMCIA_IDX, "PCMCIA Address Index");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_1, "Power On Interval 1");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_2, "Power On Interval 2");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_3, "Enable Interval 1");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_4, "Enable Interval 2");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_5, "Card Insert Done Interval 1");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_6, "Card Insert Done Interval 2");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_7, "Card Removal Done Interval 1");
	CI_PRINT_REG(dbg_idx, cidev, CREG_HS_CTRL_8, "Card Removal Done Interval 2");
}

int ci_hw_rd_io_chk_da(CI_DEV_T *cidev,
					int chk_cnt, int delay, char *dbg)
{
	volatile u8 status_reg = 0;

	LOG_DBG3("> chk_cnt[%d], delay[%d]\n", chk_cnt, delay);

	/* confirm that data is available */
	while (chk_cnt--) {
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR(ci_is_power_restart(cidev), return -EFAULT, "power_restart detected");

		status_reg = ci_cam_rd_status(cidev);
		if (ci_chk_da(status_reg)) {
		//	LOG_DBG2("DA checked\n");
			break;
		}
		ci_sleep(delay);
	}
	if (chk_cnt <= 0) {
		LOG_ERROR("%s, status=0x%02X\n", dbg, status_reg);
	//	return HW_IO_BUSY;
		return -EBUSY;
	}
	return 0;
}

int ci_hw_wr_io_chk_da(CI_DEV_T *cidev,
					int chk_cnt, int delay, char *dbg)
{
	volatile u8 status_reg = 0;

	LOG_DBG3(">>> chk_cnt[%d], delay[%d]\n", chk_cnt, delay);

	/* confirm that data is not available */
	while (chk_cnt--) {
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR(ci_is_power_restart(cidev), return -EFAULT, "power_restart detected");

		status_reg = ci_cam_rd_status(cidev);
		if (!ci_chk_da(status_reg)) {
			break;
		}
		ci_sleep(delay);
	}
	if (chk_cnt <= 0) {
		LOG_ERROR("%s, status=0x%02X\n", dbg, status_reg);
		return -EBUSY;
	}
	return 0;
}

int ci_hw_wr_io_chk_fr(CI_DEV_T *cidev,
					int chk_cnt, int delay,
					int chk_pwr, char *dbg)
{
	volatile u8 status_reg = 0;

	LOG_DBG3(">>> chk_cnt[%d], delay[%d]\n", chk_cnt, delay);

	/* confirm that module is free */
	while (chk_cnt--) {
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR( (!!(chk_pwr == WR_PWR_CHK)) && (ci_is_power_restart(cidev)) ,
					return -EFAULT, "power_restart with WR_PWR_CHK");

		status_reg = ci_cam_rd_status(cidev);
		if (ci_chk_fr(status_reg)) {
			break;
		}
		ci_sleep(delay);
	}
	if (chk_cnt <= 0) {
		LOG_ERROR("%s, status=0x%02X\n", dbg, status_reg);
		return -EBUSY;
	}
	return 0;
}

int ci_hw_wr_io_chk_1st(CI_DEV_T *cidev,
						int chk_cnt, int delay,
						int mode, char *dbg)
{
	volatile u8 status_reg = 0;

	LOG_DBG3(">>> chk_cnt[%d], delay[%d]\n", chk_cnt, delay);

	/* confirm that module is free */
	while (chk_cnt--) {
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR(ci_is_power_restart(cidev), return -EFAULT, "power_restart detected");

		if (mode == CI_ERR_CHK_MODE_SIMPLE) {
			break;
		}
		status_reg = ci_cam_rd_status(cidev);
		if (!ci_chk_fr(status_reg) && ci_chk_we(status_reg)) {
			break;
		}
		ci_sleep(delay);
	}
	if (chk_cnt <= 0) {
		LOG_ERROR("%s, status=0x%02X\n", dbg, status_reg);
		return -EBUSY;
	}
	return 0;
}

int ci_hw_wr_io_chk_we(CI_DEV_T *cidev,
					int chk_cnt,
					int delay,
					int mode,
					int last_byte,
					char *dbg)
{
	volatile u8 status_reg = 0;
	int cond;

	LOG_DBG3(">>> chk_cnt[%d], delay[%d]\n", chk_cnt, delay);

	cond = (last_byte == WR_DATA_LAST)? 0 : CI_WE;

	/* confirm that module is free */
	while (chk_cnt--) {
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR(ci_is_power_restart(cidev), return -EFAULT, "power_restart detected");

		if (mode == CI_ERR_CHK_MODE_SIMPLE) {
			break;
		}
		status_reg = ci_cam_rd_status(cidev);
	#if 1
		if (ci_chk_we(status_reg) == cond) {
			break;
		}
	#else
		if (last_byte == WR_LAST) {
			if (!ci_chk_we(status_reg)) {
				break;
			}
		} else {
			if (ci_chk_we(status_reg)) {
				break;
			}
		}
	#endif
		ci_sleep(delay);
	}
	if (chk_cnt <= 0) {
		LOG_ERROR("%s, status=0x%02X\n", dbg, status_reg);
		return -EBUSY;
	}
	return 0;
}

static int ci_hw_cd_pol_state(CI_DEV_T *cidev)
{
	u16 state;

	state = CI_READ16(cidev, CREG_CTRL_STATUS_2);
	if ((state & CD1_CD2_HIGH) == 0x00) {
		return CD_POL_FLAG_INSERT;
	}
	return CD_POL_FLAG_REMOVE;
}

static void ci_hw_cd_pol_change(CI_DEV_T *cidev, int state)
{
	u16 reg_val;
	reg_val = CI_READ16(cidev, CREG_INTR_CTRL);
	if (state == CD_POL_FLAG_INSERT) {
		reg_val |= CD_POL;
	} else {
		reg_val &= ~CD_POL;
	}
	LOG_DBG2(">> Clear Interrupt Control : 0x%04X\n", reg_val);
	CI_WRITE16(cidev, reg_val, CREG_INTR_CTRL);
}

static void ci_hw_cd_pol_process(CI_DEV_T *cidev, int pol_state)
{
	ci_hw_cd_pol_change(cidev, pol_state);
	if (pol_state == CD_POL_FLAG_INSERT) {
		ci_is_card_detected(cidev) = 1;
		ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_CAM_IN);
	} else {
		ci_is_card_detected(cidev) = 0;
		ci_hw_cis_set_chk_state(cidev, 0);
		ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_CAM_OUT);
	}
	ci_is_flag_reset_for_cam(cidev);
}

int ci_hw_verify_card_detection(CI_DEV_T *cidev, int opt, const char *func)
{
	unsigned long flags;
	u16 pol_state;
	int detect;
	int ret = 0;

	if (!ci_opt_cd_pol(cidev)) {
		return 0;
	}

	ci_lock_irqsave(cidev, flags);

	detect = ci_is_card_detected(cidev);

	pol_state = ci_hw_cd_pol_state(cidev);

	if (pol_state == CD_POL_FLAG_REMOVE) {
		if (detect) {
			ci_hw_cd_pol_process(cidev, pol_state);

			LOG_INFO("abnormal cd status : removed [%s]\n", (char *)func);
		}
		ret = 1;
	} else {
		if (opt) {
			if (!detect) {
				ci_hw_cd_pol_process(cidev, pol_state);

				LOG_INFO("abnormal cd status : inserted [%s]\n", (char *)func);
			}
			ret = 2;
		}
	}

	ci_unlock_irqrestore(cidev, flags);

	return ret;
}

static void ci_hw_detect_card_process(CI_DEV_T *cidev, int isr)
{
	u16 pol_state;
	int detect;
	int msg = -1;

	detect = ci_is_card_detected(cidev);

	pol_state = ci_hw_cd_pol_state(cidev);

	if (pol_state == CD_POL_FLAG_INSERT) {
		if (isr || !detect) {
			msg = (int)pol_state;
		}
	} else {
		if (isr || detect) {
			msg = (int)pol_state;
		}
	}
	if (msg != -1) {
		ci_hw_cd_pol_process(cidev, pol_state);
		switch (msg) {
			case CD_POL_FLAG_INSERT:
				LOG_INFO("CAM is inserted ... (%d)\n", isr);
				break;
			case CD_POL_FLAG_REMOVE:
				LOG_INFO("CAM is %s ... (%d)\n",
						(isr)? "removed" : "not inserted", isr);
				break;
			default:
				break;
		}
	}
}

static int SetPcmciaSpeed(CI_DEV_T *cidev, UINT32 speed)
{
	int bus_changed = 0;
	int bus_param_1, bus_param_2;

	switch( speed )
	{
		case PCMCIA_BUS_SPEED_MIN :
		case PCMCIA_BUS_SPEED_LOW :
			bus_changed = 1;
			bus_param_1 = 0xF03;
			bus_param_2 = 0x003;
			break;
		case PCMCIA_BUS_SPEED_HIGH :
		case PCMCIA_BUS_SPEED_MAX :
			bus_changed = 1;
			//change the register from 0x101 to 0x201 (20130218, ohsung.roh)
			bus_param_1 = 0x0201;
			bus_param_2 = 0x0001;
			break;
		default :
			LOG_WARNING("Invalid speed : %d\n", speed);
			break;
	}

	if (bus_changed) {
		CI_WRITE16(cidev, bus_param_1, CREG_PC_CARD_CTRL_2);
		CI_WRITE16(cidev, bus_param_2, CREG_PC_CARD_CTRL_3);

		ci_bus_speed(cidev) = speed;
		ci_bus_param_1(cidev) = bus_param_1;
		ci_bus_param_2(cidev) = bus_param_2;
		LOG_INFO("set PCMCIA bus timing : %d\n", speed);
	}

	return 0;
}

/**
 * @brief
 *   core bridge function : set PCMCIA I/F bus speed
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   speed :setting value
 * @return
 *  int
 */
int CI_OPS_SetPcmciaSpeed(CI_DEV_T *cidev, UINT32 speed)
{

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	if (!ci_is_init_done(cidev))
	{
		LOG_ERROR("[ CI Block Init not completed <<F>> ]");
		return -EFAULT;
	}

	return SetPcmciaSpeed(cidev, speed);

}

static u16 ci_burst_ctrl_val[] = {
	[ACCESS_1BYTE_MODE]	= 0x00,
	[ACCESS_2BYTE_MODE]	= 0x01,
	[ACCESS_4BYTE_MODE]	= 0x03,
};

//Internal use
int ci_hw_change_access_mode(CI_DEV_T *cidev, u32 mode)
{
	if (mode > ACCESS_4BYTE_MODE) {
		LOG_WARNING("Invalid mode : %d", mode);
		return -1;
	}

	LOG_INFO("set change mode : %d", mode);
	CI_WRITE16(cidev, ci_burst_ctrl_val[mode], CREG_BUSRT_CTRL);

	return 0;
}

/**
 * @brief
 *   core bridge function : set CAM data burst mode
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   mode :setting value
 * @return
 *  int
 */
int CI_OPS_ChangeAccessMode(CI_DEV_T *cidev, UINT32 mode)
{
	CHECK_ERROR(!cidev, return -EINVAL, "NULL cidev");
	if (!ci_is_init_done(cidev))
	{
		LOG_ERROR("[ CI Block Init not completed <<F>> ]");
		return -EFAULT;
	}

	return ci_hw_change_access_mode(cidev, mode);
}

static int ci_hw_uninit_buf(CI_DEV_T *cidev)
{
	if (cidev->cis_info != NULL) {
		ci_free(cidev->cis_info);
		cidev->cis_info = NULL;
	}

	if (cidev->io.buf != NULL) {
		ci_free(cidev->io.buf);
		cidev->io.buf = NULL;
	}

	return 0;
}

static int ci_hw_init_buf(CI_DEV_T *cidev)
{
//	int ret;

	cidev->io.buf = (u8 *)ci_malloc(MAX_IO_BUF_SIZE);
	if (cidev->io.buf == NULL) {
		LOG_ERROR("unable to allocte cidev->io.buf failed");
	//	ret = -ENOMEM;
		goto out;
	}

	cidev->cis_info = (void *)ci_zalloc(sizeof(ci_dev_cis_info_t));
	if (cidev->cis_info == NULL) {
		LOG_ERROR("unable to allocte cidev->cis_info failed\n");
	//	ret = -ENOMEM;
		goto out_buf;
	}

	return 0;

out_buf:
	ci_free(cidev->io.buf);
	cidev->io.buf = NULL;

out:
	return -ENOMEM;
}

static int ci_hw_uninit_smc(CI_DEV_T *cidev)
{
	unsigned long flags;

	ci_lock_irqsave(cidev, flags);

	if (cidev->smc_addr) {
		iounmap((void *)cidev->smc_addr);
		LOG_NOTI("CI unmap smc[0x%p]\n", cidev->smc_addr);
		cidev->smc_addr = 0;
	}

	ci_unlock_irqrestore(cidev, flags);

	return 0;
}

#define SMBIDCYR		(0x00)
#define SMBCR			(0x14)
#define IDCY_MASK		(0xf)
#define IDLE_CYCLE			0x00
#define SMBCR_MW16BIT		(1 << 6)
#define SMBCR_WAITEN	(1 << 2)
#define SMBCR_RBLE		(1 << 0)
static int ci_hw_init_smc(CI_DEV_T *cidev)
{
	CI_CFG_T *cfg = cidev->cfg;
	int ret = 0;
	UINT16 reg_val;

	cidev->smc_addr = (void *)0;
	if (cfg->smc_phys_addr && cfg->smc_phys_size) {
		cidev->smc_addr = ioremap(cfg->smc_phys_addr, cfg->smc_phys_size);
		if (!cidev->smc_addr) {
			LOG_ERROR("smc ioremap failed : base[0x%08X] size[0x%08X]\n",
					cfg->smc_phys_addr, cfg->smc_phys_size);
			ret = -ENOMEM;
			goto out;
		}
		LOG_NOTI("CI ioremap smc[0x%p <- 0x%08X]", cidev->smc_addr, cfg->smc_phys_addr);

		if(cfg->smc_need_vcc)
		{
			/* VCC Enable before access smc (M16P3 issue) */
			reg_val = CI_READ16(cidev, CREG_CTRL_STATUS_1);
			CI_WRITE16(cidev, (reg_val | VCC_SW0), CREG_CTRL_STATUS_1);

			/* VCC up time: typical 0.5 ms, max 1.5 ms */
			LOG_NOTI("VCC on before Access SMC (5 ms)");

			ci_sleep(5);

			writel(IDLE_CYCLE & IDCY_MASK, (void *)((uintptr_t)cidev->smc_addr + SMBIDCYR));
			writel(SMBCR_MW16BIT | SMBCR_WAITEN | SMBCR_RBLE, (void *)((uintptr_t)cidev->smc_addr + SMBCR));

			/* Recover Vcc status */
			CI_WRITE16(cidev, reg_val, CREG_CTRL_STATUS_1);
		}
		else
		{
			writel(IDLE_CYCLE & IDCY_MASK, (void *)((uintptr_t)cidev->smc_addr + SMBIDCYR));
			writel(SMBCR_MW16BIT | SMBCR_WAITEN | SMBCR_RBLE, (void *)((uintptr_t)cidev->smc_addr + SMBCR));
		}

		LOG_DBG1("> smc_addr[0x00] <- 0x%08X\n", readl((void *)cidev->smc_addr));
		LOG_DBG1("> smc_addr[0x14] <- 0x%08X\n", readl((void *)((uintptr_t)cidev->smc_addr + (uintptr_t)0x14)));
	}

out:
	return ret;
}

static int ci_hw_uninit_pre(CI_DEV_T *cidev)
{
	unsigned long flags;

	ci_lock_irqsave(cidev, flags);

	if (cidev->reg_addr)
	{
		iounmap((void __iomem *)cidev->mod_addr);
		iounmap((void __iomem *)cidev->reg_addr);

		cidev->mod_addr = 0;
		cidev->reg_addr = 0;
	}

	ci_hw_uninit_buf(cidev);

	ci_unlock_irqrestore(cidev, flags);

	return 0;
}

int CI_OPS_Uninit(CI_DEV_T *cidev)
{
	ci_hw_uninit_smc(cidev);

	ci_hw_uninit_pre(cidev);

	return 0;
}

static void __ci_hw_init_post_1(CI_DEV_T *cidev)
{
	PrintRegisters(cidev, LOG_LEVEL_DBG1);

	ci_is_card_detected(cidev) = 0;
	ci_is_power_restart(cidev) = 0;
	ci_is_init_done(cidev) = 0;
	ci_is_flag_reset_for_cam(cidev);

	LOG_DBG2(">> Reset Card Control 1\n");

	mutex_lock(&cidev->access_mutex); //For Power Off

	CI_WRITE16(cidev, INIT_VAL, CREG_CTRL_STATUS_1);
	cidev->power_on = 0;
	cidev->on_init = 0;

	mutex_unlock(&cidev->access_mutex);

	// Set POD Mode (for fix test)
#ifdef POD_ON_INIT
	LOG_DBG2(">> Set POD Mode\n");
	CI_WRITE16(cidev, POD_MODE, CREG_CTRL_STATUS_3);
#else
	// Set Not-POD Mode
	LOG_DBG2(">> Set Not-POD Mode\n");
	CI_WRITE16(cidev, INIT_VAL, CREG_CTRL_STATUS_3);
#endif

	LOG_DBG2(">> Init Interrupt Control\n");
	CI_WRITE16(cidev, INIT_VAL, CREG_INTR_CTRL);

	// Interrupt Enable
	LOG_DBG2(">> Interrupt Enable\n");
	CI_WRITE16(cidev, 0xFFFE, CREG_INTR_MASK);
}

static void __ci_hw_init_post_2(CI_DEV_T *cidev)
{
	// CI Module detect ... check if module is already inserted
	LOG_DBG2(">> Module Detection\n");
	ci_hw_detect_card_process(cidev, 0);

#if 1
	SetPcmciaSpeed(cidev, PCMCIA_BUS_SPEED_LOW);
#else
	LOG_DBG2(">> PCMCIA Bus Speed Min - control 2\n");
	CI_WRITE16(cidev, 0x0F03, CREG_PC_CARD_CTRL_2);

	LOG_DBG2(">> PCMCIA Bus Speed Min - control 3\n");
	CI_WRITE16(cidev, 0x0003, CREG_PC_CARD_CTRL_3);
#endif

	LOG_DBG2(">> Init Interrupt Flag\n");
	CI_WRITE16(cidev, INIT_VAL, CREG_INTR_FLAG);
}

static int ci_hw_init_post(CI_DEV_T *cidev)
{
	unsigned long flags;

	ci_lock_irqsave(cidev, flags);
	__ci_hw_init_post_1(cidev);
	ci_unlock_irqrestore(cidev, flags);

	// for interrupt signal is stabled
	ci_sleep(ci_get_delay_param(cidev, DELAY_INIT_AFTER_INTERRUPT_ENABLE));

	ci_lock_irqsave(cidev, flags);
	__ci_hw_init_post_2(cidev);
	ci_unlock_irqrestore(cidev, flags);

	PrintRegisters(cidev, LOG_LEVEL_DBG1);

	LOG_DBG2(">> Done\n");

	return 0;
}

static int ci_hw_init_pre(CI_DEV_T *cidev)
{
	CI_CFG_T *cfg = cidev->cfg;
	unsigned long flags;
	int ret = 0;

	ci_lock_irqsave(cidev, flags);

	ret = ci_hw_init_buf(cidev);
	if (ret != 0) {
		goto out;
	}

	LOG_DBG1("> ioremap\n");

	cidev->reg_addr = ioremap(cfg->reg_base, cfg->reg_size);
	cidev->mod_addr = ioremap(cfg->mod_base, cfg->mod_size);

	LOG_DBG1("> cidev->reg_addr = 0x%p\n", cidev->reg_addr);
	LOG_DBG1("> cidev->mod_addr = 0x%p\n", cidev->mod_addr);
	if (!cidev->reg_addr || !cidev->mod_addr) {
		LOG_ERROR("failed!!!\n");
		ret = -ENOMEM;
		goto out_malloc;
	}

	ci_unlock_irqrestore(cidev, flags);

	return 0;

out_malloc:
	iounmap((void __iomem *)cidev->mod_addr);
	iounmap((void __iomem *)cidev->reg_addr);
	cidev->mod_addr = 0;
	cidev->reg_addr = 0;

//out_buf:
	ci_hw_uninit_buf(cidev);

out:
	ci_unlock_irqrestore(cidev, flags);
	return ret;
}

/* sub-function flow
ci_hw_init - ci_hw_init_pre  : malloc & ioremap
             ci_hw_init_smc  : smc control
             ci_hw_init_post - __ci_hw_init_post_1 : reg. init
                               __ci_hw_init_post_2 : card detection & speed setting
*/
int CI_OPS_Init(CI_DEV_T *cidev)
{
	int ret = 0;

	ret = ci_hw_init_pre(cidev);
	if (ret != 0) {
		LOG_ERROR("error : init pre\n");
		goto out;
	}

	ret = ci_hw_init_smc(cidev);
	if (ret != 0) {
		LOG_ERROR("error : init smc\n");
		goto out_pre;
	}

	ret = ci_hw_init_post(cidev);
	if (ret != 0) {
		LOG_ERROR("error : init post\n");
		goto out_smc;
	}

	ci_is_init_done(cidev) = 1;

	return 0;

out_smc:
	ci_hw_uninit_smc(cidev);

out_pre:
	ci_hw_uninit_pre(cidev);

out:
	return ret;
}

/**
 * @brief
 *   core bridge function : Reset CI host
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   _cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_OPS_Reset(CI_DEV_T *cidev)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ci_is_power_restart(cidev) = 1;
	return 0;
}

static void __ci_hw_cam_off(CI_DEV_T *cidev)
{
	LOG_DBG1("> CAM off\n");

	/* Power Off */
	ci_is_flag_reset_for_cam(cidev);

	mutex_lock(&cidev->access_mutex); //For Power Off

	CI_WRITE16(cidev, 0x0000, CREG_CTRL_STATUS_1);
	ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_POWER_OFF);
	cidev->power_on = 0;

	mutex_unlock(&cidev->access_mutex);
}

static void ResetIOErrs(CI_DEV_T *cidev)
{
	ci_io_lock(cidev);

	memset((void *)(&cidev->io.wr), 0x00, sizeof(CI_IO_ERR_INFO_T));
	memset((void *)(&cidev->io.rd), 0x00, sizeof(CI_IO_ERR_INFO_T));

	ci_io_unlock(cidev);
}

static int __ci_hw_cam_init(CI_DEV_T *cidev)
{
	u16 reg_val = 0x0;

	ci_hw_reset_cis_info(cidev);
	ci_hw_reset_nego_info(cidev);

	ResetIOErrs(cidev);

	ci_dbg_perf_reset(cidev);
	ci_dbg_test_reset(cidev);

	LOG_DBG1("> CAM init");

	ci_sleep(ci_get_delay_param(cidev, DELAY_CAM_INIT_VCC_CARD_RESET));

	/* Power On */
	/*
	 * VCCEN_N = Active-LOW
	 * CTOP power polarity default setting = By-pass
	 * AP2151WG(IC700) EN = Active-High
	 * So, 'unRegVal |= VCC_SW0' generates HIGH signal
	 * and makes power IC enable signal.
	 */

	mutex_lock(&cidev->access_mutex); //For Power On (Only VCC_EN matters)

	reg_val = CI_READ16(cidev, CREG_CTRL_STATUS_1);
	reg_val |= VCC_SW0;
	CI_WRITE16(cidev, reg_val, CREG_CTRL_STATUS_1);
	ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_POWER_ON);
	cidev->power_on = 1;

	mutex_unlock(&cidev->access_mutex);

	/* Enable Card */

	/* 20150902 Hyunjong Yim.
	   Before, CI module received PCI enable signal(CE) and Reset H signal
	   at same time and after that, Reset L signal receive.(By register control)

	   But in CI spec, CI module should have at least 20ms delay between
	   Reset signal's toggle and PCI card enable(CE). So, Reset H with PCI enable
	   at same time is spec out.

	   Because of this, split Reset H siganl and PCI enable signal's enable and
	   Change code location for Reset L signal enable.

	   By this, 3 kinds of CI CAM which cannot detect before can work find
	   in Certification Test at HE center. */

	/* 20150902 Hyunjong Yim.
	   Set 300ms delay before Reset H by CI spec. */
	ci_sleep(ci_get_delay_param(cidev, DELAY_CAM_INIT_VCC_CARD_RESET));

	reg_val = CI_READ16(cidev, CREG_CTRL_STATUS_1);
	reg_val |= (CARD_RESET);
	CI_WRITE16(cidev, reg_val, CREG_CTRL_STATUS_1);
	ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_RESET_L);

	/* 20150902 Hyunjong Yim.
	   Set 20ms delay before Reset L by CI spec.
	   (in spec, min value is 5ms. But gives more margine.) */
	ci_sleep(ci_get_delay_param(cidev, DELAY_CAM_INIT_CARD_RESET_NOT_RESET));

	reg_val &= ~CARD_RESET;
	CI_WRITE16(cidev, reg_val, CREG_CTRL_STATUS_1);
	ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_RESET_H);

	/* 20150902 Hyunjong Yim.
	   Set 80ms delay before PCI card Enable (Card Enable, CE)
	   by CI spec. (in spec, min value is 20ms, but gives more margine) */
	ci_sleep(ci_get_delay_param(cidev, DELAY_CAM_INIT_CARD_RESET_EN_PCCARD));

	reg_val = CI_READ16(cidev, CREG_CTRL_STATUS_1);
	reg_val |= (EN_PCCARD);
	CI_WRITE16(cidev, reg_val, CREG_CTRL_STATUS_1);
//	ci_pcap_mon_hw_evt(cidev, CI_PCAP_HW_EVT_RESET_L);

	/* 20150902 Hyunjong Yim.
	   Set 20ms delay after PCI card Enable (Card Enable, CE).
	   This is not about spec code, but works well when this delay
	   set here in before code. So remain this here. */
	ci_sleep(ci_get_delay_param(cidev, DELAY_CAM_INIT_CARD_RESET_NOT_RESET));

	ci_hw_change_access_mode_byte(cidev, 1);

	PrintRegisters(cidev, LOG_LEVEL_DBG1);

	ci_is_cam_init_done(cidev) = 1;

	return OK;
}

/**
 * @brief
 *   core bridge function : Turn-off CI CAM
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *  cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_OPS_CAMOff(CI_DEV_T *cidev)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	mutex_lock(&cidev->access_mutex); //For Power Off

	cidev->on_init = 1;

	mutex_unlock(&cidev->access_mutex);

	ci_is_power_restart(cidev) = 1;
	__ci_hw_cam_off(cidev);
	return 0;
}
/**
 * @brief
 *   core bridge function : Turn-on CI CAM
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *  cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_OPS_CAMOnCompleted(CI_DEV_T *cidev)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ci_is_power_restart(cidev) = 0;

	return 0;
}

/**
 * @brief
 *   core bridge function : Initialize CI CAM
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   _cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_OPS_CAMInit(CI_DEV_T *cidev)
{
	int rc;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	mutex_lock(&cidev->access_mutex); //For Power Off

	cidev->on_init = 1;

	mutex_unlock(&cidev->access_mutex);

	__ci_hw_cam_off(cidev);
	rc = __ci_hw_cam_init(cidev);

	mutex_lock(&cidev->access_mutex); //For Power Off

	cidev->on_init = 0;

	mutex_unlock(&cidev->access_mutex);

	return rc;
}

/**
 * @brief
 *   core bridge function : Reset CI CAM (CI+)
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_OPS_SetPhysReset(CI_DEV_T *cidev)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* detect & init */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	mutex_lock(&cidev->access_mutex);
	CHECK_ERROR(!cidev->power_on, goto out, "VCC Power Off");

	ci_cam_wr_status(cidev, RESET_PHY_INT);

	mutex_unlock(&cidev->access_mutex);
	LOG_INFO("Reset Physical Intrf <<S>>");

	return 0;

out:
	mutex_unlock(&cidev->access_mutex);
	LOG_ERROR("Reset Physical Intrf <<F>>");

	return -EFAULT;
}

/**
 * @brief
 *   core bridge function : Reset CI CAM
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_OPS_SetRS(CI_DEV_T *cidev)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* detect & init */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	mutex_lock(&cidev->access_mutex);
	CHECK_ERROR(!cidev->power_on, goto out, "VCC Power Off");

	ci_cam_wr_cmd(cidev, CI_RS);

	mutex_unlock(&cidev->access_mutex);
	LOG_INFO("Set RS <<S>>");

	return 0;

out:
	mutex_unlock(&cidev->access_mutex);
	LOG_ERROR("Set RS <<F>>");

	return -EFAULT;
}

/**
 * @brief
 *   core bridge function : Check CAM-detection status
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   status :pointer of CAM-detection status
 * @return
 *  int
 */
int CI_OPS_DetectCard(CI_DEV_T *cidev, UINT32 *status)
{
	*status = 0;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	ci_hw_verify_card_detection(cidev, 1, __func__);

	(*status) = ci_is_card_detected(cidev);

	LOG_DBG1("> CAM Module is %s\n", (*status) ? "inserted" : "removed");

	return 0;

}

/**
 *	Perform software reset of hardware IO interface
 */
int ci_hw_io_soft_reset(CI_DEV_T *cidev)
{
//	volatile u8 status_reg;
	int	chk_cnt, delay;
	int ret;

	ci_cam_wr_cmd(cidev, CI_RS);

	chk_cnt = ci_get_delay_param(cidev, DELAY_MAXIM_RETRY_CNT);
	delay = ci_get_delay_param(cidev, DELAY_IO_SOFT_RESET_CHECK_FR);
	ret = ci_hw_wr_io_chk_fr(cidev, chk_cnt, delay, WR_PWR_SKIP,
							"IO reset soft : status error (FR=0)");
//	if (ret != 0) {
	if (ret == -ENODEV) {
		return ret;
	}

	/* CI spec doesn't say that RS must be cleared on soft reset. but */
	/* in case of some modules RS must be cleared to complete soft reset */
	ci_cam_wr_cmd(cidev, 0x00);

	// OS_MsecSleep(10) L9 Originally Blocked by comment , but Previous Exist, So Ready with 0 jinhwan.bae
	ci_sleep(ci_get_delay_param(cidev, DELAY_IO_END_SOFT_RESET));

	return 0;
}

static int _ci_hw_nego_buff_softreset(CI_DEV_T *cidev)
{
	int ret;

	LOG_DBG3(">>> step 1 : perform sw reset\n");

	ret = ci_hw_io_soft_reset(cidev);
	if (ret != 0) {
		LOG_ERROR("IO nego buff : HW_IO_ResetSoft() failed\n");
		return ret;
	}
	ci_nego_step(cidev) = CI_NEGO_STEP_SOFT_RESET;
	return 0;
}

static int _ci_hw_nego_buff_get_size(CI_DEV_T *cidev, u16 *_size)
{
	int	chk_cnt, delay;
	int size, size_len;
	int ret;

	LOG_DBG3(">>> step 2 : read buffer size from module\n");

	(*_size) = 0;

	ci_cam_wr_cmd(cidev, CI_SR);
	chk_cnt = ci_get_delay_param(cidev, DELAY_MAXIM_RETRY_CNT);
	delay = ci_get_delay_param(cidev, DELAY_IO_NEGO_BUFF_CHECK_DA);
	ret = ci_hw_rd_io_chk_da(cidev, chk_cnt, delay,
							"IO nego buff : data not available");
	if (ret != 0) {
		return ret;
	}
	ci_nego_step(cidev) = CI_NEGO_STEP_GET_BUFF_SIZE;

	/* read the length of buffer size */
//	LOG_DBG3(">> read size ms\n");
	size_len = ((u16)ci_cam_rd_size_ms(cidev))<<8;
//	LOG_DBG3(">> read size ls\n");
	size_len |= (u16)ci_cam_rd_size_ls(cidev);

	LOG_IO_INFO("length of module buffer size = %d\n", size_len);

	/* read the high byte of buffer size */
	size = (u16)ci_cam_rd_data(cidev);
	if (size_len == 2) {
		/* read the low byte of buffer size */
		size <<= 8;
		size |= (u16)ci_cam_rd_data(cidev);
	}

	(*_size) = size;

	LOG_IO_INFO("%s buffer size = %d\n", ci_dev_name(cidev), size);

	ci_pcap_mon_nego_pkt(cidev, size, CI_PCAP_DATA_CAM_TO_HOST);

	ci_cam_wr_cmd(cidev, 0x00);

	return 0;
}

static int _ci_hw_nego_buff_chk_size(CI_DEV_T *cidev, u16 size)
{
	LOG_DBG3(">>> step 3 : determine buffer size\n");
//	if ((size<MOD_BUF_SIZE_MIN) || (size>MOD_BUF_SIZE_MAX)) {
	if (size < MOD_BUF_SIZE_MIN) {
		LOG_ERROR("IO nego buff : invalid module buffer size[%d]\n", size);
		return -EFAULT;
	}
#if 0
	if (size > MOD_BUF_SIZE_MAX) {
		size = (UINT16) MOD_BUF_SIZE_MAX;
	}
#endif
	ci_nego_step(cidev) = CI_NEGO_STEP_FIX_BUFF_SIZE;

	ci_nego_buff_size(cidev) = size;

	LOG_IO_INFO("negotiated buffer size = %d[0x%04X]\n", size, size);

	return 0;
}

static int _ci_hw_nego_buff_set_size(CI_DEV_T *cidev, u16 size)
{
	int	chk_cnt, delay;
	int ret;

	LOG_DBG3(">>> step 4 : write buffer size on module\n");

	ci_cam_wr_cmd(cidev, CI_SW|CI_HC);
	chk_cnt = ci_get_delay_param(cidev, DELAY_MAXIM_RETRY_CNT);
	delay = ci_get_delay_param(cidev, DELAY_IO_NEGO_BUFF_CHECK_FR);
	ret = ci_hw_wr_io_chk_fr(cidev, chk_cnt, delay, WR_PWR_SKIP,
							"IO nego buff : status error (FR=0)");
	if (ret != 0) {
		return ret;
	}
	ci_nego_step(cidev) = CI_NEGO_STEP_SET_BUFF_SIZE;

	/* write the size of buffer size */
//	LOG_DBG2("write buffer size : ls - 0x02\n");
	ci_cam_wr_size_ls(cidev, (u8)0x02);
//	LOG_DBG2("write buffer size : ms - 0x00\n");
	ci_cam_wr_size_ms(cidev, (u8)0x00);

	/* write the high byte of buffer size */
	LOG_DBG3(">>> write ms byte of buffer Size : 0x%02X\n", (u8)((size>>8)&0xFF));
	ci_cam_wr_data(cidev, (u8)((size>>8)&0xFF));
	/* write the low byte of buffer size */
	LOG_DBG3(">>> write ls byte of Buffer Size : 0x%02X\n", (u8)(size&0xFF));
	ci_cam_wr_data(cidev, (u8)(size&0xFF));

	//  OS_MsecSleep(10) In L9, Previous 10 Exist. Please Refer to that at the problem. jinhwan.bae
	ci_sleep(ci_get_delay_param(cidev, DELAY_IO_NEGO_BUFF_AFTER_WRITE_DATA));

	ci_cam_wr_cmd(cidev, 0x00);

	ci_pcap_mon_nego_pkt(cidev, size, CI_PCAP_DATA_HOST_TO_CAM);

	return 0;
}

int CI_OPS_NegoBuff(CI_DEV_T *cidev, UINT32 *nego_buff_size)
{
	UINT16 size;
	int ret = -EFAULT;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR(!nego_buff_size, return -EFAULT, "nego_buff_size is NULL");

	/* detect & init & cor */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");
	CHECK_ERROR(!ci_is_cam_cor_done(cidev), return -EFAULT, "[ CAM COR-Write not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	mutex_lock(&cidev->access_mutex);
	CHECK_ERROR(!cidev->power_on, goto out, "VCC Power Off");

	ci_nego_buff_size(cidev) = 0;
	ci_nego_step(cidev) = CI_NEGO_STEP_START;

	LOG_IO_INFO("status reg value before reset => 0x%02X\n", ci_cam_rd_status(cidev));

	ci_sleep(ci_get_delay_param(cidev, DELAY_IO_NEGO_BUFF_BEFORE_SOFT_RESET));

	/* STEP 1: PERFORM SOFTWARE RESET ----------------------------------------*/
	ret = _ci_hw_nego_buff_softreset(cidev);
	if (ret != 0) {
		LOG_ERROR("IO nego buff : HW_IO_ResetSoft() failed\n");
		goto out;
	}

	/* STEP 2: READ BUFFER SIZE FROM MODULE ----------------------------------*/
	ret = _ci_hw_nego_buff_get_size(cidev, &size);
	if (ret != 0) {
		goto out;
	}

	/* STEP 3: DETERMINE BUFFER SIZE -----------------------------------------*/
	ret = _ci_hw_nego_buff_chk_size(cidev, size);
	if (ret != 0) {
		goto out;
	}

	/* STEP 4: WRITE BUFFER SIZE TO MODULE -----------------------------------*/
	ret = _ci_hw_nego_buff_set_size(cidev, size);
	if (ret != 0) {
		goto out;
	}

	ci_is_cam_nego_done(cidev) = 1;

	*nego_buff_size = ci_nego_buff_size(cidev);

	mutex_unlock(&cidev->access_mutex);

	LOG_IO_INFO("Buffer negotiation SUCCESS\n");
	LOG_INFO("Calc Negotiation Buffer <<S>>\n");

	return 0;

out:
	*nego_buff_size = 0;

	mutex_unlock(&cidev->access_mutex);

	LOG_ERROR("nego error : ret[%d], step[%d]\n", ret, ci_nego_step(cidev));
	LOG_ERROR("Calc Negotiation Buffer <<F>>\n");
	return ret;
}

/**
 * @brief
 *   core bridge function : Check if CI+ or not
 *   (not trustworthy because the actual version is detected by resource identifier)
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   cam_type :pointer of CAM type
 * @return
 *  int
 */
int CI_OPS_CheckCapability(CI_DEV_T *cidev, UINT32 *cam_type)
{
	cis_vers_1_t *vers;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* check CAM detect status */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");

	vers = &(cidev->cis_info->info_vers_1);

// for lower capability (return 1 if any ciplus is written)
	*cam_type = (vers->is_checked)? vers->is_ci_plus : -1;
	return 0;
}

/**
 * @brief
 *   core bridge function : get CI+ version
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   version :pointer of CI+ version
 * @return
 *  int
 */
int CI_OPS_GetCiplusVer(CI_DEV_T *cidev, UINT32 *version)
{
	cis_vers_1_t *vers;

	*version = -1;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR(!version, return -EFAULT, "version is NULL");

	/* check CAM detect status */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");

	vers = &(cidev->cis_info->info_vers_1);

	*version = (vers->is_checked)? vers->version : -1;
	return 0;
}

/**
 * @brief
 *   core bridge function : get CI+ profile
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   profile :pointer of CI+ profile
 * @return
 *  int
 */
int CI_OPS_GetCiplusOPProfile(CI_DEV_T *cidev, UINT32 *profile)
{
	cis_vers_1_t *vers;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR(!profile, return -EFAULT, "profile is NULL");

	/* check CAM detect status */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");

	vers = &(cidev->cis_info->info_vers_1);

	(*profile) = (vers->is_checked)? vers->profile : -1;
	return 0;
}

/**
 * @brief
 *   core bridge function : set H/W control options
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   func :function select
 *   mode :pointer of function parmeter
 * @return
 *  int
 */
int CI_OPS_ControlOption(CI_DEV_T *cidev, u32 func, u32 *mode)
{
	int set_option;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR(!mode, return -EFAULT, "mode is NULL");

	set_option = !!(func & (1<<31));
	func &= 0xFFFF;
	if (set_option)	{	//write
		switch (func) {
		case 0x0000 :
			ci_opt_io_mode(cidev) = ((*mode))? CI_ERR_CHK_MODE_SIMPLE : CI_ERR_CHK_MODE_FULL;
			break;
		default:
			LOG_ERROR("invalid func [0x%X]", func);
			break;
		}
	} else { //read
		switch (func) {
		case 0x0000 :
			(*mode) = (ci_opt_io_mode(cidev))? CI_ERR_CHK_MODE_SIMPLE : CI_ERR_CHK_MODE_FULL;
			break;
		default:
			LOG_ERROR("invalid func [0x%X]", func);
			break;
		}
	}

	return 0;
}

int CI_OPS_SetHWMode(CI_DEV_T *cidev, UINT16 mode, UINT16 val)
{
	const char *str;

	if(mode == CHIP_MODE_ATTR) str = "attr";
	else if (mode == CHIP_MODE_IO) str = "io";
	else str = "Unknown";

	LOG_DBG3(">>> control status 3 : 0x%04X\n", val);
	CI_WRITE16(cidev, val, CREG_CTRL_STATUS_3);
	LOG_DBG3(">>> set mode %s : 0x%04X\n", str, mode);
	CI_WRITE16(cidev, mode, CREG_PC_CARD_CTRL_1);
	return 0;
}

/**
 * @brief
 *   core bridge function : get DA(Data Available) status
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   da_stauts :pointer of DA stauts
 * @return
 *  int
 */
int CI_OPS_ReadDAStatus(CI_DEV_T *cidev, UINT32 *da_status)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* detect & init */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	*da_status = (ci_rd_chk_da(cidev)) ? 1 : 0;
	return 0;
}

/**
 * @brief
 *   core bridge function : get IIR(Initialize Interface Request) status
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   _cidev :pointer of ci device structure
 *   iir_stauts :pointer of IIR stauts
 * @return
 *  int
 */
int CI_OPS_ReadIIRStatus(CI_DEV_T *cidev, UINT32 *iir_status)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* detect & init */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	(*iir_status) = (ci_rd_chk_iir(cidev)) ? 1 : 0;
	return 0;
}

/**
 * @brief
 *   core bridge function : show current register values
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
* @return
 *  int
 */
int CI_OPS_ShowRegisters(CI_DEV_T *cidev)
{
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	LOG_NOTI("Print Registers\n");
	PrintRegisters(cidev, LOG_LEVEL_NOTI);

	return 0;
}

/**
 * @brief
 *   core bridge function : update a register value
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   idx :target register index
 *   val :register value to update
 * @return
 *  int
 */
int CI_OPS_WriteReg(CI_DEV_T *cidev, UINT32 idx, UINT32 val)
{
	UINT32 value_old;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR((idx & 0x01), return -EINVAL, "invalid reg addr : 0x%04X", idx);
	CHECK_ERROR(idx > CREG_HS_CTRL_8, return -EINVAL, "invalid reg addr : 0x%04X", idx);
	CHECK_ERROR(val > 0xFFFF, return -EINVAL, "value overflow : 0x%08X", val);

	value_old = CI_READ16(cidev, idx);
	CI_WRITE16(cidev, val, idx);
	LOG_NOTI("Reg[0x%04X] value changed : [0x%04X] -> [0x%04X]\n", idx, value_old, val);

	return 0;
}

int CI_OPS_Suspend(CI_DEV_T *cidev)
{
	int ret;

	ret = ci_hw_uninit_smc(cidev);
	return ret;
}

int CI_OPS_Resume(CI_DEV_T *cidev)
{
	int ret;

	ret = ci_hw_init_smc(cidev);
	CHECK_ERROR(ret != 0, return ret, "error : init smc");

	ret = ci_hw_init_post(cidev);
	CHECK_ERROR(ret != 0, return ret, "error : init post");

	ci_is_init_done(cidev) = 1;

	return ret;
}

static irqreturn_t _ci_hw_irq_handler(CI_DEV_T *cidev, int irq)
{
	irqreturn_t irq_ret = IRQ_HANDLED;
	u16 intr_flag = 0;

	ci_lock(cidev);

	LOG_ISR("[%s] irq handler", ci_dev_name(cidev));

	CI_WRITE16(cidev, CD_CHANGED_DISABLE_INT, CREG_INTR_MASK);
	LOG_ISR("> set intr mask : 0x%04X (disable)", CD_CHANGED_DISABLE_INT);

	intr_flag = CI_READ16(cidev, CREG_INTR_FLAG);
	LOG_ISR("> get intr flag = 0x%04X", intr_flag);

	/* Check CI detect interrupt and update the flag */
	if (intr_flag & CD_CHANGED) {
		ci_hw_detect_card_process(cidev, 1);

		CI_WRITE16(cidev, intr_flag & 0xFE, CREG_INTR_FLAG);
		LOG_ISR("> set intr flag : 0x%04X", intr_flag & 0xFE);

		complete(&cidev->completion);
	}

	CI_WRITE16(cidev, CD_CHANGED_ENABLE_INT, CREG_INTR_MASK);
	LOG_ISR("> set intr mask : 0x%04X (enable)", CD_CHANGED_ENABLE_INT);

	ci_unlock(cidev);

	/* ilkyu.kim, 2016/06/08
	 * Try to recover power off mechanism to find out the original reason */

	/*------------------------------------------------------------------------
	  * Jinhwan Bae , 2012/09/17
	  * To Block POWER OFF and PC CARD Disable at the time of CAM removing
	  * Because, if we set like this, PCMCIA Bus latch Up happened
	  * at the time of access bus by CPU without CAM,
	  * it causes the problem that System Latch Up when we insert/remove CAM repeatedly
	  * The problem opened at 2nd SU of L9 Platform, but same problem exist in H13.
	  * Found temp solution and adapted it until new H/W solution in H15.
	  *-----------------------------------------------------------------------*/
#if 1
	//FIXME
	//queue_work(cidev->workqueue, &cidev->work);
#endif

	return irq_ret;
}

irqreturn_t CI_irq_handler(int irq, void *dev_id)
{
	CI_DEV_T *cidev = dev_id;
	irqreturn_t irq_ret = IRQ_HANDLED;

	if (cidev == NULL) {
		LOG_ERROR("NULL cidev");
		goto out;
	}

	if (!ci_is_init_done(cidev)) {
		LOG_ERROR("[ CI Block Init not completed <<F>> ]");
		goto out;
	}

	irq_ret = _ci_hw_irq_handler(cidev, irq);

out:
	return irq_ret;
}

