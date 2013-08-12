Visualize A Static Dense 2D Level-Set Zero-Set
==============================================

.. index::
   single: VTKVisualize2DLevelSetAsZeroSet
   single: BinaryImageToLevelSetImageAdaptor
   single: LevelSetDenseImage

Synopsis
--------

Visualize a static dense level-set function 2D's zero set. From the input
image, first an otsu thresholding technique is used to get a binary mask, which
is then converted to a dense level-set function.


Results
-------

.. figure:: cells.png
  :scale: 100%
  :alt: Input image (cells)

  Input image

.. figure:: levelsets.png
  :scale: 100%
  :alt: Static level-sets zero-sets

  Static level-sets


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::VTKVisualize2DLevelSetAsZeroSet
