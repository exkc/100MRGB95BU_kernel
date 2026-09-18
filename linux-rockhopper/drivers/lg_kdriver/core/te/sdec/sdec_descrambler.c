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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>
#include <lg1k/te/mem.h>

#include "sdec_impl.h"

#define DATA_RETURN_TIMEOUT	500
#define DSC_SENDDATA_NUM	2

static DEFINE_MUTEX(dsc_mutex);

static int convert_cas_type(LX_SDEC_CAS_TYPE_T cas_type)
{
	switch (cas_type) {
	case LX_SDEC_BYPASS:
		return IPC_DSC_CAS_BYPASS;
	case LX_SDEC_DES:
		return IPC_DSC_CAS_DES;
	case LX_SDEC_TDES:
		return IPC_DSC_CAS_TDES;
	case LX_SDEC_AES:
		return IPC_DSC_CAS_AES;
	case LX_SDEC_CSA:
		return IPC_DSC_CAS_DVB_CSA;
	case LX_SDEC_MULTI2:
		return IPC_DSC_CAS_MULTI2;
	default:
		return -1;
	}
}

static int convert_block_mode(LX_SDEC_BLK_MODE_T blk_mode)
{
	switch (blk_mode) {
	case LX_SDEC_ECB:
		return IPC_DSC_BLOCK_ECB;
	case LX_SDEC_CBC:
		return IPC_DSC_BLOCK_CBC;
	default:
		return -1;
	}
}

static int convert_res_mode(LX_SDEC_RES_MODE_T res_mode)
{
	switch (res_mode) {
	case LX_SDEC_CLEAR:
		return IPC_DSC_RES_CLEAR;
	case LX_SDEC_CTS:
		return IPC_DSC_RES_CTS;
	case LX_SDEC_OFB:
		return IPC_DSC_RES_OFB;
	case LX_SDEC_SCTE52_2008:
	case LX_SDEC_CTSOC:
	default:
		return -1;
	}
}

static int convert_key_size(LX_SDEC_KEY_SIZE_T key_size)
{
	switch (key_size) {
	case LX_SDEC_KEY_64BIT:
		return IPC_DSC_KEY_SIZE_64BIT;
	case LX_SDEC_KEY_128BIT:
		return IPC_DSC_KEY_SIZE_128BIT;
	case LX_SDEC_KEY_192BIT:
		return IPC_DSC_KEY_SIZE_192BIT;
	case LX_SDEC_KEY_256BIT:
		return IPC_DSC_KEY_SIZE_256BIT;
	default:
		return -1;
	}
}

static int convert_desc_mode(LX_SDEC_DESC_MODE_T mode)
{
	switch (mode) {
	case LX_SDEC_DESC_MODE_CHANNEL:
		return IPC_DSC_ALGO_MODE_CH;
	case LX_SDEC_DESC_MODE_PID:
		return IPC_DSC_ALGO_MODE_PID;
	case LX_SDEC_DESC_MODE_CHANNEL_PID:
		return IPC_DSC_ALGO_MODE_CH_PID;
	default:
		return -1;
	}
}

static IPC_DSC_KEY_MODE_TYPE_T convert_pid_mode(LX_SDEC_DESC_PID_MODE_T mode)
{
	switch (mode) {
	case LX_SDEC_DESC_PID_ENABLE:
		return IPC_DSC_KEY_MODE_PID_SET;
	case LX_SDEC_DESC_PID_DISABLE:
		return IPC_DSC_KEY_MODE_PID_CANCEL;
	case LX_SDEC_DESC_PID_CLEAR:
		return IPC_DSC_KEY_MODE_PID_CANCEL;
	default:
		return IPC_DSC_KEY_MODE_MAX;
	}
}

static IPC_DSC_CAS_MODE_T convert_cas_mode(enum lx_sdec_desc_cas_mode mode)
{
	switch (mode) {
	case LX_SDEC_DESC_CAS_NORMAL:
		return IPC_DSC_CAS_MODE_NORMAL;
	case LX_SDEC_DESC_CAS_ECP:
		return IPC_DSC_CAS_MODE_ECP;
	case LX_SDEC_DESC_CAS_XCAS:
		return IPC_DSC_CAS_MODE_XCAS;
	case LX_SDEC_DESC_CAS_NAGRA:
		return IPC_DSC_CAS_MODE_NAGRA;
	default:
		return IPC_DSC_CAS_MODE_MAX;
	}
}

static const char *desc_mode_str(LX_SDEC_DESC_MODE_T desc)
{
	switch (desc) {
	case LX_SDEC_DESC_MODE_CHANNEL:
		return "CH";
	case LX_SDEC_DESC_MODE_PID:
		return "PID";
	case LX_SDEC_DESC_MODE_CHANNEL_PID:
		return "CH_PID";
	default:
		return "Invalid";
	}
}

