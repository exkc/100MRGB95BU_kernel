About This Document
###################

Purpose
*******

The Hardware Adaptation Layer (HAL) libraries are a type of user-level device drivers that provide an interface between webOS TV and the hardware devices. They do not directly control the hardware but instead, access the hardware through kernel-level device drivers. The LG HAL Libs Implementation document provides details about the functionalities, requirements, and interface specifications of each HAL library module. 

The primary audience for this document is developers who are writing a HAL library module for webOS TV on a new hardware platform. In most cases, the document assumes that the developer has knowledge of implementing Linux user space drivers.

webOS TV BSP Documentation
==========================

The webOS TV BSP Documentation includes the following four parts:

- **Part I Foundations** — This document describes the architecture of the webOS TV platform, the components that make up a BSP for webOS TV, and the steps needed to develop the webOS TV BSP for a new hardware platform. It also provides information on the build environment and requirements for porting the bootloader and kernel for webOS TV.
- **Part II LG Linux TV Drivers Implementation** — This document describes an overview of each LG Linux TV driver and provides details about its functionalities, requirements, and interface specification related to writing the driver to a new hardware platform.
- **Part III LG HAL Libs Implementation (this document)** — This document describes an overview of each HAL library module and provides details about its functionalities, requirements, and interface specification related to writing the module to a new hardware platform.
- **Part IV Testing and Verification** — This document describes how to use the SoCTS tool used to test and verify a BSP for webOS TV.


Revision History
****************

  .. list-table:: 
    :header-rows: 1

    * - Version
      - Date
      - Changed by
      - Description
    * - 1.0
      - 2023-11-30
      - eunyoung.lee
      - Initial release

Terminology
***********

These terms are used throughout this document:

  .. list-table:: 
    :header-rows: 1

    * - Term
      - Description
    * - HAL
      - Hardware Adaptation Layer.  A layer that provides the basic unit functions for controlling the SoC to the Device Interface Layer in webOS TV.
    * - webOS TV
      - webOS TV is a web-centric smart TV platform that has powered LG Smart TVs.