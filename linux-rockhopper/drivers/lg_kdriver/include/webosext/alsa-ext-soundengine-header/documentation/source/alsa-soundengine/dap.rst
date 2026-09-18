.. _dap-doc:

DAP
###

Introduction
************

| This document describes the Dolby Audio Post-processing(DAP) module in the kernel space. The document gives an overview of the DAP module and provides details about its functionalities and implementation requirements.

Revision History
================

======= ========== ===================== =======
Version Date       Changed by            Comment
======= ========== ===================== =======
1.0.6   2024-04-19 kwangshik.kim@lge.com Add new API with enum for DAFC
1.0.5   2024-04-19 kwangshik.kim@lge.com Refine description
1.0.4   2023-11-14 minjae.jun@lge.com    Applied new document template.
1.0.3   2023-10-10 kwangshik.kim@lge.com add deprecated api LGSE_DAP_PROCESSOPTIMIZER
1.0.2   2022-09-22 kwangshik.kim@lge.com fill missed requirement
1.0.1   2022-05-31 kwangshik.kim@lge.com update about dap supporting machines
1.0.0   2020-07-08 kwangshik.kim@lge.com create dap guide
======= ========== ===================== =======

Terminology
===========

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

====================================== ==================================
Definition                             Description
====================================== ==================================
ALSA                                   Advanced Linux Sound Architecture
Sound Engine API                       Sound Engine Block Control implemented in SoC Driver and Parameter delivered
                                       Interface functions
Sound Engine (UI operation) Scenario   UI operation and Sound Engine Block mapping table
                                       The worst case can be verified by listing the numbers in all cases.
Sound Engine Parameter                 A set of tuning values that can precisely tune each Sound Effect in the
                                       Sound Engine.
                                       SE Middleware provides a branch structure for tuning parameters for TOOL,
                                       INCH, AMP, REGION, etc.
GEQ (Graphical Equalization)           Same functionality of LGSE Parametric EQ, SoundMode or UserEQ mapping EQ Block
Magic Space Sound (MSS)                EQ for spatial acoustic correction, 10 band EQ, independent operation with
                                       existing PEQ
DAFC                                   Dolby Atmos Flex Connect (DAFC). With this algorithm, audio data would be wirelessly
                                       transmitted to multiple external speakers.
                                       Device info (named as sconf/dconf) of TV and external speakers including location
                                       and capability should be inserted into Flex Renderer to process and render audio data which represents spatial atmosphere for each speaker device
                                       sconf/dconf would be made by Dolby's Calibration Service and delivered by :c:macro:`SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS`
====================================== ==================================

Technical Assistance
====================

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:

=============== ==========
Module          Owner
=============== ==========
dap             kwangshik.kim@lge.com
=============== ==========


Overview
********

General Description
===================

DAP is abbreviation for Dolby Audio Post-processing.
The DAP module is related to SoundEngine Common and LGSE (LG Sound Engine). See also :ref:`soundengine-common-doc` and :ref:`lgse-doc`.

In TV Service Middleware, Sound Engine maps user sound effect menu and
Sound Engine Driver's block function according to UI Scenario.

Some SoCs have hardware limitations that prevent them from executing both LGSE (LG Sound Engine) and DAP. To prevent computing power issues, these SoCs will not support DAP, and tests for DAP will also be skipped. The BSP should notify and discuss this limitation before implementation.

Architecture
============

Driver Architecture
-------------------

The following figure illustrates an example of possible sound output combinations where sound is output through the Sound Engine.

.. image:: resources/audio-overview.png
  :width: 100%
  :alt: ADEC Overview

Requirements
************


Functional Requirements
=======================
The data types and functions used in this module are described in the Data Types and Functions in the API List.


Quality and Constraints
=======================

Performance
-----------
Function elapsed time should be less than 5ms

Design Constraints
------------------
DAP Firmware (FW) is implemented by Dolby, and the DAP FW codes are released to the BSP. The BSP should port the released codes to connect DAP APIs and FW. Therefore, the BSP should discuss with DAP to understand the detailed functionalities of each API.


Mutax Lock
----------
All Sound Engine Middleware operations can be performed using the following functions after executing a function with a 1-lock structure.

If there is no return from the driver, there is a possibility of lock up.
Therefore, the driver (HAL function) must pass the control right after execution.

Implementation
**************

