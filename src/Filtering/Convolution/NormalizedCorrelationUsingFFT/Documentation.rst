Normalized Correlation Using FFT
================================

.. index::
   single: FFTNormalizedCorrelationImageFilter

Synopsis
--------

Normalized correlation using the FFT.


Results
-------
.. figure:: fixedImage.png
  :scale: 600%
  :alt: fixedimage.png image generated

  Fixed image.

.. figure:: movingImage.png
  :scale: 600%
  :alt: movingimage.png image generated

  Moving image.

.. figure:: NormalizedCorrelationUsingFFT.png
  :scale: 50%
  :alt: correlation.mha

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

.. breathelink:: itk::FFTNormalizedCorrelationImageFilter
