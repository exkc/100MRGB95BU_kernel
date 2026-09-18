SNDOUT
######

Introduction
************

This document describes the Sound Out module (hereafter referred to as SNDOUT) in the kernel space. The document gives an overview of the SNDOUT module and provides details about its functionalities and implementation requirements.

Revision History
================

======= ========== ========================== =======
Version Date       Changed by                 Comment
======= ========== ========================== =======
1.0.28  2025-06-08 yookyung.uh@lge.com        Add DAFC feature requirements
1.0.27  2025-03-26 kwangshik.kim@lge.com      Add APIs for webOS Soundbar
1.0.26  2025-01-02 yookyung.uh@lge.com        Add MICOM_PIN_MODE
1.0.25  2024-06-05 sungmo.yang@lge.com        Add SNDOUT_WOWCAST_ONOFF, SNDOUT_WOWCAST_OUTPUT_TYPE
1.0.24  2024-04-09 kwangshik.kim@lge.com      Add enum for DAFC Output type and related APIs
1.0.23  2024-04-19 kwangshik.kim@lge.com      Refine description
1.0.22  2024-04-04 myeonggyu.choe@lge.com     Add DOLBY_MS12_IIDK_VERSION, SNDOUT_EARC_MS12_SP50_ONOFF
1.0.21  2024-01-23 seonghyun.cha@lge.com      Add enum for line out sound output (for hotel)
1.0.20  2023-11-13 minjae.jun@lge.com         Applied new document template.
1.0.19  2023-07-12 wookchan.kim@lge.com       Add ARC/eARC passThrough requirement
1.0.18  2022-07-29 jungyong.choi@lge.com      Update Overall Description and Performance
1.0.17  2022-03-29 wookchan.kim@lge.com       Add ARC requirement
1.0.16  2021-05-14 kwangshik.kim@lge.com      Add new API "SNDOUT_CAPTURE_PATH_POINT"
1.0.15  2021-05-06 hyungyong.park@lge.com     Add new sndout structure and api for arc/optic
1.0.14  2020-04-21 kwangshik.kim@lge.com      Add enum for SE + HDMI ARC sound output
1.0.13  2020-04-09 jungyong.choi@lge.com      Add new output in SNDOUT
1.0.12  2019-07-04 kenneth0.park@lge.com      Modify description of "Sndout ARC OnOff"
                                              and "Sndout EARC OnOff"
======= ========== ========================== =======

Terminology
===========

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

================================ ==================================
Definition                       Description
================================ ==================================
AMIXER                           Audio Mixer; Audio PCM on input resource
SNDOUT                           Sound Output; devices such as TV speakers, ARC, and headphones
ARC                              Audio Return Channel
ES                               Elementary Stream
Sound Engine                     If the audio data is passed through Sound Engine, sound effect Dolby produces is applied.
LGSE                             | LG Sound Engine
                                 | One of the sound engine produced by LG SIC
DAP                              | Dolby Audio Post-processing
                                 | One of the sound engine produced by Dolby
================================ ==================================

Technical Assistance
====================

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:

=============== ==========
Module          Owner
=============== ==========
sndout          jungyong.choi@lge.com
=============== ==========

Overview
********

General Description
===================
The SNDOUT module is responsible for audio output. It controls the input/output connection and handles settings for the main audio, re-encoding format, and copyright bit.

* Control of input/output connection : Define the audio data flow so that sound can be output by connecting the audio input and output desired by the user.
* Setting for the main audio : From an input that has one or more audio sources, determines which audio to connect to the output.
* Setting for re-encoding format : Change the audio format to match the audio output device.
* Setting for copyright bit : The copyright signal is transmitted to the output according to the audio signal for which the copyright is set.


Architecture
============

Driver Architecture
-------------------
The diagram below illustrates the main modules of the webOS audio framework, which is based on ALSA, and shows their interactions.

.. image:: resources/audio-overview.png
  :width: 100%
  :alt: ADEC Overview


Audio SNDOUT is responsible for the output of audio, providing control of the
input and output resources and the current output state.

  ex) Output audio to N (Source) x M (Output)

  The output connection of SNDOUT is made by resource open / close / connect /
  disconnect of PATH and is operated by pipeline controller when pipeline
  creation / termination / stop

  Output mute of SNDOUT is done by input mute and output mute of MUTE, and is
  used by intention of app or internal module.

  In addition to that, SNDOUT is responsible for audio specific output related
  settings.

