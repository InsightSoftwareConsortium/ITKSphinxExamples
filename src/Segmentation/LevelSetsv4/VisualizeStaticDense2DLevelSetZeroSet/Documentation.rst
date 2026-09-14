:name: VisualizeStaticDense2DLevelSetZeroSet

Visualize a Static Dense 2D Level-Set Zero-Set
==============================================

.. index::
   single: BinaryImageToLevelSetImageAdaptor
   single: LevelSetDenseImage
   single: ZeroCrossingImageFilter

Synopsis
--------

Convert a binary mask into a dense level-set function, extract its zero set
with itk::ZeroCrossingImageFilter, and write the contour as an image. The mask
comes from an Otsu threshold of the input image.


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
