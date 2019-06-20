Normalized Correlation Using FFT With Mask Images For Input Images
==================================================================

.. index::
   single: MaskedFFTNormalizedCorrelationImageFilter
   pair: masked; input
   single: FFT

Synopsis
--------

Normalized correlation using the FFT with optional mask images for both input images.


Results
-------
.. figure:: fixedImage.png
  :scale: 600%
  :alt: fixedImage.png image generated

  Fixed image.

.. figure:: movingImage.png
  :scale: 600%
  :alt: movingImage.png

  Moving image.

.. figure:: NormalizedCorrelationUsingFFTWithMaskImages.png
  :scale: 50%
  :alt: correlation.mha generated

  correlation.mha

.. figure:: correlation.png
  :scale: 600%
  :alt: correlation.png image generated

  Correlation image.

Output::

  Maximum location: [45, 44]
  Maximum location fixed: [5, 6]
  Maximum value: 1

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MaskedFFTNormalizedCorrelationImageFilter
