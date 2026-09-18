/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 *  audio buffer control hal driver
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/delay.h>

#include "common/ipc_reg_offs.h"
#include "hma_alloc.h"
#include "logm.h"

#include "hal/hal.h"
#include "hal/hal_bc.h"
#include "hal/o24/regs.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define REG_TP0_DSPMODE                         tpmbc_ctrl
#define FLD_TP0_DSPMODE                         tpmbc_dspmode
#define REG_TP0_SWRESET                         tpmbc_ctrl
#define FLD_TP0_SWRESET                         tpmbc_swreset
#define REG_TP0_UNIT_INT_ENABLE                 tpmbc_ctrl
#define FLD_TP0_UNIT_INT_ENABLE                 tpmbc_uinten
#define REG_TP0_DATA_FORMAT                     tpmbc_ctrl
#define FLD_TP0_DATA_FORMAT                     tpmbc_dataformat
#define REG_TP0_START_ADDRESS                   tpmbc_start_address
#define REG_TP0_END_ADDRESS                     tpmbc_end_address
#define REG_TP0_WRITE_ADDRESS                   tpmbc_write_point_status
#define REG_TP0_READ_ADDRESS                    tpmbc_read_address
#define REG_TP0_ALMOST_LEVEL                    tpmbc_almost_full_level
#define REG_TP0_UNIT_SIZE                       tpmbc_unit_level

#define REG_TP1_DSPMODE                         tpabc_ctrl
#define FLD_TP1_DSPMODE                         tpabc_dspmode
#define REG_TP1_SWRESET                         tpabc_ctrl
#define FLD_TP1_SWRESET                         tpabc_swreset
#define REG_TP1_UNIT_INT_ENABLE                 tpabc_ctrl
#define FLD_TP1_UNIT_INT_ENABLE                 tpabc_uinten
#define REG_TP1_DATA_FORMAT                     tpabc_ctrl
#define FLD_TP1_DATA_FORMAT                     tpabc_dataformat
#define REG_TP1_START_ADDRESS                   tpabc_start_address
#define REG_TP1_END_ADDRESS                     tpabc_end_address
#define REG_TP1_WRITE_ADDRESS                   tpabc_write_point_status
#define REG_TP1_READ_ADDRESS                    tpabc_read_address
#define REG_TP1_ALMOST_LEVEL                    tpabc_almost_full_level
#define REG_TP1_UNIT_SIZE                       tpabc_unit_level

#define REG_SAI0_DSPMODE                        sai0bc_ctrl
#define FLD_SAI0_DSPMODE                        sai0bc_dspmode
#define REG_SAI0_SWRESET                        sai0bc_ctrl
#define FLD_SAI0_SWRESET                        sai0bc_swreset
#define REG_SAI0_UNIT_INT_ENABLE                sai0bc_ctrl
#define FLD_SAI0_UNIT_INT_ENABLE                sai0bc_uinten
#define REG_SAI0_DATA_FORMAT                    sai0bc_ctrl
#define FLD_SAI0_DATA_FORMAT                    sai0bc_data_format
#define REG_SAI0_START_ADDRESS                  sai0bc_start_address
#define REG_SAI0_END_ADDRESS                    sai0bc_end_address
#define REG_SAI0_WRITE_ADDRESS                  sai0bc_write_point_status
#define REG_SAI0_READ_ADDRESS                   sai0bc_read_address
#define REG_SAI0_ALMOST_LEVEL                   sai0bc_almost_full_level
#define REG_SAI0_UNIT_SIZE                      sai0bc_unit_interrupt_level

#define REG_SAI1_DSPMODE                        sai1bc_ctrl
#define FLD_SAI1_DSPMODE                        sai1bc_dspmode
#define REG_SAI1_SWRESET                        sai1bc_ctrl
#define FLD_SAI1_SWRESET                        sai1bc_swreset
#define REG_SAI1_UNIT_INT_ENABLE                sai1bc_ctrl
#define FLD_SAI1_UNIT_INT_ENABLE                sai1bc_uinten
#define REG_SAI1_DATA_FORMAT                    sai1bc_ctrl
#define FLD_SAI1_DATA_FORMAT                    sai1bc_data_format
#define REG_SAI1_START_ADDRESS                  sai1bc_start_address
#define REG_SAI1_END_ADDRESS                    sai1bc_end_address
#define REG_SAI1_WRITE_ADDRESS                  sai1bc_write_point_status
#define REG_SAI1_READ_ADDRESS                   sai1bc_read_address
#define REG_SAI1_ALMOST_LEVEL                   sai1bc_almost_full_level
#define REG_SAI1_UNIT_SIZE                      sai1bc_unit_interrupt_level

