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

Python
......

.. literalinclude:: Code.py

Classes demonstrated
--------------------

.. breathelink:: itk::SmoothingRecursiveGaussianImageFilter
