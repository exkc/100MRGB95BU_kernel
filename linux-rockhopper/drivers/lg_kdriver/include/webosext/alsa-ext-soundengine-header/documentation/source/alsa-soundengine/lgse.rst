.. _lgse-doc:

LGSE
========


Introduction
------------

| This document describes the LGSE driver in the kernel space. The document gives an overview of the LGSE driver and provides details about its functionalities and implementation requirements.


Revision History
^^^^^^^^^^^^^^^^

======= ========== ====================== =======
Version Date       Changed by             Comment
======= ========== ====================== =======
1.0.15  2025-07-01 seungseop.lim@lge.com  Modify mode 5 in lgse_ll_mode_type_t
1.0.14  2025-06-13 myunghee.kim@lge.com   Add FN005_1 for LGSE8.3
1.0.13  2025-05-27 myunghee.kim@lge.com   update APIs for LGSE8.3
1.0.12  2025-05-22 myunghee.kim@lge.com   Add 2 APIs for LGSE8.3
1.0.11  2025-04-23 myunghee.kim@lge.com   Add APIs for LGSE8.3
1.0.10  2025-03-26 kwangshik.kim@lge.com  Add APIs for webOS Soundbar
1.0.9   2024-11-25 seungseop.lim@lge.com  Add requirments of NPU deep learning model porting
1.0.8   2024-06-03 myeonggyu.choe@lge.com Add LGSE_LL functions
1.0.7   2024-05-07 myeonggyu.choe@lge.com Add new API Fn025
1.0.6   2023-11-14 kwonwoo.kang@lge.com   Applied new document template.
1.0.5   2023-09-11 kwangshik.kim@lge.com  Add new API FN001_2
1.0.4   2023-07-03 kwangshik.kim@lge.com  Add new API and modify existed API
1.0.3   2022-09-22 kwangshik.kim@lge.com  fill missed requirement
1.0.2   2022-06-07 kwangshik.kim@lge.com  modify params number of FN005
1.0.1   2020-06-08 kwangshik.kim@lge.com  add new api FN014_1
1.0.0   2020-07-07 kwangshik.kim@lge.com  create lgse guide
======= ========== ====================== =======


Terminology
^^^^^^^^^^^

| The key words "must", "must not", "required", "shall", "shall not", "should", "should not", "recommended", "may", and "optional" in this document are to be interpreted as described in RFC2119.

| The following table lists the terms used throughout this document:

====================================== ==================================
Term                                   Description
====================================== ==================================
ALSA                                   Advanced Linux Sound Architecture
Sound Engine API                       Sound Engine Block Control implemented in SoC Driver and Parameter delivered Interface functions
Sound Engine (UI operation) Scenario   UI operation and Sound Engine Block mapping table, The worst case can be verified by listing the numbers in all cases
Sound Engine Parameter                 | A set of tuning values that can precisely tune each Sound Effect in the Sound Engine
                                       | SE Middleware provides a branch structure for tuning parameters for TOOL, INCH, AMP, REGION, etc
PEQ                                    Parametric EQ, SoundMode or UserEQ mapping EQ Block
MSS                                    **Magic Space Sound**, EQ for spatial acoustic correction, 10 band EQ, independent operation with existing PEQ
====================================== ==================================


Technical Assistance
^^^^^^^^^^^^^^^^^^^^

| For assistance or clarification on information in this guide, please create an issue in the LGE JIRA project and contact the following person:

=============== ==========
Module          Owner
=============== ==========
lgse            kwangshik.kim@lge.com
=============== ==========


Overview
--------


General Description
^^^^^^^^^^^^^^^^^^^


In TV Service Middleware, Sound Engine maps user sound effect menu and
Sound Engine Driver's block function according to UI Scenario.

LGSE is an abbreviation for LG Sound Engine. It is used to apply various sound effects for the user.
It is related to Sound Engine Common and Dolby Audio Post-processing (DAP). See also :ref:`soundengine-common-doc`, :ref:`dap-doc`

Architecture
^^^^^^^^^^^^

Driver Architecture
*******************

.. image:: resources/audio-overview.png
  :width: 100%
  :alt: ADEC Overview


Requirements
------------


Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^

The data types and functions used in this module are located in the Data Types and Functions in the API List.


Quality and Constraints
^^^^^^^^^^^^^^^^^^^^^^^


Performance
***********
Function elapsed time should be less than 5ms


Design Constraints
******************

LGSE Firmware (FW) is implemented by LG SIC, and the LGSE FW library is released to the other BSP.
The BSP should port the released library to connect LGSE APIs and FW.
Therefore, the other BSP should discuss with LG SIC to understand the detailed functionalities of each API.
This is because the FW codes are blocked and obfuscated for security purposes.


