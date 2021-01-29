Compute Laplacian
=================

.. index::
   single: LaplacianImageFilter

Synopsis
--------

This filter computes the Laplacian of a scalar-valued image.


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


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
   :lines: 1, 16-

Classes demonstrated
--------------------

.. breathelink:: itk::LaplacianImageFilter
