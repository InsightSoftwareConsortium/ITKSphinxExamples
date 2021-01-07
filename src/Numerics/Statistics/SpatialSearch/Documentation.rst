Spatial Search
==============

.. index::
   single: KdTreeGenerator

Synopsis
--------

Spatial search.


Results
-------
Output::

  K-Neighbor search:
  [9, 9]
  [7, 7]
  [8, 8]
  Radius search:
  There are 4 neighbors.
  [7, 7]
  [8, 8]
  [9, 9]
  [10, 10]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Statistics::KdTreeGenerator
