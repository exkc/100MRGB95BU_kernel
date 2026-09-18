/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

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
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/version.h>

#include "os_util.h"
#include "proc_util.h"
#include "sys_drv.h"
#include "sys_log.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
    PROC_ID_DUMMY = 0,
    PROC_ID_MAX
};

typedef struct
{
    uint32_t opcode;
    uint32_t operand;
}
reg_param_t;

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void sys_shadow_init(void);
void sys_shadow_init_proc(void);
void sys_shadow_pm_function(struct device* dev, char* command);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern struct os_proc* lg1k_sys_proc_entry;

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
#ifdef CHIP_NAME_o26
#ifdef BUILD_FEATURE_audio_board
#include "o26/shadow_rom_audio.h"
#else
#include "o26/shadow_rom.h"
#endif
#endif

#ifdef CHIP_NAME_o24
#include "o24/shadow_rom.h"
#endif

#ifdef CHIP_NAME_o22
#include "o22/shadow_rom.h"
#endif

#ifdef CHIP_NAME_m23
#include "m23/shadow_rom.h"
#endif

/*========================================================================================
    Implementation Group
========================================================================================*/
static void shadow_init_cmm(void)
{
    int i;
    int reg_num;

    reg_num = NELEMENTS(shadow_rom_cmm);

    for (i = 0; i < reg_num; i++)
    {
        SYS_DEBUG("[shadow %03d] 0x%08x 0x%08x\n", i, shadow_rom_cmm[i].opcode, shadow_rom_cmm[i].operand);
        OS_WrReg(shadow_rom_cmm[i].opcode, shadow_rom_cmm[i].operand);
    }

    SYS_NOTI("[shadow] %d cmm completed\n", reg_num);
}

void sys_shadow_init(void)
{
    shadow_init_cmm();
}

void sys_shadow_pm_function(struct device* dev, char* command)
{
    bool restore_hw = false;

    if (!strncmp(command, "resume", 6) || !strncmp(command, "restore", 7))
    {
        restore_hw = true;
    }

    // 초기값으로 강제 설정토록 함
    if (restore_hw)
    {
        shadow_init_cmm();
    }

    // add something
}

/*========================================================================================
    Implementation Group
========================================================================================*/
static int shadow_proc_reader_func(UINT32 procId, char* buffer);
static int shadow_proc_writer_func(UINT32 procId, char* command);

static int shadow_read_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return shadow_proc_reader_func(procId, buffer);
}

static int shadow_write_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return shadow_proc_writer_func(procId, buffer);
}
static int shadow_proc_print_status(struct seq_file* m, void* data)
{
    int i;
    int reg_num;

    reg_num = NELEMENTS(shadow_rom_cmm);

    for (i = 0; i < reg_num; i++)
    {
        seq_printf(m, "[%03d] 0x%08x 0x%08x\n", i, shadow_rom_cmm[i].opcode, shadow_rom_cmm[i].operand);
    }

    return 0;
}

static int shadow_proc_reader_func(UINT32 procId, char* buffer)
{
    return 0;
}

static int shadow_proc_writer_func(UINT32 procId, char* command)
{
    switch (procId)
    {
        case PROC_ID_DUMMY:
        {
            // do nothing
        }
        break;
    }

    return strlen(command);
}


void sys_shadow_init_proc(void)
{
    struct os_proc* pdir = os_proc_create_dir(lg1k_sys_proc_entry, "shadow", shadow_read_proc_handler,
                           shadow_write_proc_handler);

    os_proc_create_file(pdir, "dummy",  PROC_ID_DUMMY, NULL);
    os_proc_create_seq_file(pdir, "status", shadow_proc_print_status, NULL, NULL);
}

/** @} */

