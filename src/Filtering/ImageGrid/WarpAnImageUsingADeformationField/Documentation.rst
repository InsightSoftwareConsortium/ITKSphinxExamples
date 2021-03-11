Warp an Image Using a Deformation Field
=======================================

.. index::
   single: WarpImageFilter

Synopsis
--------

Use WarpImageFilter and a deformation field for resampling an image.


Results
-------

.. figure:: WarpImageFilterInput.png
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :alt: Output image

  Output image


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

.. breathelink:: itk::WarpImageFilter
