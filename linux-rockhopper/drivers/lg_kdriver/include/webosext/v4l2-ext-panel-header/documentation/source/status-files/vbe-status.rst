VBE Status
==========

.. seealso::

  :doc:`/v4l2/panel-controller`

History
-------

======= ========== =================== =======
Version Date       Changed by          Comment
======= ========== =================== =======
1.0.2   2019-06-20 sungjun.gi@lge.com  Modify file path and name
======= ========== =================== =======

Overview
--------

For checking VBE(Video Backend) driver's status, we require some items and
format to describe that information. Even chip vendor also add some values for
check driver status.

Detail
------

Default Print Rules
^^^^^^^^^^^^^^^^^^^

For parsing these information, we should follow below rules.

#. Items should be placed key and value
#. Before you print the Items, print which linuxtv-ext-header version like below
   version=linuxtv-ext-header ver.1.0.1 (submissions/21)
#. If some of section need many categories, you should print "Start" & "End" for
   separate that information. (See the example below)

.. code-block:: bash

  example)
  version=linuxtv-ext-header ver.1.0.1 (submissions/21)
  [vbe status]
  Open=1
  ...

Section
^^^^^^^

VBE
"""

TODO
