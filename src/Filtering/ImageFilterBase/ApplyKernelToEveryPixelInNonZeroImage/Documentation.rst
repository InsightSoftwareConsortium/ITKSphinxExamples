Apply Kernel to Every Pixel in Non-Zero Image
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
  :scale: 70%
  :alt: input.png

  input.png

.. figure:: mask.png
  :scale: 70%
  :alt: mask.png

  mask.png

.. figure:: output.png
  :scale: 70%
  :alt: output.png

  output.png

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MaskNeighborhoodOperatorImageFilter