#define REG_SAI2_DSPMODE                        sai2bc_ctrl
#define FLD_SAI2_DSPMODE                        sai2bc_dspmode
#define REG_SAI2_SWRESET                        sai2bc_ctrl
#define FLD_SAI2_SWRESET                        sai2bc_swreset
#define REG_SAI2_UNIT_INT_ENABLE                sai2bc_ctrl
#define FLD_SAI2_UNIT_INT_ENABLE                sai2bc_uinten
#define REG_SAI2_DATA_FORMAT                    sai2bc_ctrl
#define FLD_SAI2_DATA_FORMAT                    sai2bc_data_format
#define REG_SAI2_START_ADDRESS                  sai2bc_start_address
#define REG_SAI2_END_ADDRESS                    sai2bc_end_address
#define REG_SAI2_WRITE_ADDRESS                  sai2bc_write_point_status
#define REG_SAI2_READ_ADDRESS                   sai2bc_read_address
#define REG_SAI2_ALMOST_LEVEL                   sai2bc_almost_full_level
#define REG_SAI2_UNIT_SIZE                      sai2bc_unit_interrupt_level

#ifdef SUPPORT_SOUNDBAR
#define REG_SAI4_DSPMODE                        sai4bc_ctrl
#define FLD_SAI4_DSPMODE                        sai4bc_dspmode
#define REG_SAI4_SWRESET                        sai4bc_ctrl
#define FLD_SAI4_SWRESET                        sai4bc_swreset
#define REG_SAI4_UNIT_INT_ENABLE                sai4bc_ctrl
#define FLD_SAI4_UNIT_INT_ENABLE                sai4bc_uinten
#define REG_SAI4_DATA_FORMAT                    sai4bc_ctrl
#define FLD_SAI4_DATA_FORMAT                    sai4bc_data_format
#define REG_SAI4_START_ADDRESS                  sai4bc_start_address
#define REG_SAI4_END_ADDRESS                    sai4bc_end_address
#define REG_SAI4_WRITE_ADDRESS                  sai4bc_write_point_status
#define REG_SAI4_READ_ADDRESS                   sai4bc_read_address
#define REG_SAI4_ALMOST_LEVEL                   sai4bc_almost_full_level
#define REG_SAI4_UNIT_SIZE                      sai4bc_unit_interrupt_level

#define REG_AEC_SAI_DSPMODE                     aec_sai_bc_ctrl
#define FLD_AEC_SAI_DSPMODE                     dspmode_en
#define REG_AEC_SAI_SWRESET                     aec_sai_bc_ctrl
#define FLD_AEC_SAI_SWRESET                     sai_swreset
#define REG_AEC_SAI_UNIT_INT_ENABLE             aec_sai_bc_ctrl
#define FLD_AEC_SAI_UNIT_INT_ENABLE             sai_int_en
#define REG_AEC_SAI_DATA_FORMAT                 aec_sai_bc_ctrl
#define FLD_AEC_SAI_DATA_FORMAT                 sai_data_format
#define REG_AEC_SAI_START_ADDRESS               aec_sai_bc_str_addr
#define REG_AEC_SAI_END_ADDRESS                 aec_sai_bc_end_addr
#define REG_AEC_SAI_WRITE_ADDRESS               aec_sai_bc_wptr_status
#define REG_AEC_SAI_READ_ADDRESS                aec_sai_bc_read_addr
#define REG_AEC_SAI_ALMOST_LEVEL                aec_sai_bc_af_lvl
#define REG_AEC_SAI_UNIT_SIZE                   aec_sai_bc_int_lvl
#endif

