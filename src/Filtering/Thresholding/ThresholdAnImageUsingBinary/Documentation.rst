Threshold An Image Using Binary Thresholding
============================================

.. index::
   single: BinaryThresholdImageFilter

Synopsis
--------


Binarize an input image by thresholding.


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-

Classes demonstrated
--------------------

.. breathelink:: itk::BinaryThresholdImageFilter
