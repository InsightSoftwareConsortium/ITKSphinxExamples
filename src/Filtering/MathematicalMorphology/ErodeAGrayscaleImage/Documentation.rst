Erode a grayscale image
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

C++
...

.. literalinclude:: Code.cxx

Python
......

.. literalinclude:: ErodeAGrayscaleImage.py


Classes demonstrated
--------------------

.. breathelink:: itk::GrayscaleErodeImageFilter itk::FlatStructuringElement