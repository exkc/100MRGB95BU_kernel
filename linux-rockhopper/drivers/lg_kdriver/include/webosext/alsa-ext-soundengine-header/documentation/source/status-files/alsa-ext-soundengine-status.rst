ALSA ext renderer Status
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

For checking alsa sound engine related driver's status, we require some items and format to
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

LGSE
""""""

Path
''''

* /proc/lgtv-driver/audio/lgse

Contents
''''''''

==================== ========================= ====================================== =======
Key                  Example Values            Description                            Remarks
==================== ========================= ====================================== =======
seMode               LGSE_ONLY, LGSE_ATMOS ... LG Sound engine mode
seDownmix            1, 0                      Whether to use LGSE downmix
lgseModeFlag         0x00000003                Currently enabled lgse function mask
connected            1, 0                      Connected LG sound engine
==================== ========================= ====================================== =======

Example
'''''''

.. code-block:: bash

  [LGSE_ARC]
  seMode=LGSE_ATMOS
  seDownmix=1
  lgseModeFlag=0x00000003
  connected=0
  [LGSE_BT_BTSUR]
  seMode=LGSE_ONLY
  seDownmix=0
  lgseModeFlag=0x04090243
  connected=0
  [LGSE_BT]
  seMode=LGSE_ONLY
  seDownmix=0
  lgseModeFlag=0x04090643
  connected=0
  [LGSE_SPK_ARC]
  seMode=LGSE_ATMOS
  seDownmix=1
  lgseModeFlag=0x00000003
  connected=0
  [LGSE_SPK_BTSUR]
  seMode=LGSE_ONLY
  seDownmix=0
  lgseModeFlag=0x04090643
  connected=0
  [LGSE_SPK]
  seMode=LGSE_ATMOS
  seDownmix=1
  lgseModeFlag=0x00000003
  connected=1
