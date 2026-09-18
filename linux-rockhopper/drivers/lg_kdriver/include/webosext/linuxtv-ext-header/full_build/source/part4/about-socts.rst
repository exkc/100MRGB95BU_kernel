About This Document
###################

Purpose
*******

SoCTS (SoC Compliance Test Suite) is a verification testing tool for webOS TV BSP. Its purpose is to enhance the overall quality of webOS TV BSP and prevent any potential regressions. This Testing and Verification document provides information on how to set up the test environment for SoCTS and effectively utilize it to test and verify a BSP for webOS TV.

The primary audience for this document is developers who want to evaluate the quality of BSP implementation using SoCTS.



webOS TV BSP Documentation
==========================

The webOS TV BSP Documentation includes the following four parts:

- Part I Foundations — This document describes the architecture of the webOS TV platform, the components that make up a BSP for webOS TV, and the steps needed to develop the webOS TV BSP for a new hardware platform. It also provides information on the build environment and requirements for porting the bootloader and kernel for webOS TV.
- Part II LG Linux TV Driver Implementation — This document describes an overview of each LG Linux TV driver and provides details about its functionalities, requirements, and interface specification related to writing the driver to a new hardware platform.
- Part II LG HAL Implementation — This document describes an overview of each HAL library module and provides details about its functionalities, requirements, and interface specification related to writing the module to a new hardware platform.
- Part IV Testing and Verification (this document) — This document describes how to use the SoCTS tool used to test and verify a BSP for webOS TV.


Revision History
****************

======== ============ =============== ====================================
Version  Date         Changed by      Description
======== ============ =============== ====================================
1.0      2023-12-22   eunyoung.lee     Updated the content in User Guide
======== ============ =============== ====================================


Terminology
***********

=================== =======================================================
Term                Description
=================== =======================================================
BD Player           Blu-ray Disc Player
BIT                 BSP Integration Test. The process of verifying the integration of your BSP into webOS TV
Broadcast Table     A broadcast table contains information about the broadcasting signal environment. Broadcast tables for the Gangnam, Seocho, and Pyeongtaek areas are currently supoorted.
CI+ Cam             Common Interface Plus Conditional Access Module. A module used in digital television receivers to decrypt encrypted channels.
CCC                 Change Control Committee. A procedure that is required to submit a change for approval and incorporation into the official release repository.
DUT                 Device Under Test. The TV device or board that is being tested.
GPSC                General Presentation and Service Control. A feature used for controlling and managing various content in general Smart TV services, including TV channels, programs, and advertisements. GPSC content refers to the various types of content used in TV services.
HDCP                High-bandwidth Digital Content Protection. An encryption technology used for secure transmission and protection of digital content.
MSPG                Multiple Signal Pattern Generator. A device used to generate external input signals during the execution of SoCTS.
MST                 Memory Stress Tests. A method for testing the load on the system's memory.
OE                  OpenEmbedded. It provides a build system for embedded Linux.
QSM                 Quality of Service Management
RF                  Radio Frequency. The frequency range used in wireless communication.
SSH                 Secure shell. A network protocol used for secure remote communication. It provides a secure way to access and control a target device to run SoCTS.
TAS                 Test Automation System. A system designed to allow running specified set of tests on specified webos-image using isolated environment.
TAF                 Test Automation Framework. A framework for execution tests on webOS devices.
TS                  Transport Stream
webOS TV            webOS TV is a web-centric smart TV platform that has powered LG Smart TVs.
=================== =======================================================