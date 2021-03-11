Convert Mesh to Unstructered Grid
=================================

.. index::
   single: Mesh

Synopsis
--------

Convert an itk::Mesh to a vtkUnstructuredGrid.


Results
-------
An Output.vtu file will be generated alone with the following output.

Output::

  Unstructered grid has 3 cells.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Mesh