This section provides materials that are useful for DAP implementation.

- The File Location section provides the location of the Git repository where you can get the header file in which the interface for the DAP implementation is defined.
- The API List section provides a brief summary of DAP APIs that you must implement.

File Location
=============

The DAP interfaces are defined in the alsa-ext-dap.h header file, which can be obtained from https://swfarmhub.lge.com/.
- Git repository: bsp/ref/alsa-ext-soundengine-header

API List
========
The DAP driver implementation must adhere to the interface specifications defined and implements its functions. Refer to the API Reference for more details.

Data Types
----------

Extended Enumerations
^^^^^^^^^^^^^^^^^^^^^
============================================================= ==================================
Data Type                                                     Description
============================================================= ==================================
:type:`lgse_dap_surround_virtualizer_mode_t`                  Defined in File **alsa-ext-dap.h**
:type:`lgse_dap_perceptual_height_filter_mode_ext_type_t`     Defined in File **alsa-ext-dap.h**
:type:`lgse_dap_virtual_bass_mode_ext_type_t`                 Defined in File **alsa-ext-dap.h**
:type:`lgse_dap_regulator_mode_ext_type_t`                    Defined in File **alsa-ext-dap.h**
:type:`soundengine_dafc_flex_configs_status_t`                Defined in File **alsa-ext-dap.h**
============================================================= ==================================

Functions
---------

Extended functions
^^^^^^^^^^^^^^^^^^

================================================= ===============================================
Funtion                                           Description
================================================= ===============================================
 :c:macro:`LGSE_POSTPROCESS`                      Put/Get Audio Post Processing mode.
 :c:macro:`LGSE_DAP_SURROUNDVIRTUALIZERMODE`      Put/Get DAP surround virtualizer mode.
 :c:macro:`LGSE_DAP_DIALOGUEENHANCER`             Put/Get DAP dialogue enhancer.
 :c:macro:`LGSE_DAP_VOLUMELEVELER`                Put/Get DAP volume leveler.
 :c:macro:`LGSE_DAP_VOLUMEMODELER`                Put/Get DAP volume Modeler.
 :c:macro:`LGSE_DAP_VOLUMEMAXIMIZER`              Put/Get DAP volume maximizer.
 :c:macro:`LGSE_DAP_OPTIMIZER`                    Put/Get DAP Optimizer.
 :c:macro:`LGSE_DAP_SURROUNDDECODER`              Put/Get DAP surround decoder.
 :c:macro:`LGSE_DAP_SURROUNDCOMPRESSOR`           Put/Get DAP surround compressor.
 :c:macro:`LGSE_DAP_VIRTUALIZERSPEAKERANGLE`      Put/Get DAP virtualizer speaker angle.
 :c:macro:`LGSE_DAP_INTELLIGENCEEQ`               Put/Get intelligence EQ.
 :c:macro:`LGSE_DAP_MEIDAINTELLIGENCE`            Put/Get media intelligence.
 :c:macro:`LGSE_DAP_GRAPHICALEQ`                  Put/Get graphical EQ.
 :c:macro:`LGSE_DAP_PERCEPTUALHEIGHTFILTER`       Put/Get media intelligence.
 :c:macro:`LGSE_DAP_BASSENHANCER`                 Put/Get BassEnhancer.
 :c:macro:`LGSE_DAP_BASSEXTRACTION`               Put/Get BassExtraction.
 :c:macro:`LGSE_DAP_VIRTUALBASS`                  Put/Get VirtualBass.
 :c:macro:`LGSE_DAP_REGULATOR`                    Put/Get Regulator.
 :c:macro:`SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS`  This setting would set/get of DAFC Flex Configs Status (:type:`soundengine_dafc_flex_configs_status_t`)
================================================= ===============================================

.. deprecated:: webOS22
   it will be removed from webOS 24^M

============================================= ===============================================
Funtion                                       Description
============================================= ===============================================
  :c:macro:`LGSE_DAP_PROCESSOPTIMIZER`        except from socts, deprecated function
============================================= ===============================================

Testing
*******
To test the implementation of the DAP module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the DAP module and verifies the kernel event operations for the module by using a test execution file. 
For more information, see :doc:`DAP’s SoCTS Unit Test manual </part4/socts/Documentation/source/producer-manual/producer-manual_alsa/producer-manual_alsa-soundengine>`.

