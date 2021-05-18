:name: SmoothImageWithDiscreteGaussianFilter

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
.. figure:: Yinyang.png
  :scale: 70%

  Input image.

.. figure:: SmoothImageWithDiscreteGaussianFilter.png
  :scale: 70%

  Yinyang.png And Output.png With Variance = 8

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::DiscreteGaussianImageFilter
