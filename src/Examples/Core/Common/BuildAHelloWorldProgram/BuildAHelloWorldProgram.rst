Build A Hello World Program
===========================

.. index::
   single: Image, hello world

Synopsis
--------

This demonstrates building a simple Hello World ITK program.  We instantiate an
image and print it to stdout.


Results
-------

Output::

  ITK Hello World!
  Image (0x19ca6d0)
    RTTI typeinfo:   itk::Image<unsigned short, 3u>
    Reference Count: 2
    Modified Time: 1
    Debug: Off
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
      Size: [0, 0, 0]
    BufferedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [0, 0, 0]
    RequestedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [0, 0, 0]
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
      ImportImageContainer (0x19ca990)
        RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned short>
        Reference Count: 1
        Modified Time: 2
        Debug: Off
        Observers:
          none
        Pointer: 0
        Container manages memory: true
        Size: 0
        Capacity: 0

Code
----

C++
...

.. literalinclude:: BuildAHelloWorldProgram.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::Image
