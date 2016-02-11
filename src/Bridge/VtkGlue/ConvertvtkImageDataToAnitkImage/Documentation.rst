Convert vtkImageData to an itk::Image
=====================================

.. index::
   single: VTKImageToImageFilter

Synopsis
--------

Convert vtkImageData to an itk::Image in a processing pipeline.


Results
-------

Output::

  Image (0x3b9d810)
    RTTI typeinfo:   itk::Image<unsigned char, 3u>
    Reference Count: 2
    Modified Time: 62
    Debug: Off
    Object Name:
    Observers:
      none
    Source: (0x47e5460)
    Source output name: Primary
    Release Data: Off
    Data Released: False
    Global Release Data: Off
    PipelineMTime: 57
    UpdateMTime: 63
    RealTimeStamp: 0 seconds
    LargestPossibleRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [181, 217, 1]
    BufferedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [181, 217, 1]
    RequestedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [181, 217, 1]
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
      ImportImageContainer (0x4875620)
        RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned char>
        Reference Count: 1
        Modified Time: 61
        Debug: Off
        Object Name:
        Observers:
          none
        Pointer: 0x334e260
        Container manages memory: false
        Size: 39277
        Capacity: 39277


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

.. breathelink:: itk::VTKImageToImageFilter