static const char *cas_type_str(LX_SDEC_CAS_TYPE_T cas)
{
	switch (cas) {
	case LX_SDEC_BYPASS:
		return "BYPASS";
	case LX_SDEC_DES:
		return "DES";
	case LX_SDEC_TDES:
		return "TDES";
	case LX_SDEC_AES:
		return "AES";
	case LX_SDEC_CSA:
		return "CSA";
	case LX_SDEC_MULTI2:
		return "MULTI2";
	default:
		return "Invalid";
	}
}

static const char *block_mode_str(LX_SDEC_BLK_MODE_T blk)
{
	switch (blk) {
	case LX_SDEC_ECB:
		return "ECB";
	case LX_SDEC_CBC:
		return "CBC";
	default:
		return "Invalid";
	}
}

static const char *res_mode_str(LX_SDEC_RES_MODE_T res)
{
	switch (res) {
	case LX_SDEC_CLEAR:
		return "CLEAR";
	case LX_SDEC_CTS:
		return "CTS";
	case LX_SDEC_OFB:
		return "OFB";
	case LX_SDEC_SCTE52_2008:
		return "SCTE52";
	case LX_SDEC_CTSOC:
		return "CTSOC";
	default:
		return "Invalid";
	}
}

static const char *key_size_str(LX_SDEC_KEY_SIZE_T size)
{
	switch (size) {
	case LX_SDEC_KEY_64BIT:
		return "64bit";
	case LX_SDEC_KEY_128BIT:
		return "128bit";
	case LX_SDEC_KEY_192BIT:
		return "192bit";
	case LX_SDEC_KEY_256BIT:
		return "256bit";
	default:
		return "Invalid";
	}
}

static const char *key_type_str(LX_SDEC_DESC_KEY_TYPE_T key_type)
{
	switch (key_type) {
	case LX_SDEC_KEY_TYPE_EVEN:
		return "EVEN";
	case LX_SDEC_KEY_TYPE_ODD:
		return "ODD";
	case LX_SDEC_KEY_TYPE_ODD_IV:
		return "ODD_IV";
	case LX_SDEC_KEY_TYPE_EVEN_IV:
		return "EVEN_IV";
	case LX_SDEC_KEY_TYPE_MULTI2:
		return "MULTI2";
	default:
		return "Invalid";
	}
}

static int set_descrambler(struct sdec_channel *channel, struct sdec_desc *desc)
{
	IPC_MSG_DSC_ALGO_T ipc_dsc = {0};
	LX_SDEC_DESC_CONFIG_T *cfg = &desc->cfg;
	int ret, v;

	ipc_dsc.ch = channel->num;

	v = convert_desc_mode(cfg->desc_mode);
	CHECK_PARAM(v < 0, "invalid mode(%d)", cfg->desc_mode);
	ipc_dsc.mode = v;

	v = convert_cas_type(cfg->cas_type);
	CHECK_PARAM(v < 0, "invalid cas_type(%d)\n", cfg->cas_type);
	ipc_dsc.cas_type = v;

	v = convert_block_mode(cfg->blk_mode);
	CHECK_PARAM(v < 0, "invalid block_mode(%d)\n", cfg->blk_mode);
	ipc_dsc.block_type = v;

	v = convert_res_mode(cfg->res_mode);
	CHECK_PARAM(v < 0, "invalid res_mode(%d)\n", cfg->res_mode);
	ipc_dsc.res_type = v;

	v = convert_key_size(cfg->key_size);
	CHECK_PARAM(v < 0, "invalid key_size(%d)\n", cfg->key_size);
	ipc_dsc.key_size = v;

	ipc_dsc.cas_mode = convert_cas_mode(cfg->cas_mode);
	CHECK_PARAM(ipc_dsc.cas_mode == IPC_DSC_CAS_MODE_MAX,
		    "invalid cas mode (%u)\n", cfg->cas_mode);

	ret = TE_IPC_SetCipherMode(&ipc_dsc);
	if (ret) {
		log_error("Error(%d) in TE_IPC_SetCipherMode"
			  "(ch=%d,mode=%d,cas=%d,block=%d,res=%d,size=%d)\n",
			  ret, ipc_dsc.ch, ipc_dsc.mode, ipc_dsc.cas_type,
			  ipc_dsc.block_type, ipc_dsc.res_type,
			  ipc_dsc.key_size);
		return ret;
	}

	return 0;
}

