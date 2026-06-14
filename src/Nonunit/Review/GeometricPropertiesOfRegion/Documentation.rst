:name: GeometricPropertiesOfRegion

Geometric Properties of Labeled Region
======================================

.. index::
   single: LabelImageToShapeLabelMapFilter
   single: LabelStatisticsImageFilter
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

  Number of labels: 3

  	Label: 85
  	Physical size: 16
  	Number of pixels: 16
  	Centroid: [7.5, 7.5]
  	Equivalent ellipsoid diameter: [4.51352, 4.51352]
  	Elongation: 1
  	Flatness: 1
  	Principal axes: 1 0
  0 1

  	Bounding box: ImageRegion
    Dimension: 2
    Index: [6, 6]
    Size: [4, 4]

  	Integrated intensity: 2487
  	Mean intensity: 155.438


  	Label: 127
  	Physical size: 25
  	Number of pixels: 25
  	Centroid: [14, 14]
  	Equivalent ellipsoid diameter: [5.6419, 5.6419]
  	Elongation: 1
  	Flatness: 1
  	Principal axes: 1 0
  0 1

  	Bounding box: ImageRegion
    Dimension: 2
    Index: [12, 12]
    Size: [5, 5]

  	Integrated intensity: 4310
  	Mean intensity: 172.4


  	Label: 191
  	Physical size: 15
  	Number of pixels: 15
  	Centroid: [14, 3]
  	Equivalent ellipsoid diameter: [3.32063, 5.7515]
  	Elongation: 1.73205
  	Flatness: 1.73205
  	Principal axes: 0 1
  -1 -0

  	Bounding box: ImageRegion
    Dimension: 2
    Index: [12, 2]
    Size: [5, 3]

  	Integrated intensity: 2155
  	Mean intensity: 143.667

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LabelImageToShapeLabelMapFilter

.. breathelink:: itk::LabelStatisticsImageFilter
