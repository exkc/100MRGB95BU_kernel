/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2023 by LG Electronics Inc.
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
 *  remote uta linux kernel driver
 *
 *  author		
 *  version		1.0
 *  date		2023.01.14
 *  note		Additional information.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/rmap.h>
#include <linux/completion.h>
#include <linux/io.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <uapi/linux/sched/types.h>
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/tee_drv.h>
#endif
#include <linux/types.h>
#include <linux/arm-smccc.h>


#include "ree_kconfig.h"
#include "ree_kdrv.h"
#include "smc_cmd_defines.h"




struct rwsm_mem_unit {
	unsigned long base;
	unsigned long size;
};


struct rwsm_map {
	struct rwsm_mem_unit overall;
	struct rwsm_mem_unit param;
	struct rwsm_mem_unit data;
};


/* get from secure os */
struct rwsm_phy_map {
	struct rwsm_map ca;
	struct rwsm_map rmt;
};



struct ruta_kdrv_ops {
	/* Serializes access to this struct */
	struct mutex mutex;
	struct tee_context *ctx;

	int req_id;
	struct list_head reqs;
	struct idr idr;
	struct completion rmt_smc_c; /* wait ruta, complete after rmt_smc */
	struct completion rmt_ruta_c; /* wait rmt smc, complete after ruta  */

	int (*get_rwsm) (void *);
	int (*recv) (void *);
	int (*send) (void *);

	struct rwsm_phy_map phy_rwsm;
};


struct ruta_kdrv_ops *rkdrv_ops = NULL;


void ruta_kdrv_init(struct ruta_kdrv_ops *rkdrv_ops);


static int get_rwsm(void *arg)
{
	int ret = 0;


	if( copy_to_user((void __user *)arg, 
			(void *)(&rkdrv_ops->phy_rwsm), sizeof(rkdrv_ops->phy_rwsm)) ) {
		ret = -EIO;
	}

	return ret;
}


static int recv(void *arg)
{
	int ret = 0;

	while (true) {

		if (wait_for_completion_interruptible(&rkdrv_ops->rmt_smc_c))
			return -ERESTARTSYS;

		break;
	}

	return ret;
}


static int send(void *arg)
{
	int ret = 0;

	complete(&rkdrv_ops->rmt_ruta_c);
	
	return ret;
}

void handle_remote_smc(struct rmt_param *rparam)
{

	init_completion(&rkdrv_ops->rmt_ruta_c);

	/* Tell an eventual waiter there's a new request */
	complete(&rkdrv_ops->rmt_smc_c);


	while (wait_for_completion_interruptible(&rkdrv_ops->rmt_ruta_c)) {

	}

	rparam->a0 = TZ_CMD_RETURN_FROM_RMT;
}


/* called from ioctl */
int ruta_kdrv_get_rmt_rwsm(unsigned long arg)
{
	/*
	pr_info("rkdrv_ops->get_rwsm (%p),(%p)\n", rkdrv_ops->get_rwsm, rkdrv_ops);
	*/
	return rkdrv_ops->get_rwsm((void *)arg);
}


int ruta_kdrv_recv(unsigned long arg)
{
	/*
	pr_info("------------------>ruta_kdrv_recv \n");
	*/
	return rkdrv_ops->recv((void *)arg);
}


int ruta_kdrv_send(unsigned long arg)
{
	/*
	pr_info("ruta_kdrv_send --------------------> \n");
	*/
	return rkdrv_ops->send((void *)arg);
}

void ree_smccc_smc( unsigned long a0, unsigned long a1, 
					unsigned long a2, unsigned long a3, unsigned long a4, 
					unsigned long a5, unsigned long a6, unsigned long a7, 
					struct arm_smccc_res *res)
{   
    arm_smccc_smc(a0, a1, a2, a3, a4, a5, a6, a7, res);
}


int do_smc_with_args(u32 *smc_args)
{	
	struct arm_smccc_res res;
	struct rmt_param rparam = { };
	int ret = -1;
	
	
	
	//memcpy(&rparam, &_gSeInfo.tzArgs[0], sizeof(struct rmt_param));
	memcpy(&rparam, smc_args, sizeof(struct rmt_param));
		
	while (1) {

		/*
		pr_info("do_smc_with_args, 0x%x \n", rparam.a0);
		*/
		ree_smccc_smc( rparam.a0, rparam.a1, rparam.a2, rparam.a3, rparam.a4,
						rparam.a5, rparam.a6, rparam.a7, 
						&res);


		//if(res.a0 == 8004) {
		if(res.a0 == LGTEE_RMT_SMC_FUNC_FOREIGN_IRQ) {

			/*
			pr_info("do_smc_with_args, LGTEE_RMT_SMC_FUNC_FOREIGN_IRQ \n");
			*/
			
			rparam.a0 = TZ_CMD_RETURN_FROM_RMT;
			//rparam.a1 = res.a1;
			//rparam.a2 = res.a2;
			//rparam.a3 = res.a3;
			
			/* for performance */
			yield();

		} else if (res.a0 == LGTEE_RMT_SMC_FUNC_RUTA) {

			/*
			pr_info("do_smc_with_args, LGTEE_RMT_SMC_FUNC_RUTA \n");
			*/
			//might_sleep();
			rparam.a0 = res.a0;
			rparam.a1 = res.a1;
			rparam.a2 = res.a2;
			rparam.a3 = res.a3;

			/* 
			 * TZ_CMD_RETURN_FROM_RMT
			 * Set rparam.a0 to TZ_CMD_RETURN_FROM_RMT in the function below and 
			 * then this value is trasfered to secure os in order to restore 
			 * thread context. 
			 */
			handle_remote_smc(&rparam);

		} else {

			/*
			pr_info("do_smc_with_args, normal smc return from tee(0x%lx)\n", 
								res.a0);
			*/
			smc_args[0] = res.a0;
			smc_args[1] = res.a1;
			smc_args[2] = res.a2;
			smc_args[3] = res.a3;

			if (smc_args[0] == TEE_SUCCESS)
				ret = 0;

			break;
		}
	}

	/*
	pr_info("return do_smc_with_args, return 0x%x \n", ret);
	*/
	
	return ret;
}


