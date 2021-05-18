:name: StatisticalPropertiesOfRegions

Statistical Properties of Labeled Regions
=========================================

.. index::
   single: LabelStatisticsImageFilter
   pair: label; regions
   pair: statistics; regions

Synopsis
--------

Get statistical properties of labeled regions in an image.


Results
-------
.. figure:: StatisticalPropertiesOfRegions.png
  :scale: 70%
  :alt: image.png

  image.png

Output::

  Number of labels: 2

  min: 255
  max: 255
  median: 0
  mean: 255
  sigma: 0
  variance: 0
  sum: 4080
  count: 16
  region: ImageRegion (0x7ffedfd04a28)
  Dimension: 2
  Index: [6, 6]
  Size: [4, 4]

  min: 0
  max: 0
  median: 0
  mean: 0
  sigma: 0
  variance: 0
  sum: 0
  count: 384
  region: ImageRegion (0x7ffedfd04a28)
  Dimension: 2
  Index: [0, 0]
  Size: [20, 20]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LabelStatisticsImageFilter
