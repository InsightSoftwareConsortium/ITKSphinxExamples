:name: ComputeInverseFFTOfImage

Compute Inverse FFT of Image
============================

.. index::
   single: InverseFFTImageFilter
   single: FFT
   single: inverse

Synopsis
--------

Compute the inverse FFT of an image.


Results
-------
.. figure:: ComputeInverseFFTOfImage.png
  :scale: 70%
  :alt: ifft.png

  ifft.png

Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::InverseFFTImageFilter
