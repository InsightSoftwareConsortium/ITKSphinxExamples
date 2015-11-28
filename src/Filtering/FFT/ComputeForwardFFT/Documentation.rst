Compute Forward FFT
===================

.. index::
   single: ForwardFFTImageFilter
   single: ComplexToRealImageFilter
   single: ComplexToImaginaryImageFilter
   single: ComplexToModulusImageFilter
   single: RescaleIntensityImageFilter
   single: WrapPadImageFilter
   single: NumericTraits
   single: ImageFileReader
   single: ImageFileWriter

Synopsis
--------

Compute forward FFT of an image.


Results
-------

.. figure:: HeadMRVolume.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: Real.png
  :scale: 50%
  :alt: Real image

  Output Real image

.. figure:: Complex.png
  :scale: 50%
  :alt: Imaginary image

  Output Imaginary image

.. figure:: Modulus.png
  :scale: 50%
  :alt: Modulus image

  Output Modulus image

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ForwardFFTImageFilter

.. breathelink:: itk::ComplexToRealImageFilter

.. breathelink:: itk::ComplexToImaginaryImageFilter

.. breathelink:: itk::ComplexToModulusImageFilter

.. breathelink:: itk::WrapPadImageFilter

.. breathelink:: itk::RescaleIntensityImageFilter
