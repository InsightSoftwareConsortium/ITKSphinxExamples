:name: ComputeFFTInOneDimension

Compute Forward FFT In One Dimension
====================================

.. index::
   single: Forward1DFFTImageFilter
   single: ComplexToRealImageFilter
   single: ComplexToImaginaryImageFilter
   single: ComplexToModulusImageFilter
   single: CyclicShiftImageFilter
   single: ImageFileReader
   single: ImageFileWriter

Synopsis
--------

Compute forward FFT of an image in one dimension.


Results
-------

.. figure:: MouseLiverRFInput.png
  :scale: 50%
  :alt: Input image

  Input RF Ultrasound Image

.. figure:: MouseLiverModulusOutput.png
  :scale: 50%
  :alt: Modulus Image

  Output Modulus Image

.. figure:: MouseLiverPhaseOutput.png
  :scale: 50%
  :alt: Phase Image

  Output Phase Image

Output::

  Read real input image of type <class 'itk.itkImagePython.itkImageF2'> and size itkSize2 ([1536, 128])
  Padded input image to size itkSize2 ([1536, 128])
  Performing FFT along axis 0
  Generated complex frequency image of type <class 'itk.itkImagePython.itkImageCF2'> and size itkSize2 ([1536, 128])

Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-


Classes demonstrated
--------------------

.. breathelink:: itk::FFTPadImageFilter

.. breathelink:: itk::Forward1DFFTImageFilter

.. breathelink:: itk::CyclicShiftImageFilter

.. breathelink:: itk::ComplexToModulusImageFilter

.. breathelink:: itk::ComplexToPhaseImageFilter
