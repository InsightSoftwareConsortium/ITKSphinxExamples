Smooth Image While Preserving Edges (Curvature)
===============================================

.. index::
   single: VectorCurvatureAnisotropicDiffusionImageFilter
   single: curvature
   pair: smooth; image
   pair: preserve; edges

Synopsis
--------

Smooth an image while preserving edges.


Results
-------
.. note:: SmoothImageWhilePreservingEdges2.png
  :scale: 50%
  :alt: output in vtk window

  Output in VTK window.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VectorCurvatureAnisotropicDiffusionImageFilter
