Dilate a grayscale image
========================

.. index::
  single: FlatStructuringElement
  single: GrayscaleDilateImageFilter
  pair: mathematical morphology; dilation

.. seealso:: dilation; erosion


Synopsis
--------

Dilate regions by using a specified kernel, also known as a structuring element. In this example, the white regions are enlarged.


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input ct head image.

  Input grayscale image.

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Dilated output.

  Dilated output.


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
   :lines: 1, 16-


Classes demonstrated
--------------------

.. breathelink:: itk::GrayscaleDilateImageFilter itk::FlatStructuringElement
