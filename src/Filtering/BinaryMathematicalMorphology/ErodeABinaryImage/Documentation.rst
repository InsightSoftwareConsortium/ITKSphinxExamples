Erode a Binary Image
====================

.. index::
  single: BinaryBallStructuringElement
  single: BinaryErodeImageFilter
  pair: mathematical morphology; erosion
  pair: BinaryBallStructuringElement; SetRadius

.. seealso:: erosion; dilation


Synopsis
--------
Erode regions by using a specified kernel, also known as a structuring element.  In this example, the white regions shrink.


Results
-------

.. |input| image:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

.. |output| image:: OutputBaseline.png
  :scale: 50%
  :alt: Eroded output.

.. |input_caption| replace:: Input binary image.

.. |output_caption| replace:: Eroded output image.

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
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryErodeImageFilter itk::BinaryBallStructuringElement
