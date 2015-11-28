Create A Backward Difference Operator
=====================================

.. index::
   single: BackwardDifferenceOperator

Synopsis
--------


Create a backward difference operator


Results
-------

Output::

  Size: [3, 3]
  Neighborhood:
      Radius:[1, 1]
      Size:[3, 3]
      DataBuffer:NeighborhoodAllocator { this = 0x7fffb3cae9f8, begin = 0x1dd0e50, size=9 }

  [-1, -1] 0
  [0, -1] 0
  [1, -1] 0
  [-1, 0] -1
  [0, 0] 1
  [1, 0] 0
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

.. breathelink:: itk::BackwardDifferenceOperator
