/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  Header for Security Engine kdriver.
 *
 *  @author     stan.kim@lge.com
 *  @version    2.0
 *  @date       2012.5
 *  @note       Additional information.
 */

#ifndef	_SE_KAPI_H_
#define	_SE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	SE_IOC_MAGIC			'S'
#define SE_NETLINK				31
#define SE_IOW_SEND_MSG_LENGTH	256

#define SE_DRV_STATUS_AFTER_RESUME    0x01
#define SE_DRV_STATUS_AFTER_RESTORE   0x10

/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/**
@name Secure Engine IOCTL List
ioctl list for Secure Engine
@{
*/

/**
@def SE_IORW_RUN_TZ_OP
	Run TZ Operation
	@param	pTzArg	[in/out] pointer to TrustZone Arguments
	@return	RET_OK if success, RET_ERROR otherwise.
*/
//////////////
/*
 * "unsigned long long" for passing user ptr (unsigned int *), so, need casting.
 *
 */
#define SE_IORW_RUN_TZ_OP		_IOWR(SE_IOC_MAGIC, 0, unsigned long long)

/**
@def SE_IOR_WAIT
	Wait TZ Signal
	@param	offset	[in] signal flag offset for wait
	@return	RET_OK if success, RET_ERROR otherwise.
*/
#define SE_IOR_WAIT				_IOR(SE_IOC_MAGIC, 1, unsigned int)


#ifdef CFG_REE_KDRV_RUTA_KDRV

#define RUTA_IOR_GET_RMT_RWSM	_IOWR(SE_IOC_MAGIC, 2, void *)

#define RUTA_IORW_RECV			_IOWR(SE_IOC_MAGIC, 3, unsigned int *)

#define RUTA_IORW_SEND			_IOWR(SE_IOC_MAGIC, 4, unsigned int *)

#endif /* CFG_REE_KDRV_RUTA_KDRV */


/**
@def SE_IOR_GET_SMC_THREAD_SCHED_POLICY
	Get SMC thread Sched policy
	@param
	@return	scheduling policy if success, RET_ERROR otherwise.
*/
//////////////
/*
 * "unsigned long long" for passing user ptr (unsigned int *), so, need casting.
 *
 */
#define SE_IOR_GET_SMC_THREAD_SCHED_POLICY	_IOR(SE_IOC_MAGIC, 5, unsigned long long)

/**
@def SE_IOWR_SET_SMC_THREAD_SCHED_POLICY
	Set SMC thread Sched policy
	@param Scheduling policy
	@return	0 if success, RET_ERROR otherwise.
*/
//////////////
/*
 * "unsigned long long" for passing user ptr (unsigned int *), so, need casting.
 *
 */
#define SE_IOWR_SET_SMC_THREAD_SCHED_POLICY	_IOWR(SE_IOC_MAGIC, 6, unsigned long long)


#define DMA_BUF_IO_GET_INFO_FROM_FD	_IOWR(SE_IOC_MAGIC, 7, unsigned long long)

#define DMA_BUF_IO_TEST_EXPORT		_IOWR(SE_IOC_MAGIC, 8, unsigned long long)


/**
@def SE_IOW_CACHE_CTL
	Cache Control
	@param	pCtrl	[in] Cache Contol Info
	@return	RET_OK if success, RET_ERROR otherwise.
*/
//////////////
/*
 * "unsigned long long" for passing user ptr (void *), so, need casting.
 *
 */
#define SE_IOW_CACHE_CTRL		_IOR(SE_IOC_MAGIC, 0x80, unsigned long long)

/**
@def SE_IOW_SEND_MSG
	Send Message to Deamon (kadpd)
	@param	msg[SE_IOW_SEND_MSG_LENGTH]	[in] message to kadpd
	@return	RET_OK if success, RET_ERROR otherwise.
*/
//////////////
/*
 * "unsigned long long" for passing user ptr (void *), so, need casting.
 *
 */
#define SE_IORW_SEND_MSG		_IOWR(SE_IOC_MAGIC, 0x90, unsigned long long)

/**
@def SE_IO_CHECK_RESUME
	Check Permission
	@return	RET_OK if NO permission, RET_ERROR otherwise.
*/
#define SE_IO_CHECK_PERMISSION	_IO(SE_IOC_MAGIC, 0x100)

/**
@def SE_IO_CHECK_RESUME
	Check Resume
	@return	RET_OK if resume, RET_ERROR otherwise.
*/
#define SE_IO_CHECK_RESUME		_IO(SE_IOC_MAGIC, 0xfe)

#define SE_IOR_GET_RESUME_STATUS	_IOR(SE_IOC_MAGIC, 0xf1, unsigned int)


/**
@def SE_IOW_GET_MEM_INFO
	Get SE Memory Info
	@param	pInfo	[in] Memory Info
	@return	RET_OK if success, RET_ERROR otherwise.
*/
//////////////
/*
 * "unsigned long long" for passing user ptr (void *), so, need casting.
 *
 */
#define SE_IOW_GET_MEM_INFO		_IOR(SE_IOC_MAGIC, 0xff, unsigned long long)


/* MAX_USER_IO_MAP_SHM_SZ related to SE_IOR_GET_MAP_USER_SHM_MEM*/
#define MAX_USER_IO_MAP_SHM_SZ (4096)

#define SE_IOR_GET_MAP_USER_SHM_MEM	\
				_IOR(SE_IOC_MAGIC, 0xf2, unsigned long long)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	SE_CACHE_MAP	= 0,
	SE_CACHE_INVALIDATE,
	SE_CACHE_CLEAN,
} SE_CACHE_OP;

typedef struct {
	unsigned long long paddr;		/**< Physical Address */
	unsigned long long vaddr;		/**< Virtual Address */
	unsigned int size;		/**< Contol Size */
	SE_CACHE_OP operation;	/**< Cache Control Operation */
} SE_CACHE_CTRL_T;

typedef struct {
	unsigned int idx;	/**< MemCfg Idx */
	unsigned int base;	/**< Base */
	unsigned int size;	/**< Size */
} SE_MEMCFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _SE_KAPI_H_ */

/** @} */
