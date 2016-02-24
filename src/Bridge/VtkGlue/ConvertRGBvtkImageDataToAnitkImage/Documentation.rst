Convert RGB vtkImageData to an itk::Image
=========================================

.. index::
   single: VTKImageToImageFilter

Synopsis
--------

Convert RGB vtkImageData to an itk::Image in a processing pipeline.  This
transfers the image buffer data along with image size, pixel spacing, and
origin. Since `vtkImageData` does not yet support an orientation matrix, the
direction cosines are lost. This requires `Module_ITKVtkGlue` to be turned on
in ITK's CMake configuration.


Results
-------

Output::

  Image (0x2dc70e0)
    RTTI typeinfo:   itk::Image<itk::RGBPixel<unsigned char>, 2u>
    Reference Count: 2
    Modified Time: 28
    Debug: Off
    Object Name:
    Observers:
      none
    Source: (0x3281a40)
    Source output name: Primary
    Release Data: Off
    Data Released: False
    Global Release Data: Off
    PipelineMTime: 23
    UpdateMTime: 29
    RealTimeStamp: 0 seconds
    LargestPossibleRegion:
      Dimension: 2
      Index: [0, 0]
      Size: [127, 162]
    BufferedRegion:
      Dimension: 2
      Index: [0, 0]
      Size: [127, 162]
    RequestedRegion:
      Dimension: 2
      Index: [0, 0]
      Size: [127, 162]
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
      ImportImageContainer (0x3282c00)
        RTTI typeinfo:   itk::ImportImageContainer<unsigned long, itk::RGBPixel<unsigned char> >
        Reference Count: 1
        Modified Time: 27
        Debug: Off
        Object Name:
        Observers:
          none
        Pointer: 0x3196130
        Container manages memory: false
        Size: 20574
        Capacity: 20574


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
