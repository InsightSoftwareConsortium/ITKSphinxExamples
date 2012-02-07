Flip an image over specified axes
=================================

.. index::
  single: FlipImageFilter


Synopsis
--------

Flip an image over the specified axes.  Pixels are swapped over the given axis.

Results
-------

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: FlipAnImageOverSpecifiedAxesOutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: FlipAnImageOverSpecifiedAxes.cxx

Python
......

.. literalinclude:: FlipAnImageOverSpecifiedAxes.py


Classes demonstrated
--------------------

.. doxygenclass:: itk::FlipImageFilter
  :no-link:

* Detailed documentation: :itkdox:`itk::FlipImageFilter`
