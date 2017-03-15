Create An Image
===============

.. index::
   single: Image
   single: instantiate

Synopsis
--------

This example illustrates how to manually construct Image.

This example illustrates how to manually construct an *itk::Image*
class. The following is the minimal code needed to instantiate, declare
and create the Image class.

Results
-------

::

  Image (0x1eb5f10)
    RTTI typeinfo:   itk::Image<unsigned char, 3u>
    Reference Count: 1
    Modified Time: 4
    Debug: Off
    Object Name:
    Observers:
      none
    Source: (none)
    Source output name: (none)
    Release Data: Off
    Data Released: False
    Global Release Data: Off
    PipelineMTime: 0
    UpdateMTime: 0
    RealTimeStamp: 0 seconds
    LargestPossibleRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [200, 200, 200]
    BufferedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [200, 200, 200]
    RequestedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [200, 200, 200]
    Spacing: [1, 1, 1]
    Origin: [0, 0, 0]
    Direction:
  1 0 0
  0 1 0
  0 0 1

    IndexToPointMatrix:
  1 0 0
  0 1 0
  0 0 1

    PointToIndexMatrix:
  1 0 0
  0 1 0
  0 0 1

    Inverse Direction:
  1 0 0
  0 1 0
  0 0 1

    PixelContainer:
      ImportImageContainer (0x1a678a0)
	RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned char>
	Reference Count: 1
	Modified Time: 5
	Debug: Off
	Object Name:
	Observers:
	  none
	Pointer: 0x7facf287d010
	Container manages memory: true
	Size: 8000000
	Capacity: 8000000


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::Image
