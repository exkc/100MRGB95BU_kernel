About This Document
###################

Purpose
*******

Linux TV drivers are a means of communication between a hardware device and the webOS TV platform. These device drivers for webOS TV run in the kernel space and provide an interface between webOS TV and the specific hardware devices. The LG Linux TV Drivers Implementation document provides details about the functionalities, requirements, and interface specifications of each LG Linux TV driver. 

The primary audience for this document is developers who are writing device drivers for webOS TV on a new hardware platform. In most cases, the document assumes that the developer has knowledge of implementing Linux kernel space drivers.

webOS TV BSP Documentation
==========================

The webOS TV BSP Documentation includes the following four parts:

- **Part I Foundations** — This document describes the architecture of the webOS TV platform, the components that make up a BSP for webOS TV, and the steps needed to develop the webOS TV BSP for a new hardware platform. It also provides information on the build environment and requirements for porting the bootloader and kernel for webOS TV.
- **Part II LG Linux TV Drivers Implementation (this document)** — This document describes an overview of each LG Linux TV driver and provides details about its functionalities, requirements, and interface specification related to writing the driver to a new hardware platform.
- **Part III LG HAL Libs Implementation** — This document describes an overview of each HAL library module and provides details about its functionalities, requirements, and interface specification related to writing the module to a new hardware platform.
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
    * - webOS TV
      - webOS TV is a web-centric smart TV platform that has powered LG Smart TVs.

Additional Resources
********************

Before beginning any Linux TV driver development, it is important to have a good understanding of the Linux kernel internals, device driver model, media drivers, and debugging techniques. For further details, refer to the Linux kernel documentation. 

- `The Linux Kernel documentation <https://docs.kernel.org/>`_
- `Linux TV documentation <https://linuxtv.org/>`_