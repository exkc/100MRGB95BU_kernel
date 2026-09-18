Scaler Status
=============

.. seealso::

  :doc:`/v4l2/scaler`

History
-------

.. _seonghoon1128.do: seonghoon1128.do@lge.com

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
1.0.2   2019-06-13 `seonghoon1128.do`_ Modified file path
0.0.0   ...        ...                 ...
======= ========== =================== =======

Overview
--------

For checking scaler driver's status, we require some items and format to
describe that information. Even chip vendor also add some values for check
driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules.

  #. Items should be placed key and value
  #. Before you print the Items, print which linuxtv-ext-header version like
     below:

     ``version=linuxtv-ext-header ver.1.0.1 (submissions/21)``

  #. If some of section need many categories, you should print "Start" & "End"
     for separate that information. (See the example below)

.. code-block:: bash

  example)
  version=linuxtv-ext-header ver.1.0.1 (submissions/21)
  [main scaler]
  open=1
  connect=1
  window=...

  [sub0 scaler]
  open=1
  connect=1
  window=...

Section
^^^^^^^

File Path
  ``/proc/lgtv-driver/scaler/``

File name
  ``pq-status``

Tree
  =========== ================= ========================================
  Type        File name         V4L2 device driver name
  =========== ================= ========================================
  Main Scaler main.p0           V4L2_EXT_DEV_PATH_SCALER0 "/dev/video30"
  Sub Scaler  sub.p0            V4L2_EXT_DEV_PATH_SCALER1 "/dev/video31"
              sub.p1            V4L2_EXT_DEV_PATH_SCALER2 "/dev/video32"
              sub.p2            V4L2_EXT_DEV_PATH_SCALER3 "/dev/video33"
  GP Scaler   gp.p0 ~ gp.pxx... V4L2_EXT_DEV_PATH_GPSCALER "/dev/video70
  =========== ================= ========================================

TODO