Input resource

====================================== ==================================
Definition                             Description
====================================== ==================================
COMMON_INPUT_ADEC_EXT_TYPE0            Port Number for INPUT: UINT16
COMMON_INPUT_AMIXER_EXT_TYPE1          Port Number for INPUT: UINT16
====================================== ==================================

The output resource

====================================== ==================================
Definition                             Description
====================================== ==================================
:c:macro:`COMMON_SPK`                  SoundEngine + TV Speaker: Receives PCM data and controls AMP with I2S
:c:macro:`COMMON_OPTIC`                Receives ES or PCM data and transmits SPDIF format data to external output
:c:macro:`COMMON_OPTIC_LG`             | SPDIF + SPDIF Modify CSD area (LG Spec both TV and CAV)
                                       | => Control the Volume, Mute, and Power on / off of LG Soundbar
:c:macro:`COMMON_BLUETOOTH`            The audio data is transmitted to BT or Wifi through the PCM uploading block at the rear of the mixer.
:c:macro:`COMMON_HP`                   The audio data is transmitted to Head Phone
:c:macro:`COMMON_ARC`                  The audio data is transmitted to HDMI ARC
:c:macro:`COMMON_SE_BT`                SoundEngine + Bluetooth
:c:macro:`COMMON_WISA`                 | Output via WISA Importantly, sound output must operate independently of the Input Source.
                                       | As an example, input decoders should operate
                                       | according to the connection of SNDOUT regardless of Play / Pause / Stop.
:c:macro:`COMMON_CAPTURE`              This output is for capture to send to mobile device.
:c:macro:`COMMON_SE_ARC`               SoundEngine + HDMI ARC
:c:macro:`COMMON_SE_BT_SUR`            SoundEngine + Bluetooth for Surround Effect
:c:macro:`COMMON_LINE_OUT`             This output is for line out2 in STB models (for hotel)
:c:macro:`COMMON_WOWCAST`              The audio data is transmitted to wowcast (supported Wifi external speaker)
:c:macro:`COMMON_DAP_HP_BT`            | The audio data is transmitted to BT output with DAP.
                                       | Only DAP supporting BT Headphone (or Speaker) would get the audio data
:c:macro:`COMMON_DAFC`                 | This output is for Dolby Atmos Flex Connect (DAFC).
                                       | After processed by FlexRenderer, the audio data would be captured and wirelessly transmitted to multiple external speakers.
                                       | To transmit audio data, various protocol would be used such as Wi-Fi, Bluetooth, and so on.
                                       | The audio data could be played to TV Speaker with time synchronization by the transmission protocol with delay settings
====================================== ==================================


Requirements
************

Functional Requirements
=======================

The data types and functions used in this module are described in the Data Types and Functions in the API List.


Control of Input/Output connection
==================================

The only information we know about the input at SNDOUT is the input resource.
In other words, if the SNDOUT is connected after the decoder is played, the sound should be output after SNDOUT is connected,
If the decoder is played after SNDOUT is connected, the sound should be output after the decoder is played.

ARC IP should be not enable before connecting ARC activation. Block outputting ARC by setting ARC Pin disable as default.

In Dolby MS12, 32kHz DDP is not supported. It is out of Spec.
But, for avoiding no sound outputting, this type of input should be trans-encoded to 48kHz while digital sound output is passThrough.

Below two functions are following below mapping table

  * :type:`sndout_optic_mode_ext_type_t`

    .. image:: resources/PassThrough_Mapping_Table-OPTIC.png
      :width: 100%
      :alt: ADEC Overview

  * :type:`sndout_arc_mode_ext_type_t`

    .. image:: resources/PassThrough_Mapping_Table-ARC.png
      :width: 100%
      :alt: ADEC Overview

Decoder Speaker configuration
=============================

Speaker configuration to notify to audio decoder
It would be set for dolby decoder to map decoder's output channel info to speakers channel info

* For DAFC output, FlexRenderer would make 7.1ch audio output and channel mapping would be done by FlexRenderer
* For Non-DAFC output, dolby decoder would make audio output channel according to :c:macro:`DECODER_SPK_CONFIGURATION` and sound engine's input/output also match channel info according to :c:macro:`DECODER_SPK_CONFIGURATION`