static int set_key(struct sdec_channel *channel, LX_SDEC_DESC_KEY_T *param)
{
	struct sdec_desc *desc;
	LX_SDEC_DESC_CONFIG_T *cfg;
	IPC_MSG_DSC_KEY_T ipc_dsc;
	int i, ret;

	CHECK_PARAM(param->size == 0 || param->size > 32 || (param->size % 4),
		    "invalid key size(%d)", param->size);

	desc = &channel->desc;
	cfg = &desc->cfg;

	if (cfg->cas_type == LX_SDEC_BYPASS) {
		log_error("Can't set descrambler key in bypass mode");
		return -EINVAL;
	}

	memset(&ipc_dsc, 0, sizeof(ipc_dsc));

	ipc_dsc.ch = channel->num;

	if (cfg->desc_mode == LX_SDEC_DESC_MODE_CHANNEL ||
	    cfg->desc_mode == LX_SDEC_DESC_MODE_CHANNEL_PID) {
		ipc_dsc.mode = IPC_DSC_KEY_MODE_CH;
	} else if (cfg->desc_mode == LX_SDEC_DESC_MODE_PID) {
		if (param->pidf_id == LX_SDEC_ALL_PID_FILTER) {
			ipc_dsc.mode = IPC_DSC_KEY_MODE_CH;
		} else {
			CHECK_PARAM(param->pid >= 0x1fff, "invalid pid(0x%x)\n",
				    param->pid);

			ipc_dsc.mode = IPC_DSC_KEY_MODE_PID_SET;
			ipc_dsc.pid = param->pid;
		}
	} else {
		log_error("invalid mode(%d)", cfg->desc_mode);
		return -EINVAL;
	}


	switch (param->type) {
	case LX_SDEC_KEY_TYPE_EVEN:
		if (cfg->cas_type == LX_SDEC_MULTI2)
			ipc_dsc.key_type = IPC_DSC_KEY_TYPE_MULTI2_DKEY;
		else
			ipc_dsc.key_type = IPC_DSC_KEY_TYPE_KEY;

		ipc_dsc.attribute = IPC_DSC_KEY_ATTR_EVEN;
		break;

	case LX_SDEC_KEY_TYPE_ODD:
		if (cfg->cas_type == LX_SDEC_MULTI2)
			ipc_dsc.key_type = IPC_DSC_KEY_TYPE_MULTI2_DKEY;
		else
			ipc_dsc.key_type = IPC_DSC_KEY_TYPE_KEY;

		ipc_dsc.attribute = IPC_DSC_KEY_ATTR_ODD;
		break;

	case LX_SDEC_KEY_TYPE_EVEN_IV:
		if (cfg->cas_type == LX_SDEC_MULTI2)
			ipc_dsc.attribute = IPC_DSC_KEY_ATTR_MULTI2_IV;
		else
			ipc_dsc.attribute = IPC_DSC_KEY_ATTR_EVEN;

		ipc_dsc.key_type = IPC_DSC_KEY_TYPE_IV;
		if (param->location == LX_SDEC_KEY_FROM_MSG) {
			desc->even_iv.used = 1;
			desc->even_iv.pid = param->pid;
			desc->even_iv.pidf_id = param->pidf_id;
			memcpy(desc->even_iv.data, param->key, param->size);
		} else {
			desc->even_iv.used = 0;
		}
		desc->even_iv.loc = param->location;
		break;

	case LX_SDEC_KEY_TYPE_ODD_IV:
		if (cfg->cas_type == LX_SDEC_MULTI2)
			ipc_dsc.attribute = IPC_DSC_KEY_ATTR_MULTI2_IV;
		else
			ipc_dsc.attribute = IPC_DSC_KEY_ATTR_ODD;

		ipc_dsc.key_type = IPC_DSC_KEY_TYPE_IV;
		if (param->location == LX_SDEC_KEY_FROM_MSG) {
			desc->odd_iv.used = 1;
			desc->odd_iv.pid = param->pid;
			desc->odd_iv.pidf_id = param->pidf_id;
			memcpy(desc->odd_iv.data, param->key, param->size);
		} else {
			desc->odd_iv.used = 0;
		}
		desc->odd_iv.loc = param->location;
		break;

	case LX_SDEC_KEY_TYPE_MULTI2:
		/* key_type will be ignored in fw */
		ipc_dsc.key_type = IPC_DSC_KEY_TYPE_KEY;
		ipc_dsc.attribute = IPC_DSC_KEY_ATTR_MULTI2_SKEY;
		if (param->location == LX_SDEC_KEY_FROM_MSG) {
			desc->skey.used = 1;
			desc->skey.pid = param->pid;
			desc->skey.pidf_id = param->pidf_id;
			memcpy(desc->skey.data, param->key, param->size);
		} else {
			desc->skey.used = 0;
		}
		desc->skey.loc = param->location;
		break;

	default:
		log_error("invalid key_type(%d)\n", param->type);
		return -EINVAL;
	}

	if (param->location == LX_SDEC_KEY_FROM_MSG) {
		ipc_dsc.op_mode = IPC_DSC_KEY_OP_MODE_NORMAL;
		for (i = 0; i < param->size / 4; i++)
			ipc_dsc.data[i] = TE_GET32(&param->key[i * 4]);	/* swap key data for H/W */

		ret = TE_IPC_SetCipherKey(&ipc_dsc);
		if (ret) {
			log_error("Error(%d) in TE_IPC_SetCipherKey"
				  "(ch=%d,mode=%d,attr=%d,type=%d,pid=0x%x)\n",
				  ret, ipc_dsc.ch, ipc_dsc.mode,
				  ipc_dsc.attribute, ipc_dsc.key_type,
				  ipc_dsc.pid);
			return ret;
		}
	} else { // LX_SDEC_KEY_FROM_MEM
		log_error("Not supported indirect key mode");
		return -EINVAL;
	}

	return 0;
}

