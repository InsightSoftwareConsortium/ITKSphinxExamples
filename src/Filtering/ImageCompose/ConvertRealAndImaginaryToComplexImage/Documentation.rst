Convert Real And Imaginary Images To Complex Image
==================================================

.. index::
   single: ComposeImageFilter
   pair: real; imaginary
   single: complex

Synopsis
--------

Convert a real image and an imaginary image to a complex image.


Results
-------
Output::

  Image (0x7ff58250cf20)
  RTTI typeinfo:   itk::Image<std::__1::complex<float>, 2u>
  Reference Count: 1
  Modified Time: 25
  Debug: Off
  Object Name:
  Observers:
    none
  Source: (0x7ff58250c590)
  Source output name: Primary
  Release Data: Off
  Data Released: False
  Global Release Data: Off
  PipelineMTime: 22
  UpdateMTime: 26
  RealTimeStamp: 0 seconds
  LargestPossibleRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [0, 0]
  BufferedRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [0, 0]
  RequestedRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [0, 0]
  Spacing: [1, 1]
  Origin: [0, 0]
  Direction:
  1 0
  0 1

  IndexToPointMatrix:
  1 0
  0 1

  PointToIndexMatrix:
  1 0
  0 1

  Inverse Direction:
  1 0
  0 1

  PixelContainer:
    ImportImageContainer (0x7ff58250d0e0)
      RTTI typeinfo:   itk::ImportImageContainer<unsigned long, std::__1::complex<float> >
      Reference Count: 1
      Modified Time: 24
      Debug: Off
      Object Name:
      Observers:
        none
      Pointer: 0x7ff58250c1b0
      Container manages memory: true
      Size: 0
      Capacity: 0

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ComposeImageFilter
