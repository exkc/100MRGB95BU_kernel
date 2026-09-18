Behavioral Perspective Design for Video Implementation
======================================================

.. Document Descriptions:

Document Descriptions
----------------------

.. _seonghoon1128.do: seonghoon1128.do@lge.com

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
1.3     2022-04-25 `seonghoon1128.do`_ First release
======= ========== =================== =======

.. The Purpose of Document:

The Purpose of Document
^^^^^^^^^^^^^^^^^^^^^^^^
This document describes the video flow from a behavioral perspective for BSP driver developers.

.. The Scope of Document:

The Scope of Document
^^^^^^^^^^^^^^^^^^^^^^^^^
This document describes the operation flow between the BSP driver and
the user's service in terms of dynamic perspectives and dynamic behavior.

.. important::
  1. Contents such as functional requirements and static perspectives that overlap with the BSP Implementation Guide are not described in this document.
  2. Users' services and libraries that are not related to the BSP driver are not mentioned in this document.

.. The Organization of Document:

The Organization of Document
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
1. `Document Descriptions`_

    1.1 `The Purpose of Document`_

    1.2 `The Scope of Document`_

    1.3 `The Organization of Document`_

    1.4 `Terminology and Definitions`_

2. `Architecture Design`_

    2.1 `Dynamic Perspectives`_

    2.2 `Dynamic Behavior about DTV`_

        2.2.1 `Dynamic Behavior DTV`_

        2.2.2 `Sequence Diagram for Resource Allocation of DTV`_

        2.2.3 `Sequence Diagram for Release Resoueces of DTV`_

    2.3 `Dynamic Behavior about HDMI`_

        2.3.1 `Dynamic Behavior HDMI`_

        2.3.2 `Sequence Diagram for Resource Allocation of HDMI`_

        2.3.3 `Sequence Diagram for Release Resoueces of HDMI`_

3. `Reference`_

.. Terminology and Definitions:

Terminology and Definitions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Definitions of terms and abbreviations used in this document are as follows.

============= ============
Definition    Description
============= ============
V4L2          Video4Linux
ALSA          Advanced Linux Sound Architecture
FE            Frond End
Extinput      External Input
A/V           Audio/Video
PQ            Picture Quality
AVD           Analog Video Decoder
Demod         Demodulator
SDEC          System Decoder
VDEC          Video Decoder
ADEC          Audio Decoder
VDO           Video Decoder Output
VSC           Video Scaler
VBE           Video BackEnd
VENC          Video Encoder
AENC          Audio Encoder
SENC          System Encoder
PVR           Personal Video Recorder
A/V Sync      Audio Video Synchronization
CEC           Consumer Electronics Control
HDMI          High Definition Multimedia Interface
EDID          Extended Display Identification Data
HDCP          High-bandwidth Digital Content Protection
============= ============

.. Architecture Design:

Architecture Design
---------------------
This chapter describes the architecture design for the system.
The described content describes the operation flow between the BSP driver and user service
with dynamic perspectives and dynamic behavior.
The conditions of dynamic perspectives and dynamic behavior are described with DTV input and HDMI input.

.. Dynamic Perspectives:

Dynamic Perspectives
^^^^^^^^^^^^^^^^^^^^^
[Figure 1-1] describes the relationship between the BSP driver module and user service from a dynamic perspective.

-----

**[Figure 1-1] Dynamic Perspective**

.. image:: /behavioral-perspective/video_behavioral-perspective_1_1.png
  :width: 100%
  :alt: Dynamic Perspective

-----

Responsibility for Architectural Elements in [Figure 1-1] is as shown in [Table 1-1].

-----

**[Table 1-1] Element Responsibility**

======================= ============
Element                 Responsibility
======================= ============
External Input Manager  - This service sets HDCP Key Download, HDMI EDID, HPD, etc.
                        - for external input, sends and receives information between
                        - equipment and TV through CEC communication, and shares the
                        - driver status with other user processes.
