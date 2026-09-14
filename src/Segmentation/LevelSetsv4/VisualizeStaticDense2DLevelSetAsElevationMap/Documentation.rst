:name: VisualizeStaticDense2DLevelSetAsElevationMap

Visualize a Static Dense 2D Level Set as Elevation Map
======================================================

.. index::
   single: BinaryImageToLevelSetImageAdaptor
   single: LevelSetDenseImage

Synopsis
--------

Convert a binary mask into a dense level-set function and write the function
values as an image. Rendered as a height field, these values form an elevation
map whose zero level is the contour. The mask comes from an Otsu threshold of
the input image.


Results
-------

.. figure:: cells.png
  :scale: 100%
  :alt: Input image (cells)

  Input image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::LevelSetDenseImage
