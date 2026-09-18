Delay
=====

Introduction
------------

| This document describes the Delay driver in the kernel space. The document gives an overview of the Delay driver and provides details about its functionalities and implementation requirements.

Revision History
^^^^^^^^^^^^^^^^

======= ========== ===================== =======
Version Date       Changed by            Comment
======= ========== ===================== =======
1.0.7   2023-11-15 kwonwoo.kang@lge.com  Applied new document template
1.0.6   2023-07-03 kwangshik.kim@lge.com Add new function LOW_LATENCY_MODE
1.0.5   2022-07-25 cheolhwa.yoo@lge.com  Add performance/constraint requirement
1.0.4   2020-04-13 cheolhwa.yoo@lge.com  Add new function AUDIO_LATENCY_TIME
1.0.3   2019-05-02 kenneth0.park@lge.com Modify more for delay min/max
======= ========== ===================== =======


Terminology
^^^^^^^^^^^

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

================================ ==================================
Term                             Description
================================ ==================================
ALSA                             Advanced Linux Sound Architecture
PCR                              Program Clock Reference
PTS                              Presentation Time Stamp
AV Sync                          Audio to video synchronization
================================ ==================================


Technical Assistance
^^^^^^^^^^^^^^^^^^^^

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:
=============== ==========
Module          Owner
=============== ==========
Delay           cheolhwa.yoo@lge.com
=============== ==========


Overview
--------


General Description
^^^^^^^^^^^^^^^^^^^

Delay controls the audio input/output delay to minimize lip sync, and the input/output delay value changes according to the combination of input signal/output speaker/TV scenario.


Architecture
^^^^^^^^^^^^

Driver Architecture
*******************

The diagram below illustrates the main modules of the webOS audio framework, which is based on ALSA, and shows their interactions.
At the top right of the picture, there is an explanation of the color of the module that represents the input/output delay block.
The input delay is located in front of the MIXER, and the output delay exists for each output.
In conclusion, the total audio delay is equal to the sum of the input delay and output delay of the connected between input and output.

.. image:: resources/audio-overview.png
  :width: 100%
  :alt: ADEC Overview

The variable type used in Kcontrol is always ``int``.

Audio Delay is responsible for storing data in the buffer internally to
eliminate gaps between video and audio.


Requirements
------------

Variable delays between:

* input : 0 ~ 250 ms
* output : 0 ~ 400 ms

The purpose of this function is to compensate for AV sync or AA sync.
In the decoder, AV sync is adjusted to PTS using the PCR dmf reference. However, the AV sync of the final output is distorted by the audio and video processor that occurs behind the decoder.
To compensate this, audio delay is used.
As another example, webOS supports simultaneous audio output. (Example: TV speaker + BT) In this case, we can set the delay between the two audio outputs to sync between the outputs.

Setting the delay value The data in the delay buffer before setting must be
flushed.

Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^

Audio Delay implementation must adhere to the interface specifications defined by LG.
For more information about the data types and functions used in this module, refer to API List :ref:`API List <ALSA DELAY API LIST>`.


Quality and Constraints
^^^^^^^^^^^^^^^^^^^^^^^


Performance
***********
Function elapsed time must be less than 10ms


Design Constraints
******************
Input delay works only for ADEC port and input delay does not work for AMIXER port.
In the case of SPDIF pass-through, output delay may not work because encoding is not performed.


Implementation
--------------

This section provides materials that are useful for Delay implementation.

The File Location section provides the location of the Git repository where you can get the header file in which the interface for the Delay implementation is defined.

The API List section provides a brief summary of Delay APIs that you must implement.


File Location
^^^^^^^^^^^^^

The Component input interfaces are defined in the alsa-ext-delay.h header file, which can be obtained from https://swfarmhub.lge.com/.

- Git repository: bsp/ref/alsa-ext-renderer-header


.. _ALSA DELAY API LIST:
API List
^^^^^^^^


Data Types
**********

Extended Enumerations
"""""""""""""""""""""

================================================================================== ===================================================================================================
Enumeration                                                                        Description
================================================================================== ===================================================================================================
:type:`delay_input_src_type_t`                                                     input source type for audio latency time
:type:`low_latency_mode_type_t`                                                    audio low latency mode type for minimize audio latency
================================================================================== ===================================================================================================


Functions
*********


Extended Functions
""""""""""""""""""

======================================== ===============================================
Function                                 Description
======================================== ===============================================
:c:macro:`DELAY_INPUTOUTPUT`             put/get delay input/output
:c:macro:`AUDIO_LATENCY_TIME`            put/get audio letency time
:c:macro:`LOW_LATENCY_MODE`              put/get audio low latency mode
======================================== ===============================================


Testing
-------
To test the implementation of the Delay module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the Delay module and verifies the kernel event operations for the module by using a test execution file.
For more information, see :doc:`see DMG in SoCTS Unit Test Specification </part4/socts/Documentation/source/producer-manual/producer-manual_alsa/producer-manual_alsa-delay_alsa-gain_alsa-mute_alsa-dmg>`.


References
----------
For additional information on related standards or technical topics, refer to:
| `ALSA-Project <https://www.alsa-project.org/wiki/Main_Page>`_
| `ALSA Kernel API Documentation <https://www.kernel.org/doc/html/v6.6-rc3/sound/kernel-api/index.html>`_