static void register_send_data(struct sdec_dev_senddata *e, void *data)
{
	unsigned long flag;
	spin_lock_irqsave(&e->spinlock, flag);
	e->data = data;
	spin_unlock_irqrestore(&e->spinlock, flag);
}

static void unregister_send_data(struct sdec_dev_senddata *e)
{
	unsigned long flag;
	spin_lock_irqsave(&e->spinlock, flag);
	e->data = NULL;
	spin_unlock_irqrestore(&e->spinlock, flag);
}

/* send data -> requires return data */
static int set_senddata(struct sdec_channel *channel,
		        enum lx_sdec_cas_type cas_type,
		        enum lx_sdec_desc_key_type key_type,
		        void *data,
			bool is_dsc)
{
	struct sdec_dev_senddata *e = &channel->dev->dsc_senddata;
	IPC_MSG_DSC_SEND_DATA_T ipc;
	int rc;

	if (!data)
		return -EFAULT;

	register_send_data(e, data);

	ipc.ch = channel->num;
	if (is_dsc) {
		ipc.data_type = IPC_DSC_SENDTYPE_KEY;
		if (cas_type == LX_SDEC_AES)
			ipc.cas_type = IPC_DSC_CAS_AES;
		else
			ipc.cas_type = IPC_DSC_CAS_DES;
		if (key_type == LX_SDEC_KEY_TYPE_EVEN)
			ipc.attribute = IPC_DSC_KEY_ATTR_EVEN;
		else
			ipc.attribute = IPC_DSC_KEY_ATTR_ODD;
	} else {
		ipc.data_type = IPC_DSC_SENDTYPE_PVR;
	}

	memcpy(ipc.data, data, IPC_SEND_DATA_MSG_SIZE);
	reinit_completion(&e->completion);

	/* Send an IPC message and wait until the response is coming */
	rc = te_ipc_send_dsc_data(&ipc);
	if (rc)
		goto error;

	rc = wait_for_completion_timeout(&e->completion,
					 msecs_to_jiffies(DATA_RETURN_TIMEOUT));
	if (rc <= 0) {
		log_error("fatal error, timeout occured");
		rc = -ETIME;
		goto error;
	}

	rc = 0;
error:
	unregister_send_data(e);
	return rc;
}

static int set_xcas_senddata(struct sdec_channel *channel,
			     struct sdec_send_noti_param *param)
{
	struct sdec_dev_senddata *e = &channel->dev->dsc_senddata;
	IPC_MSG_DSC_XCAS_DATA_T ipc;
	int rc;
	size_t len = param->len;

	if (len > IPC_SEND_DATA_XCAS_MSG_SIZE)
		len = IPC_SEND_DATA_XCAS_MSG_SIZE;

	register_send_data(e, param->data);

	ipc.ch = channel->num;

	if (param->command_type == SDEC_SEND_TYPE_KEY) {
		ipc.pid = param->pid;
		ipc.data_type = IPC_DSC_SENDTYPE_KEY;

		if (param->cas == LX_SDEC_AES)
			ipc.cas_type = IPC_DSC_CAS_AES;
		else
			ipc.cas_type = IPC_DSC_CAS_DVB_CSA;
		if (param->key == LX_SDEC_KEY_TYPE_EVEN)
			ipc.attribute = IPC_DSC_KEY_ATTR_EVEN;
		else
			ipc.attribute = IPC_DSC_KEY_ATTR_ODD;
	} else if (param->command_type == SDEC_SEND_TYPE_PVR_PES) {
		ipc.data_type = IPC_DSC_SENDTYPE_PVR;
	} else {
		log_error("invalid command type:%d", param->command_type);
		rc = -EINVAL;
		goto error;
	}

	memcpy(ipc.data, param->data, len);
	reinit_completion(&e->completion);

	/* Send an IPC message and wait until the response is coming */
	rc = te_ipc_send_xcas_data(&ipc);
	if (rc)
		goto error;

