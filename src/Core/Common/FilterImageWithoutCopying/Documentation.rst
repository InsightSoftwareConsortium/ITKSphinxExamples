Filter Image Without Copying Its Data
=====================================

.. index::
   single: InPlaceImageFilter

Synopsis
--------

Filter an image without copying its data.


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input image

  Input image.

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image.


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

.. breathelink:: itk::InPlaceImageFilter