Worst Case
""""""""""

The worst case scenario does not activate all functions of the Sound Engine Block.
Instead, it is based on cases that demand maximum performance,
as determined by the Sound Engine UI behavior scenarios set annually.

2016 worst case: 0x1409cac7 (MODE FLAG) - Operation amount 182Mhz


Parameter setting according to branch structure
"""""""""""""""""""""""""""""""""""""""""""""""

The current branch structure is divided into Inch, Tool, Home/Store,
and Extra (User Defined) categories, such as AMP and tv speaker orientation

Parameters use a bit flag operation of 32-bit unsigned int and
a parameter set can be used in several models.

In the LGSE function of HAL, the function that receives
the parameter can be modified based on various conditions, such as product orientation and model.
However, the number of parameters is determined by the specified specifications.


Mutax Lock
""""""""""

All Sound Engine Middleware operations can be performed
using the following functions after executing a function with a 1-lock structure.

If there is no return from the driver, there is a possibility of lock up.
Therefore, the driver (HAL function) must pass the control right after execution.


Remark
""""""

:c:macro:`LGSE_VAR_FN009`  is associated with volume control.
The default value for this function should be set to 0, which ensures no audio output during the initialization status

Implementation
--------------

This section provides materials that are useful for LGSE implementation.
The File Location section provides the location of the Git repository
where you can get the header file in which the interface for the LGSE implementation is defined.
The API List section provides a brief summary of LGSE APIs that you must implement.
For porting deep learning models to NPU, you must implement FN014, FN031 and FN032
according to the requirements of section NPU deep learning model porting.


File Location
^^^^^^^^^^^^^

The Component input interfaces are defined in the alsa-ext-lgse.h header file, which can be obtained from https://swfarmhub.lge.com/.

- Git repository: bsp/ref/alsa-ext-soundengine-header


API List
^^^^^^^^


Data Types
**********


Extended Enumerations
"""""""""""""""""""""

================================================================================== ===================================================================================================
Enumeration                                                                        Description
================================================================================== ===================================================================================================
:type:`lgse_se_init_ext_type_t`                                                    set initial driver setting for sound engine
:type:`lgse_se_mode_ext_type_t`                                                    set driver setting for sound engine
================================================================================== ===================================================================================================


Functions
*********


Extended Functions
""""""""""""""""""

======================================== ===============================================
Function                                 Description
======================================== ===============================================
:c:macro:`LGSE_VERSION`                  Get LGSE version for what driver use
:c:macro:`LGSE_MODE`                     Set LGSE Mode
:c:macro:`LGSE_INIT_MAIN`                Set LGSE FNxxx
:c:macro:`LGSE_VAR_MAIN`                 Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_MIXER_GAIN`               Defined in File **alsa-ext-lgse.h**

:c:macro:`LGSE_INIT_FN000`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN000`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN000_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN001`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN001`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN001_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN001_2`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN002`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN002`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN002_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN002_V83`            Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN002_1_V83`          Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN003`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN003_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN004`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN004_V83`           Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN004_V83`            Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN004_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN004_1_V83`          Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN005`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN008`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN008`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN008_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN009`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN009`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN009_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN010`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN010`                Defined in File **alsa-ext-lgse.h**

:c:macro:`LGSE_INIT_FN011`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN011`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN014`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN014`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN014_1`              Related to DNN (Dynamic Neural Network) of FN014
:c:macro:`LGSE_INIT_FN016`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN016`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN017`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN017_2`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN017_2_V83`          Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN017_3`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN017_3_V83`          Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN019`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN019_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN020`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN020`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN020`                Defined in File **alsa-ext-lgse.h**

:c:macro:`LGSE_VAR_FN022`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN022_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN022_2`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN023`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN024`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN025`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN026`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN028`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN029`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN030`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN030`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN030_1`              Defined in File **alsa-ext-lgse.h**

:c:macro:`LGSE_VAR_FN031`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN032`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_INIT_FN034`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN034`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN025_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN032_1`              Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_VAR_FN005_1`              Defined in File **alsa-ext-lgse.h**

:c:macro:`LGSE_LL_VERSION`               Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_OPEN`                  Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_CLOSE`                 Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_START`                 Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_STOP`                  Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_CONFIG`                Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_BRIGHTNESS`            Defined in File **alsa-ext-lgse.h**
:c:macro:`LGSE_LL_LIGHT_FREQUENCY`       Defined in File **alsa-ext-lgse.h**
======================================== ===============================================

.. deprecated:: webOS22
   it will be removed from webOS 24

