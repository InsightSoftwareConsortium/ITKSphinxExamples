Matrix
======

.. index::
   single: Matrix

Synopsis
--------

This will create and display a matrix of NxN dimensions, then multiply it by a vector of N dimension.


Results
-------
Output::

  M: 1 2 3
     4 5 6
     7 8 9

  M: 1 2 3
     4 5 6
     7 8 9

  V: [1, 2, 3]
  MV: [14, 32, 50]

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
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::Matrix
