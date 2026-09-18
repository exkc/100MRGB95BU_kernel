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

static int _ci_hw_io_chk_buff_size(u8 **_tbuf, u8 **_pbuf, u8 *io_buf, u16 size)
{
	u8 *tbuf, *pbuf;

	if (size > MAX_IO_BUF_SIZE) {
		tbuf = ci_malloc(size);
		if (tbuf == NULL) {
			return -ENOMEM;
		}
		pbuf = tbuf;
	} else {
		tbuf = NULL;
		pbuf = io_buf;
	}

	(*_tbuf) = tbuf;
	(*_pbuf) = pbuf;

	return 0;
}

static void _ci_hw_io_dbg_buf_print(CI_DEV_T *cidev, u8 *pbuf, u16 size, int read)
{
#ifdef CI_IO_DUMP
	int i;

	LOG_IO_INFO("%s Data(%d): ", (read)? "Read":"Write", size);
	for (i = 0; i < size; i++) {
		LOG_IO_INFO("0x%02X ", pbuf[i]);
	}
	LOG_IO_INFO("\n");
#endif /* CI_IO_DUMP */
}

static void _ci_hw_io_time_show_size(CI_DEV_T *cidev, u16 size)
{
	if (ci_opt_io_time_show(cidev)) {
		LOG_IO_INFO("original data size is %d bytes <<S>>\n", size);
	}
}

static void _ci_hw_io_time_show_result(CI_DEV_T *cidev,
									ktime_t start_t,
									ktime_t end_t,
									u16 size,
									int read)
{
	if (ci_opt_io_time_show(cidev)) {
		cim_time_us_io(start_t, end_t, size);
	//	cim_time_us_io(data_t, end_t, size);
	} else {
		if (size) {
		#if 1
			LOG_IO_INFO("%d bytes of data %s <<S>>\n",
					size, (read)? "read":"write");
		#else
			LOG_IO_INFO("%s IO Data Success ... \n",
					(read)? "Read":"Write");
		#endif
		} else {
			LOG_ERROR("\n %s IO Data <<F>>\n\n",
					(read)? "Read":"Write");
		}
	}
}

static int _ci_hw_read_io_data_size(CI_DEV_T *cidev, u16 *size)
{
	int	chk_cnt, delay;
	u16 rsize;
	int ret;

	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_R_PRE);
	delay = ci_get_delay_param(cidev, DELAY_IO_READ_CHECK_DA);
	ret = ci_hw_rd_io_chk_da(cidev, chk_cnt, delay,
							"IO read : IO busy (DA=0)");
	if (ret != 0) {
		ci_set_io_rd_err_code(cidev, CI_IO_ERR_RD_1ST_CHK_DA);
		return ret;
	}

	/* read the size of data */
	rsize = ((u16)ci_cam_rd_size_ms(cidev))<<8;
	rsize |= (u16)ci_cam_rd_size_ls(cidev);
	LOG_DBG3(">>> size = 0x%04X\n", rsize);

	if (rsize < 2) {
		LOG_ERROR("IO read : Too small size[%d]\n", rsize);
		return -EFAULT;
	}
	if (rsize > ci_nego_buff_size(cidev)) {
		LOG_ERROR("IO read : size is bigger than buffer (size=%d, buff=%d)\n",
				rsize, ci_nego_buff_size(cidev));
		return -EFAULT;
	}
	(*size) = rsize;
	return 0;
}

static int _ci_hw_read_io_data_first(CI_DEV_T *cidev, u8 *buf, int mode)
{
	volatile u8 status_reg;

	(*buf) = ci_cam_rd_data(cidev);

	if (mode != CI_ERR_CHK_MODE_SIMPLE) {
	 	status_reg = ci_cam_rd_status(cidev);
		if (ci_chk_da(status_reg) || !ci_chk_re(status_reg)) {
			ci_set_io_rd_err_code(cidev, CI_IO_ERR_RD_1ST_BYTE);
			LOG_ERROR("HW_IO_Read: IO status error (DA=1 or RE=0), status=0x%02X\n", status_reg);
			return -EFAULT;
		}
	}
	return 0;
}