ExtInput Integration    - This service communicates with the HDMI, AVD, and ADC
                        - drivers of the TV and shares input source information and
                        - driver status to other processes in the user area.
Legacy-broadcast        - This service communicates with the TV's Demod, AVD, SDEC,
                        - and VDEC drivers and shares input source information and
                        - driver status with other processes in the user area.
VideooutputD            - VideooutputD controls HW Video Resource and video processing
                        - of Main SoC. It controls the image being output through the
                        - output device and provides information to other modules.
A/V mute manger         - AV Mute Manager provides a function to block video output
                        - and audio mute so that damaged media is not output when
                        - a channel or input media is switched.
PQ controller           - The PQ Controller controls the quality of the video output
                        - on the TV screen. The purpose is to show the optimal picture
                        - quality to the user by using the picture quality setting
                        - values (Picture Mode, Color Gamut, Gamma, White Balance,
                        - etc.) set in the TV and the sensor.
Panel controller        - The Panel Controller controls the power sequence and
                        - panel-related functions to display the screen. Power sequence
                        - sets the panel, inverter, and Main / Sub PMIC (Power
                        - Management IC) according to the specifications of the panel.
AudiooutputD            - AudiooutputD includes analog TV, digital TV, media files
                        - stored in TV, multimedia delivered through network, and system
                        - sound. The sound of these inputs is output to the TV's speaker,
                        - headphone jack, optical output terminal, and wireless audio
                        - device. That is, H/W is controlled to output various inputs
                        - and outputs according to the user's intention.
======================= ============

.. Dynamic Behavior about DTV:

-----

Dynamic Behavior about DTV
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. important::

  Operations in which communication occurs periodically between the BSP driver and LG service (ex: SDEC Section Data operation) are not included. These contents will be dealt with in detail in the implementation guide document written from the service or module point of view.

  The ideal flow is shown in figures and sequence diagrams below. The order of commands and function calls may be changed according to the multi-process race condition.

  Also, it can be called multiple times for a specific function and command in the user's service.

  Therefore, each driver module should be able to operate independently without dependency on function call relationship with other modules.

.. Dynamic Behavior DTV:

Dynamic Behavior DTV
~~~~~~~~~~~~~~~~~~~~~
[Figure 2-1] describes the process of exchanging messages with the user service and the BSP driver at the DTV input.

The numbers written in [Figure 2-1] are random numbers. Therefore, it is not the actual execution order.

-----

**[Figure 2-1] Dynamic Behavior**

.. image:: /behavioral-perspective/video_behavioral-perspective_2_1.png
  :width: 100%
  :alt: Dynamic Behavior

-----

[Table 2-1] and [Table 2-2] describe in detail the process of setting the BSP driver
by the user service in the DTV input in [Figure 2-1].

-----

**[Table 2-1] Resource Allocation (Play DTV)**

============= ============
Sequence      Description
============= ============
1             * **Lecagy-broadcast Service → LG Demod Driver → Demod Drivder**
              - Set Demod init, Set PLL, Demod Tune
              1. Open
                  - KHAL_DEMOD_XXX_Initialize  if it's not executed yet.
              2. Connect
                  - KHAL_DEMOD_XXX_ChangeTransMedia
              3. Start
                  - KHAL_DEMOD_XXX_SetDemod
                  - KHAL_DEMOD_XXX_TunePostJob
                  - KHAL_DEMOD_XXX_CheckLock
                  - KHAL_DEMOD_XXX_CheckSignalState
                  - KHAL_DEMOD_XXX_CheckSpecialData
3             * **Lecagy-broadcast Service → SDEC Driver**
              - Open SDEC
5             * **Lecagy-broadcast Service  → VDEC Driver**
              - VDEC Open
3             * **Lecagy-broadcast Service → SDEC Driver**
              - SDEC Connect
              - SDEC set Input Config
5             * **Lecagy-broadcast Service  → VDEC Driver**
              - VDEC Connect
              1. VIDIOC_S_INPUT ( value : VTP channel )
              2. VIDIOC_S_OUTPUT ( value : VDEC channel )
