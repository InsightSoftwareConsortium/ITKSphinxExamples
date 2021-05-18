:name: DelaunayConformEdgeFlipping

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

.. raw:: html

  <div class="figure">
    <iframe src="mushroom.html" width="315" height="240" seamless></iframe>
    <p class="caption">Interactive input mesh</p>
  </div>


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::DelaunayConformingQuadEdgeMeshFilter
