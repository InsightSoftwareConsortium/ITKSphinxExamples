Dilate a binary image
=====================

Dilate regions by using a specified kernel.  In this example, the white regions
are enlarged.

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

  Input binary image.

.. figure:: BinaryDilateImageFilterOutputBaseline.png
  :scale: 50%
  :alt: Dilated output.

  Dilated output.

.. doxygenclass:: itk::BinaryDilateImageFilter

.. literalinclude:: BinaryDilateImageFilter.cxx
