:name: VisualizeStaticWhitaker2DLevelSetLayers

Visualize a Static Sparse Whitaker 2D Level-Set Layers
======================================================

.. index::
   single: BinaryImageToLevelSetImageAdaptor
   single: WhitakerSparseLevelSetImage

Synopsis
--------

Convert a binary mask into a sparse Whitaker level-set function and write its
layers as an image, by sampling the function at every pixel. The mask comes
from an Otsu threshold of the input image.

The written values are -3, -2, -1, 0, 1, 2, and 3.


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

.. breathelink:: itk::WhitakerSparseLevelSetImage
