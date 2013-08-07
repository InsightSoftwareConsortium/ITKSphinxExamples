Delaunay Conform Edge Flipping
==============================

.. index::
   single: DelaunayConformingQuadEdgeMeshFilter
   single: MeshFileReader
   single: MeshFileWriter
   single: QuadEdgeMesh

Synopsis
--------


Flip the edges of one itk::QuadEdgeMesh to satisfy Delaunay condition.


Results
-------

.. figure:: InputMesh.png
  :scale: 50%
  :alt: Input mesh

  Input mesh

.. figure:: OutputMesh.png
  :scale: 50%
  :alt: Output image

  Output mesh


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::DelaunayConformingQuadEdgeMeshFilter
