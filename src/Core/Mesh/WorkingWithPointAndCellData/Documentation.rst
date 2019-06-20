Working With Point And Cell Data
================================

.. index::
   single: Mesh
   pair: point; data
   pair: cell; data

Synopsis
--------

Associate point and cell data with a mesh.


Results
-------
.. figure:: mesh.vtk
  :scale: 70%
  :alt: mesh.vtk

  Mesh created.

Output::

  66
  66
  5

  128
  128
  10

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Mesh
