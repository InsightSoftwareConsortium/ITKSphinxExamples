Change Image Origin Spacing Or Direction
========================================

.. index::
   single: ChangeInformationImageFilter

Synopsis
--------

Change an Image's Origin, Spacing, or Direction.

The `ChangeInformationImageFilter` is commonly used to modify image metadata
such as *Origin*, *Spacing*, and *Orientation*. This filter leaves intact the
pixel data of the image. This filter should be used with extreme caution, since
it can easily change information that is critical for the safety of many medical
image analysis tasks, such as measurement the volume of a tumor, or providing
guidance for surgery.


Results
-------

::

  Original image: Image (0x3131ce0)
    RTTI typeinfo:   itk::Image<unsigned char, 3u>
    Reference Count: 3
    Modified Time: 195
    Debug: Off
    Object Name:
    Observers:
      none
    Source: (0x312d620)
    Source output name: Primary
    Release Data: Off
    Data Released: False
    Global Release Data: Off
    PipelineMTime: 47
    UpdateMTime: 0
    RealTimeStamp: 0 seconds
    LargestPossibleRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [48, 62, 42]
    BufferedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [0, 0, 0]
    RequestedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [0, 0, 0]
    Spacing: [4, 4, 4]
    Origin: [0, 0, 0]
    Direction:
  1 0 0
  0 1 0
  0 0 1

    IndexToPointMatrix:
  4 0 0
  0 4 0
  0 0 4

    PointToIndexMatrix:
  0.25 0 0
  0 0.25 0
  0 0 0.25

    Inverse Direction:
  1 0 0
  0 1 0
  0 0 1

    PixelContainer:
      ImportImageContainer (0x3131fa0)
        RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned char>
        Reference Count: 1
        Modified Time: 34
        Debug: Off
        Object Name:
        Observers:
          none
        Pointer: 0
        Container manages memory: true
        Size: 0
        Capacity: 0

  **************************************
  Changed image: Image (0x3137100)
    RTTI typeinfo:   itk::Image<unsigned char, 3u>
    Reference Count: 3
    Modified Time: 222
    Debug: Off
    Object Name:
    Observers:
      none
    Source: (0x3132240)
    Source output name: Primary
    Release Data: Off
    Data Released: False
    Global Release Data: Off
    PipelineMTime: 215
    UpdateMTime: 0
    RealTimeStamp: 0 seconds
    LargestPossibleRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [48, 62, 42]
    BufferedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [0, 0, 0]
    RequestedRegion:
      Dimension: 3
      Index: [0, 0, 0]
      Size: [0, 0, 0]
    Spacing: [8.4, 8.4, 8.4]
    Origin: [8.4, 2.9, 4.4]
    Direction:
  0.866025 -0.5 0
  0.5 0.866025 0
  0 0 1

    IndexToPointMatrix:
  7.27461 -4.2 0
  4.2 7.27461 0
  0 0 8.4

    PointToIndexMatrix:
  0.103098 0.0595238 0
  -0.0595238 0.103098 0
  0 0 0.119048

    Inverse Direction:
  0.866025 0.5 0
  -0.5 0.866025 0
  0 0 1

    PixelContainer:
      ImportImageContainer (0x3137520)
        RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned char>
        Reference Count: 1
        Modified Time: 200
        Debug: Off
        Object Name:
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

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::ChangeInformationImageFilter
