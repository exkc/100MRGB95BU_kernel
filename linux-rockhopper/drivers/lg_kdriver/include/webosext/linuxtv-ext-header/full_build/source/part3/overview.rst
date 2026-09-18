LG HAL Libs Overview
####################

The HAL libraries, also known as hal-libs, are a type of user-level device drivers. They provide an interface between the upper layer (webOS applications, modules, and services) and the hardware devices. HAL libraries do not directly control the hardware but instead, access the hardware through kernel-level device drivers. 

HAL Libraries
*************

The HAL libraries consist of various modules responsible for TV broadcast-related features, graphic control, content protection, as well as system and hardware control.

- **Broadcast-related features** include the following modules that provide interfaces for video recording as well as encryption and security features related to broadcasting. 
    - Enhanced Content Protection (ECP)
    - Private Video Recorder (PVR)
    - ACAS_LIB
- **GPU control** include the following module that provides interfaces for abstracting graphic processing. 
    - Graphic Abstraction Layer (GAL)
- **Image** include the following modules that provide interfaces for JPEG image processing and video output management.
    - JPEG
    - Video Output (VO)
- **Content protection** include the following modules that provide interfaces for encryption and security of digital content, preventing unauthorized replication and playback.
    - Secure Video Path (SVP)
    - DRM
    - CRYPTO
    - High-bandwidth Digital Content Protection (HDCP2)
- **System and hardware control** include the following modules that provide interfaces for controlling and managing the system and hardware.
    - SYS
    - USB
    - MICOM
    - MMC

Product-based HAL Implementation 
********************************

The webOS TV platform can be applied to various products such as Smart TVs and Smart Monitors. The following table shows the implementation requirements of the HAL module based on the product features to which the webOS TV platform is applied.

- "O" indicates that the driver is required to be fully implemented for the product.
- "△" indicates that the driver is required to be partially implemented for the product.
- "X" indicates that the driver is not required to be implemented for the product.

+--------------------+---------------------------------------------------------------+----------+----------------+
| HAL Module                                                                         | Smart TV | Smart Monitor  |
+====================+===============================================================+==========+================+
|Broadcast           | Enhanced Content Protection (ECP)                             | O        | X              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | Private Video Recorder (PVR)                                  | O        | X              |
|                    +---------------------------------------------------------------+----------+----------------+ 
|                    | Acas_lib                                                      | O        | X              |
+--------------------+---------------------------------------------------------------+----------+----------------+      
|Graphics            | Graphic Abstraction Layer (GAL)                               | O        | O              |
+--------------------+---------------------------------------------------------------+----------+----------------+  
|Image               | JPEG                                                          | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+ 
|                    | Video Output (VO)                                             | O        | O              |
+--------------------+---------------------------------------------------------------+----------+----------------+  
|Security            | AirPlay                                                       | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+ 
|                    | Crypto                                                        | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | Digital Rights Management (DRM)                               | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | High-bandwidth Digital Content Protection (HDCP2)             | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | KEYMASTER                                                     | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | SSTR                                                          | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | Secure Video Path (SVP)                                       | O        | O              |
+--------------------+---------------------------------------------------------------+----------+----------------+  
|System              | SYS                                                           | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | USB                                                           | △        | △              |
|                    +---------------------------------------------------------------+----------+----------------+ 
|                    | Multi-Media Card (MMC)                                        | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+
|                    | Suspend-to-RAM (STR)                                          | O        | O              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | IR Blaster (IRB)                                              | O        | X              |
|                    +---------------------------------------------------------------+----------+----------------+  
|                    | Checkpoint/Restore In Userspace (CRIU)                        | O        | O              |
+--------------------+---------------------------------------------------------------+----------+----------------+  
|Others              | UCOM                                                          | △        | △              |
|                    +---------------------------------------------------------------+----------+----------------+ 
|                    | Video Encoder (VENC)                                          | O        | △              |
+--------------------+---------------------------------------------------------------+----------+----------------+