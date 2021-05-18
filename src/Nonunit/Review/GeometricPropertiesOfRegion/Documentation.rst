:name: GeometricPropertiesOfRegion

Geometric Properties of Labeled Region
======================================

.. index::
   single: LabelGeometryImageFilter
   pair: geometric; property
   pair: geometric; region

Synopsis
--------

Get geometric properties of labeled regions in an image.


Results
-------
.. figure:: GeometricPropertiesOfRegionQuickview.png
   :scale: 50%
   :alt: QuickView output.

   Output In QuickView

Output::

  Image (0x7fd274c5f3c0)
  RTTI typeinfo:   itk::Image<unsigned int, 2u>
  Reference Count: 1
  Modified Time: 46
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
    Size: [20, 20]
  BufferedRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [20, 20]
  RequestedRegion:
    Dimension: 2
    Index: [0, 0]
    Size: [20, 20]
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
    ImportImageContainer (0x7fd274c5f5b0)
      RTTI typeinfo:   itk::ImportImageContainer<unsigned long, unsigned int>
      Reference Count: 1
      Modified Time: 47
      Debug: Off
      Object Name:
      Observers:
        none
      Pointer: 0x7fd27502d800
      Container manages memory: true
      Size: 400
      Capacity: 400
  Number of labels: 4

  Label: 0
  Volume: 344
  Integrated Intensity: 44128
  Centroid: [9.06977, 9.54942]
  Weighted Centroid: [9.44273, 9.96021]
  Axes Length: [23.6173, 23.9599]
  MajorAxisLength: 23.9599
  MinorAxisLength: 23.6173
  Eccentricity: 0.168492
  Elongation: 1.0145
  Orientation: 2.74768
  Bounding box: [0, 19, 0, 19]


  Label: 85
  Volume: 16
  Integrated Intensity: 2544
  Centroid: [7.5, 7.5]
  Weighted Centroid: [7.44811, 7.47602]
  Axes Length: [4.6188, 4.6188]
  MajorAxisLength: 4.6188
  MinorAxisLength: 4.6188
  Eccentricity: 0
  Elongation: 1
  Orientation: 1.5708
  Bounding box: [6, 9, 6, 9]

  Label: 127
  Volume: 25
  Integrated Intensity: 3263
  Centroid: [14, 14]
  Weighted Centroid: [13.6883, 14.1192]
  Axes Length: [5.7735, 5.7735]
  MajorAxisLength: 5.7735
  MinorAxisLength: 5.7735
  Eccentricity: 0
  Elongation: 1
  Orientation: 1.5708
  Bounding box: [12, 16, 12, 16]

  Label: 191
  Volume: 15
  Integrated Intensity: 1840
  Centroid: [14, 3]
  Weighted Centroid: [13.8647, 3.10978]
  Axes Length: [3.4641, 5.7735]
  MajorAxisLength: 5.7735
  MinorAxisLength: 3.4641
  Eccentricity: 0.8
  Elongation: 1.66667
  Orientation: 0
  Bounding box: [12, 16, 2, 4]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LabelGeometryImageFilter
