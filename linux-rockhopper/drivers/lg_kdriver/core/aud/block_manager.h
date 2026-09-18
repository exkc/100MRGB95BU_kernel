/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file
 * @ingroup Base
 *
 *  header for audio block manager
 *
 *  @author Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.06.30
 *
 *  @addtogroup Base
 *  @{
 *  @}
 */

#ifndef _BLOCK_MANAGER_H_
#define _BLOCK_MANAGER_H_

#include "block.h"

/** @enum block type
 */
struct audio_block_impl
{
    const char *block_type;
    struct list_head list;

    int block_info_size;

    int preffered_processor; ///< processor that block preffer

    int (*constructor) (struct aud_block_info* block_info);
    void (*destructor) (struct aud_block_info *block_info);
    int (*pre_connect) (struct aud_block_info* block_info, int port, bool in);
    int (*post_connect) (struct aud_block_info* block_info, int port, bool in);
    int (*pre_disconnect) (struct aud_block_info* block_info, int port, bool in);
    int (*post_disconnect) (struct aud_block_info* block_info, int port, bool in);
    int (*suspend) (struct aud_block_info* block_info);
    int (*resume) (struct aud_block_info* block_info);
    int (*pre_reconnect) (struct aud_block_info* block_info);
    int (*post_reconnect) (struct aud_block_info* block_info);
};

int bm_init (void);
int bm_close (void);
int bm_suspend (void);
int bm_resume (void);
bool bm_get_suspended (void);
void bm_block_registry (struct audio_block_impl *block_impl);
struct aud_block_info *bm_get_block_info_by_index (const char *block_type, int index);
int bm_unregister_port_forward (struct aud_block_info *block_info, bool in, int port_block);
int bm_register_port_forward (struct aud_block_info *block_info, bool in, int port_block, struct apipeline *pipeline, int port_pipeline);
int bm_connect_block (struct aud_block_info *block_out, int port_out, struct aud_block_info *block_in, int port_in);
int bm_connect_block_reserved (struct aud_block_info *block_info_in, int port_in, const char *block_type_out, int index_out, int port_out);
int bm_connect_block_reserved_in (struct aud_block_info *block_info_out, int port_out, const char *block_type_in, int index_in, int port_in);
int bm_connect_block_reserved_out (    const char *block_type_out, int index_out, int port_out, struct aud_block_info *block_info_in, int port_in);
int bm_disconnect_block (    struct aud_block_info *block_info_in, int port_in);
int bm_disconnect_block_reserved (struct aud_block_info *block_info_in, int port_in);
int bm_remove_reserved (struct aud_block_info *block_info_in, int port, bool reserved_as_output);
struct aud_block_info *bm_create_block (const char *block_type, int index);
struct aud_block_info *bm_create_block_peer (const char *block_type, int index, struct aud_block_info *peer, bool peer_is_input);
int bm_destroy_block (struct aud_block_info *block_info);
unsigned int bm_get_block_head (struct aud_block_info *block_info);
unsigned int bm_get_block_tail (struct aud_block_info *block_info);
int bm_get_index_by_block_info (struct aud_block_info *block_info);
int bm_get_preffered_processor (struct aud_block_info *block_info);
int bm_set_preffered_processor (struct aud_block_info *block_info, int proc);
bool bm_is_connected (struct aud_block_info *block_info, int port, bool in);
bool bm_check_query_farm (struct aud_block_info *block_info, bool (*check_func) (struct aud_block_info *me, struct aud_block_info *other));
struct aud_block_info *bm_get_master_by_block_info (struct aud_block_info *block_info);
int bm_set_main_audio_decoder_index (int index);
bool bm_is_main_audio (struct aud_block_info *block_info);

#endif /* _BLOCK_MANAGER_H_ */
