Smooth Image With Discrete Gaussian Filter
==========================================

.. index::
   single: DiscreteGaussianImageFilter
   pair: gaussian; filter

Synopsis
--------

Smooth an image with a discrete Gaussian filter.


Results
-------
.. filter:: SmoothImageWithDiscreteGaussianFilter.png
  :scale: 60%
  :alt: output in vtk window

  Input and output image with variance = 8.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::DiscreteGaussianImageFilter
