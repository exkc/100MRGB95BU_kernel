LG Linux TV Driver Overview
###########################

The LG Linux TV drivers refers to device drivers that serve as a means of communication between hardware devices and the webOS TV platform. These device drivers for webOS TV run in the kernel space and provide an interface between webOS TV and the specific hardware devices. The webOS TV application/framework can directly access the hardware through these kernel-level drivers or indirectly through user-level HAL libraries and kernel-level drivers, enabling the utilization of all device functionalities.

To ensure optimal performance and compatibility, the device drivers are based primarily on open-source technologies. These technologies include Digital Video Broadcasting (DVB), Video for Linux API version 2 (V4L2), and Advanced Linux Sound Architecture (ALSA). By leveraging these technologies, the device drivers provide a reliable and efficient foundation for hardware interaction in webOS TV.

Device Driver Classes
*********************

The device drivers can be categorized into four classes: DVBv5, V4L2, ALSA, and ETC. 

DVBv5 (Digital Video Broadcast version 5)
=========================================

The DVBv5 drivers provide interfaces to control hardware devices associated with digital broadcasting service, as defined by the Linux Media Subsystem standard.

- Tuner and Demodulator
    - DVB Frontend    
- Conditional Access 
    - Advanced Conditional Access System (ACAS)    
    - Broadcast Conditional Access System (BCAS)    
    - Conditional Access (CA)    
    - CI Plus 1.4    
- TS Demultiplexer  
    - Demux    
    - Delivery    
    - Private Video Recorder (PVR)

V4L2 (Video4Linux API version 2)
================================

The V4L2 drivers provide interfaces to control video-related broadcasting inputs, external inputs, and outputs, as defined by the Linux Media Subsystem standard.

- MPEG2 Video Decoder 
    - Video TextureVideo Decoder (VDEC)
- External Inputs 
    - HDMI Input
    - HDMI eARC
    - Displayport Input
    - Vertical Blanking Interval (VBI)
    - AV Input
    - Component Input
- Video Outputs 
    - General Purpose Scaler (GP Scaler)
    - Video Scaler (VSC)
    - Picture Quality (PQ)
    - Panel Controller (VBE)
    - Video Texture (VT)

ALSA (Advanced Linux Sound Architecture)
========================================

The ALSA drivers provide interfaces to control audio-related inputs, external inputs, outputs, and sound engines, as defined by the Linux Sound Subsystem standard.

- MPEG2 Audio Decoder
    - Audio Decoder (ADEC)
    - Analog TV (ATV)
- External Inputs
    - HDMI
    - Display Port
    - Analog-to-Digital Converter (ADC)
- Audio Outputs
    - Audio Capture
    - Audio Delay
    - Audio Gain
    - Audio Mute
    - Sound Out (SNDOUT)
- Sound Effects
    - Dolby Audio Post-processing (DAP)
    - LG Sound Engine (LGSE)

ETC
===

In addition to the DVBv5, V4L2, and ALSA drivers, there are the following device drivers.

Consumer Electronics Control (CEC)
Ethernet
Voice


Product-based Driver Implementation 
The webOS TV platform can be applied to various products such as Smart TVs and Smart Monitors. The following table shows the implementation requirements of the Linux TV driver module based on the product features to which the webOS TV platform is applied.

- "O" indicates that the driver is required to be fully implemented for the product.
- "△" indicates that the driver is required to be partially implemented for the product.
- "X" indicates that the driver is not required to be implemented for the product.

+----------------------------------------------+---------------------------------------------------------------+----------+----------------+
| Linux Driver Module                                                                                          | Smart TV | Smart Monitor  |
+==============================================+===============================================================+==========+================+
| Common I/O                                   | General Purpose Input Output (GPIO)                           | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | Inter-Integrated Circuit (I2C)                                | O        | O              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+ 
| Power Management                             | Runtime PM                                                    | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+
|                                              | Suspend-to-Disk (STD)                                         | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | Suspend-to-RAM (STR)                                          | O        | O              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+ 
| Media                                        | GStreamer                                                     | O        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+
|                                              | PlayReady DRM                                                 | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | Widevine DRM                                                  | O        | O              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+
| Graphics                                     | Graphic Processing Unit (GPU)                                 | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | FrameBuffer                                                   | O        | O              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+  
|Digital TV (DVBv5)                            | Common                                                        | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | DVB Frontend                                                  | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Demux                                                         | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Conditional Access (CA)                                       | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Advanced Conditional Access System (ACAS)                     | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Broadcast Conditional Access System (BCAS)                    | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | CI Plus 1.4                                                   | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Delivery                                                      | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Private Video Recorder (PVR)                                  | O        | X              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+      
|Advanced Linux Sound Architecture (ALSA)      | Audio Decoder (ADEC)                                          | △        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | Analog TV (ATV)                                               | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Audio Capture                                                 | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Audio Delay                                                   | O        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Audio Gain                                                    | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Audio Mute                                                    | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Sound Out (SNDOUT)                                            | O        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Analog-to-Digital Converter (ADC)                             | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Display Port                                                  | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+    
|                                              | HDMI                                                          | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Sound Engine Common                                           | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Dolby Audio Post-processing (DAP)                             | O        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | LG Sound Engine (LGSE)                                        | O        | O              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+    
| Video for Linux 2 (V4L2)                     | AV Input                                                      | X        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+  
|                                              | Component Input                                               | X        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Displayport Input                                             | X        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | HDMI eARC                                                     | O        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | HDMI Input                                                    | △        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Vertical Blanking Interval (VBI)                              | X        | X              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | General Purpose Scaler (GP Scaler)                            | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Panel Controller  (VBE)                                       | O        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Video Picture Quality (PQ)                                    | △        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+    
|                                              | Video Scaler (VSC)                                            | △        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+ 
|                                              | Video Texture (VT)                                            | O        | △              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Video Decoder (VDEC)                                          | O        | X              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+    
| Others                                       | Consumer Electronics Control (CEC)                            | O        | O              |
|                                              +---------------------------------------------------------------+----------+----------------+      
|                                              | Ethernet                                                      | O        | X              |
+----------------------------------------------+---------------------------------------------------------------+----------+----------------+    