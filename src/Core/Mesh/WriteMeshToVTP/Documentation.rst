Write Mesh To VTP
=================

.. index::
   single: VTKPolyDataWriter

Synopsis
--------

Write an itk::Mesh to a vtp (vtkPolyData) file.


Results
-------
.. warning::
  **Fix Errors**
  Example contains errors needed to be fixed for proper output.

Output::

  Points = 4
  [-1, -1, 0]
  [1, -1, 0]
  [1, 1, 0]
  [1, 1, 1]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VTKPolyDataWriter
