Visualize A Static Dense 2D Level Set As Elevation Map
======================================================

.. index::
   single: VTKVisualize2DLevelSetAsElevationMap
   single: BinaryImageToLevelSetImageAdaptor
   single: LevelSetDenseImage

Synopsis
--------

Visualize a static dense level-set function 2D rendered as an elevation map.
From the input image, first an otsu thresholding technique is used to get a
binary mask, which is then converted to a dense level-set function.


Results
-------

.. figure:: cells.png
  :scale: 100%
  :alt: Input image (cells)

  Input image

.. figure:: levelsets.png
  :scale: 100%
  :alt: Static level-sets rendered as an elevation map

  Static level-sets


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. [breathelink:: itk::VTKVisualize2DLevelSetAsElevationMap]
