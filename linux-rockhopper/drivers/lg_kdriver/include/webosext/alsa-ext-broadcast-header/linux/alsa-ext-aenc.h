/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_AENC_H
#define _ALSA_EXT_AENC_H

#define AENC_BUF_SIZE_MAX (10 * 1024)

/**
 * Data struct for each AENC callback
 */
typedef struct {
    unsigned long long pts; /**< PTS for each encoding packet */
    unsigned char pData[AENC_BUF_SIZE_MAX]; /**< pointer to Audio Data */
    unsigned int dataLen; /**< Audio Data Length */
} aenc_data_t;


/**
 * AENC encoding codec
 */
typedef enum {
    AENC_ENCODE_UNKNOWN = 0,
    AENC_ENCODE_MP3, /**< Encoding to MP3 codec */
    AENC_ENCODE_AAC, /**< Encoding to AAC codec */
    AENC_ENCODE_PCM /**< Encoding to PCM codec */
} aenc_encoding_format_t;


/**
 * AENC encoding bitrate
 */
typedef enum {
    AENC_BIT_UNKNOWN = 0, /**< NO set */
    AENC_BIT_48K, /**< Encoding bitrate to 48K */
    AENC_BIT_56K, /**< Encoding bitrate to 56K */
    AENC_BIT_64K, /**< Encoding bitrate to 64K */
    AENC_BIT_80K, /**< Encoding bitrate to 80K */
    AENC_BIT_112K, /**< Encoding bitrate to 112K */
    AENC_BIT_128K, /**< Encoding bitrate to 128K. default */
    AENC_BIT_160K, /**< Encoding bitrate to 160K */
    AENC_BIT_192K, /**< Encoding bitrate to 192K */
    AENC_BIT_224K, /**< Encoding bitrate to 224K */
    AENC_BIT_256K, /**< Encoding bitrate to 256K */
    AENC_BIT_320K, /**< Encoding bitrate to 320K */
} aenc_bitrate_t;

/**
 * @brief Set encoding parameter
 * @li priority : 2
 *
 * 1.decoder index : represent adec id to connect AENC.
 *
 * 2.codec : represent encoding audio format. The value can be set based on aenc_encoding_format_t. LG will set it as AENC_ENCODE_AAC. Others is optional.
 *
 * 3.bitrate : represent encoding bitrate. The value can be set based on aenc_bitrate_t.
 *
 * @b Pseudocode
 * @code
 * snd_ctl_elem_id_set_name      (pmId,  "Aenc Info");
 *
 * pmElem = snd_hctl_find_elem(pmHctl, pmId);

 * snd_ctl_elem_value_alloca     (&pmControl);
 * snd_ctl_elem_value_set_integer(pmControl, 0, 0);               // decoder index
 * snd_ctl_elem_value_set_integer(pmControl, 1, AENC_ENCODE_PCM); // codec
 * snd_hctl_elem_write           (pmElem, pmControl);
 * @endcode
 *
 *
 * @return 0 if it success. Otherwise:
 * @li negative     a negative error code on failure
 * @li positive     on success when value was changed
 */
#define AENC_INFO "Aenc Info"


/**
 * @brief Setting Encoding volume level. dB based on the original decoder output.
 * @li priority : 2
 *
 * data is unsigned 32bit and the meaning of each bytes below
 *
 * 1st : main volume , -127 ~ 30 dB
 *
 * 2nd : fine volumen , 1/16 db step , 0dB ~ 15/16 dB
 *
 * 3rd , 4th : reserved.
 *
 * example : 0x7F000000 ( 0dB ) , 0x8F000000 (16dB)
 * @b Pseudocode
 * @code
 * snd_ctl_elem_id_set_name(pmId,  "Aenc Volume");
 * pmElem = snd_hctl_find_elem(pmHctl, pmId);
 * snd_ctl_elem_value_set_integer(pmControl, 0, 0x800000); // volume setting
 * snd_hctl_elem_write(pmElem, pmControl);
 * @endcode
 *
 *
 * @return 0 if it success. Otherwise:
 * @li negative     a negative error code on failure
 * @li positive     on success when value was changed
 */
#define AENC_VOLUME "Aenc Volume"

/*
Read aenc pts
*/
#define AENC_PTS "Aenc PTS"

#endif
