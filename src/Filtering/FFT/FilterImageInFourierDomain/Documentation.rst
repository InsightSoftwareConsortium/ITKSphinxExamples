Filter Image in Fourier Domain
==============================

.. index::
   single: FFTShiftImageFilter
   single: ForwardFFTImageFilter
   single: InverseFFTImageFilter
   single: Fast Fourier Transform


Synopsis
--------

Filter an Image in the Fourier Domain
One of the most common image processing operations performed in the Fourier
Domain is the masking of the spectrum in order to modulate a range of
spatial frequencies from the input image. This operation is typically
performed by taking the input image, computing its Fourier transform using
a FFT filter, masking the resulting image in the Fourier domain with a
mask, and finally taking the result of the masking and computing its
inverse Fourier transform.


Results
-------

.. figure:: Input.png
  :scale: 100%
  :alt: Input image

  Input image

.. figure:: Output.png
  :scale: 100%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ForwardFFTImageFilter

.. breathelink:: itk::FFTShiftImageFilter

.. breathelink:: itk::MultiplyImageFilter

.. breathelink:: itk::InverseFFTImageFilter
