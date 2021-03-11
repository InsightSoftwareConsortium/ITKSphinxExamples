Visualize a Static Sparse Whitaker 2D Level-Set Layers
======================================================

.. index::
   single: vtkVisualize2DSparseLevelSetLayers
   single: BinaryImageToLevelSetImageAdaptor
   single: WhitakerSparseLevelSetImage

Synopsis
--------

Visualize a static sparse Whitaker level-set function 2D's layers. From the input
image, first an otsu thresholding technique is used to get a binary mask, which
is then converted to a sparse level-set function.

Note that Whitaker's representation is composed of 5 layers where values are real.

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
   :lines: 18-


Classes demonstrated
--------------------

.. [breathelink:: itk::VTKVisualize2DSparseLevelSetLayers]
