Dilate a Binary Image
=====================

.. index::
  single: BinaryBallStructuringElement
  single: BinaryDilateImageFilter
  pair: mathematical morphology; dilation
  pair: BinaryBallStructuringElement; SetRadius

.. seealso:: dilation; erosion


Synopsis
--------

Dilate regions by using a specified kernel, also known as a structuring element.
In this example, the white regions are enlarged.


Results
-------

.. |input| image:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

.. |output| image:: OutputBaseline.png
  :scale: 50%
  :alt: Dilated output.

.. |input_caption| replace:: Input binary image.

.. |output_caption| replace:: Dilated output image.

+-----------------+------------------+
|     |input|     |     |output|     |
+                 +                  +
| |input_caption| | |output_caption| |
+-----------------+------------------+


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

.. breathelink:: itk::BinaryDilateImageFilter itk::BinaryBallStructuringElement