#define REG_PCM_MAIN_DSPMODE                    mainbc_ctrl
#define FLD_PCM_MAIN_DSPMODE                    pcm_main_dspmode
#define REG_PCM_MAIN_SWRESET                    mainbc_ctrl
#define FLD_PCM_MAIN_SWRESET                    pcm_main_swreset
#define REG_PCM_MAIN_UNIT_INT_ENABLE            mainbc_ctrl
#define FLD_PCM_MAIN_UNIT_INT_ENABLE            pcm_main_uinten
#define REG_PCM_MAIN_DATA_FORMAT                mainbc_ctrl
#define FLD_PCM_MAIN_DATA_FORMAT                pcm_main_dataformat
#define REG_PCM_MAIN_START_ADDRESS              mainbc_start_address
#define REG_PCM_MAIN_END_ADDRESS                mainbc_end_address
#define REG_PCM_MAIN_WRITE_ADDRESS              mainbc_write_address
#define REG_PCM_MAIN_READ_ADDRESS               mainbc_read_address
#define REG_PCM_MAIN_ALMOST_LEVEL               mainbc_almost_empty_level
#define REG_PCM_MAIN_UNIT_SIZE                  mainbc_unit_interrupt_level

#define REG_PCM_SUB_DSPMODE                     subbc_ctrl
#define FLD_PCM_SUB_DSPMODE                     pcm_sub_dspmode
#define REG_PCM_SUB_SWRESET                     subbc_ctrl
#define FLD_PCM_SUB_SWRESET                     pcm_sub_swreset
#define REG_PCM_SUB_UNIT_INT_ENABLE             subbc_ctrl
#define FLD_PCM_SUB_UNIT_INT_ENABLE             pcm_sub_uniten
#define REG_PCM_SUB_DATA_FORMAT                 subbc_ctrl
#define FLD_PCM_SUB_DATA_FORMAT                 pcm_sub_dataformat
#define REG_PCM_SUB_START_ADDRESS               subbc_start_address
#define REG_PCM_SUB_END_ADDRESS                 subbc_end_address
#define REG_PCM_SUB_WRITE_ADDRESS               subbc_write_address
#define REG_PCM_SUB_READ_ADDRESS                subbc_read_address
#define REG_PCM_SUB_ALMOST_LEVEL                subbc_almost_empty_level
#define REG_PCM_SUB_UNIT_SIZE                   subbc_unit_interrupt_level

#define REG_SPDIF_DSPMODE                       spdifbc_ctrl
#define FLD_SPDIF_DSPMODE                       spdif_dspmode
#define REG_SPDIF_SWRESET                       spdifbc_ctrl
#define FLD_SPDIF_SWRESET                       spdif_swreset
#define REG_SPDIF_UNIT_INT_ENABLE               spdifbc_ctrl
#define FLD_SPDIF_UNIT_INT_ENABLE               spdif_uinten
#define REG_SPDIF_DATA_FORMAT                   spdifbc_ctrl
#define FLD_SPDIF_DATA_FORMAT                   spdif_dataformat
#define REG_SPDIF_START_ADDRESS                 spdifbc_start_address
#define REG_SPDIF_END_ADDRESS                   spdifbc_end_address
#define REG_SPDIF_WRITE_ADDRESS                 spdifbc_write_address
#define REG_SPDIF_READ_ADDRESS                  spdifbc_read_address
#define REG_SPDIF_ALMOST_LEVEL                  spdifbc_almost_empty_level
#define REG_SPDIF_UNIT_SIZE                     spdifbc_unit_interrupt_level

#ifdef SUPPORT_SOUNDBAR
#define REG_EARC_I2S_DSPMODE                    earc_ibc_ctrl
#define FLD_EARC_I2S_DSPMODE                    earc_i2s_dspmode
#define REG_EARC_I2S_SWRESET                    earc_ibc_ctrl
#define FLD_EARC_I2S_SWRESET                    earc_is2_swreset
#define REG_EARC_I2S_UNIT_INT_ENABLE            earc_ibc_ctrl
#define FLD_EARC_I2S_UNIT_INT_ENABLE            earc_i2s_uinten
#define REG_EARC_I2S_DATA_FORMAT                earc_ibc_ctrl
#define FLD_EARC_I2S_DATA_FORMAT                earc_i2s_dataformat
#define REG_EARC_I2S_START_ADDRESS              earc_i_start_address
#define REG_EARC_I2S_END_ADDRESS                earc_i_end_address
#define REG_EARC_I2S_WRITE_ADDRESS              earc_i_write_address
#define REG_EARC_I2S_READ_ADDRESS               earc_i_read_address
#define REG_EARC_I2S_ALMOST_LEVEL               earc_i_almost_empty_level
#define REG_EARC_I2S_UNIT_SIZE                  earc_i_unit_interrupt_level
#endif

