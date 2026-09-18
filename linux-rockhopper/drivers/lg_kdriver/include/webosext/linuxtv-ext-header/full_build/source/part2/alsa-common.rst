Common
########

Introduction
************

| This document describes the ALSA common interface in the kernel space. The document gives an overview of the common interface and provides details about theirs functionalities and implementation requirements.

Revision History
================

======= ========== ===================== =======
Version Date       Changed by            Comment
======= ========== ===================== =======
1.0.7   2024-04-19 kwangshik.kim@lge.com Add DAFC play/capture device
1.0.6   2024-04-19 kwangshik.kim@lge.com Refine description
1.0.5   2023-11-15 minjae.jun@lge.com    Applied new document template.
1.0.4   2021-03-04 kwangshik.kim@lge.com Add enum for sound output capture path point
1.0.3   2020-02-12 kenneth0.park@lge.com Add description for devices.
1.0.2   2019-03-11 kenneth0.park@lge.com Add variable to Output.
                                         COMMON_SE_BT, COMMON_MAX_OUTPUT
======= ========== ===================== =======

Overview
*********

General Description
===================

The common module defines ENUM for input/output devices used in SNDOUT, DELAY, MUTE, GAIN.

For PCM devices such as the ALSA mixer among the input types, the functions
are described in the following list.

The common driver should support ALSA plugins like dnsoop, dmix ... etc.

=========== ================ ======================= ============ ============ =============== ============
Device Name Playback/Capture Usage                   Remark       Channel      Format          Bitrates
=========== ================ ======================= ============ ============ =============== ============
hw:0,0      Playback         GStreamer               PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,1      Playback         GStreamer               PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,2      Playback         GStreamer               PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,3      Playback         GStreamer               PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,4      Playback         GStreamer               PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,5      Playback         System                  PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,6      Playback         Pulse Audio             PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,7      Playback         Pulse Audio             PCM          2            S16_LE, S16_BE  44100, 48000
hw:0,8      Playback         TV SPK Out from         PCM          2            S16_LE, S16_BE  44100, 48000
                             DAFC
hw:0,10     Capture          BT, Wisa, BT_SPK        PCM          2, 6         S16_LE          48000
hw:0,11     Capture          AENC to DVR             Bitstream    N/A          N/A             Depend on ALSA driver
hw:0,12     Capture          Other Applications      PCM          2 ~ 8        S16_LE          48000
                             (dsnoop)
hw:0,13     Capture          Test                    PCM          2            S32_LE          44100, 48000
hw:0,14     Capture          WOWCAST                 Bitstream    2 ~ 8        S16_LE, S32_LE  Depend on ALSA driver
hw:0,15     Capture          DAFC                    PCM          2 ~ 8        S16_LE, S32_LE  44100, 48000
=========== ================ ======================= ============ ============ =============== ============

Implementation
**************

File Location
=============

The ALSA common interface is defined in the **alsa-ext-common.h** header file, which can be obtained from https://swfarmhub.lge.com/.

- Git repository: bsp/ref/linux-ext-header

API List
========

Data Types
----------

Extended Enumerations
^^^^^^^^^^^^^^^^^^^^^

================================= =====================
Data Type                         Description
================================= =====================
:type:`common_output_ext_type_t`  Sound output type
:type:`common_input_ext_type`     Input type for soundout
:type:`sndout_capture_path_t`     Sndout capture path
================================= =====================