static int get_rwsm_config(struct rwsm_phy_map *phy_rwsm_map)
{
	int ret = 0;
	struct arm_smccc_res res;
	unsigned long cmd = TZ_CMD_GET_RMT_RWSM_CONFIG;
	unsigned long base = 0, size = 0, offset = 0;   

	
	ree_smccc_smc(cmd, 0, 0, 0, 0, 0, 0, 0, &res);

	/*
	pr_info("get_rwsm_config (0x%lx) (0x%lx) (0x%lx) (0x%lx)\n", 
											res.a0, res.a1, res.a2,res.a3);
	*/
	
	/* 
	 * X1[31:00] : base address of ca rwsm
	 * X1[63:32] : size of ca rwsm 
	 * X2[31:00] : base address of rmt rwsm
	 * X2[63:32] : size of rmt rwsm
	 * X3[31:00] : offset of ca param
	 * X3[63:32] : offset of rmt param
	 */
	base = res.a1 & 0x00000000FFFFFFFF;
	size = (res.a1 >> 32) & 0x00000000FFFFFFFF;
	offset = res.a3 & 0x00000000FFFFFFFF;
	phy_rwsm_map->ca.overall.base = base;
	phy_rwsm_map->ca.overall.size = size;
	phy_rwsm_map->ca.data.base = base;
	phy_rwsm_map->ca.data.size = offset;
	phy_rwsm_map->ca.param.base = base + offset;
	phy_rwsm_map->ca.param.size = base + size - (base + offset);

	base = res.a2 & 0x00000000FFFFFFFF;
	size = (res.a2 >> 32) & 0x00000000FFFFFFFF;
	offset = (res.a3 >> 32) & 0x00000000FFFFFFFF;
	phy_rwsm_map->rmt.overall.base = base;
	phy_rwsm_map->rmt.overall.size = size;
	phy_rwsm_map->rmt.data.base = base;
	phy_rwsm_map->rmt.data.size = offset;
	phy_rwsm_map->rmt.param.base = base + offset;
	phy_rwsm_map->rmt.param.size = base + size - (base + offset);

	return ret;
}


void ruta_kdrv_init(struct ruta_kdrv_ops *rkdrv_ops)
{
	memset(rkdrv_ops, 0, sizeof(*rkdrv_ops));

	mutex_init(&rkdrv_ops->mutex);
	
	init_completion(&rkdrv_ops->rmt_smc_c);
	init_completion(&rkdrv_ops->rmt_ruta_c);

	rkdrv_ops->get_rwsm = get_rwsm;
	rkdrv_ops->recv = recv;
	rkdrv_ops->send = send;


	//idr_init(&ruta->idr);

	/* not used yet */
	INIT_LIST_HEAD(&rkdrv_ops->reqs);

	rkdrv_ops->req_id = -1;

	get_rwsm_config(&rkdrv_ops->phy_rwsm);
}


int ree_ruta_kdrv_init(void)
{
	int rc = 0;

	rkdrv_ops = kzalloc(sizeof(*rkdrv_ops), GFP_KERNEL);
	
	if (!rkdrv_ops) {
		rc = -ENOMEM;
		goto err;
	}

	ruta_kdrv_init(rkdrv_ops);

	return rc;

err:

	kfree(rkdrv_ops);

	return rc;
}


#if 0
static const struct tee_driver_ops lgkree_ruta_ops = {
	.get_version = lgtee_get_version,
	.open = lgtee_open,
	.release = lgtee_release,
	.supp_recv = lgtee_ruta_recv,
	.supp_send = lgtee_ruta_send,
	//.shm_register = optee_shm_register_supp,
	//.shm_unregister = optee_shm_unregister_supp,
};

static const struct tee_desc lgkree_ruta_desc = {
	.name = DRIVER_NAME "-ruta",
	.ops = &lgkree_ruta_ops,
	.owner = THIS_MODULE,
	.flags = TEE_DESC_PRIVILEGED,
};
#endif