| :c:macro:`DECODER_SPK_CONFIGURATION` will be called with :type:`decoder_spk_configuration_type_t`,
| and the type is referred to Dolby's Documentation.
| In the documentation, "e" indicates Dolby Atmos Enabled speaker, which means an upward-facing speaker.
| So :type:`decoder_spk_configuration_type_t` consists of below speaker option

=============== =========================================
Speaker option  Summary
=============== =========================================
lr              Left/Right speaker (default state: on)
c               Center speaker
lfe             Low-frequency effects channel
lrs             Left/Right surround speakers
lrrs            Left/Right rear surround speakers
lrtf            Left/Right top front speakers
lrtm            Left/Right top middle speakers
lrtr            Left/Right top rear speakers
lrfh            Left/Right front height speakers
lrrh            Left/Right rear height speakers
lre             Left/Right Dolby Atmos enabled speakers
lrse            Left/Right surround Dolby Atmos enabled speakers
lrrse           Left/Right rear surround Dolby Atmos enabled speakers
lrsc            Left/Right screen speakers
lrc             Left/Right center speakers
lrw             Left/Right wide speakers
lrs1            Left/Right surround 1 speakers
lrs2            Left/Right surround 2 speakers
lrrs1           Left/Right rear surround 1 speakers
lrrs2           Left/Right rear surround 2 speakers
lrcs            Left/Right center surround speakers
cs              Center surround speaker
sh              Single height speaker
=============== =========================================

Quality and Constraints
=======================

Performance
-----------

All alsa api for sndout should be returned within 10 msec

Design Constraints
------------------

Each sound output should be controlled without dependency


Implementation
**************

This section provides materials that are useful for SNDOUT implementation.

- The File Location section provides the location of the Git repository where you can get the header file in which the interface for the SNDOUT implementation is defined.
- The API List section provides a brief summary of SNDOUT APIs that you must implement.

File Location
=============

The SNDOUT interfaces are defined in the alsa-ext-sndout.h header file, which can be obtained from https://swfarmhub.lge.com/.

- Git repository: bsp/ref/alsa-ext-renderer-header

API List
========

The SNDOUT driver implementation must adhere to the interface specifications defined and implements its functions. Refer to the API Reference for more details.

Data Types
----------

Extended Enumerations
^^^^^^^^^^^^^^^^^^^^^
============================================================= ==================================
Data Type                                                     Description
============================================================= ==================================
:type:`sndout_optic_mode_ext_type_t`                          Defined in File **alsa-ext-sndout.h**
:type:`sndout_arc_mode_ext_type_t`                            Defined in File **alsa-ext-sndout.h**
:type:`sndout_optic_copyprotection_ext_type_t`                Defined in File **alsa-ext-sndout.h**
:type:`sndout_arc_copyprotection_ext_type_t`                  Defined in File **alsa-ext-sndout.h**
:type:`sndout_spk_output_ext_type_t`                          Defined in File **alsa-ext-sndout.h**
:type:`sndout_output_set_type_t`                              Defined in File **alsa-ext-sndout.h**
:type:`sndout_output_codec_type_t`                            Defined in File **alsa-ext-sndout.h**
:type:`sndout_output_channel_num_t`                           Defined in File **alsa-ext-sndout.h**
:type:`sndout_output_sample_rate_t`                           Defined in File **alsa-ext-sndout.h**
:type:`sndout_output_mix_option_t`                            Defined in File **alsa-ext-sndout.h**
:type:`sndout_capture_path_t`                                 Defined in File **alsa-ext-sndout.h**
:type:`sndout_dafc_output_type_t`                             Defined in File **alsa-ext-sndout.h**
:type:`micom_pin_mode_t`                                      Defined in File **alsa-ext-sndout.h**
:type:`sndout_spk_sampling_frequency_type_t`                  Defined in File **alsa-ext-sndout.h**
:c:macro:`SNDOUT_SPK_LOCAL_CHANNEL_MAX_NUM`                   Defined in File **alsa-ext-sndout.h**
:type:`decoder_spk_configuration_type_t`                      Defined in File **alsa-ext-sndout.h**
============================================================= ==================================

Functions
---------

Extended functions
^^^^^^^^^^^^^^^^^^

