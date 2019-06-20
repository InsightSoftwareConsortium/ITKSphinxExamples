Make Part Of An Image Transparent
=================================

.. index::
   single: RGBAPixel
   single: transparency

Synopsis
--------

Demonstrates how to assign transparency to pixels in an image, then writing the result to a tif file for inspection and verification.


Results
-------
.. figure:: test.tif
  :scale: 50%
  :alt: test.tif

  Output image.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::RGBAPixel