	rc = wait_for_completion_timeout(&e->completion,
					 msecs_to_jiffies(DATA_RETURN_TIMEOUT));
	if (rc <= 0) {
		log_error("fatal error, timeout occured");
		rc = -ETIME;
		goto error;
	}
	rc = 0;
	param->len = e->size;
error:
	unregister_send_data(e);
	return rc;
}

static int get_key_size(struct sdec_desc *desc, LX_SDEC_DESC_KEY_TYPE_T type)
{
	LX_SDEC_DESC_CONFIG_T *cfg = &desc->cfg;
	int size;

	switch (cfg->cas_type) {
	case LX_SDEC_DES:
		if (type == LX_SDEC_KEY_TYPE_EVEN
		    || type == LX_SDEC_KEY_TYPE_ODD
		    || type == LX_SDEC_CIPHER_KEY_EVEN_IV
		    || type == LX_SDEC_KEY_TYPE_ODD_IV)
			size = 8;
		else
			size = 0;
		break;

	case LX_SDEC_TDES:
		if (type == LX_SDEC_KEY_TYPE_EVEN
		    || type == LX_SDEC_KEY_TYPE_ODD)
			size = 24;
		else if (type == LX_SDEC_CIPHER_KEY_EVEN_IV ||
			 type == LX_SDEC_KEY_TYPE_ODD_IV)
			size = 8;
		else
			size = 0;
		break;

	case LX_SDEC_AES:
		if (cfg->key_size == LX_SDEC_KEY_128BIT)
			size = 16;
		else if (cfg->key_size == LX_SDEC_KEY_256BIT)
			size = 32;
		else
			size = 0;
		break;

	case LX_SDEC_MULTI2:
		if (type == LX_SDEC_KEY_TYPE_MULTI2)
			size = 32;
		else if (type == LX_SDEC_KEY_TYPE_EVEN
			 || type == LX_SDEC_KEY_TYPE_ODD
			 || type == LX_SDEC_CIPHER_KEY_EVEN_IV
			 || type == LX_SDEC_KEY_TYPE_ODD_IV)
			size = 8;
		else
			size = 0;
		break;

	default:
		size = 0;
		break;
	}

	return size;
}

static int desc_recovery(struct sdec_device *dev)
{
	struct sdec_channel *channel;
	struct sdec_desc *desc;
	LX_SDEC_DESC_CONFIG_T *cfg;
	LX_SDEC_DESC_KEY_T param;
	int i, ret;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		desc = &channel->desc;
		cfg = &desc->cfg;

		if (cfg->cas_type == LX_SDEC_BYPASS)
			continue;

		ret = set_descrambler(channel, desc);
		CHECK_ERROR(ret < 0, return ret, "Error in set_descrambler");

		if (cfg->cas_type == LX_SDEC_MULTI2 && desc->skey.used) {
			/* for arib recovery */
			param.type = LX_SDEC_KEY_TYPE_MULTI2;
			param.size = get_key_size(desc, param.type);

			param.pidf_id = LX_SDEC_ALL_PID_FILTER;
			memcpy(param.key, desc->skey.data, param.size);
			param.location = desc->skey.loc;
			ret = set_key(channel, &param);
			CHECK_ERROR(ret < 0, return ret, "Error in set_key");
		}

		if (cfg->blk_mode == LX_SDEC_CBC) {
			if (desc->even_iv.used) {
				/* even iv */
				param.type = LX_SDEC_KEY_TYPE_EVEN_IV;
				param.size = get_key_size(desc, param.type);
				param.pid = desc->even_iv.pid;
				param.pidf_id = desc->even_iv.pidf_id;
				memcpy(param.key, desc->even_iv.data,
				       param.size);
				param.location = desc->even_iv.loc;

				ret = set_key(channel, &param);
				CHECK_ERROR(ret < 0, return ret,
					    "Error in set_key");
			}

			if (desc->odd_iv.used) {
				/* odd iv */
				param.type = LX_SDEC_KEY_TYPE_ODD_IV;
				param.size = get_key_size(desc, param.type);
				param.pid = desc->odd_iv.pid;
				param.pidf_id = desc->odd_iv.pidf_id;
				memcpy(param.key, desc->odd_iv.data,
				       param.size);
				param.location = desc->odd_iv.loc;

				ret = set_key(channel, &param);
				CHECK_ERROR(ret < 0, return ret,
					    "Error in set_key");
			}
		}
	}

	return 0;
}

static int mcu_recovery_desc_pre_callback(void *arg)
{
	mutex_lock(&dsc_mutex);

	return 0;
}