============================================= ===============================================
Funtion                                       Description
============================================= ===============================================
:c:macro:`SNDOUT_OPEN`                        Open sndout device
:c:macro:`SNDOUT_CLOSE`                       Close sndout device
:c:macro:`SNDOUT_CONNECT`                     Connect sndout device with input
:c:macro:`SNDOUT_DISCONNECT`                  Disconnect sndout device
:c:macro:`SNDOUT_MAINAUDIO_OUTPUT`            Put/get MainAudio Output
:c:macro:`SNDOUT_SPDIF_OUTPUTTYPE`            Put/get Spdif OutputType
:c:macro:`SNDOUT_SPDIF_CATERGORYCODE`         Put/get Spdif category
:c:macro:`SNDOUT_SPDIF_COPYPROTECTIONINFO`    Put/get Spdif copy protection type
:c:macro:`SNDOUT_OPTIC_LIGHTONOFF`            Put/get Optic Light OnOff
:c:macro:`SNDOUT_ARC_ONOFF`                   Put/get ARC OnOff
:c:macro:`SNDOUT_OPTIC_LG`                    Put/get Sndout Command
:c:macro:`SNDOUT_SPK_OUTPUT`                  I2S Output Channel number for 2 or 4 multi-channel.
:c:macro:`SNDOUT_CAPTURE_DISABLE`             If it’s value is on(true), get NULL audio data from alsa capture
:c:macro:`SNDOUT_CAPTURE_INPUT_TIMECLOCK`     | Get inputTimeClock and inputBitrate for calculate Resampling value.
                                              | This function working with Sndout Open :c:macro:`COMMON_WISA`
:c:macro:`SNDOUT_CAPTURE_OUTPUT_RESAMPLING`   Set Resampling frequency on runtime for WISA. This function working with Sndout Open “COMMON_WISA”
:c:macro:`SNDOUT_EARC_ONOFF`                  Put/get EARC OnOff
:c:macro:`SNDOUT_WOWCAST_ONOFF`               Put/get WOWCAST OnOff
:c:macro:`SNDOUT_EARC_OUTPUT_TYPE`            Put/get EARC Outputtype
:c:macro:`SNDOUT_EAC3_ATMOS_ENCODE_ONOFF`     Put/get eAC3 ATMOS Encode OnOff
:c:macro:`SNDOUT_OPTIC_OUTPUT_TYPE`           Put/get OPTIC Outputtype
:c:macro:`SNDOUT_ARC_OUTPUT_TYPE`             Put/get ARC Outputtype
:c:macro:`SNDOUT_WOWCAST_OUTPUT_TYPE`         Put/get WOWCAST Outputtype
:c:macro:`SNDOUT_CAPTURE_PATH_POINT`          Put/get capture path point
:c:macro:`SNDOUT_EARC_MS12_SP50_ONOFF`        Put/get eARC MS12 SP50 OnOff
:c:macro:`DOLBY_MS12_IIDK_VERSION`            Get Dolby ms12 iidk major and minor version
:c:macro:`SNDOUT_DAFC_OUTPUT_TYPE`            Put/get DAFC output type
:c:macro:`SNDOUT_CENTER_EXTRACTION_ONOFF`     Put/get Center Extraction OnOff
:c:macro:`INPUT_DOWNMIX_ENABLE`               Put/get Input DownMix Enable
:c:macro:`HW_BUFFER_WRITE_TIME`               Get HW Buffer Write Time
:c:macro:`AUDIO_BUFFER_LATENCY`               Get Audio Buffer Latency
:c:macro:`PLL_CONTROL_INFO`                   Get PLL Control Info
:c:macro:`STC_SYSTEM_MICOM_CLOCK_TIME`        Get STC SYSTEM MICOM Clock Time
:c:macro:`MICOM_PIN_MODE`                     Put/get Micom Pin Mode
:c:macro:`SNDOUT_SPK_SAMPLING_FREQUENCY`      Put/get Speaker's Sampling Frequency
:c:macro:`SNDOUT_SPK_MAX_OUTPUT_CHANNEL`      Put/get Speaker Maximum Output Channel
:c:macro:`DECODER_SPK_CONFIGURATION`          Put/get Speaker configuration to notify to audio decoder
============================================= ===============================================

Testing
*******
To test the implementation of the SNDOUT module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the SNDOUT module and verifies the kernel event operations for the module by using a test execution file.
For more information, see :doc:`SNDOUT`s SoCTS Unit Test manual </part4/socts/Documentation/source/producer-manual/producer-manual_alsa/producer-manual_alsa-sndout>`.


