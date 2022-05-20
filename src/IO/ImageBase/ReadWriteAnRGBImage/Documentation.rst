:name: WriteAnImage

Write an Image
==============

.. index::
   single: itk::Image
   single: itk::ImageFileReader
   single: itk::ImageFileWriter
   single: itk::RGBPixelImage


Synopsis
--------

RGB images are commonly used for representing data acquired from
cryogenic sections, optical microscopy and endoscopy. This example
illustrates how to read and write RGB color images to and from a file.


Results
-------
.. figure:: WriteAnImage.png
  :scale: 70%
  :alt: test.png

  test.png


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

.. breathelink:: itk::RGBPixelImage
