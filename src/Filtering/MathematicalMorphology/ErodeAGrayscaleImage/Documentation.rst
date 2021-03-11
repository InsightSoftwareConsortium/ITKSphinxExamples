Erode a Grayscale Image
=======================

.. index::
  single: FlatStructuringElement
  single: GrayscaleErodeImageFilter
  pair: mathematical morphology; erosion

.. seealso:: erosion; dilation


Synopsis
--------
Erode regions by using a specified kernel, also known as a structuring element. In this example, the white regions shrink.


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input ct head image.

  Input grayscale image.

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Eroded output.

  Eroded output.


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

.. breathelink:: itk::GrayscaleErodeImageFilter itk::FlatStructuringElement
