:name: ComputesSmoothingWithGaussianKernel

Computes Smoothing With Gaussian Kernel
=======================================

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

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::SmoothingRecursiveGaussianImageFilter
