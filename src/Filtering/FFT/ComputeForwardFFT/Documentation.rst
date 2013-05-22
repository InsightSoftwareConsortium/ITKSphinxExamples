Compute Forward FFT
===================

.. index::
   single: ForwardFFTImageFilter
   single: ComplexToRealImageFilter
   single: RescaleIntensityImageFilter
   single: NumericTraits
   single: ImageFileReader
   single: ImageFileWriter

Synopsis
--------

Compute forward FFT of an image


Results
-------

.. figure::
  :scale: 50%
  :alt: Input image

  Input image

.. figure::
  :scale: 50%
  :alt: Real image

  Output Real image

.. figure::
  :scale: 50%
  :alt: Imaginary image

  Output Imaginary image

.. figure::
  :scale: 50%
  :alt: Modulus image

  Output Modulus image

Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::ForwardFFTImageFilter

.. breathelink:: itk::ComplexToRealImageFilter

.. breathelink:: itk::RescaleIntensityImageFilter
