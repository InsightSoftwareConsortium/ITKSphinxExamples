Create Forward Difference Kernel
================================

.. index::
   single: ForwardDifferenceOperator
   pair: difference; kernel

Synopsis
--------

Create a forward difference kernel.


Results
-------
Output::

  Size: [3, 3]
  Neighborhood:
  Radius:[1, 1]
  Size:[3, 3]
  DataBuffer:NeighborhoodAllocator { this = 0x7ffee23339e0, begin = 0x7fd6921a8f60, size=9 }
  [-1, -1] 0
  [0, -1] 0
  [1, -1] 0
  [-1, 0] 0
  [0, 0] -1
  [1, 0] 1
  [-1, 1] 0
  [0, 1] 0
  [1, 1] 0

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ForwardDifferenceOperator
