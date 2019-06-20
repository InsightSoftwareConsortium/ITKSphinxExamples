Create Derivative Kernel
========================

.. index::
   single: DerivativeOperator
   pair: derivative; kernel

Synopsis
--------

Create a derivative kernel.


Results
-------
Output::

  Size: [3, 3]
  Neighborhood:
  Radius:[1, 1]
  Size:[3, 3]
  DataBuffer:NeighborhoodAllocator { this = 0x7ffeec8f19e8, begin = 0x7f822c2a8f00, size=9 }
  [-1, -1] 0
  [0, -1] 0
  [1, -1] 0
  [-1, 0] 0.5
  [0, 0] 0
  [1, 0] -0.5
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

.. breathelink:: itk::DerivativeOperator
