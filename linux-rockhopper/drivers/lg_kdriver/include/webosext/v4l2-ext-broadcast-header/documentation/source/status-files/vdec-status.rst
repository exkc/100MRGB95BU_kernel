vdec Status
=============

.. seealso::

  :doc:`/v4l2/vdec`

History
-------

.. _seong.lee: seong.lee@lge.com

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
1.0.0   2020-04-14 seong.lee           initial
0.0.0   ...        ...                 ...
======= ========== =================== =======

Overview
--------

For checking vdec driver's status, we require some items and format to
describe that information. Even chip vendor also add some values for check
driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules.

  #. Items should be placed key and value
  #. If some of section need many categories, you should print "Start" & "End"
     for separate that information. (See the example below)

.. code-block:: bash

  example)
   VTP port = 0
   VDO Port = 0
   VDO Connected = 1
   active = [720, 576]
   crop = [0, 0, 0, 0]
   framerate = [25 / 1]
   Codec type = [M P G 2]

Section
^^^^^^^

File location
  ``/proc/lgtv-driver/v4l2_vdec/``

File name
  ``status.p[N}``

Tree
  =========== ================= ========================================
  Type        File name         V4L2 device driver name
  =========== ================= ========================================
  vdec 0      status.p0         "/dev/video28"
  vdec 1      status.p1         "/dev/video28"
  =========== ================= ========================================

VDEC Status
..........................

VTP port
    value of VTP Port, Default is "None". ( 0 / 1 )

VDO Port
    value of VDO Port, Default is "None". ( O / 1 )

VDO Connected
    value of VDO connection, Default is "0" ( Disconnected = 0 / Connected = 1)

Active
    value of decoded video frame size [ width , height]

Crop
    frame cropping information [0, 0, 0, 0]

Framerate
    value of frame rate , numerator(if it's N) and denominator(if it's M) in frame_rate struct. Result is [ N / M ]

Progressive
    value of Video scan type , Result is [ interlace = 0, progressive = 1 ]

Codec type
    value of codec, fourcc type. ( char , char , char , char )

FRAME Count
    value of V4L2_SUB_EXT_VDEC_FRAME Event that occurred after VIDIOC_STREAMON was called.(decimal)

PICINFO Count
    value of V4L2_SUB_EXT_VDEC_PICINFO Event that occurred after VIDIOC_STREAMON was called.(decimal)


Example
-------

.. code-block:: bash

   $ cat /proc/lgtv-driver/v4l2_vdec/status.p0

 VDEC status

   VTP port = 0
   VDO Port = 0
   VDO Connected = 1
   Active = [720, 576]
   Crop = [0, 0, 0, 0]
   Framerate = [25 / 1]
   Progressive = [0]
   Codec type = [M P G 2]
   FRAME Count = 240
   PICINFO Count = 235