======================================== ===============================================
Function                                 Description
======================================== ===============================================
:c:macro:`LGSE_INIT_FN019`               except from socts, deprecated Function
:c:macro:`LGSE_INIT_FN022`               except from socts, deprecated Function
:c:macro:`LGSE_OUT_FN030`                except from socts, deprecated Function
======================================== ===============================================


NPU deep learning model porting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Please refer to below description to implement AI Sound related functions using NPU.
APIs and parameters in the description are about encrypted LGSE FW code we would share

**FN014 (asc)**

Quantized In/Out data Q-value setting

- `lgse_setparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN014_DNN_IN_QUANTIZATION, API_PARAM_AISE_FN014_DNN_OUT_QUANTIZATION

  - data : int16_t (Q-value, number of Interget bit)

    - After quantizing the model, set the integet Q value of the 16-bit integer data input/output

    - ex) Q9(integer bit).7(fractional bit) --> 9


Get/Set data from AI model

- `lgse_getparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN014_FEATURE

  - data : int16_t[18] (dnn_input)

    - dnn_input can be get after "API_CMD_PROC_AISE_FEATURE"

    - before data is input to DNN, data should be converted to floating values (qX.Y)

    - ex) lgse_getparam (&_LGSE06001, API_PARAM_AISE_FN014_FEATURE, data);

- `lgse_setparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_SE_MANUAL_ASC

  - data : int32_t[4] (dnn_output)

    - before data is input to se, data should be converted to integer values (qX.Y)

    - ex) lgse_setparam (&_LGSE06001, API_PARAM_SE_MANUAL_ASC, data);



**FN031 (upmixer)**

Quantized In/Out data Q-value setting

- `lgse_setparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN031_DNN_IN_QUANTIZATION, API_PARAM_AISE_FN031_DNN_OUT_QUANTIZATION

  - data : int16_t (Q-value, number of Integer bit)

    - After quantizing the model, set the integer Q value of the 16-bit integer data input/output.

    - ex) Q9(integer bit).7(fractional bit) --> 9


Get/Set data for AI Model

- `lgse_getparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN031_FEATURE

  - data : int16_t[58] (dnn_input)

    - dnn_input can be get after "API_CMD_PROC_AISE_FEATURE"

    - before data is input to DNN, data should be converted to floating values (qX.Y)

    - ex) lgse_getparam (&_LGSE06001, API_PARAM_AISE_FN031_FEATURE, data);

- `lgse_setparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN031_SYNTHPARAM

  - data : int16_t[60] (dnn_output)

    - before data is input to aise, data should be converted to integer values (qX.Y)

    - ex) lgse_setparam (&_LGSE06001, API_PARAM_AISE_FN031_SYNTHPARAM, data);



**FN032(deepvoice)**

Quantized In/Out data Q-value setting

- `lgse_setparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN032_DNN_IN_QUANTIZATION, API_PARAM_AISE_FN032_DNN_OUT_QUANTIZATION

  - data : int16_t (Q-value, number of Integer bit)

    - After quantizing the model, set the integer Q value of the 16-bit integer data input/output.

    - ex) Q9(integer bit).7(fractional bit) --> 9


Get/Set data for AI Model

- `lgse_getparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN032_FEATURE

  - data : int16_t[2388] (dnn_input)

    - dnn_input can be get after "API_CMD_PROC_AISE_FEATURE"

    - before data is input to DNN, data should be converted to floating values (qX.Y)

    - ex) lgse_getparam (&_LGSE06001, API_PARAM_AISE_FN032_FEATURE, data);

- `lgse_setparam(lgse_obj_t *lgse, lgse_api_param api, void *data)`

  - api : API_PARAM_AISE_FN032_SYNTHPARAM

  - data : int16_t[1024] (dnn_output)

    - before data is input to aise, data should be converted to integer values (qX.Y)

    - ex) lgse_setparam (&_LGSE06001, API_PARAM_AISE_FN032_SYNTHPARAM, data);


Testing
-------
To test the implementation of the LGSE module, webOS TV provides SoCTS (SoC Test Suite) tests. The SoCTS checks the basic operations of the LGSE module and verifies the kernel event operations for the module by using a test execution file.
For more information, see :doc:`LGSE’s SoCTS Unit Test manual </part4/socts/Documentation/source/producer-manual/producer-manual_alsa/producer-manual_alsa-soundengine>`.


References
----------
| `ALSA-Project <https://www.alsa-project.org/wiki/Main_Page>`_
| `ALSA Kernel API Documentation <https://www.kernel.org/doc/html/v6.6-rc3/sound/kernel-api/index.html>`_
