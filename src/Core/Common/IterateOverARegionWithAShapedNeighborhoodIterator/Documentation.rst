Iterate Over A Region With A Shaped Neighborhood Iterator
=========================================================

.. index::
   single: ShapedNeighborhoodIterator

Synopsis
--------


Iterate over a region of an image with a shaped neighborhood.


Results
-------

Output::

  By default there are 0 active indices.
  Now there are 2 active indices.
  1 7
  New position:
  Centered at [0, 0]
  Neighborhood index 1 is offset [0, -1] and has value 0 The real index is [0, -1]
  Centered at [0, 0]
  Neighborhood index 7 is offset [0, 1] and has value 0 The real index is [0, 1]
  New position:
  Centered at [1, 0]
  Neighborhood index 1 is offset [0, -1] and has value 0 The real index is [1, -1]
  Centered at [1, 0]
  Neighborhood index 7 is offset [0, 1] and has value 0 The real index is [1, 1]
  New position:
  Centered at [2, 0]
  Neighborhood index 1 is offset [0, -1] and has value 0 The real index is [2, -1]
  Centered at [2, 0]
  Neighborhood index 7 is offset [0, 1] and has value 0 The real index is [2, 1]

  [...]

  New position:
  Centered at [7, 9]
  Neighborhood index 1 is offset [0, -1] and has value 0 The real index is [7, 8]
  Centered at [7, 9]
  Neighborhood index 7 is offset [0, 1] and has value 0 The real index is [7, 10]
  New position:
  Centered at [8, 9]
  Neighborhood index 1 is offset [0, -1] and has value 0 The real index is [8, 8]
  Centered at [8, 9]
  Neighborhood index 7 is offset [0, 1] and has value 0 The real index is [8, 10]
  New position:
  Centered at [9, 9]
  Neighborhood index 1 is offset [0, -1] and has value 0 The real index is [9, 8]
  Centered at [9, 9]
  Neighborhood index 7 is offset [0, 1] and has value 0 The real index is [9, 10]


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ShapedNeighborhoodIterator
