Compute Geodesic Distance On Mesh
=================================

.. index::
   single: FastMarchingQuadEdgeMeshFilterBase
   single: FastMarchingThresholdStoppingCriterion

Synopsis
--------

Compute the geodesic distance from a provided seed vertex on a mesh.


Results
-------

.. figure:: Input.png
  :scale: 100%
  :alt: Input mesh

  Input mesh

.. figure:: Output.png
  :scale: 100%
  :alt: Output mesh

  Output mesh

.. raw:: html

  <div class="figure">
    <iframe src="genusZeroSurface01.html" width="200" height="225" seamless></iframe>
    <p class="caption">Interactive input mesh</p>
  </div>

  <div class="figure">
    <iframe src="ComputeGeodesicDistanceOnMeshOutput.html" width="200" height="225" seamless></iframe>
    <p class="caption">Interactive output mesh</p>
  </div>


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::FastMarchingQuadEdgeMeshFilterBase