static int __ci_hw_read_io_data_middle_single(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	volatile u8 status_reg;
	int i;

	/* read middle bytes - original one, byte mode , same as H13, H14, M14Ax */
	for (i = 1; i< (size-1); i++)
	{
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR(ci_is_power_restart(cidev), return -EFAULT, "power_restart detected");

		buf[i] = ci_cam_rd_data(cidev);
		if (mode != CI_ERR_CHK_MODE_SIMPLE)
		{
			status_reg = ci_cam_rd_status(cidev);
			if (!ci_chk_re(status_reg))
			{
				ci_set_io_rd_err_code(cidev, CI_IO_ERR_RD_MIDDLE_RE);
				LOG_ERROR("IO read : IO status error (RE=0)\n");
				LOG_ERROR("          %d'th byte of %d bytes, status reg=0x%02X\n",
						i, size, status_reg);
				return -EFAULT;
			}
		}
	}

	return i;
}

static int _ci_hw_read_io_data_middle(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	return __ci_hw_read_io_data_middle_single(cidev, buf, size, mode);
}

static int _ci_hw_read_io_data_last(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	volatile u8 status_reg;

	(*buf) = ci_cam_rd_data(cidev);

	status_reg = ci_cam_rd_status(cidev);
	if (ci_chk_re(status_reg)) {
		ci_set_io_rd_err_code(cidev, CI_IO_ERR_RD_LAST_RE);
		LOG_ERROR("IO read : IO status error (RE=1)\n");
		LOG_ERROR("          size=%d, status reg=0x%02X\n", size, status_reg);

	#if 1
		return -EFAULT;
	#else
		mdelay(1);
		status_reg = ci_cam_rd_status(cidev);
		if (ci_chk_re(status_reg)) {
			LOG_ERROR("IO read : IO status error(again) (RE=1)\n");
			LOG_ERROR("          size=%d, status reg=0x%02X\n", size, status_reg);
			//
        	LOG_ERROR("/* read the last byte */\n");
	        LOG_ERROR("|Data|Stat|Size  |\n");
	        LOG_ERROR("|0x%02X|0x%02X|0x%04X|\n", pbuf[i], status_reg, size);
			return -EFAULT;
		}
	#endif
	}
	return 0;
}

static int _ci_hw_read_io_data(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	int i;
	int ret;

	_ci_hw_io_time_show_size(cidev, size);

	ret = _ci_hw_read_io_data_first(cidev, &buf[0], mode);
	if (ret != 0) {
		return ret;
	}

	i = _ci_hw_read_io_data_middle(cidev, buf, size, mode);
	if (i < 0) {
		return -EFAULT;
	}

	ret = _ci_hw_read_io_data_last(cidev, &buf[i], size, mode);
	if (ret != 0) {
		return ret;
	}
	return 0;
}

static int _ci_hw_read_io_data_buffer_copy(CI_DEV_T *cidev,
										u8 *rbuf, u8 *pbuf,
										int size, int to_user)
{
	if (to_user) {
		if (!ci_opt_io_time_show(cidev)) {
			LOG_IO_INFO("CI-IO> copy_to_user - addr[0x%p] len[%d]\n", (void *)rbuf, size);
		}
		if (copy_to_user(( void __user * )rbuf, pbuf, size)) {
			LOG_ERROR("CI-IO> copy_to_user <<F>>\n");
			return -EIO;
	    }
	} else {
		if (!ci_opt_io_time_show(cidev)) {
			LOG_IO_INFO("CI-IO> memcpy to rbuf - addr[0x%p] len[%d]\n", (void *)rbuf, size);
		}
		memcpy((void *)rbuf, pbuf, size);
	}
	return 0;
}

static int CheckReadIOStatus(CI_DEV_T *cidev, u8 *rbuf, u32 *rsize)
{
	int idx = cidev->idx;

	if ((rbuf == NULL) || (rsize == NULL)) {
		LOG_ERROR("IO[%d] read : Invalid input param - rbuf[0x%p], rsize[0x%p]\n",
				idx, rbuf, rsize);
		return -EINVAL;
	}

	if (!(*rsize)) {
		LOG_ERROR("IO[%d] read : Invalid input param - (*rsize)[%d]\n",
				idx, (*rsize));
		return -EINVAL;
	}

	if (!ci_nego_buff_size(cidev)) {
		LOG_ERROR("IO[%d] read : Zero nego buff_size\n", idx);
		return -EFAULT;
	}

	if (cidev->io.buf == NULL) {
		LOG_ERROR("IO[%d] read : NULL io_buf\n", idx);
		return -ENOMEM;
	}

	return 0;
}

