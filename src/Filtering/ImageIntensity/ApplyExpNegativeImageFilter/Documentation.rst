Apply Exp Negative Image Filter
===============================

.. index::
   single: ExpNegativeImageFilter

Synopsis
--------

Compute :math:`exp(-K x)` of each pixel.


Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: Output.png
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
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::ExpNegativeImageFilter