static int mcu_recovery_desc_post_callback(void *arg)
{
	int ret;
	struct sdec_device *dev = arg;

	ret = desc_recovery(dev);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int init_descrambler(struct sdec_channel *channel,
			    struct lx_sdec_desc_config *param)
{
	struct sdec_desc desc;
	int rc;

	log_desc("ch:%d, mode:%s, algo: %s_%s_%s, key_size:%s", channel->num,
		 desc_mode_str(param->desc_mode), cas_type_str(param->cas_type),
		 block_mode_str(param->blk_mode), res_mode_str(param->res_mode),
		 key_size_str(param->key_size));

	memset(&desc, 0, sizeof(desc));
	desc.cfg = *param;

	rc = set_descrambler(channel, &desc);
	CHECK_ERROR(rc < 0, return rc, "Error in InitDescrambler");

	channel->desc = desc;

	return 0;
}

int sdec_init_descrambler(struct sdec_channel *channel,
			  struct lx_sdec_desc_config *cfg)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = init_descrambler(channel, cfg);
	mutex_unlock(&dsc_mutex);

	return ret;
}

int sdec_set_descrambler_key(struct sdec_channel *channel,
			     struct lx_sdec_desc_key *param)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = set_key(channel, param);
	mutex_unlock(&dsc_mutex);

	return ret;
}


/**
 * Initialize the specified channel descrambler
 *
 * @param	ch_ctrl	[in	] handle for sdec channel
 * @param	arg		[in	] LX_SDEC_DESC_CONFIG_T
 * @return	if succeeded - 0, else - errno.
 * @see SDEC_IOC_DESC_INIT
 */
static int ioc_init_descrambler(struct sdec_fh *fh, void *arg)
{
	struct sdec_channel *channel = fh->channel;
	LX_SDEC_DESC_CONFIG_T *param = arg;

	return init_descrambler(channel, param);
}

/**
 * Set descrambler key
 *
 * @param	ch_ctrl	[in	] handle for sdec channel
 * @param	arg		[in	]
 * @return	if succeeded - 0, else - errno.
 * @see
 */

static int ioc_set_descrambler_key(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_channel *channel = fh->channel;
	LX_SDEC_DESC_KEY_T *param = arg;

	log_desc("type(%s), size(%d)", key_type_str(param->type), param->size);

	ret = set_key(channel, param);
	CHECK_ERROR(ret < 0, return ret, "Error in set_key");

	return 0;
}

static int set_descrambler_pid(struct sdec_channel *channel,
			       struct lx_sdec_desc_pid *param)
{
	int ret;
	LX_SDEC_DESC_MODE_T desc_mode;
	IPC_MSG_DSC_KEY_T key;

	CHECK_PARAM(param->pid >= 0x1fff, "invalid pid(0x%x)\n", param->pid);

	log_desc("%s(ch:%d,pid:0x%x,enable:%d)", __func__, channel->num,
		 param->pid, param->mode);

	desc_mode = channel->desc.cfg.desc_mode;

	/* Error Check */
	if (desc_mode == LX_SDEC_DESC_MODE_PID) {
		if (param->mode == LX_SDEC_DESC_PID_ENABLE) {
			log_error("not allowed PID mode to set here");
			return -EINVAL;
		}
	} else if (desc_mode == LX_SDEC_DESC_MODE_CHANNEL) {
		log_error("Channel mode not allowed");
		return -EINVAL;
	}

	memset(&key, 0, sizeof(key));	/* clear param */

	key.ch = channel->num;
	key.mode = convert_pid_mode(param->mode);
	key.pid = param->pid;
	key.op_mode = IPC_DSC_KEY_OP_MODE_NORMAL;

	ret = TE_IPC_SetCipherKey(&key);
	CHECK_ERROR(ret < 0, return ret,
		    "Error(%d) in TE_IPC_SetCipherKey(ch=%d,mode=%d,attr=%d,type=%d,pid=0x%x)",
		    ret, key.ch, key.mode, key.attribute, key.key_type,
		    key.pid);

	return 0;
}

/**
 * Set descrambler pid
 *
 * @param	ch_ctrl	[in	] handle for sdec channel
 * @param	arg		[in	]
 * @return	if succeeded - 0, else - errno.
 * @see
 */

static int ioc_set_descrambler_pid(struct sdec_fh *fh, void *arg)
{
	LX_SDEC_DESC_PID_T *param = arg;
	struct sdec_channel *channel = fh->channel;

	return set_descrambler_pid(channel, param);
}

int sdec_set_descrambler_pid(struct sdec_channel *channel,
			     struct lx_sdec_desc_pid *param)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = set_descrambler_pid(channel, param);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int ioc_set_ecp_key(struct sdec_fh *fh, void *arg)
{
	log_error("Not Supported anymore");

	return 0; //by HE request
}

int sdec_desc_noti_data_info(struct sdec_channel *channel,
			     enum lx_sdec_cas_type cas_type,
			     enum lx_sdec_desc_key_type key_type,
			     void *data,
			     bool is_dsc)
{
	int ret;
	void *d;

#ifdef USE_FIXEDMEM_STATUS
	d = dev->pmem;
#else
	d = data;
#endif

	mutex_lock(&dsc_mutex);
	ret = set_senddata(channel, cas_type, key_type, d, is_dsc);
	mutex_unlock(&dsc_mutex);

	return ret;
}