7             * **Videooutputd Service → VDO Driver**
              - VDO Connect
              1. VDO V4L2 open
              2. V4L2_CID_EXT_VDO_VDEC_CONNECTING
              3. VDO V4L2 close
8             * **Videooutputd Service → VSC Driver**
              - VSC V4L2 Connect
              1. V4L2_CID_EXT_VSC_CONNECT_INFO
3             * **Lecagy-broadcast Service → SDEC Driver**
              - Set PCR/Video/Audio PID
5             * **Lecagy-broadcast Service  → VDEC Driver**
              - VDEC Strat
              1. VIDIOC_S_CTRL,
                  - id : V4L2_CID_EXT_VDEC_FAST_IFRAME_MODE, value : 0
              2. VIDIOC_S_CTRL
                  - id : V4L2_CID_EXT_VDEC_PVR_MODE, value : 0
              3. VIDIOC_S_FMT
                  - fmt.pix.pixelformat : v4l2_fourcc(codec type)
                  - type : V4L2_BUF_TYPE_VIDEO_OUTPUT
              4. VIDIOC_STREAMON
                  - value : V4L2_BUF_TYPE_VIDEO_OUTPUT
2             * **Demod Driver → LG Demod Driver → Lecagy-broadcast Service**
              - Demod tune is finished
4             * **VDEC Driver →  Lecagy-broadcast Service**
              - 1st Frame type event occurred for new channel
              - 1st Picture info event occurred for new channel
14            * **Lecagy-broadcast Service → Videooutputd Service**
              - Notify video information
8             * **Videooutputd Service → VSC Driver**
              - Set display information
              1. V4L2_CID_EXT_VSC_ADAPTIVE_STREAM
              2. V4L2_CID_EXT_VSC_RGB444
              3. V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
              4. V4L2_CID_EXT_VSC_HDR_TYPE
              5. V4L2_CID_EXT_VSC_WINDOW_REGION
15            * **Videooutputd Service → PQ Controller Service**
              - Sends a message to set PQ.
11            * **PQ Contoller Service → PQ Driver**
              - The PQ Controller sets the PQ data to the driver.
9             * **A/V Mute Manager Service → VSC Driver**
              - Turn Off Video Mute Off
              1. V4L2_CID_BG_COLOR
10            * **VSC Driver → A/V Mute Manager**
              - Driver notifies that Video Mute is Off with Kernel Event.
              1. V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF
============= ============

**[Table 2-2] Resource Allocation (Stop DTV)**

============= ============
Sequence      Description
============= ============
9             * **A/V Mute Manager Service → VSC Driver**
              - Turn On Video Mute
              1. V4L2_CID_BG_COLOR
3             * **Lecagy-broadcast Service → SDEC Driver**
              - Close PCR PID filter
5             * **Lecagy-broadcast Service → VDEC Driver**
              - Stop VDEC
              1. VIDIOC_STREAMOFF
              2. VIDIOC_S_CTRL
                  - id : V4L2_CID_EXT_VDEC_HFR_TYPE
                  - value : 0 (SFR, Standard Frame Rate)
              3. VIDIOC_S_CTRL
                  - id : V4L2_CID_EXT_VDEC_TEMPORAL_ID_MAX
                  - value : -1 (default value)
              4. VIDIOC_S_CTRL
                  - id : V4L2_CID_EXT_VDEC_PVR_MODE, value : 0 (off)
3             * **Lecagy-broadcast Service → SDEC Driver**
              - Close Video PES PID filter
5             * **Lecagy-broadcast Service → VDEC Driver**
              - Release the VDEC kernel event and close the VDEC instance.
              1. VIDIOC_STREAMOFF
              2. VIDIOC_UNSUBSCRIBE_EVENT
                  - type : V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT
                  - id : V4L2_SUB_EXT_VDEC_USERDATA
              3. VIDIOC_UNSUBSCRIBE_EVEN
                  - type : V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT
                  - id : V4L2_SUB_EXT_VDEC_FRAME
              4. VIDIOC_UNSUBSCRIBE_EVENT
                  - type : V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT
                  - id : V4L2_SUB_EXT_VDEC_PICINFO
              5. V4L2_CID_EXT_VDEC_CHANNEL ( value : -1 ) for release resource
              6. VDEC V4L2 close
