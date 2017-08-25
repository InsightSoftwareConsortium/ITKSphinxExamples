Computes the smoothing with Gaussian kernel
===========================================

.. index::
   single: SmoothingRecursiveGaussianImageFilter
   single: smooth

Synopsis
--------

Computes the smoothing of an image by convolution with Gaussian kernels.


Results
-------

.. figure:: BrainProtonDensitySlice.png
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-

Classes demonstrated
--------------------

.. breathelink:: itk::SmoothingRecursiveGaussianImageFilter