/**
 * Perform Read from CI Module
 *
 * @brief
 *   core bridge function : Read Command DATA (Host <- CAM)
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   buf :pointer of read data buffer
 *   input_size :pointer of read data size
 * @return
 *  int
 */
int CI_OPS_IO_ReadData(CI_DEV_T *cidev, UINT8* buf, UINT32* input_size)
{
	ktime_t	start_t, data_t, end_t;
	UINT8 *pbuf = NULL, *tbuf = NULL, *io_buf = NULL;
	UINT16 size;
	UINT32 opt_io_mode;
	int	burst_mode = !!ci_opt_burst_mode(cidev);
	int ret = -EFAULT;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR(!buf, return -EFAULT, "buf is NULL");
	CHECK_ERROR(!input_size, return -EFAULT, "size is NULL");

	/* detect & init & nego check */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");
	CHECK_ERROR(!ci_is_cam_nego_done(cidev), return -EFAULT, "[ CAM Nego-Buff not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	mutex_lock(&cidev->access_mutex);
	CHECK_ERROR(!cidev->power_on, goto out, "VCC Power Off");

	opt_io_mode = ci_opt_io_mode(cidev);

	start_t = ktime_get();

	ret = CheckReadIOStatus(cidev, buf, input_size);
	if (ret != 0) {
		goto out;
	}
	io_buf = cidev->io.buf;

	/* Set 1 Byte Mode Default, */
	ci_hw_change_access_mode_byte(cidev, burst_mode);

	ret = _ci_hw_read_io_data_size(cidev, &size);
	if (ret != 0) {
		goto out;
	}

	LOG_DBG3(">>> Input len : %d\n", (*input_size));
	LOG_DBG3(">>> Trans len : %d\n", size);

	if (!(*input_size) || ((*input_size) > size)) {
		(*input_size) = size;
	} else {
		size = (*input_size);
	}

	ret = _ci_hw_io_chk_buff_size(&tbuf, &pbuf, io_buf, size);
	if (ret != 0) {
		LOG_ERROR("IO read : malloc <<F>>\n");
		ret = -ENOMEM;
		goto out;
	}

	data_t = ktime_get();

	ret = _ci_hw_read_io_data(cidev, pbuf, size, opt_io_mode);
	if (ret != 0) {
		goto out_r_fail;
	}

	_ci_hw_io_dbg_buf_print(cidev, pbuf, size, 1);

	ret = _ci_hw_read_io_data_buffer_copy(cidev, buf, pbuf, size, 1); // 1:to_user
	if (ret != 0) {
		goto out_r_fail;
	}

	end_t = ktime_get();

	ci_pcap_mon_io_pkt(cidev, pbuf, size, CI_PCAP_DATA_CAM_TO_HOST);

	ci_free(tbuf);

	ci_dbg_perf_r_data(cidev, start_t, end_t, size);

	_ci_hw_io_time_show_result(cidev, start_t, end_t, size, 1);

	mutex_unlock(&cidev->access_mutex);
	LOG_INFO(">>> Read IO Data <<S>>");
	return 0;

out_r_fail:
	end_t = ktime_get();

	ci_free(tbuf);

	_ci_hw_io_time_show_result(cidev, start_t, end_t, 0, 1);

out:
	mutex_unlock(&cidev->access_mutex);
	LOG_ERROR(">>> Read IO Data <<F>>");
	return ret;
}


static int _ci_hw_write_io_data_size(CI_DEV_T *cidev, u16 size)
{
	int chk_cnt, delay;
	int ret;

	_ci_hw_io_time_show_size(cidev, size);

	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_W_PRE);
	delay = ci_get_delay_param(cidev, DELAY_IO_WRITE_CHECK_DA);
	ret = ci_hw_wr_io_chk_da(cidev, chk_cnt, delay,
							"IO write: IO busy (DA=1)");
	if (ret != 0) {
		ci_set_io_wr_err_code(cidev, CI_IO_ERR_WR_1ST_CHK_DA);
		return -EIO;
	}

	/* set HC=1 */
	ci_cam_wr_cmd(cidev, CI_HC);
	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_W_PRE);
	delay = ci_get_delay_param(cidev, DELAY_IO_WRITE_CHECK_FR);
	ret = ci_hw_wr_io_chk_fr(cidev, chk_cnt, delay, WR_PWR_CHK,
							"IO write: IO status error (FR=0)");
	if (ret != 0) {
		ci_set_io_wr_err_code(cidev, CI_IO_ERR_WR_1ST_CHK_FR);
		return -EFAULT;
	}

	// write the size of data
	ci_cam_wr_size_ls(cidev, (u8)(size&0x00FF));
	ci_cam_wr_size_ms(cidev, (u8)((size>>8)&0x00FF));
	LOG_DBG3(">>> size = 0x%04X\n", size);

	return 0;
}