#define REG_EARC_SPDIF0_DSPMODE                 earc_sbc0_ctrl
#define FLD_EARC_SPDIF0_DSPMODE                 earc_spdif0_dspmode
#define REG_EARC_SPDIF0_SWRESET                 earc_sbc0_ctrl
#define FLD_EARC_SPDIF0_SWRESET                 earc_spdif0_swreset
#define REG_EARC_SPDIF0_UNIT_INT_ENABLE         earc_sbc0_ctrl
#define FLD_EARC_SPDIF0_UNIT_INT_ENABLE         earc_spdif0_uinten
#define REG_EARC_SPDIF0_DATA_FORMAT             earc_sbc0_ctrl
#define FLD_EARC_SPDIF0_DATA_FORMAT             earc_spdif0_dataformat
#define REG_EARC_SPDIF0_START_ADDRESS           earc_s0_start_address
#define REG_EARC_SPDIF0_END_ADDRESS             earc_s0_end_address
#define REG_EARC_SPDIF0_WRITE_ADDRESS           earc_s0_write_address
#define REG_EARC_SPDIF0_READ_ADDRESS            earc_s0_read_address
#define REG_EARC_SPDIF0_ALMOST_LEVEL            earc_s0_almost_empty_level
#define REG_EARC_SPDIF0_UNIT_SIZE               earc_s0_unit_interrupt_level

#define REG_EARC_SPDIF1_DSPMODE                 earc_sbc1_ctrl
#define FLD_EARC_SPDIF1_DSPMODE                 earc_spdif1_dspmode
#define REG_EARC_SPDIF1_SWRESET                 earc_sbc1_ctrl
#define FLD_EARC_SPDIF1_SWRESET                 earc_spdif1_swreset
#define REG_EARC_SPDIF1_UNIT_INT_ENABLE         earc_sbc1_ctrl
#define FLD_EARC_SPDIF1_UNIT_INT_ENABLE         earc_spdif1_uinten
#define REG_EARC_SPDIF1_DATA_FORMAT             earc_sbc1_ctrl
#define FLD_EARC_SPDIF1_DATA_FORMAT             earc_spdif1_dataformat
#define REG_EARC_SPDIF1_START_ADDRESS           earc_s1_start_address
#define REG_EARC_SPDIF1_END_ADDRESS             earc_s1_end_address
#define REG_EARC_SPDIF1_WRITE_ADDRESS           earc_s1_write_address
#define REG_EARC_SPDIF1_READ_ADDRESS            earc_s1_read_address
#define REG_EARC_SPDIF1_ALMOST_LEVEL            earc_s1_almost_empty_level
#define REG_EARC_SPDIF1_UNIT_SIZE               earc_s1_unit_interrupt_level

#define REG_EARC_SPDIF2_DSPMODE                 earc_sbc2_ctrl
#define FLD_EARC_SPDIF2_DSPMODE                 earc_spdif2_dspmode
#define REG_EARC_SPDIF2_SWRESET                 earc_sbc2_ctrl
#define FLD_EARC_SPDIF2_SWRESET                 earc_spdif2_swreset
#define REG_EARC_SPDIF2_UNIT_INT_ENABLE         earc_sbc2_ctrl
#define FLD_EARC_SPDIF2_UNIT_INT_ENABLE         earc_spdif2_uinten
#define REG_EARC_SPDIF2_DATA_FORMAT             earc_sbc2_ctrl
#define FLD_EARC_SPDIF2_DATA_FORMAT             earc_spdif2_dataformat
#define REG_EARC_SPDIF2_START_ADDRESS           earc_s2_start_address
#define REG_EARC_SPDIF2_END_ADDRESS             earc_s2_end_address
#define REG_EARC_SPDIF2_WRITE_ADDRESS           earc_s2_write_address
#define REG_EARC_SPDIF2_READ_ADDRESS            earc_s2_read_address
#define REG_EARC_SPDIF2_ALMOST_LEVEL            earc_s2_almost_empty_level
#define REG_EARC_SPDIF2_UNIT_SIZE               earc_s2_unit_interrupt_level

