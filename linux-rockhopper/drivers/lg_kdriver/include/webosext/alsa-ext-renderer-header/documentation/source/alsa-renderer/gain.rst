Gain
####

Introduction
************

| This document describes the Audio Gain module in the kernel space. The document gives an overview of the Gain module and provides details about its functionalities and implementation requirements.

Revision History
================

======= ========== ===================== ====================
Version Date       Changed by            Describtion
======= ========== ===================== ====================
1.0.6   2024-06-05 sungmo.yang@lge.com   Add GAIN_INPUT_DURATION
1.0.5   2023-11-13 minjae.jun@lge.com    Applied new document template.
1.0.4   2022-07-25 cheolhwa.yoo@lge.com  Add performance/constraint requirement
1.0.3   2019-04-01 kenneth0.park@lge.com Modify Initial Value
======= ========== ===================== ====================

Terminology
===========

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

================================ ==================================
Definition                       Description
================================ ==================================
dB                               decibel
ALSA                             Advanced Linux Sound Architecture
AD                               Audio Description
================================ ==================================

Technical Assistance
====================

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:

=============== ==========
Module          Owner
=============== ==========
gain            cheolhwa.yoo@lge.com
=============== ==========


Overview
********

General Description
===================

The input gain and output gain have values for each input and output, and based on these values gain calculate the input gain
for the audio mixing operation of ADEC output and AMIXER output, and calculate the audio output gain to set the volume of a specific speaker.


Architecture
============

Driver Architecture
-------------------

The diagram below illustrates the main modules of the webOS audio framework, which is based on ALSA, and shows their interactions.
At the top right of the picture, there is an explanation of the color of the module that represents the input/output gain block.
The input gain is located in front of the MIXER, and the output gain exists for each output.

.. image:: resources/audio-overview.png
  :width: 100%
  :alt: ADEC Overview

In the TV Service Middleware, the volume sets the input/output gain value for
the input (ATV, DTV, HDMI, Music, Movie) selected by the user.
Audio Description Volume and the overall volume of the TV.

And cause difficult calculate float values, TV service middleware will change the value like below,
and then send it to ALSA driver.

.. code-block:: c

  //// mainVol, fineVol define by HW Side.
  /**
  * AUDIO Volume Structure
  * dB Scale     :     main, fine
  *   -127dB Min     : 0x00(-127dB)   0x00(0 dB)
  * - 125.9325 dB    : 0x01(-126 dB), 0x01(1/16 dB)
  * - 121.8125 dB    : 0x05(-122 dB), 0x03(3/16 dB)
  * -0.9375dB        : 0x7E(-1dB),    0x01(1/16dB)
  *    0 dB          : 0x7F(0 dB),    0x00(0 dB)
  *    30dB          : 0x9D(30dB),    0x00(0 dB)
  */
  typedef struct audio_volume
  {
      UINT8   mainVol;    // 1 dB step, -127 ~ +30 dB.
      UINT8   fineVol;    // 1/16 dB step, 0dB ~ 15/16dB
  } audio_volume_t;

  //// Define related constant
  /* define adec volume scale and step*/
  #define ADEC_MAIN_VOLUME_GAIN_0DB           0x7F
  #define ADEC_MAIN_VOLUME_GAIN_MUTE          0x00
  #define ADEC_FINE_VOLUME_GAIN_STEP          0x10
  #define ADEC_DRC_ON_VOLUME_GAIN_8DB         0x08

  /* define adec DSP volume value */
  #define ADEC_DSP_MAIN_VOLUME_GAIN_0DB       0x00800000
  #define ADEC_DSP_MAIN_VOLUME_GAIN_MUTE      0x00000000
  #define ADEC_DSP_MIX_VOLUME_GAIN_0DB        1024
  #define ADEC_DSP_MIX_VOLUME_GAIN_MUTE       0
  #define ADEC_DSP_VOLUME_MUTE_MIN            10
  #define ADEC_DSP_SE_VOLUME_ZERO             0

  //// Transformation equation for "GAIN Input" and "Gain Output"
  /* Convert UI value to dB volume */
  decibelVolume = (double)(volume.mainVol - ADEC_MAIN_VOLUME_GAIN_0DB) + (double)volume.fineVol/ADEC_FINE_VOLUME_GAIN_STEP;
  /* Convert dB value to DSP volume */
  adecVolume = (UINT32)((double)ADEC_DSP_MAIN_VOLUME_GAIN_0DB * (double)pow(10.0, decibelVolume/20.0));


  // we will send this "adecVolume" to Driver.


Requirements
************

Functional Requirements
=======================

Audio Gain implementation must adhere to the interface specifications defined by LG.
For more information about the data types and functions used in this module, refer to API List :ref:`API List <ALSA GAIN API LIST>`.

Quality and Constraints
=======================

Performance
-----------

Function elapsed time must be less than 10ms

Design Constraints
------------------
There is no design constraints.


Implementation
**************

This section provides materials that are useful for Gain implementation.

- The File Location section provides the location of the Git repository where you can get the header file in which the interface for the Gain implementation is defined.
- The API List section provides a brief summary of Gain APIs that you must implement.
- The Status Log section provides information about the DAP status log file which is used for examining the status and operation of Gain.

File Location
=============

The Gain interfaces are defined in the alsa-ext-gain.h header file, which can be obtained from https://swfarmhub.lge.com/.

- Git repository: bsp/ref/alsa-ext-renderer-header

.. _ALSA GAIN API LIST:
API List
========

The Gain driver implementation must adhere to the interface specifications defined and implements its functions. Refer to the API Reference for more details.

Data Types
----------

 No Data Types

Functions
---------

Extended Functions
^^^^^^^^^^^^^^^^^^

============================================= ===============================================
Funtion                                       Description
============================================= ===============================================
 :c:macro:`GAIN_INPUT_DURATION`               put/get gain value for input gain duration
 :c:macro:`GAIN_INPUT`                        put/get gain value for input.
 :c:macro:`GAIN_OUTPUT`                       put/get gain value for output.
 :c:macro:`GAIN_AUDIODESCRIPTION`             put/get gain value for Audio description.
============================================= ===============================================

Testing
*******
To test the implementation of the Gain module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the Gain module and verifies the kernel event operations for the module by using a test execution file.
For more information, see :doc:`see DMG in SoCTS Unit Test Specification </part4/socts/Documentation/source/producer-manual/producer-manual_alsa/producer-manual_alsa-delay_alsa-gain_alsa-mute_alsa-dmg>`.

Reference
*********
For additional information on related standards or technical topics, refer to:
| `ALSA-Project <https://www.alsa-project.org/wiki/Main_Page>`_
| `ALSA Kernel API Documentation <https://www.kernel.org/doc/html/v6.6-rc3/sound/kernel-api/index.html>`_