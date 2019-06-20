Create Laplacian Kernel
=======================

.. index::
   single: LaplacianOperator
   pair: laplacian; operator
   pair: laplacian; kernel
   pair: create; kernel

Synopsis
--------

Create a Laplacian kernel.


Results
-------
Output::

  Size: [3, 3]
  Neighborhood:
  Radius:[1, 1]
  Size:[3, 3]
  DataBuffer:NeighborhoodAllocator { this = 0x7ffee97e29e0, begin = 0x7f87798a8810, size=9 }
  [-1, -1] 0
  [0, -1] 1
  [1, -1] 0
  [-1, 0] 1
  [0, 0] -4
  [1, 0] 1
  [-1, 1] 0
  [0, 1] 1
  [1, 1] 0

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LaplacianOperator
