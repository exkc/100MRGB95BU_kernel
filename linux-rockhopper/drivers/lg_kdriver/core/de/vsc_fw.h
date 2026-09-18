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
 *  driver interface header for de device. ( used only within kdriver )
 *	de device will teach you how to make device driver with new platform.
 *
 *  @author
 *  @version
 *  @date
 *
 *  @addtogroup
 *	@{
 */

#ifndef	_VSC_FW_H_
#define	_VSC_FW_H_

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
#define VSC_FW_MAX_NUM    (10)
#define VSC_FW_CRC_MAGIC  (0xDECAFE)
#define VSC_FW_HEAD_MAGIC (0x50515348)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum vsc_fw_ret {
    VSC_FW_RET_OK = 0,
    VSC_FW_RET_ERROR,
    VSC_FW_RET_NEXT,
    VSC_FW_RET_SKIP,
    VSC_FW_RET_MAX
};

enum vsc_fw_opt {
    VSC_FW_OPT_NONE = 0,
    VSC_FW_OPT_SKIP,
    VSC_FW_OPT_BIN,
    VSC_FW_OPT_USR,
    VSC_FW_OPT_LOCAL,
    VSC_FW_OPT_HEADER,
	VSC_FW_OPT_DBGMAP,
    VSC_FW_OPT_MAX
};

enum vsc_fw_from {
    VSC_FW_FROM_NORMAL = 0,
    VSC_FW_FROM_THREAD,
    VSC_FW_FROM_USERBIN,
    VSC_FW_FROM_RESUME,
    VSC_FW_FROM_THAW,
    VSC_FW_FROM_RESTORE,
    VSC_FW_FROM_RPM_RESUME,
    VSC_FW_FROM_RPM_SUSPEND,
    VSC_FW_FROM_MAX
};

enum {
	VSC_FW_LOAD_NONE = 0,
	VSC_FW_LOAD_STOP,
	VSC_FW_LOAD_PREPARE,
	VSC_FW_LOAD_COMPLETE,
	VSC_FW_LOAD_MAX,
	VSC_FW_MEM_CPY,
	VSC_FW_UPDATE_PC,
	VSC_FW_UPDATE_EXCE,
};

struct vsc_fw_crc {
	union {
		unsigned int u32;
		struct {
		unsigned int num   :8; //(7:0)
		unsigned int magic :24;//(31:8)
		};
	} h;
	unsigned int size;
	unsigned int crc;
};

struct vsc_fw_load_param {
	int idx;
	char *name;
	int action;
	int secure;
	unsigned int word;
	int cfg;
	unsigned int bin_size;
	char *bin_data;
	char *hma_pool;
	phys_addr_t hma_base;
	phys_addr_t hma_base_bkup;
	unsigned int hma_size;
	char *int_pool;
	phys_addr_t int_base;
	phys_addr_t vmap_phys;
	void *vmap_base;
	void *vmap_base_bkup;
	unsigned int vmap_size;
	phys_addr_t src_base;
	phys_addr_t dst_base;
	unsigned int rom_base;
	unsigned int mem_src;
	unsigned int mem_dst;
	unsigned int mem_size;
	unsigned int mem_crc;
	struct vsc_fw_crc crc;
	unsigned int bin_crc;
	unsigned int bin_u32;
	unsigned int pc;
	unsigned int exce;
	char *err_mesg;
};

struct vsc_fw_load {
	int (*handler)(struct vsc_fw_load_param *, int);
	struct vsc_fw_load_param *param[VSC_FW_MAX_NUM];
};

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int vsc_fw_init(void);
extern unsigned int vsc_fw_get_user_bin_num(void);
extern int vsc_fw_init_late(unsigned int flag);
extern int vsc_fw_view_log(void);
extern int vsc_fw_rpm(int from);
extern int vsc_fw_download(int from);
extern int vsc_fw_io_download(void *param, unsigned int flag);
extern int vsc_fw_hal_load(int idx, int cfg, int size, char *data);
extern int vsc_fw_alloc_backup_all(void);
extern int vsc_fw_free_backup_all(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VSC_FW_H_ */
