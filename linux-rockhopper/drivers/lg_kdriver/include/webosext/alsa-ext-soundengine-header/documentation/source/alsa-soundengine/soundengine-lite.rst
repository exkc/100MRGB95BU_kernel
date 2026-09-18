.. _soundengine-lite-doc:

SoundEngine Lite
==================


Introduction
------------

| This document describes the SoundEngine Lite driver in the kernel space. The document gives an overview of the SoundEngine Lite driver and provides details about its functionalities and implementation requirements.

Revision History
^^^^^^^^^^^^^^^^

======= ========== ===================== =======
Version Date       Changed by            Comment
======= ========== ===================== =======
1.0.0   2025-02-19 seungseop.lim@lge.com create soundengine lite guide
======= ========== ===================== =======


Terminology
^^^^^^^^^^^

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

====================================== ==================================
Term                                   Description
====================================== ==================================
ALSA                                   Advanced Linux Sound Architecture
Vendor EQ                              Equalizer which SoC vendor support
====================================== ==================================


Technical Assistance
^^^^^^^^^^^^^^^^^^^^

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:

=============== ==========
Module          Owner
=============== ==========
soundengine     kwangshik.kim@lge.com
=============== ==========


Overview
--------


General Description
^^^^^^^^^^^^^^^^^^^

LGSE/DAP Migration to new SoC requires a lot of effort and time. Therefore, we would like to support the sound mode using EQ/Volume/Auto Volume provided by SoC Vendor without LGSE/DAP migration. We call it SoundEngine Lite.

Architecture
^^^^^^^^^^^^


Hardware Architecture
*********************

SoundEngine Lite shall be applied to TVSPK.

Driver Architecture
*******************

SoundEngine Lite use Vendor EQ instead of LGSE and DAP.


Requirements
------------

Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^



Quality and Constraints
^^^^^^^^^^^^^^^^^^^^^^^


Performance
***********

Function elapsed time should be less than 10ms

Design Constraints
******************

If Soc vendor does not support its own EQ, then we cannot use SoundEngine Lite.

Mutax Lock
""""""""""

All Sound Engine Middleware operations can be performed using the following functions after executing a function with a 1-lock structure.

If there is no return from the driver, there is a possibility of lock up. Therefore, the driver (HAL function) must pass the control right after execution.


Implementation
--------------



File Location
^^^^^^^^^^^^^

The Component input interfaces are defined in the alsa-ext-soundengine-common.h header file, which can be obtained from https://swfarmhub.lge.com/.

- Git repository: bsp/ref/alsa-ext-soundengine-header




API List
^^^^^^^^


Data Types
**********


Extended Enumerations
"""""""""""""""""""""


Functions
*********


Extended Functions
""""""""""""""""""

================================================ ===============================================
Function                                         Description
================================================ ===============================================
:c:macro:`SOUND_ENGINE_LITE_GEQ_PARAM`           geq setting
:c:macro:`SOUND_ENGINE_LITE_VOLUME_PARAM`        volume setting
:c:macro:`SOUND_ENGINE_LITE_AUTO_VOLUME_PARAM`   auto volume setting
================================================ ===============================================

Testing
-------

To test the implementation of the SoundEngine Lite module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the SoundEngine Lite module and verifies the kernel event operations for the module by using a test execution file.

References
----------
| `ALSA-Project <https://www.alsa-project.org/wiki/Main_Page>`_
| `ALSA Kernel API Documentation <https://www.kernel.org/doc/html/v6.6-rc3/sound/kernel-api/index.html>`_