static int _ci_hw_write_io_data_first(CI_DEV_T *cidev, u8 *buf, int mode)
{
	int chk_cnt, delay;
	int ret;

	// write the first byte
	ci_cam_wr_data(cidev, (*buf));
	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_W);
	delay = ci_get_delay_param(cidev, DELAY_IO_WRITE_1ST_BYTE_STAT_RD_FR_WE);
	ret = ci_hw_wr_io_chk_1st(cidev, chk_cnt, delay, mode,
							"IO write: IO status error (FR=1 or WE=0)");
	if (ret != 0) {
		ci_set_io_wr_err_code(cidev, CI_IO_ERR_WR_1ST_BYTE);
		return ret;
	}

	return 0;
}

static int __ci_hw_write_io_data_middle_single(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	int	chk_cnt, delay;
	char *msg;
	int i;
	int ret = 0;

	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_W);
	delay = ci_get_delay_param(cidev, DELAY_IO_WRITE_MIDDLE_BYTE_CHECK_WE);
	msg = "IO write : IO status error (WE=0)";

	/* write middle bytes - original one, byte mode , H13, H14, M14Ax */
	for (i = 1; i < (size-1); i++)
	{
		ci_cam_wr_data(cidev, buf[i]);

		ret = ci_hw_wr_io_chk_we(cidev, chk_cnt, delay,
								mode, WR_DATA_MIDDLE, msg);
		if (ret != 0)
		{
			ci_set_io_wr_err_code(cidev, CI_IO_ERR_WR_MIDDLE_WE);
			return ret;
		}
	}

	return i;
}

static int _ci_hw_write_io_data_middle(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	return __ci_hw_write_io_data_middle_single(cidev, buf, size, mode);
}

static int _ci_hw_write_io_data_last(CI_DEV_T *cidev, u8 *buf, int mode)
{
	char *msg;
	int chk_cnt, delay;
	int ret;

	/* write the last byte */
	ci_cam_wr_data(cidev, (*buf));
	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_W);
	delay = ci_get_delay_param(cidev, DELAY_IO_WRITE_LAST_BYTE_CHECK_WE);
	msg = "IO write : IO status error (WE=1)";
	ret = ci_hw_wr_io_chk_we(cidev, chk_cnt, delay,
							mode, WR_DATA_LAST, msg);
	if (ret != 0) {
		ci_set_io_wr_err_code(cidev, CI_IO_ERR_WR_LAST_WE);
		return ret;
	}

	ci_cam_wr_cmd(cidev, 0x00);
	return 0;
}

static int _ci_hw_write_io_data(CI_DEV_T *cidev, u8 *buf, u32 size, int mode)
{
	int i;
	int ret;

	ret = _ci_hw_write_io_data_first(cidev, &buf[0], mode);
	if (ret != 0) {
		return ret;
	}

	i = _ci_hw_write_io_data_middle(cidev, buf, size, mode);
	if (i < 0) {
		return -EFAULT;
	}

	ret = _ci_hw_write_io_data_last(cidev, &buf[i], mode);
	if (ret != 0) {
		return ret;
	}
	return 0;
}

static int _ci_hw_write_io_data_buffer_copy(CI_DEV_T *cidev,
										u8 *wbuf, u8 *pbuf,
										int size, int from_user)
{
	if (from_user) {
		if (!ci_opt_io_time_show(cidev)) {
			LOG_IO_INFO("CI-IO> copy_from_user - addr[0x%p] len[%d]\n", (void *)wbuf, size);
		}
		if (copy_from_user(pbuf, ( void __user * )wbuf, size)) {
			LOG_ERROR("CI-IO> copy_from_user <<F>>\n");
			return -EIO;
	    }
	} else {
		if (!ci_opt_io_time_show(cidev)) {
			LOG_IO_INFO("CI-IO> memcpy from wbuf - addr[0x%p] len[%d]\n", (void *)wbuf, size);
		}
		memcpy((void *)pbuf, (void *)wbuf, size);
	}
	return 0;
}

