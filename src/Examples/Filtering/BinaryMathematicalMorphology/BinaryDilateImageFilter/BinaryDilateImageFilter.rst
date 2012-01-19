Dilate a binary image
=====================

Synopsis
--------

Dilate regions by using a specified kernel, also known as a structuring element.
In this example, the white regions are enlarged.

Doxygen
-------

.. doxygenclass:: itk::BinaryDilateImageFilter

Code
----

C++
...

.. literalinclude:: BinaryDilateImageFilter.cxx

Results
-------

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

  Input binary image.

.. figure:: BinaryDilateImageFilterOutputBaseline.png
  :scale: 50%
  :alt: Dilated output.

  Dilated output.