#define REG_EARC_SPDIF3_DSPMODE                 earc_sbc3_ctrl
#define FLD_EARC_SPDIF3_DSPMODE                 earc_spdif3_dspmode
#define REG_EARC_SPDIF3_SWRESET                 earc_sbc3_ctrl
#define FLD_EARC_SPDIF3_SWRESET                 earc_spdif3_swreset
#define REG_EARC_SPDIF3_UNIT_INT_ENABLE         earc_sbc3_ctrl
#define FLD_EARC_SPDIF3_UNIT_INT_ENABLE         earc_spdif3_uinten
#define REG_EARC_SPDIF3_DATA_FORMAT             earc_sbc3_ctrl
#define FLD_EARC_SPDIF3_DATA_FORMAT             earc_spdif3_dataformat
#define REG_EARC_SPDIF3_START_ADDRESS           earc_s3_start_address
#define REG_EARC_SPDIF3_END_ADDRESS             earc_s3_end_address
#define REG_EARC_SPDIF3_WRITE_ADDRESS           earc_s3_write_address
#define REG_EARC_SPDIF3_READ_ADDRESS            earc_s3_read_address
#define REG_EARC_SPDIF3_ALMOST_LEVEL            earc_s3_almost_empty_level
#define REG_EARC_SPDIF3_UNIT_SIZE               earc_s3_unit_interrupt_level

#ifdef SUPPORT_SOUNDBAR
#define REG_PCM_SUB1_DSPMODE                     sub1bc_ctrl
#define FLD_PCM_SUB1_DSPMODE                     pcm_sub1_dspmode
#define REG_PCM_SUB1_SWRESET                     sub1bc_ctrl
#define FLD_PCM_SUB1_SWRESET                     pcm_sub1_swreset
#define REG_PCM_SUB1_UNIT_INT_ENABLE             sub1bc_ctrl
#define FLD_PCM_SUB1_UNIT_INT_ENABLE             pcm_sub1_uniten
#define REG_PCM_SUB1_DATA_FORMAT                 sub1bc_ctrl
#define FLD_PCM_SUB1_DATA_FORMAT                 pcm_sub1_dataformat
#define REG_PCM_SUB1_START_ADDRESS               sub1bc_start_address
#define REG_PCM_SUB1_END_ADDRESS                 sub1bc_end_address
#define REG_PCM_SUB1_WRITE_ADDRESS               sub1bc_write_address
#define REG_PCM_SUB1_READ_ADDRESS                sub1bc_read_address
#define REG_PCM_SUB1_ALMOST_LEVEL                sub1bc_almost_empty_level
#define REG_PCM_SUB1_UNIT_SIZE                   sub1bc_unit_interrupt_level
#endif

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_hal_bc,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_hal_bc,fmt,##args)
#define info(fmt,args...)   logm_info(aud_hal_bc,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_hal_bc,fmt,##args)
#define warn(fmt,args...)   logm_warning(aud_hal_bc,fmt,##args)
#define error(fmt,args...)  logm_error(aud_hal_bc,fmt,##args)

#define SET_REGISTER(_name, _value)     \
do {                                                                            \
    AUD_REG_Wr (PERI_CTRL, REG_##_name, _value);                                     \
} while (0)

#define SET_FEILD(_name, _value)        \
do {                                                                            \
    AUD_REG_RdFL (PERI_CTRL, REG_##_name);                                           \
    AUD_REG_WrFd (PERI_CTRL, REG_##_name, FLD_##_name, _value);                      \
    AUD_REG_WrFL (PERI_CTRL, REG_##_name);                                           \
} while (0)

#define CONFIG_FUNC_NAME(_bc)    _config_bc_##_bc
#define CONFIG_FUNC_DECLARATION(_bc)    \
static void CONFIG_FUNC_NAME(_bc) (struct bc_buffer *conf, union bc_conf_opt *opt)
#define CONFIG_FUNC_DEFINE(_bc)         \
CONFIG_FUNC_DECLARATION(_bc)                                                    \
{                                                                               \
    uint32_t start_addr = aud_hal_phys_to_aud_bus (conf->base);                 \
    uint32_t end_addr = aud_hal_phys_to_aud_bus (conf->base + conf->size);      \
    SET_FEILD(_bc##_DSPMODE, 0);                                                \
    SET_FEILD(_bc##_SWRESET, 1);                                                \
    SET_FEILD(_bc##_UNIT_INT_ENABLE, 1);                                        \
    SET_FEILD(_bc##_DATA_FORMAT, conf->format);                                 \
    SET_REGISTER(_bc##_START_ADDRESS, start_addr);                              \
    SET_REGISTER(_bc##_END_ADDRESS, end_addr);                                  \
    if (opt->in) {                                                              \
        SET_REGISTER(_bc##_READ_ADDRESS, start_addr);                           \
    } else {                                                                    \
        SET_REGISTER(_bc##_WRITE_ADDRESS, start_addr);                          \
    }                                                                           \
    SET_REGISTER(_bc##_ALMOST_LEVEL, 0);                           \
    SET_REGISTER(_bc##_UNIT_SIZE, conf->unit_size);                             \
    SET_FEILD(_bc##_SWRESET, 0);                                                \
}

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

enum bc_list
{
    BC_TP0,
    BC_TP1,
    BC_SAI0,
    BC_SAI1,
    BC_SAI2,
#ifdef SUPPORT_SOUNDBAR
    BC_SAI4,
    BC_AEC_SAI,
#endif
    BC_SPEAKER,
    BC_HEADPHONE,
    BC_SPDIF,
#ifdef SUPPORT_SOUNDBAR
    BC_EARC_I2S,
    BC_PC,
#else
    BC_EARC_SPDIF0,
    BC_EARC_SPDIF1,
    BC_EARC_SPDIF2,
    BC_EARC_SPDIF3,
#endif
};

/**
 * @brief
 * Structure for bc configuration
 *
 * @details
 * bc 설정을 위한 configuration
 */
struct bc_buffer
{
    phys_addr_t base;
    unsigned int size;
    unsigned int unit_size;
    unsigned int format;
};

union bc_conf_opt
{
    bool in;
    uint32_t reg_offs;
};

struct bc_config
{
    const char *name;
    void (*config_func) (struct bc_buffer * conf, union bc_conf_opt * opt);
    struct bc_buffer buffer;
    union bc_conf_opt option;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/
logm_define (aud_hal_bc, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
CONFIG_FUNC_DECLARATION (TP0);
CONFIG_FUNC_DECLARATION (TP1);
CONFIG_FUNC_DECLARATION (SAI0);
CONFIG_FUNC_DECLARATION (SAI1);
CONFIG_FUNC_DECLARATION (SAI2);
#ifdef SUPPORT_SOUNDBAR
CONFIG_FUNC_DECLARATION (SAI4);
CONFIG_FUNC_DECLARATION (AEC_SAI);
#endif
CONFIG_FUNC_DECLARATION (PCM_MAIN);
CONFIG_FUNC_DECLARATION (PCM_SUB);
CONFIG_FUNC_DECLARATION (SPDIF);
#ifdef SUPPORT_SOUNDBAR
CONFIG_FUNC_DECLARATION (EARC_I2S);
CONFIG_FUNC_DECLARATION (PCM_SUB1);
#else
CONFIG_FUNC_DECLARATION (EARC_SPDIF0);
CONFIG_FUNC_DECLARATION (EARC_SPDIF1);
CONFIG_FUNC_DECLARATION (EARC_SPDIF2);
CONFIG_FUNC_DECLARATION (EARC_SPDIF3);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct bc_config bc_configs[] = {
    /* *INDENT-OFF* */
    [BC_TP0]         = { "bc-tp0",      CONFIG_FUNC_NAME (TP0),         { 0x00,     8192,    256, 0 }, { .in = true } },
    [BC_TP1]         = { "bc-tp1",      CONFIG_FUNC_NAME (TP1),         { 0x00,     8192,    256, 0 }, { .in = true } },
    [BC_SAI0]        = { "bc-sai0",     CONFIG_FUNC_NAME (SAI0),        { 0x00,    65536,   1024, 3 }, { .in = true } },
    [BC_SAI1]        = { "bc-sai1",     CONFIG_FUNC_NAME (SAI1),        { 0x00,    65536,   1024, 3 }, { .in = true } },
    [BC_SAI2]        = { "bc-sai2",     CONFIG_FUNC_NAME (SAI2),        { 0x00,     1024,    256, 3 }, { .in = true } },
#ifdef SUPPORT_SOUNDBAR
    [BC_SAI4]        = { "bc-sai4",     CONFIG_FUNC_NAME (SAI4),        { 0x00,    64512,    768, 3 }, { .in = true } },
    [BC_AEC_SAI]     = { "bc-aec-sai",  CONFIG_FUNC_NAME (AEC_SAI),     { 0x00,    65536,   1024, 3 }, { .in = true } },
    [BC_SPEAKER]     = { "bc-speaker",  CONFIG_FUNC_NAME (PCM_MAIN),    { 0x00,    32768,   1024, 3 }, { .in = false } },
    [BC_HEADPHONE]   = { "bc-hp",       CONFIG_FUNC_NAME (PCM_SUB),     { 0x00,     8192,    256, 3 }, { .in = false } },
    [BC_SPDIF]       = { "bc-spdif",    CONFIG_FUNC_NAME (SPDIF),       { 0x00,     4096,    256, 3 }, { .in = false } },
    [BC_EARC_I2S]    = { "bc-earc-i",   CONFIG_FUNC_NAME (EARC_I2S),    { 0x00,    32768,   1024, 3 }, { .in = false } },
    [BC_PC]          = { "bc-pc",       CONFIG_FUNC_NAME (PCM_SUB1),    { 0x00,     8192,    256, 3 }, { .in = false } },
#else
    [BC_SPEAKER]     = { "bc-speaker",  CONFIG_FUNC_NAME (PCM_MAIN),    { 0x00,     8192,    512, 3 }, { .in = false } },
    [BC_HEADPHONE]   = { "bc-hp",       CONFIG_FUNC_NAME (PCM_SUB),     { 0x00,     4096,    256, 3 }, { .in = false } },
    [BC_SPDIF]       = { "bc-spdif",    CONFIG_FUNC_NAME (SPDIF),       { 0x00,     4096,    256, 3 }, { .in = false } },
    [BC_EARC_SPDIF0] = { "bc-earc-s0",  CONFIG_FUNC_NAME (EARC_SPDIF0), { 0x00,    16384,   1024, 3 }, { .in = false } },
    [BC_EARC_SPDIF1] = { "bc-earc-s1",  CONFIG_FUNC_NAME (EARC_SPDIF1), { 0x00,    16384,   1024, 3 }, { .in = false } },
    [BC_EARC_SPDIF2] = { "bc-earc-s2",  CONFIG_FUNC_NAME (EARC_SPDIF2), { 0x00,    16384,   1024, 3 }, { .in = false } },
    [BC_EARC_SPDIF3] = { "bc-earc-s3",  CONFIG_FUNC_NAME (EARC_SPDIF3), { 0x00,    16384,   1024, 3 }, { .in = false } },
#endif
    /* *INDENT-ON* */
};

/*==============================================================================
    Implementation Group
==============================================================================*/

int aud_hal_bc_init (void)
{
    int i;

    AUD_REG_Wr (DSP_CTRL, dsp0_pwaitmode, 0x0);

    for (i = 0; i < ARRAY_SIZE (bc_configs); i++)
    {
        struct bc_config *conf = bc_configs + i;

        if (!conf->buffer.base)
        {
            conf->buffer.base = hma_alloc_user ("audio_buffer", conf->buffer.size, 256, conf->name);
            if (!conf->buffer.base)
            {
                error ("cannot allocate \"%s\". size %d\n", conf->name, conf->buffer.size);
                continue;
            }
        }

        conf->config_func (&conf->buffer, &conf->option);
    }

    // Set BC for speaker mode to 4-channels
    /* ***************************************************************
     * 0: 1ch, 1: 2ch, ~ 7: 8ch
     * ***************************************************************/
    AUD_REG_Wr (PERI_CTRL, mainbc_chnum, 0x3);
    /* ***************************************************************
     * HW: L(0) R(1) Ls(2) Rs(3) C(4) LF(5) Lr(6) Rr(7) = 0x76543210
     * FW: L(0) R(1) Ls(2) Rs(3) Lr(6) Rr(7) C(4) LF(5) = 0x54763210
     * ***************************************************************/
    AUD_REG_Wr (PERI_CTRL, mainbc_chset, 0x3210);

#ifdef SUPPORT_SOUNDBAR
    AUD_REG_Wr (PERI_CTRL, earc_i_chnum, 0x7);
    AUD_REG_Wr (PERI_CTRL, earc_i_chset, 0x10765432);
#endif

    return 0;
}

void aud_hal_bc_exit (void)
{
}

int aud_hal_bc_buffer_init (const char *name)
{
    int i;

    for (i = 0; i < ARRAY_SIZE (bc_configs); i++)
    {
        struct bc_config *conf = bc_configs + i;

        if (strcmp (conf->name, name))
        {
            continue;
        }

        if (!conf->buffer.base)
        {
            error ("bc buffer %s is not allocated.\n", name);
            return -1;
        }

        info ("\"%s\". base 0x%p size %d\n", conf->name, (void *) conf->buffer.base,
            conf->buffer.size);

        conf->config_func (&conf->buffer, &conf->option);
        break;
    }

    return 0;
}

int aud_hal_bc_enable (const char *name)
{
    int i;

    for (i = 0; i < ARRAY_SIZE (bc_configs); i++)
    {
        struct bc_config *conf = bc_configs + i;

        if (strcmp (conf->name, name))
        {
            continue;
        }

        if (conf->buffer.base)
        {
            return -1;
        }

        conf->buffer.base = hma_alloc_user ("audio_buffer", conf->buffer.size, 256, conf->name);
        if (!conf->buffer.base)
        {
            error ("cannot allocate \"%s\". size %d\n", conf->name, conf->buffer.size);
            return -1;
        }

        conf->config_func (&conf->buffer, &conf->option);
        break;
    }

    return 0;
}

int aud_hal_bc_disable (const char *name)
{
    int i;

    for (i = 0; i < ARRAY_SIZE (bc_configs); i++)
    {
        struct bc_config *conf = bc_configs + i;

        if (strcmp (conf->name, name))
        {
            continue;
        }

        if (conf->buffer.base)
        {
            hma_free ("audio_buffer", conf->buffer.base);
            conf->buffer.base = 0x00;
        }

        break;
    }

    if (i == ARRAY_SIZE (bc_configs))
    {
        warn ("unknown name for bc %s\n", name);
        return -1;
    }

    return 0;
}

/* *INDENT-OFF* */
CONFIG_FUNC_DEFINE (TP0)
CONFIG_FUNC_DEFINE (TP1)
CONFIG_FUNC_DEFINE (SAI0)
CONFIG_FUNC_DEFINE (SAI1)
CONFIG_FUNC_DEFINE (SAI2)
#ifdef SUPPORT_SOUNDBAR
CONFIG_FUNC_DEFINE (SAI4)
CONFIG_FUNC_DEFINE (AEC_SAI)
#endif
CONFIG_FUNC_DEFINE (PCM_MAIN)
CONFIG_FUNC_DEFINE (PCM_SUB)
CONFIG_FUNC_DEFINE (SPDIF)
#ifdef SUPPORT_SOUNDBAR
CONFIG_FUNC_DEFINE (EARC_I2S)
CONFIG_FUNC_DEFINE (PCM_SUB1)
#else
CONFIG_FUNC_DEFINE (EARC_SPDIF0)
CONFIG_FUNC_DEFINE (EARC_SPDIF1)
CONFIG_FUNC_DEFINE (EARC_SPDIF2)
CONFIG_FUNC_DEFINE (EARC_SPDIF3)
#endif
/* *INDENT-ON* */
