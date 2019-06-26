Iterate Region In Image With Neighborhood Without Write Access
==============================================================

.. index::
   single: ConstNeighborhoodIterator
   pair: write; access
   single: neighborhood

Synopsis
--------

Iterate over a region of an image with a neighborhood (without write access).


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
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ConstNeighborhoodIterator
