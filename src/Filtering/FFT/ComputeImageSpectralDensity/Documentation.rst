Compute Image Spectral Density
==============================

.. index::
   single: ComplexToModulusImageFilter
   single: FFTShiftImageFilter
   single: ForwardFFTImageFilter
   single: Fast Fourier Transform
   single: spectral density


Synopsis
--------

Compute the magnitude of an image\'s spectral components.


Results
-------

.. figure:: Input.png
  :scale: 100%
  :alt: Input image

  Input image

.. figure:: Output.png
  :scale: 100%
  :alt: Output image of spectral density.

  Output image of spectral density.  The DC component is shifted to the center
  of the image.


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::ComplexToModulusImageFilter

.. breathelink:: itk::FFTShiftImageFilter
