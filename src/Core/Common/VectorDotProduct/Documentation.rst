Vector Dot Product
==================

.. index::
  single: Vector
  pair: Vector; operator *

Synopsis
--------

Dot product of Vectors


Results
-------

Output::

  u :[-1, 1, -1]
  v :[1, 2, 3]
  DotProduct( u, v ) = -2
  u - DotProduct( u, v ) * v = [1, 5, 5]


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::Vector
