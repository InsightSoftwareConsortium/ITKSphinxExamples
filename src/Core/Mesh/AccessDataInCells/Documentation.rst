Access data in cells
====================

.. index::
   single: Mesh

Synopsis
--------

Just as custom data can be associated with points in the mesh,
it is also possible to associate custom data with cells. The type of the
data associated with the cells can be different from the data type
associated with points. By default, however, these two types are the same.
The following example illustrates how to access data associated with cells.
The approach is analogous to the one used to access point data.


Results
-------

::

  Points = 10
  Cells  = 9

  Cell 0 = 0
  Cell 1 = 1
  Cell 2 = 4
  Cell 3 = 9
  Cell 4 = 16
  Cell 5 = 25
  Cell 6 = 36
  Cell 7 = 49
  Cell 8 = 64


Code
----

C++
...

.. literalinclude:: Code.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::Mesh
