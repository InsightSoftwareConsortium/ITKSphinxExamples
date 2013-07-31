Cut Mesh
========

.. index::
   single: QuadEdgeMesh
   single: QuadEdgeMeshPolygonCell
   single: MeshFileReader
   single: MeshFileWriter
   double: QuadEdge, GetLnext
   double: QuadEdge, GetOnext
   double: QuadEdgeMeshPoint, CastFrom
   double: QuadEdgeMeshPolygonCell, GetEdgeRingEntry
   double: QuadEdgeMesh, AddPoint
   double: QuadEdgeMesh, AddFaceTriangle
   double: PointSet, GetPoints

Synopsis
--------

Given a bounding box and a mesh, first retrieve all vertices whose coordinates
are in the bounding box; then retrieve all faces connected to these vertices.

Results
-------

.. figure:: inputMesh.png
  :scale: 50%
  :alt: Input mesh

  Input mesh

.. figure:: outputMesh.png
  :scale: 50%
  :alt: Output mesh

  Output mesh (cut)


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::QuadEdgeMesh
