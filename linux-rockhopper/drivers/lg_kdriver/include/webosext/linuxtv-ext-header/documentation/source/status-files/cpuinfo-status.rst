CPU frequency Status
====================

History
-------

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
0.0.1   2022-11-01 byungki80.kim       initial
======= ========== =================== =======

Overview
--------

Check the current CPU frequency.
If the CPU frequency changes after booting, you can check the changed frequency and time through dmesg.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing thes information, we should follow below rules.

  #. [    2.040208]       : Time
  #. cpufreq:             : Message header
  #. frequency changed to : Message
  #. 1000000              : changed frequency

CPU Frequency Status
..........................

  #. /sys/devices/system/cpu/cpufreq/policy0/cpuinfo_cur_freq
  #. /sys/devices/system/cpu/cpufreq/policy2/cpuinfo_cur_freq

Example
-------

.. code-block:: bash

  dmesg | grep cpufreq
  [    2.040208] cpufreq:frequency changed to: 1000000
  cat /sys/devices/system/cpu/cpufreq/policy0/cpuinfo_cur_freq
  1000000
  cat /sys/devices/system/cpu/cpufreq/policy2/cpuinfo_cur_freq
  200000
