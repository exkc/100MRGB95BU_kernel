About This Document
====================

A Board Support Package (BSP) is a collection of software required to run webOS TV on a hardware platform (SoC). The webOS TV BSP Documentation provides information and concepts that are foundational to a BSP for webOS TV and describes the requirements and implementation of the BSP.

The primary audience for this documentation is developers who are writing a BSP for webOS TV on a new hardware platform. In most cases, the documentation assumes that the developer has knowledge of Linux driver implementation.

The webOS TV BSP Documentation includes the following four parts:

* **Part I Foundations** (this document) — This document describes the architecture of the webOS TV platform, the components that make up a BSP for webOS TV, and the steps needed to develop the webOS TV BSP for a new hardware platform. It also provides information on the build environment and requirements for porting the bootloader and kernel for webOS TV.
* **Part II LG Linux TV Driver Implementation** — This document describes an overview of each LG Linux TV driver and provides details about its functionalities, requirements, and interface specification related to writing the driver to a new hardware platform.
* **Part II LG HAL Implementation** — This document describes an overview of each HAL library module and provides details about its functionalities, requirements, and interface specification related to writing the module to a new hardware platform.
* **Part IV Testing and Verification** — This document describes how to use the SoCTS tool used to test and verify a BSP for webOS TV.

Revision History
====================

======= ========== ========================== ================================== 
Version Date       Changed by                 Description                   
======= ========== ========================== ================================== 
0.1     2023-08-18 | eunyoung.lee             Initial draft
                   | sangwook82.lee
======= ========== ========================== ================================== 

Terminology
============

These terms are used throughout this document:

.. list-table:: 
   :widths: 25 100
   :header-rows: 1

   * - Term
     - Description
   * - CCC
     - Code Change Control. A process to integrate changes in components into official builds.
   * - EPK
     - EPK is the standard format used by webOS to distribute and install the platform's binary image.
   * - OE
     - OpenEmbedded. It provides a build system for embedded Linux.
   * - webOS TV
     - webOS TV is a web-centric smart TV platform that has powered LG Smart TVs.


