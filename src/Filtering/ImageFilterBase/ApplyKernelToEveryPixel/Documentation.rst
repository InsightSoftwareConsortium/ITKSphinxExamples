Apply Kernel To Every Pixel
===========================

.. index::
   single: NeighborhoodOperatorImageFilter
   pair: kernel; pixel

Synopsis
--------

Apply a kernel to every pixel in an image.


Results
-------
.. figure:: input.png
  :scale: 300%
  :alt: input.png image generated

  Input image.

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

.. breathelink:: itk::NeighborhoodOperatorImageFilter
