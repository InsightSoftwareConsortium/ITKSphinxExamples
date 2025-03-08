:name: CreateDerivativeKernel

Create Derivative Kernel
========================

.. index::
   single: DerivativeOperator
   pair: derivative; kernel

Synopsis
--------

Create a derivative kernel.

.. figure:: DerivativeOperator.png
  :scale: 70%
  :alt: DerivativeOperator.png

Applied a neighborhood iterator using a first-order derivative operator to approximate y-derivative

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


.. figure:: DerivativeKernel.png
  :scale: 70%
  :alt: DerivativeKernel.png



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

.. breathelink:: itk::DerivativeOperator
