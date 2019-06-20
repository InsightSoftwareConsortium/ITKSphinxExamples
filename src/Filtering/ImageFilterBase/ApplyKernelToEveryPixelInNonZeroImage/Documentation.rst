Apply Kernel To Every Pixel In Non-Zero Image
=============================================

.. index::
   single: MaskNeighborhoodOperatorImageFilter
   pair: mask; non-zero
   single: kernel

Synopsis
--------

Apply a kernel to every pixel in an image that is non-zero in a mask.


Results
-------
.. figure:: input.png
  :scale: 300%
  :alt: input.png image generated

  Input image.

.. figure:: mask.png
  :scale: 300%
  :alt: mask.png image generated

  Mask image.

.. figure:: output.png
  :scale: 300%
  :alt: output.png image generated

  Output image.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MaskNeighborhoodOperatorImageFilter
