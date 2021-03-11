Create Gaussian Derivative Kernel
=================================

.. index::
   single: GaussianDerivativeOperator
   pair: gaussian; derivative

Synopsis
--------

Create a Gaussian derivative kernel.


Results
-------
Output::

  Size: [3, 3]
  Neighborhood:
  Radius:[1, 1]
  Size:[3, 3]
  DataBuffer:NeighborhoodAllocator { this = 0x7ffee86419a8, begin = 0x7fb16bc5cc50, size=9 }
  [-1, -1] 0
  [0, -1] 0
  [1, -1] 0
  [-1, 0] 0.208375
  [0, 0] 0
  [1, 0] -0.208375
  [-1, 1] 0
  [0, 1] 0
  [1, 1] 0

Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::GaussianDerivativeOperator
