:name: ConvolveImageWithKernel

Convolve Image With Kernel
==========================

.. index::
   single: ConvolutionImageFilter
   single: convolution

Synopsis
--------

Convolve an image with a kernel.


Results
-------
.. figure:: Yinyang.png
  :scale: 70%
  :alt: input image

  Input image.

.. figure:: ConvolveImageWithKernel.png
  :scale: 70%

  Output In VTK Window

.. figure:: MatplotlibVisualizeConvolution.png
  :scale: 70%

  Output In Matplotlib

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ConvolutionImageFilter
