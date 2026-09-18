Introduction
##################

.. _eunyoung.lee: eunyoung.lee@lge.com
.. _sangwook82.lee: sangwook82.lee@lge.com

About This Document
*********************

A Board Support Package (BSP) is a collection of software required to run webOS TV on a hardware platform (SoC). The webOS TV BSP Documentation provides information and concepts that are foundational to a BSP for webOS TV and describes the requirements and implementation of the BSP.

The primary audience for this document is developers who want to understand the components that make up a BSP  for webOS TV or who are writing a BSP for webOS TV on a new hardware platform. 

webOS TV BSP Documentation
==========================

The webOS TV BSP Documentation includes the following four parts:

* **Part I Foundations** (this document) — This document describes the architecture of the webOS TV platform, the components that make up a BSP for webOS TV, and the steps needed to develop the webOS TV BSP for a new hardware platform. It also provides information on the build environment and requirements for porting the bootloader and kernel for webOS TV.
* **Part II LG Linux TV Driver Implementation** — This document describes an overview of each LG Linux TV driver and provides details about its functionalities, requirements, and interface specification related to writing the driver to a new hardware platform.
* **Part II LG HAL Implementation** — This document describes an overview of each HAL library module and provides details about its functionalities, requirements, and interface specification related to writing the module to a new hardware platform.
* **Part IV Testing and Verification** — This document describes how to use the SoCTS tool used to test and verify a BSP for webOS TV.

Revision History
*********************

======= ========== ========================== ================================== 
Version Date       Changed by                 Description                   
======= ========== ========================== ================================== 
1.0     2023-11-30 | `eunyoung.lee`_          Initial release
                   | `sangwook82.lee`_
======= ========== ========================== ================================== 

Terminology
*********************

These terms are used throughout this document:

.. list-table:: 
   :widths: 25 100
   :header-rows: 1

   * - Term
     - Description
   * - BAT
     - Build Acceptance Testing (BAT). A type of software testing intended to ensure the most important functions are working properly when a software is implemented.
   * - BIT
     - BSP Integration Test. The process of verifying the integration of your BSP into webOS TV.
   * - beanbird kernel
     - The standard kernel for webOS TV.
   * - Bring-up
     - Bringing up a SoC board means the process of developing a BSP for a new SoC board in a non-booting state, to a level where basic TV functionality is operational.
   * - CCC
     - Change Control Committee. A procedure that is required to submit a change for approval and incorporation into the official release repository.
   * - DILE
     - Device Interface Layer Extension. A shared library that can be used collectively by external processes, including webOS TV..
   * - EPK
     - An EPK file is an extended package file, which serves as the standard format used by webOS to distribute and install the platform's binary image.
   * - Jenkins
     - A build server that allows for easy webOS OE builds.
   * - OE
     - OpenEmbedded. It provides a build system for embedded Linux.
   * - PAK
     - A PAK file is a package file created to bundle files or resources. It is  commonly used in BSP to package the components such as the kernel, device drivers, libraries, configuration files, and more.
   * - SWFarmHub
     - A Git server for collaborating with 3rd party vendors.
   * - SIT
     - Sprint Integration Test
   * - SoCTS
     - SoC Compliance Test Suite. A BSP verification testing tool for webOS TV.
   * - TVBin
     - A data server for storing and versioning of pre-built binary image.
   * - Wall
     - A Git server for webOS TV.
   * - webOS TV
     - webOS TV is a web-centric smart TV platform that has powered LG Smart TVs.



