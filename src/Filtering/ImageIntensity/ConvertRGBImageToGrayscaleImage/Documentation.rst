Convert RGB Image To Grayscale Image
====================================

.. index::
   single: RGBToLuminanceImageFilter

Synopsis
--------


Convert a RGB Image to its luminance image (grayscale one).


Results
-------

.. figure:: itk_eg_logo.png
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
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
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::RGBToLuminanceImageFilter
