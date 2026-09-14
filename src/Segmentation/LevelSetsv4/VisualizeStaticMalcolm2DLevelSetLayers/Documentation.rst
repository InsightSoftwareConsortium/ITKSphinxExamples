:name: VisualizeStaticMalcolm2DLevelSetLayers

Visualize a Static Sparse Malcolm 2D Level-Set Layers
=====================================================

.. index::
   single: BinaryImageToLevelSetImageAdaptor
   single: MalcolmSparseLevelSetImage

Synopsis
--------

Convert a binary mask into a sparse Malcolm level-set function and write its
layers as an image, by sampling the function at every pixel. The mask comes
from an Otsu threshold of the input image.

The written values are -1, 0, and 1.


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

.. breathelink:: itk::MalcolmSparseLevelSetImage
