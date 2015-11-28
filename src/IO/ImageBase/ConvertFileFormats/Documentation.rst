Convert File Formats
====================

.. index::
   single: ImageFileReader, ImageFileWriter

Synopsis
--------

Convert from one image file format to another.  ITK will automatically detect
the file type of the input and output files by their extension, and an
`itk::ImageFileReader` and `itk::ImageFileWriter` will use the appropriate
`ImageIO` class.


Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Gourds.png

  Gourds.png

.. figure:: OutputBaseline.jpg
  :scale: 50%
  :alt: Gourds.jpg

  Gourds.jpg


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageFileReader itk::ImageFileWriter
