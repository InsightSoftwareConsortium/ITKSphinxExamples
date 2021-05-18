:name: IterateWithNeighborhoodWithoutAccess

Iterate Region in Image With Neighborhood Without Write Access
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
  :scale: 70%

  Yinyang.png input image.

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
  ...


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ConstNeighborhoodIterator