3             * **Lecagy-broadcast Service → SDEC Driver**
              - Initialize SDEC Path with Set input Config and close SDEC device
              1. SDEC set input config to disconnect tuner connection.
              2. SDEC Close
1             * **Lecagy-broadcast Service → LG Demod Driver → Demod Drivder**
              - Stop the demod operation.
              1. Stop : Nothing
              2. Close : KHAL_DEMOD_XXX_ChangeTransMedia()
8             * **Videooutputd Service → VSC Driver**
              - Initializes VSC Display related information.
              1. V4L2_CID_EXT_VSC_ADAPTIVE_STREAM
              2. V4L2_CID_EXT_VSC_RGB444
              3. V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
              4. V4L2_CID_EXT_VSC_HDR_TYPE
8             * **Videooutputd Service → VSC Driver**
              - Disconnect VSC
              1. V4L2_CID_EXT_VSC_CONNECT_INFO
7             * **Videooutputd Service → VDO Driver**
              - Disconnect VDO
              1. VDO V4L2 open
              2. VDO V4L2 Connect
                  - V4L2_CID_EXT_VDO_VDEC_DISCONNECTING
              3. VDO V4L2 close
11            * **PQ Contoller Service → PQ Driver**
              - PQ Controller sets PQ data to driver
============= ============

-----

.. _Sequence Diagram for Resource Allocation of DTV:

Sequence Diagram for Resource Allocation of DTV
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Figure 2-2] shows the relationship between the BSP driver
and the user service as a sequence diagram of the resource setting process at the DTV input in [Table 2-1].

-----

**[Figure 2-2] Sequence Diagram of Setting Function Flow**

.. image:: /behavioral-perspective/video_behavioral-perspective_2_2.png
  :width: 100%
  :alt: Resource Allocation

-----

.. Sequence Diagram for Release Resoueces of DTV:

Sequence Diagram for Release Resoueces of DTV
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Figure 2-3] shows the relationship between the BSP driver
and the user service as a sequence diagram of the released resource process at the DTV input in [Table 2-2].

-----

**[Figure 2-3] Sequence Diagram of Setting Function Flow**

.. image:: /behavioral-perspective/video_behavioral-perspective_2_3.png
  :width: 100%
  :alt: Release Resoueces

-----

.. Dynamic Behavior about HDMI:

Dynamic Behavior about HDMI
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. Dynamic Behavior HDMI:

Dynamic Behavior HDMI
~~~~~~~~~~~~~~~~~~~~~
[Figure 2-4] describes the process of exchanging messages with the user service and the BSP driver at the HDMI input.

The numbers written in [Figure 2-4] are random numbers. Therefore, it is not the actual execution order.

-----

**[Figure 2-4] Dynamic Behavior**

.. image:: /behavioral-perspective/video_behavioral-perspective_2_4.png
  :width: 100%
  :alt: Dynamic Behavior

-----

[Table 2-3] and [Table 2-4] describe in detail the process of setting the BSP driver
by the user service in the HDMI input in [Figure 2-4].

-----

**[Table 2-3] Resource Allocation (Play HDMI)**

============= ============
Sequence      Description
============= ============
1             * **External-Input-Manager Service → HDMI Driver**
              - **Condition : Power On**
              - ExtInput-Integration Service sets Open, HDCP, EDID, HPD to HDMI Driver.
              1. Open()
              2. V4L2_CID_EXT_HDMI_HDCP_KEY, if it's not executed yet.
              3. V4L2_CID_EXT_HDMI_EDID, if it's not executed yet.
              4. V4L2_CID_EXT_HDMI_HPD, if HPD is low voltage.
