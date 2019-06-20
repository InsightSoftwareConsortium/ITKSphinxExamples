Create Gaussian Kernel
======================

.. index::
   single: GaussianOperator
   pair: kernel; gaussian
   pair: create; kernel

Synopsis
--------

Create a Gaussian kernel.


Results
-------
Output::

  Size: [3, 3]
  Neighborhood:
  Radius:[1, 1]
  Size:[3, 3]
  DataBuffer:NeighborhoodAllocator { this = 0x7ffee598a9d8, begin = 0x7f7f502572a0, size=9 }
  [-1, -1] 0
  [0, -1] 0
  [1, -1] 0
  [-1, 0] 0.208375
  [0, 0] 0.466801
  [1, 0] 0.208375
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

.. breathelink:: itk::GaussianOperator
