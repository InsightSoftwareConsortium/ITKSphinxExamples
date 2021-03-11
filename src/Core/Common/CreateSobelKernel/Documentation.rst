Create Sobel Kernel
===================

.. index::
   single: SobelOperator
   pair: sobel; kernel

Synopsis
--------

Create the Sobel kernel.


Results
-------
Output::

  Neighborhood:
  Radius:[1, 1]
  Size:[3, 3]
  DataBuffer:NeighborhoodAllocator { this = 0x7ffee3e84a00, begin = 0x7fca93256b10, size=9 }
  -1
  0
  1
  -2
  0
  2
  -1
  0
  1

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

.. breathelink:: itk::SobelOperator
