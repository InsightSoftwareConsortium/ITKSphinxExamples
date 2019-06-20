Covariant Vector Dot Product
============================

.. index::
  single: Vector
  pair: Vector; operator *
  pair: dot; product

Synopsis
--------

Dot product of vectors.


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


Classes demonstrated
--------------------

.. breathelink:: itk::Vector
