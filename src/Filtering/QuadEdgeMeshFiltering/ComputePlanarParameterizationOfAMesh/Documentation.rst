Compute Planar Parameterization Of A Mesh
=========================================

.. index::
   single: ParameterizationQuadEdgeMeshFilter

Synopsis
--------

Compute planar parameterization of a surface mesh represented by one itk::QuadEdgeMesh.


Results
-------

.. figure:: InputMesh.png
  :scale: 100%
  :alt: Input mesh

  Input mesh

.. figure:: OutputMeshes.png
  :scale: 100%
  :alt: Output meshes

  Output planes with left column) SQUARE, and right column) DISK BorderType,
  and row 1) OnesMatrix, 2) InverseEuclideanMatrix 3) ConformalMatrix, 4)
  AuthalicMatrix, and 5) HarmonicMatrix CoefficientType.


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::ParameterizationQuadEdgeMeshFilter
