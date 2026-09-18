eMMC Status
=============

History
-------

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
0.0.1   2022-07-29 khkh.lee            initial
======= ========== =================== =======

Overview
--------

For checking eMMC status, we require some items and format to
describe that information.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules.

  #. Items should be placed key and value
  #. If the eMMC frequency changes after booting, you can check the changed frequency and time through dmesg.
  #. Kernel has eMMC information

Linux eMMC information
^^^^^^^^^^^^^^^^^^^^^^

File location
  ``/sys/kernel/debug/mmc0/ios``

Example

.. code-block:: bash

   / # cat sys/kernel/debug/mmc0/ios
   clock:          200000000 Hz
   vdd:            7 (1.65 - 1.95 V)
   bus mode:       2 (push-pull)
   chip select:    0 (don't care)
   power mode:     2 (on)
   bus width:      3 (8 bits)
   timing spec:    10 (mmc HS400)
   signal voltage: 1 (1.80 V)
   driver type:    0 (driver type B)

Print frequency
^^^^^^^^^^^^^^^

if the eMMC frequency changes after booting, you can check the changed frequency and time through dmesg.

Kernel log format
 ``emmc clock: EMMC: Clock changed to  190000000 Hz from  200000000 Hz``


