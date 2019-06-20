Smooth Image While Preserving Edges
===================================

.. index::
   single: VectorGradientAnisotropicDiffusionImageFilter
   single: smooth
   pair: preserve; edges

Synopsis
--------

Smooth an image while preserving edges.


Results
-------
.. figure:: SmoothImageWhilePreservingEdges.png
  :scale: 50%
  :scale: output in vtk window

  Output in VTK window.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VectorGradientAnisotropicDiffusionImageFilter