static int CheckWriteIOStatus(CI_DEV_T *cidev, u8 *wbuf, u32 wsize)
{
	int idx = cidev->idx;

	if ((wbuf == NULL) || !wsize) {
		LOG_ERROR("IO[%d] write : Invalid input param - wbuf[0x%p], wsize[%d]\n",
				idx, wbuf, wsize);
		return -EINVAL;
	}

	if (!ci_nego_buff_size(cidev)) {
		LOG_ERROR("IO[%d] write : Zero nego buff_size\n", idx);
		return -EFAULT;
	}

	if (cidev->io.buf == NULL) {
		LOG_ERROR("IO[%d] write : NULL io_buf\n", idx);
		return -ENOMEM;
	}

	return 0;
}

/**
 * Perform Write to CI Module
 * @brief
 *   core bridge function : Write Command DATA (Host -> CAM)
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   wbuf :pointer of write data buffer
 *   wsize :wad data size
 * @return
 *  int
 */
int CI_OPS_IO_WriteData(CI_DEV_T *cidev, UINT8 *wbuf, UINT32 wsize)
{
	ktime_t	start_t, data_t, end_t;
	UINT8 *pbuf = NULL, *tbuf = NULL, *io_buf = NULL;
	UINT16 size = wsize;
	UINT32	opt_io_mode;
	int	burst_mode = !!ci_opt_burst_mode(cidev);
	int ret = -EFAULT;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");
	CHECK_ERROR(!wbuf, return -EFAULT, "buf is NULL");
	CHECK_ERROR(!wsize, return -EFAULT, "size is zero");

	/* detect & init & nego check */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");
	CHECK_ERROR(!ci_is_cam_nego_done(cidev), return -EFAULT, "[ CAM Nego-Buff not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_IO, (POD_MODE | IO_INT_MODE));

	mutex_lock(&cidev->access_mutex);
	CHECK_ERROR(!cidev->power_on, goto out, "VCC Power Off");

	opt_io_mode = ci_opt_io_mode(cidev);

	start_t = ktime_get();

	ret = CheckWriteIOStatus(cidev, wbuf, wsize);
	if (ret != 0) {
		goto out;
	}
	io_buf = cidev->io.buf;

	LOG_DBG3(">>> Trans len : %d\n", size);

	ret = _ci_hw_io_chk_buff_size(&tbuf, &pbuf, io_buf, size);
	if (ret != 0) {
		LOG_ERROR("IO write : malloc <<F>>\n");
		ret = -ENOMEM;
		goto out;
	}

	ret = _ci_hw_write_io_data_buffer_copy(cidev, wbuf, pbuf, size, 1); // 1:from_user
	if (ret !=0) {
		goto out_w_fail_before_cmd;
	//	goto out_w_fail;
	}

	_ci_hw_io_dbg_buf_print(cidev, pbuf, size, 0);

	/* Set 1 Byte Mode Default, */
	ci_hw_change_access_mode_byte(cidev, burst_mode);

	ret = _ci_hw_write_io_data_size(cidev, size);
	if (ret != 0) {
		if (ret == -EIO) {
			goto out_w_fail_before_cmd;
		}
		goto out_w_fail;
	}

	data_t = ktime_get();

	ret = _ci_hw_write_io_data(cidev, pbuf, size, opt_io_mode);
	if (ret != 0) {
		goto out_w_fail;
	}

	end_t = ktime_get();

	ci_pcap_mon_io_pkt(cidev, pbuf, size, CI_PCAP_DATA_HOST_TO_CAM);

	ci_free(tbuf);

	ci_dbg_perf_w_data(cidev, start_t, end_t, size);

	_ci_hw_io_time_show_result(cidev, start_t, end_t, size, 1);

	mutex_unlock(&cidev->access_mutex);
	LOG_INFO("Write IO Data <<S>>");
	return 0;

out_w_fail:
	ci_cam_wr_cmd(cidev, 0x00);

out_w_fail_before_cmd:
	end_t = ktime_get();

	ci_free(tbuf);

	_ci_hw_io_time_show_result(cidev, start_t, end_t, 0, 1);

out:
	mutex_unlock(&cidev->access_mutex);
	LOG_ERROR("Write IO Data <<F>>");
	return ret;
}

