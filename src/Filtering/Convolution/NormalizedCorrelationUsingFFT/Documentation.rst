:name: NormalizedCorrelationUsingFFT

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
  :scale: 70%
  :alt: fixedImage.png

  fixedImage.png

.. figure:: movingImage.png
  :scale: 70%
  :alt: movingImage.png

  movingImage.png

.. figure:: NormalizedCorrelationUsingFFT.png
  :scale: 70%
  :alt: correlation.mha

  correlation.mha

.. figure:: correlation.png
  :scale: 70%
  :alt: correlation.png

  correlation.png

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
