Cut Mesh
========

.. index::
   single: QuadEdgeMesh
   single: QuadEdgeMeshPolygonCell
   single: MeshFileReader
   single: MeshFileWriter
   pair: QuadEdge; GetLnext
   pair: QuadEdge; GetOnext
   pair: QuadEdgeMeshPoint; CastFrom
   pair: QuadEdgeMeshPolygonCell; GetEdgeRingEntry
   pair: QuadEdgeMesh; AddPoint
   pair: QuadEdgeMesh; AddFaceTriangle
   pair: PointSet; GetPoints

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
