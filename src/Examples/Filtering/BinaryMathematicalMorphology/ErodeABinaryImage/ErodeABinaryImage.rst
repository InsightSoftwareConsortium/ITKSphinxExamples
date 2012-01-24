Erode a binary image
====================

.. index::
  single: BinaryBallStructuringElement
  single: BinaryErodeImageFilter
  pair: mathematical morphology; erosion
  pair: BinaryBallStructuringElement; SetRadius
  seealso: erosion; dilation


Synopsis
--------
Erode regions by using a specified kernel, also known as a structuring element.  In this example, the white regions shrink.


Code
----

C++
...

.. literalinclude:: ErodeABinaryImage.cxx


Results
-------

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

  Input binary image.

.. figure:: ErodeABinaryImageOutputBaseline.png
  :scale: 50%
  :alt: Eroded output.

  Eroded output.


Classes demonstrated
--------------------

.. doxygenclass:: itk::BinaryErodeImageFilter
  :no-link:

* `BinaryErodeImageFilter detailed doxygen documentation`_

.. doxygenclass:: itk::BinaryBallStructuringElement
  :no-link:

* `BinaryBallStructuringElement detailed doxygen documentation`_

.. _BinaryErodeImageFilter detailed doxygen documentation:
  http://www.itk.org/Doxygen/html/classitk_1_1BinaryErodeImageFilter.html
.. _BinaryBallStructuringElement detailed doxygen documentation:
  http://www.itk.org/Doxygen/html/classitk_1_1BinaryBallStructuringElement.html
