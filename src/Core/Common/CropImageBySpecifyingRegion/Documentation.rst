:name: CropImageBySpecifyingRegion

Crop Image by Specifying Region
===============================

.. index::
   single: ExtractImageFilter
   pair: crop; region

Synopsis
--------

Crop an image by specifying the region to keep.

.. figure:: 3DVolume.png
  :scale: 70%
  :alt: 3dvolume.png

.. figure:: ExtractedSlice.png
  :scale: 70%
  :alt: extractedslice.png

Extracting a 2D slice from a 3D volume.

Results
-------
Output::

  Image largest region: ImageRegion (0x7f886fc0de00)
  Dimension: 2
  Index: [0, 0]
  Size: [10, 10]

  desiredRegion: ImageRegion (0x7ffeef707978)
  Dimension: 2
  Index: [3, 3]
  Size: [4, 4]

  new largest region: ImageRegion (0x7f886fc0eb00)
  Dimension: 2
  Index: [3, 3]
  Size: [4, 4]

  new: 2
  Original: 5

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ExtractImageFilter
