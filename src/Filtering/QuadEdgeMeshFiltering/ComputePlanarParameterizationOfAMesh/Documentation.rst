Compute Planar Parameterization of a Mesh
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

.. raw:: html

  <div class="figure">
    <iframe src="mushroom.html" width="400" height="300" seamless></iframe>
    <p class="caption">Interactive input mesh</p>
  </div>

  <div class="figure">
    <iframe src="param_border0_coeff0.html" width="400" height="300" seamless></iframe>
    <p class="caption">Interactive SQUARE BorderType, OnesMatrix CoefficientType output</p>
  </div>

  <div class="figure">
    <iframe src="param_border1_coeff0.html" width="400" height="300" seamless></iframe>
    <p class="caption">Interactive DISK BorderType, OnesMatrix CoefficientType output</p>
  </div>


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ParameterizationQuadEdgeMeshFilter
