Read Write Vector Image
=======================

.. index::
   single: Image
   single: read
   single: write

Synopsis
--------

This example illustrates how to read and write an image of pixel type Vector.


Results
-------

.. |input| image:: image.png
  :scale: 150%
  :alt: Input image

.. |output| image:: image.png
  :scale: 150%
  :alt: Output image

.. |input_caption| replace:: Input image.

.. |output_caption| replace:: Output image.

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
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::Image