int sdec_desc_noti_xcas_data(struct sdec_channel *channel,
			     struct sdec_send_noti_param *param)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = set_xcas_senddata(channel, param);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int cancel_xcas_pid(struct sdec_channel *channel, u16 pid)
{
	IPC_MSG_DSC_XCAS_CANCEL_T ipc;
	int rc;

	ipc.ch = channel->num;
	ipc.pid = pid;

	rc = te_ipc_cancel_xcas_pid(&ipc);
	if (rc) {
		log_error("error in te_ipc_cancel_xcas_pid %d, 0x%02x", rc,
			  pid);
		return rc;
	}

	return 0;
}

int sdec_desc_cancel_xcas_pid(struct sdec_channel *channel, u16 pid)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = cancel_xcas_pid(channel, pid);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int set_nagra_key(struct sdec_channel *channel,
			 struct sdec_desc_nagra_key_param *param)
{
	IPC_MSG_DSC_NAGRA_KMSG_T msg;
	int ret, v;
	u8 len;

	v = convert_desc_mode(param->desc_mode);
	CHECK_PARAM(v < 0, "invalid mode(%d)", param->desc_mode);

	msg.algo_mode = v;
	msg.ch = channel->num;
	msg.pid = param->pid;
	msg.attribute = (param->key_type == LX_SDEC_KEY_TYPE_EVEN) ?
			 IPC_DSC_KEY_ATTR_EVEN : IPC_DSC_KEY_ATTR_ODD;
	msg.key_len = param->key_len;
	msg.iv_len = param->iv_len;
	msg.key_encrypted = (param->key_encrypted) ? 1 : 0;
	msg.iv_encrypted = (param->iv_encrypted) ? 1 : 0;
	if (param->key_len) {
		len = (param->key_encrypted) ? 32 : param->key_len;
		memcpy(msg.data, param->data, len);
	}
	if (param->iv && param->iv_len) {
		len = (param->iv_encrypted) ? 32 : param->iv_len;
		memcpy(msg.iv, param->iv, len);
	}
	if (param->key_encrypted || param->iv_encrypted)
		memcpy(msg.comm_iv, param->comm_iv, 16);

	ret = te_ipc_set_nagra_key(&msg);
	if (ret < 0) {
		log_error("error(%d) in te_ip_set_nagra_key(ch:%u attr:%u "
			  "pid:0x%02x", ret, msg.ch, msg.attribute, msg.pid);
		return ret;
	}

	return 0;
}

int sdec_desc_set_nagra_key(struct sdec_channel *channel,
			    struct sdec_desc_nagra_key_param *param)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = set_nagra_key(channel, param);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int cancel_nagra_pid(struct sdec_channel *channel, u16 pid)
{
	struct pid_cancel ipc;
	int rc;

	ipc.ch = channel->num;
	ipc.pid = pid;

	rc = te_ipc_cancel_nagra_pid(&ipc);
	if (rc) {
		log_error("error in te_ipc_cancel_nagra_pid %d, 0x%02x", rc,
			  pid);
		return rc;
	}

	return 0;
}

int sdec_desc_cancel_nagra_pid(struct sdec_channel *channel, u16 pid)
{
	int ret;

	mutex_lock(&dsc_mutex);
	ret = cancel_nagra_pid(channel, pid);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int get_nagra_nonce(struct sdec_channel *channel, u8 *nonce)
{
	struct sdec_dev_senddata *e = &channel->dev->dsc_senddata;
	IPC_MSG_DSC_NAGRA_REQUEST_NONCE_T msg;
	int rc;

	register_send_data(e, nonce);
	reinit_completion(&e->completion);

	msg.ch = channel->num;
	rc = te_ipc_get_nagra_nonce(&msg);
	if (rc) {
		log_error("error in te_ipc_get_nagra_nonce ch:%u %d",
			  channel->num, rc);
		goto error;
	}

	rc = wait_for_completion_timeout(&e->completion,
					 msecs_to_jiffies(DATA_RETURN_TIMEOUT));
	if (rc <= 0) {
		log_error("fatal error, timeout occured");
		rc = -ETIME;
		goto error;
	}

	rc = 0;
error:
	unregister_send_data(e);
	return rc;
}

int sdec_desc_get_nagra_nonce(struct sdec_channel *channel, u8 *nonce)
{
	int ret;

	if (!nonce)
		return -EFAULT;

	mutex_lock(&dsc_mutex);
	ret = get_nagra_nonce(channel, nonce);
	mutex_unlock(&dsc_mutex);

	return ret;
}

static int set_nagra_state(struct sdec_channel *channel, u8 *data, u8 *iv)
{
	IPC_MSG_DSC_NAGRA_SET_STATE_T msg;
	int rc;

	msg.ch = channel->num;
	memcpy(msg.data, data, 32);
	memcpy(msg.comm_iv, iv, 16);

	rc = te_ipc_set_nagra_state(&msg);
	if (rc) {
		log_error("error in te_ipc_set_nagra_state ch:%u %d",
			  channel->num, rc);
		return rc;
	}

	return 0;
}

int sdec_desc_set_nagra_state(struct sdec_channel *channel, u8 *data, u8 *iv)
{
	int ret;

	if (!data || !iv)
		return -EFAULT;

	mutex_lock(&dsc_mutex);
	ret = set_nagra_state(channel, data, iv);
	mutex_unlock(&dsc_mutex);

	return ret;
}

/* sdec sub device functions */
static int desc_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	const struct sdec_ioctl_info ioctls[] = {
		IOC_INFO(SDEC_IOC_DESC_INIT, ioc_init_descrambler),
		IOC_INFO(SDEC_IOC_DESC_SET_KEY, ioc_set_descrambler_key),
		IOC_INFO(SDEC_IOC_DESC_SET_PID, ioc_set_descrambler_pid),
		IOC_INFO(SDEC_IOC_DESC_SEND_ECP, ioc_set_ecp_key),
	};

	return sdec_do_ioctl(priv, cmd, arg, dsc_mutex, ioctls);
}

