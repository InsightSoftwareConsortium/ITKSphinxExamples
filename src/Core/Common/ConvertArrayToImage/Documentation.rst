:name: ConvertArrayToImage

Convert Array to Image
======================

.. index::
   single: ImportImageFilter
   pair: array; convert
   pair: array; image

Synopsis
--------

Convert a C-style array to an itkImage.


Results
-------
.. figure:: ConvertArrayToImageOutput.png
  :scale: 70%
  :alt: test.png

  Output Image.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImportImageFilter
