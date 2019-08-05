Mask Image
==========

.. index::
   single: MaskImageFilter
   pair: mask; image

Synopsis
--------

Apply a mask to an image.


Results
-------
.. figure:: Yinyang.png
  :scale: 70%
  :alt: input image

  Input Image

.. figure:: MaskImage.png
  :scale: 70%
  :alt: VTK Window

  Output In VTK Window

Output::

  Image (0x7f9d9c95ccc0)
  RTTI typeinfo:   itk::Image<unsigned char, 2u>
  Reference Count: 2
  Modified Time: 235
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
    Dimension: 2
    Index: [0, 0]
    Size: [512, 342]
  BufferedRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [512, 342]
  RequestedRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [512, 342]
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
    ImportImageContainer (0x7f9d9c95d000)
      RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned char>
      Reference Count: 1
      Modified Time: 236
      Debug: Off
      Object Name:
      Observers:
        none
      Pointer: 0x7f9d90050000
      Container manages memory: true
      Size: 175104
      Capacity: 175104


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MaskImageFilter
