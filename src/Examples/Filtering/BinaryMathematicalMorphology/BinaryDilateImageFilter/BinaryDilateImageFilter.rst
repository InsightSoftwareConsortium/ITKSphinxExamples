Dilate a binary image
=====================

Synopsis
--------

Dilate regions by using a specified kernel, also known as a structuring element.
In this example, the white regions are enlarged.

Doxygen
-------

.. doxygenclass:: itk::BinaryDilateImageFilter

* `Corresponding detailed doxygen documentation`_
* `Doxygen documentation`_

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

.. _Corresponding detailed doxygen documentation:   http://www.itk.org/Doxygen/html/classitk_1_1BinaryDilateImageFilter.html
.. _Doxygen documentation:                          http://www.itk.org/Doxygen/html/index.html