1             * **HDMI Driver →  External-Input-Manager Service**
              - External-Input-Manager Service reads information from HDMI driver every 100ms.
              1. V4L2_CID_EXT_HDMI_CONNECTION_STATE
              2. V4L2_CID_EXT_HDMI_SPD_INFO
2             * **ExtInput-Integration Service → HDMI Driver**
              - Set Open, Input Port
              1. Open()
              2. VIDIOC_S_INPUT
2             * **HDMI Driver →  ExtInput-Integration Service**
              - ExtInput-Integration Service  reads video information from HDMI driver every 40ms.
              1. V4L2_CID_EXT_HDMI_TIMING_INFO
              2. V4L2_CID_EXT_HDMI_AVI_INFO
              3. V4L2_CID_EXT_HDMI_SPD_INFO
3             * **Videooutputd Service → VSC Driver**
              - Connect VSC
              1. V4L2_CID_EXT_VSC_CONNECT_INFO
9             * **ExtInput-Integration Service → Videooutputd Service**
              - When the HDMI driver reads normal video information from the driver,
              - it notifies the video information to the Videooutputd Service.
3             * **Videooutputd Service → VSC Driver**
              - Set VIdeo information
              1. V4L2_CID_EXT_VSC_ADAPTIVE_STREAM
              2. V4L2_CID_EXT_VSC_RGB444
              3. V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
              4. V4L2_CID_EXT_VSC_HDR_TYPE
              5. V4L2_CID_EXT_VSC_WINDOW_REGION
10            * **Videooutputd Service → PQ Controller Service**
              - Sends a message to set PQ.
6             * **PQ Contoller Service → PQ Driver**
              - The PQ Controller sets the PQ data to the driver.
4             * **A/V Mute Manager Service → VSC Driver**
              - Turn Off Video Mute Off
              1. V4L2_CID_BG_COLOR
5             * **VSC Driver → A/V Mute Manager Service**
              - Driver notifies that Video Mute is Off with Kernel Event.
              1. V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF
============= ============

**[Table 2-4] Resource Allocation (Stop HDMI)**

============= ============
Sequence      Description
============= ============
4             * **A/V Mute Manager Service → VSC Driver**
              - Turn On Video Mute
              1. V4L2_CID_BG_COLOR
2             * **ExtInput-Integration Service → HDMI Driver**
              - HDMI Input Port Disconnect, Close Device
              1. V4L2_CID_EXT_HDMI_DISCONNECT
              2. Close()
3             * **Videooutputd Service → VSC Driver**
              - Initializes VSC display information
              1. V4L2_CID_EXT_VSC_ADAPTIVE_STREAM
              2. V4L2_CID_EXT_VSC_RGB444
              3. V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
              4. V4L2_CID_EXT_VSC_HDR_TYPE
3             * **Videooutputd Service → VSC Driver**
              - Disconnect VSC
              1. V4L2_CID_EXT_VSC_CONNECT_INFO
6             * **PQ Contoller Service → PQ Driver**
              - PQ Controller sets PQ data to driver
============= ============

-----

.. Sequence Diagram for Resource Allocation of HDMI:

Sequence Diagram for Resource Allocation of HDMI
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Figure 2-5] shows the relationship between the BSP driver
and the user service as a sequence diagram of the resource setting process at the HDMI input in [Table 2-3].

-----

**[Figure 2-5] Sequence Diagram of Setting Function Flow**

.. image:: /behavioral-perspective/video_behavioral-perspective_2_5.png
  :width: 100%
  :alt: Resource Allocation

-----

.. Sequence Diagram for Release Resoueces of HDMI:

Sequence Diagram for Release Resoueces of HDMI
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Figure 2-6] shows the relationship between the BSP driver
and the user service as a sequence diagram of the released resource process at the DTV input in [Table 2-4].

-----

**[Figure 2-6] Sequence Diagram of Setting Function Flow**

.. image:: /behavioral-perspective/video_behavioral-perspective_2_6.png
  :width: 100%
  :alt: Release Resoueces

-----

.. Reference:

Reference
----------
Collab : http://collab.lge.com/main/pages/viewpage.action?pageId=1610514875
