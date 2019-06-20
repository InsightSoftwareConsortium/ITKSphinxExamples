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
.. figure:: Yinyang.png
  :scale: 60%
  :alt: yin-yang input image

  Input image.

Output::

  -1 -1
  0 -1
  1 -1
  -1 0
  0 0
  1 0
  -1 1
  0 1
  1 1
  0 -1
  1 -1
  2 -1
  0 0
  1 0
  2 0
  0 1
  1 1
  2 1
  1 -1
  2 -1
  3 -1
  1 0
  2 0
  3 0
  1 1
  2 1
  3 1
  2 -1
  3 -1
  4 -1
  2 0
  3 0
  4 0
  2 1
  3 1
  4 1
  3 -1
  4 -1
  5 -1
  3 0
  4 0
  5 0
  3 1
  4 1
  5 1
  4 -1
  5 -1
  6 -1
  4 0
  5 0
  6 0
  4 1
  5 1
  6 1
  5 -1
  6 -1
  7 -1
  5 0
  6 0
  7 0
  5 1
  6 1
  7 1
  6 -1
  7 -1
  8 -1
  6 0
  7 0
  8 0
  6 1
  7 1
  8 1
  7 -1
  8 -1
  9 -1
  7 0
  8 0
  9 0

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
