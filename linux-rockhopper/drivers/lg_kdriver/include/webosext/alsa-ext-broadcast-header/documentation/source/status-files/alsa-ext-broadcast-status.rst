ALSA ext broadcast Status
============

.. note::

  For document writer, each status file must be splitted files.
  Or some new hierarchy for status files of audio(alsa).

History
-------

======= ========== ===================== =======
Version Date       Changed by            Comment
======= ========== ===================== =======
1.0.0   ...        ...                   ...
======= ========== ===================== =======

Overview
--------

For checking alsa broadcast related driver's status, we require some items and format to
describe that information. Even chip vendor also add some values for
check driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules:

  #. Items should be placed key and value.

    * Key and value are classified into '='.
    * Key must comply the camel case.

  #. If some of section need many categories, you should print '[category]'
     & 'empty line' for separate that information. (See the example below)

.. code-block:: bash

  example) /proc/lgtv-driver/audio # cat sndout
  [SPK]
  Open=1
  Connect=1
  SpkOutputChannel=1
  Gain=0x800000
  Mute=0
  Delay=0
  ProcessingDelay=15
  I2SNumber=1
  Underflow=0

  [OPTIC]
  Open=0
  Connect=0
  Light=0
  OpticMode=PCM
  OutputCodec=PCM
  OutputChannel=2
  SrcCopyProtection=FREE
  OutputCopyProtection=FREE
  Gain=0x800000
  Mute=1
  Delay=0
  ProcessingDelay=0
  Underflow=0

Section
^^^^^^^

ADEC
""""

Path
''''

* /proc/lgtv-driver/audio/adec.p0
* /proc/lgtv-driver/audio/adec.p1

Contents
''''''''

================= ===================== ======================================= =======
Key               Example Values        Description                             Remarks
================= ===================== ======================================= =======
AdecPortNum       0,1,2,3 ...           Describe which port it is
Open              1,0                   Status of Open
Connect           UNKNOWN, ATP0, ...    None                                    Those values are based on :type:`adec_src_port_index_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_``.
Start             1,0                   Status of Start
UserCodec         UNKNOWN, PCM, AC3 ... What codec set on "Adec Codec" by user  Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
CurCodec          UNKNOWN, PCM, AC3 ... What codec that Adec actually decoding  Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
SrcCodec          UNKNOWN, PCM, AC3 ... Input source codec that defined by Adec Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
SrcBitrates       192                   Input source's bit rates (kb/s)
SrcSamplingRate   48                    Input source's Sampling rates (kHz)
SrcChannel        5.1                   Input source's channel number
OutputCodec       PCM                   Adec output codec                       Those values are based on :type:`adec_src_codec_ext_type_t` in alsa-ext-adec.h. Use except ``ADEC_SRC_CODEC_``.
OutputChannel     2                     Adec output codec
PTS               123123124             Input source's PTS
Language          None, English, ...    Input source's language
DolbyDRCMode      LINE, RF, DRC_OFF     What user set on "Adec DolbyDRCMode"    Those values are based on :type:`adec_dolbydrc_mode_ext_type_t` in alsa-ext-adec.h
Downmix           LORO, LTRT            What user set on "Adec DownMixMode"     Those values are based on :type:`adec_downmix_mode_ext_type_t` in alsa-ext-adec.h
SyncMode          1,0                   What user set on "Adec SyncMode"        Those values are based on alsa-ext-adec.h
TrickMode         None, Pause, ...      What user set on "Adec TrickMode"       Those values are based on :type:`adec_trick_mode_ext_type_t` in alsa-ext-adec.h
Delay             15                    Delay for Adec X
Mute              1,0                   Mute for Adec X
Gain              0x800000              Gain for Adec X
AudioDescription  1,0                   Print AudioDescription On/Off Status
DefaultPRL        -2147483647           Value of DefaultPRL
Skip              0                     Skip count of lipsync module
Repeat            255                   Repeat count of lipsync module
Discontinuity     0                     Discontinuity count of lipsync module
FreeRun           0                     FreeRun count of lipsync module
Underflow         0                     Underflow count of fader
Overflow          0                     Overflow count of fader
================= ===================== ======================================= =======

Example
'''''''

.. code-block:: bash

  AdecPortNum=0
  Open=1
  Connect=ATP0
  Start=1
  UserCodec=AC3
  CurCodec=AC3
  SrcCodec=AC3
  SrcBitrate=256
  SrcSamplingRate=48000
  SrcChannel=2
  OutputCodec=PCM
  OutputChannel=8
  PTS=4294967295
  Language=0
  DolbyDRCMode=LINE
  DownmixMode=LTRT
  SyncMode=1
  TrickMode=NONE
  DualmonoMode=LR
  Gain=0x81DAFA
  Mute=0
  Delay=0
  AudioDescription=0
  EaseGain=0
  EaseDuration=0
  DefaultPRL=-2147483647
  Skip=0
  Repeat=255
  Discontinuity=0
  FreeRun=0
  Underflow=0
  Overflow=0

ATV
""""""

Path
''''

* /proc/lgtv-driver/audio/atv

Contents
''''''''

================= ===================== ============================================ =======
Key               Example Values        Description                                  Remarks
================= ===================== ============================================ =======
Open              1,0                   Status of Open
Connect           1,0                   Status of Connect
BandCountry       NONE, ATSC, ...       What country set on "Sif BandSetup"          Those values are based on alsa-ext-atv.h
BandSoundSystem   UNKNOWN, BG, ...      What country set on "Sif BandSetup"          Those values are based on alsa-ext-atv.h
Standard          DETECT, BG_NICAM, ... What country set on "Sif StandardSetup"      Those values are based on alsa-ext-atv.h
CurAnalogMode     PAL_UNKNOWN, ...      Current analog mode what driver detected     Those values are based on alsa-ext-atv.h
UserAnalogMode    PAL_UNKNOWN, ...      Analog mode what user set                    Those values are based on alsa-ext-atv.h
SifExist          ABSENT, PRESENT, ...  What driver detected sif siginal             Those values are based on alsa-ext-atv.h
HDev              1,0                   What user set "Sif HDev"
================= ===================== ============================================ =======

Example
'''''''

.. code-block:: bash
  version=linuxtv-ext-header ver.1.0.1 (submissions/21)
  Open=1
  Connect=1
  BandCountry=DVB
  BandSoundSystem=BG
  Standard=BG_NICAM
  CurAnalogMode=PAL_NICAM_STEREO
  UserAnalogMode=PAL_NICAM_STEREO_FORCED
  SifExist=PRESENT
  HDev=1

AENC
""""""

Path
''''

* /proc/lgtv-driver/audio/aenc

Contents
''''''''

================= ===================== ============================================ =======
Key               Example Values        Description                                  Remarks
================= ===================== ============================================ =======
status            idle / playing        aenc status
pts               0x11706644            value of current encoding ES ( hex )
decoder index     1,0                   current connected decoder index
volume gain       0,1                   currently encoding volume gain
format            AAC / MP3 / PCM       encoding format
bitrate           128k / 192k / etc     encoding bitrate
================= ===================== ============================================ =======

Example
'''''''

.. code-block:: bash

  status : playing
  pts : 0x11706644
  decoder index : 1
  volume gain : 0 dB
  format : AAC
  bitrate : 128k