static int dsc_senddata_callback(void *msg, void *arg)
{
	IPC_MSG_DSC_RETURN_DATA_T *data = msg;
	struct sdec_device *dev = arg;
	struct sdec_dev_senddata *e;

	e = &dev->dsc_senddata;

	spin_lock(&e->spinlock);
	/* copy predefined memory area (encrypted) */
	if (e->data) {
		memcpy(e->data, data->data, data->size);
		e->size = data->size;
	} else {
		log_error("Fatal error, target mem was not set");
	}
	spin_unlock(&e->spinlock);
	complete(&e->completion);

	return 0;
}

static int desc_dev_senddata_init(struct sdec_dev_senddata *e)
{
	e->data = NULL;
	init_completion(&e->completion);
	spin_lock_init(&e->spinlock);

	return 0;
}


/**
 * Initialize the descrambler at initial time
 *
 * @param	sdec	[in	] sdec param
 * @return	if succeeded - 0, else - errno.
 * @see
 */
static int desc_dev_init(struct sdec_device *dev)
{
	int rc;
#ifdef USE_FIXEDMEM_STATUS
#define FIXEDMEM_LOCATION 0x7d000000
	dev->pmem = te_vmap(FIXEDMEM_LOCATION, SZ_1K, false);
	if (dev->pmem) {
		memset(dev->pmem, 0, IPC_SEND_DATA_MSG_SIZE);
	} else {
		log_error("FATAL ERROR; fail to alloc pmem");
		return -EFAULT;
	}
#else
	dev->pmem = NULL;
#endif //USE_FIXEDMEM_STATUS

	rc = desc_dev_senddata_init(&dev->dsc_senddata);
	if (rc)
		return rc;

	te_ipc_register_dsc_callback(dsc_senddata_callback, dev);

	te_mcu_register_rcallback(get_te_device(dev),
				  TE_MCU_FUNC_TYPE_DSC,
				  mcu_recovery_desc_pre_callback,
				  mcu_recovery_desc_post_callback, dev);

	return 0;
}

static void desc_dev_release(struct sdec_device *dev)
{
	te_ipc_register_dsc_callback(NULL, NULL);
#ifdef USE_FIXEDMEM_STATUS
	te_vunmap(dev->pmem);
#endif
}

static int desc_dev_suspend(struct sdec_device *dev)
{
	te_ipc_register_dsc_callback(NULL, NULL);
	return 0;
}

static int desc_dev_resume(struct sdec_device *dev)
{
#ifdef USE_FIXEDMEM_STATUS
	if (dev->pmem) {
		memset(dev->pmem, 0, IPC_SEND_DATA_MSG_SIZE);
	} else {
		log_error("FATAL ERROR; No pmem allocated");
		return -EFAULT;
	}
#endif
	te_ipc_register_dsc_callback(dsc_senddata_callback, dev);
	return 0;
}

static const struct sdec_ioctl ioctl_desc = {
	.magic = SDEC_IOC_DESC_MAGIC,
	.func = desc_dev_ioctl,
};

const struct sdec_sub_driver sdec_desc_driver = {
	.name = "sdec_desc",
	.init = desc_dev_init,
	.release = desc_dev_release,
	.suspend = desc_dev_suspend,
	.resume = desc_dev_resume,

	.ioctl = &ioctl_desc,
};
